// DDEngineTool.cpp: implementation of the CDDEngineTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "igt4.h"
#include "DDEngineTool4.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDDEngineTool4::CDDEngineTool4()
{

}

CDDEngineTool4::~CDDEngineTool4()
{

}

POINT CDDEngineTool4::FindCenterAuto(LPDIRECTDRAWSURFACE lpDDS, CRect rc, COLORREF CColor)
{
	CPoint pt(rc.left, rc.top);

	if(lpDDS == NULL) return pt;
	
	// �������� �ڵ����� ã�´�.
	WORD wCColor = this->RGB16(CColor);

	if(this->SurfaceLock(lpDDS, &m_ddsdTmp1) != DD_OK) return pt;
	
	WORD* pSrc = (WORD*)m_ddsdTmp1.lpSurface;
	int pitch = m_ddsdTmp1.lPitch / 2;

	WORD Pixel1, Pixel2, Pixel3, Pixel4, Pixel5;
	int x, y;
	for(x = rc.left+1; x < rc.right-1; x++)
	{
		for(y = rc.top+1; y < rc.bottom-1; y++)
		{
			Pixel1 = *(pSrc + (y-1)*pitch + x);
			Pixel2 = *(pSrc + y*pitch + x-1);
			Pixel3 = *(pSrc + y*pitch + x);
			Pixel4 = *(pSrc + y*pitch + x+1);
			Pixel5 = *(pSrc + (y+1)*pitch + x);
			if(	(Pixel1 == wCColor) && 
				(Pixel2 == wCColor) && 
				(Pixel3 == wCColor) && 
				(Pixel4 == wCColor) && 
				(Pixel5 == wCColor) )
			{
				pt.x = x;
				pt.y = y;
				goto SUCCESS;
			}
		}
	}

SUCCESS:
	this->SurfaceUnlock(lpDDS);
	return pt;
}

RECT CDDEngineTool4::FindRegionManual(LPDIRECTDRAWSURFACE lpDDS, CRect rc, COLORREF TColor)
{
	CRect rc1 = rc, rc2;

	this->SurfaceGetSize(lpDDS, &rc2);
	CRect rcClip;
	rc.IntersectRect(rc1, rc2); // Ŭ���� ó��..

	WORD wTColor = this->RGB16(TColor);
	WORD wPixel;

	if(this->SurfaceLock(lpDDS, &m_ddsdTmp1) != DD_OK) return rc;
	WORD* pSrc = (WORD*) m_ddsdTmp1.lpSurface;
	int pitch = m_ddsdTmp1.lPitch / 2;

	int x, y;

	// ������ �ٿ��ش�.
	for(x = rc.left; x < rc.right; x++)
	{
		for(y = rc.top; y < rc.bottom; y++)
		{
			wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
			if(wPixel != wTColor) break;
		}
		if(wPixel != wTColor) break;
	}
	rc.left = x;

	// ������ �ٿ��ش�.
	for(y = rc.top; y < rc.bottom; y++)
	{
		for(x = rc.left; x < rc.right; x++)
		{
			wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
			if(wPixel != wTColor) break;
		}
		if(wPixel != wTColor) break;
	}
	rc.top = y;

	// �������� �ٿ��ش�.
	for(x = rc.right-1; x > rc.left; x--)
	{
		for(y = rc.bottom-1; y > rc.top; y--)
		{
			wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
			if(wPixel != wTColor) break;
		}
		if(wPixel != wTColor) break;
	}
	rc.right = x+1;

	// �Ʒ����� �ٿ��ش�.
	for(y = rc.bottom-1; y > rc.top; y--)
	{
		for(x = rc.right-1; x > rc.left; x--)
		{
			wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
			if(wPixel != wTColor) break;
		}
		if(wPixel != wTColor) break;
	}
	rc.bottom = y+1;

	this->SurfaceUnlock(lpDDS);

	return rc;
}

