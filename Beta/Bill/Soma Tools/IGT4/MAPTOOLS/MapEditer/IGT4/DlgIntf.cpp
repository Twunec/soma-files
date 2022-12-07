// TabZone.cpp : implementation file
//

#include "stdafx.h"
#include "DlgIntf.h"

#include "GlobalVar.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgIntf dialog
CDlgIntf::CDlgIntf(CWnd* pParent) : CDialog(CDlgIntf::IDD)
{
	BOOL m_bUpdateData = FALSE;
	BOOL m_bUpdateInfo = FALSE;
	m_lpDDSBkg = NULL;

	//{{AFX_DATA_INIT(CDlgIntf)
	//}}AFX_DATA_INIT
}

CDlgIntf::~CDlgIntf()
{
	RELEASE_SAFE(m_lpDDSBkg);
}

void CDlgIntf::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgIntf)
	DDX_Control(pDX, IDC_C_VIEW_OUTLINE, m_CViewOutLine);
	DDX_Control(pDX, IDC_CB_INTF_TYPE, m_CBIntfType);
	DDX_Control(pDX, IDC_CB_RENDER_TYPE, m_CBRenderType);
	DDX_Control(pDX, IDC_C_VIEW_BKG, m_CViewBkg);
	DDX_Control(pDX, IDC_C_VIEW_TRANS, m_CViewTrans);
	DDX_Control(pDX, IDC_C_VIEW_LINE, m_CViewLine);
	DDX_Control(pDX, IDC_C_VIEW_ZOOM, m_CViewZoom);
	DDX_Control(pDX, IDC_C_PLAY_ANIMATION, m_CPlayAnimation);
	DDX_Control(pDX, IDC_TREE, m_Tree);
	DDX_Control(pDX, IDC_ANI_LIST, m_AniList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgIntf, CDialog)
	//{{AFX_MSG_MAP(CDlgIntf)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_SAVE_AS, OnSaveAs)
	ON_BN_CLICKED(IDC_BROWSE_SPR, OnBrowseSpr)
	ON_BN_CLICKED(IDC_BROWSE_ANI, OnBrowseAni)
	ON_WM_TIMER()
	ON_NOTIFY(NM_RCLICK, IDC_TREE, OnRclickTree)
	ON_NOTIFY(TVN_KEYDOWN, IDC_TREE, OnKeydownTree)
	ON_NOTIFY(TVN_ENDLABELEDIT, IDC_TREE, OnEndlabeleditTree)
	ON_COMMAND(ID_MENU_LAYER_ADD, OnMenuLayerAdd)
	ON_COMMAND(ID_MENU_LAYER_INSERT, OnMenuLayerInsert)
	ON_COMMAND(ID_MENU_LAYER_DELETE, OnMenuLayerDelete)
	ON_COMMAND(ID_MENU_INTF_ADD, OnMenuIntfAdd)
	ON_COMMAND(ID_MENU_INTF_INSERT, OnMenuIntfInsert)
	ON_COMMAND(ID_MENU_INTF_DELETE, OnMenuIntfDelete)
	ON_COMMAND(ID_MENU_INTF_COPY, OnMenuIntfCopy)
	ON_COMMAND(ID_MENU_INTF_PASTE, OnMenuIntfPaste)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE, OnSelchangedTree)
	ON_LBN_SELCHANGE(IDC_ANI_LIST, OnSelchangeAniList)
	ON_NOTIFY(TVN_BEGINDRAG, IDC_TREE, OnBegindragTree)
	ON_NOTIFY(NM_CLICK, IDC_TREE, OnClickTree)
	ON_BN_CLICKED(IDC_C_PLAY_ANIMATION, OnCPlayAnimation)
	ON_BN_CLICKED(IDC_C_VIEW_LINE, OnCViewLine)
	ON_BN_CLICKED(IDC_C_VIEW_BKG, OnCViewBkg)
	ON_BN_CLICKED(IDC_C_VIEW_ZOOM, OnCViewZoom)
	ON_EN_CHANGE(IDC_EDIT_WIDTH, OnChangeEditWidth)
	ON_EN_CHANGE(IDC_EDIT_HEIGHT, OnChangeEditHeight)
	ON_NOTIFY(TVN_BEGINLABELEDIT, IDC_TREE, OnBeginlabeleditTree)
	ON_BN_CLICKED(IDC_B_BROWSE_BKG, OnBBrowseBkg)
	ON_CBN_SELCHANGE(IDC_CB_INTF_TYPE, OnSelchangeCbIntfType)
	ON_EN_CHANGE(IDC_E_FLAG0, OnChangeEFlag0)
	ON_EN_CHANGE(IDC_E_FLAG1, OnChangeEFlag1)
	ON_EN_CHANGE(IDC_E_FLAG2, OnChangeEFlag2)
	ON_EN_CHANGE(IDC_E_FLAG3, OnChangeEFlag3)
	ON_CBN_SELCHANGE(IDC_CB_RENDER_TYPE, OnSelchangeCbRenderType)
	ON_EN_CHANGE(IDC_E_A, OnChangeEA)
	ON_EN_CHANGE(IDC_E_R, OnChangeER)
	ON_EN_CHANGE(IDC_E_G, OnChangeEG)
	ON_EN_CHANGE(IDC_E_B, OnChangeEB)
	ON_BN_CLICKED(IDC_C_VIEW_OUTLINE, OnCViewOutline)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgIntf::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	New();
	
	m_CViewLine.SetCheck(TRUE); // ������ üũ...
	m_CViewOutLine.SetCheck(TRUE); // ȭ�� �ܰ������� üũ...
	SetDlgItemInt(IDC_EDIT_WIDTH, 800);
	SetDlgItemInt(IDC_EDIT_HEIGHT, 600);

