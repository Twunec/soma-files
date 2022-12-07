// IntfTool.cpp: implementation of the CIntfTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "IntfTool.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CIntfTool::CIntfTool()
{
	MAKE_ZERO(m_pIntfClips);
	New();
}

CIntfTool::~CIntfTool()
{
	ClipBoardClear();
}

void CIntfTool::New()
{
	this->IntfRelease();
	MAKE_ZERO(m_Header);
	
	DELETE_SAFE(m_pAniObj);
	m_pAniObj = new CAniObjLSP();
}

void CIntfTool::Save(const char* szFileName)
{
	CFile file;
	file.Open(szFileName, CFile::modeWrite | CFile::modeCreate);
	
	_INTF_HEADER Header = m_Header; // �ӽ÷� �ִ� �͸� ã�Ƽ� ����..

	Header.nQt = 0;
	for(int i = 0; i < MAX_INTF; i++)
	{
		if(m_pIntfs[i]) Header.nQt++;
	}

	file.Write(&Header, sizeof(_INTF_HEADER)); // �������̽� ��� ����.

	BOOL bSetRgnDefault = FALSE;
	for(i = 0; i < MAX_INTF; i++)
	{
		if(m_pIntfs[i] == NULL) continue;
		if(m_pIntfs[i]->nParentLayer < 0 || m_pIntfs[i]->nParentLayer >= MAX_LAYER) 
		{
			MessageBox(NULL, "���̾� ��ȣ�� �߸��Ǿ� �ֽ��ϴ�. �ٽ� ������ �ּ���", "���� ���� ����", MB_OK);
			file.Close();
			return;
		}
		
		// ��ư ���� üũ..
		if(m_pIntfs[i]->nType != INTF_TYPE_NORMAL) // ����� ���� �ִ� �������̽��̸�...
		{
			if(	(m_pIntfs[i]->rcRgn.right - m_pIntfs[i]->rcRgn.left < 3 &&
				m_pIntfs[i]->rcRgn.bottom - m_pIntfs[i]->rcRgn.top < 3) || m_pIntfs[i]->rcRgn.left < 0 || m_pIntfs[i]->rcRgn.top < 0)
			{	
				if(bSetRgnDefault == FALSE)
				{
					CString str;
					str.Format("�������� �ʹ� �۰ų� �������� �ʾҽ��ϴ� : �������̽� ��ȣ %d - ��� �⺻������ �����Ͻðڽ��ϱ�?", i);
					int id = MessageBox(NULL, str, "�⺻�� ���� Ȯ��", MB_YESNO);
					if(id == IDYES) bSetRgnDefault = TRUE;
				}
				
				if(bSetRgnDefault == TRUE)
				{
					_ANI_DATA* pAni = m_pAniObj->AniDataGet(m_pIntfs[i]->nAnis[0]);
					if(pAni)
					{
						const _SPR_LSP* pSpr;
						m_pAniObj->SprGet(pAni->pnFrms[0], &pSpr);
						if(pSpr)
						{
							m_pIntfs[i]->rcRgn.left = m_pIntfs[i]->ptView.x + pSpr->rcV.left;
							m_pIntfs[i]->rcRgn.top = m_pIntfs[i]->ptView.y + pSpr->rcV.top;
							m_pIntfs[i]->rcRgn.right = m_pIntfs[i]->ptView.x + pSpr->rcV.right;
							m_pIntfs[i]->rcRgn.bottom = m_pIntfs[i]->ptView.y + pSpr->rcV.bottom;
						}
					}
				}
			}
			// ��ũ�ѹٿ� ���̾� üũ
			if(	(m_pIntfs[i]->nType & INTF_TYPE_DIAL_LR) || 
				(m_pIntfs[i]->nType & INTF_TYPE_DIAL_TB) || 
				(m_pIntfs[i]->nType & INTF_TYPE_SCROLL_LR) || 
				(m_pIntfs[i]->nType & INTF_TYPE_SCROLL_TB) ||
				(m_pIntfs[i]->nType & INTF_TYPE_PROGRESS) ) 
			{
				// �ʱⰪ�� ��ũ��(���̾�) �ּ�,�ִ밪 ����..
				if(m_pIntfs[i]->nFlags[0] >= m_pIntfs[i]->nFlags[1])
				{
					CString str;
					str.Format("�ּ�, �ִ밪�� �������� �ʾҽ��ϴ� : �������̽� ��ȣ %d - �⺻��(0 ~ 100)���� �Ͻðڽ��ϱ�?", i);
					if(MessageBox(NULL, str, "�⺻�� ���� Ȯ��", MB_YESNO) == IDYES)
					{
						m_pIntfs[i]->nFlags[0] = 0;
						m_pIntfs[i]->nFlags[1] = 100;
					}
				}
			}
		}
		file.Write(m_pIntfs[i], sizeof(_INTF_DATA)); // �������̽� ������ �б�.
		if(m_pIntfs[i]->nText > 0) file.Write(m_pIntfs[i]->szText, m_pIntfs[i]->nText); // �ؽ�Ʈ ������ ����.
	}
	file.Close();
}

