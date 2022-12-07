// WndObjPreview.cpp : implementation file
//

#include "stdafx.h"
#include "igt4.h"
#include "WndObjPreview.h"
#include "GlobalVar.h"
#include "DlgTileMapObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWndObjPreview

CWndObjPreview::CWndObjPreview( CDlgTileMapObj* DlgTMapObj )
{
	m_DlgTMapObj = DlgTMapObj;
}

CWndObjPreview::~CWndObjPreview()
{
}


BEGIN_MESSAGE_MAP(CWndObjPreview, CWnd)
	//{{AFX_MSG_MAP(CWndObjPreview)
	ON_WM_PAINT()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CWndObjPreview message handlers

void CWndObjPreview::OnPaint() 
{
	CPaintDC dc(this); // device context for painting

	int nSet, nSubSet;
	CAniObjLSP* pAniObj;
	const _SPR_LSP* pSpr = NULL;
	int nSpr;
	CPoint pt;
	CRect rcClient;
	int nData = m_DlgTMapObj->GetSelectedObjData();

	if(nData >= 0) // ���õ� ���� �߸��Ǿ� ������ -1 ����.
	{
		nSet = nData >> 8; // ������Ʈ ��Ʈ
		nSubSet = nData & 0xff; // ������Ʈ ���� ��Ʈ
		if(nSet >= 0 && nSet < MAX_MAP_OBJ_REG && nSubSet >= 0)
		{
			pAniObj = &m_DlgTMapObj->m_MapObj.m_Objs[nSet];
			pSpr = NULL;
			nSpr = pAniObj->FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
			pAniObj->SprGet(nSpr, &pSpr);
			if(pSpr)
			{
				int width,height,xgap,ygap;
				xgap = pSpr->rcV.right - pSpr->rcV.left;
				ygap = pSpr->rcV.bottom - pSpr->rcV.top;
				if( xgap <= 0 || ygap <= 0 )
				{
					g_pTEng->HWndSet(this->m_hWnd);
					g_pTEng->Flip(&dc.m_ps.rcPaint);
					return;
				}
				CRect rcAdjust(0, 0, xgap, ygap);
				::AdjustWindowRect(&rcAdjust, this->GetStyle(), FALSE);
				width = rcAdjust.Width();
				height = rcAdjust.Height();
				this->SetWindowPos(NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER);

				GetClientRect(&rcClient);
				g_pTEng->SurfaceFillRect(NULL, &rcClient, RGB(64,64,64)); // ��Ŀ�ݰ� �Ѵ�..

				pt.x = -pSpr->rcV.left;
				pt.y = -pSpr->rcV.top;
				g_pTEng->BackBufferLock();
				g_pTEng->BltLSP(NULL, pt.x, pt.y, pSpr);
				g_pTEng->BackBufferUnlock();
				g_pTEng->HWndSet(this->m_hWnd);
				g_pTEng->Flip(&rcClient);
			}
		}
	}
	else
	{
		GetClientRect(&rcClient);
		g_pTEng->SurfaceFillRect(NULL, &rcClient, RGB(64,64,64)); // ��Ŀ�ݰ� �Ѵ�..
		g_pTEng->HWndSet(this->m_hWnd);
		g_pTEng->Flip(&rcClient);
	}
	// Do not call CWnd::OnPaint() for painting messages
}

void CWndObjPreview::OnDestroy() 
{
	CWnd::OnDestroy();
}