/*
const int RENDER_NORMAL = 0;
const int RENDER_TRANS = 1;
const int RENDER_ALPHA_ADD = 2;
const int RENDER_ALPHA_SOFT = 3;
const int RENDER_SHADOW = 4;
const int RENDER_DARK = 5;
const int RENDER_COLOR = 6;

const int INTF_TYPE_NORMAL = 0;
const int INTF_TYPE_BUTTON_NORMAL = 1;
const int INTF_TYPE_BUTTON_TOGGLE = 2;
const int INTF_TYPE_BUTTON_JUMP = 3;
const int INTF_TYPE_BUTTON_RADIO = 4;
const int INTF_TYPE_SCROLL_LR = 5;
const int INTF_TYPE_SCROLL_TB = 6;
const int INTF_TYPE_DIAL_LR = 7;
const int INTF_TYPE_DIAL_TB = 8;
const int INTF_TYPE_PROGRESS = 9;
const int INTF_TYPE_COLOR_BOX = 10;
const int INTF_TYPE_TEXT_IN = 11;
const int INTF_TYPE_TEXT_OUT = 12;
const int INTF_TYPE_LIST_BOX = 13;
const int INTF_TYPE_COMBO_BOX = 14;
const int INTF_TYPE_DRAG_RGN = 15;
*/
	
	m_CBIntfType.AddString("����");
	m_CBIntfType.AddString("��ư");
	m_CBIntfType.AddString("��ư - ���");
	m_CBIntfType.AddString("��ư - �̵�");
	m_CBIntfType.AddString("��ư - ����");
	m_CBIntfType.AddString("��ũ�ѹ� - �¿�");
	m_CBIntfType.AddString("��ũ�ѹ� - ����");
	m_CBIntfType.AddString("���̾� - �¿�");
	m_CBIntfType.AddString("���̾� - ����");
	m_CBIntfType.AddString("���� ��Ȳ");
	m_CBIntfType.AddString("���� - ��ĥ");
	m_CBIntfType.AddString("�ؽ�Ʈ - �Է�");
	m_CBIntfType.AddString("�ؽ�Ʈ - ���");
	m_CBIntfType.AddString("����Ʈ �ڽ�");
	m_CBIntfType.AddString("�޺� �ڽ�");
	m_CBIntfType.AddString("�巡�� ����");


	m_CBRenderType.AddString("����");
	m_CBRenderType.AddString("������");
	m_CBRenderType.AddString("Alpha Add");
	m_CBRenderType.AddString("Alpha Soft");
	m_CBRenderType.AddString("�׸���");
	m_CBRenderType.AddString("��Ӱ�");

	UpdateDlg();
	UpdateWorkWnd();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/////////////////////////////////////////////////////////////////////////////
// CDlgIntf message handlers

void CDlgIntf::AniLoad(const char* szFileName)
{
	m_pWndWork = NULL;
}

void CDlgIntf::AniNew()
{
}

void CDlgIntf::UpdateWorkWnd()
{
	if(m_pWndWork) m_pWndWork->InvalidateRect(NULL, FALSE);
}

void CDlgIntf::New()
{
	g_pIntf->New();
	UpdateDlg();
}

void CDlgIntf::OnNew() 
{
	SetDlgItemText(IDC_FILE_NAME, "");
	g_pIntf->New();

	UpdateDlg();
	UpdateWorkWnd();
}

void CDlgIntf::OnLoad() 
{
	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "int", NULL, dwFlags, "�������̽� ������(*.int)|*.int||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("DATA");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();

	g_pIntf->Load(FileName, g_pTEng->PathGetCur("ANI"), g_pTEng->PathGetCur("SPR", 1), g_pTEng->PixelFormatGet());
	
	UpdateDlg();
	UpdateWorkWnd();

	SetDlgItemText(IDC_FILE_NAME, FileName);
}

void CDlgIntf::OnSave() 
{
	CString FileName;
	GetDlgItemText(IDC_FILE_NAME, FileName);
	if(!FileName.GetLength())
	{
		OnSaveAs();
		return;
	}
	
	g_pTEng->PathSetCur("DATA");
	g_pIntf->Save(FileName);
	
	this->UpdateDlg();
	this->Refresh();
	this->UpdateWorkWnd();
}

