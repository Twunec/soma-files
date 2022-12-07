// DDEngine.h: interface for the CDDEngineNew class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DDENGINE_H__CF5FF875_6921_4E64_904F_C074E41AD179__INCLUDED_)
#define AFX_DDENGINE_H__CF5FF875_6921_4E64_904F_C074E41AD179__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
//#include <DDraw.h>
//#include <windows.h>
#include "MyMacro.h"
#include "MyConstAndDef.h"

#include "ddraw.h"	// Added by ClassView

//int RENDER_NORMAL = 0; // ����

class CDDEngineNew  
{
protected:
public:
	LPDIRECTDRAW			m_lpDD;
	LPDIRECTDRAWSURFACE7	m_lpDDSPri;
	LPDIRECTDRAWSURFACE7	m_lpDDSBB;
	LPDIRECTDRAWCLIPPER		m_lpDDClipper;
	
	LPDIRECTDRAW7			m_lpDD4;

//	DirectDrawCreate(NULL,&m_lpDD,NULL);
//	m_lpDD->QueryInterface(IID_IDirectDraw4, (void**)&m_pIDD4);

	HWND m_hWnd;
	BOOL m_bFullScreen;

	int m_nFrmRate; // �ʴ� �����Ӽ�..

	RECT m_rcScr; // ȭ��� ��Ÿ�� ����
	WORD*	m_pwBB; // ����� ������
	int		m_nPitchBB; // ����� ��ġ - ���� ���� -> ���� �� ��..!!

	DDSURFACEDESC2 m_ddsdTmp1, m_ddsdTmp2; // �ӽ÷θ� ���̴� ���ǽ� ����ü.. -> ���� �ӽ÷θ� ������ �Ѵ�..

	int m_nPF; // �ȼ� ����
	DWORD m_dwRBMask, m_dwRMask, m_dwGMask, m_dwBMask; // �� ���� ����ũ..

	char m_szPath[128]; // ���� ������ ���
	BOOL	m_bBBLocked; // ���� ����ۿ� ���� �ɷ� �ִ���..

	WORD m_wRTbls[32]; // ���� ���̺�
	WORD m_wGTbls[32]; // �׸� ���̺�
	WORD m_wBTbls[32]; // ��� ���̺�
public:
	// ���� ���� ����.
	LPDIRECTDRAWSURFACE7 m_lpDDSExtra; // ����� ����.. lsp ��������Ʈ�� �۰� ��� �ٰų� �Ҷ� ����.

public: // �ζ��� �Լ��� ��Ƶ���..
	int		FrmRateGet() { return m_nFrmRate; } // ������ ����
	void	ScreenGetSize(RECT* pRC) { *pRC = m_rcScr; }
	const	LPDIRECTDRAW GetDirectDraw() const { return m_lpDD; }
	int		PixelFormatGet() { return m_nPF; }

	WORD RGB16(COLORREF crColor) // �÷� ���۷��� ���� ���� �ȼ� ���˿� ���߾� 16��Ʈ ������..
	{
		if(m_nPF == PF_555) return (WORD) (	(((crColor&0x000000ff)>>3)<<10) | ((((crColor&0x0000ff00)>>8)>>3)<<5) | (((crColor&0x00ff0000)>>16)>>3) );
		else if(m_nPF == PF_565) return (WORD) ( (((crColor&0x000000ff)>>3)<<11) | ((((crColor&0x0000ff00)>>8)>>2)<<5) | (((crColor&0x00ff0000)>>16)>>3) );
		else return -1;
	}
	
	WORD RGB16(WORD wR, WORD wG, WORD wB) // R,G,B ���� ���� �ȼ� ���˿� ���߾� 16��Ʈ ������..
	{
		if(m_nPF == PF_555) return (((wR>>3)<<10) | ((wG>>3)<<5) | (wB>>3));
		else if(m_nPF == PF_565) return (((wR>>3)<<11) | ((wG>>2)<<5) | (wB>>3));
		else return -1;
	}
	
