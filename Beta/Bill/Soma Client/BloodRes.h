// BloodRes.h: interface for the CBloodRes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BLOODRES_H__CD4EDB82_B6FF_11D4_956A_00D0B77259E8__INCLUDED_)
#define AFX_BLOODRES_H__CD4EDB82_B6FF_11D4_956A_00D0B77259E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "illstruct.h"

typedef CTypedPtrArray<CPtrArray, PWORD>			ARR_WORDDATA;
typedef CTypedPtrArray<CPtrArray, _SPR_LSP*>		ARR_SPRDATA;

/*
0:���� ��ũ��, ���ϸ�, ������
1:���� ĳ���� ���� ��Ÿ�� ��Ÿ
2:�ΰ���ĳ���� ���� �׸��� ��ũ1 ��ũ2 ������ ����ź ��Ÿ�� NPC
3:ū ĳ���� ���� ������ ī��ī �ĸ�ī 
4:���� ĳ���� ��Ÿ�� û�� 
5:�ΰ��� ĳ���� û��
6:ū ĳ���� û�� �Ŵ�Ź� 
*/
class CDDSurface;
class CBloodRes  
{
public:
	int					m_RefCount;
	_SPR_HEADER			m_HSpr;						//CharRes�� ������ ����(CharRes�����Ұ�)
	ARR_WORDDATA		m_arrFxData;
	ARR_SPRDATA			m_arrSprData;

public:
	CBloodRes();
	virtual ~CBloodRes();
	void AddRef();
	int  Release();
	BOOL Draw(CDDSurface* pSurface,CPoint ptPos,int nCurFrame, BOOL bNext);
	BOOL LoadRes(int nBloodKind);
	BOOL LoadRes(CString szFileName);


};

#endif // !defined(AFX_BLOODRES_H__CD4EDB82_B6FF_11D4_956A_00D0B77259E8__INCLUDED_)