void CDlgIntf::OnSaveAs() 
{
	CString FN; GetDlgItemText(IDC_EDIT_ANI_FILE_NAME, FN);
	if(FN.GetLength() >= 5) FN = FN.Left(FN.GetLength() - 4);

	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(FALSE, "int", FN, dwFlags, "�������̽� ������(*.int)|*.int||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("DATA");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();
	
	SetDlgItemText(IDC_FILE_NAME, FileName);

	OnSave();
}

void CDlgIntf::OnBrowseSpr() 
{
	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "spl", NULL, dwFlags, "LSP ��������Ʈ(*.spl)|*.spl||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("SPR");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();

	g_pIntf->ImportSpr(FileName, g_pTEng->PixelFormatGet()); // 8���� ��������Ʈ���� �о����..

	UpdateDlg();
	UpdateWorkWnd();
}

void CDlgIntf::OnBrowseAni() 
{
	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "ani", NULL, dwFlags, "���ϸ��̼�(*.ani)|*.ani||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("ANI");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();

	g_pIntf->ImportAni(FileName); // ���ϸ��̼� ���Ͽ��� �о����..

	UpdateDlg();
	UpdateWorkWnd();
}

void CDlgIntf::RefreshData()
{
	if(m_bUpdateInfo == TRUE) return; // ��ȭ���� ������Ʈ �߿� ������ ������Ʈ�� ���´�...
	m_bUpdateData = TRUE; // ������ ������Ʈ�� �÷��� ����

	HTREEITEM hItem = m_Tree.GetSelectedItem();
	if(hItem == NULL) return;

	HTREEITEM hIntf = NULL, hChild = NULL;
	int nNodeType = HIWORD(m_Tree.GetItemData(hItem));
	if(nNodeType == NODE_INTF)
	{
		hIntf = hItem;
		hChild = m_Tree.GetChildItem(hIntf);
	}
	else if(nNodeType == NODE_RENDER_STATE)
	{
		hIntf = m_Tree.GetParentItem(hItem);
		hChild = hItem;
	}
	else return;

	int nIntf = LOWORD(m_Tree.GetItemData(hIntf));
	_INTF_DATA* pIntf = g_pIntf->IntfGet(nIntf);
	if(pIntf == NULL) return;

	int nState = LOWORD(m_Tree.GetItemData(hChild));
	if(nState < 0 || nState >= 4) nState = 0;

	// ����� ���ϸ��̼�
	int nAni = m_AniList.GetCurSel();
	pIntf->nAnis[nState] = nAni;

	// �������̽� Ÿ��..
	pIntf->nType = m_CBIntfType.GetCurSel();
	pIntf->crFill = RGB(GetDlgItemInt(IDC_E_R), GetDlgItemInt(IDC_E_G), GetDlgItemInt(IDC_E_B));
	pIntf->crFill |= GetDlgItemInt(IDC_E_A) << 24; // alpha ��

	// �÷���
	pIntf->nFlags[0] = GetDlgItemInt(IDC_E_FLAG0);
	pIntf->nFlags[1] = GetDlgItemInt(IDC_E_FLAG1);
	pIntf->nFlags[2] = GetDlgItemInt(IDC_E_FLAG2);
	pIntf->nFlags[3] = GetDlgItemInt(IDC_E_FLAG3);

	// ���¿� ���� ������ Ÿ��(�ɼ�??)
	pIntf->nRenderTypes[nState] = m_CBRenderType.GetCurSel();

	// ä��� �� Alpha ��
	int a = GetDlgItemInt(IDC_E_A);
	int r = GetDlgItemInt(IDC_E_R);
	int g = GetDlgItemInt(IDC_E_G);
	int b = GetDlgItemInt(IDC_E_B);
	pIntf->crFill = RGB(r,g,b);
	pIntf->crFill |= a << 24;

	// ��ư���� ���� �����Ǿ�����..
	BOOL bUNI = FALSE;
	if(	(pIntf->nType >= INTF_TYPE_BUTTON_NORMAL && pIntf->nType <= INTF_TYPE_BUTTON_RADIO) == FALSE &&
		(pIntf->nType >= INTF_TYPE_BUTTON_NORMAL && pIntf->nType <= INTF_TYPE_BUTTON_RADIO) == TRUE)
	{
		for(int i = 1; i < 4; i++) pIntf->nAnis[i] = pIntf->nAnis[0];
		bUNI = TRUE; // Ʈ�� �������̽� ��� ������Ʈ �ʿ�..
	}

	// ������ ������Ʈ�� �÷��� ����
	m_bUpdateData = FALSE; 

	if(bUNI == TRUE) this->UpdateNodeIntf(NULL); // Ʈ�� �������̽� ��� ������Ʈ
}

void CDlgIntf::Refresh()
{
	if(m_bUpdateData == TRUE) return; // ������ ������Ʈ �Ǵ� �߿� �������� �� ��������...
	m_bUpdateInfo = TRUE; // ��ȭ���� ������Ʈ�� �÷��� ����

	HTREEITEM hItem = m_Tree.GetSelectedItem();
	if(hItem == NULL) return;

	HTREEITEM hChild = NULL;
	int nNodeType = HIWORD(m_Tree.GetItemData(hItem));
	if(nNodeType == NODE_INTF) hChild = m_Tree.GetChildItem(hItem);
	else if(nNodeType == NODE_RENDER_STATE)
	{
		hChild = hItem;
		hItem = m_Tree.GetParentItem(hItem); // �������̽� ��� �ڵ��� ����Ű�� �Ѵ�.
	}
	else return;

	int nIntf = LOWORD(m_Tree.GetItemData(hItem));
	_INTF_DATA* pIntf = g_pIntf->IntfGet(nIntf);
	if(pIntf == NULL) return;

	// Ŀ�� ��Ȳ ��ġ�� ���� ���ϸ��̼� ��ȣ �� �̸�ǥ��
	int nStatus = LOWORD(m_Tree.GetItemData(hChild));
	if(nStatus < 0 || nStatus >= 4) nStatus = 0;

	m_CBIntfType.SetCurSel(pIntf->nType); // �������̽� Ÿ��
	m_CBRenderType.SetCurSel(pIntf->nRenderTypes[nStatus]); // ������ Ÿ��..
	
	SetDlgItemInt(IDC_E_FLAG0, pIntf->nFlags[0]); // �÷���
	SetDlgItemInt(IDC_E_FLAG1, pIntf->nFlags[1]);
	SetDlgItemInt(IDC_E_FLAG2, pIntf->nFlags[2]);
	SetDlgItemInt(IDC_E_FLAG3, pIntf->nFlags[3]);

	SetDlgItemInt(IDC_E_A, pIntf->crFill >> 24); // ä��� �� ����..
	SetDlgItemInt(IDC_E_R, (pIntf->crFill & 0x00ff0000) >> 16);
	SetDlgItemInt(IDC_E_G, (pIntf->crFill & 0x0000ff00) >> 8);
	SetDlgItemInt(IDC_E_B, pIntf->crFill & 0x000000ff);

	m_AniList.SetCurSel(pIntf->nAnis[nStatus]);

	m_bUpdateInfo = FALSE; // ��ȭ���� ������Ʈ�� �÷��� ����
}

void CDlgIntf::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 0: // Animation..
		UpdateWorkWnd();
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgIntf::OnCViewBkg() 
{
	UpdateWorkWnd();
}

void CDlgIntf::OnCViewTrans() 
{
	UpdateWorkWnd();	
}

void CDlgIntf::OnCViewZoom() 
{
	UpdateWorkWnd();
}

void CDlgIntf::OnCViewLine() 
{
	UpdateWorkWnd();
}

void CDlgIntf::OnCPlayAnimation() 
{
	if(m_CPlayAnimation.GetCheck())
		SetTimer(0, 20, NULL);
	else KillTimer(0);
}

void CDlgIntf::UpdateDlg()
{
	// ��������Ʈ �̸��� ���ϸ��̼� �̸��� ����
	SetDlgItemText(IDC_EDIT_SPR_FILE_NAME, g_pIntf->m_Header.szSprFN);
	SetDlgItemText(IDC_EDIT_ANI_FILE_NAME, g_pIntf->m_Header.szAniFN);

	SetDlgItemInt(IDC_EDIT_WIDTH, g_pIntf->m_Header.rcWhole.right);
	SetDlgItemInt(IDC_EDIT_HEIGHT, g_pIntf->m_Header.rcWhole.bottom);

	// ���� �����ͷ� Ʈ���� �����Ѵ�..
	UpdateTreeByData();

	// ���ϸ��̼� ����Ʈ ����
	m_AniList.ResetContent();
	int nAniQt = g_pIntf->AniObjGet()->m_HAni.nQt;
	
	_ANI_DATA* pAni;
	CString str;
	for(int i = 0; i < nAniQt; i++)
	{
		pAni = g_pIntf->AniObjGet()->AniDataGet(i);
		if(pAni == NULL) continue;
		if(lstrlen(pAni->szName)) str.Format("%3d : %s", i, pAni->szName);
		else str.Format("%3d : �̸� ����", i);
		m_AniList.AddString(str);
	}

	Refresh();
}

void CDlgIntf::OnRclickTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	CPoint point;
	GetCursorPos(&point);
	m_Tree.ScreenToClient(&point);
	HTREEITEM hItem = m_Tree.HitTest(point);
	if(hItem == NULL) return;
	
	HTREEITEM hRoot = m_Tree.GetRootItem();
	HTREEITEM hParent = m_Tree.GetParentItem(hItem);
	int nItem = HIWORD(m_Tree.GetItemData(hItem));
	
	m_Tree.SelectItem(hItem); // ����

	CMenu popup;
	popup.LoadMenu(IDM_POPUP_INTF);
	CMenu* pSubMenu = popup.GetSubMenu(0);
		
	if(hItem == hRoot) // �������� ��Ʈ�̸�..
	{
		// ���̾� �߰� �޴��� ��Ÿ���� �Ѵ�..
		pSubMenu = pSubMenu->GetSubMenu(0);
		m_Tree.ClientToScreen(&point);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	else if(nItem == NODE_LAYER) // �������� ���̾��̸�
	{
		// ���̾� �߰�, ����, ����, �������̽� �߰��޴��� ��Ÿ���� �Ѵ�..
		pSubMenu = pSubMenu->GetSubMenu(1);
		m_Tree.ClientToScreen(&point);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
	else if(nItem == NODE_INTF) // �������� �������̽� �׸��̸�...
	{
		// �������̽� �߰�, ����, ����, ���� �׸� ��Ÿ���� �Ѵ�..
		pSubMenu = pSubMenu->GetSubMenu(2);
		m_Tree.ClientToScreen(&point);
		pSubMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}

	*pResult = 0;
}

void CDlgIntf::OnKeydownTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_KEYDOWN* pTVKeyDown = (TV_KEYDOWN*)pNMHDR;
	
	int nKey = pTVKeyDown->wVKey;
	UINT nFlags = pTVKeyDown->flags;

	HTREEITEM hRoot = m_Tree.GetRootItem();
	HTREEITEM hItem = m_Tree.GetSelectedItem();
	if(hItem == NULL) return;
	int nNodeType = HIWORD(m_Tree.GetItemData(hItem));

	switch(nKey)
	{
	case VK_ADD:
		if(nNodeType == NODE_LAYER || nNodeType == NODE_INTF)
			OnMenuIntfAdd();
		else if(hItem == hRoot)
			OnMenuLayerAdd();
		break;
	case VK_INSERT:
		if(nNodeType == NODE_INTF)
			OnMenuIntfInsert();
		else if(nNodeType == NODE_LAYER)
			OnMenuLayerInsert();
		break;
	case VK_DELETE:
		if(nNodeType == NODE_INTF)
			OnMenuIntfDelete();
		else if(nNodeType == NODE_LAYER)
			OnMenuLayerDelete();
		break;
	case VK_F2:
		if(nNodeType == NODE_LAYER)
			m_Tree.EditLabel(hItem);
		break;
	case VK_RETURN:
		if(nNodeType == NODE_LAYER)
			m_Tree.SelectItem(hItem);
		break;
	}

	*pResult = 0;
}

void CDlgIntf::OnEndlabeleditTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;

	CString str = pTVDispInfo->item.pszText;
	HTREEITEM hItem = pTVDispInfo->item.hItem;

	if(hItem == NULL || str.GetLength() <= 0)
	{
		*pResult = TRUE;  // �� ���� ���
		return;
	}

	int nNodeType = HIWORD(m_Tree.GetItemData(hItem));
	if(nNodeType == NODE_LAYER) // ��尡 ���̾��..
	{
		char szTemp[128]; int nTemp = 0; // ���ڿ��� ��ȯ...
		lstrcpy(szTemp, str);
		for(int i = 0; i < str.GetLength(); i++)
			if(str[i] >= '0' && str[i] <= '9') szTemp[nTemp++] = str[i];
		szTemp[nTemp] = NULL;
		int nLayer = atoi(szTemp); // ���ڿ����� ���ڸ� ����..

		BOOL bOverLapLayer = FALSE; // �ߺ��Ǵ� ���̾� ��ȣ�� �ִ��� ���캻��..
		HTREEITEM hRoot = m_Tree.GetRootItem(); // Ʈ���� ���鼭 ��ȿ�� �������̽� ��ȣ ����Ʈ�� �̴´�.
		HTREEITEM hLayer;
		hLayer = m_Tree.GetChildItem(hRoot); // ���̾� ���..
		while(hLayer)
		{
			int nTmp = LOWORD(m_Tree.GetItemData(hLayer)); // �����ۿ� ����� ���̾� ��ȣ ��������...
			if(hItem != hLayer) // ���� �Ͱ� �������� ���̾� �϶�..
			{
				if(nLayer == nTmp)
				{
					bOverLapLayer = TRUE; // �ߺ�..
					break;
				}
			}
			hLayer = m_Tree.GetNextSiblingItem(hLayer); // ���� ��� ��������..
		}

		if(nLayer < 0 || nLayer >= MAX_LAYER || bOverLapLayer == TRUE)
		{
			MessageBox("���ڿ� ���� ���̾� ��ȣ�� �ߺ��ǰų� �߸��Ǿ� �ֽ��ϴ�.");
		}
		else
		{
			HTREEITEM hIntf = m_Tree.GetChildItem(hItem); // �������̽� ���..
			while(hIntf) // �ڽ� ���(�������̽� ���) ���̾� ���� �ٲٱ�..
			{
				int nIntf = LOWORD(m_Tree.GetItemData(hIntf)); // �������̽� �� ��������..
				_INTF_DATA* pIntf = g_pIntf->IntfGet(nIntf);
				if(pIntf)
				{
					pIntf->nParentLayer = nLayer;
				}

				hIntf = m_Tree.GetNextSiblingItem(hIntf); // ���� ��� ��������..
			}
			str.Format("���̾� %2d", nLayer);
			m_Tree.SetItemText(hItem, str); // ���ڿ� �ٲٱ�..
			m_Tree.SetItemData(hItem, MAKELPARAM(nLayer, NODE_LAYER));
		}
	}
	else if(nNodeType == NODE_INTF)
	{
		int nIntf = LOWORD(m_Tree.GetItemData(hItem));
		_INTF_DATA* pIntf = g_pIntf->IntfGet(nIntf);
		if(pIntf == NULL) *pResult = TRUE; // ���..
		else
		{
			lstrcpy(pIntf->szName, str); // �̸� �ٲٰ� 
			
			this->UpdateNodeIntf(hItem); // Ʈ�� ��� ������Ʈ
		}
	}
	*pResult = 0;
}

