// AlphaProcess.cpp: implementation of the CAlphaProcess class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AlphaProcess.h"
#include "AlphaMask.h"
#include "BB_Direct.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAlphaProcess::CAlphaProcess(CDirectDraw *pDirectDraw)
{
    DDPIXELFORMAT ddpf;
    ZeroMemory(&ddpf, sizeof(ddpf));
    ddpf.dwSize = sizeof(ddpf);

	if (FAILED(pDirectDraw->GetFrontBuffer()->GetInterface()->GetPixelFormat(&ddpf)))
	{
		TRACE("Pixel ������ �������� ����\n");
	}

	m_pAlphaMask = new CAlphaMask;	//Mask��ü �켱 ����
//�׽�Ʈ Code
//	CString szFname;
//	szFname.Format("SGRES\\testmask.rbm");
//	LoadAlphaBitmap(szFname);
}

CAlphaProcess::~CAlphaProcess()
{
	if (m_pAlphaMask) delete m_pAlphaMask, m_pAlphaMask = NULL;
}

BOOL CAlphaProcess::LoadAlphaBitmap(CString szFileName)
{
	return m_pAlphaMask->LoadMask(szFileName);	//������ ������ Mask�� Load��
}
//���������� ������ �������
CRect CAlphaProcess::GetAdjustedRect(CDDSurface *pSurface, CRect *pRect, CRect &alphaRect)
{
	CRect r;
	pSurface->GetRect(r);
	if (pRect) 
	{
		r &= *pRect;
		if (pRect->left<0) alphaRect.left = -pRect->left;
		if (pRect->top<0) alphaRect.top = -pRect->top;
	}
	CPoint alphaOffset = alphaRect.TopLeft();
	CPoint destOffset = r.TopLeft();
	alphaRect.OffsetRect(-alphaOffset.x, -alphaOffset.y);
	r.OffsetRect(-destOffset.x, -destOffset.y);
	r &= alphaRect;
	alphaRect.OffsetRect(alphaOffset);
	r.OffsetRect(destOffset);
	return r;
}

/////////////////////////
//byAmount: 64 (Standard), 64���� ������ ��Ӱ� 128�̸� �ι� ��� ��(������ ���� ������)
/////////////////////////
//Shift���꿡�� 6bit�� ����ϹǷ� 64�� standard�� ��
BOOL CAlphaProcess::LighteningSurface(CDDSurface *pSurface, CRect *pRect, CAlphaMask *pMask)
{
	CRect alphaRect(0, 0, pMask->m_dwWidth, pMask->m_dwHeight);
	CRect r = GetAdjustedRect(pSurface, pRect, alphaRect);

	ASSERT(pMask&&pMask->m_pvBits);

	if (r.IsRectEmpty()) return TRUE;
	if (!pSurface->Lock(NULL, DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT)) return FALSE;
	DDSURFACEDESC2& ddsd = pSurface->GetDescription();

	DWORD dwRMask, dwGMask, dwBMask;
	DWORD dwRTmp, dwGTmp, dwBTmp;
	pSurface->GetRGBMasks(dwRMask, dwGMask, dwBMask);

	int		width = r.Width();
	int		height = r.Height();
	DWORD	semiBlack = pSurface->GetSemiBlack();
	int		destModulo = ddsd.lPitch - (width<< 1);
	WORD	*pwDestBits = (WORD*)((BYTE*)ddsd.lpSurface+r.left*2+r.top*ddsd.lPitch);
	WORD	*pwSrc;
	
	int		x;
	DWORD	dwSrc;
	DWORD	dwResult;
	//AlphaMask�� ���� �׸������� ��ġ������ ��.
	BYTE	*pAmount = (BYTE*)pMask->m_pvBits;
	BYTE	*pbyAmount = pAmount+alphaRect.left+alphaRect.top*pMask->m_dwPitch;
	DWORD	dwAmount;
	do
	{
		x = width;
		pwSrc = pwDestBits;
		do
		{
			dwSrc = *pwSrc++;
			if (!dwSrc)
			{
				pwDestBits++;
				pbyAmount++;
				continue;
			}
			dwAmount = *pbyAmount++;
			if (dwAmount<=64)
			{
				pwDestBits++;
				continue;
			}
			dwRTmp = ((dwSrc & dwRMask) * dwAmount) >> 6;
			dwGTmp = ((dwSrc & dwGMask) * dwAmount) >> 6;
			dwBTmp = ((dwSrc & dwBMask) * dwAmount) >> 6;
			if (dwRTmp>dwRMask) dwRTmp = dwRMask;
			if (dwGTmp>dwGMask) dwGTmp = dwGMask;
			if (dwBTmp>dwBMask) dwBTmp = dwBMask;
			dwRTmp &= dwRMask;
			dwGTmp &= dwGMask;
			dwBTmp &= dwBMask;
			dwResult = dwRTmp|dwGTmp|dwBTmp;
			if (dwResult==0L) dwResult = semiBlack;
			*pwDestBits++ = (WORD)dwResult;
		}while (--x);
		pwDestBits = (WORD*)((BYTE*)pwDestBits+destModulo);
		pbyAmount += pMask->m_dwPitch-width;
	}while (--height);

	pSurface->Unlock(NULL);
	return TRUE;
}

