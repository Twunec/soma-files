// ObjBasic.cpp: implementation of the CObjBasic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ObjBasic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "DDEngineLSP.h"

CObjBasic::CObjBasic()
{
	MAKE_ZERO(m_Header);
	m_bReferenceAniObj = FALSE;
	m_nAniCtrl = 0;
	m_ptCur.x = 0; m_ptCur.y = 0;
	m_nDir = 0;
	MAKE_ZERO(m_pAniObjs);
}

CObjBasic::~CObjBasic()
{
	this->Release();
}

// ������ ���ָ� ������ �ʴ´�.
void CObjBasic::SetReferenceAniObj(BOOL bReferenceAniObj)
{
	this->Release();
	m_bReferenceAniObj = bReferenceAniObj; 
} 

void CObjBasic::AniObjSet(int index, int nAniCtrl, CAniObjLSP* pAniObj)
{
	if(m_bReferenceAniObj == FALSE) return; // ������ �ٸ� ���ϸ��̼� ������Ʈ �����͸� ���� ������ ���ư���.

	if(index < 0 || index >= MAX_OBJ_ANI) return;
	if(nAniCtrl < 0 || nAniCtrl >= MAX_ANI_CTRL) return;

	if(index == 0) m_nAniCtrl = nAniCtrl;
	m_pAniObjs[index] = pAniObj;
}

void CObjBasic::Release()
{
	MAKE_ZERO(m_Header);
	m_nAniCtrl = 0;
	m_ptCur.x = 0; m_ptCur.y = 0;
	m_nDir = 0;
	if(m_bReferenceAniObj == FALSE) this->ReleaseAniObjs(); // ������ �ƴ� �ڱ� �ڽ��� ���� ������ ����...
	MAKE_ZERO(m_pAniObjs);
}

void CObjBasic::Load(const char *szFileName, const char *szAniPath, const char *szSprPath, int nAniCtrlQt, int nPF)
{
	if(m_bReferenceAniObj == TRUE) return; // ������ �ٸ� ���ϸ��̼� ������Ʈ �����͸� ���� ������ ���ư���.

	DWORD dwCount = 0;
	HANDLE hFile = CreateFile(szFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		OutputDebugString("������Ʈ ���� �θ��� ���� : ");
		OutputDebugString(szFileName);
		OutputDebugString("\n");
		return;
	}
	ReadFile(hFile, &m_Header, sizeof(_OBJ_HEADER), &dwCount, NULL);
	CloseHandle(hFile);

	SetCurrentDirectory(szSprPath); // ��������Ʈ �ε�..
	for(int i = 0; i < MAX_OBJ_ANI; i++)
	{
		if(lstrlen(m_Header.szSprFNs[i]) > 0)
		{
			if(m_pAniObjs[i] == NULL) m_pAniObjs[i] = new CAniObjLSP();
			m_pAniObjs[i]->SprLoad(m_Header.szSprFNs[i], nPF);
		}
	}

	SetCurrentDirectory(szAniPath);
	if(m_pAniObjs[0])
	{
		m_pAniObjs[0]->AniLoad(m_Header.szAniFN);
		m_pAniObjs[0]->AniCtrlAlloc(nAniCtrlQt);
	}

	m_bReferenceAniObj = FALSE;
}

// ���붧�� ���� ���� �ʴ´�.. �ֳ�! ���� ������ ��찡 �����ϱ� �׷���.
// �׷� ���� �̰� ȣ���ϴ���! -> �������� �ʰ� �������� �������� ��츸 �Ѵ�.!!
void CObjBasic::ReleaseAniObjs()
{
	for(int i = 0; i < MAX_OBJ_ANI; i++)
	{
		DELETE_SAFE(m_pAniObjs[i]);
	}
}

void CObjBasic::Render(CDDEngineLSP *pEng, POINT ptScroll)
{
	BOOL bBBLocked = pEng->IsBBLocked();
	if(bBBLocked == FALSE) pEng->BackBufferLock();

	if(m_pAniObjs[0] == NULL) return;

	int nSpr = m_pAniObjs[0]->FrmGetAnimated(m_nAniCtrl);

	int nRenderType;
	const _SPR_LSP* pSpr;
	for(int i = 0; i < MAX_OBJ_ANI; i++)
	{
		if(m_pAniObjs[i] == NULL) continue;
		m_pAniObjs[i]->SprGet(nSpr, &pSpr);
		if(pSpr == NULL) continue;

		if(i == 0) nRenderType = RENDER_SHADOW; // �׸���.. 
		else nRenderType = RENDER_NORMAL;

		pEng->BltLSP(NULL, m_ptCur.x - ptScroll.x, m_ptCur.y - ptScroll.y, pSpr, nRenderType, 16);
	}
	
	if(bBBLocked == FALSE) pEng->BackBufferUnlock();
}
