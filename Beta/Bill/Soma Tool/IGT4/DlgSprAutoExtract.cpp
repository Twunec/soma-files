// AutoSpriteDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DlgSprAutoExtract.h"

#include "DDEngineTool4.h"
#include "DlgFolderSelect.h"
#include "..\\IGObject\\Dib16.h"
#include "AniObjTool.h"
#include "DlgSetCenter.h"

#include "GlobalVar.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgSprAutoExtract property page

CDlgSprAutoExtract::CDlgSprAutoExtract() : CDialog(CDlgSprAutoExtract::IDD)
{
	//{{AFX_DATA_INIT(CDlgSprAutoExtract)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bStopProcess = FALSE;
}

CDlgSprAutoExtract::~CDlgSprAutoExtract()
{
}

void CDlgSprAutoExtract::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSprAutoExtract)
	DDX_Control(pDX, IDC_PROGRESS, m_Progress);
	DDX_Control(pDX, IDC_FILE_NAME, m_FileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSprAutoExtract, CDialog)
	//{{AFX_MSG_MAP(CDlgSprAutoExtract)
	ON_BN_CLICKED(IDC_BROWSE_WORK_FOLDER_AND_START_WORKING, OnBrowseWorkFolderAndStartWorking)
	ON_BN_CLICKED(IDC_CLOSEDLG, OnClosedlg)
	ON_BN_CLICKED(IDC_CANCEL_PROCESS, OnCancelProcess)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSprAutoExtract message handlers

void CDlgSprAutoExtract::OnBrowseWorkFolderAndStartWorking() 
{
	// TODO: Add your control notification handler code here
	CDlgFolderSelect dlgFS;
	if(dlgFS.DoModal() == IDCANCEL) return;

	CString Path = dlgFS.GetFolderName();

	m_bStopProcess = FALSE; // �ϴ� �ߴ� �÷��� ��������,. ��ư ������ �ٲ��..
	SetCurrentDirectory(Path);

	int check = GetCheckedRadioButton(IDC_R_SPL, IDC_R_SP8);

	CDlgSetCenter DlgSC; // ������ ���
	if(DlgSC.DoModal() == IDCANCEL) return;
	CPoint ptCenter = DlgSC.GetCenter(); // ������..

	switch(check)
	{
	case IDC_R_SPL:
	case IDC_R_SP8:
		{
			BOOL bSuccess = FALSE;
			CString SrcFN = ProcessLSPSprSimple(Path, ptCenter, 0);
/*			if(check == IDC_R_SP8) // 8 ��Ʈ ������ ���� ���..
			{
				DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
				CFileDialog dlg(TRUE, "bmp", NULL, dwFlags, "8 ��Ʈ ��Ʈ�� ����(*.bmp)|*.bmp||", NULL);
				char szBuff[128]; lstrcpy(szBuff, Path); lstrcat(szBuff, "�� ���� 8��Ʈ �ε��� ��Ʈ�� ���� ����");
				dlg.m_ofn.lpstrTitle = szBuff;
				dlg.m_ofn.lpstrInitialDir = Path;

				if(dlg.DoModal() == IDCANCEL ) break;

				CString IndexFN = dlg.GetPathName();
				CString DestFN = SrcFN;
				int n = DestFN.GetLength();
				DestFN.SetAt(n-3, 's');
				DestFN.SetAt(n-2, 'p');
				DestFN.SetAt(n-1, '8');
				// �ܼ� LSP ������ 8��Ʈ �ε��� ���Ϸ� �ٲ۴�..
//					BOOL bSuccess = g_pTEng->ConvertSImpleLSPFileToIndexedLSPFile(SrcFN, DestFN, IndexFN);
				if(!bSuccess) break;
				CString tbuff;
				tbuff = SrcFN + " -> " + DestFN + " �� ���� �Ǿ����ϴ�.\n ���� " + SrcFN + "�� ������?";
				int yesno = MessageBox(tbuff, "���� Ȯ��", MB_YESNO);
				if(yesno == IDYES) remove(SrcFN); // ������ �����..
			}
			if(m_bStopProcess == TRUE) break;
*/
		}
		break;
	default:
		MessageBox("�۾� ���� ������ �ȵǾ� �ֽ��ϴ�.");
		break;
	}
}

void CDlgSprAutoExtract::OnClosedlg() 
{
	CDialog::OnCancel();
}

void CDlgSprAutoExtract::OnCancelProcess() 
{
	m_bStopProcess = TRUE;
}

BOOL CDlgSprAutoExtract::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CheckRadioButton(IDC_R_SPL, IDC_R_SP8, IDC_R_SPL); // ���� ��ư üũ
	SetDlgItemInt(IDC_REMOVE_PIXEL_DELTA, 100); // �⺻������ 100 �� �ָ� �� ����ŭ �ȼ��� ���� ���� ��� �����Ѵ�.

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