//ĳ���͸� ��濡 Mix�ϴ� ȿ���� ������
BOOL CAlphaProcess::MixEffect(CDDSurface *pDestSurface, CRect *pDestRect, CDDSurface *pSrcSurface, BYTE bFactor)
{
	CRect alphaRect;
	pSrcSurface->GetRect(alphaRect);
	CRect r = GetAdjustedRect(pDestSurface, pDestRect, alphaRect);

	if (!pDestSurface->Lock(NULL, DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT)) return FALSE;
	if (!pSrcSurface->Lock(NULL, DDLOCK_READONLY|DDLOCK_WAIT))
	{
		pDestSurface->Unlock(NULL);
		return FALSE;
	}

	DWORD dwRMask, dwGMask, dwBMask;
	pDestSurface->GetRGBMasks(dwRMask, dwGMask, dwBMask);

	int	iWidth = r.Width();
	int	iHeight = r.Height();
	WORD *pTmpSrcBuf;

	DDSURFACEDESC2& ddsdDest = pDestSurface->GetDescription();
	DDSURFACEDESC2& ddsdSrc = pSrcSurface->GetDescription();

	WORD	*pwDestBits = (WORD*)((BYTE*)ddsdDest.lpSurface+r.left*2+r.top*ddsdDest.lPitch);
	WORD	*pwSrcBits = (WORD*)((BYTE*)ddsdSrc.lpSurface+alphaRect.left*2+alphaRect.top*ddsdSrc.lPitch);
	WORD	wDestModulo = ddsdDest.lPitch - (iWidth<<1);
	WORD	wSrcModulo = ddsdSrc.lPitch - (iWidth<<1);
	int		iRead;
	int		iTRead;
	int		x;

	do
	{
		x = iWidth;
		pTmpSrcBuf = pwDestBits;
		do
		{
			iRead = *pwSrcBits++;
			iTRead = *pTmpSrcBuf++;
			if (!iRead)
			{
				pwDestBits++;
				continue;
			}

			*pwDestBits++ = (WORD) (AP_MIXBLT(iRead, iTRead, bFactor, dwRMask) |
									AP_MIXBLT(iRead, iTRead, bFactor, dwGMask) |
									AP_MIXBLT(iRead, iTRead, bFactor, dwBMask));
		}while (--x);
		pwDestBits = (WORD*)((BYTE*)pwDestBits+wDestModulo);
		pwSrcBits = (WORD*)((BYTE*)pwSrcBits+wSrcModulo);
	}while (--iHeight);


	pSrcSurface->Unlock(NULL);
	pDestSurface->Unlock(NULL);
	return TRUE;
}