	COLORREF RGB24(WORD wColor) // ���� �ȼ� ����16��Ʈ ���� �÷� ���۷��� ������..
	{
		COLORREF crColor = wColor;
		if(m_nPF == PF_555) return ( (((crColor&0x00007c00)>>10)<<3) | ((((crColor&0x000003e0)>>5)<<3)<<8) | (((crColor&0x0000001f)<<3)<<16) );
		else if(m_nPF == PF_565) return ( (((crColor&0x0000f800)>>11)<<3) | ((((crColor&0x000007e0)>>5)<<2)<<8) | (((crColor&0x0000001f)<<3)<<16) );
		else return (crColor = -1);
	}

	HRESULT SurfaceLock(LPDIRECTDRAWSURFACE7 lpDDS, DDSURFACEDESC2* pDDSD, RECT* pRC = NULL) // ���ǽ� ��.. DMA �̿��� �ݵ�� �ý��� �޸𸮿� �����Ǿ��� ��쿡�� �Ѵ�..
	{
		MAKE_ZERO(*pDDSD);
		if(lpDDS == NULL) return -1;
		pDDSD->dwSize = sizeof(DDSURFACEDESC2);
		return lpDDS->Lock(pRC, pDDSD, DDLOCK_WAIT, NULL);
	}
	HRESULT SurfaceUnlock(LPDIRECTDRAWSURFACE7 lpDDS, RECT* pRC = NULL)
	{
		if(lpDDS == NULL) return -1;
		return lpDDS->Unlock(pRC);
	}

	void Conv565_0PixelTo555Pixel(WORD* pDest, const WORD* pSrc, int nCount) // 565 �ȼ��� 555 �ȼ��� ī��Ʈ ��ŭ ��ȯ���ش�.
	{
		for(int i = 0; i < nCount; i++, pDest++, pSrc++)
		{
			*pDest = ((*pSrc&0xffc0)>>1) | (*pSrc&0x001f);
		}
	}
	void Conv565_1PixelTo555Pixel(WORD* pDest, const WORD* pSrc, int nCount) // 565 �ȼ��� 555 �ȼ��� ī��Ʈ ��ŭ ��ȯ���ش�.
	{
		for(int i = 0; i < nCount; i++, pDest++, pSrc++)
		{
			if( *pDest == 0x00 || *pDest == 0xf81f )
				*pDest = ((*pSrc&0xffc0)>>1) | (*pSrc&0x001f);
			else
				*pDest = ((*pSrc&0xffc0)>>1) | (*pSrc&0x001f) | 0x8000;
		}
	}
	void Conv565_0SetPixel(WORD* pDest, const WORD* pSrc, int nCount) // 565 �ȼ��� 555 �ȼ��� ī��Ʈ ��ŭ ��ȯ���ش�.
	{
		for(int i = 0; i < nCount; i++, pDest++, pSrc++)
		{
			if( *pSrc & 0x20 )
				*pDest = *pSrc - 0x20;
			else *pDest = *pSrc;
		}
	}
	void Conv565_1SetPixel(WORD* pDest, const WORD* pSrc, int nCount) // 565 �ȼ��� 555 �ȼ��� ī��Ʈ ��ŭ ��ȯ���ش�.
	{
		for(int i = 0; i < nCount; i++, pDest++, pSrc++)
		{
			if( *pSrc == 0x00 || *pSrc == 0xf81f )
				*pDest = *pSrc;
			else if( *pSrc & 0x20 )
				*pDest = *pSrc;
			else *pDest = *pSrc + 0x20;
		}
	}
	void Conv555PixelTo565Pixel(WORD* pDest, const WORD* pSrc, int nCount) // 565 �ȼ��� 555 �ȼ��� ī��Ʈ ��ŭ ��ȯ���ش�.
	{
		for(int i = 0; i < nCount; i++, pDest++, pSrc++)
		{
			*pDest = ((*pSrc&0x7fe0)<<1) | (*pSrc&0x001f);
		}
	}

