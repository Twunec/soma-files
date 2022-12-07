// DlgAniObj.cpp : implementation file
//

#include "stdafx.h"

#include "DlgAniObj.h"
#include "Dib16.h"

#include "GlobalVar.h"

CDlgAniObj::CDlgAniObj() : CDialog(CDlgAniObj::IDD)
{
	//{{AFX_DATA_INIT(CDlgAniObj)
	//}}AFX_DATA_INIT

	m_pWndWork = NULL;
	m_bPlaying = 0;
	m_pClipAni = NULL;

	MAKE_ZERO(m_nFrmCurs);
}

CDlgAniObj::~CDlgAniObj()
{
	if(m_pClipAni)
	{
		DELETE_ARRAY_SAFE(m_pClipAni->pnFrms);
		DELETE_SAFE(m_pClipAni);
	}
}

void CDlgAniObj::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAniObj)
	DDX_Control(pDX, IDC_CB_DIR, m_CBDir);
	DDX_Control(pDX, IDC_CB_WORK, m_CBWork);
	DDX_Control(pDX, IDC_SLIDER_SPR, m_SliderSpr);
	DDX_Control(pDX, IDC_ANI_NAME, m_EditAniName);
	DDX_Control(pDX, IDC_ANI_LIST, m_ListAni);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgAniObj, CDialog)
	//{{AFX_MSG_MAP(CDlgAniObj)
	ON_BN_CLICKED(IDC_B_ANI_FRM_NEXT, OnBAniFrmNext)
	ON_BN_CLICKED(IDC_B_ANI_FRM_PREV, OnBAniFrmPrev)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_B_ANI_PLAY, OnBAniPlay)
	ON_BN_CLICKED(IDC_B_ANI_ADD, OnBAniAdd)
	ON_BN_CLICKED(IDC_B_ANI_DELETE, OnBAniDelete)
	ON_BN_CLICKED(IDC_B_ANI_INSERT, OnBAniInsert)
	ON_BN_CLICKED(IDC_B_ANI_COPY, OnBAniCopy)
	ON_BN_CLICKED(IDC_B_ANI_PASTE, OnBAniPaste)
	ON_BN_CLICKED(IDC_B_ANI_NEW, OnBAniNew)
	ON_BN_CLICKED(IDC_B_ANI_LOAD, OnBAniLoad)
	ON_BN_CLICKED(IDC_B_ANI_SAVE, OnBAniSave)
	ON_BN_CLICKED(IDC_B_ANI_SAVE_AS, OnBAniSaveAs)
	ON_LBN_SELCHANGE(IDC_ANI_LIST, OnSelchangeAniList)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_B_ANI_FRMS_GET_FROM_STRING, OnBAniFrmsGetFromString)
	ON_BN_CLICKED(IDC_B_ANI_FRMS_GET_AUTO_FROM_FRONT, OnBAniFrmsGetAutoFromFront)
	ON_BN_CLICKED(IDC_B_ANI_FRMS_GET_AUTO_SEQ, OnBAniFrmsGetAutoSeq)
	ON_BN_CLICKED(IDC_B_ANI_FRMS_SET_SAME_TO_FRONT, OnBAniFrmsSetSameToFront)
	ON_EN_CHANGE(IDC_ANI_NAME, OnChangeAniName)
	ON_BN_CLICKED(IDC_B_SPR_EXPORT_TO_BMP, OnBSprExportToBmp)
	ON_BN_CLICKED(IDC_B_SPR_IMPORT_FROM_BMP, OnBSprImportFromBmp)
	ON_EN_CHANGE(IDC_E_ANI_MAX_FRM, OnChangeEAniMaxFrm)
	ON_BN_CLICKED(IDC_B_SPR_LOAD, OnBSprLoad)
	ON_BN_CLICKED(IDC_B_SPR_NEW, OnBSprNew)
	ON_BN_CLICKED(IDC_B_SPR_SAVE, OnBSprSave)
	ON_BN_CLICKED(IDC_B_SPR_SAVE_AS, OnBSprSaveAs)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_B_SPR_SET_QT, OnBSprSetQt)
	ON_BN_CLICKED(IDC_B_SPR_BROWSE_BMP, OnBSprBrowseBmp)
	ON_BN_CLICKED(IDC_C_SPR_CK_R, OnCSprCkR)
	ON_BN_CLICKED(IDC_C_SPR_CK_G, OnCSprCkG)
	ON_BN_CLICKED(IDC_C_SPR_CK_B, OnCSprCkB)
	ON_CBN_SELENDOK(IDC_CB_WORK, OnSelendokCbWork)
	ON_EN_CHANGE(IDC_E_ANI_SPEED, OnChangeEAniSpeed)
	ON_BN_CLICKED(IDC_B_ANI_SET_DIR_QT, OnBAniSetDirQt)
	ON_CBN_SELCHANGE(IDC_CB_DIR, OnSelchangeCbDir)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_E_ANI_SPEED, OnChangeEAniSpeed)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAniObj message handlers