BOOL CAlphaProcess::AlphaBlit(CDDSurface *pDestSurface, CRect *pDestRect, CDDSurface *pSrcSurface, CAlphaMask *pMask)
{
	CRect alphaRect;
	pSrcSurface->GetRect(alphaRect);

	ASSERT(pMask&&pMask->m_pvBits);
	ASSERT(alphaRect.Width()==(int)pMask->m_dwWidth);
	ASSERT(alphaRect.Height()==(int)pMask->m_dwHeight);

	CRect r = GetAdjustedRect(pDestSurface, pDestRect, alphaRect);

	if (!pDestSurface->Lock(NULL, DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT)) return FALSE;
	if (!pSrcSurface->Lock(NULL, DDLOCK_READONLY|DDLOCK_WAIT))
	{
		pDestSurface->Unlock(NULL);
		return FALSE;
	}

	DWORD dwRMask, dwGMask, dwBMask;
	pDestSurface->GetRGBMasks(dwRMask, dwGMask, dwBMask);

	int	iWidth = r.Width();
	int	iHeight = r.Height();
	WORD *pTmpSrcBuf;

	DDSURFACEDESC2& ddsdDest = pDestSurface->GetDescription();
	DDSURFACEDESC2& ddsdSrc = pSrcSurface->GetDescription();

	WORD	*pwDestBits = (WORD*)((BYTE*)ddsdDest.lpSurface+r.left*2+r.top*ddsdDest.lPitch);
	WORD	*pwSrcBits = (WORD*)((BYTE*)ddsdSrc.lpSurface+alphaRect.left*2+alphaRect.top*ddsdSrc.lPitch);
	WORD	wDestModulo = ddsdDest.lPitch - (iWidth<<1);
	WORD	wSrcModulo = ddsdSrc.lPitch - (iWidth<<1);
	int		iRead;
	int		iTRead;
	int		x;

	//AlphaMask�� ���� �׸������� ��ġ������ ��.
	BYTE	*pAmount = (BYTE*)pMask->m_pvBits;
	BYTE	*pbyAmount = pAmount+alphaRect.left+alphaRect.top*pMask->m_dwPitch;
	BYTE	byAmount;

	do
	{
		x = iWidth;
		pTmpSrcBuf = pwDestBits;
		do
		{
			iRead = *pwSrcBits++;
			iTRead = *pTmpSrcBuf++;
			if (!iRead)
			{
				pwDestBits++;
				pbyAmount++;
				continue;
			}
			byAmount = *pbyAmount++;

			*pwDestBits++ = (WORD) (AP_MIXBLT(iRead, iTRead, byAmount, dwRMask) |
									AP_MIXBLT(iRead, iTRead, byAmount, dwGMask) |
									AP_MIXBLT(iRead, iTRead, byAmount, dwBMask));
		}while (--x);
		pwDestBits = (WORD*)((BYTE*)pwDestBits+wDestModulo);
		pwSrcBits = (WORD*)((BYTE*)pwSrcBits+wSrcModulo);
		pbyAmount += pMask->m_dwPitch-iWidth;
	}while (--iHeight);


	pSrcSurface->Unlock(NULL);
	pDestSurface->Unlock(NULL);
	return TRUE;
}

