// ObjFaceTool.cpp: implementation of the CObjFaceTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "igt4.h"
#include "ObjFaceTool.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CObjFaceTool::CObjFaceTool()
{
	this->Alloc(MAX_FACE_PART);
}

CObjFaceTool::~CObjFaceTool()
{
}

void CObjFaceTool::Save(const char *szFileName)
{
	CFile file;
	if(file.Open(szFileName, CFile::modeWrite | CFile::modeCreate) == FALSE) return;
	
	m_Header.szID[0] = 'F'; m_Header.szID[1] = 'A'; m_Header.szID[2] = 'D'; m_Header.szID[3] = 'F';
	lstrcpy(m_Header.szRemark, "�� ǥ�� ���� ������ ����");
	
	file.Write(&m_Header, sizeof(_FACE_HEADER));

	for(int i = 0; i < m_Header.nQt; i++)
	{
		file.Write(m_pDatas[i], sizeof(_FACE_DATA));
	}

	file.Close();
}