void CDlgAniObj::OnBAniFrmsGetFromString() 
{
	// ����Ʈ�� �ִ� ���ڿ����� ���� �迭�� ������ �´�.
	CString frames;
	int dir = m_CBDir.GetCurSel();
	GetDlgItemText(IDC_E_ANI_FRMS, frames);

	CString temp;
	int n = 0;
	int nPrev = 0;
	int nCount = 0;
	
	// ���ڿ��� ������ , �տ� �ִ� ���ڿ��� ���ڷ� �ٲ���..
	int nAni = m_ListAni.GetCurSel(); if(nAni == CB_ERR) return; // ����Ʈ���� ���ϸ��̼��� ���õǾ� ���� �ʴ�..
	_ANI_DATA* pAni = m_pAniObj->AniDataGet(nAni);
	if(pAni == NULL) return;

	while(TRUE)
	{
		if(nCount >= pAni->nMaxFrm) break; // �ִ� �����ӱ��� ���� �߶������.
		n = frames.Find(",", nPrev);
		// ���̻� ����ǥ�� ������ �ǵ��� ���ڿ��� ���ڿ��� �ٲپ� �ش�.
		if(n == -1)
		{
			temp = frames.Mid(nPrev, frames.GetLength() - nPrev);
			if(temp.GetLength()) pAni->pnFrms[dir*pAni->nMaxFrm + nCount] = atoi(temp);
			break;
		}
		temp = frames.Mid(nPrev, n-nPrev);
		pAni->pnFrms[dir*pAni->nMaxFrm + nCount] = atoi(temp);
		nCount++;
		nPrev = n+1;
	}

	// �θ� ������ �� ��ȭ���� ����
	UpdateWorkWindow();
	this->UpdateAniInfo();
}

void CDlgAniObj::OnBAniFrmPrev() 
{
	int nIndex = m_ListAni.GetCurSel();
	if(nIndex < 0 || nIndex >= MAX_ANI) return;
	m_nFrmCurs[nIndex]--;

	// �θ� ������ �� ��ȭ���� ����
	this->UpdateAniInfo();
	UpdateWorkWindow();
}

void CDlgAniObj::OnBAniFrmNext() 
{
	int nIndex = m_ListAni.GetCurSel();
	if(nIndex < 0 || nIndex >= MAX_ANI) return;
	m_nFrmCurs[nIndex]++;

	// �θ� ������ �� ��ȭ���� ����
	this->UpdateAniInfo();
	UpdateWorkWindow();
}

void CDlgAniObj::UpdateAniInfo()
{
	m_bRefreshing = TRUE;

	int nAni = m_ListAni.GetCurSel();
	if(nAni < 0 || nAni >= MAX_ANI || nAni == CB_ERR) return; // ����Ʈ���� ���ϸ��̼��� ���õǾ� ���� �ʴ�..

	_ANI_DATA* pAni = m_pAniObj->AniDataGet(nAni);
	if(pAni == NULL) return;
	
	int nDirQt = m_pAniObj->m_HAni.nDirQt;
	int nDir = m_CBDir.GetCurSel();
	if(nDir < 0) nDir = 0;
	if(nDir >= nDirQt) nDir = nDirQt - 1;
	
	// ��ȭ������ �� ������Ʈ
	CString szSpd; szSpd.Format("%5.2f", pAni->fSpd);
	int nMaxFrm = GetDlgItemInt(IDC_E_ANI_MAX_FRM);
	if(nMaxFrm != pAni->nMaxFrm) SetDlgItemInt(IDC_E_ANI_MAX_FRM, pAni->nMaxFrm);
	
	if(pAni->nMaxFrm > 0)
	{
		if(m_nFrmCurs[nAni] < 0) m_nFrmCurs[nAni] = 0; // ���° ����������..
		if(m_nFrmCurs[nAni] >= pAni->nMaxFrm) m_nFrmCurs[nAni] = pAni->nMaxFrm - 1;
		SetDlgItemInt(IDC_E_ANI_CUR_FRM, m_nFrmCurs[nAni]);
		SetDlgItemInt(IDC_E_ANI_SPR, pAni->pnFrms[nDir*pAni->nMaxFrm + m_nFrmCurs[nAni]]); // ��������Ʈ ��ȣ ǥ��
	}
	
	SetDlgItemText(IDC_E_ANI_SPEED, szSpd);
	SetDlgItemInt(IDC_E_ANI_NUMBER, nAni);

	// �������� ������Ʈ ���ش�...
	CString temp, szFrms;
	szFrms.Empty();
	for(int j = 0; j < pAni->nMaxFrm; j++)
	{
		temp.Format("%d,", pAni->pnFrms[nDir*pAni->nMaxFrm + j]);
		szFrms += temp;
	}
	SetDlgItemText(IDC_E_ANI_FRMS, szFrms);
	
	m_bRefreshing = FALSE;
}

void CDlgAniObj::UpdateSprInfo()
{
	SetDlgItemInt(IDC_E_SPR_CUR, m_SliderSpr.GetPos());
}

void CDlgAniObj::UpdateSprObjInfo()
{
	m_SliderSpr.SetRange(0, m_pAniObj->m_HSpr.nQt - 1, TRUE);
	SetDlgItemText(IDC_E_SPR_BMP_FILE_NAME, m_pAniObj->m_HSpr.szBMPFN);
	SetDlgItemInt(IDC_E_SPR_WHOLE, m_pAniObj->m_HSpr.nQt);

	if(m_pAniObj->m_lpDDS) 
	{
		CRect rc; g_pTEng->SurfaceGetSize(m_pAniObj->m_lpDDS, &rc);
		m_pAniObj->m_HSpr.nWidth = rc.Width();
		m_pAniObj->m_HSpr.nHeight = rc.Height();
	}

	if(m_pAniObj->m_HSpr.SrcCK & 0x000000ff) CheckDlgButton(IDC_C_SPR_CK_R, 1); else CheckDlgButton(IDC_C_SPR_CK_R, 0);
	if(m_pAniObj->m_HSpr.SrcCK & 0x0000ff00) CheckDlgButton(IDC_C_SPR_CK_G, 1); else CheckDlgButton(IDC_C_SPR_CK_G, 0);
	if(m_pAniObj->m_HSpr.SrcCK & 0x00ff0000) CheckDlgButton(IDC_C_SPR_CK_B, 1); else CheckDlgButton(IDC_C_SPR_CK_B, 0);
}