//Alpha Mask ���� ���� ���� �����ؼ� blt
BOOL CAlphaProcess::AlphaBlit(CDDSurface *pDestSurface, CRect *pDestRect, COLORREF color, CAlphaMask *pMask)
{
	CRect alphaRect;
	pDestSurface->GetRect(alphaRect);

	CRect r = GetAdjustedRect(pDestSurface, pDestRect, alphaRect);

	int		iRead = (int)pDestSurface->GetMatchColor(color);
	if (!iRead) return TRUE;//Black�̵ǹǷ� �����̹��� ����

	if (!pDestSurface->Lock(NULL, DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT)) return FALSE;

	DWORD dwRMask, dwGMask, dwBMask;
	pDestSurface->GetRGBMasks(dwRMask, dwGMask, dwBMask);

	int	iWidth = r.Width();
	int	iHeight = r.Height();
	WORD *pTmpSrcBuf;

	DDSURFACEDESC2& ddsdDest = pDestSurface->GetDescription();

	WORD	*pwDestBits = (WORD*)((BYTE*)ddsdDest.lpSurface+r.left*2+r.top*ddsdDest.lPitch);
	WORD	wDestModulo = ddsdDest.lPitch - (iWidth<<1);
	int		iTRead;
	int		x;

	//AlphaMask�� ���� �׸������� ��ġ������ ��.
	BYTE	*pAmount = (BYTE*)pMask->m_pvBits;
	BYTE	*pbyAmount = pAmount+alphaRect.left+alphaRect.top*pMask->m_dwPitch;
	BYTE	byAmount;

	do
	{
		x = iWidth;
		pTmpSrcBuf = pwDestBits;
		do
		{
			iTRead = *pTmpSrcBuf++;
			byAmount = *pbyAmount++;

			*pwDestBits++ = (WORD) (AP_MIXBLT(iRead, iTRead, byAmount, dwRMask) |
									AP_MIXBLT(iRead, iTRead, byAmount, dwGMask) |
									AP_MIXBLT(iRead, iTRead, byAmount, dwBMask));
		}while (--x);
		pwDestBits = (WORD*)((BYTE*)pwDestBits+wDestModulo);
		pbyAmount += pMask->m_dwPitch-iWidth;
	}while (--iHeight);


	pDestSurface->Unlock(NULL);
	return TRUE;
}
//byamount�� 256�̸� DestSurface�� ������ ���� color�� �ٲ� 0�̸� DestSurface����
BOOL CAlphaProcess::ToTheColor(CDDSurface* pDestSurface, CRect *pDestRect, COLORREF color, BYTE byAmount)
{
	CRect alphaRect;
	pDestSurface->GetRect(alphaRect);
	CRect r = GetAdjustedRect(pDestSurface, pDestRect, alphaRect);
	int	iToColor = (int)pDestSurface->GetMatchColor(color);

	if (byAmount==0) return TRUE;//�����׸� ����

	if (!pDestSurface->Lock(NULL, DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT)) return FALSE;

	DWORD dwRMask, dwGMask, dwBMask;
	pDestSurface->GetRGBMasks(dwRMask, dwGMask, dwBMask);

	int	iWidth = r.Width();
	int	iHeight = r.Height();

	DDSURFACEDESC2& ddsdDest = pDestSurface->GetDescription();
	WORD	*pwDestBits = (WORD*)((BYTE*)ddsdDest.lpSurface+r.left*2+r.top*ddsdDest.lPitch);
	WORD	wDestModulo = ddsdDest.lPitch - (iWidth<<1);

	WORD *pTmpSrcBuf;

	int		iRead;

	int x;
	do
	{
		x = iWidth;
		pTmpSrcBuf = pwDestBits;
		do
		{
			iRead = *pTmpSrcBuf++;

			*pwDestBits++ = (WORD) (AP_MIXBLT(iToColor, iRead, byAmount, dwRMask) |
									AP_MIXBLT(iToColor, iRead, byAmount, dwGMask) |
									AP_MIXBLT(iToColor, iRead, byAmount, dwBMask));

		}while (--x);
		pwDestBits = (WORD*)((BYTE*)pwDestBits+wDestModulo);
	}while (--iHeight);

	pDestSurface->Unlock(NULL);
	return TRUE;
}








