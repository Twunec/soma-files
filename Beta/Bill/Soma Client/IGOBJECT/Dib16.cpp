// Dib.cpp: implementation of the CDib16 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dib16.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDib16::CDib16()
{
	m_hBuff = NULL;
	MAKE_ZERO(m_Header);
}

CDib16::~CDib16()
{
	Release();
}

void CDib16::Release()
{
	if(m_hBuff)
	{
		GlobalFree(m_hBuff); // �޸� ����..
		m_hBuff = NULL;
	}
	MAKE_ZERO(m_Header);
}

BOOL CDib16::ImportGenericBMP(const char* szFileName)
{
	DWORD dwAccessed = 0;
	HANDLE hFile = CreateFile(szFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		OutputDebugString("��Ʈ�� Import ���� : ���� ���� ���� - ");
		OutputDebugString(szFileName);
		OutputDebugString("\n");
		return FALSE;
	}

	BITMAPFILEHEADER bmHFile;
	BITMAPINFOHEADER bmHInfo;

	ReadFile(hFile, &bmHFile, sizeof(BITMAPFILEHEADER), &dwAccessed, NULL);
	if(bmHFile.bfType != 0x4d42)
	{
		OutputDebugString("��Ʈ�� Import ���� : ��Ʈ�� ������ �ƴ� - ");
		OutputDebugString(szFileName);
		OutputDebugString("\n");
		CloseHandle(hFile);
		return FALSE;
	}

	ReadFile(hFile, &bmHInfo, sizeof(BITMAPINFOHEADER), &dwAccessed, NULL);
	
	if(New(bmHInfo.biWidth, bmHInfo.biHeight) == FALSE) // ������ �����ϸ� ���Ϸκ��� �д´�.
	{
		CloseHandle(hFile);
		return FALSE;
	}

	DWORD dwAllocSize = 0;
	RGBQUAD* pcrIndices = NULL;
	DWORD dwPixelSize = 0;
	if(bmHInfo.biClrUsed != 0 && bmHInfo.biBitCount == 8) // �ε����� �ְ� 8 ��Ʈ ��Ʈ���̸�..
	{
		dwAllocSize = (bmHInfo.biWidth+bmHInfo.biWidth%2)*bmHInfo.biHeight;
		dwPixelSize = 1;
		
		pcrIndices = new RGBQUAD[256]; // �ȷ�Ʈ ���� ����
		ReadFile(hFile, pcrIndices, sizeof(RGBQUAD)*256, &dwAccessed, NULL); // �ȷ�Ʈ�� �д´�.
	}
	else if(bmHInfo.biClrUsed == 0 && bmHInfo.biBitCount == 24) // �ε����� ���� 24 ��Ʈ ��Ʈ���̸�..
	{
		dwAllocSize = (((bmHInfo.biWidth*3)+(bmHInfo.biWidth*3)%2))*bmHInfo.biHeight;
		dwPixelSize = 3;
	}
	else
	{
		OutputDebugString("��Ʈ�� Import ���� : �˼� ���� ��Ʈ�� ���� ���� - ");
		OutputDebugString(szFileName);
		OutputDebugString("\n");
		CloseHandle(hFile);
		return FALSE;
	}

	HGLOBAL hSrc = GlobalAlloc(GMEM_FIXED, dwAllocSize); // �ӽ� ���� ����
	unsigned char* pbiSrc = (unsigned char*)GlobalLock(hSrc);
	ReadFile(hFile, pbiSrc, dwAllocSize, &dwAccessed, NULL); // ���Ͽ��� �б�

	WORD* pwDest = this->Lock(); // ���� ���� ��
	for(int y = 0; y < bmHInfo.biHeight; y++)
	{
		unsigned char* pbiTmpSrc = pbiSrc + (bmHInfo.biHeight - y - 1) * (bmHInfo.biWidth*dwPixelSize + (bmHInfo.biWidth*dwPixelSize)%2); // ��Ʈ���� �Ųٷ� �ִ�..
		WORD* pwTmpDest = pwDest + y * bmHInfo.biWidth;
		for(int x = 0; x < bmHInfo.biWidth; x++)
		{
			if(dwPixelSize == 3) // 24 ��Ʈ �϶�
			{
				*pwTmpDest = this->RGB16(pbiTmpSrc[2], pbiTmpSrc[1], pbiTmpSrc[0]);
			}
			else
			{
				*pwTmpDest = this->RGB16(pbiTmpSrc[2], pbiTmpSrc[1], pbiTmpSrc[0]);
			}
			pbiTmpSrc += dwPixelSize;
			pwTmpDest++;
		}
	}
	this->Unlock(); // ���� ���� ���

	CloseHandle(hFile); // ���� �ڵ� �ݱ�

	GlobalUnlock(hSrc);
	GlobalFree(hSrc); hSrc = NULL; // �ӽ� ���� ����..
	if(pcrIndices) { delete [] pcrIndices; pcrIndices = NULL; } // �ȷ�Ʈ ���� ����
	return TRUE;
}