void CDlgAniObj::OnChangeEAniMaxFrm() 
{
	if(m_bRefreshing == TRUE) return;

	int n = GetDlgItemInt(IDC_MAX_FRAME);
	if(n < 0) n = 0;

	int nAni = m_ListAni.GetCurSel(); if(nAni == CB_ERR) return; // ����Ʈ���� ���ϸ��̼��� ���õǾ� ���� �ʴ�..
	_ANI_DATA* pAni = m_pAniObj->AniDataGet(nAni);
	if(pAni == NULL) return;

	int nDirQt = m_pAniObj->m_HAni.nDirQt; // ���� �������� ����Ѵ�..
	int nFrms[32][64]; MAKE_ZERO(nFrms);
	if(pAni->nMaxFrm > 0)
	{
		for(int i = 0; i < nDirQt; i++)
		{
			for(int j = 0; j < pAni->nMaxFrm; j++)
			{
				nFrms[i][j] = pAni->pnFrms[nDirQt * i + j];
			}
		}
	}

	DELETE_ARRAY_SAFE(pAni->pnFrms);
	pAni->nMaxFrm = n;
	if(pAni->nMaxFrm > 0)
	{
		pAni->pnFrms = new short int[pAni->nMaxFrm*m_pAniObj->m_HAni.nDirQt];
		memset(pAni->pnFrms, 0, pAni->nMaxFrm*m_pAniObj->m_HAni.nDirQt*2);
	}

	// ��ȭ���� ����
	this->UpdateAniInfo();
}

void CDlgAniObj::OnChangeEAniSpeed() 
{
	CString string; 
	GetDlgItemText(IDC_ANI_SPEED, string);
	float f = (float)atof(string);
	if(f <= 0.0f) f = 10.0f;

	int nAni = m_ListAni.GetCurSel(); if(nAni == CB_ERR) return; // ����Ʈ���� ���ϸ��̼��� ���õǾ� ���� �ʴ�..
	_ANI_DATA* pAni = m_pAniObj->AniDataGet(nAni);
	if(pAni == NULL) return;
	pAni->fSpd = f;
}

BOOL CDlgAniObj::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	m_CBWork.AddString("��������Ʈ �۾�");
	m_CBWork.AddString("���ϸ��̼� �۾�");
	m_CBWork.SetCurSel(0); // �۾� ������ �����ش�..

	this->OnBAniNew();
	this->OnBSprNew();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

int CDlgAniObj::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_pAniObj = new CAniObjTool();
	
	return 0;
}

void CDlgAniObj::OnDestroy() 
{
	DELETE_SAFE(m_pAniObj);

	CDialog::OnDestroy();
}

void CDlgAniObj::OnBAniPlay() 
{
	if(m_bPlaying == FALSE)
	{
		CButton* b = (CButton*) GetDlgItem(IDC_PLAY);
		b->SetWindowText("Stop");
		b->UpdateWindow();
		m_bPlaying = TRUE;
		SetTimer(1, 5, NULL); // 1 ��Ÿ�̸Ӹ� ���ϸ��̼� ������ ����.
	}
	else // �÷������̸�..
	{
		CButton* b = (CButton*) GetDlgItem(IDC_PLAY);
		b->SetWindowText("Play");
		b->UpdateWindow();
		this->UpdateAniInfo();
		m_bPlaying = FALSE;
		KillTimer(1); // 1 ��Ÿ�̸Ӹ� ���ϸ��̼� ������ ����.
	}
}

void CDlgAniObj::UpdateWorkWindow()
{
	if(m_pWndWork == NULL) return;

	m_pWndWork->InvalidateRect(NULL, FALSE);
}

void CDlgAniObj::OnBAniNew() 
{
	m_pAniObj->AniNew(); // ���ϸ��̼� ������Ʈ �ʱ�ȭ
	this->UpdateAniList();
	this->UpdateAniInfo();
	this->UpdateWorkWindow();

	m_CBDir.ResetContent(); // ���� ���� ǥ��
	SetDlgItemInt(IDC_E_ANI_DIR_QT, 0); // ���� ���� ǥ��
	SetDlgItemText(IDC_E_ANI_FILE_NAME, "");
}

void CDlgAniObj::OnBAniLoad() 
{
	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "ani", NULL, dwFlags, "���ϸ��̼�(*.ani)|*.ani||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("ANI");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();

	m_pAniObj->AniNew(); // ���ϸ��̼� ����...
	m_pAniObj->AniLoad(FileName);

	int nDirQt = m_pAniObj->m_HAni.nDirQt;
	m_CBDir.ResetContent(); // ���� ���� ǥ��
	CString szDir;
	m_CBDir.ResetContent();
	for(int i = 0; i < nDirQt; i++)
	{
		szDir.Format("%d", i);
		m_CBDir.AddString(szDir);
	}
	m_CBDir.SetCurSel(0);
	SetDlgItemInt(IDC_E_ANI_DIR_QT, nDirQt); // ���� ���� ǥ��
	SetDlgItemText(IDC_E_ANI_FILE_NAME, FileName);

	this->UpdateAniList();
	this->UpdateAniInfo();
	this->UpdateWorkWindow();
}

void CDlgAniObj::OnBAniSave() 
{
	CString FileName;
	GetDlgItemText(IDC_E_ANI_FILE_NAME, FileName);
	if(FileName.GetLength() == 0)
	{
		OnBAniSaveAs();
		return;
	}
	
	g_pTEng->PathSetCur("ANI");  // ��� ����
	m_pAniObj->AniSave(FileName); // ���ϸ��̼Ǹ�
}

