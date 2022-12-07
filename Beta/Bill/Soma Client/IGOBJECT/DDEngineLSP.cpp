// DDEngineLSP.cpp: implementation of the CDDEngineLSP class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DDEngineLSP.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDDEngineLSP::CDDEngineLSP()
{

}

CDDEngineLSP::~CDDEngineLSP()
{

}

void CDDEngineLSP::BltLSP(LPDIRECTDRAWSURFACE7 lpDDSDest, int x, int y, const _SPR_LSP* pSprLSP, int nRenderType, int nAlpha, COLORREF crColor)
{
	if(pSprLSP == NULL) return;
	if(pSprLSP->pwV == NULL) return; // LSP �����Ͱ� ������ ���ư���..
	if(pSprLSP->rcV.right - pSprLSP->rcV.left <= 0 || pSprLSP->rcV.bottom - pSprLSP->rcV.top <= 0) return; // ��ȿ�� �ȼ��� ������ ���ư���..
	
	int nPitchDest = 0;
	WORD* pwDest = NULL;
	BOOL bNeedUnlockDDS = TRUE; // ���̸� ���ǽ� ����� �ʿ��ϴ�.
	if(lpDDSDest == NULL)
	{
		lpDDSDest = m_lpDDSBB;
		pwDest = m_pwBB;
		nPitchDest = m_nPitchBB;
		bNeedUnlockDDS = FALSE;
	}
	else
	{
		this->SurfaceLock(lpDDSDest, &m_ddsdTmp1);
		pwDest = (WORD*)m_ddsdTmp1.lpSurface;
		nPitchDest = m_ddsdTmp1.lPitch/2;
		bNeedUnlockDDS = TRUE;
	}

	if(pwDest == NULL) return;

	RECT rc = {x+pSprLSP->rcV.left, y+pSprLSP->rcV.top, x+pSprLSP->rcV.right, y+pSprLSP->rcV.bottom};
	if(rc.right < 0 || rc.bottom < 0 || rc.left >= m_rcScr.right || rc.top >= m_rcScr.bottom) return; // ȭ���� ������ ���..
	if(nAlpha < 0) nAlpha = 0;
	if(nAlpha > 32) nAlpha = 32;

	RECT rcClip; // Ŭ���� ������ ���ϰ� �ɼµ� ���Ѵ�.
	BOOL bUseXClip = GetClippedRect(&rc, &rcClip); // ���� ����, Ŭ���� ó���� ����

	int nNode; // �Ѷ��δ� ����..
	int nZeroCount = 0; // �ǳʶٴ� �ȼ��� ����
	int nCopyCount = 0; // ������ �ȼ��� ����

	const WORD* pSrc = pSprLSP->pwV;
	// �߸��� ���� �ټ� ��ŭ ������ ������ �̵�..
	if(rc.top < 0)
	{
		int skipY = -rc.top;
		for(int i = 0; i < skipY; i++) // ��ŵ �ټ�..
		{
			nNode = *pSrc; pSrc++; // ����;
			for(;nNode; nNode--)
			{
				pSrc++; // 0 �� ����
				pSrc += *pSrc + 1; // ��ȿ �ȼ� ����
			}
		}
	}

	WORD* pDestOrg = pwDest + nPitchDest*rcClip.top + rcClip.left; // ������ �ּ� ���..
	int width = rcClip.right - rcClip.left;
	int height = rcClip.bottom - rcClip.top;

	int nAlphaSrc = nAlpha; // 32 �� ���� ���� ���̴�.
	int nAlphaDest = 32 - nAlpha;
	WORD wColor = RGB16(crColor);
	DWORD dwColor = ((((wColor & m_dwRBMask)*nAlphaSrc)>>5)&m_dwRBMask) + ((((wColor & m_dwGMask)*nAlphaSrc)>>5)&m_dwGMask);

	int nD = 0, nDR1 = 0, nDG1 = 0, nDB1 = 0, nDR2 = 0, nDG2 = 0, nDB2 = 0;
	if(nRenderType == RENDER_COLOR_LEVEL) // �÷� ���� ����
	{
		nDR1 = crColor & 0x000000ff;
		nDG1 = (crColor & 0x0000ff00) >> 8;
		nDB1 = (crColor & 0x00ff0000) >> 16;
	}

	if(bUseXClip == FALSE) // X �� Ŭ������ �ʿ���ٸ�..
	{
		int nPixelCount = 0; // �ǳʶٴ� ��ȿ �ȼ��� ����
		for(y = 0; y < height; y++)
		{
			WORD* pDest = pDestOrg + nPitchDest*y; nNode = *pSrc; pSrc++;
			for(;nNode;nNode--, pDest+=nCopyCount, pSrc+=nCopyCount) // �ȼ��� ��ŭ ������ �̵�..
			{
				pDest += *pSrc; pSrc++; nCopyCount = *pSrc; pSrc++; // 0 �κ� skip... // ��ȿ �ȼ�, ������ �ȼ� ���� ���
				if(nRenderType == RENDER_NORMAL)			PutPixelNormal(pDest, pSrc, nCopyCount);
				else if(nRenderType == RENDER_SHADOW)		PutPixelShadow(pDest, pSrc, nCopyCount, m_dwRBMask, m_dwGMask);
				else if(nRenderType == RENDER_TRANS)		PutPixelTrans(pDest, pSrc, nCopyCount, nAlphaDest, nAlphaSrc, m_dwRBMask, m_dwGMask);
				else if(nRenderType == RENDER_ALPHA_ADD)	PutPixelAlphaAdd(pDest, pSrc, nCopyCount, m_dwRMask, m_dwGMask, m_dwBMask);
				else if(nRenderType == RENDER_ALPHA_SOFT)	PutPixelAlphaSoft(pDest, pSrc, nCopyCount, m_dwRMask, m_dwGMask, m_dwBMask);
				else if(nRenderType == RENDER_DARK)			PutPixelDark(pDest, pSrc, nCopyCount, nAlphaDest, m_dwRBMask, m_dwGMask);
				else if(nRenderType == RENDER_COLOR)		PutPixelColor(pDest, pSrc, nCopyCount, nAlphaDest, dwColor, m_dwRBMask, m_dwGMask);
				else if(nRenderType == RENDER_COLOR_LEVEL)
				{
					for(x = 0; x < nCopyCount; x++)
					{
						nD = *(pSrc+x) & m_dwBMask;
//						if(nD < 20)
//						{
							nDR2 = (nD * nDR1) >> 8;
							nDG2 = (nD * nDG1) >> 8;
							nDB2 = (nD * nDB1) >> 8;
							*(pDest+x) = m_wRTbls[nDR2] | m_wGTbls[nDG2] | m_wBTbls[nDB2];
//						}
//						else
//						{
//							nDR2 = (nD * nDR1) >> 8; nDR2 += (31 - nDR2)*11/31;
//							nDG2 = (nD * nDG1) >> 8; nDG2 += (31 - nDG2)*11/31;
//							nDB2 = (nD * nDB1) >> 8; nDB2 += (31 - nDB2)*11/31;
//							*(pDest+x) = m_wRTbls[nDR2] | m_wGTbls[nDG2] | m_wBTbls[nDB2];
//						}
					}
				}
			}
		}
	}
	else // X �� Ŭ������ �Ͼ�ٸ�..
	{
		// 0 �ȼ��� ����, ��ȿ �ȼ� ���� // ������ ���� ����, �ȼ�����, �� ��ġ �ε���..
		int nAddCount = 0, ndxZ = 0, ndxS = 0, ndxE = 0;
		int clipXL = -rc.left, clipXR = rc.right - m_rcScr.right;
		for(y = 0; y < height; y++)
		{
			WORD* pDest = pDestOrg+nPitchDest*y;
			nNode = *pSrc; pSrc++; ndxE = 0; // ������ ���� �ε���
			for(;nNode;nNode--, pDest+=nCopyCount, pSrc += nCopyCount + nAddCount)
			{
				nZeroCount = *pSrc; pSrc++; nCopyCount = *pSrc; pSrc++;// 0 �κ� skip... // ��ȿ �ȼ� ���� ���
				ndxZ = ndxE; ndxS = ndxE + nZeroCount; ndxE = ndxS + nCopyCount;
				if(clipXL > 0) // ���� Ŭ����
				{
					if(ndxE <= clipXL) { pSrc += nCopyCount; nCopyCount = 0; continue; }
					if(ndxZ >= clipXL) { pDest += nZeroCount; }
					else if(ndxZ < clipXL)
					{
						if(ndxS < clipXL) { nCopyCount -= clipXL - ndxS; pSrc += clipXL - ndxS; } else { pDest += ndxS - clipXL; }
					}
				}
				if(clipXR > 0) // ������ Ŭ����
				{
					nAddCount = 0; if(ndxZ >= width || ndxS >= width) continue;
					pDest += nZeroCount; if(ndxE > width) { nCopyCount -= ndxE - width; nAddCount = ndxE - width; }
				}
				if(nRenderType == RENDER_NORMAL)			PutPixelNormal(pDest, pSrc, nCopyCount);
				else if(nRenderType == RENDER_TRANS)		PutPixelTrans(pDest, pSrc, nCopyCount, nAlphaDest, nAlphaSrc, m_dwRBMask, m_dwGMask);
				else if(nRenderType == RENDER_ALPHA_ADD)	PutPixelAlphaAdd(pDest, pSrc, nCopyCount, m_dwRMask, m_dwGMask, m_dwBMask);
				else if(nRenderType == RENDER_ALPHA_SOFT)	PutPixelAlphaSoft(pDest, pSrc, nCopyCount, m_dwRMask, m_dwGMask, m_dwBMask);
				else if(nRenderType == RENDER_SHADOW)		PutPixelShadow(pDest, pSrc, nCopyCount, m_dwRBMask, m_dwGMask);
				else if(nRenderType == RENDER_DARK)			PutPixelDark(pDest, pSrc, nCopyCount, nAlphaDest, m_dwRBMask, m_dwGMask);
				else if(nRenderType == RENDER_COLOR)		PutPixelColor(pDest, pSrc, nCopyCount, nAlphaDest, dwColor, m_dwRBMask, m_dwGMask);
			}
		}
	}

	if(bNeedUnlockDDS) SurfaceUnlock(lpDDSDest);
}

BOOL CDDEngineLSP::GetClippedRect(RECT *pRC, RECT* pRCClip)
{
	*pRCClip = *pRC;
	if(pRC->top < 0)
	{
		pRCClip->top = 0;
	}
	else if(pRC->bottom > m_rcScr.bottom)
	{
		pRCClip->bottom = m_rcScr.bottom;
	}

	if(pRC->left < 0)
	{ 
		pRCClip->left = 0;
		return TRUE;
	}
	else if(pRC->right > m_rcScr.right)
	{ 
		pRCClip->right = m_rcScr.right;
		return TRUE;
	}
	return FALSE;
}
