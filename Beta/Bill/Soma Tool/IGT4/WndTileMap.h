#if !defined(AFX_WNDMAPTILE_H__3615582C_69D3_403E_9CAA_E7E5148404D7__INCLUDED_)
#define AFX_WNDMAPTILE_H__3615582C_69D3_403E_9CAA_E7E5148404D7__INCLUDED_

#include "MouseSelectManager.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WndMapTile.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWndMapTile window

#include "DlgTileMap.h"
#include "DlgTileMapObj.h"
#include "DlgHouseInfo.h" // ����������

class CWndTileMap : public CWnd
{
// Construction
public:
	CWndTileMap();
	
// Attributes
public:
	CDlgTileMap		m_Dlg; // Ÿ�ϼ°� ���� �ٷ��.
	CDlgTileMapObj	m_DlgObj; // �ʻ��� ������Ʈ �� �ٷ��.
	CDlgHouseInfo	m_DlgHouse; // ����������

	CPoint m_ptMouse;
	CPoint m_ptLBDown;
	CPoint m_ptRBDown;
	CRect m_rcCopy; // ������ ������ ����
	CRect m_rcSelect; // �� �۾��� ���������� �巡���� ���� 

	CPoint m_ptLBPrev; // �����̽��ٸ� �������� ��ũ�� ������ ����س��´�.
	CPoint m_ptScrollPrev; // �����̽��ٸ� ������ ��ũ�� ��ġ..

	CRect m_rcNeedUpdate;
	CRect m_rcSetSel;

	HCURSOR m_hCursorDrag;
	HCURSOR m_hCursorOrg;

	MouseSelectManager m_MSM;
// Operations
protected:
	_TILE_MAP_DATA_TOOL_FOR_UNDO m_UndoData; // ���� ��ҿ� ������..

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWndTileMap)
	//}}AFX_VIRTUAL

// Implementation
public:
	void GotoHouse(int number);
	void UnoClearData();
	void Undo();
	void UndoPrepareData(CRect rc);
	void RecalcScrollBar();
	BOOL TileMapSet(int x, int y, int nBrush);
	BOOL TileMapDelete(int x, int y, int nBrush);
	virtual ~CWndTileMap();

	void ActiveAni();
	void DeactiveAni();
	void AniPaint();

	void DrawBitmap(LPDIRECTDRAWSURFACE DstSurf, CRect draw_rect);
	BOOL m_bAniMode;
	// Generated message map functions
protected:
	//{{AFX_MSG(CWndTileMap)
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WNDMAPTILE_H__3615582C_69D3_403E_9CAA_E7E5148404D7__INCLUDED_)
