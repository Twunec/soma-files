// DDEngine.cpp: implementation of the CDDEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DDEngine.h"
#include "Dib16.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDDEngine::CDDEngine()
{
	m_bFullScreen = 0;
	MAKE_ZERO(m_ddsdTmp1);
	MAKE_ZERO(m_ddsdTmp2);

	m_dwRBMask = 0;
	m_dwRMask = 0;
	m_dwGMask = 0;
	m_dwBMask = 0;

	m_hWnd = NULL;
	m_lpDD = NULL;
	m_lpDDClipper = FALSE;
	m_lpDDSBB = NULL;
	m_lpDDSPri = NULL;

	m_nPF = 0;
	m_nPitchBB = 0;
	m_pwBB = NULL;

	SetRect(&m_rcScr, 0, 0, 0, 0);

	m_nFrmRate = 40;

	MAKE_ZERO(m_szPath);

	m_bBBLocked = FALSE; // ���� ����ۿ� ���� �ɷ� �ִ���..

	// �÷� ���̺� �ʱ�ȭ
	MAKE_ZERO(m_wRTbls);
	MAKE_ZERO(m_wGTbls);
	MAKE_ZERO(m_wBTbls);
}

CDDEngine::~CDDEngine()
{
	RELEASE_SAFE(m_lpDDSExtra); // ���� �ý��� ���� ����.
	RELEASE_SAFE(m_lpDDSBB);
	RELEASE_SAFE(m_lpDDSPri);
	RELEASE_SAFE(m_lpDDClipper);
	RELEASE_SAFE(m_lpDD);
}