RECT CDDEngineTool4::FindRegionAuto(LPDIRECTDRAWSURFACE lpDDS, CPoint pt, COLORREF TColor)
{
	CRect rc(0,0,0,0);

	WORD wTColor = this->RGB16(TColor);
	WORD wPixel;

	CRect rcSrc;
	this->SurfaceGetSize(lpDDS, &rcSrc);

	this->SurfaceLock(lpDDS, &m_ddsdTmp1);
	WORD* pSrc = (WORD*) m_ddsdTmp1.lpSurface;
	int pitch = m_ddsdTmp1.lPitch / 2;

	int x = pt.x;
	int y = pt.y;

	x = pt.x;
	y = pt.y;
	while(1)
	{
		wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
		if(wPixel == wTColor)
		{
			rc.left = x+1;
			break;
		}
		if(x <= 0) break;
		x--;
	}

	x = pt.x;
	y = pt.y;
	while(1)
	{
		wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
		if(wPixel == wTColor)
		{
			rc.top = y+1;
			break;
		}
		if(y <= 0)
		{
			rc.top = 0;
			break;
		}
		y--;
	}

	x = pt.x;
	y = pt.y;
	while(1)
	{
		wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
		if(wPixel == wTColor)
		{
			rc.right = x;
			break;
		}
		if(x >= rcSrc.right){rc.right = rcSrc.right; break;}
		x++;
	}

	x = pt.x;
	y = pt.y;
	while(1)
	{
		wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
		if(wPixel == wTColor)
		{
			rc.bottom = y;
			break;
		}
		if(y >= rcSrc.bottom){rc.bottom = rcSrc.bottom; break;}
		y++;
	}

	////////////////////////////////////////////////////////
	// ���� ��� ����
	// �������� �þ..
	x = rc.left;
	while(1)
	{
		if(x < 0) { rc.left = 0; break;}
		BOOL bT = TRUE;
		for(int y = rc.top; y < rc.bottom; y++)
		{
			wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
			if(wPixel != wTColor)
			{
				bT = FALSE;
			}
		}
		if(bT)
		{
			rc.left = x+1;
			break;
		}
		x--;
	}

	// �������� �þ..
	y = rc.top;
	while(1)
	{
		if(y < 0) {rc.top = 0; break;}
		BOOL bT = TRUE;
		for(int x = rc.left; x < rc.right; x++)
		{
			wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
			if(wPixel != wTColor)
			{
				bT = FALSE;
			}
		}
		if(bT)
		{
			rc.top = y+1;
			break;
		}
		y--;
	}

	// ���������� �þ..
	x = rc.right;
	while(1)
	{
		if(x > rcSrc.right) {rc.right = rcSrc.right; break;}
		BOOL bT = TRUE;
		for(int y = rc.top; y < rc.bottom; y++)
		{
			wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
			if(wPixel != wTColor)
			{
				bT = FALSE;
			}
		}
		if(bT)
		{
			rc.right = x;
			break;
		}
		x++;
	}

	// ������ �þ..
	y = rc.bottom;
	while(1)
	{
		if(y > rcSrc.bottom) {rc.bottom = rcSrc.bottom; break;}
		BOOL bT = TRUE;
		for(int x = rc.left; x < rc.right; x++)
		{
			wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
			if(wPixel != wTColor)
			{
				bT = FALSE;
			}
		}
		if(bT)
		{
			rc.bottom = y;
			break;
		}
		y++;
	}
	// ���� ��� ����
	////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////
	// �ѹ� �� ���
	// �������� �þ..
	x = rc.left;
	while(1)
	{
		if(x < 0) { rc.left = 0; break;}
		BOOL bT = TRUE;
		for(int y = rc.top; y < rc.bottom; y++)
		{
			wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
			if(wPixel != wTColor)
			{
				bT = FALSE;
			}
		}
		if(bT)
		{
			rc.left = x+1;
			break;
		}
		x--;
	}

	// �������� �þ..
	y = rc.top;
	while(1)
	{
		if(y < 0) {rc.top = 0; break;}
		BOOL bT = TRUE;
		for(int x = rc.left; x < rc.right; x++)
		{
			wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
			if(wPixel != wTColor)
			{
				bT = FALSE;
			}
		}
		if(bT)
		{
			rc.top = y+1;
			break;
		}
		y--;
	}

	// ���������� �þ..
	x = rc.right;
	while(1)
	{
		if(x > rcSrc.right) {rc.right = rcSrc.right; break;}
		BOOL bT = TRUE;
		for(int y = rc.top; y < rc.bottom; y++)
		{
			wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
			if(wPixel != wTColor)
			{
				bT = FALSE;
			}
		}
		if(bT)
		{
			rc.right = x;
			break;
		}
		x++;
	}

	// ������ �þ..
	y = rc.bottom;
	while(1)
	{
		if(y > rcSrc.bottom) {rc.bottom = rcSrc.bottom; break;}
		BOOL bT = TRUE;
		for(int x = rc.left; x < rc.right; x++)
		{
			wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
			if(wPixel != wTColor)
			{
				bT = FALSE;
			}
		}
		if(bT)
		{
			rc.bottom = y;
			break;
		}
		y++;
	}
	// �ѹ� �� ���
	////////////////////////////////////////////////////////
	
	this->SurfaceUnlock(lpDDS);
	return rc;
}

