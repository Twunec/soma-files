// Rain.cpp: implementation of the CRain class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Rain.h"
//#include <time.h>
//#include <stdlib.h>
//#include <stdio.h>
#include "CharManager.h"
#include "ChildView.h"

#include "user.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DWORD CRain::m_dwTime		= 0;
BOOL  CRain::m_bLightning	= FALSE;
int   CRain::m_nRainNum		= 0;
int   CRain::m_nState		= 0;
DWORD CRain::m_dwStateTime	= 0;
int	  CRain::m_nAlphaGamma	= 50;
BOOL  CRain::m_bReduce		= FALSE;
BOOL  CRain::m_bIncrease	= FALSE;
BOOL  CRain::m_bGammaApplyed = FALSE;
int g_nAniFrame				= 0;

CArray< WORD*, WORD* > CRain::m_arrPword;
CArray< _SPR_LSP *,_SPR_LSP *> CRain::m_arrSprLsp;

CRain::CRain()
{
	m_nFrame		= g_nAniFrame;
	m_nCurFrame		= 0;
	m_nX			= 0;
	m_nY			= 0;
	m_nWidth		= 0;
	m_nCount		= 0;
	m_nRainDropsX	= -1;
	m_nRainDropsY	= -1;
	m_bDropsEnabled = FALSE;
	m_dwDropsTime   = 0;
	m_nLength		= 0;
}

CRain::~CRain()
{
	WORD* pWord = NULL;
	int nArrSize = m_arrPword.GetSize();
	for( int i = 0; i < nArrSize ; i++ )
	{
		pWord = m_arrPword.GetAt(i);
		if( pWord ) delete [] pWord;
		pWord = NULL;
	}
	m_arrPword.RemoveAll();
	
	_SPR_LSP* pSprData = NULL;
	nArrSize = m_arrSprLsp.GetSize();
	for( i = 0 ; i < nArrSize ; i++ )
	{
		pSprData = m_arrSprLsp.GetAt(i); 
		if( pSprData ) delete pSprData;
		pSprData = NULL;

	}
	m_arrSprLsp.RemoveAll();

}

void CRain::SetState()
{
	static BOOL bNext = FALSE;
	DWORD dwNowTime = GetTickCount();
	if( dwNowTime - m_dwStateTime > 5000 )
	{
		if( 1 == rand()%2 )
		{
			m_bLightning = TRUE;
			if( 1 == rand()%2 )
				bNext = TRUE;
		}

		int nState;
		m_dwStateTime = dwNowTime;
		nState = rand()%2;
		if( nState == 0 )
		{
			if( m_nState == 0 ) return;
			else m_nState -= 1;
		}
		else
		{
			if( m_nState == 2 ) return;
			else m_nState += 1; 
		}
	}
	if( bNext == TRUE &&( dwNowTime - m_dwStateTime > 150 ) )
	{
		m_bLightning = TRUE;
		bNext = FALSE;
	}

}