/////////////////////////////
//�߽����� �������� �� blt��		(����ũ�� ���ɿ����� ��� ����� ���ؼ�)
/////////////////////////////
BOOL CAlphaProcess::AlphaBlit(CDDSurface* pDestSurface, CPoint pos, CDDSurface *pSrcSurface, CAlphaMask *pMask)
{
	CRect alphaRect;
	pSrcSurface->GetRect(alphaRect);

	ASSERT(pMask&&pMask->m_pvBits);
	ASSERT(alphaRect.Width()==(int)pMask->m_dwWidth);
	ASSERT(alphaRect.Height()==(int)pMask->m_dwHeight);

	CRect r = GetAdjustedRect(pDestSurface, pos, alphaRect);

	if (!pDestSurface->Lock(NULL, DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT)) return FALSE;
	if (!pSrcSurface->Lock(NULL, DDLOCK_READONLY|DDLOCK_WAIT))
	{
		pDestSurface->Unlock(NULL);
		return FALSE;
	}

	DWORD dwRMask, dwGMask, dwBMask;
	pDestSurface->GetRGBMasks(dwRMask, dwGMask, dwBMask);

	int	iWidth = r.Width();
	int	iHeight = r.Height();
	WORD *pTmpSrcBuf;

	DDSURFACEDESC2& ddsdDest = pDestSurface->GetDescription();
	DDSURFACEDESC2& ddsdSrc = pSrcSurface->GetDescription();

	WORD	*pwDestBits = (WORD*)((BYTE*)ddsdDest.lpSurface+r.left*2+r.top*ddsdDest.lPitch);
	WORD	*pwSrcBits = (WORD*)((BYTE*)ddsdSrc.lpSurface+alphaRect.left*2+alphaRect.top*ddsdSrc.lPitch);
	WORD	wDestModulo = ddsdDest.lPitch - (iWidth<<1);
	WORD	wSrcModulo = ddsdSrc.lPitch - (iWidth<<1);
	int		iRead;
	int		iTRead;
	int		x;

	//AlphaMask�� ���� �׸������� ��ġ������ ��.
	BYTE	*pAmount = (BYTE*)pMask->m_pvBits;
	BYTE	*pbyAmount = pAmount+alphaRect.left+alphaRect.top*pMask->m_dwPitch;
	BYTE	byAmount;

	do
	{
		x = iWidth;
		pTmpSrcBuf = pwDestBits;
		do
		{
			iRead = *pwSrcBits++;
			iTRead = *pTmpSrcBuf++;
			if (!iRead)
			{
				pwDestBits++;
				pbyAmount++;
				continue;
			}
			byAmount = *pbyAmount++;

			*pwDestBits++ = (WORD) (AP_MIXBLT(iRead, iTRead, byAmount, dwRMask) |
									AP_MIXBLT(iRead, iTRead, byAmount, dwGMask) |
									AP_MIXBLT(iRead, iTRead, byAmount, dwBMask));
		}while (--x);
		pwDestBits = (WORD*)((BYTE*)pwDestBits+wDestModulo);
		pwSrcBits = (WORD*)((BYTE*)pwSrcBits+wSrcModulo);
		pbyAmount += pMask->m_dwPitch-iWidth;
	}while (--iHeight);


	pSrcSurface->Unlock(NULL);
	pDestSurface->Unlock(NULL);
	return TRUE;
}

BOOL CAlphaProcess::AlphaBlit(CDDSurface* pDestSurface, CPoint pos, COLORREF color, CAlphaMask *pMask)
{
	CRect alphaRect(0, 0, 0, 0);
	alphaRect.right = (int)pMask->m_dwWidth;
	alphaRect.bottom = (int)pMask->m_dwHeight;

	CRect r = GetAdjustedRect(pDestSurface, pos, alphaRect);

	int		iRead = (int)pDestSurface->GetMatchColor(color);
	if (!iRead) return TRUE;//Black�̵ǹǷ� �����̹��� ����

	if (!pDestSurface->Lock(NULL, DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT)) return FALSE;

	DWORD dwRMask, dwGMask, dwBMask;
	pDestSurface->GetRGBMasks(dwRMask, dwGMask, dwBMask);

	int	iWidth = r.Width();
	int	iHeight = r.Height();
	WORD *pTmpSrcBuf;

	DDSURFACEDESC2& ddsdDest = pDestSurface->GetDescription();

	WORD	*pwDestBits = (WORD*)((BYTE*)ddsdDest.lpSurface+r.left*2+r.top*ddsdDest.lPitch);
	WORD	wDestModulo = ddsdDest.lPitch - (iWidth<<1);
	int		iTRead;
	int		x;

	//AlphaMask�� ���� �׸������� ��ġ������ ��.
	BYTE	*pAmount = (BYTE*)pMask->m_pvBits;
	BYTE	*pbyAmount = pAmount+alphaRect.left+alphaRect.top*pMask->m_dwPitch;
	BYTE	byAmount;

	do
	{
		x = iWidth;
		pTmpSrcBuf = pwDestBits;
		do
		{
			iTRead = *pTmpSrcBuf++;
			byAmount = *pbyAmount++;

			*pwDestBits++ = (WORD) (AP_MIXBLT(iRead, iTRead, byAmount, dwRMask) |
									AP_MIXBLT(iRead, iTRead, byAmount, dwGMask) |
									AP_MIXBLT(iRead, iTRead, byAmount, dwBMask));
		}while (--x);
		pwDestBits = (WORD*)((BYTE*)pwDestBits+wDestModulo);
		pbyAmount += pMask->m_dwPitch-iWidth;
	}while (--iHeight);


	pDestSurface->Unlock(NULL);
	return TRUE;
}