// ��������Ʈ �簢 ������ ���� ��� �ؾ� �ȴ�.. �ݵ��!!!
BOOL CDDEngineTool4::EncodeToLSPData(LPDIRECTDRAWSURFACE lpDDS, COLORREF TColor, RECT rcRgn, POINT ptCenter, _SPR_LSP* pSpr)
{
	if(pSpr == NULL) return FALSE;
	
	DELETE_ARRAY_SAFE(pSpr->pwV);
	MAKE_ZERO(*pSpr);

	if(lpDDS == NULL) return FALSE;

	this->FindRegionManual(lpDDS, rcRgn, TColor); // ������ ���δ�.
	int width = rcRgn.right - rcRgn.left;
	int height = rcRgn.bottom - rcRgn.top;
	if(width <= 1 || height <= 1) return TRUE; // ������ ���°� ��¿�� ����....

	this->SurfaceLock(lpDDS, &m_ddsdTmp1);
	
	WORD* pSrc = (WORD*)m_ddsdTmp1.lpSurface;
	int pitch = m_ddsdTmp1.lPitch / 2;

	WORD wPixel;
	WORD wTColor = this->RGB16(TColor);

	WORD* pwBuff = new WORD[width*height*4]; // �ϴ� �Ҵ�.
	memset(pwBuff, 0, width*height*4*2);

	// ������ ���� ����
	int x, y;
	int nLine = 0;
	int nBuffCount = 0;
	WORD* pwTmpBuff = pwBuff; // ������ ù �κ��� ���μ��� ����..

	for(y = rcRgn.top; y < rcRgn.bottom; y++)
	{
		int nNode = 0;	// ����� ����.. �⺻�����δ� �ϳ� ���..
		BOOL IsTherePixel = FALSE; // �ȼ��� �ϳ��� ������ ��带 �ϳ� ���δ�.

		_LSP_ENCODE_BUFF* EncodeBuff;
		_LSP_ENCODE_BUFF* pStart;
		
		int ing = -1; // ó�� ����.. 0 �϶��� ����� ó����.. 1�϶��� �ȼ� ó����..
		for(x = rcRgn.left; x < rcRgn.right; x++)
		{
			if (ing == -1) // �����Ҷ� ���� ��� �ϳ��� �Ҵ��Ѵ�.. �׸��� ��尡 �ϳ��� �� ���ٴ� �� �˷��ش�.
			{
				EncodeBuff = new _LSP_ENCODE_BUFF;
				memset(EncodeBuff, 0, sizeof(_LSP_ENCODE_BUFF));
				pStart = EncodeBuff;
				nNode++;
			}
			
			wPixel = GET_ARRAY_VALUE(pSrc, pitch, x, y);
			// ������̸�...
			if(wPixel == wTColor)
			{
				if(ing == 1) // ���ο� ���� �ȼ��϶�..
				{
					// ���� ��� �ϳ��� �Ҵ��Ѵ�.. �׸��� ��尡 �ϳ��� �� ���ٴ� �� �˷��ش�.
					_LSP_ENCODE_BUFF* tmp = new _LSP_ENCODE_BUFF;
					memset(tmp, 0, sizeof(_LSP_ENCODE_BUFF));
					tmp->Prev = EncodeBuff;
					EncodeBuff->Next = tmp;
					tmp->Next = NULL;
					EncodeBuff = tmp;
					IsTherePixel = FALSE; // ��ȿ �ȼ� �÷��� ��������.
					nNode++;
				}
				// 0 �� ���� ����.
				EncodeBuff->QtZero++;
				ing = 0;
			}
			else // ������� �ƴϸ�...
			{
				EncodeBuff->Pixel[EncodeBuff->QtPixel] = wPixel;
				EncodeBuff->QtPixel++;
				ing = 1;
				IsTherePixel = TRUE; //��ȿ �ȼ��� �ִ�..
			}
		} // end of for x
		
		if(IsTherePixel == FALSE) nNode--; // ������ ��忡 �ȼ��� �ϳ��� ������ ��带 �ϳ� �ٿ��ش�.
		*pwTmpBuff = nNode; pwTmpBuff++; nBuffCount+=2; // ���� ���.
		if(nNode == 0) // ��尡 0 �̸� ���۸� ����..
		{
			delete EncodeBuff; EncodeBuff = NULL;
		}
		else // ������ 0 �̻��̸�..
		{
			int n=0; // ������ ��..
			while (pStart != NULL) // ����Ʈ�� ��ȸ �ϸ鼭 ���ۿ� ����ϰ� �ӽ� ��� �޸� ����..
			{
				if(n < nNode)
				{
					*pwTmpBuff = pStart->QtZero; pwTmpBuff++; nBuffCount+=2;
					*pwTmpBuff = pStart->QtPixel; pwTmpBuff++;  nBuffCount+=2;
					memcpy(pwTmpBuff, pStart->Pixel, pStart->QtPixel*2); pwTmpBuff += pStart->QtPixel; nBuffCount+=pStart->QtPixel*2;
					n++;
				}
				_LSP_ENCODE_BUFF* tmp = pStart->Next;
				delete pStart; pStart = tmp;
			}
		}
		nLine++; // ���μ� ����
	} // end of for y
	this->SurfaceUnlock(lpDDS);

	pSpr->nLine = nLine; // ���μ� ���
	pSpr->nDataSize = nBuffCount; // ������ ����Ʈ�� ���..
	pSpr->pwV = pwBuff; // ����� �ȵȴ�.. �� ����� �ص�..

	pSpr->rcV = rcRgn; // ��������Ʈ�� �簢 ����
	pSpr->rcV.left -= ptCenter.x;
	pSpr->rcV.top -= ptCenter.y;
	pSpr->rcV.right -= ptCenter.x;
	pSpr->rcV.bottom -= ptCenter.y;

	return TRUE;
}