BOOL CRain::RainMove()
{
	switch(m_nState)
	{
	case 0:
		m_nX -= 7;

		if( m_nWidth  == 2 ) m_nY += 20;
		else				 m_nY += 10;

		break;
	case 1:
		if( m_nWidth  == 2 )
		m_nY += 20;
		else m_nY += 10;
		break;
	case 2:
		m_nX += 7;

		if( m_nWidth == 2 ) m_nY += 20;
		else 				m_nY += 10;
		break;
	}
	m_nCount++;

	if( m_nY >= 575 || m_nX <= 0 || m_nX >= 800 )
	{
		return TRUE;
	}

	switch( m_nWidth )
	{
	case 1:
		m_nLength--;
		if( m_nCount >= 10 )
		{
			m_nRainDropsX = m_nX;
			m_nRainDropsY = m_nY;	
			m_nCount = 0;
			m_bDropsEnabled = TRUE;
			m_nCurFrame = 0;
			return TRUE;
		}
		break;
	case 2:
		//if( m_nCount % 2 )
		m_nLength--; 
		if( m_nCount >= 15 )
		{
			m_nRainDropsX = m_nX;
			m_nRainDropsY = m_nY;	
			m_nCount = 0;
			m_bDropsEnabled = TRUE;
			m_nCurFrame = 0;
			return TRUE;
		}
		break;
	}
	return FALSE;
}
void CRain::SetPosition()
{
	m_nX = rand()%800;
	m_nY = rand()%300;
	m_nWidth = rand()%2 + 1;
	if( m_nWidth == 2 ) m_nLength = 13;
	else				m_nLength = 10;

}
void CRain::RainDraw( DDSURFACEDESC2 ddsd )
{
	int lPitch = ddsd.lPitch / 2;

	WORD* pSurface = (WORD*)((PBYTE)ddsd.lpSurface);
	int j, nSide = 0;
	WORD RAIN;

	switch( m_nWidth )
	{
	case 1:
		if( CChildView::CharManager.GetPixelFormat() == 565 )
			RAIN = 0xa514;
		else
			RAIN = 0x5294;
		break;
	case 2:
		if( CChildView::CharManager.GetPixelFormat() == 565 )
			RAIN = 0xffff;
		else
			RAIN = 0xffff;
		break;
	}
	
	switch( m_nState )
	{
	case 0:
			for( j = 0; j < m_nLength ; j++ )
			{
				*( pSurface + lPitch*(j + m_nY) + nSide + m_nX ) = RAIN; 
				if( j % 3 == 0 ) nSide--;
			}
			nSide = 0;
		break;
	case 1:
			for( j = 0; j < m_nLength ; j++ )
				*( pSurface + lPitch*(j + m_nY) + m_nX ) = RAIN; 
		break;
	case 2:
			for( j = 0; j < m_nLength ; j++ )
			{
				*( pSurface + lPitch*(j + m_nY) + nSide + m_nX ) = RAIN; 
				if( j % 3 == 0 ) nSide++;
			}
			nSide = 0;

			break;
	}

}

BOOL CRain::RainDrops( BOOL bEarth, DDSURFACEDESC2 ddsd, CPoint dPos )
{
	if( !m_bDropsEnabled ) return FALSE;

	int lPitch = ddsd.lPitch / 2;
	WORD* pSurface = (WORD*)((PBYTE)ddsd.lpSurface);
	
	WORD RAINDROPS;
	if( CChildView::CharManager.GetPixelFormat() == 565 )
		RAINDROPS = 0xa514;
	else RAINDROPS = 0x5294;

	//m_nRainDropsX -= dPos.x;
	//m_nRainDropsY -= dPos.y;

	if(m_nRainDropsY < 0 || m_nRainDropsY >= 575 || m_nRainDropsX < 0 || m_nRainDropsX >= 800 )
	{
		return TRUE;
	}
	if( bEarth )
	{
		switch( m_nWidth )
		{
		case 1:
			*( pSurface + lPitch*m_nRainDropsY + m_nRainDropsX ) = RAINDROPS; 

			break;
		case 2:
			*( pSurface + lPitch*m_nRainDropsY + m_nRainDropsX )			 = 0xffff;//RAINDROPS; 
//			*( pSurface + lPitch*m_nRainDropsY + 1 + m_nRainDropsX )		 = RAINDROPS; 
//			*( pSurface + lPitch*m_nRainDropsY + lPitch + m_nRainDropsX )	 = RAINDROPS; 
//			*( pSurface + lPitch*m_nRainDropsY + lPitch + 1 +m_nRainDropsX ) = RAINDROPS; 
			break;
		}

	}
	else
	{
		
		WORD* pWord= m_arrPword.GetAt( m_nCurFrame ); 
		_SPR_LSP* pSprData = m_arrSprLsp.GetAt( m_nCurFrame ); 
		
		DWORD dwNowTime = GetTickCount();
		BltLSPNormal( ddsd, m_nRainDropsX, m_nRainDropsY, &(pSprData->rcV), pWord);
		if( dwNowTime - m_dwDropsTime > 100 )
		{
			m_dwDropsTime = dwNowTime;
			m_nCurFrame++;
		}
		if( m_nFrame <= m_nCurFrame ) m_nCurFrame = 0;
	}

	return TRUE;

}
BOOL CRain::LightningEx(LPDIRECTDRAWGAMMACONTROL lpDDGammaControl, DDGAMMARAMP* pDDGammaLightning,DDGAMMARAMP* pDDGammaRamp )
{
	if( !m_bLightning ) return TRUE;
	if( m_nAlphaGamma ) return TRUE;//�� �ö� �ִ�� ��ο������� ����ȿ���� �ֱ� ����
	//������ ������ �����Ǹ� ������ �����ش�. TRUE�� �������༭

	static BOOL bConverted = TRUE;
	static BOOL bNext = FALSE;
	DWORD nInterval;
	if( bNext )
		nInterval = 50;
	else nInterval = 100;

	DWORD dwNowTime = GetTickCount();
	if( bConverted == TRUE )
	{
		m_dwTime = GetTickCount();
		bConverted = FALSE;
	}
	if( dwNowTime - m_dwTime < nInterval )
	{
		bConverted = FALSE;
	}
	else
	{
		bNext = !bNext;
		bConverted = TRUE;
//		m_bLightning = TRUE;
		if ( m_bGammaApplyed )
			CChildView::DirectXMng.SetRainGammaRate( m_nAlphaGamma - 50 );
		else CChildView::DirectXMng.SetRainGammaRate( 0 );

//		lpDDGammaControl->SetGammaRamp(0, pDDGammaRamp); 
		return TRUE;
	}

	HRESULT hr = lpDDGammaControl->SetGammaRamp(0, pDDGammaLightning); 

	if( FAILED( hr ) ) return FALSE;
	return FALSE;
}