BOOL CDib16::ExportTo24BMP(const char *szFileName)
{
	if(m_Header.nWidth <= 0 || m_Header.nHeight <= 0)
	{
		OutputDebugString("��Ʈ�� Export ���� : ���� Ȥ�� ���� 0 ���� ���� - ");
		OutputDebugString(szFileName);
		OutputDebugString("\n");
		return FALSE;
	}

	DWORD dwAccessed = 0;
	HANDLE hFile = CreateFile(szFileName, GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		OutputDebugString("��Ʈ�� Export ���� : ���� ���� ���� - ");
		OutputDebugString(szFileName);
		OutputDebugString("\n");
		return FALSE;
	}
	
	BITMAPFILEHEADER bmHFile; MAKE_ZERO(bmHFile);
	BITMAPINFOHEADER bmHInfo; MAKE_ZERO(bmHInfo);

	bmHFile.bfSize = sizeof(BITMAPFILEHEADER);
	bmHFile.bfType = 0x4d42; // 'BM'
	bmHFile.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);
	
	bmHInfo.biSize = sizeof(BITMAPINFOHEADER);
	bmHInfo.biWidth = m_Header.nWidth;
	bmHInfo.biHeight = m_Header.nHeight;
	bmHInfo.biBitCount = 24;
	bmHInfo.biCompression = BI_RGB;
	bmHInfo.biPlanes = 1;
	bmHInfo.biSizeImage = 0; // ����� ������ �ƴϴ�....!!
	bmHInfo.biClrUsed = 0; // 24 ��Ʈ �÷�~!!
	bmHInfo.biClrImportant = 0;

	WriteFile(hFile, &bmHFile, sizeof(BITMAPFILEHEADER), &dwAccessed, NULL);
	WriteFile(hFile, &bmHInfo, sizeof(BITMAPINFOHEADER), &dwAccessed, NULL);
	
	WORD* pwSrc = this->Lock(); // ���� ���� ��

	int nPitch = m_Header.nWidth*3+m_Header.nWidth%2;
	HGLOBAL hDest = GlobalAlloc(GMEM_FIXED, nPitch*m_Header.nHeight);  // �ӽ� ���� �޸� �Ҵ�..
	BYTE* pDest = (BYTE*)GlobalLock(hDest); // �ӽ� ���� ��..
	// ������ �б�..
	COLORREF crPixel = 0;
	for(int y = m_Header.nHeight - 1, y2 = 0; y >= 0; y--, y2++) // �Ųٷ� ��� �Ұ�...
	{
		WORD* pwTmpSrc = pwSrc + y2*m_Header.nWidth;
		BYTE* pTmpDest = pDest + y*nPitch;
		for(int x = 0; x < m_Header.nWidth; x++)
		{
			crPixel = this->RGB24(*(pwTmpSrc+x));
			*(pTmpDest+0) = (BYTE)((crPixel&0x00ff0000)>>16); // r
			*(pTmpDest+1) = (BYTE)((crPixel&0x0000ff00)>>8); // g
			*(pTmpDest+2) = (BYTE)((crPixel&0x000000ff)); // b
			
			pTmpDest += 3;
		}
	}

	// ���Ͽ� ����..
	WriteFile(hFile, pDest, nPitch*m_Header.nHeight, &dwAccessed, NULL);

	GlobalUnlock(hDest); // �ӽ� ���� ���
	GlobalFree(hDest); hDest = NULL;
	this->Unlock(); // ���� ���� ���

	CloseHandle(hFile);
	return TRUE;
}

BOOL CDib16::New(int nWidth, int nHeight)
{
	if(	nWidth <= 0 || nHeight <= 0)
	{
		OutputDebugString("��Ʈ�� ���� ���� : �ʺ�, ���̰� 0���� ����");
		OutputDebugString("\n");
		return FALSE;
	}
	
	Release();
	
	m_hBuff = GlobalAlloc(GMEM_FIXED, nWidth*nHeight*2);  // �޸� �Ҵ�..
	if(m_hBuff != NULL)
	{
		m_Header.nWidth = nWidth;
		m_Header.nHeight = nHeight;
		m_Header.szID[0] = 16;
		m_Header.szID[1] = 'B';
		m_Header.szID[2] = 'M';
		m_Header.szID[3] = 'P';
		WORD* pwDest = (WORD*)GlobalLock(m_hBuff);
		memset(pwDest, 0, nWidth*nHeight*2);
		GlobalUnlock(m_hBuff);
	}
	else
	{
		Release();
		OutputDebugString("��Ʈ�� ���� ����� : �޸� �Ҵ� ����\n");
		return FALSE;
	}

	return TRUE;
}

