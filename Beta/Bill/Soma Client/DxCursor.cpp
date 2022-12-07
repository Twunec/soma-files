// DxCursor.cpp: implementation of the CDxCursor class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "soma.h"
#include "DxCursor.h"
#include "DManage/BB_Direct.h"
#include "ChildView.h"
#include "User.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDxCursor::CDxCursor()
{
	m_dwTick = 0;
	m_iCursorIndex = 0;
	m_iSpriteIndex = 0;
	m_ptHotSpot = CPoint(0,0);
	for(int i = 0; i < CURSOR_COUNT; i++) m_arrCursor[i] = NULL;
}

CDxCursor::~CDxCursor()
{
	RemoveAllData();
}

void CDxCursor::RemoveAllData()
{
	for (int i = 0; i < CURSOR_COUNT; i++)
	{
		delete m_arrCursor[i];
		m_arrCursor[i] = NULL;
	}
}

void CDxCursor::SetCursorIndex(int index)
{
	if(m_iCursorIndex == index) return;

	m_iCursorIndex = index;
	m_iSpriteIndex = 0;
}

void CDxCursor::Draw(CDDSurface *pSurface, CPoint ptPos)
{
//	ptPos.x -= m_ptHotSpot.x;
//	ptPos.y -= m_ptHotSpot.y;

	SPR_DATA *spr_data;
	_SPR_LSP* spr;
	PWORD pV;

	spr_data = m_arrCursor[m_iCursorIndex];
	if(spr_data == NULL)
	{
		spr = NULL;
		pV = NULL;
		return;
	}

	if(m_iSpriteIndex == spr_data->m_AniData.nMaxFrm) m_iSpriteIndex = 0;

	int frame;
	DWORD dwTick = GetTickCount();
	BOOL bFrameChange = FALSE;
	// �ð��� ������ ���� ������ ������..
	if (dwTick > m_dwTick + 1000 / spr_data->m_AniData.fSpd)
	{
		m_dwTick = dwTick;
		if(m_iSpriteIndex < 0 || m_iSpriteIndex >= spr_data->m_HAni.nDirQt * spr_data->m_AniData.nMaxFrm)
		{
			return;
		}
		frame = spr_data->m_AniData.pnFrms[m_iSpriteIndex];
		if(frame < 0 || frame >= spr_data->m_HSpr.nQt)
		{
			return;
		}
		m_iSpriteIndex++;
	}
	else frame = spr_data->m_AniData.pnFrms[m_iSpriteIndex];

	spr = &spr_data->m_arrSprData[frame];
	pV = spr_data->m_arrVData[frame];

	RECT rcV = spr->rcV;

	BltLSPNormal(pSurface, ptPos.x, ptPos.y, &rcV, pV);
}

static char CURSOR_NAME[CURSOR_COUNT][7] = {"normal", "attack", "pickup"};

