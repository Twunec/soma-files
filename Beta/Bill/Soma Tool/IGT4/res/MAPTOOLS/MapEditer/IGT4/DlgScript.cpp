// DlgScript.cpp : implementation file
//

#include "StdAfx.h"
#include "DlgScript.h"
#include "GlobalVar.h"

CDlgScript::CDlgScript(CWnd* pParent) : CDialog(CDlgScript::IDD)
{
	//{{AFX_DATA_INIT(CDlgScript)
	//}}AFX_DATA_INIT

	for(int i = 0; i < MAX_SCT_COMMAND; i++)
	{
		m_nSC[i] = 0;
		m_SC[i] = "";
		m_SD[i] = "";
	}

	int n = 0;
	n=0; m_nSC[n] = SCT_TALK;				m_SC[n] = "��ȭ";				m_SD[n] = "(Text - ��系�� F1 - ĳ���� ��ȣ F2 - �÷���(0:ǳ��,1:��ȭâ,2:�޽���â,4:��ũ�� ����,8:�ʿ�����,16:������ĳ���Ϳ� ����)";

	n++; m_nSC[n] = SCT_IMAGE_OUTPUT;		m_SC[n] = "�׸� ���";			m_SD[n] = "(Text - ��Ʈ�� ���� �̸� | PT1 - ��ġ";
	n++; m_nSC[n] = SCT_AVI_PLAY;			m_SC[n] = "������ ���";		m_SD[n] = "(Text - ���� �̸�, RC1:�����ġ(0,0,0,0 �̸� ��üȭ�� ���))";

	n++; m_nSC[n] = SCT_LOAD;				m_SC[n] = "�θ���";				m_SD[n] = "(Text - ��ũ��Ʈ ���� �̸�)";
	n++; m_nSC[n] = SCT_GAME_PAUSE;			m_SC[n] = "���� ��� ����"; 	m_SD[n] = "(F1 - 0:�ð�, 1:���콺 Ŭ���Ҷ����� Time - �ð��� ��� mSec���� �ð�, 2:������ ����)";
	n++; m_nSC[n] = SCT_GAME_RESUME;		m_SC[n] = "���� �ٽ� ����";		m_SD[n] = "�μ� ����";
	n++; m_nSC[n] = SCT_PAUSE;				m_SC[n] = "��ũ��Ʈ ��� ����"; m_SD[n] = "(F1 - 0:�ð�, 1:���콺 Ŭ���Ҷ����� Time - �ð��� ��� mSec���� �ð�, 2:������ ����)";
	n++; m_nSC[n] = SCT_RESUME;				m_SC[n] = "��ũ��Ʈ �ٽ� ����";	m_SD[n] = "�μ� ����";
	n++; m_nSC[n] = SCT_END;				m_SC[n] = "��";					m_SD[n] = "�μ� ����";

	n++; m_nSC[n] = SCT_JUMP;				m_SC[n] = "����";				m_SD[n] = "(F1 - ��ũ��Ʈ �Ϸù�ȣ)";
	n++; m_nSC[n] = SCT_JUMP_RANDOM;		m_SC[n] = "���� ����";			m_SD[n] = "(F1 - ��ũ��Ʈ �Ϸù�ȣ, F2 - ��ũ��Ʈ �Ϸù�ȣ, F3 - ��ũ��Ʈ �Ϸù�ȣ)";
	n++; m_nSC[n] = SCT_JUMP_IF;			m_SC[n] = "���Ǻ�����";			m_SD[n] = "(F1 - �Ǵ��� �ٰŰ� �Ǵ� �������� | F2 - ���϶� ������ ��ũ��Ʈ �Ϸù�ȣ | F2 - �����϶� ������ ��ũ��Ʈ �Ϸù�ȣ)";
	n++; m_nSC[n] = SCT_SET_GLOBAL_VAR;		m_SC[n] = "�������� ����";		m_SD[n] = "(F1 - �������� ��ȣ | F2 - ��,����)";

	n++; m_nSC[n] = SCT_SOUND_PLAY;			m_SC[n] = "���� ���"; 			m_SD[n] = "���� ��� Text - ���� �̸� | F1- 0:�ӽ�ä�����, 1:��Ʈ����ä�� | F2- 0:����, 1:�ѹ���";
	n++; m_nSC[n] = SCT_SOUND_STOP;			m_SC[n] = "���� ����";			m_SD[n] = "F1- 0:�ӽ�ä��, 1:��Ʈ����ä��";
	
	n++; m_nSC[n] = SCT_MODE_CHANGE;		m_SC[n] = "���Ӹ�� �ٲ�";		m_SD[n] = "(??????????????)";
	
	n++; m_nSC[n] = SCT_MAP_LOAD_ATTR;		m_SC[n] = "�� �Ӽ� �θ���";		m_SD[n] = "(Text - �� �Ӽ� �����̸� | F1 - 0:���� ��� 1: ���� ���)";
	n++; m_nSC[n] = SCT_MAP_LOAD_SETTING;	m_SC[n] = "�� ���� �θ���";		m_SD[n] = "(Text - �� ���� �����̸� | F1 - 0:���� ��� 1: ���� ���)";
	n++; m_nSC[n] = SCT_MAP_RETURN;			m_SC[n] = "�ֹ������ ����";	m_SD[n] = "(Text - �� ���� �����̸�, ������ �׳� ���� ������ ����";
	n++; m_nSC[n] = SCT_MAP_SCROLL;			m_SC[n] = "�� ��ũ��";			m_SD[n] = "(F1 - 0:���� 1:���� | PT1 - �� ��ǥ)";

	n++; m_nSC[n] = SCT_CHR_SET_ATTACK;		m_SC[n] = "ĳ���� ����";		m_SD[n] = "(F1 - ĳ���� ��ȣ | F2 - ��� ĳ����)";
	n++; m_nSC[n] = SCT_CHR_SET_DIRECTION;	m_SC[n] = "ĳ���� ��������";	m_SD[n] = "(F1 - ĳ���� ��ȣ | F2 - 0~7 ������ͽð����)";
	n++; m_nSC[n] = SCT_CHR_SET_ANIMATION;	m_SC[n] = "ĳ���� ���ϸ��̼�";	m_SD[n] = "(F1 - ĳ���� ��ȣ | F2 - ���ϸ��̼� ��ȣ | F3 - 0:Loop 1:�ѹ���)";
	n++; m_nSC[n] = SCT_CHR_SET_MOVE;		m_SC[n] = "ĳ���� �̵�";		m_SD[n] = "(F1 - ĳ���� ��ȣ | F2 - 0:�ɾ�̵�, 1:����, 8:�پ F3 - 0:���� ��ũ��Ʈ�� �ٷ� ���� 1:�̵� ���� ������ ��ٸ� | PT1 - Map �ȼ� ��ǥ)";
	n++; m_nSC[n] = SCT_CHR_STOP_MOVE;		m_SC[n] = "ĳ���� ����";		m_SD[n] = "(F1 - ĳ���� ��ȣ)";
	n++; m_nSC[n] = SCT_CHR_SET_PARTY;		m_SC[n] = "ĳ���� ��Ƽ ����";	m_SD[n] = "(F1 - ĳ���� ��ȣ | F2 - 0:�ѾƳ� 1:�շ�)";

	n++; m_nSC[n] = SCT_FX_ENV_BEGIN;		m_SC[n] = "Ư��ȿ�� ����";		m_SD[n] = "(F1 - Ư��ȿ������ | Time - ���� �ð� mSec)";
	n++; m_nSC[n] = SCT_FX_ENV_END;			m_SC[n] = "Ư��ȿ�� ����";		m_SD[n] = "(F1 - Ư��ȿ������)";
	n++; m_nSC[n] = SCT_RENDER_MAIN;		m_SC[n] = "������ ����/����";	m_SD[n] = "(F1 - 0:���� 1:����)";

	n++; m_nSC[n] = SCT_INTF_SET;			m_SC[n] = "�������̽� ����";	m_SD[n] = "(F1 - �������̽� ��ȣ | F2 - ���̾� ��ȣ | F3 - ��ư ��ȣ)";
}