CString CDlgSprAutoExtract::ProcessLSPSprSimple(const char* szPath, POINT ptCenter, int nSubFolderDepth)
{
	static nSFD = 0;
	if(nSubFolderDepth == 0) nSFD = 0;

	SetCurrentDirectory(szPath);
	CString Path = szPath;
	
	CFileFind finder; // ������ �ִ� ������ �� ã�´�.
	BOOL bWorking = finder.FindFile("*.*");

	CString FileName;
	char* szFNs = new char [1024*256]; memset(szFNs, 0, 1024*256);
	int nFileCount = 0; // �� ���� ����..
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		FileName = finder.GetFilePath();
		if(finder.IsDirectory() == TRUE && FileName.Right(2) == "\\." || FileName.Right(3) == "\\..") continue;
		
		if(finder.IsDirectory() == TRUE)
		{
			nSFD++;
			this->ProcessLSPSprSimple(FileName, ptCenter, nSFD); // ������ ���� ����.. // ��� ȣ���̴�.. ��������.
			nSFD--;
		}

		if(lstrcmpi(FileName.Right(3), "bmp") == 0)
		{
			lstrcpy(&szFNs[nFileCount*256], FileName);
			nFileCount++;
		}
	}
	if(nFileCount <= 0)
	{
		DELETE_ARRAY_SAFE(szFNs);
		return "";
	}

	CFile file; // goto �� ���� �ε��� �ϰ� �ű�..
	CFileDialog* pDlg = NULL;

	int n1 = 0;
	CString szFolder;
	char szBuff[256]; MAKE_ZERO(szBuff);
	int n2 = 0;
	for(int j = Path.GetLength(); j > 2; j--)
	{
		if(n1 > nSubFolderDepth) break;
		if(Path[j-1] == '\\')
		{
			szBuff[n2++] = '_';
			n1++;
		}
		else
		{
			if(Path[j-1] & 0x80)
			{
				szBuff[n2++] = Path[j-2];
				szBuff[n2++] = Path[j-1];
				j--;
			}
			else szBuff[n2++] = Path[j-1];
		}
	}
	szFolder = szBuff;
	szFolder.MakeReverse(); // ���ڿ� ������.
	if(szFolder.GetLength() <= 0)
	{
		DELETE_ARRAY_SAFE(szFNs);
		return "";
	}

	int nFrmCount = 0;

	// ����� ������ ��ȣ�� ���� 	// "NASTASHA_0_01_00_00_V1_A_4_0000.bmp"
	qsort(szFNs, nFileCount, 256, CompareDirAndFrmsProc);

	// ��������Ʈ ������ �غ�..
	CAniObjTool sprobj;
	sprobj.SprAlloc(nFileCount);

	BOOL bSuccess = FALSE;
	int nReinforceDelta = GetDlgItemInt(IDC_REMOVE_PIXEL_DELTA); // ��Ƴ� ���� ����.. �������� ��� ��Ƴ��� ����...
	m_Progress.SetRange(0, nFileCount);
	for(int i = 0; i < nFileCount; i++)
	{
		m_Progress.SetPos(i+1); // ���� ��Ȳ
		CString str;
		str.Format("%s - ������ : %d", &szFNs[i*256], i);
		m_FileName.SetWindowText(str);
		
		const _SPR_LSP* pSprTmp = NULL;
		sprobj.SprGet(i, &pSprTmp);
		_SPR_LSP* pSpr = (_SPR_LSP*)pSprTmp;
		if(pSpr == NULL) goto ERROR_PROCESS;

		bSuccess = g_pTEng->TransactPieceLSPSpr(&szFNs[i*256], nReinforceDelta, ptCenter, pSpr); // ���� Ÿ��Ʋ�� ���� ��������Ʈ �� LSP �ڵ� ó��..		
		UpdatePreview(pSprTmp); // ������ ������Ʈ
		if(bSuccess == FALSE) goto ERROR_PROCESS;// ��ȯ�� ���� �ϰų� Esc ������ ��ȯ �ߴ�..
		if(m_bStopProcess == TRUE) goto STOP_PROCESS;

		// �ý����� ��� �����Ѵ�...  // ������ ���� ������Ʈ
		MSG msg; PeekMessage(&msg, NULL, 0, 0, PM_REMOVE); TranslateMessage(&msg); DispatchMessage(&msg); this->UpdateWindow();
	}
	
	///////////////////////////////////////////////////////////////////////////////////////////
	// ��������Ʈ ���� ���� ..
	if(pDlg) { delete pDlg; pDlg = NULL; }
	pDlg = new CFileDialog(FALSE, "spl", szFolder+".spl", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "�ܼ� LSP ��������Ʈ(*.spl)|*.spl||", NULL);
	pDlg->m_ofn.lpstrTitle = "��������Ʈ ���� ����";
	pDlg->m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("SPR_�ڵ�����");
	
	if(pDlg->DoModal() == IDCANCEL)
	{
		delete pDlg; pDlg = NULL;
		goto STOP_PROCESS;
	}
	
	FileName = pDlg->GetPathName();

	// ����� ����.... �����ϸ�..
	if(lstrlen(&szFNs[0]) > 0)
	{
		SetCurrentDirectory(Path);
		LPDIRECTDRAWSURFACE lpDDS = g_pTEng->SurfaceCreateWithBMP(&szFNs[0], FALSE, 0);
		if(lpDDS)
		{
			DDSURFACEDESC ddsd;
			g_pTEng->SurfaceLock(lpDDS, &ddsd);
			sprobj.m_HSpr.SrcCK = g_pTEng->RGB24(GET_ARRAY_VALUE((WORD*)ddsd.lpSurface, ddsd.lPitch / 2, 0, 0)); // ȭ���� 0,0 �� ��..
			g_pTEng->SurfaceUnlock(lpDDS);
			RELEASE_SAFE(lpDDS);
		}
	}
	sprobj.SprSave(FileName); // ���� ����..
	
	goto STOP_PROCESS;