BOOL CDib16::Load(const char* szFileName)
{
	DWORD dwAccessed = 0;
	HANDLE hFile = CreateFile(szFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		OutputDebugString("��Ʈ�� ���� �θ��� ���� : ���� ���� ���� - ");
		OutputDebugString(szFileName);
		OutputDebugString("\n");
		return FALSE;
	}

	// ����� �а� 16 ��Ʈ ��Ʈ������ Ȯ��...
	_BMP16_HEADER Header;
	ReadFile(hFile, &Header, sizeof(_BMP16_HEADER), &dwAccessed, NULL);
	if(Header.szID[0] == 'B' && Header.szID[1] == 'M' && Header.szID[2] == 'C' && Header.szID[3] == 16)
	{
		int data_size, d_count;
		int i = 0, j = 0, k;
		WORD filter;

		ReadFile(hFile, &data_size, sizeof(int), &dwAccessed, NULL);
		WORD *src_data = new WORD[data_size];
		ReadFile(hFile, src_data, data_size*2, &dwAccessed, NULL);
		// ���� ����..
		if(New(Header.nWidth, Header.nHeight)) // ������ �����ϸ� ���Ϸκ��� �д´�.
		{
			lstrcpy(m_Header.szRemark, Header.szRemark); // ����� �ּ��� �ٿ��ְ�..
			WORD* pBuff = this->Lock();
			while(i < data_size)
			{
				// ���� ������
				d_count = *(int *)(src_data+i); i += 2;
				if(d_count > 0)
				{
					CopyMemory(pBuff+j, src_data+i, d_count*2);
					j += d_count;
					i += d_count;
				}
				d_count = *(int *)(src_data+i); i += 2;
				filter = src_data[i++];
				for(k = 0; k < d_count; k++,j++) *(pBuff+j) = filter;
			}
			this->Unlock();
		}

		delete[] src_data;
		CloseHandle(hFile);
		return TRUE;
	}
	else if(Header.szID[0] == 'B' && Header.szID[1] == 'M' && Header.szID[2] == 'P' && Header.szID[3] == 16)
	{
		if(New(Header.nWidth, Header.nHeight)) // ������ �����ϸ� ���Ϸκ��� �д´�.
		{
			lstrcpy(m_Header.szRemark, Header.szRemark); // ����� �ּ��� �ٿ��ְ�..
			WORD* pBuff = this->Lock();
			ReadFile(hFile, pBuff, m_Header.nWidth*m_Header.nHeight*2, &dwAccessed, NULL); // �д´�..
			this->Unlock();
		}

		CloseHandle(hFile);
		return TRUE;
	}
	else
	{
		CloseHandle(hFile);
		return FALSE;
	}
}

BOOL CDib16::Save(const char *szFileName)
{
	DWORD dwAccessed = 0;
	HANDLE hFile = CreateFile(szFileName, GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		OutputDebugString("��Ʈ�� ���� : ���� ���� ���� - ");
		OutputDebugString(szFileName);
		OutputDebugString("\n");
		return FALSE;
	}

	// ����� �а� 16 ��Ʈ ��Ʈ������ Ȯ��...
	m_Header.szID[0] = 'B', m_Header.szID[1] = 'M', m_Header.szID[2] = 'P', m_Header.szID[3] = 16;
	WriteFile(hFile, &m_Header, sizeof(_BMP16_HEADER), &dwAccessed, NULL);

	WORD* pBuff = this->Lock();
	WriteFile(hFile, pBuff, m_Header.nWidth*m_Header.nHeight*2, &dwAccessed, NULL); // �д´�..
	this->Unlock();

	CloseHandle(hFile);

	return TRUE;
}

// ������ ������ ������ ����� ĥ�Ѵ�. ���������Ͱ� NULL�̸� ��ü�� ĥ�Ѵ�..
void CDib16::FillColor(RECT *pRC, COLORREF crFill)
{
	if(m_Header.nWidth <= 0 || m_Header.nHeight <= 0) return;
	
	RECT rcFill;
	if(pRC == NULL) SetRect(&rcFill, 0, 0, m_Header.nWidth, m_Header.nHeight);
	else
	{
		RECT rcWhole = {0, 0, m_Header.nWidth, m_Header.nHeight};
		IntersectRect(&rcFill, pRC, &rcWhole);
		if(rcFill.right - rcFill.left <= 0 || rcFill.bottom - rcFill.top <= 0) return; // ä�� ������ �߸��Ǹ� ���ư�..
	}

	WORD wFillColor = this->RGB16(crFill);
	int nPixel = m_Header.nHeight*m_Header.nWidth;
	
	WORD* pwDest = this->Lock();
	for(int i = 0; i < nPixel; i++) *(pwDest+i) = wFillColor;
	this->Unlock();
}