	void HWndSet(HWND hWnd) // Ŭ���ۿ� �ڵ� ����..
	{
		m_hWnd = hWnd;
		if(m_bFullScreen == FALSE && m_lpDDClipper != NULL) m_lpDDClipper->SetHWnd(0, hWnd);
	}

	BOOL IsBBLocked() { return m_bBBLocked; } // ���� ����ۿ� ���� �ɷ� �ִ���

public:
	void Blt(LPDIRECTDRAWSURFACE7 lpDDSDest, LPDIRECTDRAWSURFACE7 lpDDSSrc, RECT* pRCDest, RECT* pRCSrc, BOOL bUseColorKey);
	void PathSetWork(const char* szPath);
	void TextOut(LPDIRECTDRAWSURFACE7 lpDDS, int x, int y, const char* szText, COLORREF crText, UINT align = TA_TOP);
	void DrawBox(LPDIRECTDRAWSURFACE7 lpDDS, const RECT* pRC, COLORREF crColor);
	void DrawLine(LPDIRECTDRAWSURFACE7 lpDDS, int sx, int sy, int ex, int ey, COLORREF crColor);
	void DrawRhombus(LPDIRECTDRAWSURFACE7 lpDDS, int x, int y, COLORREF crColor);
	void DrawPolygon(LPDIRECTDRAWSURFACE7 lpDDS, POINT *point, int count, COLORREF crColor);

	HWND HWndGet() { return m_hWnd; }

	void Flip(const RECT* pRCClip = NULL);
	
	LPDIRECTDRAWSURFACE7 SurfaceCreateWith16BMP(const char *szFileName, BOOL bUseVideoMemory, COLORREF crCK,BOOL bSetting = FALSE);
	LPDIRECTDRAWSURFACE7 SurfaceCreateWithBMP(const char* szFileName, BOOL bUseVideoMemory, COLORREF crColorKey,BOOL bSetting = FALSE);
	LPDIRECTDRAWSURFACE7 SurfaceCreate(int nWidth, int nHeight, BOOL bUseVideoMemory, COLORREF crColorKey);
	COLORREF SurfaceColorKeyGet(LPDIRECTDRAWSURFACE7 lpDDS);
	void SurfaceColorKeySet(LPDIRECTDRAWSURFACE7 lpdds, COLORREF ColorKey);
	void SurfaceFillRect(LPDIRECTDRAWSURFACE7 lpDDS = NULL, const RECT *pRC = NULL, COLORREF crFill = 0, int nAlpha = 32);
	void SurfaceGetSize(LPDIRECTDRAWSURFACE7 lpDDS, RECT* pRC);

	void BackBufferLock();
	void BackBufferUnlock();
	void Init(HWND hWnd, BOOL bFullScreen, int nWidth, int nHeight);

	void PathSetCur(const char* szSubPath);
	const char* PathGetCur(const char* szPath, int nPath = 0) const;

	void BltNormal(LPDIRECTDRAWSURFACE7 lpDDSSrc, int x, int y, const RECT* prcSrc, BOOL bUseColorKey, int nRenderType = 0, int nAlpha = 0, COLORREF crColor = 0, LPDIRECTDRAWSURFACE7 lpDDSDest = NULL);
	void BltCenter(LPDIRECTDRAWSURFACE7 lpDDSSrc, int x, int y, const RECT* prcSrc, POINT* pptCenter, BOOL bUseColorKey, int nRenderType = 0, int nAlpha = 0, COLORREF crColor = 0, LPDIRECTDRAWSURFACE7 lpDDSDest = NULL)
	{
		x -= pptCenter->x - prcSrc->left; y -= pptCenter->y - prcSrc->top;
		this->BltNormal(lpDDSSrc, x, y, prcSrc, bUseColorKey, nRenderType, nAlpha, crColor, lpDDSDest);
	}