BOOL CDDEngineTool4::Convert16PixelTo8Pixel(WORD *p16Pixels, BYTE* p8Pixels, RGBQUAD* pRGBTbls, int nQt)
{
	if(!p16Pixels || !p8Pixels || !pRGBTbls || nQt <= 0) return FALSE;
	memset(p8Pixels, 0, nQt);

	for(int i = 0; i < nQt; i++)
	{
		WORD wPixel = *p16Pixels; p16Pixels++;
		COLORREF Pixel = this->RGB16(wPixel);
		BYTE R = (BYTE)((Pixel&0x000000ff));
		BYTE G = (BYTE)((Pixel&0x0000ff00) >> 8);
		BYTE B = (BYTE)((Pixel&0x00ff0000) >> 16);
		int index = 0;
		int dif = 0;
		int min = 1024;
		for(int j = 0; j < 255; j++) // ���� ������ ������ ã�´�..
		{
			dif = 0;
			if(pRGBTbls[j].rgbRed > R) dif += pRGBTbls[j].rgbRed - R;
			else if(pRGBTbls[j].rgbRed < R) dif += R - pRGBTbls[j].rgbRed;
			if(pRGBTbls[j].rgbGreen > G) dif += pRGBTbls[j].rgbGreen - G;
			else if(pRGBTbls[j].rgbGreen < G) dif += G - pRGBTbls[j].rgbGreen;
			if(pRGBTbls[j].rgbBlue > B) dif += pRGBTbls[j].rgbBlue - B;
			else if(pRGBTbls[j].rgbBlue < B) dif += B - pRGBTbls[j].rgbBlue;

			if(dif < min)
			{
				min = dif;
				index = j;
			}
		}
		*p8Pixels = index; p8Pixels++;
	}
	return TRUE;
}

BOOL CDDEngineTool4::Convert8PixelTo16Pixel(BYTE* p8Pixels, WORD *p16Pixels, RGBQUAD* pRGBTbls, int nQt)
{
	if(!p16Pixels || !p8Pixels || !pRGBTbls || nQt <= 0) return FALSE;
	memset(p16Pixels, 0, nQt*2);

	WORD wPixel;
	BYTE byIndex;
	for(int i = 0; i < nQt; i++)
	{
		byIndex = *p8Pixels; p8Pixels++;
		wPixel = this->RGB16(pRGBTbls[byIndex].rgbRed, pRGBTbls[byIndex].rgbGreen, pRGBTbls[byIndex].rgbBlue);
		*p16Pixels = wPixel; p16Pixels++;
	}

	return TRUE;
}

