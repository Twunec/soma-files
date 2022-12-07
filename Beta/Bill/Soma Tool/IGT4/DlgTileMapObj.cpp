// DlgTileMapObj.cpp : implementation file
//

#include "stdafx.h"
#include "igt4.h"
#include "DlgTileMapObj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#include "GlobalVar.h"

// Ver.100 (2000/12/21) : �� Object �߰�
#define CURRENT_VER		100
/////////////////////////////////////////////////////////////////////////////
// CDlgTileMapObj dialog

CDlgTileMapObj::CDlgTileMapObj(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTileMapObj::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTileMapObj)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_vCurrentVersion = CURRENT_VER;
	m_bShowInnerHouse = FALSE;
}


void CDlgTileMapObj::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTileMapObj)
	DDX_Control(pDX, IDC_LIST_OBJ_SUB_SET, m_ListObjSubSet);
	DDX_Control(pDX, IDC_LIST_OBJ_SET, m_ListObjSet);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTileMapObj, CDialog)
	//{{AFX_MSG_MAP(CDlgTileMapObj)
	ON_BN_CLICKED(IDC_B_SET_SIZE, OnBSetSize)
	ON_BN_CLICKED(IDC_B_ANI_FILE_NAME_SET, OnBAniFileNameSet)
	ON_BN_CLICKED(IDC_B_ANI_FILE_NAME_DELETE, OnBAniFileNameDelete)
	ON_BN_CLICKED(IDC_B_SPR_FILE_NAME_SET, OnBSprFileNameSet)
	ON_BN_CLICKED(IDC_B_SPR_FILE_NAME_DELETE, OnBSprFileNameDelete)
	ON_BN_CLICKED(IDC_B_NEW, OnBNew)
	ON_BN_CLICKED(IDC_B_LOAD, OnBLoad)
	ON_BN_CLICKED(IDC_B_SAVE, OnBSave)
	ON_BN_CLICKED(IDC_B_SAVE_AS, OnBSaveAs)
	ON_LBN_SELCHANGE(IDC_LIST_OBJ_SET, OnSelchangeListObjSet)
	ON_LBN_SELCHANGE(IDC_LIST_OBJ_SUB_SET, OnSelchangeListObjSubSet)
	ON_BN_CLICKED(IDC_B_SPR_FILE_NAME_SET2, OnBSprFileNameSet2)
	ON_BN_CLICKED(IDC_B_SPR_FILE_NAME_DELETE2, OnBSprFileNameDelete2)
	ON_BN_CLICKED(IDC_B_SPR_FILE_NAME_SET3, OnBSprFileNameSet3)
	ON_BN_CLICKED(IDC_B_SPR_FILE_NAME_SET4, OnBSprFileNameSet4)
	ON_BN_CLICKED(IDC_B_SPR_FILE_NAME_DELETE3, OnBSprFileNameDelete3)
	ON_BN_CLICKED(IDC_B_SPR_FILE_NAME_DELETE4, OnBSprFileNameDelete4)
	ON_BN_CLICKED(IDC_CHECK_SHOW_INNERHOUSE, OnCheckShowInnerhouse)
	ON_BN_CLICKED(IDC_C_OBJ_PRE_VIEW, OnCObjPreView)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTileMapObj message handlers