int CRain::SetGammaRamp( LPDIRECTDRAWGAMMACONTROL lpDDGammaControl, DDGAMMARAMP* pDDGammaRamp, BOOL bGamma )
{

	if( !m_bReduce && !m_bIncrease ) return 0;

	static DWORD dwGammaTime = GetTickCount();
	DWORD dwNowTime = GetTickCount();

	if( dwNowTime - dwGammaTime < 200 ) return 0;

	dwGammaTime = dwNowTime;

	m_bGammaApplyed = bGamma;

	if( m_bReduce )
	{
		if( m_nAlphaGamma <= 0 ) 
		{
			m_bReduce = FALSE;
			m_nAlphaGamma = 0;
			m_nRainNum = 150;
			return 3;
		}
		m_nAlphaGamma--;

		if( bGamma )
		{
			CChildView::DirectXMng.SetRainGammaRate( m_nAlphaGamma - 50 );
/*
			for(int loop=0;loop<256;loop++)
			{
				if(pDDGammaRamp->red[loop] > 255) 
					pDDGammaRamp->red[loop] -= 255; 
				else pDDGammaRamp->red[loop] = 0;

				if(pDDGammaRamp->green[loop] > 255)
					pDDGammaRamp->green[loop] -= 255; 
				else pDDGammaRamp->green[loop] = 0;

				if(pDDGammaRamp->blue[loop] > 255) 
					pDDGammaRamp->blue[loop] -= 255; 
				else pDDGammaRamp->blue[loop] = 0;
			}
			if( lpDDGammaControl )
				lpDDGammaControl->SetGammaRamp(0, pDDGammaRamp);
*/
		}
		m_nRainNum += 3;
		return 1;
	}
	if( m_bIncrease )
	{
		m_nAlphaGamma++;
		if( m_nAlphaGamma >= 50 )
		{
			m_bIncrease = FALSE;
			m_nAlphaGamma = 50;
			m_nRainNum = 0;
			return 4;
		}

		if( bGamma )
		{
			CChildView::DirectXMng.SetRainGammaRate( m_nAlphaGamma - 50 );

/*			for(int loop=0;loop<256;loop++)
			{
				if( loop > m_nAlphaGamma )
					pDDGammaRamp->red[loop] += 255; 

				if( loop > m_nAlphaGamma )
					pDDGammaRamp->green[loop] += 255; 

				if( loop > m_nAlphaGamma )
					pDDGammaRamp->blue[loop] += 255; 
			}

			if( lpDDGammaControl )
				lpDDGammaControl->SetGammaRamp(0, pDDGammaRamp); 
*/
		}
		m_nRainNum -= 3;
		return 2;
	}
	return 0;
}