BOOL CDDEngineTool4::ConvertSImpleLSPFileToIndexedLSPFile(const char* szSrcFN, const char* szDestFN, const char* szIndexFN)
{
	if(szSrcFN == NULL || szDestFN == NULL || szIndexFN == NULL) return FALSE;

	// �ȷ�Ʈ �ε��� ��Ʈ�� �б�..
	CFile file; if(file.Open(szIndexFN, CFile::modeRead) == FALSE) { MessageBox(NULL, szIndexFN, "���� ���� ����", MB_OK); return FALSE; }
	BITMAPFILEHEADER BMFileHeader; BITMAPINFOHEADER BMInfoHeader;
	file.Read(&BMFileHeader, sizeof(BITMAPFILEHEADER));
	file.Read(&BMInfoHeader, sizeof(BITMAPINFOHEADER));

	// �ε����� �ְ� 8 ��Ʈ ��Ʈ���� �ƴϸ�..
	if(BMInfoHeader.biClrUsed != 256 && BMInfoHeader.biBitCount != 8)
	{
		MessageBox(m_hWnd, "8��Ʈ ��Ʈ���� �ƴմϴ�.", szIndexFN, MB_OK);
		file.Close();
		return FALSE;
	}
	RGBQUAD RGBTbls[256];
	file.Read(RGBTbls, sizeof(RGBQUAD)*256);
	file.Close();


	// �ܼ� ��������Ʈ �б�
	_SPR_HEADER HSpr; MAKE_ZERO(HSpr);
	_SPR_LSP Sprs[MAX_SPR]; MAKE_ZERO(Sprs);
	WORD* pwVs[MAX_SPR]; MAKE_ZERO(pwVs);
	DWORD dwVs[MAX_SPR]; MAKE_ZERO(dwVs);

	file.Open(szSrcFN, CFile::modeRead);
	file.Read(&HSpr, sizeof(_SPR_HEADER)); // ��������Ʈ ��� �б�.
	file.Seek(sizeof(_SPR_TOOL)*HSpr.nQt, CFile::current); // �������� ���̴� �ΰ����� ������.
	file.Read(Sprs, sizeof(_SPR_LSP)*HSpr.nQt); // ��������Ʈ ���� - ���� ���ӿ����� ���̴� ������.

	for(int i = 0; i < HSpr.nQt; i++) 	// ���� ��������Ʈ ������
	{
		file.Read(&dwVs[i], 4); // ĳ���� ���� - Part 1
		if(dwVs[i] > 640000) { MessageBox(NULL, szSrcFN, "���������� ��������Ʈ", MB_OK); exit(-1); }
		if(dwVs[i] > 0)
		{
			pwVs[i] = new WORD[dwVs[i]/2];
			file.Read(pwVs[i], dwVs[i]);
		}
	}
	file.Close();

	
	// 8 ��Ʈ �ε��� ��������Ʈ ����...
	file.Open(szDestFN, CFile::modeWrite | CFile::modeCreate);
	file.Write(&HSpr, sizeof(_SPR_HEADER)); // ��������Ʈ ��� �б�.
	_SPR_TOOL tspr; MAKE_ZERO(tspr);
	for(i = 0; i < HSpr.nQt; i++) file.Write(&tspr, sizeof(_SPR_TOOL)); // �������� ���̴� �ΰ����� ������.
	file.Write(RGBTbls, sizeof(RGBQUAD)*256);	// ��������Ʈ �ȷ�Ʈ ����
	for(i = 0; i < HSpr.nQt; i++) file.Write(&Sprs[i], sizeof(_SPR_LSP)); // ��������Ʈ ���� - ���� ���ӿ����� ���̴� ������.

	/////////////////////////
	// ���� ��������Ʈ ������
	for(i = 0; i < HSpr.nQt; i++)
	{
		file.Write(&dwVs[i], 4);
		if(dwVs[i])
		{
			WORD* pTemp = pwVs[i];
			WORD wLine = *pTemp; pTemp++;
			file.Write(&wLine, 2); // ���� ī��Ʈ
			for(int j = 0; j < wLine; j++)
			{
				WORD wNode = *pTemp; pTemp++;
				file.Write(&wNode, 2); // ��� ī��Ʈ
				for(int k = 0; k < wNode; k++)
				{
					WORD wSkip = *pTemp; pTemp++;
					WORD wPixelCount = *pTemp; pTemp++;
					file.Write(&wSkip, 2); // �ǳʶٴ� �ȼ� ī��Ʈ
					file.Write(&wPixelCount, 2); // ���� �ȼ� ī��Ʈ
					// �ȷ�Ʈ ó��...
					BYTE* p8Pixels = new BYTE[wPixelCount];
					Convert16PixelTo8Pixel(pTemp, p8Pixels, RGBTbls, wPixelCount); pTemp += wPixelCount;
					file.Write(p8Pixels, wPixelCount);
					delete [] p8Pixels; p8Pixels = NULL;
				}
			}
		}
	} // end of for i
	file.Close();

	for(i = 0; i < MAX_SPR; i++)
	{
		if(pwVs[i]) { delete pwVs[i]; pwVs[i] = NULL; }
	}
	return TRUE;
}

BOOL CDDEngineTool4::ConvertIndexedLSPFileToSImpleLSPFile(const char* szSrcFN, const char* szDestFN)
{
	if(szSrcFN == NULL || szDestFN == NULL) return FALSE;

	return TRUE;
}