void CDDEngine::Init(HWND hWnd, BOOL bFullScreen, int nWidth, int nHeight)
{
	// ���� ������ �ڵ�, ����� ���� ���, Ǯ ��ũ�� ��� ���
	m_hWnd = hWnd;
	m_bFullScreen = bFullScreen;

	HRESULT rval = 0; // DirectDraw ��ü ����
	rval = DirectDrawCreate(NULL, &m_lpDD, NULL);
	if(rval != DD_OK) { MessageBox(m_hWnd, "DirecX Not Installed. or Incorrect.", "Initialization Error", MB_OK); exit(-1);}
//	rval = lpDD1->QueryInterface(IID_IDirectDraw7, (void**)&m_lpDD);
//	if(rval != DD_OK) { MessageBox(m_hWnd, "DirectX 7 Not Installed. or Incorrect.", "Initialization Error", MB_OK); exit(-1);}
//	RELEASE_SAFE(lpDD1);

	DDSCAPS		ddscaps; DDSURFACEDESC	ddsd;

	// ��ũ�� ������ ����� ���� ���..
	SetRect(&m_rcScr, 0, 0, nWidth, nHeight);

	// Ǯ��ũ���� ��� ....
	if(m_bFullScreen == TRUE)
	{
		rval = m_lpDD->SetCooperativeLevel(m_hWnd, DDSCL_ALLOWREBOOT | DDSCL_EXCLUSIVE | DDSCL_FULLSCREEN);
		if (rval != DD_OK)
		{
			MessageBox(m_hWnd, "Can't set cooperative level. Check DirecX.", "Initialization Error", MB_OK);
			exit(-1);
		}

		rval = m_lpDD->SetDisplayMode(m_rcScr.right, m_rcScr.bottom, 16);
		if (rval != DD_OK)
		{
			MessageBox(m_hWnd, "Can't set display mode. Check DirecX.", "Initialization Error", MB_OK);
			exit(-1);
		}

		// Primary ���� ���� - Flipping ����
		MAKE_ZERO(ddscaps);
		MAKE_ZERO(ddsd);
		ddsd.dwSize     = sizeof(ddsd);
		ddsd.dwFlags    = DDSD_CAPS | DDSD_BACKBUFFERCOUNT;
		ddsd.ddsCaps.dwCaps    = DDSCAPS_PRIMARYSURFACE | DDSCAPS_FLIP | DDSCAPS_COMPLEX | DDSCAPS_VIDEOMEMORY;
		ddsd.dwBackBufferCount = 1;
		rval = m_lpDD->CreateSurface(&ddsd, &m_lpDDSPri, NULL); // Create the primary surface

		ddscaps.dwCaps         = DDSCAPS_BACKBUFFER;
		rval = m_lpDDSPri->GetAttachedSurface(&ddscaps, &m_lpDDSBB);
	}
	// ������ ���..
	else if(m_bFullScreen == FALSE)
	{
		rval = m_lpDD->SetCooperativeLevel(m_hWnd, DDSCL_NORMAL);
		// Primary ���� ����
		MAKE_ZERO(ddscaps);
		MAKE_ZERO(ddsd);
		ddsd.dwSize         = sizeof(ddsd);
		ddsd.dwFlags        = DDSD_CAPS;
		ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE | DDSCAPS_VIDEOMEMORY;
		
		rval = m_lpDD->CreateSurface(&ddsd, &m_lpDDSPri, NULL); // Create the primary surface

		rval = DirectDrawCreateClipper(0, &m_lpDDClipper, 0);
		rval = m_lpDDClipper->SetHWnd(0, m_hWnd); // Ŭ����
		rval = m_lpDDSPri->SetClipper(m_lpDDClipper);
		
		// BackBuffer ���� - �ý��� �޸𸮿� �����.
		MAKE_ZERO(ddsd);
		ddsd.dwSize         = sizeof(ddsd);
		ddsd.dwFlags        = DDSD_CAPS | DDSD_WIDTH | DDSD_HEIGHT;// | DDSD_PIXELFORMAT;
		ddsd.dwWidth        = m_rcScr.right;
		ddsd.dwHeight       = m_rcScr.bottom;
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
//		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
		rval = m_lpDD->CreateSurface(&ddsd, &m_lpDDSBB, NULL); // Create the rendering surface

		if(rval != DD_OK)
		{
			MessageBox(m_hWnd, "there is not enough video memory for BackBuffer.", "Initialization Error", MB_OK);
			exit(-1);
		}
	}

	// Pixel Format ����, ����ũ �̸� ����
	DDPIXELFORMAT PF;
	PF.dwSize = sizeof(DDPIXELFORMAT);
	PF.dwFlags = DDPF_RGB;
	rval = m_lpDDSBB->GetPixelFormat(&PF);
	if(PF.dwRBitMask == 0x7c00) // 555
	{
		m_nPF = PF_555;
		m_dwRBMask = 0x00007c1f;
		m_dwRMask = 0x00007c00;
		m_dwGMask = 0x000003e0;
		m_dwBMask = 0x0000001f;
	}
	else if(PF.dwRBitMask == 0xf800) // 565
	{
		m_nPF = PF_565;
		m_dwRBMask = 0x0000f81f;
		m_dwRMask = 0x0000f800;
		m_dwGMask = 0x000007e0;
		m_dwBMask = 0x0000001f;
	}
	else 
	{
		char szTemp[128];
		wsprintf(szTemp, "Current BitsPerPixel is not 16 or Unknown PixelFormat... R:%d, G:%d, B:%d", PF.dwRBitMask, PF.dwGBitMask, PF.dwBBitMask);
		MessageBox(m_hWnd, szTemp, "Initialization Error", MB_OK);
		exit(-1);
	}

	// �ý��� �޸𸮿� ���� ���� ����
	m_lpDDSExtra = this->SurfaceCreate(m_rcScr.right - m_rcScr.left, m_rcScr.bottom - m_rcScr.top, FALSE, RGB(255,0,255));

	// �÷� ���̺� �� ���
	if(m_nPF = PF_565)
	{
		for(int i = 0; i < 32; i++)
		{
			m_wRTbls[i] = i << 11;
			m_wGTbls[i] = (i*2) << 5;
			m_wBTbls[i] = i;
		}
	}
	else
	{
		for(int i = 0; i < 32; i++)
		{
			m_wRTbls[i] = i << 10;
			m_wGTbls[i] = i << 5;
			m_wBTbls[i] = i;
		}
	}
}

