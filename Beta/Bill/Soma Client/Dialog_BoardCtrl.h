// Dialog_KrBoard.h: interface for the CDialog_BoardCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIALOG_KRBOARD_H__6566C202_6153_11D4_A1F5_00D0B769A081__INCLUDED_)
#define AFX_DIALOG_KRBOARD_H__6566C202_6153_11D4_A1F5_00D0B769A081__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "UIRes.h"


#include "Soma.h"
#include "ChildView.h"
#include "DManage\BBDX_MouseInformation.h"
#include "DManage/BB_Direct.h"
#include "DManage/AlphaProcess.h"
#include "illstruct.h"

class CDirectDraw;
class CChildView;

class CDialog_BoardList;
class CDialog_BoardRead;
class CDialog_BoardWrite;

class CTWFont;


#define LINE_GAP 3


#define BOARDDRAW_NONE	0
#define BOARDDRAW_LIST	1
#define BOARDDRAW_READ	2
#define BOARDDRAW_WRITE 3

#define BOARD_NORMAL	0		// �б�, ����, �ڱ�� �����
#define BOARD_READONLY	1		// �б⸸ ����
#define BOARD_READWRITE	2		// �б�, ���⸸ ����, ����� �Ұ�
#define BOARD_FULL		3		// ��� ����(Ŭ���̾�Ʈ�� 0���� ����)

class LIST_DATA;
typedef CTypedPtrArray<CPtrArray, LIST_DATA*> ARR_LIST;
class LIST_DATA {
public:
	int m_nNum;
	CString m_strData[3];
};


class CDialog_BoardCtrl
{
public:
	BOOL IsUnique(int nNum);
	void BBS_SetRead(PBYTE bypData);
	void BBS_PKT_Process(PBYTE bypData);
	BOOL BBS_SetList(PBYTE bypData);
	void BBS_SetOpen(PBYTE bypData);
	void DrawMode(int nMode);
	int BoardMouseProcess(BBDX_MouseInformation *pMouseInfo);
	BOOL InitData(CDirectDraw *pDD, CChildView *pWnd);
	void Draw(CDDSurface *pDest);

	int GetBoardNum() {return m_nBoardNum;};
	void RemoveAllSaveList();

	CDialog_BoardCtrl();
	virtual ~CDialog_BoardCtrl();

	CUIRes *m_pDrawBoard;		// �׷��ֱ� ���� �����ͷμ� ���� ������  Board�� �ϳ��� ����Ų��
								// Virtual�� Dynamic ����Type�� ���󰡰� �ִ�. 
	ARR_LIST m_arrList;
	BYTE m_nBoardSpec;		// ���� �Ӽ�

	CDialog_BoardList *m_pBoardList;	//  Board List�����ֱ�.
	CDialog_BoardRead *m_pBoardRead;	//  Board �б�.
	CDialog_BoardWrite *m_pBoardWrite;	//  Board ����.

protected:
	CDirectDraw *m_pDD;
	CChildView *m_pWnd;

	int m_nBoardNum;	// BoardCtrl�� �����ϴ� �Խ����� ��ȣ.

	int m_nDrawMode;
	
private:
	BOOL m_bInit;
};

#endif // !defined(AFX_DIALOG_KRBOARD_H__6566C202_6153_11D4_A1F5_00D0B769A081__INCLUDED_)