void CDlgTileMapObj::OnBAniFileNameSet() 
{
	int index = m_ListObjSet.GetCurSel();
	if(index < 0 || index >= MAX_MAP_OBJ_REG) return;

	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "ani", NULL, dwFlags, "���ϸ��̼�(*.ani)|*.ani||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("ANI");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();

	lstrcpy(m_MapObj.m_Header.szRegObjAniFNs[index], FileName); // ����� ���� �̸� �־��ְ�..
	m_MapObj.m_Objs[index].AniLoad(FileName); // ���ϸ��̼� �ε�
	lstrcpy(m_ShadowObj.m_Header.szRegObjAniFNs[index], FileName); // ����� ���� �̸� �־��ְ�..
	m_ShadowObj.m_Objs[index].AniLoad(FileName); // ���ϸ��̼� �ε�
	lstrcpy(m_HOutObj.m_Header.szRegObjAniFNs[index], FileName); // ����� ���� �̸� �־��ְ�..
	m_HOutObj.m_Objs[index].AniLoad(FileName); // ���ϸ��̼� �ε�
	lstrcpy(m_HInObj.m_Header.szRegObjAniFNs[index], FileName); // ����� ���� �̸� �־��ְ�..
	m_HInObj.m_Objs[index].AniLoad(FileName); // ���ϸ��̼� �ε�

	CString sz = m_MapObj.m_Header.szRegObjAniFNs[index]; // ����Ʈ�� ���� �̸� �����..
	sz += " + ";
	sz += m_MapObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_ShadowObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HOutObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HInObj.m_Header.szRegObjSprFNs[index];

	m_ListObjSet.DeleteString(index); // ����Ʈ �ڽ� ���� �ٲپ� �ְ�..
	m_ListObjSet.InsertString(index, sz);
	m_ListObjSet.SetCurSel(index);
	this->UpdateObjSubSet(); // ���� ����Ʈ ������Ʈ

	this->UpdateWorkWindow();
}

void CDlgTileMapObj::OnBAniFileNameDelete() 
{
	int index = m_ListObjSet.GetCurSel();
	if(index < 0 || index >= MAX_MAP_OBJ_REG) return;

	m_MapObj.m_Objs[index].AniRelease();
	lstrcpy(m_MapObj.m_Header.szRegObjAniFNs[index], ""); // ����� ���� �̸� �־��ְ�..
	m_ShadowObj.m_Objs[index].AniRelease();
	lstrcpy(m_ShadowObj.m_Header.szRegObjAniFNs[index], ""); // ����� ���� �̸� �־��ְ�..
	m_HOutObj.m_Objs[index].AniRelease();
	lstrcpy(m_HOutObj.m_Header.szRegObjAniFNs[index], ""); // ����� ���� �̸� �־��ְ�..
	m_HInObj.m_Objs[index].AniRelease();
	lstrcpy(m_HInObj.m_Header.szRegObjAniFNs[index], ""); // ����� ���� �̸� �־��ְ�..

	CString sz = m_MapObj.m_Header.szRegObjAniFNs[index]; // ����Ʈ�� ���� �̸� �����..
	sz += " + ";
	sz += m_MapObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_ShadowObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HOutObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HInObj.m_Header.szRegObjSprFNs[index];

	m_ListObjSet.DeleteString(index); // ����Ʈ �ڽ� ���� �ٲپ� �ְ�..
	m_ListObjSet.InsertString(index, "");
	m_ListObjSet.SetCurSel(index);
	this->UpdateObjSubSet(); // ���� ����Ʈ ������Ʈ

	this->UpdateWorkWindow();
}

void CDlgTileMapObj::OnBSprFileNameSet() 
{
	int index = m_ListObjSet.GetCurSel();
	if(index < 0 || index >= MAX_MAP_OBJ_REG) return;

	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "spl", NULL, dwFlags, "�ܼ� LSP ��������Ʈ(*.spl)|*.spl||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("SPR");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();

	lstrcpy(m_MapObj.m_Header.szRegObjSprFNs[index], FileName); // ����� ���� �̸� �־��ְ�..
	m_MapObj.m_Objs[index].SprLoad(FileName, g_pTEng->PixelFormatGet()); // ���ϸ��̼� �ε�

	CString sz = m_MapObj.m_Header.szRegObjAniFNs[index]; // ����Ʈ�� ���� �̸� �����..
	sz += " + ";
	sz += m_MapObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_ShadowObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HOutObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HInObj.m_Header.szRegObjSprFNs[index];

	m_ListObjSet.DeleteString(index); // ����Ʈ �ڽ� ���� �ٲپ� �ְ�..
	m_ListObjSet.InsertString(index, sz);
	m_ListObjSet.SetCurSel(index);
	this->UpdateObjSubSet(); // ���� ����Ʈ ������Ʈ

	this->UpdateWorkWindow();
}

