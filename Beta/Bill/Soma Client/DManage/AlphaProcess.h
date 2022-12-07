// AlphaProcess.h: interface for the CAlphaProcess class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ALPHAPROCESS_H__B36D8028_1829_11D3_8422_00105A6B97E2__INCLUDED_)
#define AFX_ALPHAPROCESS_H__B36D8028_1829_11D3_8422_00105A6B97E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CAlphaMask;
class CDirectDraw;
class CDDSurface;

class AFX_EXT_CLASS CAlphaProcess  
{
public:
	CAlphaMask*		GetMask() {return m_pAlphaMask;}

	//Dest Surface�� DestRect�� color�� byAmount�� ������ ��ŭ �߰���Ŵ
	static	BOOL	ToTheColor(CDDSurface* pDestSurface, CRect *pDestRect, COLORREF color, BYTE byAmount);
	//Dest Surface�� DestRect�� color�� Mask�� �� ������ ���� �߰���Ŵ
	static	BOOL	AlphaBlit(CDDSurface *pDestSurface, CRect *pDestRect, COLORREF color, CAlphaMask *pMask);
	//Dest Surface�� DestRect�� SourceSurface�� Mask�� �� ������ ���� �߰���Ŵ
	static	BOOL	AlphaBlit(CDDSurface *pDestSurface, CRect *pDestRect, CDDSurface *pSrcSurface, CAlphaMask *pMask);
	//�� Surface�� ���� ����
	static	BOOL	MixEffect(CDDSurface *pDestSurface, CRect *pDestRect, CDDSurface *pSrcSurface, BYTE bFactor);
	//��� ����
	static	BOOL	LighteningSurface(CDDSurface *pSurface, CRect *pRect, CAlphaMask *pMask);
	//����ũ�� Surface�� ���� �������ؿ�
	static	CRect	GetAdjustedRect(CDDSurface *pSurface, CRect *pRect, CRect &alphaRect);

	//�߽����� �̿��� Blt (������ ��ġ�� Mask�� �߽��� ������ ��´�)
	static	BOOL	AlphaBlit(CDDSurface* pDestSurface, CPoint pos, COLORREF color, CAlphaMask *pMask);
	static	BOOL	AlphaBlit(CDDSurface* pDestSurface, CPoint pos, CDDSurface *pSrcSurface, CAlphaMask *pMask);
	static	BOOL	MixEffect(CDDSurface *pDestSurface, CPoint pos, CDDSurface *pSrcSurface, BYTE bFactor);
	static	CRect	GetAdjustedRect(CDDSurface *pSurface, CPoint pos, CRect &alphaRect);

	//�߽��������� �ƴ� (Blt�� �Ȱ��� ���)
	static	BOOL	MixEffect(CDDSurface *pDestSurface, CRect r, CDDSurface *pSrcSurface, CRect sr, BYTE bFactor);
	static	BOOL	MixHalf(CDDSurface *pDestSurface, CRect r, CDDSurface *pSrcSurface, CRect sr);

	BOOL			LoadAlphaBitmap(CString szFileName);
	
	CAlphaProcess(CDirectDraw *pDirectDraw);
	virtual ~CAlphaProcess();

protected:
	CAlphaMask		*m_pAlphaMask;
};

#define AP_MIXBLT(f, s, alpha, mask) \
	((((((f&mask)-(s&mask))*(alpha)) >> 8) + (s&mask)) & (mask))
#define AP_MIXHALF(f, s, mask) \
	((((((f&mask)-(s&mask))) >> 1) + (s&mask)) & (mask))
#endif // !defined(AFX_ALPHAPROCESS_H__B36D8028_1829_11D3_8422_00105A6B97E2__INCLUDED_)
