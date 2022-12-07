// CharManager.h: interface for the CCharManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHARMANAGER_H__5A5901E1_3853_11D3_8422_00105A6B97E2__INCLUDED_)
#define AFX_CHARMANAGER_H__5A5901E1_3853_11D3_8422_00105A6B97E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDDSurface;
#include "CharRes.h"

class CHAR_RES
{
public:
	CHAR_RES();
	~CHAR_RES();

public:
	CCharRes	m_CharRes;
	int			m_RefCount;
};

typedef CMap<int, int, CHAR_RES *, CHAR_RES *> MAP_CHARRES;

//ĳ������ resource�� �����ϴ� Ŭ����
class CCharManager  
{
public:
	int					GetPixelFormat() {return m_PixelFormat;}	//16bitmode������ pixel format : 555 565 bit(in RGB)
	CCharRes*			GetIndexedCharRes(int index);				//Resource Index�� �̿��� ĳ���� resouce��������
	void				Release(int index);		//�������� ���̴� �׸� ���� ��ȣ Index (�پ��� index����)
	void				AddRef(int index);		//�������� ���̴� �׸� ���� ��ȣ Index (����Ҷ� Index����)
	void				UnloadCharRes(int index); //��ȣ Index�� Zero�� �ɶ� Resource ����
	void				SetPixelFormat(CDDSurface*	pSurface);
	void				SetPixelFormat(int pf) {m_PixelFormat = pf;}
	void				LoadAllCharRes();
	BOOL				LoadCharRes(int index);	//ĳ������ Resource Load
	void				RemoveAllData();

	CCharManager();
	virtual ~CCharManager();

protected:
	MAP_CHARRES			m_mapCharRes; 
	int					m_PixelFormat;
};

#endif // !defined(AFX_CHARMANAGER_H__5A5901E1_3853_11D3_8422_00105A6B97E2__INCLUDED_)