CDlgScript::~CDlgScript()
{
}

void CDlgScript::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgScript)
	DDX_Control(pDX, IDC_E_SCRIPT_FILE_NAME, m_Edit_ScriptFileName);
//	DDX_Control(pDX, IDC_STATIC_FILENAME, m_Static_FileName);
//	DDX_Control(pDX, IDC_STATIC_USAGE, m_Static_Usage);
	DDX_Control(pDX, IDC_E_SCRIPT_USAGE, m_Edit_Usage);
	DDX_Control(pDX, IDC_B_SCRIPT_NEW, m_Button_New);
	DDX_Control(pDX, IDC_B_SCRIPT_LOAD, m_Button_Load);
	DDX_Control(pDX, IDC_B_SCRIPT_SAVE, m_Button_Save);
	DDX_Control(pDX, IDC_B_SCRIPT_SAVE_AS, m_Button_SaveAs);
	DDX_Control(pDX, IDC_SPREAD_SCRIPT, m_Sheet);
	//}}AFX_DATA_MAP
}

/////////////////////////////////////////////////////////////////////////////
// DlgScript message handlers
BEGIN_MESSAGE_MAP(CDlgScript, CDialog)
	//{{AFX_MSG_MAP(CDlgScript)
	ON_BN_CLICKED(IDC_NEW, OnNew)
	ON_BN_CLICKED(IDC_LOAD, OnLoad)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_SAVE_AS, OnSaveAs)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_COMMAND(ID_SCRIPT_EXPAND_WIDTH, OnSheetExpandWidth)
	ON_COMMAND(ID_SCRIPT_REDUCE_WIDTH, OnSheetReduceWidth)
	ON_COMMAND(ID_SCRIPT_REPAIR_WIDTH, OnSheetRepairWidth)
	ON_WM_SHOWWINDOW()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDlgScript::Refresh()
{
	UpdateData(FALSE);
}