ERROR_PROCESS:
	FileName.Format(" %d ������ ó���� ���� �߻��߾�", i);
	MessageBox(&szFNs[i*256], "Error");
	FileName = "";

STOP_PROCESS:
	
	DELETE_ARRAY_SAFE(szFNs);
	DELETE_SAFE(pDlg);

	return FileName;
}

void CDlgSprAutoExtract::UpdatePreview(const _SPR_LSP* pSpr)
{
	if(!pSpr) return;

	CRect rc;
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PREVIEW);
	pWnd->GetClientRect(&rc);
	
	g_pTEng->SurfaceFillRect(NULL, &rc, RGB(64,64,64));
	
	g_pTEng->BackBufferLock();
	g_pTEng->BltLSP(NULL, rc.Width()/2, rc.Height()/2, pSpr);
	g_pTEng->BackBufferUnlock();
	
	g_pTEng->HWndSet(pWnd->m_hWnd);
	g_pTEng->Flip(&rc);
}

void CDlgSprAutoExtract::ClearPreview()
{
	CWnd* pWnd = GetDlgItem(IDC_STATIC_PREVIEW);
	CDC* pDC = pWnd->GetDC();
	CRect rc;
	pWnd->GetClientRect(&rc);
	pDC->FillSolidRect(&rc, RGB(96,96,96));
	pWnd->ReleaseDC(pDC);
}

int CDlgSprAutoExtract::CompareIntegerProc(const void *arg1, const void *arg2)
{
	int frame1 = *(int*)arg1;
	int frame2 = *(int*)arg2;

	if(frame1 < frame2) return -1;
	else if(frame1 == frame2) return 0;
	return 1;
}

int CDlgSprAutoExtract::CompareDirAndFrmsProc(const void *arg1, const void *arg2)
{
	CString FN1 = (const char*)arg1;
	CString FN2 = (const char*)arg2;

	char szDir1[3]; 
	char szDir2[3]; 
	lstrcpy(szDir1, FN1.Mid(FN1.GetLength() - 11, 2));
	lstrcpy(szDir2, FN2.Mid(FN2.GetLength() - 11, 2));

	if(szDir1[0] < '0' || szDir1[0] > '9') szDir1[0] = '0';
	if(szDir2[0] < '0' || szDir2[0] > '9') szDir2[0] = '0';
	if(szDir1[1] < '0' || szDir1[1] > '9') szDir1[1] = NULL;
	if(szDir2[1] < '0' || szDir2[1] > '9') szDir2[1] = NULL;

	// "00_0000.bmp"
	int dir1 = atoi(szDir1);
	int dir2 = atoi(szDir2);

	int frm1 = atoi(FN1.Mid(FN1.GetLength() - 8, 4));
	int frm2 = atoi(FN2.Mid(FN2.GetLength() - 8, 4));
	
	int t1 = dir1*1000 + frm1;
	int t2 = dir2*1000 + frm2;

	if(t1 < t2) return -1;
	else if(t1 > t2) return 1;
	else return 0;

	return 0;
}

int CDlgSprAutoExtract::CompareStringAscendProc(const void *arg1, const void *arg2)
{
	const char* pStr1 = (char*)arg1;
	const char* pStr2 = (char*)arg2;

	return lstrcmpi(pStr1, pStr2);
}

void CDlgSprAutoExtract::OnOK()
{

}

void CDlgSprAutoExtract::OnCancel()
{

}