void CDlgIntf::OnBeginlabeleditTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	TV_DISPINFO* pTVDispInfo = (TV_DISPINFO*)pNMHDR;
	// TODO: Add your control notification handler code here
	HTREEITEM hItem = pTVDispInfo->item.hItem;

	*pResult = TRUE; // �䷸�� �ϸ� ���� �������..!!

	if(hItem == NULL) return;
	int nNodeType = HIWORD(m_Tree.GetItemData(hItem));
	if(nNodeType != NODE_LAYER && nNodeType != NODE_INTF) return; // ��尡 ���̾ �������̽��� �ƴϸ� ���ư���..
	
	*pResult = 0;
}

void CDlgIntf::OnMenuLayerAdd() 
{
	HTREEITEM hRoot = m_Tree.GetRootItem();
	if(hRoot == NULL) return;
	
	CString str = "���̾� - ��ȣ ������ �ּ���";
	HTREEITEM hLayer = m_Tree.InsertItem(str, hRoot, TVI_LAST);
	m_Tree.SetItemData(hLayer, MAKELPARAM(-1, NODE_LAYER));
	m_Tree.Expand(hRoot, TVE_EXPAND);
	m_Tree.SelectItem(hLayer);
}

void CDlgIntf::OnMenuLayerInsert() 
{
	HTREEITEM hLayer = m_Tree.GetSelectedItem();
	if(hLayer == NULL) return;
	int nNodeType = HIWORD(m_Tree.GetItemData(hLayer));
	HTREEITEM hRoot = m_Tree.GetRootItem();

	if(nNodeType != NODE_LAYER) return;
	
	CString str = "���̾� - ��ȣ ������ �ּ���";
	hLayer = m_Tree.InsertItem(str, hRoot, hLayer);
	m_Tree.SetItemData(hLayer, MAKELPARAM(-1, NODE_LAYER));
	m_Tree.Expand(hRoot, TVE_EXPAND);
	m_Tree.SelectItem(hLayer);
}