BOOL CAlphaProcess::MixEffect(CDDSurface *pDestSurface, CPoint pos, CDDSurface *pSrcSurface, BYTE bFactor)
{
	CRect alphaRect;
	pSrcSurface->GetRect(alphaRect);
	CRect r = GetAdjustedRect(pDestSurface, pos, alphaRect);

	if (!pDestSurface->Lock(NULL, DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT)) return FALSE;
	if (!pSrcSurface->Lock(NULL, DDLOCK_READONLY|DDLOCK_WAIT))
	{
		pDestSurface->Unlock(NULL);
		return FALSE;
	}

	DWORD dwRMask, dwGMask, dwBMask;
	pDestSurface->GetRGBMasks(dwRMask, dwGMask, dwBMask);

	int	iWidth = r.Width();
	int	iHeight = r.Height();
	WORD *pTmpSrcBuf;

	DDSURFACEDESC2& ddsdDest = pDestSurface->GetDescription();
	DDSURFACEDESC2& ddsdSrc = pSrcSurface->GetDescription();

	WORD	*pwDestBits = (WORD*)((BYTE*)ddsdDest.lpSurface+r.left*2+r.top*ddsdDest.lPitch);
	WORD	*pwSrcBits = (WORD*)((BYTE*)ddsdSrc.lpSurface+alphaRect.left*2+alphaRect.top*ddsdSrc.lPitch);
	WORD	wDestModulo = ddsdDest.lPitch - (iWidth<<1);
	WORD	wSrcModulo = ddsdSrc.lPitch - (iWidth<<1);
	int		iRead;
	int		iTRead;
	int		x;

	do
	{
		x = iWidth;
		pTmpSrcBuf = pwDestBits;
		do
		{
			iRead = *pwSrcBits++;
			iTRead = *pTmpSrcBuf++;
			if (!iRead)
			{
				pwDestBits++;
				continue;
			}

			*pwDestBits++ = (WORD) (AP_MIXBLT(iRead, iTRead, bFactor, dwRMask) |
									AP_MIXBLT(iRead, iTRead, bFactor, dwGMask) |
									AP_MIXBLT(iRead, iTRead, bFactor, dwBMask));
		}while (--x);
		pwDestBits = (WORD*)((BYTE*)pwDestBits+wDestModulo);
		pwSrcBits = (WORD*)((BYTE*)pwSrcBits+wSrcModulo);
	}while (--iHeight);


	pSrcSurface->Unlock(NULL);
	pDestSurface->Unlock(NULL);
	return TRUE;
}

BOOL CAlphaProcess::MixEffect(CDDSurface *pDestSurface, CRect r, CDDSurface *pSrcSurface, CRect sr, BYTE bFactor)
{
	if (!pDestSurface->Lock(NULL, DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT)) return FALSE;
	if (!pSrcSurface->Lock(NULL, DDLOCK_READONLY|DDLOCK_WAIT))
	{
		pDestSurface->Unlock(NULL);
		return FALSE;
	}

	DWORD dwRMask, dwGMask, dwBMask;
	pDestSurface->GetRGBMasks(dwRMask, dwGMask, dwBMask);

	int	iWidth = r.Width();
	int	iHeight = r.Height();
	WORD *pTmpSrcBuf;

	DDSURFACEDESC2& ddsdDest = pDestSurface->GetDescription();
	DDSURFACEDESC2& ddsdSrc = pSrcSurface->GetDescription();

	WORD	*pwDestBits = (WORD*)((BYTE*)ddsdDest.lpSurface+r.left*2+r.top*ddsdDest.lPitch);
	WORD	*pwSrcBits = (WORD*)((BYTE*)ddsdSrc.lpSurface+sr.left*2+sr.top*ddsdSrc.lPitch);
	WORD	wDestModulo = ddsdDest.lPitch - (iWidth<<1);
	WORD	wSrcModulo = ddsdSrc.lPitch - (iWidth<<1);
	int		iRead;
	int		iTRead;
	int		x;

	do
	{
		x = iWidth;
		pTmpSrcBuf = pwDestBits;
		do
		{
			iRead = *pwSrcBits++;
			iTRead = *pTmpSrcBuf++;
			if (!iRead)
			{
				pwDestBits++;
				continue;
			}

			*pwDestBits++ = (WORD) (AP_MIXBLT(iRead, iTRead, bFactor, dwRMask) |
									AP_MIXBLT(iRead, iTRead, bFactor, dwGMask) |
									AP_MIXBLT(iRead, iTRead, bFactor, dwBMask));
		}while (--x);
		pwDestBits = (WORD*)((BYTE*)pwDestBits+wDestModulo);
		pwSrcBits = (WORD*)((BYTE*)pwSrcBits+wSrcModulo);
	}while (--iHeight);


	pSrcSurface->Unlock(NULL);
	pDestSurface->Unlock(NULL);
	return TRUE;
}