LPDIRECTDRAWSURFACE CDDEngine::SurfaceCreate(int nWidth, int nHeight, BOOL bUseVideoMemory, COLORREF ColorKey)
{
	if(m_lpDD == NULL) return NULL;

	DDSURFACEDESC ddsd;
	LPDIRECTDRAWSURFACE lpdds = NULL;
	MAKE_ZERO(ddsd);
	ddsd.dwSize = sizeof(ddsd);
	ddsd.dwFlags = DDSD_CAPS | DDSD_HEIGHT |DDSD_WIDTH;
	ddsd.dwWidth = nWidth;
	ddsd.dwHeight = nHeight;

    if(bUseVideoMemory == TRUE) // ���� �޸𸮿� ������ ����...
	{
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_VIDEOMEMORY;
 
		if (m_lpDD->CreateSurface(&ddsd, &lpdds, NULL) != DD_OK) // ���� �޸� ����.. �ý��� �޸𸮿� ����
		{
			ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
			if (m_lpDD->CreateSurface(&ddsd, &lpdds, NULL) != DD_OK) return NULL;
		}
	}
	else
	{
		ddsd.ddsCaps.dwCaps = DDSCAPS_OFFSCREENPLAIN | DDSCAPS_SYSTEMMEMORY;
		m_lpDD->CreateSurface(&ddsd, &lpdds, NULL);
	}

	// �÷�Ű ����
	this->SurfaceColorKeySet(lpdds, ColorKey);

	// ���ǽ� ����
	return lpdds;
}

void CDDEngine::SurfaceColorKeySet(LPDIRECTDRAWSURFACE lpdds, COLORREF ColorKey)
{
	if(lpdds == NULL) return;

	// �÷�Ű ����
	DDCOLORKEY ddck;
	DWORD CK = RGB16(ColorKey);
	ddck.dwColorSpaceHighValue = CK;
	ddck.dwColorSpaceLowValue = CK;
	lpdds->SetColorKey(DDCKEY_SRCBLT , &ddck);
}

// RenderType : RENDER_NORMAL, RENDER_TRANS, RENDER_ALPHA_ADD, RENDER_ALPHA_SOFT, RENDER_SHADOW
// nAlpha - 0 ~ 32
void CDDEngine::BltNormal(LPDIRECTDRAWSURFACE lpDDSSrc,
						  int x,
						  int y,
						  const RECT *prcSrc,
						  BOOL bUseColorKey,
						  int nRenderType,
						  int nAlpha,
						  COLORREF crColor,
						  LPDIRECTDRAWSURFACE lpDDSDest)
{
	if(lpDDSSrc == NULL) return;

	RECT rcDest;
	if(lpDDSDest == NULL) { lpDDSDest = m_lpDDSBB; rcDest = m_rcScr; }  // ����ǽ��� ���̸� ����۸� ������� �Ѵ�.
	else this->SurfaceGetSize(lpDDSDest, &rcDest);
	if(x >= rcDest.right) return;
	if(y >= rcDest.bottom) return;
	
	RECT rcSrc;
	if(prcSrc == NULL) this->SurfaceGetSize(lpDDSSrc, &rcSrc); // ���� �����Ͱ� ���̸� ��ü ������ ���Ѵ�.
	else rcSrc = *prcSrc;
	if(x < 0) { rcSrc.left -= x; x = 0; }
	if(y < 0) { rcSrc.top -= y; y = 0; }
	if((rcSrc.right - rcSrc.left) + x > rcDest.right)
	{
		rcSrc.right = rcSrc.left + rcDest.right - x;
	}
	if((rcSrc.bottom - rcSrc.top) + y > rcDest.bottom)
	{
		rcSrc.bottom = rcSrc.top + rcDest.bottom - y;
	}

	HRESULT rval;

	DWORD dwFlag = DDBLTFAST_WAIT; // �÷�Ű�� ������ ���ϱ�..
	if(bUseColorKey == TRUE) dwFlag |= DDBLTFAST_SRCCOLORKEY;
	else dwFlag |= DDBLTFAST_NOCOLORKEY;
	
	if(nRenderType == RENDER_NORMAL) 
	{
		rval = lpDDSDest->BltFast(x, y, lpDDSSrc, &rcSrc, dwFlag);
	}
	else
	{
		int width = rcSrc.right - rcSrc.left, height = rcSrc.bottom - rcSrc.top;
		if(width <=0) return;
		this->SurfaceLock(lpDDSDest, &m_ddsdTmp1);
		this->SurfaceLock(lpDDSSrc, &m_ddsdTmp2);
		int pitchDest = m_ddsdTmp1.lPitch/2; // ���� ������ �̱� ���� /2 �� ���ش�.
		int pitchSrc = m_ddsdTmp2.lPitch/2;
		WORD* pDest = (WORD*)m_ddsdTmp1.lpSurface + y*pitchDest + x;
		WORD* pSrc = (WORD*)m_ddsdTmp2.lpSurface + rcSrc.top*pitchSrc + rcSrc.left;

		if(nRenderType == RENDER_TRANS)
		{
			for(int y = 0; y < height; y++, pDest += pitchDest, pSrc += pitchSrc)
				this->PutPixelTrans(pDest, pSrc, width, nAlpha, 32-nAlpha, m_dwRBMask, m_dwGMask);
		}
		else if(nRenderType == RENDER_ALPHA_SOFT)
		{
			for(int y = 0; y < height; y++, pDest += pitchDest, pSrc += pitchSrc)
				this->PutPixelAlphaSoft(pDest, pSrc, width, m_dwRMask, m_dwGMask, m_dwBMask);
		}
		else if(nRenderType == RENDER_ALPHA_ADD)
		{
			for(int y = 0; y < height; y++, pDest += pitchDest, pSrc += pitchSrc)
				this->PutPixelAlphaAdd(pDest, pSrc, width, m_dwRMask, m_dwGMask, m_dwBMask);
		}
		else if(nRenderType == RENDER_SHADOW)
		{
			for(int y = 0; y < height; y++, pDest += pitchDest, pSrc += pitchSrc)
				this->PutPixelShadow(pDest, pSrc, width, m_dwRBMask, m_dwGMask);
		}
		else if(nRenderType == RENDER_DARK)
		{
			for(int y = 0; y < height; y++, pDest += pitchDest, pSrc += pitchSrc)
				this->PutPixelDark(pDest, pSrc, width, nAlpha, m_dwRBMask, m_dwGMask);
		}
		else if(nRenderType == RENDER_COLOR)
		{
			for(int y = 0; y < height; y++, pDest += pitchDest, pSrc += pitchSrc)
				this->PutPixelColor(pDest, pSrc, width, nAlpha, crColor, m_dwRBMask, m_dwGMask);
		}

		this->SurfaceUnlock(lpDDSSrc);
		this->SurfaceUnlock(lpDDSDest);
	}
}