BOOL CRain::LoadRainDrops( TCHAR* strName )
{
	FILE *file;
    file = fopen( strName, "rb" );
	_SPR_HEADER HSpr;
	if( file == NULL )
	{
		return FALSE;
	}

	UINT nReadCount;
	nReadCount = fread( &HSpr, sizeof(_SPR_HEADER), 1, file );
	if( nReadCount == sizeof(_SPR_HEADER))
	{
		return FALSE;
	}

	fseek( file, sizeof(_SPR_TOOL)*HSpr.nQt, SEEK_CUR );

	_SPR_LSP *pSprData;		//������ ������ ���� ������
	g_nAniFrame = HSpr.nQt; 
	for (int i=0; i<HSpr.nQt; i++)
	{
		pSprData = new _SPR_LSP;
		nReadCount = fread( pSprData, sizeof(_SPR_LSP), 1, file );
		pSprData->pwV = NULL;
		m_arrSprLsp.Add( pSprData ); 
	}
	PWORD	pWordData;
	UINT	nCount;

	for ( i = 0; i < HSpr.nQt; i++ )
	{
		
		pSprData = m_arrSprLsp.GetAt(i); 
		nCount = pSprData->nDataSize;
		if (nCount)
		{
			pWordData = new WORD[nCount>>1];
			fread( (PVOID)pWordData, 1, nCount, file );
			m_arrPword.Add(pWordData); 
		}

	}

	fclose( file );
	return TRUE;

}
BOOL CRain::GetClippedRect(RECT *pRC, RECT* pRCClip)
{
	int ScreenX = 800;
	int ScreenY = 600;

	BOOL bUseXClip = FALSE;
	*pRCClip = *pRC;

	if(pRC->left < 0)
	{ 
		pRCClip->left = 0;
		bUseXClip = TRUE;
	}
	else if(pRC->right > ScreenX)
	{ 
		pRCClip->right = ScreenX;
		bUseXClip = TRUE;
	}
	if(pRC->top < 0)
	{
		pRCClip->top = 0;
	}
	else if(pRC->bottom > ScreenY)
	{
		pRCClip->bottom = ScreenY;
	}
	return bUseXClip;
}