void CDlgTileMapObj::OnBSprFileNameDelete() 
{
	int index = m_ListObjSet.GetCurSel();
	if(index < 0 || index >= MAX_MAP_OBJ_REG) return;

	m_MapObj.m_Objs[index].SprRelease();

	lstrcpy(m_MapObj.m_Header.szRegObjSprFNs[index], ""); // ����� ���� �̸� �־��ְ�..

	CString sz = m_MapObj.m_Header.szRegObjAniFNs[index]; // ����Ʈ�� ���� �̸� �����..
	sz += " + ";
	sz += m_MapObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_ShadowObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HOutObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HInObj.m_Header.szRegObjSprFNs[index];

	m_ListObjSet.DeleteString(index); // ����Ʈ �ڽ� ���� �ٲپ� �ְ�..
	m_ListObjSet.InsertString(index, sz);
	m_ListObjSet.SetCurSel(index);
	this->UpdateObjSubSet(); // ���� ����Ʈ ������Ʈ

	this->UpdateWorkWindow();
}

void CDlgTileMapObj::OnBSprFileNameSet2() 
{
	int index = m_ListObjSet.GetCurSel();
	if(index < 0 || index >= MAX_MAP_OBJ_REG) return;

	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "spl", NULL, dwFlags, "�ܼ� LSP ��������Ʈ(*.spl)|*.spl||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("SPR");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();

	lstrcpy(m_ShadowObj.m_Header.szRegObjSprFNs[index], FileName); // ����� ���� �̸� �־��ְ�..
	m_ShadowObj.m_Objs[index].SprLoad(FileName, g_pTEng->PixelFormatGet()); // ���ϸ��̼� �ε�

	CString sz = m_MapObj.m_Header.szRegObjAniFNs[index]; // ����Ʈ�� ���� �̸� �����..
	sz += " + ";
	sz += m_MapObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_ShadowObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HOutObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HInObj.m_Header.szRegObjSprFNs[index];

	m_ListObjSet.DeleteString(index); // ����Ʈ �ڽ� ���� �ٲپ� �ְ�..
	m_ListObjSet.InsertString(index, sz);
	m_ListObjSet.SetCurSel(index);
	this->UpdateObjSubSet(); // ���� ����Ʈ ������Ʈ

	this->UpdateWorkWindow();
}

void CDlgTileMapObj::OnBSprFileNameDelete2() 
{
	int index = m_ListObjSet.GetCurSel();
	if(index < 0 || index >= MAX_MAP_OBJ_REG) return;

	m_ShadowObj.m_Objs[index].SprRelease();

	lstrcpy(m_ShadowObj.m_Header.szRegObjSprFNs[index], ""); // ����� ���� �̸� �־��ְ�..

	CString sz = m_MapObj.m_Header.szRegObjAniFNs[index]; // ����Ʈ�� ���� �̸� �����..
	sz += " + ";
	sz += m_MapObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_ShadowObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HOutObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HInObj.m_Header.szRegObjSprFNs[index];

	m_ListObjSet.DeleteString(index); // ����Ʈ �ڽ� ���� �ٲپ� �ְ�..
	m_ListObjSet.InsertString(index, sz);
	m_ListObjSet.SetCurSel(index);
	this->UpdateObjSubSet(); // ���� ����Ʈ ������Ʈ

	this->UpdateWorkWindow();
}

void CDlgTileMapObj::UpdateWorkWindow()
{
	CWnd* pWnd = this->GetOwner();
	if(pWnd)
		pWnd->InvalidateRect(NULL, FALSE);
}

void CDlgTileMapObj::OnBNew() 
{
	m_MapObj.ReleaseEx();
	m_ShadowObj.ReleaseEx();
	m_HOutObj.ReleaseEx();
	m_HInObj.ReleaseEx();
	
	this->UpdateObjInfo();

	SetDlgItemText(IDC_E_FILE_NAME, "");
}