void CDxCursor::InitCursor()
{
	const CString szExePath = CDirectDraw::GetExecutionPath();
	CString szSplFileName, szAniFileName;
	int i=0;

	int Count = 0;
	UINT count;
	CFile spl_file, ani_file;
	WORD *word;
	int index = 0;
	SPR_DATA *spr_data;

	for(int j = 0; j < CURSOR_COUNT; j++)
	{
		szSplFileName.Format("%sNRes\\%s.spl", (LPCTSTR)szExePath, (LPCTSTR)CURSOR_NAME[j]);
		szAniFileName.Format("%sNRes\\%s.ani", (LPCTSTR)szExePath, (LPCTSTR)CURSOR_NAME[j]);
		
		if(spl_file.Open(szSplFileName, CFile::modeRead) == FALSE)
		{
			continue;
		}
		if(ani_file.Open(szAniFileName, CFile::modeRead) == FALSE)
		{
			spl_file.Close();
			continue;
		}
		//Spl ���� �б� (������ Spr�� �ٸ�)
		//�켮.. 10�� 15��..
		
		spr_data = new SPR_DATA;
		
		spl_file.Read(&spr_data->m_HSpr, sizeof(_SPR_HEADER));
		spl_file.Seek(sizeof(_SPR_TOOL)*spr_data->m_HSpr.nQt, CFile::current);
		
		if(spr_data->m_HSpr.nQt > 0)
		{
			spr_data->m_arrSprData = new _SPR_LSP[spr_data->m_HSpr.nQt];
			spr_data->m_arrVData = new WORD *[spr_data->m_HSpr.nQt];
			
			for (i=0; i<spr_data->m_HSpr.nQt; i++)
			{
				spl_file.Read((PVOID)&spr_data->m_arrSprData[i], sizeof(_SPR_LSP));
				spr_data->m_arrSprData[i].pwV = NULL;
			}
			
			for (i=0; i<spr_data->m_HSpr.nQt; i++)
			{
				count = spr_data->m_arrSprData[i].nDataSize;
				if(count)
				{
					word = new WORD[count>>1];
					spl_file.Read((PVOID)word, count);
					if(CChildView::CharManager.GetPixelFormat()==PF_555) CCharRes::Decode2_555(spr_data->m_arrSprData[i].nLine, word);
					spr_data->m_arrVData[i] = word;
				}
				else
				{
					spr_data->m_arrVData[i] = NULL;
				}
			}
		}
		
		// �ִϸ��̼�
		ani_file.Read((PVOID)&spr_data->m_HAni, sizeof(_ANI_HEADER));
		ani_file.Read((PVOID)&spr_data->m_AniData, sizeof(_ANI_DATA));
		spr_data->m_AniData.pnFrms = NULL;
		if(spr_data->m_AniData.nMaxFrm > 0)
		{
			int nQt = spr_data->m_HAni.nDirQt * spr_data->m_AniData.nMaxFrm; // ���� ��� = ���� * �����Ӱ���
			spr_data->m_AniData.pnFrms = new short int[nQt]; // ���� ��ŭ ����
			ani_file.Read(spr_data->m_AniData.pnFrms, nQt*2); // ���� ��ŭ �д´�.
		}
		
		m_arrCursor[j] = spr_data;
		
		spl_file.Close();
		ani_file.Close();
	}
}

void CDxCursor::BltLSPNormal(CDDSurface *pSurface, int x, int y, RECT* pRC, WORD* data)
{
	if(data == NULL) return;
	if(pRC == NULL) return;

	int ScreenX = 800;
	int ScreenY = 600;

	if(pRC->right - pRC->left <= 0 || pRC->bottom - pRC->top <= 0) return; // ��ȿ�� �ȼ��� ������ ���ư���..
	RECT rc = {x+pRC->left, y+pRC->top, x+pRC->right, y+pRC->bottom};
	if(rc.right < 0 || rc.bottom < 0 || rc.left >= ScreenX || rc.top >= ScreenY) return; // ȭ���� ������ ���..

	RECT rcClip; // Ŭ���� ������ ���ϰ� �ɼµ� ���Ѵ�.
	BOOL bUseXClip = FALSE;
	rcClip = rc;

	if(rc.left < 0)
	{ 
		rcClip.left = 0;
		bUseXClip = TRUE;
	}
	else if(rc.right > ScreenX)
	{ 
		rcClip.right = ScreenX;
		bUseXClip = TRUE;
	}
	if(rc.top < 0)
	{
		rcClip.top = 0;
	}
	else if(rc.bottom > ScreenY)
	{
		rcClip.bottom = ScreenY;
	}

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

	if( NULL == pSurface->Lock() ) return;
	DDSURFACEDESC2& ddsd = pSurface->GetDescription();
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
				if(nCopyCount == 0)
				{
					pSurface->Unlock();
					return;
				}
				CUser::PutPixelNormal(pDest, pSrc, nCopyCount);

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
				CUser::PutPixelNormal(pDest, pSrc, nCopyCount);
				// }

			}
		}
	}
	pSurface->Unlock();
}