BOOL CDlgScript::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// ������ ���� �ʺ�� ���̸� ����Ѵ�..
	int w = m_Sheet.GetMaxCols();
	int i;
	for(i = 0; i <= w; i++)
	{
		m_Widths[i] = m_Sheet.GetColWidth(i);
	}

	// ��ũ��Ʈ �������� ��Ʈ �ʱ�ȭ..
	m_Sheet.SetCol(1); m_Sheet.SetCol2(9); m_Sheet.SetRow(1); m_Sheet.SetRow2(1024);
	m_Sheet.SetBlockMode(TRUE);
	m_Sheet.SetAction(3); // ���� �ȿ� �ִ� ��� ������ ����
	m_Sheet.SetBlockMode(FALSE);

	// ��ũ��Ʈ����Ʈ��  �޺� �ڽ��� �Է�
	long rows;
	rows = m_Sheet.GetMaxRows();
	CString list;
	for(int m = 0; m < MAX_SCT_COMMAND; m++)
	{
		if(m_SC[m].GetLength() != 0)
		{
			list += m_SC[m];
			list += '\t'; // ���� �ٿ��ָ� �ȴ�.
		}
	}

	for(int l = 1; l <= MAX_SCT; l++)
	{
		m_Sheet.SetCol(1);
		m_Sheet.SetRow(l);
		m_Sheet.SetTypeComboBoxList(list);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgScript::OnOK()
{
}

void CDlgScript::OnCancel()
{
}

void CDlgScript::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	BOOL b = FALSE;
	m_Sheet.SetWindowPos(NULL, 10, 10, cx - 20, cy - 130, NULL);

//	m_Static_Usage.SetWindowPos(NULL, 10, cy - 115, 50, 25, NULL);
	m_Edit_Usage.SetWindowPos(NULL, 70, cy - 115, cx - 80, 25, NULL);

//	m_Static_FileName.SetWindowPos(NULL, 10, cy - 85, 50, 25, NULL);
	m_Edit_ScriptFileName.SetWindowPos(NULL, 70, cy - 85, cx - 80, 25, NULL);
	
	int s = (cx-20) / 4;
	m_Button_New.SetWindowPos(NULL, 10, cy - 55, s-10, 25, NULL);
	m_Button_Load.SetWindowPos(NULL, 10 + s*1, cy - 55, s-10, 25, NULL);
	m_Button_Save.SetWindowPos(NULL, 10 + s*2, cy - 55, s-10, 25, NULL);
	m_Button_SaveAs.SetWindowPos(NULL, 10 + s*3, cy - 55, s-10, 25, NULL);
}