// ����ũ ���̺� ���� ó��.. ���ǽ�, ����ũ ���̺�..(1-�����, 0 �ȼ�). �ʺ�, ����, 
BOOL CDDEngineTool4::TransactMaskAndAnti(LPDIRECTDRAWSURFACE lpDDS, WORD *pMaskTbl, COLORREF TColor)
{
	if(lpDDS == NULL || pMaskTbl == NULL) return FALSE;

	//����ũ���� ����� �κ��� ��������� ���ٳ���.
	this->SurfaceLock(lpDDS, &m_ddsdTmp2);
	int width = m_ddsdTmp2.dwWidth, height = m_ddsdTmp2.dwHeight;
	WORD* pDest = (WORD*)m_ddsdTmp2.lpSurface;
	int pitch = m_ddsdTmp2.lPitch / 2;
	int x, y;
	WORD wTColor = this->RGB16(TColor);
	for(y = 0; y < height; y++)
	{
		for(x = 0; x < width; x++)
		{
			if(pMaskTbl[y*width+x] == wTColor)
			{
				SET_ARRAY_VALUE(pDest, pitch, x, y, wTColor); 
			}
		}
	}

	// ���ι��� ��Ƽ ó��.. - �ȼ��� ���۵Ǵ� ��쿡�� ����ũ ���̺��� ������ ��ġ�Ѵ�..
	WORD wPrevPixel = 0, wCurPixel = 0, wNextPixel = 0, wPixel = 0;
	for(y = 1; y < height-1; y++)
	{
		for(x = 1; x < width-1; x++)
		{
			wPrevPixel = GET_ARRAY_VALUE(pDest, pitch, x-1, y);
			wCurPixel = GET_ARRAY_VALUE(pDest, pitch, x, y);
			wNextPixel = GET_ARRAY_VALUE(pDest, pitch, x+1, y);
			if(wPrevPixel == wTColor && wCurPixel != wTColor) // ����������� �ȼ�
			{
				SET_ARRAY_VALUE(pDest, pitch, x, y, pMaskTbl[y*width+x]); // ����ũ ���̺��� ������ ��ġ�Ѵ�..
				x += 2;
			}
			if(wCurPixel != wTColor && wNextPixel == wTColor) // �ȼ� ������ ����� �ȼ�
			{
				SET_ARRAY_VALUE(pDest, pitch, x, y, pMaskTbl[y*width+x]); // ����ũ ���̺��� ������ ��ġ�Ѵ�..
				x+=2;
			}
		}
	}

	// ���ι��� ��Ƽ ó��..
	for(x = 1; x < width-1; x++)
	{
		for(y = 1; y < height-1; y++)
		{
			wPrevPixel = GET_ARRAY_VALUE(pDest, pitch, x, y-1);
			wCurPixel = GET_ARRAY_VALUE(pDest, pitch, x, y);
			wNextPixel = GET_ARRAY_VALUE(pDest, pitch, x, y+1);
			if(wPrevPixel == wTColor && wCurPixel != wTColor) // ����������� �ȼ�
			{
				SET_ARRAY_VALUE(pDest, pitch, x, y, pMaskTbl[y*width+x]); // ����ũ ���̺��� ������ ��ġ�Ѵ�..
				y+=2;
			}
			if(wCurPixel != wTColor && wNextPixel == wTColor) // �ȼ� ������ ����� �ȼ�
			{
				SET_ARRAY_VALUE(pDest, pitch, x, y, pMaskTbl[y*width+x]); // ����ũ ���̺��� ������ ��ġ�Ѵ�..
				y+=2;
			}
		}
	}

	this->SurfaceUnlock(lpDDS);

	return TRUE;
}