// ����۸� �� �ϰ�... ���� �ּҿ� ��ġ�� ���...
void CDDEngine::BackBufferLock()
{
	HRESULT rval = this->SurfaceLock(m_lpDDSBB, &m_ddsdTmp1, NULL);
	if(rval == DD_OK)
	{
		m_pwBB = (WORD*)m_ddsdTmp1.lpSurface;
		m_nPitchBB = m_ddsdTmp1.lPitch/2;
		m_bBBLocked = TRUE; // ���� ����ۿ� ���� �ɷ� �ִ���..
	}
}

// ����۸� ��� �ϰ�.... ���� �ּҿ� ��ġ�� ���� �ɷ� ���...
void CDDEngine::BackBufferUnlock()
{
	HRESULT rval = this->SurfaceUnlock(m_lpDDSBB, NULL);
	m_pwBB = NULL;
	m_nPitchBB = 0;
	m_bBBLocked = FALSE; // ���� ����ۿ� ���� �Ȱɷ� ����.
}

LPDIRECTDRAWSURFACE CDDEngine::SurfaceCreateWithBMP(const char *szFileName, BOOL bUseVideoMemory, COLORREF crCK)
{
	HANDLE hFile;
	DWORD dwCount;
	hFile = CreateFile( szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{ 
		OutputDebugString("���ǽ� ���� ���� : ��Ʈ�� ���� ���� ����");
		OutputDebugString(szFileName);
		OutputDebugString("\n");
		return NULL;
	}
	char szID[4];
	ReadFile(hFile, szID, 4, &dwCount, NULL); // ID �б�
	CloseHandle(hFile);

	if(szID[0] == 'B' && szID[1] == 'M' && szID[2] == 'P' && szID[3] == 16)
		return this->SurfaceCreateWith16BMP(szFileName, bUseVideoMemory, crCK);
	else if(szID[0] == 'B' && szID[1] == 'M')
		return this->SurfaceCreateWithGenericBMP(szFileName, bUseVideoMemory, crCK);
	else
	{
		OutputDebugString("��Ʈ�� ���� ���� ���� : �߸��� ���� ��� - ");
		OutputDebugString(szFileName);
		OutputDebugString("\n");
		return NULL;
	}
}

LPDIRECTDRAWSURFACE CDDEngine::SurfaceCreateWithGenericBMP(const char *szFileName, BOOL bUseVideoMemory, COLORREF crCK)
{
	if(m_lpDD == NULL) return NULL;

	HBITMAP					hbm;
	BITMAP					bm;
	hbm = (HBITMAP)LoadImage(GetModuleHandle(NULL), szFileName, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if (hbm == NULL)
	hbm = (HBITMAP)LoadImage(NULL, szFileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
	if (hbm == NULL) return NULL;
	GetObject(hbm, sizeof(bm), &bm);      // get size of bitmap

	// ���ǽ��� �����.
	LPDIRECTDRAWSURFACE lpDDS = NULL;
	lpDDS = this->SurfaceCreate(bm.bmWidth, bm.bmHeight, bUseVideoMemory, crCK);

	if (lpDDS == NULL) return NULL;

	HDC                 hdcImage;
	HDC                 hdc;
	HRESULT             hr;

	hdcImage = CreateCompatibleDC(NULL);
	SelectObject(hdcImage, hbm);
	hr = lpDDS->GetDC(&hdc);
	StretchBlt(hdc, 0, 0, bm.bmWidth, bm.bmHeight, hdcImage, 0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);
	lpDDS->ReleaseDC(hdc);
	DeleteDC(hdcImage);
	DeleteObject(hbm);

	return lpDDS;
}

LPDIRECTDRAWSURFACE CDDEngine::SurfaceCreateWith16BMP(const char *szFileName, BOOL bUseVideoMemory, COLORREF crCK)
{
	CDib16 dib;
	if(dib.Load(szFileName) == FALSE) return NULL;

	int width = dib.GetWidth();
	int height = dib.GetHeight();

	if(width <= 0 || height <= 0) return NULL;

	// ���ǽ��� �����.
	LPDIRECTDRAWSURFACE lpDDS = this->SurfaceCreate(width, height, bUseVideoMemory, crCK);

	this->SurfaceLock(lpDDS, &m_ddsdTmp1);
	WORD* pDest = (WORD*)m_ddsdTmp1.lpSurface;
	int nDestPitch = m_ddsdTmp1.lPitch/2;
	WORD* pSrc = dib.Lock();
	for(int y = 0; y < height; y++)
	{
		if(m_nPF == PF_565) memcpy(pDest + y * nDestPitch, pSrc + y * width, width*2); // ���� �ȼ� ����ŭ ����..
		else Conv565PixelTo555Pixel(pDest + y * nDestPitch, pSrc + y * width, width); // ���� �ȼ� ����ŭ 565 �� 555 �� ��ȯ�Ѵ�..
	}
	dib.Unlock();
	SurfaceUnlock(lpDDS);

	return lpDDS;
}


const char* CDDEngine::PathGetCur(const char* szPath, int nPath) const
{
	if(nPath < 0 || nPath >= 8 || szPath == NULL) return m_szPath;

	static char szTmp[8][256];

	lstrcpy(szTmp[nPath], m_szPath);
	lstrcat(szTmp[nPath], "\\");
	lstrcat(szTmp[nPath], szPath);
	return szTmp[nPath];
}

// ���� ��θ� ����
void CDDEngine::PathSetCur(const char *szSubPath)
{
	static char szTmp[256];

	lstrcpy(szTmp, m_szPath);
	lstrcat(szTmp, "\\");
	lstrcat(szTmp, szSubPath);

	SetCurrentDirectory(szTmp);
}

// �۾� ��� ����
void CDDEngine::PathSetWork(const char *szPath)
{
	lstrcpy(m_szPath, szPath);
}

void CDDEngine::Flip(const RECT* pRCClip)
{
	if(m_bFullScreen) // Ǯ��ũ�� ����̸�..���� �޸𸮿� �Ѹ���. �ӵ������ �ִ�.
	{
		if(pRCClip == NULL) // �׳� ��¥�� �ø�
		{
			// ���� ���� ��ٸ�.. Ƽ� ���� ����.. �׷��� ������..
			//	m_lpDD->WaitForVerticalBlank(DDWAITVB_BLOCKBEGIN, NULL); 
			
			// �����̸Ӹ� ���۰� �ս� �Ǿ����� �˻��� �ս� �Ǿ����� ����..
			HRESULT rval = 0;
			rval = m_lpDDSPri->Flip(NULL, DDFLIP_WAIT);
			if(rval == DDERR_SURFACELOST)
			{
				rval = m_lpDDSPri->Restore(); // ���� �޸� ���� �õ�..
				rval = m_lpDDSPri->Flip(NULL, DDFLIP_WAIT);
			}
		}
		else // �Ϻκи� �ø�
		{
			RECT rcDest;
			RECT rcSrc;

			int width = pRCClip->right - pRCClip->left;
			int height = pRCClip->bottom - pRCClip->top;
			rcSrc.left = pRCClip->left;
			rcSrc.top = pRCClip->top;
			rcSrc.right = rcSrc.left + width;
			rcSrc.bottom = rcSrc.top + height;

			rcDest.left = pRCClip->left;
			rcDest.top = pRCClip->top;
			rcDest.right = rcDest.left + width;
			rcDest.bottom = rcDest.top + height;
			
			m_lpDDSPri->Blt(&rcDest, m_lpDDSBB, &rcSrc, DDBLT_WAIT, NULL);
		}
	} 
	else // �������ۿ��� ������ �̹��� ����
	{
		RECT rcDest;
		RECT rcSrc;

		m_lpDDClipper->GetHWnd(&m_hWnd);
		GetClientRect(m_hWnd, &rcSrc);
		POINT pt = {rcSrc.left, rcSrc.top};
		ClientToScreen(m_hWnd, &pt);
		
		if(pRCClip == NULL) // �׳� ��¥�� �ø�
		{
			int width = rcSrc.right - rcSrc.left;
			int height = rcSrc.bottom - rcSrc.top;
			rcDest.left = pt.x;
			rcDest.top = pt.y;
			rcDest.right = pt.x + width;
			rcDest.bottom = pt.y + height;
		}
		else // �Ϻκи� �ø�
		{
			int width = pRCClip->right - pRCClip->left;
			int height = pRCClip->bottom - pRCClip->top;
			rcSrc.left = pRCClip->left;
			rcSrc.top = pRCClip->top;
			rcSrc.right = rcSrc.left + width;
			rcSrc.bottom = rcSrc.top + height;

			rcDest.left = pt.x + pRCClip->left;
			rcDest.top = pt.y + pRCClip->top;
			rcDest.right = rcDest.left + width;
			rcDest.bottom = rcDest.top + height;
		}
		HRESULT rval;
//		rval = m_lpDDSPri->BltFast(rcDest.left, rcDest.top, m_lpDDSBB, &rcSrc, DDBLTFAST_WAIT);
		rval = m_lpDDSPri->Blt(&rcDest, m_lpDDSBB, &rcSrc, DDBLT_WAIT, NULL);
//		rval = m_lpDDSExtra->Blt(&rcSrc, m_lpDDSBB, &rcSrc, DDBLT_WAIT, NULL);
//		rval = m_lpDDSExtra->BltFast(0,0, m_lpDDSBB, &rcSrc, DDBLTFAST_WAIT);
	}

	// ������ ����Ʈ ���..
	static DWORD dwTick = GetTickCount(), dwTickPrev = GetTickCount();
	static int nFlipCount = 0, nTTT = 0;

	nFlipCount++;
	dwTick = GetTickCount();
	if(dwTick > dwTickPrev + 1000)
	{
		m_nFrmRate = nFlipCount;
		nFlipCount = 0;
		static char szTmp[256];
		wsprintf(szTmp, "Frame : %d ", m_nFrmRate);
		OutputDebugString(szTmp);
		nTTT++;
		if(nTTT%10 == 0) OutputDebugString("\n"); // �ٹٲ�

		dwTickPrev = dwTick;
	}
}

// ���ǽ� �ּҰ� ���̸� ����۸� ������� �Ѵ�..
void CDDEngine::SurfaceFillRect(LPDIRECTDRAWSURFACE lpDDS, const RECT* pRC, COLORREF crFill, int nAlpha)
{
	if(nAlpha <= 0 || nAlpha > 32) return;
	if(lpDDS == NULL) lpDDS = m_lpDDSBB;

	if(nAlpha == 32)
	{
		// ����۸� ���������� ä��
		DDBLTFX ddbltfx;
		MAKE_ZERO(ddbltfx);
		ddbltfx.dwSize = sizeof(DDBLTFX);
		ddbltfx.dwFillColor = this->RGB16(crFill);
		if(pRC)
		{
			RECT rcS;
			RECT rcDest = *pRC;
			this->SurfaceGetSize(lpDDS, &rcS);
			if(rcDest.left < 0) rcDest.left = 0;
			if(rcDest.top < 0) rcDest.top = 0;
			if(rcDest.right > rcS.right) rcDest.right = rcS.right;
			if(rcDest.bottom > rcS.bottom) rcDest.bottom = rcS.bottom;
			lpDDS->Blt(&rcDest, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
		}
		else
		{
			lpDDS->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
		}
	}
	else
	{
		RECT rcSurface;
		RECT rcDest;
		this->SurfaceGetSize(lpDDS, &rcSurface);
		if(pRC)
		{
			IntersectRect(&rcDest, pRC, &rcSurface);
		}
		else 
		{
			rcDest = rcSurface;
		}
		if(rcDest.bottom <= rcDest.top) return;
		if(rcDest.left%2) rcDest.left += 1; // ¦�� ������ ���߾� �ش�.
		if(rcDest.right%2) rcDest.right -= 1;
		if(rcDest.right <= rcDest.left) return;

//		BOOL bNeedBltToBB = FALSE;
//		if(lpDDS == m_lpDDSBB)
//		{
//			lpDDS = m_lpDDSExtra; // ������۷�..
//			this->BltNormal(m_lpDDSBB, rcDest.left, rcDest.top, &rcDest, FALSE, RENDER_NORMAL, 32, lpDDS);
//			bNeedBltToBB = TRUE;
//		}

		WORD wColor = this->RGB16(crFill);
		DWORD dwMask1, dwMask2;
		if(m_nPF == PF_555)
		{
			dwMask1 = 0x7c1f03e0;
			dwMask2 = 0x03e07c1f;
		}
		else if(m_nPF == PF_565)
		{
			dwMask1 = 0xf81f07e0;
			dwMask2 = 0x07e0f81f;
		}

		DWORD dwColor = ((wColor<<16)|wColor);
		dwColor = ((((dwColor&dwMask1)>>5)*nAlpha)&dwMask1) | ((((dwColor&dwMask2)*nAlpha)>>5)&dwMask2);

		this->SurfaceLock(lpDDS, &m_ddsdTmp1);
		DWORD* pdwDestOrg = (DWORD*)m_ddsdTmp1.lpSurface;
		int nPitch = m_ddsdTmp1.lPitch/4;

		int width = (rcDest.right - rcDest.left)/2;
		for(int y = rcDest.top; y < rcDest.bottom; y++)
		{
			DWORD* pdwDest = pdwDestOrg + y*nPitch + rcDest.left/2;
			__asm
			{
				mov esi, pdwDest; // ����� �ּ� ���

				mov ecx, width;
				COPY_LOOP_X:

				mov eax, [esi]; // BackBuffer - DWORD ����..
				and eax, dwMask1;
				shr eax, 5;
				mul nAlpha;
				and eax, dwMask1;
				mov ebx, eax;

				mov eax, [esi]; // BackBuffer - DWORD ����..
				and eax, dwMask2;
				mul nAlpha;
				shr eax, 5;
				and eax, dwMask2;
				
				or ebx, eax;
				add ebx, dwColor;
				mov [esi], ebx;

				add esi, 4; // DWORD ����

				dec ecx;
				jnz COPY_LOOP_X;
			}
		}
		this->SurfaceUnlock(lpDDS);

//		if(bNeedBltToBB == TRUE)
//		{
//			lpDDS = m_lpDDSExtra; // ������۷�..
//			this->BltNormal(lpDDS, rcDest.left, rcDest.top, &rcDest, FALSE, RENDER_NORMAL, 32, m_lpDDSBB);
//		}
	}
}

// ���ǽ� ����� ��Ʈ������ ������..
void CDDEngine::SurfaceGetSize(LPDIRECTDRAWSURFACE lpDDS, RECT* pRC)
{
	if(lpDDS == NULL)
	{
		SetRect(pRC, 0, 0, 0, 0);
		return;
	}

	m_ddsdTmp1.dwSize = sizeof(DDSURFACEDESC);
	m_ddsdTmp1.dwFlags = DDSD_WIDTH | DDSD_HEIGHT;
	lpDDS->GetSurfaceDesc(&m_ddsdTmp1);
	SetRect(pRC, 0, 0, m_ddsdTmp1.dwWidth, m_ddsdTmp1.dwHeight);
}

void CDDEngine::DrawLine(LPDIRECTDRAWSURFACE lpDDS, int sx, int sy, int ex, int ey, COLORREF crColor)
{
	if(lpDDS == NULL) lpDDS = m_lpDDSBB;

	HDC hdc;
	lpDDS->GetDC(&hdc);
	if(hdc == NULL) return;

	HPEN hPen = CreatePen(PS_SOLID, 1, crColor);
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);

	MoveToEx(hdc, sx, sy, NULL);
	LineTo(hdc, ex, ey);
	
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);

	lpDDS->ReleaseDC(hdc);
}

void CDDEngine::DrawBox(LPDIRECTDRAWSURFACE lpDDS, const RECT *pRC, COLORREF crColor)
{
	if(lpDDS == NULL) lpDDS = m_lpDDSBB;
	if(pRC == NULL) return;

	HDC hdc;
	lpDDS->GetDC(&hdc);
	if(hdc == NULL) return;

	HPEN hPen = CreatePen(PS_SOLID, 1, crColor);
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	
	Rectangle(hdc, pRC->left, pRC->top, pRC->right, pRC->bottom);
	
	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	
	lpDDS->ReleaseDC(hdc);
}

void CDDEngine::DrawRhombus(LPDIRECTDRAWSURFACE lpDDS, int x, int y, COLORREF crColor)
{
	if(lpDDS == NULL) lpDDS = m_lpDDSBB;

	HDC hdc;
	POINT p[5];
	lpDDS->GetDC(&hdc);
	if(hdc == NULL) return;

	HPEN hPen = CreatePen(PS_SOLID, 1, crColor);
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));

	p[0].x = x-32;	p[0].y = y;
	p[1].x = x;		p[1].y = y-16;
	p[2].x = x+32;	p[2].y = y;
	p[3].x = x;		p[3].y = y+16;
	p[4].x = x-32;	p[4].y = y;
	Polygon(hdc, p, 5);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	
	lpDDS->ReleaseDC(hdc);
}

