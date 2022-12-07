// Char.cpp: implementation of the CCharRes class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "soma.h"
#include "CharRes.h"
#include "DManage/BB_Direct.h"
#include "ChildView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

SPR_DATA::SPR_DATA()
{
	m_arrSprData = NULL;
	m_arrVData = NULL;
	m_AniData.pnFrms = NULL;
}

SPR_DATA::~SPR_DATA()
{
	if(m_AniData.pnFrms) delete[] m_AniData.pnFrms;

	if(m_arrSprData)
	{
		delete[] m_arrSprData;
	}

	if(m_arrVData)
	{
		for(int i = 0; i < m_HSpr.nQt; i++)
		{
			delete[] m_arrVData[i];
		}
		delete[] m_arrVData;
	}
}
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCharRes::CCharRes()
{
	int i;

	for(i = 0; i < MAX_RES_COUNT; i++)
	{
		m_CharRes[i] = NULL;
		m_bLoad[i] = FALSE;
	}
	m_vIndex = 0;
}

CCharRes::~CCharRes()
{
	RemoveAllData();
}

void CCharRes::RemoveAllData()
{
	int i;

	for(i = 0; i < MAX_RES_COUNT; i++)
	{
		if(m_CharRes[i])
		{
			delete m_CharRes[i];
			m_CharRes[i] = NULL;
		}
	}
}

BOOL CCharRes::LoadElement(int ani_index)
{
	CFile spr_file, ani_file;
	int i;
	CString szSprFileName, szAniFileName;
	const CString szExePath = CDirectDraw::GetExecutionPath();
	WORD *word;
	SPR_DATA *spr_data;

	m_bLoad[ani_index] = TRUE;

	szSprFileName.Format("%sman\\man%03d%02d%s", (LPCTSTR)szExePath ,m_vIndex ,ani_index,".spl");
	szAniFileName.Format("%sman\\man%03d%02d%s", (LPCTSTR)szExePath ,m_vIndex ,ani_index,".ani");

	if(spr_file.Open(szSprFileName, CFile::modeRead) == FALSE) return FALSE;
	if(ani_file.Open(szAniFileName, CFile::modeRead) == FALSE) 
	{
		spr_file.Close();
		return FALSE;
	}

	spr_data = new SPR_DATA;
	////////////////////////////////////////////////////////////////////////////////
	// ��������Ʈ �� ĳ���� ������..................................................
	spr_file.Read(&spr_data->m_HSpr, sizeof(_SPR_HEADER));
	spr_file.Seek(sizeof(_SPR_TOOL)*spr_data->m_HSpr.nQt, CFile::current);

	if(spr_data->m_HSpr.nQt > 0)
	{
		spr_data->m_arrSprData = new _SPR_LSP[spr_data->m_HSpr.nQt];
		spr_data->m_arrVData = new WORD *[spr_data->m_HSpr.nQt];

		for (i=0; i<spr_data->m_HSpr.nQt; i++)
		{
			spr_file.Read((PVOID)&spr_data->m_arrSprData[i], sizeof(_SPR_LSP));
			spr_data->m_arrSprData[i].pwV = NULL;
		}

		for(i=0; i<spr_data->m_HSpr.nQt; i++) 	// ���� ��������Ʈ ������
		{
			int count = spr_data->m_arrSprData[i].nDataSize;
			if(count)
			{
				word = new WORD[count>>1];
				spr_file.Read((PVOID)word, count);
				if(CChildView::CharManager.GetPixelFormat() == PF_555) Decode2_555(spr_data->m_arrSprData[i].nLine, word);
				else Decode2_565_0(spr_data->m_arrSprData[i].nLine, word);
				spr_data->m_arrVData[i] = word;
			}
			else
			{
				spr_data->m_arrVData[i] = NULL;
			}
		}
	}
	
	// �ִ� ������ �ҷ�����
	ani_file.Read((PVOID)&spr_data->m_HAni, sizeof(_ANI_HEADER));
	ani_file.Read((PVOID)&spr_data->m_AniData, sizeof(_ANI_DATA));

	if(spr_data->m_AniData.nMaxFrm > 0)
	{
		int nQt = spr_data->m_HAni.nDirQt * spr_data->m_AniData.nMaxFrm;
		spr_data->m_AniData.pnFrms = new short int[nQt];
		ani_file.Read(spr_data->m_AniData.pnFrms, nQt*2);
	}

	m_CharRes[ani_index] = spr_data;

	spr_file.Close();
	ani_file.Close();

	return TRUE;
}