void CDlgIntf::OnMenuLayerDelete()
{
	HTREEITEM hLayer = m_Tree.GetSelectedItem();
	if(hLayer == NULL) return;

	int nNodeType = HIWORD(m_Tree.GetItemData(hLayer));
	if(nNodeType != NODE_LAYER) return;

	HTREEITEM hIntf = m_Tree.GetChildItem(hLayer);
	while(hIntf) // ���� �����..
	{
		HTREEITEM hTmp = hIntf;
		int nIntf = LOWORD(m_Tree.GetItemData(hIntf));
		g_pIntf->Delete(nIntf);
		hIntf = m_Tree.GetNextSiblingItem(hIntf);
		m_Tree.DeleteItem(hTmp);
	}
	
	m_Tree.DeleteItem(hLayer); // ���̾� ��� �����..
}

// �������̽� �߰�
void CDlgIntf::OnMenuIntfAdd() 
{
	HTREEITEM hLayer = m_Tree.GetSelectedItem();
	if(hLayer == NULL) return;

	int nNodeType = HIWORD(m_Tree.GetItemData(hLayer));

	if(nNodeType == NODE_INTF) hLayer = m_Tree.GetParentItem(hLayer);
	else if(nNodeType == NODE_LAYER) hLayer = hLayer;
	else return;

	int nIntf = g_pIntf->Add();
	if(nIntf < 0 || nIntf >= MAX_INTF) return; // ���� �Ҵ翡 ����

	CString str; str.Format("�������̽� - %3d", nIntf);
	HTREEITEM hIntf = m_Tree.InsertItem(str, hLayer, TVI_LAST);
	m_Tree.SetItemData(hIntf, MAKELPARAM(nIntf, NODE_INTF));

	this->UpdateNodeIntf(hIntf);
	m_Tree.Expand(hLayer, TVE_EXPAND);
	m_Tree.SelectItem(hIntf); // ����

	int nLayer = LOWORD(m_Tree.GetItemData(hLayer));
	_INTF_DATA* pIntf = g_pIntf->IntfGet(nIntf);
	if(pIntf)
	{
		pIntf->nParentLayer = nLayer;  // �������̽��� ���̾� ��ȣ ���..
	}
	else
	{
		MessageBox("�������̽� �߰��� ����. �����Ͻð�  �ٽ� �ҷ��� �۾��� �ּ���.", MB_OK);
		return;
	}
}

// �������̽� ����
void CDlgIntf::OnMenuIntfInsert() 
{
	HTREEITEM hItem = m_Tree.GetSelectedItem();
	if(hItem == NULL) return;

	int nNodeType = HIWORD(m_Tree.GetItemData(hItem));

	if(nNodeType != NODE_INTF) return;

	int nIntf = g_pIntf->Add(); // �������̽� �߰��� ��ȣ�� �޾ƿ� ��������� �ִ´�.
	HTREEITEM hParent = m_Tree.GetParentItem(hItem);
	CString str; str.Format("�������̽� - %3d", nIntf);
	HTREEITEM hIntf = m_Tree.InsertItem(str, hParent, hItem);
	m_Tree.SetItemData(hIntf, MAKELPARAM(nIntf, NODE_INTF));

	int nLayer = LOWORD(m_Tree.GetItemData(hParent));

	// �������̽��� ���̾� ��ȣ ���..
	_INTF_DATA* pIntf = g_pIntf->IntfGet(nIntf);
	if(pIntf)
	{
		pIntf->nParentLayer = nLayer;
	}
	else
	{
		MessageBox("�������̽� �߰��� ����. �����Ͻð�  �ٽ� �ҷ��� �۾��� �ּ���.", MB_OK);
		return;
	}

	this->UpdateNodeIntf(hIntf);
	m_Tree.SelectItem(hIntf); // ����
}

