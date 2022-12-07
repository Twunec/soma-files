// Script.cpp: implementation of the CScript class.
//
//////////////////////////////////////////////////////////////////////

#include "stdAfx.h"
#include "Script.h"

CScript::CScript()
{
	m_dwTickDelay = 0;
	MAKE_ZERO(m_Header);
	m_nIndex = 0;
	MAKE_ZERO(m_pDatas);
	MAKE_ZERO(m_szFileName);
}

CScript::~CScript()
{
	this->Release();
}

const _SCT_DATA* CScript::Get()
{
	return m_pDatas[m_nIndex];
}

const _SCT_DATA* CScript::Get(int index)
{
	if(index < 0 || index >= m_Header.nQt) return NULL; // �Ҵ�� ������ �����..
	return m_pDatas[index];
}

void CScript::Load(const char* szFileName)
{
	HANDLE hFile;
	DWORD dwReadCount;
	
	// ���� �͵��� �����ش�.
	Release();

	hFile = CreateFile( szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
	if(hFile == INVALID_HANDLE_VALUE)
	{ 
		MessageBox(NULL, szFileName, "���� ���� ����", MB_OK);
		return;
	}

	lstrcpy(m_szFileName, szFileName); // ������� ���� �ֱ� �ε��� ��ũ��Ʈ�����̸��� ����� �д�.

	SetFilePointer(hFile, 0, 0, FILE_BEGIN);

	// ��� �б�
	ReadFile(hFile, &m_Header, sizeof(_SCT_HEADER), &dwReadCount, NULL);

	// ���� ��ŭ �޸� ���� �Ҵ��ϰ�..
	Alloc(m_Header.nQt);
	
	//  �д´�.
	for(int i = 0; i < m_Header.nQt; i++)
	{
		ReadFile(hFile, m_pDatas[i], sizeof(_SCT_DATA), &dwReadCount, NULL);
		if(m_pDatas[i]->nText > 0)
		{
			m_pDatas[i]->szText = new char[m_pDatas[i]->nText+1];
			ReadFile(hFile, m_pDatas[i]->szText, m_pDatas[i]->nText, &dwReadCount, NULL);
			m_pDatas[i]->szText[m_pDatas[i]->nText] = NULL;
		}
	}
	CloseHandle(hFile);

	m_nIndex = 0; // �ε����� 0 ����..
}

void CScript::Release()
{
	for(int i=0; i < MAX_SCT; i++)
	{
		if(m_pDatas[i] != NULL)
		{
			if(m_pDatas[i]->szText) delete [] m_pDatas[i]->szText; m_pDatas[i]->szText = NULL;
			delete m_pDatas[i];
			m_pDatas[i] = NULL;
		}
	}
	MAKE_ZERO(m_Header);	// ��������Ʈ ����� �η�..
	this->m_nIndex = 0;
}

void CScript::Alloc(int nQt)
{
	if(nQt <= 0 || nQt > MAX_SCT) return;

	m_Header.nQt = nQt;
	
	// �Ҵ� �� �ʱ�ȭ...
	for(int i = 0; i < nQt; i++)
	{
		if(m_pDatas[i])
		{
			if(m_pDatas[i]->szText) { delete m_pDatas[i]->szText; m_pDatas[i]->szText = NULL; }
			delete m_pDatas[i];
			m_pDatas[i] = NULL;
		}
		m_pDatas[i] = new _SCT_DATA;
		MAKE_ZERO(*m_pDatas[i]);
	}
}