void CRain::BltLSPNormal(DDSURFACEDESC2 ddsd, int x, int y, RECT* pRC, WORD* data)
{
	if(data == NULL) return;
	if(pRC == NULL) return;

	int ScreenX = 800;
	int ScreenY = 600;

	if(pRC->right - pRC->left <= 0 || pRC->bottom - pRC->top <= 0) return; // ��ȿ�� �ȼ��� ������ ���ư���..
	RECT rc = {x+pRC->left, y+pRC->top, x+pRC->right, y+pRC->bottom};
	if(rc.right < 0 || rc.bottom < 0 || rc.left >= ScreenX || rc.top >= ScreenY) return; // ȭ���� ������ ���..

	RECT rcClip; // Ŭ���� ������ ���ϰ� �ɼµ� ���Ѵ�.
	BOOL bUseXClip = GetClippedRect(&rc, &rcClip); // ���� ����, Ŭ���� ó���� ����

	int nNode; // �Ѷ��δ� ����..
	int nZeroCount = 0; // �ǳʶٴ� �ȼ��� ����
	int nCopyCount = 0; // ������ �ȼ��� ����

	const WORD* pSrc = data; 
//	int nLine = *pSrc; pSrc++; // ���̰� ��ϵǾ� �ִ�.
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

	WORD* pDestOrg = (PWORD)((PBYTE)ddsd.lpSurface+rcClip.left*2+rcClip.top*ddsd.lPitch);
	int pitchDest = ddsd.lPitch/2; // ���� �ȼ������̱ⶫ�� �׻� /2 �� ���ش�.
	int width = rcClip.right - rcClip.left; 
	int height = rcClip.bottom - rcClip.top;

	if(bUseXClip == FALSE) // X �� Ŭ������ �ʿ���ٸ�..
	{
		int nPixelCount = 0; // �ǳʶٴ� ��ȿ �ȼ��� ����
		for(y = 0; y < height; y++)
		{
			WORD* pDest = pDestOrg + pitchDest * y;
			nNode = *pSrc; pSrc++;
			for(;nNode;nNode--, pDest+=nCopyCount, pSrc+=nCopyCount) // �ȼ��� ��ŭ ������ �̵�..
			{
				pDest += *pSrc; pSrc++; // 0 �κ� skip...
				nCopyCount = *pSrc; pSrc++; // ��ȿ �ȼ�, ������ �ȼ� ���� ���
				if(nCopyCount == 0) return;
				CUser::PutPixelHalf(pDest, pSrc, nCopyCount, CChildView::DirectXMng.m_dwHalf16Mask,CChildView::DirectXMng.m_dwHalf32Mask);
				//CUser::PutPixelNormal(pDest, pSrc, nCopyCount);

			}
		}
	}
	else // X �� Ŭ������ �Ͼ�ٸ�..
	{
		int nAddCount = 0; // 0 �ȼ��� ����, ��ȿ �ȼ� ����
		int ndxZ, ndxS, ndxE; // ������ ���� ����, �ȼ�����, �� ��ġ �ε���..
		int clipXL = -rc.left;
		int clipXR = rc.right - ScreenX;
		
		for(y = 0; y < height; y++)
		{
			WORD* pDest = pDestOrg+pitchDest*y;
			nNode = *pSrc; pSrc++;
			ndxE = 0; // ������ ���� �ε���
			for(;nNode;nNode--, pDest+=nCopyCount, pSrc += nCopyCount + nAddCount)
			{
				nZeroCount = *pSrc; pSrc++; // 0 �κ� skip...
				nCopyCount = *pSrc; pSrc++; // ��ȿ �ȼ� ���� ���
				ndxZ = ndxE;
				ndxS = ndxE + nZeroCount;
				ndxE = ndxS + nCopyCount;
				if(clipXL > 0) // ���� Ŭ����
				{
					if(ndxE <= clipXL) { pSrc += nCopyCount; nCopyCount = 0; continue; }
					if(ndxZ >= clipXL) { pDest += nZeroCount; }
					else if(ndxZ < clipXL)
					{
						if(ndxS < clipXL) { nCopyCount -= clipXL - ndxS; pSrc += clipXL - ndxS; }
						else { pDest += ndxS - clipXL; }
					}
				}
				if(clipXR > 0) // ������ Ŭ����
				{
					nAddCount = 0;
					if(ndxZ >= width || ndxS >= width) continue;
					pDest += nZeroCount;
					if(ndxE > width)
					{
						nCopyCount -= ndxE - width;
						nAddCount = ndxE - width;
					}
				}
				CUser::PutPixelHalf(pDest, pSrc, nCopyCount, CChildView::DirectXMng.m_dwHalf16Mask,CChildView::DirectXMng.m_dwHalf32Mask);
				//CUser::PutPixelNormal(pDest, pSrc, nCopyCount);
				// }

			}
		}
	}
}



/*
	case 0:
		for( i = 0; i < m_nWidth ; i++ )
		{
			for( int j = 0; j < 6 + m_nWidth*3 ; j++ )
			{
				*( pSurface + lPitch*(j + m_nY) + i+ nSide + m_nX ) = 0xffff; 
				if( j % 3 == 0 )
					nSide--;
			}
			nSide = 0;
		}
		break;
	case 1:
		for( i = 0; i < m_nWidth ; i++ )
		{
			for( int j = 0; j < 6 + m_nWidth*3 ; j++ )
				*( pSurface + lPitch*(j + m_nY) + i + m_nX ) = 0xffff; 
		}
		break;
	case 2:
		for( i = 0; i < m_nWidth ; i++ )
		{
			for( int j = 0; j < 6 + m_nWidth*3 ; j++ )
			{
				*( pSurface + lPitch*(j + m_nY) + i + nSide + m_nX ) = 0xffff; 
				if( j % 3 == 0 )
					nSide++;
			}
			nSide = 0;
		}
		break;
*/