// MagicRes.h: interface for the CMagicRes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAGICRES_H__652BC4EE_5F86_11D3_8424_00105A6B96E7__INCLUDED_)
#define AFX_MAGICRES_H__652BC4EE_5F86_11D3_8424_00105A6B96E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "illstruct.h"
typedef CTypedPtrArray<CPtrArray, PWORD>			ARR_WORDDATA;
typedef CTypedPtrArray<CPtrArray, _SPR_LSP*>		ARR_SPRDATA;

class CDDSurface;
class CMagicRes  
{
public:
	CMagicRes();
	virtual ~CMagicRes();

	void				DrawMagic(CDDSurface *pSurface, int x, int y, int nFrame, int Alpha = 1);	//�ܼ��� �־��� ��ġ�� nFrame��°�� �׸��� �׸�
	BOOL				LoadMagic(CString &path);			//���� Resource�� �ε���
	int					GetMagicFrameNum(){return m_HSpr.nQt;}	//���� Resource�� Frame��

	static	DWORD		dwMagicDelay;				//���� Frame��ȭ�� Delay
protected:
	CString				m_szMagicResFileName;		//���� Resource���� �̸�

	_SPR_HEADER			m_HSpr;						//CharRes�� ������ ����(CharRes�����Ұ�)
	ARR_WORDDATA		m_arrFxData;
	ARR_SPRDATA			m_arrSprData;
};

#endif // !defined(AFX_MAGICRES_H__652BC4EE_5F86_11D3_8424_00105A6B96E7__INCLUDED_)