void CDlgScript::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	m_szSctFN = ""; // ��� �ʱ�ȭ...
	m_Script.Release();

	CDialog::OnCancel();
//	ShowWindow(SW_HIDE);
	CDialog::OnClose();
}

BEGIN_EVENTSINK_MAP(CDlgScript, CDialog)
    //{{AFX_EVENTSINK_MAP(CDlgScript)
	ON_EVENT(CDlgScript, IDC_SPREAD_SCRIPT, -602 /* KeyDown */, OnSheetKeyDown, VTS_PI2 VTS_I2)
	ON_EVENT(CDlgScript, IDC_SPREAD_SCRIPT, 3 /* ButtonClicked */, OnSheetButtonClicked, VTS_I4 VTS_I4 VTS_I2)
	ON_EVENT(CDlgScript, IDC_SPREAD_SCRIPT, 22 /* RightClick */, OnSheetRightClick, VTS_I2 VTS_I4 VTS_I4 VTS_I4 VTS_I4)
	ON_EVENT(CDlgScript, IDC_SPREAD_SCRIPT, 5 /* Click */, OnSheetClick, VTS_I4 VTS_I4)
	ON_EVENT(CDlgScript, IDC_SPREAD_SCRIPT, 31 /* ComboSelChange */, OnSheetComboSelChange, VTS_I4 VTS_I4)
	ON_EVENT(CDlgScript, IDC_SPREAD_SCRIPT, 32 /* TextTipFetch */, OnSheetTextTipFetch, VTS_I4 VTS_I4 VTS_PI2 VTS_PI4 VTS_PBSTR VTS_PBOOL)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CDlgScript::OnNew()
{
	// ���� �ʱ�ȭ..
	m_Script.Release();
	SetDlgItemText(IDC_E_SCRIPT_FILE_NAME, "");

	// ��ũ��Ʈ �������� ��Ʈ �ʱ�ȭ..
	RefreshSheet();
}

void CDlgScript::OnLoad() 
{
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "Sct", NULL, dwFlags, "Script files(*.sct)|*.sct|All files(*.*)|*.*||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("SCRIPT");
	if(dlg.DoModal() == IDCANCEL) return;

	CString FileName = dlg.GetFileName();

	// �ε� �� �������� ��Ʈ ����
	g_pTEng->PathSetCur("SCRIPT");
	m_Script.Load(FileName);
	RefreshSheet();
	SetDlgItemText(IDC_E_SCRIPT_FILE_NAME, FileName);
}

void CDlgScript::OnSave()
{
	CString FileName;
	GetDlgItemText(IDC_E_SCRIPT_FILE_NAME, FileName);
	if(FileName.GetLength() == NULL)
	{
		OnSaveAs();
		return;
	}
	
	g_pTEng->PathSetCur("SCRIPT");

	m_Script.Release(); // ��ũ��Ʈ ������ ����..
	for(int i = 0; i < MAX_SCT; i++) // ��Ʈ�� ������ ���ڵ� �� ����...
	{
		_SCT_DATA sct;
		MAKE_ZERO(sct);
		Encode(i+1, &sct);
		if(sct.nCommand == 0) break; // �ƹ��͵� ���� ����..
		m_Script.Set(i, &sct);
		if(sct.szText) delete [] sct.szText; sct.szText = NULL;
	}

	m_Script.Save(FileName);

	int n = m_Script.GetQuantity();
	CString str;
	str.Format("%d ���� ��ũ��Ʈ�� �����Ͽ����ϴ�.", n);
	MessageBox(str);
}