void CDlgAniObj::OnBAniSaveAs() 
{
	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(FALSE, "ani", NULL, dwFlags, "���ϸ��̼�(*.ani)|*.ani||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("ANI");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();
	SetDlgItemText(IDC_E_ANI_FILE_NAME, FileName);
	OnBAniSave();
}

void CDlgAniObj::OnSelchangeAniList() 
{
	int sel = m_ListAni.GetCurSel();
	if(sel == LB_ERR) return;

	_ANI_DATA* pAni = m_pAniObj->AniDataGet(sel);
	if(pAni == NULL) return;

	m_EditAniName.SetWindowText(pAni->szName); // �̸� �ٲ��ֱ�..

	this->UpdateAniInfo();
	UpdateWorkWindow();
}

void CDlgAniObj::OnBAniInsert() 
{
	int sel = m_ListAni.GetCurSel();
	if(sel == LB_ERR) return;
	if(m_pAniObj->AniInsert(sel) != TRUE) return; // ��ȿ ���ϸ��̼� ���� �ϳ� �߰�..
	
	char szBuff[128];
	sprintf(szBuff, "���� ���ϸ��̼� %.2d", sel+1);
	m_ListAni.InsertString(sel, szBuff);
}

void CDlgAniObj::OnBAniAdd() 
{
	int sel = m_ListAni.GetCurSel();
	if(m_pAniObj->AniAdd() != TRUE) return; // ��ȿ ���ϸ��̼� ���� �ϳ� �߰�..
	char szBuff[128];
	sprintf(szBuff, "�߰� ���ϸ��̼� %.2d", sel+1);
	m_ListAni.AddString(szBuff);
}

void CDlgAniObj::OnBAniDelete()
{
	int sel = m_ListAni.GetCurSel();
	if(sel == LB_ERR) return;

	if(m_pAniObj->AniDelete(sel) != TRUE) return; // ���ϸ��̼� ����...
	
	m_ListAni.DeleteString(sel);
	this->UpdateAniInfo();
	UpdateWorkWindow();
}

void CDlgAniObj::OnBAniCopy() 
{
	// TODO: Add your control notification handler code here
	int nAni = m_ListAni.GetCurSel(); if(nAni == CB_ERR) return; // ����Ʈ���� ���ϸ��̼��� ���õǾ� ���� �ʴ�..
	_ANI_DATA* pAni = m_pAniObj->AniDataGet(nAni);
	if(pAni == NULL) return;

	if(m_pClipAni)
	{
		DELETE_ARRAY_SAFE(m_pClipAni->pnFrms);
		DELETE_SAFE(m_pClipAni);
	}
	m_pClipAni = new _ANI_DATA;
	memcpy(m_pClipAni, pAni, sizeof(_ANI_DATA));
	m_pClipAni->pnFrms = NULL;
	if(pAni->nMaxFrm > 0)
	{
		m_pClipAni->pnFrms = new short int[pAni->nMaxFrm*m_pAniObj->m_HAni.nDirQt];
		memcpy(m_pClipAni->pnFrms, pAni->pnFrms, pAni->nMaxFrm*m_pAniObj->m_HAni.nDirQt*2);
	}
}

void CDlgAniObj::OnBAniPaste() 
{
	// TODO: Add your control notification handler code here
	if(m_pClipAni == NULL) return;

	int nAni = m_ListAni.GetCurSel();
	_ANI_DATA* pAni = m_pAniObj->AniDataGet(nAni);
	if(pAni == NULL) return;

	DELETE_ARRAY_SAFE(pAni->pnFrms);
	memcpy(pAni, m_pClipAni, sizeof(_ANI_DATA));
	pAni->pnFrms = NULL;

	if(m_pClipAni->nMaxFrm > 0)
	{
		pAni->pnFrms = new short int[pAni->nMaxFrm*m_pAniObj->m_HAni.nDirQt];
		memcpy(pAni->pnFrms, m_pClipAni->pnFrms, pAni->nMaxFrm*m_pAniObj->m_HAni.nDirQt*2);
	}

	m_ListAni.DeleteString(nAni);
	m_ListAni.InsertString(nAni, pAni->szName);
	m_ListAni.SetCurSel(nAni);

	UpdateWorkWindow();
	this->UpdateAniInfo();
}

void CDlgAniObj::UpdateAniList()
{
	m_ListAni.ResetContent(); // ����Ʈ �ڽ� ��Ʈ�� �ʱ�ȭ
	m_pAniObj->m_HAni;

	// ����Ʈ �ڽ� ��Ʈ�ѿ� �߰��Ѵ�. (New �Ҷ� ��� ����)
	for(int i=0; i < m_pAniObj->m_HAni.nQt; i++)
	{
		_ANI_DATA* pAni = m_pAniObj->AniDataGet(i);
		m_ListAni.AddString(pAni->szName);
		m_ListAni.SetItemData(i, i);
	}
	m_ListAni.SetCurSel(0);
}

void CDlgAniObj::OnTimer(UINT nIDEvent) 
{

	if(nIDEvent != 1) return; // 1���� ���ϸ��̼� ������ ����.
	
	// ���ǵ� ������ ����
	int nAni = m_ListAni.GetCurSel(); if(nAni == CB_ERR) return; // ����Ʈ���� ���ϸ��̼��� ���õǾ� ���� �ʴ�..
	_ANI_DATA* pAni = m_pAniObj->AniDataGet(nAni);
	if(pAni == NULL) return;

	if(pAni->fSpd <= 0) pAni->fSpd = 10.0f;

	UpdateWorkWindow();

	CDialog::OnTimer(nIDEvent);
}


void CDlgAniObj::OnBAniFrmsGetAutoFromFront() 
{
	// ����Ʈ�� �ִ� ���ڿ����� ���� �迭�� ������ �´�.
	CString frames;
	GetDlgItemText(IDC_E_ANI_FRMS, frames);
	CString temp;

	int n = 0;
	int nPrev = 0;
	
	// ���ڿ��� ������ , �տ� �ִ� ���ڿ��� ���ڷ� �ٲ���..
	int nAni = m_ListAni.GetCurSel(); if(nAni == CB_ERR) return; // ����Ʈ���� ���ϸ��̼��� ���õǾ� ���� �ʴ�..
	_ANI_DATA* pAni = m_pAniObj->AniDataGet(nAni);
	if(pAni == NULL) return;

	int nDirQt = m_pAniObj->m_HAni.nDirQt; // ���� ����
	int min = pAni->nMaxFrm, max = 0;;
	for(int i = 0; i < pAni->nMaxFrm; i++)
	{
		n = frames.Find(",", nPrev);
		// ���̻� ����ǥ�� ������ �ǵ��� ���ڿ��� ���ڿ��� �ٲپ� �ش�.
		if(n == -1)
		{
			temp = frames.Mid(nPrev, frames.GetLength() - nPrev);
			if(temp.GetLength()) pAni->pnFrms[i] = atoi(temp);
			break;
		}
		temp = frames.Mid(nPrev, n-nPrev);
		pAni->pnFrms[i] = atoi(temp);
		
		if(pAni->pnFrms[i] > max) max = pAni->pnFrms[i]; // �ִ� ���� �ּ� ���� ã�´�.
		if(pAni->pnFrms[i] < min) min = pAni->pnFrms[i];

		nPrev = n+1;
	}

	int range = max-min; // ���� ���� ���ڿ� ū ������ ���̸� ã�´�.
	int nMaxFrm = pAni->nMaxFrm;
	for(i = 1; i < nDirQt; i++)
	{
		for(int j = 0; j < pAni->nMaxFrm; j++)
		{
			pAni->pnFrms[i*nMaxFrm+j] = pAni->pnFrms[(i-1)*nMaxFrm+j]+range+1;
		}
	}


	// �θ� ������ �� ��ȭ���� ����
	this->UpdateAniInfo();
	UpdateWorkWindow();
}

void CDlgAniObj::OnBAniFrmsSetSameToFront() 
{
	this->OnBAniFrmsGetFromString();
	
	// �չ��� �����Ӱ� �Ȱ��� �����..
	int nAni = m_ListAni.GetCurSel(); if(nAni == CB_ERR) return; // ����Ʈ���� ���ϸ��̼��� ���õǾ� ���� �ʴ�..
	
	_ANI_DATA* pAni = m_pAniObj->AniDataGet(nAni);
	if(pAni == NULL) return;
	if(pAni->nMaxFrm <= 0) return;
	
	
	int nDir = m_CBDir.GetCurSel();
	if(nDir < 0 || nDir >= 8) return;

	int nDirQt = m_pAniObj->m_HAni.nDirQt;
	int nMaxFrm = pAni->nMaxFrm;

	for(int i = 1; i < nDirQt; i++)
	{
		memcpy(&pAni->pnFrms[i*nMaxFrm], pAni->pnFrms, nMaxFrm*2);
	}

	this->UpdateAniInfo();
}

void CDlgAniObj::OnBAniFrmsGetAutoSeq() 
{
	 // �չ��� �����Ӱ� �Ȱ��� �����..
	int nAni = m_ListAni.GetCurSel(); if(nAni == CB_ERR) return; // ����Ʈ���� ���ϸ��̼��� ���õǾ� ���� �ʴ�..
	_ANI_DATA* pAni = m_pAniObj->AniDataGet(nAni);
	if(pAni == NULL) return;
	if(pAni->nMaxFrm <= 0) return;

	int nDirQt = m_pAniObj->m_HAni.nDirQt;
	int nSeq = pAni->pnFrms[0];
	for(int i = 0; i < nDirQt; i++)
	{
		for(int j = 0; j < pAni->nMaxFrm; j++)
		{
			pAni->pnFrms[i*pAni->nMaxFrm+j] = nSeq;
			nSeq++;
		}
	}

	this->UpdateAniInfo();
}

CString CDlgAniObj::GetFileName()
{
	CString fn;
	GetDlgItemText(IDC_FILE_NAME, fn);
	return fn;
}

void CDlgAniObj::SetFileName(const char* szFileName)
{
	SetDlgItemText(IDC_FILE_NAME, szFileName);
}

void CDlgAniObj::OnChangeAniName()
{
	int nSel = m_ListAni.GetCurSel();
	if(nSel == CB_ERR) return;
	
	_ANI_DATA* pAni = m_pAniObj->AniDataGet(nSel);
	if(pAni == NULL) return;

	CString str;
	m_EditAniName.GetWindowText(str);
	lstrcpy(pAni->szName, str);

	m_ListAni.DeleteString(nSel);
	m_ListAni.InsertString(nSel, str);
	m_ListAni.SetCurSel(nSel);
}


// �ش� ���ϸ��̼ǿ� �ش�Ǵ� ��������Ʈ�� ��¥ ��Ʈ������ Export
void CDlgAniObj::OnBSprExportToBmp() 
{

	int nAni = m_ListAni.GetCurSel();
	if(nAni == CB_ERR)
	{
		MessageBox("���ϸ��̼��� ������ �ּ���");
		return;
	}

	const _ANI_DATA* pAni;
	pAni = m_pAniObj->AniDataGet(nAni);
	if(pAni == NULL)
	{
		MessageBox("���ϸ��̼��� �����ϴ�.");
		return;
	}

	// �ߺ��Ǵ� ��������Ʈ ������ ����Ʈ �����..
	int nDirQt = m_pAniObj->m_HAni.nDirQt;
	int* pnTmps = new int[pAni->nMaxFrm * nDirQt]; // ������ �����ش�.
	int nCountTmp = 0;
	for(int i = 0; i < nDirQt; i++)
		for(int j = 0; j < pAni->nMaxFrm; j++)
			pnTmps[nCountTmp++] = pAni->pnFrms[i*pAni->nMaxFrm+j]; // �ߺ����� ������ ����Ʈ�� �߰�..
	
	int nCountFrm = 0;
	int *pnSprs = new int[pAni->nMaxFrm * 8]; // 8�����̴�.
	for(i = 0; i < nCountTmp; i++)
	{
		BOOL bOverLapped = FALSE;
		for(int j = 0; j < nCountFrm; j++)
		{
			if(pnTmps[i] == pnSprs[j])
			{
				bOverLapped = TRUE;
				break;
			}
		}
		if(bOverLapped == FALSE) pnSprs[nCountFrm++] = pnTmps[i];
	}
	delete [] pnTmps; pnTmps = NULL;
	
	if(nCountFrm <= 0)
	{
		MessageBox("Export�� ��������Ʈ�� �����ϴ�.");
		delete [] pnSprs; pnSprs = NULL;
		return;
	}

	// ���� ū ������ ã�´�..
	CRect rcBiggest(0,0,0,0);
	CRect rcSpr;
	const _SPR_LSP* pSpr;
	for(i = 0; i < nCountFrm; i++)
	{
		m_pAniObj->SprGet(pnSprs[i], &pSpr);
		if(pSpr == NULL) continue;

		rcSpr = pSpr->rcV;
		if(rcSpr.left < rcBiggest.left) rcBiggest.left = rcSpr.left;
		if(rcSpr.top < rcBiggest.top) rcBiggest.top = rcSpr.top;
		if(rcSpr.right > rcBiggest.right) rcBiggest.right = rcSpr.right;
		if(rcSpr.bottom > rcBiggest.bottom) rcBiggest.bottom = rcSpr.bottom;
	}

	int width = rcBiggest.Width();
	int height = rcBiggest.Height();
	int nPitch = width*nDirQt; // ������ ����..
	int nPF = g_pTEng->PixelFormatGet();

	if(width <= 0 || height <= 0)
	{
		MessageBox("��������Ʈ�� �ʺ�� ���̰� �߸��Ǿ� �ֽ��ϴ�. �۾��� �Ұ����մϴ�.");
		delete [] pnSprs; pnSprs = NULL;
		return;
	}

	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(FALSE, "bmp", NULL, dwFlags, "24��Ʈ ��Ʈ��(*.bmp)|*.bmp||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("BMP");
	if(dlg.DoModal() == IDCANCEL)
	{
		delete [] pnSprs; pnSprs = NULL;
		return;
	}
	CString FileName = dlg.GetFileName();

	// ���ٿ� ���ⰹ����ŭ ��ġ
	int nAddLine = 0; // ���� ������� ��������Ʈ�� ������ �����Ⱑ �� �¾ƶ�������.. 
	(nCountFrm%nDirQt) ? nAddLine = 1 : nAddLine = 0;  // �׷��� �ʴٸ� ������ �� ����� �Ѵ�..

	CDib16 dib;
	dib.New(width*nDirQt, height*(nCountFrm/nDirQt + nAddLine)); // ��Ʈ�� �����....
	if(m_pAniObj->m_HSpr.SrcCK == 0) // ������� �������̸� Ȯ���Ѵ�. ��������� ������� �ִ�..
	{
		int id = MessageBox("������� ���������� �����Ǿ� �ֽ��ϴ�. ������� ��������� �Ͻðڽ��ϱ�?", "����� Ȯ��", MB_YESNO);
		if(id == IDYES) m_pAniObj->m_HSpr.SrcCK = RGB(255,0,255);
	}
	dib.FillColor(NULL, m_pAniObj->m_HSpr.SrcCK); // ��ü ������ ��������� ĥ���ش�..
	WORD* pwDestOrg = dib.Lock();
	for(i = 0; i < nCountFrm; i++)
	{
		m_pAniObj->SprGet(pnSprs[i], &pSpr);

		// LSP ����
		WORD* pwSrc = pSpr->pwV;
		int nLine = pSpr->nLine; // �ټ�
		for(int j = 0; j < nLine; j++)
		{
			WORD* pwDest =	pwDestOrg + // ���ⰹ����ŭ�� �̹����� �� �ٷ� ����ȴ�.
							((i/nDirQt)*height+j)*nPitch + // ��
							(i%nDirQt)*width; // ��
			int nNode = *pwSrc; pwSrc++;
			for(int k = 0; k < nNode; k++)
			{
				int nZero = *pwSrc; pwSrc++; pwDest += nZero;
				int nPixel = *pwSrc; pwSrc++;
				for(int l = 0; l < nPixel; l++)
				{
					WORD wPixel = *pwSrc; pwSrc++; 
					if(nPF == PF_565) *pwDest = wPixel;
					else
					{
						*pwDest = ((wPixel&0x7fe0)<<1)|(wPixel&0x001f);
					}
					pwDest++;
				}
			}
		}
	}
	dib.Unlock();
	
	dib.ExportTo24BMP(FileName);
	
	delete [] pnSprs; pnSprs = NULL;

}

// ��Ʈ���� �ش� ��������Ʈ�� Import
void CDlgAniObj::OnBSprImportFromBmp() 
{

	int nAni = m_ListAni.GetCurSel();
	if(nAni == CB_ERR)
	{
		MessageBox("���ϸ��̼��� ������ �ּ���");
		return;
	}

	const _ANI_DATA* pAni;
	pAni = m_pAniObj->AniDataGet(nAni);
	if(pAni == NULL)
	{
		MessageBox("���ϸ��̼��� �����ϴ�.");
		return;
	}

	// �ߺ��Ǵ� ��������Ʈ ������ ����Ʈ �����..
	int nDirQt = m_pAniObj->m_HAni.nDirQt;
	if(nDirQt <= 0) return; // ���ⰹ���� �ϳ��� ���ٸ� ���ư���..

	int* pnTmps = new int[pAni->nMaxFrm * nDirQt]; // ����*�������̴�.
	int nCountTmp = 0;
	for(int i = 0; i < nDirQt; i++)
		for(int j = 0; j < pAni->nMaxFrm; j++)
			pnTmps[nCountTmp++] = pAni->pnFrms[i*pAni->nMaxFrm+j]; // �ߺ����� ������ ����Ʈ�� �߰�..
	
	int nCountFrm = 0;
	int *pnSprs = new int[pAni->nMaxFrm * 8]; // 8�����̴�.
	for(i = 0; i < nCountTmp; i++)
	{
		BOOL bOverLapped = FALSE;
		for(int j = 0; j < nCountFrm; j++)
		{
			if(pnTmps[i] == pnSprs[j])
			{
				bOverLapped = TRUE;
				break;
			}
		}
		if(bOverLapped == FALSE) pnSprs[nCountFrm++] = pnTmps[i];
	}
	delete [] pnTmps; pnTmps = NULL;
	
	if(nCountFrm <= 0)
	{
		MessageBox("Import�� ��������Ʈ�� �����ϴ�.");
		delete [] pnSprs; pnSprs = NULL;
		return;
	}

	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "bmp", NULL, dwFlags, "24��Ʈ ��Ʈ��(*.bmp)|*.bmp||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("BMP");
	if(dlg.DoModal() == IDCANCEL)
	{
		delete [] pnSprs; pnSprs = NULL;
		return;
	}

	CString FileName = dlg.GetFileName();

	// ���ǽ� �ε�... 
	LPDIRECTDRAWSURFACE lpdds = g_pTEng->SurfaceCreateWithBMP(FileName, FALSE, m_pAniObj->m_HSpr.SrcCK);
	if(lpdds == NULL)
	{
		delete [] pnSprs; pnSprs = NULL;
		return;
	}
	
	DDSURFACEDESC ddsd;
	g_pTEng->SurfaceLock(lpdds, &ddsd);
	COLORREF TColor = g_pTEng->RGB24(*((WORD*)(ddsd.lpSurface))); // 0,0 �� ���� ������̶� �����..
	g_pTEng->SurfaceUnlock(lpdds);
	
	CRect rcDDS;
	g_pTEng->SurfaceGetSize(lpdds, &rcDDS);
	
	// �ʺ�� ���̰� �´��� ����..
	int nAddLine = 0; // ���� ������� ��������Ʈ�� ������ �����Ⱑ �� �¾ƶ�������.. 
	(nCountFrm%nDirQt) ? nAddLine = 1 : nAddLine = 0;  // �׷��� �ʴٸ� ������ �� ����� �Ѵ�..

	int nWidth = rcDDS.Width() / nDirQt;
	int nHeight = rcDDS.Height() / (nCountFrm/nDirQt+nAddLine);

	POINT ptCenter;
	for(i = 0; i < nCountFrm; i++)
	{
		const _SPR_LSP* pSpr;
		m_pAniObj->SprGet(pnSprs[i], &pSpr);
		_SPR_LSP* pSpr2 = (_SPR_LSP*) pSpr;
		if(pSpr2 == NULL) continue;

		CRect rcEncode; // ���� ���� ���ϱ�...
		rcEncode.left = (i%nDirQt)*nWidth;
		rcEncode.top = (i/nDirQt)*nHeight;
		rcEncode.right = rcEncode.left + nWidth;
		rcEncode.bottom = rcEncode.top + nHeight;

		ptCenter.x = rcEncode.left - pSpr2->rcV.left;
		ptCenter.y = rcEncode.top - pSpr2->rcV.top;

		DELETE_ARRAY_SAFE(pSpr2->pwV);
		g_pTEng->EncodeToLSPData(lpdds, TColor, rcEncode, ptCenter, pSpr2);
	}

	UpdateWorkWindow();
	MessageBox("��������Ʈ�� �����ؾ� ��ȿ �մϴ�.");

	RELEASE_SAFE(lpdds);
	delete [] pnSprs; pnSprs = NULL;
}

void CDlgAniObj::OnBSprNew() 
{
	m_pAniObj->SprNew();
	SetDlgItemText(IDC_E_SPR_FILE_NAME, "");

	this->UpdateSprObjInfo();
	this->UpdateSprInfo();

	if(m_pWndWork == NULL) return;

	CRect rcWork; // ������ ���� �޽���..
	m_pWndWork->GetWindowRect(&rcWork);
	m_pWndWork->SendMessage(WM_SIZE, SIZE_RESTORED, MAKELPARAM(rcWork.Width(), rcWork.Height()));
	this->UpdateWorkWindow();
}

void CDlgAniObj::OnBSprLoad() 
{
	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "spl", NULL, dwFlags, "LSP Sprite(*.spl)|*.spl|8Bit LSP Sprite(*.sp8)|*.sp8|Normal Sprite(*.spn)|*.spn||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("SPR");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();
	m_pAniObj->SprLoad(FileName, g_pTEng->PixelFormatGet());
	SetDlgItemText(IDC_E_SPR_FILE_NAME, FileName);

	this->UpdateSprObjInfo();
	this->UpdateSprInfo();

	if(m_pWndWork == NULL) return;

	CRect rcWork; // ������ ���� �޽���..
	m_pWndWork->GetWindowRect(&rcWork);
	m_pWndWork->SendMessage(WM_SIZE, SIZE_RESTORED, MAKELPARAM(rcWork.Width(), rcWork.Height()));
	this->UpdateWorkWindow();
}

void CDlgAniObj::OnBSprSave() 
{
	CString FileName;
	GetDlgItemText(IDC_E_SPR_FILE_NAME, FileName);
	if(FileName.GetLength() <= 0)
	{
		OnBSprSaveAs();
		return;
	}
	
	g_pTEng->PathSetCur("SPR"); // ��� ����
	m_pAniObj->SprSave(FileName);
}

void CDlgAniObj::OnBSprSaveAs() 
{
	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(FALSE, "spl", NULL, dwFlags, "LSP Sprite(*.spl)|*.spl|8Bit LSP Sprite(*.sp8)|*.sp8|Normal Sprite(*.spn)|*.spn||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("SPR");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();
	SetDlgItemText(IDC_E_SPR_FILE_NAME, FileName);
	OnBSprSave();
}

void CDlgAniObj::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	if(pScrollBar == (CScrollBar*)&m_SliderSpr) // ��������Ʈ �����̴��̸�..
	{
		this->UpdateSprInfo();
		this->UpdateWorkWindow(); // �۾� ������ ����..
	}

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CDlgAniObj::OnBSprSetQt() 
{
	int nQt = GetDlgItemInt(IDC_E_SPR_QT);
	if(nQt < 0 || nQt >= MAX_SPR) return;
	
	m_pAniObj->m_HSpr.nQt = nQt;
	SetDlgItemInt(IDC_E_SPR_WHOLE, nQt);

	m_SliderSpr.SetRange(0, nQt - 1, TRUE);
}

void CDlgAniObj::OnBSprBrowseBmp() 
{
	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "bmp", NULL, dwFlags, "24��Ʈ ��Ʈ�� ����(*.bmp)|*.bmp|16��Ʈ ���� ��Ʈ�� ����(*.obm)|*.obm||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("BMP");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();
	
	LPDIRECTDRAWSURFACE lpDDS = g_pTEng->SurfaceCreateWithBMP(FileName, FALSE, m_pAniObj->m_HSpr.SrcCK);
	if(lpDDS == NULL) return;

	RELEASE_SAFE(m_pAniObj->m_lpDDS);
	m_pAniObj->m_lpDDS = lpDDS;
	lstrcpy(m_pAniObj->m_HSpr.szBMPFN, FileName);

	this->UpdateSprObjInfo();
	
	if(m_pWndWork == NULL) return;

	CRect rcWork; // ������ ���� �޽���..
	m_pWndWork->GetWindowRect(&rcWork);
	m_pWndWork->SendMessage(WM_SIZE, SIZE_RESTORED, MAKELPARAM(rcWork.Width(), rcWork.Height()));
	this->UpdateWorkWindow();
}

void CDlgAniObj::OnCSprCkR() 
{
	m_pAniObj->m_HSpr.SrcCK = 0;

	if(IsDlgButtonChecked(IDC_C_SPR_CK_R)) m_pAniObj->m_HSpr.SrcCK |= RGB(255,0,0);
	if(IsDlgButtonChecked(IDC_C_SPR_CK_G)) m_pAniObj->m_HSpr.SrcCK |= RGB(0,255,0);
	if(IsDlgButtonChecked(IDC_C_SPR_CK_B)) m_pAniObj->m_HSpr.SrcCK |= RGB(0,0,255);

	g_pTEng->SurfaceColorKeySet(m_pAniObj->m_lpDDS, m_pAniObj->m_HSpr.SrcCK);

	this->UpdateWorkWindow();
}

void CDlgAniObj::OnCSprCkG() 
{
	m_pAniObj->m_HSpr.SrcCK = 0;

	if(IsDlgButtonChecked(IDC_C_SPR_CK_R)) m_pAniObj->m_HSpr.SrcCK |= RGB(255,0,0);
	if(IsDlgButtonChecked(IDC_C_SPR_CK_G)) m_pAniObj->m_HSpr.SrcCK |= RGB(0,255,0);
	if(IsDlgButtonChecked(IDC_C_SPR_CK_B)) m_pAniObj->m_HSpr.SrcCK |= RGB(0,0,255);

	g_pTEng->SurfaceColorKeySet(m_pAniObj->m_lpDDS, m_pAniObj->m_HSpr.SrcCK);

	this->UpdateWorkWindow();
}

void CDlgAniObj::OnCSprCkB() 
{
	m_pAniObj->m_HSpr.SrcCK = 0;

	if(IsDlgButtonChecked(IDC_C_SPR_CK_R)) m_pAniObj->m_HSpr.SrcCK |= RGB(255,0,0);
	if(IsDlgButtonChecked(IDC_C_SPR_CK_G)) m_pAniObj->m_HSpr.SrcCK |= RGB(0,255,0);
	if(IsDlgButtonChecked(IDC_C_SPR_CK_B)) m_pAniObj->m_HSpr.SrcCK |= RGB(0,0,255);

	g_pTEng->SurfaceColorKeySet(m_pAniObj->m_lpDDS, m_pAniObj->m_HSpr.SrcCK);

	this->UpdateWorkWindow();
}

void CDlgAniObj::OnSelendokCbWork() 
{
	this->UpdateWorkWindow();	
}

void CDlgAniObj::OnOK()
{

}

void CDlgAniObj::OnCancel()
{

}

void CDlgAniObj::OnBAniSetDirQt() 
{
	int nDirQt = GetDlgItemInt(IDC_E_ANI_DIR_QT);
	
	CString szDir;
	
	m_CBDir.ResetContent(); // ���� ���� ��Ÿ����
	for(int i = 0; i < nDirQt; i++)
	{
		szDir.Format("%d", i);
		m_CBDir.AddString(szDir);
	}
	m_CBDir.SetCurSel(0);

	m_pAniObj->AniDirQtSet(nDirQt);
	this->UpdateAniInfo();
	UpdateWorkWindow();
}

void CDlgAniObj::OnSelchangeCbDir() 
{
	this->UpdateAniInfo();
	UpdateWorkWindow();
}