	CDDEngineNew();
	virtual ~CDDEngineNew();

protected:
	LPDIRECTDRAWSURFACE7 SurfaceCreateWithGenericBMP(const char *szFileName, BOOL bUseVideoMemory, COLORREF crCK);

	// ��û�� ũ���� �ζ��� �Լ�.. �ӵ��� �ſ� �ΰ��ϴ�. - BltAlphaAdd.
	void PutPixelNormal(const WORD* pDest, const WORD* pSrc, int nCopyCount)
	{
/*		__asm // 32��Ʈ ī��...
		{
			mov edi, pDest;
			mov esi, pSrc;
			mov eax, nCopyCount;
			
			mov edx, 0;
			mov ecx, 2;
			div ecx; // ���� eax, ������ edx;
			cmp eax, 0;
			je WORD_COPY_LOOP;

DWORD_COPY_LOOP:
			dec eax;
			movsd; // ���� ���� ī��..
			jnz DWORD_COPY_LOOP; // ��ŭ �޸� ����
			cmp edx, 0;
			je DONT_WORD_COPY; // ���� ī�� �ʿ� ����.

WORD_COPY_LOOP:
			movsw;
			dec edx;
			jnz WORD_COPY_LOOP;
DONT_WORD_COPY:
		}
*/
		__asm
		{
			mov edi, pDest;
			mov esi, pSrc;
			
			mov ecx, nCopyCount;
			
//			movd mm0, nCopyCount;
//			movd nCopyCount, mm0;
//			EMMS

WORD_COPY_LOOP:
			movsw;
			dec ecx;
			jnz WORD_COPY_LOOP;
		}

	};

	void PutPixelAlphaAdd(const WORD* pDest, const WORD* pSrc, int nCopyCount, DWORD dwRMask, DWORD dwGMask, DWORD dwBMask)
	{
		__asm
		{
			mov edi, pDest;	// ��׶��� �ּ� ����.
			mov esi, pSrc;	// ��������Ʈ �ּ� ����.

			mov ecx, nCopyCount; // ���� ����.

COPY_LOOP:
			push ecx;
			mov ecx, [esi]; // Spr

			jecxz DONT_COPY; // ��������Ʈ ������ 0 �̸�... ó�� ����..

			mov ebx, 0; // ���� �ȼ�

			mov eax, ecx; // Spr - R
			mov edx, [edi]; // Bkg - R
			and eax, dwRMask;
			and edx, dwRMask;
			add edx, eax;
			cmp edx, dwRMask;
			ja COPY_R1;
			jmp ADD_R1;
COPY_R1:
			mov edx, dwRMask;
ADD_R1:
			or ebx, edx;

			mov eax, ecx; // Spr - G
			mov edx, [edi]; // Bkg - G
			and eax, dwGMask;
			and edx, dwGMask;
			add edx, eax;
			cmp edx, dwGMask;
			ja COPY_G1;
			jmp ADD_G1;
COPY_G1:
			mov edx, dwGMask;
ADD_G1:
			or ebx, edx;

			mov eax, ecx; // Spr - B
			mov edx, [edi]; // Bkg - B
			and eax, dwBMask;
			and edx, dwBMask;
			add edx, eax;
			cmp edx, dwBMask;
			ja COPY_B1;
			jmp ADD_B1;
COPY_B1:
			mov edx, dwBMask;
ADD_B1:
			or ebx, edx;

			mov [edi], bx; // ����ۿ� ��
			
DONT_COPY:
			add edi, 2;
			add esi, 2;

			pop ecx;
			dec ecx;
			jnz COPY_LOOP;
		}
	};

