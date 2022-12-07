// MapObj.h: interface for the CMapObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPOBJ_H__421F291A_2F93_4654_8E53_CA5B035E4EA0__INCLUDED_)
#define AFX_MAPOBJ_H__421F291A_2F93_4654_8E53_CA5B035E4EA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef struct SAVE_BUF
{
	int index;
	short value;
} SAVE_BUF;

class CMapObj  
{
public:
	_MAP_OBJ_HEADER m_Header;
	HGLOBAL m_hData; // �� ������ �޸� �ڵ�
	short int* m_pnData; // ���� �� ������.. ���� 4��Ʈ�� �÷���.. 0-���� 1-�浹 2-������� 4-�����. ���� 12��Ʈ�� �ε���
	SAVE_BUF *m_pTData;
	int m_vTCount;

public:
	void Alloc(int nWidth, int nHeight);
	short int DataGet(int x, int y) // ���� 8��Ʈ�� ��Ʈ ��ȣ, ���� 8��Ʈ�� ���꼼Ʈ (���ϸ��̼�) ��ȣ �̴�. ���� -1 �̸� ���ڸ��� �ϰ͵� ����.
	{
		if(x < 0 || y < 0 || x >= m_Header.nWidth || y >= m_Header.nHeight) return -1;
		else return m_pnData[y*m_Header.nWidth + x];
	}
	void DataSet(int x, int y, short int nData)
	{
		if(x < 0 || y < 0 || x >= m_Header.nWidth || y >= m_Header.nHeight) return;
		m_pnData[y*m_Header.nWidth + x] = nData;
	}
	void Load(const char* szFileName);
	void Load(HANDLE& hFile);
	void Release();

	CMapObj();
	virtual ~CMapObj();

};

#endif // !defined(AFX_MAPOBJ_H__421F291A_2F93_4654_8E53_CA5B035E4EA0__INCLUDED_)