void CDDEngine::DrawPolygon(LPDIRECTDRAWSURFACE lpDDS, POINT *point, int count, COLORREF crColor)
{
	if(lpDDS == NULL) lpDDS = m_lpDDSBB;

	HDC hdc;
	lpDDS->GetDC(&hdc);
	if(hdc == NULL) return;

	HPEN hPen = CreatePen(PS_SOLID, 1, crColor);
	HPEN hPenOld = (HPEN)SelectObject(hdc, hPen);
	SelectObject(hdc, GetStockObject(NULL_BRUSH));

	Polygon(hdc, point, count);

	SelectObject(hdc, hPenOld);
	DeleteObject(hPen);
	
	lpDDS->ReleaseDC(hdc);
}

void CDDEngine::TextOut(LPDIRECTDRAWSURFACE lpDDS, int x, int y, const char *szText, COLORREF crText, UINT align)
{
	if(lpDDS == NULL) lpDDS = m_lpDDSBB;

	HDC hdc;
	lpDDS->GetDC(&hdc);
	if(hdc == NULL) return;

	UINT old_align;
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, crText);
	old_align = SetTextAlign(hdc, align);
	::TextOut(hdc, x, y, szText, lstrlen(szText));
	SetTextAlign(hdc, old_align);

	lpDDS->ReleaseDC(hdc);
}


COLORREF CDDEngine::SurfaceColorKeyGet(LPDIRECTDRAWSURFACE lpDDS)
{
	if(lpDDS == NULL) return 0;
	DDCOLORKEY DDCK;
	lpDDS->GetColorKey(DDCKEY_SRCBLT, &DDCK);
	return this->RGB24(WORD(DDCK.dwColorSpaceLowValue));
}

void CDDEngine::Blt(LPDIRECTDRAWSURFACE lpDDSDest, LPDIRECTDRAWSURFACE lpDDSSrc, RECT *pRCDest, RECT *pRCSrc, BOOL bUseColorKey)
{
	if(lpDDSSrc == NULL) return;
	if(lpDDSDest == NULL) lpDDSDest = m_lpDDSBB; // ����ǽ��� ���̸� ����۸� ������� �Ѵ�.

	lpDDSDest->Blt(pRCDest, lpDDSSrc, pRCSrc, DDBLT_KEYSRC | DDBLT_WAIT, NULL);
}