	void PutPixelAlphaSoft(const WORD* pDest, const WORD* pSrc, int nCopyCount, DWORD dwRMask, DWORD dwGMask, DWORD dwBMask)
	{
		__asm
		{
			mov edi, pDest;	// ��׶��� �ּ� ����.
			mov esi, pSrc;	// ��������Ʈ �ּ� ����.

			mov ecx, nCopyCount; // ���� ����.

COPY_LOOP:
			push ecx; // ī��Ʈ ���

			mov ecx, [esi]; // ��������Ʈ �ȼ�

			jecxz DONT_COPY; // ��������Ʈ ������ 0 �̸�... ó�� ����..
			
			mov ebx, 0; // ���� �ȼ� ��..

			mov ecx, [esi]; // Spr �ȼ�
			
			mov edx, [edi]; // Bkg - R
			mov eax, ecx // Spr - R
			and edx, dwRMask;
			and eax, dwRMask;
			cmp eax, edx;
			jb COPY_R1_BKG;
			mov edx, eax
COPY_R1_BKG:
			or ebx, edx;

			mov edx, [edi]; // Bkg - R
			mov eax, ecx // Spr - R
			and edx, dwGMask;
			and eax, dwGMask;
			cmp eax, edx;
			jb COPY_G1_BKG;
			mov edx, eax
COPY_G1_BKG:
			or ebx, edx;

			mov edx, [edi]; // Bkg - R
			mov eax, ecx // Spr - R
			and edx, dwBMask;
			and eax, dwBMask;
			cmp eax, edx;
			jb COPY_B1_BKG;
			mov edx, eax
COPY_B1_BKG:
			or ebx, edx;

			mov [edi], bx; // ����ۿ� ��
		
DONT_COPY:
			add edi, 2;
			add esi, 2;

			pop ecx; // ī��Ʈ ����
			dec ecx;
			jnz COPY_LOOP;
		}
	};

	void PutPixelTrans(const WORD* pDest, const WORD* pSrc, int nCopyCount, int nAlphaDest, int nAlphaSrc, DWORD dwRBMask, DWORD dwGMask) // nAlphaSrc �� nAlphaDest �� ���� �ݵ�� 32 �̾�� �Ѵ�..
	{
/*		__asm // RGB ������ ���� ���..
		{
			mov edi, pDest;
			mov esi, pSrc;
			mov ecx, nCopyCount;
COPY_LOOP:
			push ecx; // ī��Ʈ ����..

			mov ebx, 0; // ���� ���� �ʱ�ȭ

			mov ecx, [esi]; // Spr Pixel

			jecxz DONT_COPY; // ��������Ʈ ������ 0 �̸�... ó�� ����..

			mov eax, ecx; // Spr - R B
			and eax, dwRBMask;
			mul nAlphaSrc;
			shr eax, 5;
			and eax, dwRBMask;
			add ebx, eax;

			mov eax, ecx; // Spr - G
			and eax, dwGMask;
			mul nAlphaSrc;
			shr eax, 5;
			and eax, dwGMask;
			add ebx, eax;
			
			mov ecx, [edi]; // Bkg Pixel

			mov eax, ecx; // Bkg - R B
			and eax, dwRBMask;
			mul nAlphaDest;
			shr eax, 5;
			and eax, dwRBMask;
			add ebx, eax;
			
			mov eax, ecx; // Bkg - G
			and eax, dwGMask;
			mul nAlphaDest;
			shr eax, 5;
			and eax, dwGMask;
			add ebx, eax;
			
			mov [edi], bx;
DONT_COPY:
			add edi, 2;
			add esi, 2;
			
			pop ecx; // ī��Ʈ ����..
			dec ecx;
			jnz COPY_LOOP;
		}
*/	};