// ������� ����� �� ���� ó��..
BOOL CDDEngineTool4::TransactSimilarTransColor(LPDIRECTDRAWSURFACE lpDDS, COLORREF TColor, int nReinforceDelta)
{
	if(!lpDDS) return FALSE;
	if(nReinforceDelta <= 0 || nReinforceDelta >= 255) return FALSE;

	this->SurfaceLock(lpDDS, &m_ddsdTmp1);
	WORD* pDest = (WORD*)m_ddsdTmp1.lpSurface;
	int pitch = m_ddsdTmp1.lPitch / 2;
	int width = m_ddsdTmp1.dwWidth;
	int height = m_ddsdTmp1.dwHeight;
	int x, y;
	WORD wTColor = this->RGB16(TColor);
	
	// �۾��� ���� �����..
	WORD* pwBuff = new WORD[width*height];
	for(y = 0; y < height; y++)
	{
		memcpy(pwBuff + y*width, pDest + y*pitch, width*2); //�޸𸮿� ����..
	}
	this->SurfaceUnlock(lpDDS);

	int RMin = ((TColor & 0x000000ff)) - nReinforceDelta;
	int GMin = ((TColor & 0x0000ff00) >> 8) - nReinforceDelta;
	int BMin = ((TColor & 0x00ff0000) >> 16) - nReinforceDelta;
	int RMax = ((TColor & 0x000000ff)) + nReinforceDelta;
	int GMax = ((TColor & 0x0000ff00) >> 8) + nReinforceDelta;
	int BMax = ((TColor & 0x00ff0000) >> 16) + nReinforceDelta;
	
	if(RMin < 0) RMin = 0;
	if(RMax > 255) RMax = 255;
	if(GMin < 0) GMin = 0;
	if(GMax > 255) GMax = 255;
	if(BMin < 0) BMin = 0;
	if(BMax > 255) BMax = 255;
	
	COLORREF Pixel;
	int RPixel, GPixel, BPixel;
	WORD wPixel;
	int nnnn = 0;
	for(y = 0; y < height; y++) // ������̶� ����� �� ��Ƴ���
	{
		for(x = 0; x < width; x++)
		{
			wPixel = GET_ARRAY_VALUE(pwBuff, width, x, y);
			if(wPixel == wTColor) continue;

			Pixel = this->RGB24(wPixel);
			RPixel = (Pixel & 0x000000ff);
			GPixel = (Pixel & 0x0000ff00) >> 8;
			BPixel = (Pixel & 0x00ff0000) >> 16;
			if(	(RPixel >= RMin && RPixel <= RMax) &&
				(GPixel >= GMin && GPixel <= GMax) &&
				(BPixel >= BMin && BPixel <= BMax) )
			{
				SET_ARRAY_VALUE(pwBuff, width, x, y, wTColor);
				nnnn++;
			}
		}
	}

	// ���ι��� ��Ƽ ó��..
	WORD wPrevPixel = 0, wCurPixel = 0, wNextPixel = 0;
	for(y = 2; y < height-2; y++)
	{
		for(x = 2; x < width-2; x++)
		{
			wPrevPixel = GET_ARRAY_VALUE(pwBuff, width, x-1, y);
			wCurPixel = GET_ARRAY_VALUE(pwBuff, width, x, y);
			wNextPixel = GET_ARRAY_VALUE(pwBuff, width, x+1, y);
			if(wPrevPixel == wTColor && wCurPixel != wTColor) // ����������� �ȼ�
			{
				// �߰������� ä���ش�.
				COLORREF crTmp = 0;
				WORD RTmp = 0, GTmp = 0, BTmp = 0;
				int nAvg = 0;
				for(int y2 = -1; y2 <= 1; y2++)
				{
					for(int x2 = -2; x2 <= 0; x2++)
					{
						crTmp = this->RGB24(GET_ARRAY_VALUE(pwBuff, width, x + x2, y + y2));
						if(crTmp == TColor) continue; // ������� ��������...
						RTmp += (WORD)(crTmp & 0x000000ff);
						GTmp += (WORD)((crTmp & 0x0000ff00) >> 8);
						BTmp += (WORD)((crTmp & 0x00ff0000) >> 16);
						nAvg++;
					}
				}
				if(nAvg > 0)
				{
					RTmp /= nAvg; GTmp /= nAvg; BTmp /= nAvg;
					SET_ARRAY_VALUE(pwBuff, width, x, y, this->RGB16(RTmp, GTmp, BTmp));
				}
				x += 2;
			}
			if(wCurPixel != wTColor && wNextPixel == wTColor) // �ȼ� ������ ����� �ȼ�
			{
				// �߰������� ä���ش�.
				COLORREF crTmp = 0;
				WORD RTmp = 0, GTmp = 0, BTmp = 0;
				int nAvg = 0;
				for(int y2 = -1; y2 <= 1; y2++)
				{
					for(int x2 = 0; x2 <= 2; x2++)
					{
						crTmp = this->RGB24(GET_ARRAY_VALUE(pwBuff, width, x + x2, y + y2));
						if(crTmp == TColor) continue; // ������� ��������...
						RTmp += (WORD)(crTmp & 0x000000ff);
						GTmp += (WORD)((crTmp & 0x0000ff00) >> 8);
						BTmp += (WORD)((crTmp & 0x00ff0000) >> 16);
						nAvg++;
					}
				}
				if(nAvg > 0)
				{
					RTmp /= nAvg; GTmp /= nAvg; BTmp /= nAvg;
					SET_ARRAY_VALUE(pwBuff, width, x, y, this->RGB16(RTmp, GTmp, BTmp));
				}
				x+=2;
			}
		}
	}

	// ���ι��� ��Ƽ ó��..
	for(x = 2; x < width-2; x++)
	{
		for(y = 2; y < height-2; y++)
		{
			wPrevPixel = GET_ARRAY_VALUE(pwBuff, width, x, y-1);
			wCurPixel = GET_ARRAY_VALUE(pwBuff, width, x, y);
			wNextPixel = GET_ARRAY_VALUE(pwBuff, width, x, y+1);
			if(wPrevPixel == wTColor && wCurPixel != wTColor) // ����������� �ȼ�
			{
				COLORREF crTmp = 0;
				WORD RTmp = 0, GTmp = 0, BTmp = 0;
				int nAvg = 0;
				for(int y2 = -2; y2 <= 0; y2++)
				{
					for(int x2 = -1; x2 <= 1; x2++)
					{
						crTmp = this->RGB24(GET_ARRAY_VALUE(pwBuff, width, x + x2, y + y2));
						if(crTmp == TColor) continue; // ������� ��������...
						RTmp += (WORD)(crTmp & 0x000000ff);
						GTmp += (WORD)((crTmp & 0x0000ff00) >> 8);
						BTmp += (WORD)((crTmp & 0x00ff0000) >> 16);
						nAvg++;
					}
				}
				if(nAvg > 0)
				{
					RTmp /= nAvg; GTmp /= nAvg; BTmp /= nAvg;
					SET_ARRAY_VALUE(pwBuff, width, x, y, this->RGB16(RTmp, GTmp, BTmp));
				}
				y+=2;
			}
			if(wCurPixel != wTColor && wNextPixel == wTColor) // �ȼ� ������ ����� �ȼ�
			{
				COLORREF crTmp = 0;
				WORD RTmp = 0, GTmp = 0, BTmp = 0;
				int nAvg = 0;
				for(int y2 = 0; y2 <= 2; y2++)
				{
					for(int x2 = -1; x2 <= 1; x2++)
					{
						crTmp = this->RGB24(GET_ARRAY_VALUE(pwBuff, width, x + x2, y + y2));
						if(crTmp == TColor) continue; // ������� ��������...
						RTmp += (WORD)(crTmp & 0x000000ff);
						GTmp += (WORD)((crTmp & 0x0000ff00) >> 8);
						BTmp += (WORD)((crTmp & 0x00ff0000) >> 16);
						nAvg++;
					}
				}
				if(nAvg > 0)
				{
					RTmp /= nAvg; GTmp /= nAvg; BTmp /= nAvg;
					SET_ARRAY_VALUE(pwBuff, width, x, y, this->RGB16(RTmp, GTmp, BTmp));
				}
				y+=2;
			}
		}
	}

	// �۾��� ���� ���� ���ǽ��� ����..
	this->SurfaceLock(lpDDS, &m_ddsdTmp1);
	pDest = (WORD*)m_ddsdTmp1.lpSurface;
	pitch = m_ddsdTmp1.lPitch / 2;
	for(y = 0; y < height; y++)
	{
		memcpy(pDest + y*pitch, pwBuff + y*width, width*2);
	}
	this->SurfaceUnlock(lpDDS);

	DELETE_ARRAY_SAFE(pwBuff);

	return TRUE;
}

