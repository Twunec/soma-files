// Item.cpp: implementation of the CItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Item.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItem::CItem()
{
	MAKE_ZERO(m_Header);
	MAKE_ZERO(m_pDatas);
	m_pAniObj = new CAniObjLSP();
}

CItem::~CItem()
{
	this->Release();
	DELETE_SAFE(m_pAniObj);
}

void CItem::Alloc(int nQt)
{
	if(nQt <= 0 || nQt > MAX_ITEM) return;

	m_Header.nQt = nQt;
	for(int i = 0; i < m_Header.nQt; i++)
	{
		if(m_pDatas[i] == NULL)
		{
			m_pDatas[i] = new _ITEM_DATA;
			MAKE_ZERO(*m_pDatas[i]);
		}
	}
}

void CItem::Release()
{
	m_pAniObj->SprRelease();
	m_pAniObj->AniRelease();
	MAKE_ZERO(m_Header);
	for(int i = 0; i < MAX_ITEM; i++)
	{
		if(m_pDatas[i])
		{
			DELETE_ARRAY_SAFE(m_pDatas[i]->szRemark);
			DELETE_ARRAY_SAFE(m_pDatas[i]->szRemarkNPC);
			DELETE_SAFE(m_pDatas[i]);
		}
	}
}

_ITEM_DATA* CItem::DataGet(int index)
{
	if(index < 0 || index >= MAX_ITEM) return NULL;
	return m_pDatas[index];
}

void CItem::Load(const char *szFileName, const char *szAniPath, const char *szSprPath, int nPF)
{
	HANDLE hFile;
	DWORD dwCount;

	hFile = CreateFile( szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		OutputDebugString("���� ���� ���� : ");
		OutputDebugString(szFileName);
		OutputDebugString("\n");
		return;
	}

	this->Release();
	
	ReadFile(hFile, &m_Header, sizeof(_ITEM_HEADER), &dwCount, NULL); // �������̽� ��� �б�.

	this->Alloc(m_Header.nQt);

	int i;
	for(i = 0; i < m_Header.nQt; i++)
	{
		ReadFile(hFile, m_pDatas[i], sizeof(_ITEM_DATA), &dwCount, NULL); // �������̽� ������ �б�.
		m_pDatas[i]->szRemark = NULL;
		if(m_pDatas[i]->snRemark > 0)
		{
			m_pDatas[i]->szRemark = new char[m_pDatas[i]->snRemark + 1];
			ReadFile(hFile, m_pDatas[i]->szRemark, m_pDatas[i]->snRemark, &dwCount, NULL);
			lstrcat(m_pDatas[i]->szRemark, "");
		}
		m_pDatas[i]->szRemarkNPC = NULL;
		if(m_pDatas[i]->snRemarkNPC > 0)
		{
			m_pDatas[i]->szRemarkNPC = new char[m_pDatas[i]->snRemarkNPC + 1];
			ReadFile(hFile, m_pDatas[i]->szRemarkNPC, m_pDatas[i]->snRemarkNPC, &dwCount, NULL);
			lstrcat(m_pDatas[i]->szRemarkNPC, "");
		}
	}
	CloseHandle(hFile);

	SetCurrentDirectory(szAniPath); // ���ϸ��̼�, ��������Ʈ �б�...
	m_pAniObj->AniLoad(m_Header.szAniFN);
	m_pAniObj->AniCtrlAlloc(m_Header.nQt); // ���� ��ŭ ���ϸ��̼� ���� �Ҵ�...
	for(i = 0; i < m_Header.nQt; i++)
	{
		m_pAniObj->AniSet(m_pDatas[i]->nAni, FL_ANI_LOOP, i); // ���ϸ��̼� ����
	}
	SetCurrentDirectory(szSprPath);
	m_pAniObj->SprLoad(m_Header.szSprFN, nPF);
}
