// MapObj.cpp: implementation of the CMapObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MapObj.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapObj::CMapObj()
{
	MAKE_ZERO(m_Header);
	m_hData = NULL;
	m_pnData = NULL;
	m_pTData = NULL;
}

CMapObj::~CMapObj()
{
	Release();
	if(m_pTData) delete[] m_pTData;
}

void CMapObj::Release()
{
	// �޸� ����..
	MAKE_ZERO(m_Header);
	if(m_hData)
	{
		GlobalUnlock(m_hData);
		GlobalFree(m_hData);
	}
	m_hData = NULL;
	m_pnData = NULL;
}

void CMapObj::Alloc(int nWidth, int nHeight)
{
	if(nWidth <= 0 || nHeight <= 0) return;

	if(m_hData != NULL)
	{
		this->Release();
	}

	m_Header.nWidth = nWidth;
	m_Header.nHeight = nHeight;

	// �Ҵ��ϰ� ��..
	m_hData = GlobalAlloc(GMEM_FIXED, sizeof(short int)*nWidth*nHeight);
	m_pnData = (short int*)GlobalLock(m_hData);
	memset(m_pnData, -1, sizeof(short int)*nWidth*nHeight); // �ʱ�ȭ ���̾�� �Ѵ�!!!
}

// ���ǽ��� ���� �ҷ� �־�� �Ѵ�..
void CMapObj::Load(const char *szFileName)
{
	HANDLE hFile;
	DWORD dwCount;
	int i, count;

	hFile = CreateFile( szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{ 
		OutputDebugString("Ÿ�ϸ� ������ ���� ���� ���� : ");
		OutputDebugString(szFileName);
		OutputDebugString("\n");
		return;
	}
	
	ReadFile(hFile, &m_Header, sizeof(_MAP_OBJ_HEADER), &dwCount, NULL);

	this->Alloc(m_Header.nWidth, m_Header.nHeight);
	
	ReadFile(hFile, &count, sizeof(int), &dwCount, NULL);
	if(count > 0)
	{
		if(m_pTData) delete[] m_pTData;
		m_pTData = new SAVE_BUF[count];
		m_vTCount = count;
		ReadFile(hFile, m_pTData, sizeof(SAVE_BUF)*m_vTCount, &dwCount, NULL);
		for(i = 0; i < m_vTCount; i++)
		{
			m_pnData[m_pTData[i].index] = m_pTData[i].value;
		}
	}
	
	CloseHandle(hFile);
}

void CMapObj::Load(HANDLE& hFile)
{
	DWORD dwCount;
	int i, count;
	SAVE_BUF *t_buf;

	ReadFile(hFile, &m_Header, sizeof(_MAP_OBJ_HEADER), &dwCount, NULL);
	this->Alloc(m_Header.nWidth, m_Header.nHeight);
	
	ReadFile(hFile, &count, sizeof(int), &dwCount, NULL);
	if(count > 0)
	{
		if(m_pTData) delete[] m_pTData;
		m_pTData = new SAVE_BUF[count];
		m_vTCount = count;
		ReadFile(hFile, m_pTData, sizeof(SAVE_BUF)*m_vTCount, &dwCount, NULL);
		for(i = 0; i < m_vTCount; i++)
		{
			m_pnData[m_pTData[i].index] = m_pTData[i].value;
		}
	}
}
