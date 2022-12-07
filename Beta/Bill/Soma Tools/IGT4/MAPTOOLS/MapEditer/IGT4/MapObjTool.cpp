// MapObjTool.cpp: implementation of the CMapObjTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "igt4.h"
#include "MapObjTool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMapObjTool::CMapObjTool()
{

}

CMapObjTool::~CMapObjTool()
{

}

void CMapObjTool::Save(const char *szFileName)
{
	CFile file;
	file.Open(szFileName, CFile::modeWrite | CFile::modeCreate);

	m_Header.szID[0] = 'M';
	m_Header.szID[1] = 'O';
	m_Header.szID[2] = 'B';
	m_Header.szID[3] = 'J'; 

	wsprintf(m_Header.szRemark, "�� ������Ʈ ��ġ ������ - �ʺ� : %d�� ���� %d��", m_Header.nWidth, m_Header.nHeight);
	file.Write(&m_Header, sizeof(m_Header));

	file.Write(m_pnData, sizeof(short int)*m_Header.nWidth*m_Header.nHeight);
	
	file.Close();
}


void CMapObjTool::Realloc(int nWidth, int nHeight)
{
	if(nWidth <= 0 || nWidth > MAX_TILE_MAP_WIDTH || nHeight <= 0 || nHeight > MAX_TILE_MAP_HEIGHT ) return;

	HGLOBAL		hTmpOld = NULL;
	short int*	pTmpOld = NULL;
	
	int nOldW = m_Header.nWidth;
	int nOldH = m_Header.nHeight;

	int i = 0;

	if(nOldW > 0 && nOldH > 0) // ���� ������ �����͸� ������ ���´�.
	{
		hTmpOld = m_hData;
		pTmpOld = m_pnData;
	}

	this->Alloc(nWidth, nHeight);

	int w = 0, h = 0;
	if(nOldW < nWidth) w = nOldW; else w = nWidth;
	if(nOldH < nHeight) h = nOldH; else h = nHeight;

	if(h > 0 && w > 0) // ���� �� ������ ����
	{
		for(int y = 0; y < h; y++)
		{
			memcpy(&m_pnData[y*nWidth], &pTmpOld[y*nOldW], w*sizeof(short int));
		}

		GlobalUnlock(hTmpOld); // ����
		GlobalFree(hTmpOld);
		hTmpOld = NULL;
		pTmpOld = NULL;
	}
}

void CMapObjTool::ReleaseEx()
{
	CMapObj::Release();
	for(int i = 0; i < MAX_MAP_OBJ_REG; i++)
	{
		m_Objs[i].AniRelease();
		m_Objs[i].SprRelease();
	}
}