void CDlgScript::OnSaveAs()
{
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(FALSE, "Sct", NULL, dwFlags, "��ũ��Ʈ ����(*.sct)|*.sct||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("SCRIPT");
	if(dlg.DoModal() == IDCANCEL) return;

	CString FileName = dlg.GetFileName();
	SetDlgItemText(IDC_E_SCRIPT_FILE_NAME, FileName);
	OnSave();
}

void CDlgScript::OnSheetButtonClicked(long Col, long Row, short ButtonDown) 
{
	if(Col == 3)
	{
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
		CFileDialog dlg(TRUE, "All", NULL, dwFlags, "All files(*.*)|*.*||", NULL);
		dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("");
		if(dlg.DoModal() == IDCANCEL) return;

		CString FileName = dlg.GetFileName();

		if(FileName.GetLength() != 0)
		{
			m_Sheet.SetCol(Col-1); m_Sheet.SetRow(Row); m_Sheet.SetText(FileName);
		}
	}
}

void CDlgScript::OnSheetRightClick(short ClickType, long Col, long Row, long MouseX, long MouseY) 
{
	CMenu popup;
	CMenu* pItemMenu;
	popup.LoadMenu(IDM_POPUP_SCRIPT);
	pItemMenu = popup.GetSubMenu(0);

	CPoint point;
	GetCursorPos(&point);
	BOOL b = pItemMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CDlgScript::OnSheetExpandWidth() 
{
	long x1, x2;
	x1 = m_Sheet.GetSelBlockCol();
	x2 = m_Sheet.GetSelBlockCol2();
	for(;x1 <= x2; x1++)
	{
		m_Sheet.SetColWidth(x1, m_Widths[x1]);
	}
}

void CDlgScript::OnSheetReduceWidth() 
{
	long x1, x2;
	m_Sheet.GetBottomRightCell(&x1, &x2);
	x1 = m_Sheet.GetSelBlockCol();
	x2 = m_Sheet.GetSelBlockCol2();
	for(;x1 <= x2; x1++)
	{
		m_Sheet.SetColWidth(x1, 2.0f);
	}
}

void CDlgScript::OnSheetRepairWidth() 
{
	int w = m_Sheet.GetMaxCols();
	for(int i = 1; i <= w; i++)
	{
		m_Sheet.SetColWidth(i, m_Widths[i]);
	}
}

void CDlgScript::OnSheetClick(long Col, long Row)
{
	if(Row != 0) return; // ��� Ŭ���ÿ�...
	if(m_Sheet.GetColWidth(Col) != 2.0f) m_Sheet.SetColWidth(Col, 2.0f);
	else if(m_Sheet.GetColWidth(Col) == 2.0f) m_Sheet.SetColWidth(Col, m_Widths[Col]);
}

void CDlgScript::OnSheetKeyDown(short FAR* KeyCode, short Shift) 
{
	int col, row, col2, row2;
	m_Sheet.SetBlockMode(TRUE);
	col = m_Sheet.GetSelBlockCol(); col2 = m_Sheet.GetSelBlockCol2();
	row = m_Sheet.GetSelBlockRow(); row2 = m_Sheet.GetSelBlockRow2();
	m_Sheet.SetBlockMode(FALSE);
	
	if(col == -1 && col2 == -1)
	{
		switch(*KeyCode)
		{
		case VK_DELETE:
			m_Sheet.SetRow(row);
			m_Sheet.SetRow2(row2);
			m_Sheet.SetBlockMode(TRUE);
			m_Sheet.SetAction(5); // �� ����
			m_Sheet.SetBlockMode(FALSE);
			break;
		case VK_INSERT:
			m_Sheet.SetRow(row);
			m_Sheet.SetAction(7); // �� ����
			break;
		}
	}
}

void CDlgScript::Encode(int nRow, _SCT_DATA* pSct)
{
	if(pSct == NULL) return;

	long tmp = 0;
	CString str;
	m_Sheet.SetCol(1); m_Sheet.SetRow(nRow); str = m_Sheet.GetText(); // �ƹ��͵� �� ��������..
	if(str.GetLength() <= 0)
	{
		MAKE_ZERO(*pSct); 
		return;
	}
	
	m_Sheet.SetCol(1); m_Sheet.SetRow(nRow);
	int sel = m_Sheet.GetTypeComboBoxCurSel();
	pSct->nCommand = m_nSC[sel]; // �׳� ���ڰ� �ƴϴ�.. ���ǵ� �����̴�..
	m_Sheet.SetCol(2); m_Sheet.SetRow(nRow);
	str = m_Sheet.GetText();
	if(str.GetLength() > 0)
	{
		pSct->szText = new char[str.GetLength() + 1]; // �ݵ�� ���� �ٶ�!!!
		lstrcpy(pSct->szText, str);
	}
	m_Sheet.GetInteger(4, nRow, &tmp); pSct->nFlag1 = tmp;
	m_Sheet.GetInteger(5, nRow, &tmp); pSct->nFlag2 = tmp;
	m_Sheet.GetInteger(6, nRow, &tmp); pSct->nFlag3 = tmp;
	m_Sheet.SetCol(7); m_Sheet.SetRow(nRow); str = m_Sheet.GetText(); pSct->pt = ConvertStr2Point(str);
	m_Sheet.SetCol(8); m_Sheet.SetRow(nRow); str = m_Sheet.GetText(); pSct->rc = ConvertStr2Rect(str);
	m_Sheet.SetCol(9); m_Sheet.SetRow(nRow); str = m_Sheet.GetText(); pSct->fSpeed = (float)atof(str);
	m_Sheet.GetInteger(10, nRow, &tmp); pSct->dwTime = tmp;
}

void CDlgScript::Decode(int nRow, const _SCT_DATA* pSct)
{
	// ��ũ��Ʈ ��� �ʱ�ȭ..
	m_Sheet.SetCol(1); m_Sheet.SetRow(nRow);
	m_Sheet.SetTypeComboBoxCurSel(0); m_Sheet.SetText("");

	m_Sheet.SetCol(2); m_Sheet.SetCol2(9); m_Sheet.SetRow(nRow); m_Sheet.SetRow2(nRow);
	m_Sheet.SetBlockMode(TRUE);
	m_Sheet.SetAction(3); // ���� �ȿ� �ִ� ��� ������ ����
	m_Sheet.SetBlockMode(FALSE);

	if(pSct)
	{
		long tmp = 0;
		CString str;
		
		BOOL bExist = FALSE;
		for(int i = 0; i < MAX_SCT_COMMAND; i++)
		{
			tmp = pSct->nCommand;
			if(tmp == m_nSC[i])
			{
				m_Sheet.SetCol(1); m_Sheet.SetRow(nRow); m_Sheet.SetTypeComboBoxCurSel(i);
				bExist = TRUE;
			}
		}
		if(bExist == FALSE) return;

		m_Sheet.SetCol(2); m_Sheet.SetRow(nRow); 
		if(lstrlen(pSct->szText) != 0) m_Sheet.SetText(pSct->szText);

		tmp = pSct->nFlag1; if(tmp != 0) m_Sheet.SetInteger(4, nRow, tmp);
		tmp = pSct->nFlag2; if(tmp != 0) m_Sheet.SetInteger(5, nRow, tmp);
		tmp = pSct->nFlag3; if(tmp != 0) m_Sheet.SetInteger(6, nRow, tmp);

		if(pSct->pt.x != 0 || pSct->pt.y != 0)
		{
			str.Format("%.4d, %.4d", pSct->pt.x, pSct->pt.y);
			m_Sheet.SetCol(7); m_Sheet.SetRow(nRow); m_Sheet.SetText(str);
		}
		
		if(pSct->rc.left != 0 || pSct->rc.top != 0 || pSct->rc.right != 0 || pSct->rc.bottom != 0)
		{
			str.Format("%.4d, %.4d, %.4d, %.4d", pSct->rc.left, pSct->rc.top, pSct->rc.right, pSct->rc.bottom);
			m_Sheet.SetCol(8); m_Sheet.SetRow(nRow); m_Sheet.SetText(str);
		}

		if(pSct->fSpeed != 0)
		{
			m_Sheet.SetFloat(9, nRow, pSct->fSpeed);
		}

		tmp = pSct->dwTime; if(tmp != 0) m_Sheet.SetInteger(10, nRow, tmp);
	}
}

CRect CDlgScript::ConvertStr2Rect(CString& string)
{
	int nS = 0;
	int nE = 0;
	CString ts;
	CRect rc;
	nS = 0;
	nE = string.Find(",", nS);
	ts = string.Mid(nS, nE-nS);
	rc.left = atoi(ts.GetBuffer(ts.GetLength()));

	nS = nE+1;
	nE = string.Find(",", nS);
	ts = string.Mid(nS, nE-nS);
	rc.top = atoi(ts.GetBuffer(ts.GetLength()));

	nS = nE+1;
	nE = string.Find(",", nS);
	ts = string.Mid(nS, nE-nS);
	rc.right = atoi(ts.GetBuffer(ts.GetLength()));

	nS = nE+1;
	nE = string.Find(",", nS);
	ts = string.Mid(nS, string.GetLength()-nS);
	rc.bottom = atoi(ts.GetBuffer(ts.GetLength()));

	return rc;
}

CPoint CDlgScript::ConvertStr2Point(CString& string)
{
	int nS = 0;
	int nE = 0;
	CString ts;
	CPoint pt;
	nS = 0;
	nE = string.Find(",", nS);
	ts = string.Mid(nS, nE-nS);
	pt.x = atoi(ts.GetBuffer(ts.GetLength()));

	nS = nE+1;
	nE = string.Find(",", nS);
	ts = string.Mid(nS, string.GetLength()-nS);
	pt.y = atoi(ts.GetBuffer(ts.GetLength()));

	return pt;
}

void CDlgScript::OnSheetComboSelChange(long Col, long Row) 
{
}

void CDlgScript::OnSheetTextTipFetch(long Col, long Row, 
		short FAR* MultiLine, long FAR* TipWidth, BSTR FAR* TipText, BOOL FAR* ShowTip) 
{
	if(Col == 1) 
	{
		m_Sheet.SetCol(Col);
		m_Sheet.SetRow(Row);
		CString str = m_Sheet.GetText();
		CString tip;
		for(int i=0; i < MAX_SCT_COMMAND; i++)
		{
			if(str == m_SC[i])
			{
				tip = m_SD[i];
				break;
			}
		}
		if(tip.GetLength())
		{
			*ShowTip = 1;
			*TipText = tip.AllocSysString();
			* MultiLine = FALSE;
//			*TipWidth = tip.GetLength()*128;
		}
	}
}


void CDlgScript::LoadScript(const char* szFileName)
{
	m_szSctFN = szFileName;
}

void CDlgScript::RefreshSheet()
{
	int nQt = m_Script.GetQuantity();
	for(int i = 0; i < MAX_SCT; i++)
	{
		const _SCT_DATA* pSct = m_Script.Get(i);
		Decode(i+1, pSct);
	}
}

void CDlgScript::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if(bShow == TRUE)
	{
		if(m_szSctFN.GetLength() > 0)
		{
			// �ε� �� �������� ��Ʈ ����
			g_pTEng->PathSetCur("SCRIPT");
			m_Script.Load(m_szSctFN);
			RefreshSheet();
			SetDlgItemText(IDC_E_SCRIPT_FILE_NAME, m_szSctFN);
		}
	}
}
