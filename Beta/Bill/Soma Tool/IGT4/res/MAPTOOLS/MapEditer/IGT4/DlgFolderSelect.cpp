// DlgFolderSelect.cpp : implementation file
//

#include "stdafx.h"
#include "DlgFolderSelect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFolderSelect dialog


CDlgFolderSelect::CDlgFolderSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFolderSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFolderSelect)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgFolderSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFolderSelect)
	DDX_Control(pDX, IDC_BROWSE_TREE, m_DirTree);
	DDX_Control(pDX, IDC_FOLDER_LIST, m_FolderList);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFolderSelect, CDialog)
	//{{AFX_MSG_MAP(CDlgFolderSelect)
	ON_NOTIFY(TVN_SELCHANGED, IDC_BROWSE_TREE, OnSelchangedBrowseTree)
	ON_BN_CLICKED(IDC_TUNNEL_TREE, OnTunnelTree)
	ON_CBN_SELCHANGE(IDC_FOLDER_LIST, OnSelchangeFolderList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFolderSelect message handlers

BOOL CDlgFolderSelect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// �ֱٿ� �� ������ �����´�...
	char szInitDir[128];
	LONG length = 128;
	memset(szInitDir, 0, 128);
	CString Key;
	for(int i = 0; i < 10; i++)
	{
		Key.Format("SOFTWARE\\I'llSoft\\IGT4\\RecentFolder%.1d", i);
		LONG success = RegQueryValue(HKEY_CURRENT_USER, Key, szInitDir, &length);
		if(success == ERROR_SUCCESS && lstrlen(szInitDir) != 0)
		{
			m_FolderList.AddString(szInitDir);
		}
	}

	CString szDir;
	if(m_FolderList.GetCount() <= 0)
	{
		char szCurPath[128];
		GetCurrentDirectory(128, szCurPath);
		m_FolderList.AddString(szCurPath);
	}
	m_FolderList.SetCurSel(0);
	m_FolderList.GetLBText(0, szDir);
	
	m_DirTree.Initialize();
	m_DirTree.SetPath(szDir);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFolderSelect::OnSelchangedBrowseTree(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_TREEVIEW* pNMTreeView = (NM_TREEVIEW*)pNMHDR;

	// ������ �ٲ��... ���� ����Ʈ�� �ٲپ��ش�..
	HTREEITEM hItem = m_DirTree.GetSelectedItem();
	CString Path = m_DirTree.GetFullPath(hItem);

	Path = Path.Left(Path.GetLength() - 1);
	m_FolderName = Path;
	m_FolderList.SetWindowText(Path);

	*pResult = 0;
}

void CDlgFolderSelect::OnTunnelTree() 
{
	// TODO: Add your control notification handler code here
	CString szFindFolder;
	m_FolderList.GetWindowText(szFindFolder);
	m_DirTree.SetPath(szFindFolder);
}

void CDlgFolderSelect::OnOK() 
{
	// TODO: Add extra validation here
	// �ֱٿ� �� ������ �����صд�....
	CString szFindFolder;
	m_FolderList.GetWindowText(szFindFolder);
	m_FolderList.InsertString(0, szFindFolder);

	char szInitDir[128] = "";
	LONG length = 128;
	CString Key;
	int n = 0;
	for(int i = 9; i >= 0; i--)
	{
		lstrcpy(szInitDir, "");
		m_FolderList.GetLBText(9-i, szInitDir);
		if(lstrlen(szInitDir) != 0)
		{
			Key.Format("SOFTWARE\\I'llSoft\\IGT4\\RecentFolder%.1d", n);
			LONG success = RegSetValue(HKEY_CURRENT_USER, Key, REG_SZ, szInitDir, lstrlen(szInitDir));
			n++;
		}
	}
	
	m_FolderName = szFindFolder;

	CDialog::OnOK();
}

void CDlgFolderSelect::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
}

void CDlgFolderSelect::SetInitFolderName(CString& FolderName)
{
	m_FolderName = FolderName;
}

CString CDlgFolderSelect::GetFolderName()
{
	return m_FolderName;
}

void CDlgFolderSelect::OnSelchangeFolderList() 
{
	CString Path;
	m_FolderList.GetWindowText(Path);
	m_DirTree.SetPath(Path);
}