void CDlgTileMapObj::OnBLoad() 
{
	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "mod", NULL, dwFlags, "Map, Object ��ġ ������(*.mod)|*.mod||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("MAP");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();

	HANDLE hFile;
	hFile = CreateFile(FileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{ 
		OutputDebugString("Ÿ�ϸ� ������ ���� ���� ���� : ");
		OutputDebugString(FileName);
		OutputDebugString("\n");
		return;
	}

	DWORD dwAccessed = 0;
	int version;

	ReadFile(hFile, &version, sizeof(int), &dwAccessed, NULL);

	m_MapObj.ReleaseEx(); // ����
	m_MapObj.Load(hFile); // �θ���
	for(int i = 0; i < MAX_MAP_OBJ_REG; i++) // ��ü�� �ε�.
	{
		g_pTEng->PathSetCur("ANI");
		m_MapObj.m_Objs[i].AniLoad(m_MapObj.m_Header.szRegObjAniFNs[i]);
		g_pTEng->PathSetCur("SPR");
		m_MapObj.m_Objs[i].SprLoad(m_MapObj.m_Header.szRegObjSprFNs[i], g_pTEng->PixelFormatGet());
	}
	if(m_MapObj.m_pTData)
	{
		for(i = 0; i < m_MapObj.m_vTCount; i++)
		{
			if(m_MapObj.m_pTData[i].value < 0) continue;
			
			int nSet = m_MapObj.m_pTData[i].value >> 8; // ������Ʈ ��Ʈ
			if(nSet < 0 || nSet >= MAX_MAP_OBJ_REG) continue;
			int nSubSet = m_MapObj.m_pTData[i].value & 0xff; // ������Ʈ ���� ��Ʈ
			if(nSubSet < 0) continue;
			
			CAniObjLSP* pAniObj = &m_MapObj.m_Objs[nSet];
			const _SPR_LSP* pSpr = NULL;
			int nSpr = pAniObj->FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
			pAniObj->SprGet(nSpr, &pSpr);
			if(pSpr == NULL)
			{
				m_MapObj.m_pnData[m_MapObj.m_pTData[i].index] = -1;
				TRACE("M(%d,%d) : %d,%d\n", m_MapObj.m_pTData[i].index%m_MapObj.m_Header.nWidth,
					m_MapObj.m_pTData[i].index/m_MapObj.m_Header.nWidth, nSet, nSubSet);
			}
		}
		delete[] m_MapObj.m_pTData;
		m_MapObj.m_pTData = NULL;
	}
	m_ShadowObj.ReleaseEx(); // ����
	m_ShadowObj.Load(hFile); // �θ���
	for(i = 0; i < MAX_MAP_OBJ_REG; i++) // ��ü�� �ε�.
	{
		g_pTEng->PathSetCur("ANI");
		m_ShadowObj.m_Objs[i].AniLoad(m_ShadowObj.m_Header.szRegObjAniFNs[i]);
		g_pTEng->PathSetCur("SPR");
		m_ShadowObj.m_Objs[i].SprLoad(m_ShadowObj.m_Header.szRegObjSprFNs[i], g_pTEng->PixelFormatGet());
	}
	if(m_ShadowObj.m_pTData)
	{
		for(i = 0; i < m_ShadowObj.m_vTCount; i++)
		{
			if(m_ShadowObj.m_pTData[i].value < 0) continue;
			
			int nSet = m_ShadowObj.m_pTData[i].value >> 8; // ������Ʈ ��Ʈ
			if(nSet < 0 || nSet >= MAX_MAP_OBJ_REG) continue;
			int nSubSet = m_ShadowObj.m_pTData[i].value & 0xff; // ������Ʈ ���� ��Ʈ
			if(nSubSet < 0) continue;
			
			CAniObjLSP* pAniObj = &m_ShadowObj.m_Objs[nSet];
			const _SPR_LSP* pSpr = NULL;
			int nSpr = pAniObj->FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
			pAniObj->SprGet(nSpr, &pSpr);
			if(pSpr == NULL)
			{
				m_ShadowObj.m_pnData[m_ShadowObj.m_pTData[i].index] = -1;
				TRACE("S(%d,%d) : %d,%d\n", m_ShadowObj.m_pTData[i].index%m_ShadowObj.m_Header.nWidth,
					m_ShadowObj.m_pTData[i].index/m_ShadowObj.m_Header.nWidth, nSet, nSubSet);
			}
		}
		delete[] m_ShadowObj.m_pTData;
		m_ShadowObj.m_pTData = NULL;
	}
//	m_HOutObj.Realloc(m_MapObj.m_Header.nWidth, m_MapObj.m_Header.nHeight);
//	m_HInObj.Realloc(m_MapObj.m_Header.nWidth, m_MapObj.m_Header.nHeight);
	m_HOutObj.ReleaseEx(); // ����
	m_HOutObj.Load(hFile); // �θ���
	for(i = 0; i < MAX_MAP_OBJ_REG; i++) // ��ü�� �ε�.
	{
		g_pTEng->PathSetCur("ANI");
		m_HOutObj.m_Objs[i].AniLoad(m_HOutObj.m_Header.szRegObjAniFNs[i]);
		g_pTEng->PathSetCur("SPR");
		m_HOutObj.m_Objs[i].SprLoad(m_HOutObj.m_Header.szRegObjSprFNs[i], g_pTEng->PixelFormatGet());
	}
	if(m_HOutObj.m_pTData)
	{
		for(i = 0; i < m_HOutObj.m_vTCount; i++)
		{
			if(m_HOutObj.m_pTData[i].value < 0) continue;
			
			int nSet = m_HOutObj.m_pTData[i].value >> 8; // ������Ʈ ��Ʈ
			if(nSet < 0 || nSet >= MAX_MAP_OBJ_REG) continue;
			int nSubSet = m_HOutObj.m_pTData[i].value & 0xff; // ������Ʈ ���� ��Ʈ
			if(nSubSet < 0) continue;
			
			CAniObjLSP* pAniObj = &m_HOutObj.m_Objs[nSet];
			const _SPR_LSP* pSpr = NULL;
			int nSpr = pAniObj->FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
			pAniObj->SprGet(nSpr, &pSpr);
			if(pSpr == NULL)
			{
				m_HOutObj.m_pnData[m_HOutObj.m_pTData[i].index] = -1;
				TRACE("HO(%d,%d) : %d,%d\n", m_HOutObj.m_pTData[i].index%m_HOutObj.m_Header.nWidth,
					m_HOutObj.m_pTData[i].index/m_HOutObj.m_Header.nWidth, nSet, nSubSet);
			}
		}
		delete[] m_HOutObj.m_pTData;
		m_HOutObj.m_pTData = NULL;
	}
	m_HInObj.ReleaseEx(); // ����
	m_HInObj.Load(hFile); // �θ���
	for(i = 0; i < MAX_MAP_OBJ_REG; i++) // ��ü�� �ε�.
	{
		g_pTEng->PathSetCur("ANI");
		m_HInObj.m_Objs[i].AniLoad(m_HInObj.m_Header.szRegObjAniFNs[i]);
		g_pTEng->PathSetCur("SPR");
		m_HInObj.m_Objs[i].SprLoad(m_HInObj.m_Header.szRegObjSprFNs[i], g_pTEng->PixelFormatGet());
	}
	if(m_HInObj.m_pTData)
	{
		for(i = 0; i < m_HInObj.m_vTCount; i++)
		{
			if(m_HInObj.m_pTData[i].value < 0) continue;
			
			int nSet = m_HInObj.m_pTData[i].value >> 8; // ������Ʈ ��Ʈ
			if(nSet < 0 || nSet >= MAX_MAP_OBJ_REG) continue;
			int nSubSet = m_HInObj.m_pTData[i].value & 0xff; // ������Ʈ ���� ��Ʈ
			if(nSubSet < 0) continue;
			
			CAniObjLSP* pAniObj = &m_HInObj.m_Objs[nSet];
			const _SPR_LSP* pSpr = NULL;
			int nSpr = pAniObj->FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
			pAniObj->SprGet(nSpr, &pSpr);
			if(pSpr == NULL)
			{
				m_HInObj.m_pnData[m_ShadowObj.m_pTData[i].index] = -1;
				TRACE("HI(%d,%d) : %d,%d\n", m_HInObj.m_pTData[i].index%m_HInObj.m_Header.nWidth,
					m_HInObj.m_pTData[i].index/m_HInObj.m_Header.nWidth, nSet, nSubSet);
			}
		}
		delete[] m_HInObj.m_pTData;
		m_HInObj.m_pTData = NULL;
	}

	CloseHandle(hFile);

	this->UpdateObjInfo(); // ��ȭ ���� ������Ʈ

	SetDlgItemInt(IDC_E_WIDTH, m_MapObj.m_Header.nWidth);
	SetDlgItemInt(IDC_E_HEIGHT, m_MapObj.m_Header.nHeight);
	SetDlgItemText(IDC_E_FILE_NAME, FileName);
	
	this->UpdateWorkWindow();
}

void CDlgTileMapObj::OnBSave() 
{
	CString FileName;
	GetDlgItemText(IDC_E_FILE_NAME, FileName);

	if(FileName.GetLength() <= 0) 
	{
		this->OnBSaveAs();
		return;
	}
	
	g_pTEng->PathSetCur("MAP");
	
	CFile file;

	file.Open(FileName, CFile::modeWrite | CFile::modeCreate);

	file.Write(&m_vCurrentVersion, sizeof(int));

	m_MapObj.Save(file);
	m_ShadowObj.Save(file);
	m_HOutObj.Save(file);
	m_HInObj.Save(file);

	file.Close();
}

void CDlgTileMapObj::OnBSaveAs() 
{
	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(FALSE, "mod", NULL, dwFlags, "Map Object Data(*.mod)|*.mod||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("MAP");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();

	SetDlgItemText(IDC_E_FILE_NAME, FileName);

	this->OnBSave();
}

void CDlgTileMapObj::OnBSetSize() 
{
	int nW = GetDlgItemInt(IDC_E_WIDTH);
	int nH = GetDlgItemInt(IDC_E_HEIGHT);

	m_MapObj.Realloc(nW, nH); // ������Ʈ �� �ٽ� �Ҵ�.
	m_ShadowObj.Realloc(nW, nH); // �׸��� ������Ʈ �� �ٽ� �Ҵ�.
	m_HOutObj.Realloc(nW, nH); // ������Ʈ �� �ٽ� �Ҵ�.
	m_HInObj.Realloc(nW, nH); // �׸��� ������Ʈ �� �ٽ� �Ҵ�.
	this->UpdateWorkWindow();
}

void CDlgTileMapObj::OnSelchangeListObjSet() 
{
	this->UpdateObjSubSet();
	this->UpdateWorkWindow();
}

void CDlgTileMapObj::OnSelchangeListObjSubSet() 
{
	// TODO: Add your control notification handler code here
	if(m_pWndObjPreview) m_pWndObjPreview->InvalidateRect(NULL,FALSE);
}

void CDlgTileMapObj::UpdateObjInfo()
{
	m_ListObjSet.ResetContent();
	for(int i = 0; i < MAX_MAP_OBJ_REG; i++)
	{
		CString sz = m_MapObj.m_Header.szRegObjAniFNs[i];
		sz += " + ";
		sz += m_MapObj.m_Header.szRegObjSprFNs[i];
		sz += " + ";
		sz += m_ShadowObj.m_Header.szRegObjSprFNs[i];
		sz += " + ";
		sz += m_HOutObj.m_Header.szRegObjSprFNs[i];
		sz += " + ";
		sz += m_HInObj.m_Header.szRegObjSprFNs[i];
		m_ListObjSet.AddString(sz);
	}
	m_ListObjSet.SetCurSel(0);

	this->UpdateObjSubSet(); // ����� ���� ��Ÿ����.

	SetDlgItemInt(IDC_E_WIDTH, m_MapObj.m_Header.nWidth);
	SetDlgItemInt(IDC_E_HEIGHT, m_MapObj.m_Header.nHeight);
}

void CDlgTileMapObj::UpdateObjSubSet()
{
	m_ListObjSubSet.ResetContent();

	int index = m_ListObjSet.GetCurSel();
	if(index < 0 || index >= MAX_MAP_OBJ_REG) return;

	int nAniQt = m_MapObj.m_Objs[index].m_HAni.nQt;

	for(int i = 0; i < nAniQt; i++)
	{
		_ANI_DATA* pData = m_MapObj.m_Objs[index].AniDataGet(i);
		if(pData) m_ListObjSubSet.AddString(pData->szName);
	}
	m_ListObjSubSet.SetCurSel(0);
}


BOOL CDlgTileMapObj::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	((CButton *)GetDlgItem(IDC_CHECK_SHOW_INNERHOUSE))->SetCheck(m_bShowInnerHouse);
	this->UpdateObjInfo();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

short int CDlgTileMapObj::GetSelectedObjData()
{
	int index = m_ListObjSet.GetCurSel();
	if(index < 0 || index >= MAX_MAP_OBJ_REG) return -1;
	
	int index2 = m_ListObjSubSet.GetCurSel();
	if(index2 < 0 || index2 >= MAX_ANI) return -1;

	return ((index<<8)|index2); // ���� ����Ʈ�� ��Ʈ ��ȣ, ���� ����Ʈ�� ����� ��ȣ
}

void CDlgTileMapObj::OnBSprFileNameSet3() 
{
	int index = m_ListObjSet.GetCurSel();
	if(index < 0 || index >= MAX_MAP_OBJ_REG) return;

	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "spl", NULL, dwFlags, "�ܼ� LSP ��������Ʈ(*.spl)|*.spl||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("SPR");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();

	lstrcpy(m_HOutObj.m_Header.szRegObjSprFNs[index], FileName); // ����� ���� �̸� �־��ְ�..
	m_HOutObj.m_Objs[index].SprLoad(FileName, g_pTEng->PixelFormatGet()); // ���ϸ��̼� �ε�

	CString sz = m_MapObj.m_Header.szRegObjAniFNs[index]; // ����Ʈ�� ���� �̸� �����..
	sz += " + ";
	sz += m_MapObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_ShadowObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HOutObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HInObj.m_Header.szRegObjSprFNs[index];

	m_ListObjSet.DeleteString(index); // ����Ʈ �ڽ� ���� �ٲپ� �ְ�..
	m_ListObjSet.InsertString(index, sz);
	m_ListObjSet.SetCurSel(index);
	this->UpdateObjSubSet(); // ���� ����Ʈ ������Ʈ

	this->UpdateWorkWindow();
}

void CDlgTileMapObj::OnBSprFileNameSet4() 
{
	int index = m_ListObjSet.GetCurSel();
	if(index < 0 || index >= MAX_MAP_OBJ_REG) return;

	CString FileName;
	DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
	CFileDialog dlg(TRUE, "spl", NULL, dwFlags, "�ܼ� LSP ��������Ʈ(*.spl)|*.spl||", NULL);
	dlg.m_ofn.lpstrInitialDir = g_pTEng->PathGetCur("SPR");
	if(dlg.DoModal() == IDCANCEL) return;

	FileName = dlg.GetFileName();

	lstrcpy(m_HInObj.m_Header.szRegObjSprFNs[index], FileName); // ����� ���� �̸� �־��ְ�..
	m_HInObj.m_Objs[index].SprLoad(FileName, g_pTEng->PixelFormatGet()); // ���ϸ��̼� �ε�

	CString sz = m_MapObj.m_Header.szRegObjAniFNs[index]; // ����Ʈ�� ���� �̸� �����..
	sz += " + ";
	sz += m_MapObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_ShadowObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HOutObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HInObj.m_Header.szRegObjSprFNs[index];

	m_ListObjSet.DeleteString(index); // ����Ʈ �ڽ� ���� �ٲپ� �ְ�..
	m_ListObjSet.InsertString(index, sz);
	m_ListObjSet.SetCurSel(index);
	this->UpdateObjSubSet(); // ���� ����Ʈ ������Ʈ

	this->UpdateWorkWindow();
}

void CDlgTileMapObj::OnBSprFileNameDelete3() 
{
	int index = m_ListObjSet.GetCurSel();
	if(index < 0 || index >= MAX_MAP_OBJ_REG) return;

	m_HOutObj.m_Objs[index].SprRelease();

	lstrcpy(m_HOutObj.m_Header.szRegObjSprFNs[index], ""); // ����� ���� �̸� �־��ְ�..

	CString sz = m_MapObj.m_Header.szRegObjAniFNs[index]; // ����Ʈ�� ���� �̸� �����..
	sz += " + ";
	sz += m_MapObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_ShadowObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HOutObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HInObj.m_Header.szRegObjSprFNs[index];

	m_ListObjSet.DeleteString(index); // ����Ʈ �ڽ� ���� �ٲپ� �ְ�..
	m_ListObjSet.InsertString(index, sz);
	m_ListObjSet.SetCurSel(index);
	this->UpdateObjSubSet(); // ���� ����Ʈ ������Ʈ

	this->UpdateWorkWindow();
}

void CDlgTileMapObj::OnBSprFileNameDelete4() 
{
	int index = m_ListObjSet.GetCurSel();
	if(index < 0 || index >= MAX_MAP_OBJ_REG) return;

	m_HInObj.m_Objs[index].SprRelease();

	lstrcpy(m_HInObj.m_Header.szRegObjSprFNs[index], ""); // ����� ���� �̸� �־��ְ�..

	CString sz = m_MapObj.m_Header.szRegObjAniFNs[index]; // ����Ʈ�� ���� �̸� �����..
	sz += " + ";
	sz += m_MapObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_ShadowObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HOutObj.m_Header.szRegObjSprFNs[index];
	sz += " + ";
	sz += m_HInObj.m_Header.szRegObjSprFNs[index];

	m_ListObjSet.DeleteString(index); // ����Ʈ �ڽ� ���� �ٲپ� �ְ�..
	m_ListObjSet.InsertString(index, sz);
	m_ListObjSet.SetCurSel(index);
	this->UpdateObjSubSet(); // ���� ����Ʈ ������Ʈ

	this->UpdateWorkWindow();
}

void CDlgTileMapObj::OnCheckShowInnerhouse() 
{
	m_bShowInnerHouse = ((CButton *)GetDlgItem(IDC_CHECK_SHOW_INNERHOUSE))->GetCheck();
	this->UpdateWorkWindow();
}

void CDlgTileMapObj::OnCObjPreView() 
{
	if(IsDlgButtonChecked(IDC_C_OBJ_PRE_VIEW) == 1)
	{
		m_pWndObjPreview = new CWndObjPreview( this );
		if(m_pWndObjPreview)
		{
			// Ÿ�� ���ϸ��̼� ������ ������...
			if(m_pWndObjPreview->GetSafeHwnd() == NULL)
			{
				HCURSOR hCur = LoadCursor(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDC_C_NORMAL));
				CString szWndClass;
				szWndClass = AfxRegisterWndClass(CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW, hCur, NULL, 0);
				m_pWndObjPreview->CreateEx(NULL,
										szWndClass,
										"������Ʈ ������",
										WS_OVERLAPPEDWINDOW,
										CW_USEDEFAULT,
										CW_USEDEFAULT,
										256,
										256,
										this->m_hWnd,
										NULL);
			}
			m_pWndObjPreview->ShowWindow(SW_SHOW);
		}
	}
	else
	{
		if( m_pWndObjPreview )
		{
			m_pWndObjPreview->DestroyWindow();
			delete m_pWndObjPreview;
		}
		m_pWndObjPreview = NULL;
	}
}

void CDlgTileMapObj::OnDestroy() 
{
	CDialog::OnDestroy();
	
	if( m_pWndObjPreview )
	{
		if( m_pWndObjPreview->GetSafeHwnd != NULL )
			m_pWndObjPreview->DestroyWindow();
		delete m_pWndObjPreview;
	}
	m_pWndObjPreview = NULL;
}