BOOL CAlphaProcess::MixHalf(CDDSurface *pDestSurface, CRect r, CDDSurface *pSrcSurface, CRect sr)
{
	if (!pDestSurface->Lock(NULL, DDLOCK_SURFACEMEMORYPTR|DDLOCK_WAIT)) return FALSE;
	if (!pSrcSurface->Lock(NULL, DDLOCK_READONLY|DDLOCK_WAIT))
	{
		pDestSurface->Unlock(NULL);
		return FALSE;
	}

	DWORD dwRMask, dwGMask, dwBMask;
	pDestSurface->GetRGBMasks(dwRMask, dwGMask, dwBMask);
//	TRACE("%ld %ld %ld\n", dwRMask, dwGMask, dwBMask);

	int	iWidth = r.Width();
	int	iHeight = r.Height();

	DDSURFACEDESC2& ddsdDest = pDestSurface->GetDescription();
	DDSURFACEDESC2& ddsdSrc = pSrcSurface->GetDescription();

	PWORD	pwDestBits = (PWORD)((PBYTE)ddsdDest.lpSurface+r.left*2+r.top*ddsdDest.lPitch);
	PWORD	pwSrcBuf = pwDestBits;
	PWORD	pwSrcBits = (PWORD)((PBYTE)ddsdSrc.lpSurface+sr.left*2+sr.top*ddsdSrc.lPitch);
	WORD	wDestModulo = ddsdDest.lPitch - (iWidth<<1);
	WORD	wSrcModulo = ddsdSrc.lPitch - (iWidth<<1);
	int		iRead;
	int		iTRead;
	int		x;
	
	WORD wTrans = (WORD)ddsdSrc.ddckCKSrcBlt.dwColorSpaceLowValue;

	do
	{
		x = iWidth;
		do
		{
			iRead = *pwSrcBits++;
			iTRead = *pwSrcBuf++;
//			if (!iRead)
			if (iRead == wTrans)
			{
				pwDestBits++;
				continue;
			}

			*pwDestBits++ = (WORD) (AP_MIXHALF(iRead, iTRead, dwRMask) |
									AP_MIXHALF(iRead, iTRead, dwGMask) |
									AP_MIXHALF(iRead, iTRead, dwBMask));
		}while (--x);
		pwSrcBuf = pwDestBits = (WORD*)((BYTE*)pwDestBits+wDestModulo);
		pwSrcBits = (WORD*)((BYTE*)pwSrcBits+wSrcModulo);
	}while (--iHeight);


	pSrcSurface->Unlock(NULL);
	pDestSurface->Unlock(NULL);
	return TRUE;
}

//�߽����� �������� �� �������� ���ϱ�
CRect CAlphaProcess::GetAdjustedRect(CDDSurface *pSurface, CPoint pos, CRect &alphaRect)
{
	CRect r;
	pSurface->GetRect(r);
	int alphaWidth = alphaRect.Width();
	int alphaHeight = alphaRect.Height();

	CRect maskRect(pos.x-alphaWidth/2, pos.y-alphaHeight/2, 0, 0);
	maskRect.right = maskRect.left+alphaWidth;
	maskRect.bottom = maskRect.top+alphaHeight;

	r&=maskRect;
	if (maskRect.left<0) alphaRect.left = -maskRect.left;
	if (maskRect.top<0) alphaRect.top = -maskRect.top;

	CPoint alphaOffset = alphaRect.TopLeft();
	CPoint destOffset = r.TopLeft();
	alphaRect.OffsetRect(-alphaOffset.x, -alphaOffset.y);
	r.OffsetRect(-destOffset.x, -destOffset.y);
	r &= alphaRect;
	alphaRect.OffsetRect(alphaOffset);
	r.OffsetRect(destOffset);
	return r;
}