// �������̽� ����
void CDlgIntf::OnMenuIntfDelete() 
{
	HTREEITEM hIntf = m_Tree.GetSelectedItem();
	if(hIntf == NULL) return;
	int nNodeType = HIWORD(m_Tree.GetItemData(hIntf));

	if(nNodeType != NODE_INTF) return;
	
	int nIntf = LOWORD(m_Tree.GetItemData(hIntf));
	g_pIntf->Delete(nIntf);
	
	m_Tree.DeleteItem(hIntf); // �������̽� ������ ����..
}

void CDlgIntf::OnMenuIntfCopy() 
{
	HTREEITEM hItem = m_Tree.GetSelectedItem();
	if(hItem == NULL) return;

	int nNodeType = HIWORD(m_Tree.GetItemData(hItem));
	g_pIntf->ClipBoardClear(); // Ŭ������ �����..
	
	if(nNodeType == NODE_INTF) // ���̾� ī��
	{
		int nIntf = LOWORD(m_Tree.GetItemData(hItem));
		g_pIntf->ClipBoardAdd(nIntf);
	}
	else if(nNodeType == NODE_LAYER)
	{
		HTREEITEM hIntf = m_Tree.GetChildItem(hItem);
		while(hIntf)
		{
			int nIntf = LOWORD(m_Tree.GetItemData(hIntf));
			g_pIntf->ClipBoardAdd(nIntf);
			hIntf = m_Tree.GetNextSiblingItem(hIntf);
		}
	}
	else return;

	Refresh();
	UpdateWorkWnd();
}

void CDlgIntf::OnMenuIntfPaste() 
{
	HTREEITEM hItem = m_Tree.GetSelectedItem();
	if(hItem == NULL) return;
	int nNodeType = HIWORD(m_Tree.GetItemData(hItem));

	int nIntf = this->IntfGetValid();
	int nLayer = this->LayerGetValid();

	if(nNodeType == NODE_INTF) // ���̾� ī��
	{
		g_pIntf->ClipBoardPaste(nIntf, 0, nLayer);

		HTREEITEM hIntf = hItem;
		this->UpdateNodeIntf(hIntf); // �������̽� ��� ������Ʈ
		m_Tree.Expand(hIntf, TVE_EXPAND);
	}
	else if(nNodeType == NODE_LAYER)
	{
		HTREEITEM hLayer = hItem;
		HTREEITEM hIntf = m_Tree.GetChildItem(hItem);
		while(hIntf) // ���� �����..
		{
			HTREEITEM hTmp = hIntf;
			nIntf = LOWORD(m_Tree.GetItemData(hIntf));
			g_pIntf->Delete(nIntf); // �����..
			hIntf = m_Tree.GetNextSiblingItem(hIntf);
		}

		int nClipQt = g_pIntf->ClipBoardGetQt();
		for(int i = 0; i < nClipQt; i++)
		{
			nIntf = g_pIntf->Add();
			g_pIntf->ClipBoardPaste(nIntf, i, nLayer);
			hIntf = m_Tree.InsertItem("", hLayer, TVI_LAST);
			m_Tree.SetItemData(hIntf, MAKELPARAM(nIntf, NODE_INTF));
			this->UpdateNodeIntf(hIntf); // �������̽� ��� ������Ʈ
		}
		
		m_Tree.Expand(hItem, TVE_EXPAND);
	}
	else return;

	Refresh();
	UpdateWorkWnd();
}

void CDlgIntf::OnSelchangedTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	HTREEITEM hItem = pNMTreeView->itemNew.hItem;
	if(hItem == NULL) return;

	int nNodeType = HIWORD(m_Tree.GetItemData(hItem));
	if(nNodeType != NODE_LAYER && nNodeType != NODE_INTF && nNodeType != NODE_RENDER_STATE) return;

	Refresh();
	UpdateWorkWnd();

	*pResult = 0;
	
}

void CDlgIntf::OnSelchangeAniList() 
{
	int nSel = m_AniList.GetCurSel();
	if(nSel == CB_ERR) return;

	HTREEITEM hIntf = m_Tree.GetSelectedItem();
	if(hIntf == NULL) return;

	int nNodeType = HIWORD(m_Tree.GetItemData(hIntf));

	HTREEITEM hChild = NULL;
	if(nNodeType == NODE_INTF) hChild = m_Tree.GetChildItem(hIntf); // �������̽� ���
	else if(nNodeType == NODE_RENDER_STATE)
	{
		hChild = hIntf;
		hIntf = m_Tree.GetParentItem(hIntf); // ����� ��� - �θ� ���� �ٲ۴�..!!
	}
	else return;

	RefreshData();
	this->UpdateNodeIntf(hIntf);

	Refresh();
	UpdateWorkWnd();
}

int CDlgIntf::GetRenderStatus()
{
	HTREEITEM hItem = m_Tree.GetSelectedItem();
	if(hItem == NULL) return 0;

	int nNodeType = HIWORD(m_Tree.GetItemData(hItem));
	
	if(nNodeType == NODE_RENDER_STATE) return LOWORD(m_Tree.GetItemData(hItem));
	else return 0;
}

// ���� Ʈ������ ���õǾ� �ִ� ���̾� ��ȣ�� �����´�.. �����ϸ� -1..
int CDlgIntf::LayerGetValid()
{
	HTREEITEM hRoot = m_Tree.GetRootItem();
	HTREEITEM hItem = m_Tree.GetSelectedItem();

	if(hItem == NULL || hItem == hRoot) return -1;
	
	int nNodeType = 0;
	while(nNodeType != NODE_LAYER && hItem)
	{
		nNodeType = HIWORD(m_Tree.GetItemData(hItem)); // ��� Ÿ�� ��������..
		hItem = m_Tree.GetParentItem(hItem);
	}
	if(hItem) return LOWORD(m_Tree.GetItemData(hItem));
	else return -1;
}

int CDlgIntf::IntfGetValid()
{
	HTREEITEM hIntf = m_Tree.GetSelectedItem();
	if(hIntf == NULL) return -1;
	
	int nNodeType = HIWORD(m_Tree.GetItemData(hIntf)); // ��� Ÿ�� ��������..
	if(nNodeType == NODE_INTF) hIntf = hIntf;
	else if(nNodeType == NODE_RENDER_STATE) hIntf = m_Tree.GetParentItem(hIntf);
	else return -1;

	return LOWORD(m_Tree.GetItemData(hIntf));
}