BOOL CCharRes::Load(LPCSTR	szFileName, int pf, int index)
{
	DWORD loadtime = ::GetTickCount();
	RemoveAllData();

	CFile spr_file, ani_file;
	int i;
	CString szSprFileName, szAniFileName;
	const CString szExePath = CDirectDraw::GetExecutionPath();
	WORD *word;
	SPR_DATA *spr_data;

	// 14�� ���ϸ��̼� ��...�������� ����� ������..
	UINT count;

//�켮.. 17�� 18�ιٲ�.. ���ھִϴ� ȭ���� 18���̴�...
	for(int k = 0; k < 18; k++)
	{
		szSprFileName.Format("%sman\\man%03d%02d%s", (LPCTSTR)szExePath ,index ,k,".spl");
		szAniFileName.Format("%sman\\man%03d%02d%s", (LPCTSTR)szExePath ,index ,k,".ani");

		if(spr_file.Open(szSprFileName, CFile::modeRead) == FALSE) continue;
		if(ani_file.Open(szAniFileName, CFile::modeRead) == FALSE) 
		{
			spr_file.Close();
			continue;
		}

		spr_data = new SPR_DATA;
		////////////////////////////////////////////////////////////////////////////////
		// ��������Ʈ �� ĳ���� ������..................................................
		spr_file.Read(&spr_data->m_HSpr, sizeof(_SPR_HEADER));
		spr_file.Seek(sizeof(_SPR_TOOL)*spr_data->m_HSpr.nQt, CFile::current);

		if(spr_data->m_HSpr.nQt > 0)
		{
			spr_data->m_arrSprData = new _SPR_LSP[spr_data->m_HSpr.nQt];
			spr_data->m_arrVData = new WORD *[spr_data->m_HSpr.nQt];

			for (i=0; i<spr_data->m_HSpr.nQt; i++)
			{
				spr_file.Read((PVOID)&spr_data->m_arrSprData[i], sizeof(_SPR_LSP));
				spr_data->m_arrSprData[i].pwV = NULL;
			}

			for(i=0; i<spr_data->m_HSpr.nQt; i++) 	// ���� ��������Ʈ ������
			{
				count = spr_data->m_arrSprData[i].nDataSize;
				if(count)
				{
					word = new WORD[count>>1];
					spr_file.Read((PVOID)word, count);
//					if(pf == PF_555) Decode2_555(spr_data->m_arrSprData[i].nLine, word);
					if(CChildView::CharManager.GetPixelFormat() == PF_555) Decode2_555(spr_data->m_arrSprData[i].nLine, word);
					else Decode2_565_0(spr_data->m_arrSprData[i].nLine, word);

					spr_data->m_arrVData[i] = word;
				}
				else
				{
					spr_data->m_arrVData[i] = NULL;
				}
			}
		}
		
		// �ִ� ������ �ҷ�����
		ani_file.Read((PVOID)&spr_data->m_HAni, sizeof(_ANI_HEADER));
		ani_file.Read((PVOID)&spr_data->m_AniData, sizeof(_ANI_DATA));

		if(spr_data->m_AniData.nMaxFrm > 0)
		{
			int nQt = spr_data->m_HAni.nDirQt * spr_data->m_AniData.nMaxFrm;
			spr_data->m_AniData.pnFrms = new short int[nQt];
			ani_file.Read(spr_data->m_AniData.pnFrms, nQt*2);
		}

		m_CharRes[k] = spr_data;

		spr_file.Close();
		ani_file.Close();
	}

	DWORD loadendtime = ::GetTickCount();
	TRACE(" %d �� ���� �ð� %d.\n", index, (int)(loadendtime-loadtime));
	return TRUE;
}

void CCharRes::Decode2_555(int nLine, WORD *data) //565�� �Ǿ��ִ� �����͸� 555 ī�忡 �µ��� �� ���� (LSP����)
{
	WORD* tmp = data;
	int node; int np; // ��� �� ��ȿ �ȼ� ��
	for(int y = 0; y < nLine; y++)
	{
		node = *tmp; tmp++;
		for(;node;node--, tmp+=np)
		{
			tmp++; // 0 �κ� skip... 
			np = *tmp; tmp++;
			for(;np; np--)
			{
				*tmp = ((*tmp&0xffc0)>>1) | (*tmp&0x001f);
				tmp++;
			}
		}
	}
}

void CCharRes::Decode2_565_0(int nLine, WORD *data) //565�� �Ǿ��ִ� �����͸� 555 ī�忡 �µ��� �� ���� (LSP����)
{
	WORD* tmp = data;
	int node; int np; // ��� �� ��ȿ �ȼ� ��
	for(int y = 0; y < nLine; y++)
	{
		node = *tmp; tmp++;
		for(;node;node--, tmp+=np)
		{
			tmp++; // 0 �κ� skip... 
			np = *tmp; tmp++;
			for(;np; np--)
			{
				if( *tmp & 0x20 )
				*tmp -= 0x20;
				tmp++;
//				*tmp = ((*tmp&0xffc0)>>1) | (*tmp&0x001f);
//				tmp++;
			}
		}
	}
}

SPR_DATA *CCharRes::GetSprData(int ani_number)
{
	if(ani_number < 0 || ani_number >= MAX_RES_COUNT) return NULL;

	if(m_bLoad[ani_number] == FALSE) LoadElement(ani_number);

	return m_CharRes[ani_number];
}