void CIntfTool::ImportSpr(const char* szFileName, int nPF)
{
	lstrcpy(m_Header.szSprFN, szFileName);

	m_pAniObj->SprLoad(szFileName, nPF);
}

void CIntfTool::ImportAni(const char* szFileName)
{
	lstrcpy(m_Header.szAniFN, szFileName);

	m_pAniObj->AniLoad(szFileName);
	m_pAniObj->AniCtrlAlloc(MAX_ANI_CTRL); // �ִ��� �Ҵ��ϰ�.. �������̽� �ϳ��� �ϳ��� ���ϸ��̼� �Ҵ�..
}

// ������ ã�Ƽ� �Ҵ�. �����ϸ� -1
int CIntfTool::Add()
{
	for(int i = 0; i < MAX_INTF; i++)
	{
		if(m_pIntfs[i] == NULL) // ��� ã����..
		{
			m_pIntfs[i] = new _INTF_DATA;
			MAKE_ZERO(*m_pIntfs[i]);
			return i;
		}
	}
	return -1;
}

void CIntfTool::Delete(int index) // �߰� ����.
{
	if(index < 0 || index >= MAX_INTF) return;
	
	if(m_pIntfs[index])
	{
		DELETE_ARRAY_SAFE(m_pIntfs[index]->szText);
		DELETE_SAFE(m_pIntfs[index]);
	}
}

void CIntfTool::ClipBoardAdd(int index)
{
	if(index < 0 || index >= MAX_INTF) return;
	if(m_pIntfs[index] == NULL) return;

	for(int i = 0; i < MAX_INTF; i++)
	{
		if(m_pIntfClips[i] == NULL)
		{
			m_pIntfClips[i] = new _INTF_DATA;
			MAKE_ZERO(*m_pIntfClips[i]);
			memcpy(m_pIntfClips[i], m_pIntfs[index], sizeof(_INTF_DATA));
			m_pIntfClips[i]->szText = NULL;
			if(m_pIntfClips[i]->nText > 0)
			{
				m_pIntfClips[i]->szText = new char[m_pIntfClips[i]->nText + 1];
				lstrcpy(m_pIntfClips[i]->szText, m_pIntfs[index]->szText);
			}
			return;
		}
	}
}

void CIntfTool::ClipBoardClear()
{
	for(int i = 0; i < MAX_INTF; i++)
	{
		if(m_pIntfClips[i])
		{
			DELETE_ARRAY_SAFE(m_pIntfClips[i]->szText);
			DELETE_SAFE(m_pIntfClips[i]);
		}
	}
}

void CIntfTool::ClipBoardPaste(int nDestIntf, int nSeq, int nParentLayer)
{
	if(nParentLayer < 0 || nParentLayer >= MAX_LAYER) return;
	if(nDestIntf < 0 || nDestIntf >= MAX_INTF) return;
	if(nSeq < 0 || nSeq >= MAX_INTF) return;
	if(m_pIntfs[nDestIntf] == NULL) return;
	if(m_pIntfClips[nSeq] == NULL) return;

	DELETE_ARRAY_SAFE(m_pIntfs[nDestIntf]->szText);
	memcpy(m_pIntfs[nDestIntf], m_pIntfClips[nSeq], sizeof(_INTF_DATA));
	m_pIntfs[nDestIntf]->szText = NULL;
	if(m_pIntfs[nDestIntf]->nText > 0)
	{
		m_pIntfs[nDestIntf]->szText = new char[m_pIntfs[nDestIntf]->nText + 1];
		lstrcpy(m_pIntfs[nDestIntf]->szText, m_pIntfClips[nSeq]->szText);
	}
}

int CIntfTool::ClipBoardGetQt()
{
	int nQt = 0;
	for(int i = 0; i < MAX_INTF; i++)
	{
		if(m_pIntfClips[i] == NULL) return i;
	}
	
	return 0;
}