// ���� ���̾ �����ִ� �������̽� ������ �����´�..
int CDlgIntf::IntfGetValidQt()
{
	HTREEITEM hLayer = m_Tree.GetSelectedItem();
	if(hLayer == NULL) return -1;
	
	int nNodeType = HIWORD(m_Tree.GetItemData(hLayer)); // ��� Ÿ�� ��������..
	if(nNodeType == NODE_LAYER) hLayer = hLayer;
	else if(nNodeType == NODE_INTF) hLayer = m_Tree.GetParentItem(hLayer);
	else if(nNodeType == NODE_RENDER_STATE)
	{
		hLayer = m_Tree.GetParentItem(hLayer);
		hLayer = m_Tree.GetParentItem(hLayer);
	}
	else return -1;

	HTREEITEM hIntf = m_Tree.GetChildItem(hLayer);
	int nIntfQt = 0;
	while(hIntf) // ���� ���� ����..
	{
		nIntfQt++;
		hIntf = m_Tree.GetNextSiblingItem(hIntf);
	}
	return nIntfQt;
}

// ���� ���̾ �����ִ� �������̽� �ε����� �����´�..
BOOL CDlgIntf::IntfGetValidIndex(int index, int* pnIntf, int* pnState)
{
	if(index < 0 || index >= MAX_INTF) return FALSE;
	if(pnIntf == NULL || pnState == NULL) return FALSE;

	*pnIntf = -1;
	*pnState = 0;

	HTREEITEM hLayer = m_Tree.GetSelectedItem();
	if(hLayer == NULL) return -1;
	
	int nNodeType = HIWORD(m_Tree.GetItemData(hLayer)); // ��� Ÿ�� ��������..
	if(nNodeType == NODE_LAYER) hLayer = hLayer;
	else if(nNodeType == NODE_INTF) hLayer = m_Tree.GetParentItem(hLayer);
	else if(nNodeType == NODE_RENDER_STATE)
	{
		*pnState = LOWORD(m_Tree.GetItemData(hLayer)); // ���ϵ�..
		hLayer = m_Tree.GetParentItem(hLayer);
		hLayer = m_Tree.GetParentItem(hLayer);
	}
	else return FALSE;

	HTREEITEM hIntf = m_Tree.GetChildItem(hLayer);
	for(int i = 0; i < index; i++)
	{
		if(hIntf == NULL) return FALSE;
		hIntf = m_Tree.GetNextSiblingItem(hIntf);
	}
	*pnIntf = LOWORD(m_Tree.GetItemData(hIntf));

	return TRUE;
}

int CDlgIntf::IntfGetValidCheck(int index)
{
	if(index < 0 || index >= MAX_INTF) return 0;

	HTREEITEM hLayer = m_Tree.GetSelectedItem();
	if(hLayer == NULL) return 0;
	
	int nNodeType = HIWORD(m_Tree.GetItemData(hLayer)); // ��� Ÿ�� ��������..
	if(nNodeType == NODE_LAYER) hLayer = hLayer;
	else if(nNodeType == NODE_INTF) hLayer = m_Tree.GetParentItem(hLayer);
	else if(nNodeType == NODE_RENDER_STATE)
	{
		hLayer = m_Tree.GetParentItem(hLayer);
		hLayer = m_Tree.GetParentItem(hLayer);
	}
	else return 0;

	HTREEITEM hIntf = m_Tree.GetChildItem(hLayer);
	for(int i = 0; i < index; i++)
	{
		if(hIntf == NULL) return 0;
		hIntf = m_Tree.GetNextSiblingItem(hIntf);
	}
	return m_Tree.GetCheck(hIntf);
}

// Ʈ���� ������ �������̽� ��ȣ�� ��ġ�ϸ� ����...
void CDlgIntf::IntfSetValid(int nIntf)
{
	HTREEITEM hRoot = m_Tree.GetRootItem();
	
	HTREEITEM hLayer = m_Tree.GetChildItem(hRoot);
	while(hLayer)
	{
		HTREEITEM hIntf = m_Tree.GetChildItem(hLayer);
		while(hIntf)
		{
			int tmp = LOWORD(m_Tree.GetItemData(hIntf));
			if(tmp == nIntf)
			{
				m_Tree.SelectItem(hIntf);
				return;
			}
			hIntf = m_Tree.GetNextSiblingItem(hIntf);
		}
		hLayer = m_Tree.GetNextSiblingItem(hLayer);
	}
}

// ���� �����͸� ������ Ʈ���� �����Ѵ�.
void CDlgIntf::UpdateTreeByData()
{
	CString FileName;
	GetDlgItemText(IDC_FILE_NAME, FileName);
	if(FileName.GetLength() <= 0) FileName = "���� ����";

	// Ʈ�� ����
	m_Tree.DeleteAllItems();
	
	BOOL bLayers[MAX_LAYER]; MAKE_ZERO(bLayers);
	HTREEITEM hR = m_Tree.InsertItem(FileName, TVI_ROOT, TVI_LAST);
	HTREEITEM hRoot = m_Tree.GetRootItem();
	HTREEITEM hLayers[MAX_LAYER]; MAKE_ZERO(hLayers);
	
	CString str;
	for(int i = 0 ; i < MAX_INTF; i++)
	{
		_INTF_DATA* pIntf = g_pIntf->IntfGet(i);
		if(pIntf == NULL) continue; // ������ �������� ����

		int nLayer = pIntf->nParentLayer;
		if(nLayer < 0 || nLayer >= MAX_LAYER)
		{
			CString str; str.Format("%d��° �������̽� - ���̾� ��ȣ : %d", i, nLayer);
			MessageBox(str, "�߸��� �������̽� ������ ����");
		}
		else
		{
			if(bLayers[nLayer] == TRUE) // �̹� ���̾� ��� ������ ���...
			{
			}
			else // ���̾� ��� ÷ �����ϴ� ���
			{
				CString str;
				str.Format("���̾� %d", nLayer);
				hLayers[nLayer] = m_Tree.InsertItem(str, hRoot, TVI_LAST);
				m_Tree.SetItemData(hLayers[nLayer], MAKELPARAM(nLayer, NODE_LAYER));
			}
			bLayers[nLayer] = TRUE;
			
			// �������̽� ��� ����..
			str.Format("%3d", i);
			HTREEITEM hIntf = m_Tree.InsertItem(str, hLayers[nLayer], TVI_LAST);
			m_Tree.SetItemData(hIntf, MAKELPARAM(i, NODE_INTF)); // �������̽� ��忡 �������̽� ��ȣ ���̱�..

			this->UpdateNodeIntf(hIntf);
		}
	}
	m_Tree.Expand(hRoot, TVE_EXPAND); // Ʈ�� �� ���..
}