	void PutPixelDark(const WORD* pDest, const WORD* pSrc, int nCopyCount, int nAlphaSrc, DWORD dwRBMask, DWORD dwGMask) // nAlphaSrc - 0 �� �� ��Ŀ�ݴ�.. 32 �� ���� ���.
	{
		__asm // RGB ������ ���� ���..
		{
			mov edi, pDest;
			mov esi, pSrc;
			mov ecx, nCopyCount;
COPY_LOOP:
			push ecx; // ī��Ʈ ����..

			mov ebx, 0; // ���� ���� �ʱ�ȭ

			mov ecx, [esi]; // Spr Pixel

			jecxz DONT_COPY; // ��������Ʈ ������ 0 �̸�... ó�� ����..

			mov eax, ecx; // Spr - R B
			and eax, dwRBMask;
			mul nAlphaSrc;
			shr eax, 5;
			and eax, dwRBMask;
			add ebx, eax;
			
			mov eax, ecx; // Spr - G
			and eax, dwGMask;
			mul nAlphaSrc;
			shr eax, 5;
			and eax, dwGMask;
			add ebx, eax;
			
			mov [edi], bx;

DONT_COPY:

			add edi, 2;
			add esi, 2;
			
			pop ecx; // ī��Ʈ ����..
			dec ecx;
			jnz COPY_LOOP;
		}
	};

	void PutPixelShadow(const WORD* pDest, const WORD* pSrc, int nCopyCount, DWORD dwRBMask, DWORD dwGMask) // 0 ��Ŀ�� �׸���.. 32 �׸��� ����..
	{
		__asm // RGB ������ ���� ���..
		{
			mov edi, pDest;
			mov esi, pSrc;

			mov ecx, nCopyCount;
COPY_LOOP:
			push ecx; // ī��Ʈ ����..

			mov cx, [esi]; // ���İ� ���
			jcxz DONT_COPY; // �ҽ��� ���� ���̸� �Ѿ��.
			and ecx, 0x001f; // 
			mov ebx, 0x001f;
			sub ebx, ecx;
			mov ecx, ebx;

			mov ebx, 0; // ���� ���� �ʱ�ȭ

			mov eax, [edi]; // Bkg - R B
			and eax, dwRBMask;
			mul ecx;
			shr eax, 5;
			and eax, dwRBMask;
			add ebx, eax;
			
			mov eax, [edi]; // Bkg - G
			and eax, dwGMask;
			mul ecx;
			shr eax, 5;
			and eax, dwGMask;
			add ebx, eax;
			
			mov [edi], bx;

DONT_COPY:
			add edi, 2;
			add esi, 2;
			
			pop ecx; // ī��Ʈ ����..
			dec ecx;
			jnz COPY_LOOP;
		}
	};
	
	void PutPixelColor(const WORD* pDest, const WORD* pSrc, int nCopyCount, int nAlphaSrc, DWORD dwDestColor, DWORD dwRBMask, DWORD dwGMask) // nAlphaSrc - ��������Ʈ�� ��� ��. dwDestColor - �÷��� 32��Ʈ ��. (�ݵ�� "32-nAlphaSrc"�� ������ ��ġ�Ͽ��� �Ѵ�.
	{
		__asm // RGB ������ ���� ���..
		{
			mov edi, pDest;
			mov esi, pSrc;
			mov ecx, nCopyCount;
COPY_LOOP:
			push ecx; // ī��Ʈ ����..

			mov ebx, 0; // ���� ���� �ʱ�ȭ

			mov ecx, [esi]; // Spr Pixel

			jecxz DONT_COPY; // ��������Ʈ ������ 0 �̸�... ó�� ����..

			mov eax, ecx; // Spr - R B
			and eax, dwRBMask;
			mul nAlphaSrc;
			shr eax, 5;
			and eax, dwRBMask;
			add ebx, eax;
			
			mov eax, ecx; // Spr - G
			and eax, dwGMask;
			mul nAlphaSrc;
			shr eax, 5;
			and eax, dwGMask;
			add ebx, eax;
			
			add ebx, dwDestColor; // �÷� ���� �����ش�.
			
			mov [edi], bx;

DONT_COPY:

			add edi, 2;
			add esi, 2;
			
			pop ecx; // ī��Ʈ ����..
			dec ecx;
			jnz COPY_LOOP;
		}
	};
};

#endif // !defined(AFX_DDENGINE_H__CF5FF875_6921_4E64_904F_C074E41AD179__INCLUDED_)