BOOL CDDEngineTool4::TransactPieceLSPSpr(const char* szFileName, int nRDelta, CPoint ptCenter, _SPR_LSP* pSpr)
{
	if(pSpr == NULL) return FALSE;

	LPDIRECTDRAWSURFACE lpDDS = NULL;
	if(lstrlen(szFileName)) lpDDS =  this->SurfaceCreateWithBMP(szFileName, FALSE, NULL);

	DDSURFACEDESC ddsd;
	if(lpDDS == NULL) return FALSE; // ���ǽ� �ε��� �����ϸ�..

	int width, height;
	CRect rcImage(0,0,0,0);
	COLORREF TColor = 0;

	this->SurfaceGetSize(lpDDS, &rcImage);
	if(rcImage.Width() <= 15 || rcImage.Height() <= 15)
	{
		MessageBox(NULL, "�̹��� ũ�Ⱑ 16*16 �����Դϴ�.", "��������Ʈ �ڵ� ���� ����", MB_OK);
		RELEASE_SAFE(lpDDS);
		return FALSE;
	}
	width = rcImage.Width();
	height = rcImage.Height();

	// ����� ����....
	this->SurfaceLock(lpDDS, &ddsd);
	WORD* pSrc = (WORD*)ddsd.lpSurface;
	int pitch = ddsd.lPitch / 2;
	WORD wTColor = GET_ARRAY_VALUE(pSrc, pitch, 0, 0); // ȭ���� 0,0 �� ��..
	TColor = this->RGB24(wTColor);
	this->SurfaceUnlock(lpDDS);
	
	// ���� �÷��� ��ȭ���ڿ� �Է��� Ư�� ���� �ȿ� �ִ� �ȼ��� �����÷��� ä���ش�.
	this->TransactSimilarTransColor(lpDDS, TColor, nRDelta); // �� ������ �μ��� ... ��Ƴ���..?? 0 ~ 255, �ǵڴ� ������ �Ұ��� ���Ұ���

	// ���� ���� ã�� �� LSP ����
	BOOL bSuccess = FALSE;
	CRect rc = this->FindRegionManual(lpDDS, rcImage, TColor);
	bSuccess = this->EncodeToLSPData(lpDDS, TColor, rc, ptCenter, pSpr); // ������ ����

	if(rc.Width() > 0 && rc.Height() > 0)
	{
		pSpr->rcV = rc - ptCenter; // ������ ���ϱ�..
	}

	RELEASE_SAFE(lpDDS);
	
	return bSuccess; // ���� ó���� ����
}