void CDlgIntf::OnBegindragTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}

void CDlgIntf::OnClickTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	Refresh();
	UpdateWorkWnd();
	*pResult = 0;
}

void CDlgIntf::OnChangeEditWidth() 
{
	g_pIntf->m_Header.rcWhole.left = 0;
	g_pIntf->m_Header.rcWhole.right = GetDlgItemInt(IDC_EDIT_WIDTH);
	UpdateWorkWnd();
}

void CDlgIntf::OnChangeEditHeight() 
{
	g_pIntf->m_Header.rcWhole.top = 0;
	g_pIntf->m_Header.rcWhole.bottom = GetDlgItemInt(IDC_EDIT_HEIGHT);
	UpdateWorkWnd();
}

void CDlgIntf::UpdateNodeIntf(HTREEITEM hIntf)
{
	if(hIntf == NULL) hIntf = m_Tree.GetSelectedItem(); // ���̸� ���� ���õ� ��带 �����´�..
	if(hIntf == NULL) return;

	int nNodeType = HIWORD(m_Tree.GetItemData(hIntf));
	
	if(nNodeType == NODE_INTF) hIntf = hIntf;
	else if(nNodeType == NODE_RENDER_STATE) hIntf = m_Tree.GetParentItem(hIntf);
	else return;

	int nIntf = LOWORD(m_Tree.GetItemData(hIntf));
	_INTF_DATA* pIntf = g_pIntf->IntfGet(nIntf);
	if(pIntf == NULL) return;

	// �������̽� ���� ��忡 �̸� ���̱�..
	CString szChilds[4];
	CString szTmps[4];
	szTmps[0] = "���-%d:%s";
	szTmps[1] = "Ŀ��-%d:%s";
	szTmps[2] = "Ŭ��-%d:%s";
	szTmps[3] = "����-%d:%s";
	for(int i = 0; i < 4; i++)
	{
		_ANI_DATA* pAni = g_pIntf->AniObjGet()->AniDataGet(pIntf->nAnis[i]);
		if(pAni == NULL) szChilds[i].Format(szTmps[i], pIntf->nAnis[i], "����! ���ϸ��̼� ����");
		else szChilds[i].Format(szTmps[i], pIntf->nAnis[i], pAni->szName);
	}
	
	HTREEITEM hChild = m_Tree.GetChildItem(hIntf);
	if(hChild == NULL) // ���� �����ϴ� ���
	{
		for(i = 0; i < 4; i++)
		{
			HTREEITEM hChild = m_Tree.InsertItem(szChilds[i], hIntf, TVI_LAST);
			m_Tree.SetItemData(hChild, MAKELPARAM(i, NODE_RENDER_STATE));
		}
	}
	else // �̹� �ִ� ���
	{
		for(i = 0; i < 4; i++)
		{
			if(i == 0) hChild = m_Tree.GetChildItem(hIntf);
			else hChild = m_Tree.GetNextSiblingItem(hChild);
			m_Tree.SetItemData(hChild, MAKELPARAM(i, NODE_RENDER_STATE));
			m_Tree.SetItemText(hChild, szChilds[i]);
		}
	}

	// �������̽� ��� �̸� ���̱�..
	CString szName = pIntf->szName;
	if(szName.GetLength() <= 0) szName = "�̸�����";

	CString szInfo;
	_ANI_DATA* pAni = g_pIntf->AniObjGet()->AniDataGet(pIntf->nAnis[0]);
	if(pAni == NULL) szInfo.Format("%s-%d(%d:����! ���ϸ��̼� ����)", szName, nIntf, pIntf->nAnis[0]);
	else szInfo.Format("%s-%d(%d:%s)", szName, nIntf, pIntf->nAnis[0], pAni->szName);
	
	m_Tree.SetItemText(hIntf, szInfo);
}

void CDlgIntf::OnOK()
{
}

void CDlgIntf::OnCancel()
{
}

void CDlgIntf::OnBBrowseBkg() 
{
	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "bmp", NULL, dwFlags, "bmp files(*.bmp;*.obm)|*.bmp;*.obm||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("BMP");

	if(dlg.DoModal() == IDCANCEL) return;
	
	FileName = dlg.GetFileName();

	UpdateWorkWnd();
}

void CDlgIntf::OnSelchangeCbIntfType() 
{
	this->RefreshData();
	this->UpdateWorkWnd();
}

void CDlgIntf::OnChangeEFlag0() 
{
	this->RefreshData();
	this->UpdateWorkWnd();
}

void CDlgIntf::OnChangeEFlag1() 
{
	this->RefreshData();
	this->UpdateWorkWnd();
}

void CDlgIntf::OnChangeEFlag2() 
{
	this->RefreshData();
	this->UpdateWorkWnd();
}

void CDlgIntf::OnChangeEFlag3() 
{
	this->RefreshData();
	this->UpdateWorkWnd();
}

void CDlgIntf::OnSelchangeCbRenderType() 
{
	this->RefreshData();
	this->UpdateWorkWnd();
}

void CDlgIntf::OnChangeEA() 
{
	this->RefreshData();
	this->UpdateWorkWnd();
}

void CDlgIntf::OnChangeER() 
{
	this->RefreshData();
	this->UpdateWorkWnd();
}

void CDlgIntf::OnChangeEG() 
{
	this->RefreshData();
	this->UpdateWorkWnd();
}

void CDlgIntf::OnChangeEB() 
{
	this->RefreshData();
	this->UpdateWorkWnd();
}

void CDlgIntf::OnCViewOutline() 
{
	this->UpdateWorkWnd();
}
