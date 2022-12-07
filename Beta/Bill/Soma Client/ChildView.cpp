// ChildView.cpp : implementation of the CChildView class
//

#include "stdafx.h"
#include "Soma.h"
#include "ChildView.h"
#include "DManage/BB_Direct.h"
#include "DManage/AlphaProcess.h"
#include "DManage/BBDX_MouseInformation.h"
#include "DManage/Direct3d.h"
#include "DManage/Night.h"
#include "MainFrm.h"
#include "User.h"
#include "PacketParser.h"
#include "BBDX_Editor.h"
#include "BBDX_ChatEditor.h"
#include "BBDX_ChatOuter.h"
#include "SMProtocol.h"
#include "Magic.h"
#include "Msg.h"
#include "SoundDef.h"
#include "BaseDraw.h"

#include "dmusicc.h"
#include "DManage/DirectSound.h"

#include <math.h>

  //(���)
#include "FogEffect.h"

#include "Dialog_Login.h"

#include "Dialog_Main.h"
#include "Dialog_SmallMain.h"
#include "Dialog_DeadMain.h"
#include "Dialog_BoardCtrl.h"
#include "Dialog_Shop.h"
#include "Dialog_Status.h"
#include "Dialog_Inv.h"
#include "Dialog_Option.h"
#include "Dialog_Storage.h"
#include "Dialog_MakeItem.h"
#include "Dialog_MemoCtrl.h"
#include "Dialog_MagicCtrl.h"
#include "Dialog_Exchange.h"
#include "Dialog_Message.h"
#include "Dialog_Message2.h"
#include "Dialog_Message3.h"
#include "Dialog_HowMuch.h"
#include "Dialog_AuctionSell.h"
#include "Dialog_AuctionBuy.h"
#include "Dialog_AuctionDetail.h"
#include "Dialog_Name.h"
#include "Dialog_Chat.h"
#include "Dialog_Crest.h"
#include "Dialog_GuildPositionName.h"
#include "Dialog_TaxRate.h"
#include "Dialog_Quit.h"
#include "Dialog_HowMany.h"
#include "Dialog_GuildMenu1.h"
#include "Dialog_GuildMenu2.h"
#include "Dialog_GuildMenu3.h"
#include "Dialog_GuildMenu5.h"
#include "Dialog_GuildName.h"
#include "Dialog_GuildApply.h"
#include "Dialog_Guild.h"
#include "Dialog_GuildJoin.h"
#include "Dialog_Repair.h"

#include "Dialog_EventMessage.h"
#include "Dialog_EventMessage1.h"
#include "Dialog_EventMessage2.h"
#include "Dialog_AccountLogin.h"

#include "Item_Total.h"
#include "Item_Inv.h"
#include "Item_Field.h"

#include "BuildHouseManager.h"
#include "HousePlaceManager.h"

#include "Notice.h"
#include "SMProtocol.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

CChildView			*g_pChildView;
DirectXMng			CChildView::DirectXMng;
SocketMng			CChildView::SocketMng;
SM_MapManager		CChildView::MapManager;
CCharManager		CChildView::CharManager;
CUserManager		CChildView::UserManager;
CPacketParser		CChildView::PacketParser;
CMagicManager		CChildView::MagicManager;
CArmatureManager	CChildView::ArmatureManager;
CWeather			CChildView::Weather;
CTileMapTool        CChildView::TileMapTool;
CTileSetTool        CChildView::TileSetTool;
CDDEngineNew        CChildView::g_pTEng;
//CDDEngineLSP        CChildView::g_pTEng;
CMapObj             CChildView::MapObj;
CMapObj             CChildView::MapShadowObj;
CMapObj				CChildView::MapHouseIn;
CMapObj				CChildView::MapHouseOut;


CAniObjLSP			CChildView::MapAniObjs[MAX_MAP_OBJ_REG];
CAniObjLSP			CChildView::MapShadowAniObjs[MAX_MAP_OBJ_REG];
CAniObjLSP			CChildView::MapAniHouseIn[MAX_MAP_OBJ_REG];
CAniObjLSP			CChildView::MapAniHouseOut[MAX_MAP_OBJ_REG];

CLightSource		CChildView::m_LightSource; 
//CArray<CPoint,CPoint> CChildView::m_ptLightPos;
CArray<LIGHT_INFO,LIGHT_INFO> CChildView::m_ptLightPos;
CFont				*CChildView::pAppFont;
int					CChildView::bDlgIn;
CBaseDraw			g_BaseDraw;

//(���)
CFogEffect          FogEffect;          //�Ȱ� ȿ��...

//�켮.
//CDialog_Login       Dialog_Login;
CDialog_AccountLogin *GDialog_AccountLogin;
//CDialog_Login        *GDialog_Login;


CDialog_Main		Dialog_Main;
CDialog_SmallMain	Dialog_SmallMain;
CDialog_DeadMain	Dialog_DeadMain;
CDialog_BoardCtrl	Dialog_BoardCtrl;
CDialog_Shop		Dialog_Shop;
CDialog_Status		Dialog_Status;
CDialog_Inv			Dialog_Inv;
CDialog_Option		Dialog_Option;
CDialog_Storage		Dialog_Storage;
CDialog_MakeItem	Dialog_MakeItem;
CDialog_MemoCtrl	Dialog_MemoCtrl;
CDialog_MagicCtrl	Dialog_MagicCtrl;
CDialog_Exchange	Dialog_Exchange;
CDialog_Message		Dialog_Message;
CDialog_Message2	Dialog_Message2;
CDialog_Message3	Dialog_Message3;
CDialog_HowMuch		Dialog_HowMuch;
CDialog_HowMany		Dialog_HowMany;
CDialog_Name		Dialog_Name;
CDialog_AuctionSell	Dialog_AuctionSell;
CDialog_AuctionBuy	Dialog_AuctionBuy;
CDialog_AuctionDetail Dialog_AuctionDetail;
CDialog_Chat		Dialog_Chat;
CDialog_Crest		Dialog_Crest;
CDialog_GuildPositionName Dialog_GuildPositionName;
CDialog_TaxRate		Dialog_TaxRate;
CDialog_Quit		Dialog_Quit;
CDialog_GuildMenu1	Dialog_GuildMenu1;
CDialog_GuildMenu2	Dialog_GuildMenu2;
CDialog_GuildMenu3	Dialog_GuildMenu3;
CDialog_GuildName	Dialog_GuildName;
CDialog_GuildApply	Dialog_GuildApply;
CDialog_Guild		Dialog_Guild;
CDialog_GuildJoin	Dialog_GuildJoin;
CDialog_Repair		Dialog_Repair;

CUIRes				*g_pShowDialog;
CUIRes				*g_pFocusDialog;
CUIRes				*g_pCaptureDialog;

CDialog_EventMessage Dialog_EventMessage;
CDialog_EventMessage1 Dialog_EventMessage1;
CDialog_EventMessage2 Dialog_EventMessage2;

//CItem               Item;
CItem_Total         Item_Total;
//�켮... �����ͷ� �ٲ�...... 9�� 9��...
CItem_Inv           *Item_Inv;// �κ��丮 ĳ����â�� ���� �׷���..�Ź� �о� ���δ�..�ٲ𶧸���..���������??�����̴ϱ�..
CItem_Inv           *Item_Inv2;
CItem_Inv           *Item_Inv3;// �ʱ� �޴�â�� ��Ÿ���� ĳ���͵� ǥ���ϱ� ����..������..
//�켮.

CItem_Field         Item_Field;

CBuildHouseManager	BuildHouseManager;
CHousePlaceManager	HousePlaceManager;

CPoint g_vEventPos;
CWnd				*g_pFocusWnd;

CMap<int, int, char *, char *&> g_SoundName;
CMap<int, int, char *, char *&> g_MusicName;

static RECT *g_MapPos;
static BOOL *g_MapLoading;
static CArray<int, int> *g_MapRsc;
static int	g_MapPosCount;
static CRect g_vLoadingRect;
static BYTE m_bKeyDown[255];

BOOL					g_bDisplayDate;			// ��¥�� ǥ���� ������ �÷���
DWORD					g_vRenderTime;
DWORD					g_vFaTime;
int						g_vMainMode, g_vCurMainMode;
SIZE					g_vDispPixSize, g_vDispCellSize;
int						g_vMapNumber, g_vOldMapNumber, g_mainSoundIndex, g_vCurMusicNumber;
DWORD					g_vStartMapTime;

#define INFO_NAMES				0X01
#define INFO_BASICVALUE			0X02
#define INFO_EXTVALUE			0X04
#define INFO_WEAPONEXP			0X08
#define INFO_MAKEEXP			0X10
#define INFO_MAGICEXP			0X20
void DisplayRRStats(DirectXMng &dxMng);

VOID GetDXVersion( DWORD* pdwDXVersion, DWORD* pdwDXPlatform );
//DWORD t_time1[12], t_time2[12];
/////////////////////////////////////////////////////////////////////////////
// CChildView

//�׽�Ʈ�� gammaramp
DDGAMMARAMP g_gammaramp;

CChildView::CChildView()
{
	//Standard Gamma Value
	for (int i=0; i<256; i++)
	{
		g_gammaramp.red[i] = i*257;
		g_gammaramp.green[i] = i*257;
		g_gammaramp.blue[i] = i*257;
	}

	InitStaticVariables();

	m_ptMapOffset.x = 0;
	m_ptMapOffset.y = 0;

	m_Mouse_In = 0;// ���� ���ȿ� ����..1

	PacketParser.m_bpConnectedView = this;
	m_iMyId = -1;//Invalid State
	m_pBBDX_Editor = NULL;
	m_pChatOuter = NULL;
	m_pBBDX_Editor_id = NULL;
	m_pBBDX_Editor_password = NULL;

	m_test_Flag = 1;
	m_Login_Char = 0;// �����ϴ� ĳ����..���..

	m_Chattype = 1;// �븻 ä��...
	m_S_Connection = 0;// ���ǿ� ����Ǿ������� 1

	for(i=0;i<9;i++)
		m_Old_Item_Type[i] = -100;// �����Ⱚ..

	m_CurMemoChatId = _T("");

	for(i = 0;i<1000;i++)
	{
		m_Item_Pic_Index[i] = 0;
		m_Arm_type[i] = -1; //10�� 16��.. �켮..
		m_Draw_Order[i] = 0;
	}
	
	g_pFocusDialog = NULL;

	GDialog_AccountLogin = NULL;
	g_pChildView = this;

	//�켮.
 	m_CharData[0] =	NULL;
	m_CharData[1] =	NULL;
	m_CharData[2] =	NULL;

	m_LoadinView = NULL;

//�켮.. �����ͷ� �ٲ�.. 9�� 9��..
	Item_Inv = new CItem_Inv;
	Item_Inv2 = new CItem_Inv;
	Item_Inv3 = new CItem_Inv;

	m_bMakeChar = false;
	m_bMakeFail = false;
	m_bMakeProcess = false;
	m_CharNum = 0; //ĳ���� ����.
	g_pFocusWnd = NULL;

	m_bAccountNewOk = true;
	m_bLoginOk = true;

	g_bDisplayDate = TRUE;
	g_MapPos = NULL;
	g_MapLoading = NULL;
	g_MapRsc = NULL;
	g_MapPosCount = 0;

	bDlgIn = 0;
	ZeroMemory(m_bKeyDown, 255);
	m_RestartGame = false;

	g_vMainMode = g_vCurMainMode = -1;

	m_PathFindGap = 0;
	g_vMapNumber = -1;
	g_vOldMapNumber = -1;
	g_mainSoundIndex = -1;

	m_bCtrlUp = true;
}

CChildView::~CChildView()
{
	SAFE_DELETE(m_pBBDX_Editor);
	SAFE_DELETE(m_pChatOuter);
	SAFE_DELETE(m_pBBDX_Editor_password);
	SAFE_DELETE(m_pBBDX_Editor_id);
//	SAFE_DELETE(GDialog_AccountLogin);
	g_pChildView = NULL;

	//�켮
	SAFE_DELETE(m_CharData[0]);
	SAFE_DELETE(m_CharData[1]);
	SAFE_DELETE(m_CharData[2]);

	//�켮.. �����ͷ� �ٲ�.. 9�� 9��..
	SAFE_DELETE(Item_Inv3);
	SAFE_DELETE(Item_Inv2);
	SAFE_DELETE(Item_Inv);

	if(g_MapPos)
	{
		delete[] g_MapPos;
		delete[] g_MapLoading;
		for(int i = 0; i < g_MapPosCount; i++) g_MapRsc[i].RemoveAll();
		delete[] g_MapRsc;
	}
	if(g_SoundName.IsEmpty() == FALSE)
	{
		POSITION pos;
		int key;
		char *value;

		pos = g_SoundName.GetStartPosition();
		while(pos)
		{
			g_SoundName.GetNextAssoc(pos, key, value);
			delete[] value;
		}
		g_SoundName.RemoveAll();
	}
	if(g_MusicName.IsEmpty() == FALSE)
	{
		POSITION pos;
		int key;
		char *value;

		pos = g_MusicName.GetStartPosition();
		while(pos)
		{
			g_MusicName.GetNextAssoc(pos, key, value);
			delete[] value;
		}
		g_MusicName.RemoveAll();
	}
}


BEGIN_MESSAGE_MAP(CChildView,CWnd )
	//{{AFX_MSG_MAP(CChildView)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_MESSAGE(WM_PACKET_ARRIVED, OnPacketProcess)
	ON_MESSAGE(WM_PACKET_PROCESS_PENDING, OnPacketPending)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_SYSKEYDOWN()
	ON_WM_CHAR()
	ON_MESSAGE(WM_IME_STARTCOMPOSITION, OnImeStartComposition)
	ON_MESSAGE(WM_IME_COMPOSITION, OnImeComposition)
	ON_MESSAGE(WM_IME_ENDCOMPOSITION, OnImeEndComposition)
	ON_MESSAGE(WM_IME_COMPOSITIONFULL, OnImeCompositionFull)
	ON_WM_KEYUP()
	ON_WM_SYSKEYUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), HBRUSH(COLOR_WINDOW+1), NULL);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}
#include "DxCursor.h"
BOOL CChildView::DDInit()
{
	DWORD dx_version, platform_version;

	GetDXVersion(&dx_version, &platform_version);

	if(dx_version < 0x700)
	{
		switch(dx_version)
		{
		case 0:
			AfxMessageBox("���� DirectX�� ��ġ�Ǿ� ���� �ʽ��ϴ�.\nDirectX 7.0 �̻��� ��ġ�Ͻð� �ٽ� ������� �ֽʽÿ�.", MB_OK|MB_ICONINFORMATION);
			break;
		case 0x100:
			AfxMessageBox("���� DirectX 1.0�� ��ġ�Ǿ� �ֽ��ϴ�.\nDirectX 7.0 �̻��� ��ġ�Ͻð� �ٽ� ������� �ֽʽÿ�.", MB_OK|MB_ICONINFORMATION);
			break;
		case 0x200:
			AfxMessageBox("���� DirectX 2.0�� ��ġ�Ǿ� �ֽ��ϴ�.\nDirectX 7.0 �̻��� ��ġ�Ͻð� �ٽ� ������� �ֽʽÿ�.", MB_OK|MB_ICONINFORMATION);
			break;
		case 0x300:
			AfxMessageBox("���� DirectX 3.0�� ��ġ�Ǿ� �ֽ��ϴ�.\nDirectX 7.0 �̻��� ��ġ�Ͻð� �ٽ� ������� �ֽʽÿ�.", MB_OK|MB_ICONINFORMATION);
			break;
		case 0x500:
			AfxMessageBox("���� DirectX 5.0�� ��ġ�Ǿ� �ֽ��ϴ�.\nDirectX 7.0 �̻��� ��ġ�Ͻð� �ٽ� ������� �ֽʽÿ�.", MB_OK|MB_ICONINFORMATION);
			break;
		case 0x600:
			AfxMessageBox("���� DirectX 6.0�� ��ġ�Ǿ� �ֽ��ϴ�.\nDirectX 7.0 �̻��� ��ġ�Ͻð� �ٽ� ������� �ֽʽÿ�.", MB_OK|MB_ICONINFORMATION);
			break;
		case 0x601:
			AfxMessageBox("���� DirectX 6.1�� ��ġ�Ǿ� �ֽ��ϴ�.\nDirectX 7.0 �̻��� ��ġ�Ͻð� �ٽ� ������� �ֽʽÿ�.", MB_OK|MB_ICONINFORMATION);
			break;
		default:
			AfxMessageBox("DirectX 7.0 �̻��� ��ġ�Ͻð� �ٽ� ������� �ֽʽÿ�.", MB_OK|MB_ICONINFORMATION);
			break;
		}
		return FALSE;
	}

	BOOL bFullScreen = __GetMainWnd()->m_bFullScreen;
//	BOOL bInitOk = DirectXMng.InitDirectX(640, 480, 16, bFullScreen); //640X480 , 16bit ���� ����
	BOOL bInitOk = DirectXMng.InitDirectX(800, 600, 16, bFullScreen); //640X480 , 16bit ���� ����
//	BOOL bInitOk = DirectXMng.InitDirectX(1024, 768, 16, bFullScreen); //640X480 , 16bit ���� ����

    IDirectDraw * pdd;
    HRESULT hr = ::DirectDrawCreate(NULL, &pdd, NULL);
    if (FAILED(hr)) TRACE("���̷�Ʈ ���� ����� �� �����ߴ�. \n");

    // Query IDirectDraw4 interface and release the IDirectDraw4 interface
//  hr = pdd->QueryInterface(IID_IDirectDraw, (void**)g_pTEng.m_lpDD4);
//	pdd->Release();

//	DirectXMng.m_pDD->m_pIDD
// Query IDirectDraw4 interface and release the IDirectDraw4 interface
//	DirectDrawCreate(NULL,&m_lpDD,NULL);
//	m_lpDD->QueryInterface(IID_IDirectDraw4, (void**)&m_pIDD4);

	g_pTEng.m_lpDD4 = DirectXMng.m_pDD->GetInterface();;
//	g_pTEng.m_lpDDSBB = DirectXMng.m_pDD->GetBackBuffer()->GetInterface();
//	g_pTEng.m_lpDDSPri = DirectXMng.m_pDD->GetFrontBuffer()->GetInterface();
//	g_pTEng.m_lpDDClipper = DirectXMng.m_pDD->m_pClipper->GetInterface();

	//PixelFormat Define
	DirectXMng.m_bpBackSurf->GetRGBMasks(CUser::m_dwRBitMask, CUser::m_dwGBitMask, CUser::m_dwBBitMask);
	if (CUser::m_dwRBitMask == 0x7c00) // 555
	{
		CUser::m_dwRBBitMask = 0x00007c1f;
		CUser::m_dwRBGBitMask = 0x7c1f03e0;
		CUser::m_dwGRBBitMask = 0x03e07c1f;
		CharManager.SetPixelFormat(PF_555);

		// ���� 9.17
		g_pTEng.m_nPF = PF_555;
		g_pTEng.m_dwRBMask = 0x00007c1f;
		g_pTEng.m_dwRMask = 0x00007c00;
		g_pTEng.m_dwGMask = 0x000003e0;
		g_pTEng.m_dwBMask = 0x0000001f;
		CUser::m_CheckKey = 0x8000;
		CUser::m_LineKey  = 0x07e0;
		Dialog_Inv.m_TransParentColor = 0x0c630c63;

	}
	else if (CUser::m_dwRBitMask == 0xf800) //565
	{
		CUser::m_dwRBBitMask = 0x0000f81f;
		CUser::m_dwRBGBitMask = 0xf81f07e0;
		CUser::m_dwGRBBitMask = 0x07e0f81f;
		CharManager.SetPixelFormat(PF_565);

		// ���� 9.17
		g_pTEng.m_nPF = PF_565;
		g_pTEng.m_dwRBMask = 0x0000f81f;
		g_pTEng.m_dwRMask = 0x0000f800;
		g_pTEng.m_dwGMask = 0x000007e0;
		g_pTEng.m_dwBMask = 0x0000001f;
		CUser::m_CheckKey = 0x20;
		CUser::m_LineKey  = 0x07e0;
		Dialog_Inv.m_TransParentColor = 0x39e739e7;
	}

	DirectXMng.m_pDxCursor = new CDxCursor();
	DirectXMng.m_pDxCursor->InitCursor();
//	m_pDxCursor->AddCursor("NRes\\cursor.bmp");	//Ŀ�� ������ ��ϰ���
	DirectXMng.m_pDxCursor->SetCursorIndex(0);

//	CRain::LoadRainDrops( "MagicRes\\rain.spl" );
//	int nRainNum = CRain::GetRainNum();
//	for( int i = 0; i < MAX_RAIN; i++ )
//	{
//		m_Rain[i].SetFrame();
//	}

	g_BaseDraw.InitSurface();
	///////////////////////////////////////////////////
	MapManager.InitManager(DirectXMng.m_pDD, __GetMainWnd()->GetSafeHwnd()); //�� ������ �ʱ�ȭ

	CStdioFile file;
	CFile bin_file;
	CString str_data;
	int number;
	DWORD file_size;
	CString sound_name;
	char t_name[255], *t_buf;

	if(bin_file.Open("MapPos.dat", CFile::modeRead))
	{
		file_size = bin_file.GetLength();
		bin_file.Read(&number, 4);
		if((DWORD)number*16+4 == file_size)
		{
			g_MapPosCount = number;
			g_MapPos = new RECT[g_MapPosCount];
			g_MapLoading = new BOOL[g_MapPosCount];
			g_MapRsc = new CArray<int, int>[g_MapPosCount];
			ZeroMemory(g_MapLoading, g_MapPosCount*4);
			bin_file.Read(g_MapPos, number*16);
		}
		bin_file.Close();
	}
	if(file.Open("sound.dat", CFile::modeRead))
	{
		while(file.ReadString(str_data))
		{
			if(str_data.IsEmpty()) break;
			number = -1;
			sscanf((LPCTSTR)str_data, "%d\t%s", &number, t_name);

			if(number > 0)
			{
				t_buf = new char[lstrlen(t_name)+1];
				lstrcpy(t_buf, t_name);
				g_SoundName[number] = t_buf;
			}
		}
		file.Close();
	}
	if(file.Open("music.dat", CFile::modeRead))
	{
		while(file.ReadString(str_data))
		{
			if(str_data.IsEmpty()) break;
			number = -1;
			sscanf((LPCTSTR)str_data, "%d\t%s", &number, t_name);

			if(number > 0)
			{
				t_buf = new char[lstrlen(t_name)+1];
				lstrcpy(t_buf, t_name);
				g_MusicName[number] = t_buf;
			}
		}
		file.Close();
	}

	int value;
	CWinApp *app = AfxGetApp();
	if(DirectXMng.m_pDirectSound)
	{
		value = app->GetProfileInt("Setting", "Sound Volume", 0);
		if(value == 3000) DirectXMng.m_pDirectSound->SetSoundVolume(DSBVOLUME_MIN);
		else DirectXMng.m_pDirectSound->SetSoundVolume((long)value);
		value = app->GetProfileInt("Setting", "Music Volume", 0);
		if(value == 3000) DirectXMng.m_pDirectSound->SetMusicVolume(DSBVOLUME_MIN);
		else DirectXMng.m_pDirectSound->SetMusicVolume((long)value);
	}
	if(DirectXMng.m_bFullScreen )
	{
		value = app->GetProfileInt("Setting", "Gamma Control", -25);
		DirectXMng.SetGammaRate( value );
	}
	value = app->GetProfileInt("Setting", "MainMode", 0);
	g_vMainMode = value;
	SetMainMode(g_vMainMode);
//=============
// �켮
//=============
//	GDialog_AccountLogin.InitData(DirectXMng.m_pDD);
//	GDialog_AccountLogin.Create(DirectXMng.m_pDD, "s_account.lib", 0);

	CreateEditor();	//ä���Է� ���� Editor����
//=============

	//(���) �ʱ�ȭ...
//	FogEffect.InitData(DirectXMng.m_pDD);// �ʱ�ȭ...���ο� ���ǽ��� ����鼭..�۾��ϱ�����..�ϴ� ���� ���Ѵ��..

	//�켮.
	//Dialog_Login.InitData(DirectXMng.m_pDD, this);


	CPoint t_pos;

	Dialog_Main.SetOffset(CPoint(0, 495));
	Dialog_Main.Create(DirectXMng.m_pDD, "Default.lib", 0, FALSE, FALSE, FALSE);
	Dialog_SmallMain.SetOffset(CPoint(717, 449));
	Dialog_SmallMain.Create(DirectXMng.m_pDD, "sDefault.lib", 0, FALSE, FALSE, TRUE);
	Dialog_BoardCtrl.InitData(DirectXMng.m_pDD, this);
	Dialog_MemoCtrl.InitData(DirectXMng.m_pDD, this);
	Dialog_MagicCtrl.InitData(DirectXMng.m_pDD, this);

	Item_Init(); 

//�켮.
//	Dialog_Login.SetCharacter(&Item_Inv, &Item_Inv2, &Item_Inv3); // �α��� ���̾�α׿� ĳ���� ������ ����
	ReadItemIndex();

//	ArmatureManager.LoadAllArmatureRes();
//	CharManager.LoadAllCharRes();
//	Login_Window();// �ȿ��� ������ ����.

	//���� ���� �÷���....
	g_mainSoundIndex = -1;
	g_vCurMusicNumber = 1;
	if(CChildView::DirectXMng.m_pDirectSound)
	{
		char *value;
		if(g_MusicName.Lookup(g_vCurMusicNumber, value))
		{
			g_mainSoundIndex = CChildView::DirectXMng.m_pDirectSound->MusicPlay(value, g_vCurMusicNumber, TRUE);
		}
	}

	if(m_RestartGame)
	{
		GameLogin();
	}
	else
	{
		if(InitLogin())
		{
			GameLogin();
		}
	}

	//���� ���� ����..
	if(CChildView::DirectXMng.m_pDirectSound && g_mainSoundIndex != -1)
	{
		CChildView::DirectXMng.m_pDirectSound->MusicStop(g_vCurMusicNumber, g_mainSoundIndex, TRUE);
		g_mainSoundIndex = -1;
	}

	UserManager.MagicTableInit(); 

	return bInitOk;
}

BOOL CChildView::DDRelease()
{
	SAFE_DELETE(m_pBBDX_Editor);
	SAFE_DELETE(m_pChatOuter);
	SAFE_DELETE(m_pBBDX_Editor_id);
	SAFE_DELETE(m_pBBDX_Editor_password);

	m_LightSource.Release(); 

	MapManager.EndManager();
	//���� ��ų��. (UserManager���� MagicManager�� CharManager�� �����)
	UserManager.RemoveAllData();
	MagicManager.RemoveAllData();
	ArmatureManager.RemoveAllData();
	CharManager.RemoveAllData();

	return DirectXMng.ReleaseDirectX();
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd ::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	DirectXMng.SetRelatedHwnd(GetSafeHwnd());
	SocketMng.m_bhRelatedWnd = GetSafeHwnd();

	pAppFont = new CFont;
	pAppFont->CreateFont(-12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH, "����");

	return 0;
}

void CChildView::OnDestroy() 
{
	if(!GDialog_AccountLogin) 
		SocketMng.SendLogout(0);	//����� Server�� Logout������
	KillTimer(0);
	DDRelease();

	delete pAppFont;
	pAppFont = NULL;

	AfxGetApp()->WriteProfileInt("Setting", "MainMode", g_vMainMode);

	CWnd::OnDestroy();
	
	// TODO: Add your message handler code here
	
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;	
}

void LogFrameRate(DirectXMng &dxMng, CPoint ptPos)
{
	static DWORD dwStartTick = GetTickCount();
	static int count = 0;
	DWORD dwTick = GetTickCount();
	static int curCount = count;
	if (dwTick-dwStartTick>1000)
	{
		dwStartTick = dwTick;
		curCount = count;
		count = 0;
	}

	CString str;
	str.Format("FPS: %d, X: %d, Y: %d Area: %d", curCount, ptPos.x, ptPos.y, CChildView::MapManager.GetAreaNumber(ptPos));
//	str.Format("X: %d, Y: %d", ptPos.x, ptPos.y);
//	CRect r(0, 0, 640, 40);
	CRect r(0, 0, 800, 40);
	CDC *pDC = dxMng.m_pDrawSurface->GetDC();
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));
	pDC->DrawText(str, &r, DT_SINGLELINE|DT_VCENTER|DT_CENTER);
	dxMng.m_pDrawSurface->ReleaseDC(pDC);

	count++;
}

void CChildView::DrawRainDrops()
{
	static CPoint PreMapPos = m_ptMapOffset;
	CPoint dPos =  m_ptMapOffset - PreMapPos;
	CPoint ptRainPos;
	int place;
	int nRainNum = CRain::GetRainNum();
	if( !CRain::GetLightning() )
	{
		int MyIn = MapManager.IsHouse(UserManager.GetMyCellPos());
		if(MyIn == -1)
		{
			DirectXMng.m_pDrawSurface->Lock();
			DDSURFACEDESC2& ddsd = DirectXMng.m_pDrawSurface->GetDescription();
			for( int i = 0; i < nRainNum; i++ )
			{
				m_Rain[i].m_nRainDropsX -= dPos.x;
				m_Rain[i].m_nRainDropsY -= dPos.y;

				ptRainPos.x = m_Rain[i].m_nRainDropsX;
				ptRainPos.y = m_Rain[i].m_nRainDropsY;
				ptRainPos +=  m_ptMapOffset;
				
				ptRainPos = MapManager.PixelToCell(ptRainPos);
				place = CChildView::MapManager.GetAreaNumber(ptRainPos);
				if( place ==  17 )
					m_Rain[i].RainDrops( FALSE, ddsd, dPos );
				else
					m_Rain[i].RainDrops( TRUE, ddsd, dPos );
			}
			DirectXMng.m_pDrawSurface->Unlock();
		}
	}
	PreMapPos = m_ptMapOffset;

}
#include "DManage/DirectSound.h"
void CChildView::DrawRains()
{

	static DWORD dwRainDropsTime = GetTickCount();
	DWORD dwNowTime = GetTickCount();

	
//	if( DirectXMng.m_bHalEnabled )
//	{//Hal�϶� �㿡�� ������ �������� ����
		int nNightState = Weather.GetNightState(); 
		if( nNightState != 4 )
		{
			if( nNightState == 1 && !Weather.GetRainState() &&  Weather.GetRainChange() ) 
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, TRUE );
			else if ( nNightState == 1 && Weather.GetRainState() &&  !Weather.GetRainChange() ) 
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, TRUE );
			else if ( nNightState == 1 && Weather.GetRainState() &&  Weather.GetRainChange() ) 
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, FALSE );
			else
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, FALSE );
		}
		else
		{
			if( nNightState == 3 && !Weather.GetRainState() &&  Weather.GetRainChange() ) 
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, FALSE );
			else if ( nNightState == 3 && Weather.GetRainState() && Weather.GetRainChange() ) 
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, TRUE );
			else if ( nNightState == 3 && !Weather.GetRainState() &&  !Weather.GetRainChange() ) 
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, FALSE );
			else
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, TRUE );
		}

/*
		if( nNightState > 5 || nNightState < 3 )
		{
			if( nNightState == 6 && !Weather.GetRainState() &&  Weather.GetRainChange() ) 
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, TRUE );
			else if ( nNightState == 6 && Weather.GetRainState() &&  !Weather.GetRainChange() ) 
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, TRUE );
			else if ( nNightState == 6 && Weather.GetRainState() &&  Weather.GetRainChange() ) 
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, FALSE );
			else
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, FALSE );
		}
		else
		{
			if( nNightState == 3 && !Weather.GetRainState() &&  Weather.GetRainChange() ) 
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, FALSE );
			else if ( nNightState == 3 && Weather.GetRainState() && Weather.GetRainChange() ) 
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, TRUE );
			else if ( nNightState == 3 && !Weather.GetRainState() &&  !Weather.GetRainChange() ) 
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, FALSE );
			else
				CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, TRUE );
		}
*/
//	}
//	else CRain::SetGammaRamp( DirectXMng.m_pGammaCtrl, &DirectXMng.m_orgGamma, TRUE );
	//Hal�� ������� ���� ���¿����� �㿡�� ������ ���� �ֵ��� �Ѵ�.

	if( dwNowTime - dwRainDropsTime > 50)
	{
		dwRainDropsTime = dwNowTime;
		CRain::SetState(); 

		for( int k = 0; k < MAX_RAIN; k++ )
		{
			if( m_Rain[k].RainMove( ) )
				m_Rain[k].SetPosition();
		}
	}

	if( CRain::GetLightning() )
	{
		static BOOL bThunderPlayed = FALSE;//õ�ռҸ��� ���������� �ʱ� ���ؼ� �ӽ÷� �����.
//		if( CRain::Lightning(lpDDS_BackBuffer,RGB(255,255,255)) )
		if( CRain::LightningEx( DirectXMng.m_pGammaCtrl, &DirectXMng.m_GammaLightning, &DirectXMng.m_orgGamma ) )
		{
			bThunderPlayed = FALSE;
			CRain::SetLightning( FALSE ); 
		}
		else
		{
			if( !bThunderPlayed )
			{
				int nThundNum = rand()%SOUND_THUNDER_C;
				char *value;

				if(g_SoundName.Lookup(SOUND_THUNDER+nThundNum, value))
				{
					TRACE("õ��\n");
					DirectXMng.m_pDirectSound->SoundPlay(value, SOUND_THUNDER+nThundNum, FALSE);
				}
				bThunderPlayed = TRUE;
			}
		}
	}
	else
	{
		int nRainNum = CRain::GetRainNum();
		static int nSoundIndex = -1;
		if( nRainNum > 20 )
		{
			if( !DirectXMng.m_pDirectSound->IsSoundPlaying(SOUND_RAIN, nSoundIndex) )
			{
				char *value;

				if(g_SoundName.Lookup(SOUND_RAIN, value))
				{
					nSoundIndex = DirectXMng.m_pDirectSound->SoundPlay(value, SOUND_RAIN, TRUE);
				}
			}
		}
		else
		{
			if(DirectXMng.m_pDirectSound->IsSoundPlaying(SOUND_RAIN, nSoundIndex))
			{
				DirectXMng.m_pDirectSound->SoundStop(SOUND_RAIN, nSoundIndex);
			}

		}

		int MyIn = MapManager.IsHouse(UserManager.GetMyCellPos());
		if(MyIn == -1)
		{
//			DirectXMng.SetInHouseGammaRate();
			DirectXMng.m_pDrawSurface->Lock();
			DDSURFACEDESC2& ddsd = DirectXMng.m_pDrawSurface->GetDescription();
			for( int i = 0; i < nRainNum; i++ )
			{
				m_Rain[i].RainDraw( ddsd ); 
			}
			DirectXMng.m_pDrawSurface->Unlock();
		}
	}

}

void CChildView::DrawNight()
{
	
	if( DirectXMng.m_bHalEnabled && DirectXMng.m_Night )
	{
		int nNightState = Weather.GetNightState(); 
		if( nNightState == 4 ) return;

		CRect  rc;
		CPoint ptLightPos;
		CPoint ptMapOffset;
		CRect  rcScreen(-200,-200,1000,600);
		_LIGHT_SOURCE_DATA* pLSData = NULL;

		DirectXMng.m_Night->SetNightState( nNightState );  
		ptMapOffset = CChildView::MapManager.GetMapStartPos();

		CUser *pMe = UserManager.GetMe();
		if( pMe )
		{
//			DirectXMng.m_Night->SetLight( pMe->m_bpDirectXMng->m_pMouseInfo->m_posMouse, 1000000 );
			DirectXMng.m_Night->SetLight( pMe->GetPosition() - ptMapOffset, 1000000 );
		}

		for( int i =0 ; i < m_LightSource.m_Header.nQt ; i++ )
		{
			pLSData = m_LightSource.DataGet(i); 
			if( pLSData == NULL )     continue;
			rc = pLSData->rc;
			ptLightPos =  rc.CenterPoint();
			ptLightPos -= ptMapOffset;
			if( rcScreen.PtInRect( ptLightPos ) )
			{
				DirectXMng.m_Night->SetLight( ptLightPos, rc.Width()*5000);
//				DirectXMng.m_Night->SetLight( ptLightPos, /*rc.Width()*rc.Height()*25*/rc.Width()*10000, pLSData->crColor );
			}
		}
		DirectXMng.m_Night->DrawNight();
	}
	else
	{
		TRACE0("���ӱ���� �������� �㳷 ó����\n");
	}

/*
	int nNightState = Weather.GetNightState(); 
	if( nNightState == 4 ) return;
	if( DirectXMng.m_bHalEnabled )
	{
		if(g_pShowDialog && g_pShowDialog->GetPosMode() == POS_LEFT)
		{
			DirectXMng.m_p3D->D3DRenderDay( 1, nNightState );
		}
		else
		{
			DirectXMng.m_p3D->D3DRenderDay( 0, nNightState );
		}
	}
	else
	{
		TRACE0("���ӱ���� �������� �㳷 ó����\n");
	}
*/
}

//��� ó���� ����
#define LOADING_GAP		300

void CChildView::BackLoading(CPoint pos)
{
	int Cell_X = (pos.x >> 5);
	int Cell_Y = (pos.y >> 5);
	int i, j, k, l;
	short int nData, nSet = 0, nSubSet = 0;
	const _SPR_LSP* pSpr = NULL;
	CRect t_rect;
	
	for(l = 0; l < g_MapPosCount; l++)
	{
		if(Cell_X >= g_MapPos[l].left-25 &&
			Cell_Y >= g_MapPos[l].top-19 &&
			Cell_X < g_MapPos[l].right &&
			Cell_Y < g_MapPos[l].bottom)
		{
			if(Cell_X >= g_MapPos[l].left && Cell_Y >= g_MapPos[l].top)
			{
				g_vLoadingRect.left = g_MapPos[l].left;
				g_vLoadingRect.top = g_MapPos[l].top;
				g_vLoadingRect.right = g_MapPos[l].right;
				g_vLoadingRect.bottom = g_MapPos[l].bottom;
			}

			if(g_MapLoading[l] == TRUE) continue;
			g_MapLoading[l] = TRUE;
			for(i = g_MapPos[l].top; i < g_MapPos[l].bottom; i++)
			{
				for(j = g_MapPos[l].left; j < g_MapPos[l].right; j++)
				{
					// Ÿ�� �б�
					for(k = 0; k < 3; k++)
					{
						const _TILE_MAP_DATA_TOOL* pTMData = TileMapTool.ToolDataGet(k, j, i);
						if(pTMData == NULL) continue;
						_TILE_SET_TOOL *tile_set_tool;

						tile_set_tool = TileSetTool.GetTileSet(pTMData->snTS);
						if(tile_set_tool == NULL) continue;
						if(tile_set_tool->m_lpDDSs == NULL)
						{
							CString szHFN = "house";
							CString szBMPFN = tile_set_tool->m_HTSs.szBMPFN;
							if(szBMPFN.GetLength() > 0)
							{
								szBMPFN = szBMPFN.Left(szBMPFN.GetLength() - 3);
								g_pTEng.PathSetCur("BMP");

								if( szBMPFN.Left(5) == szHFN )
								tile_set_tool->m_lpDDSs = g_pTEng.SurfaceCreateWithBMP(szBMPFN + "obm", FALSE, tile_set_tool->m_HTSs.crCK,TRUE);
								else
								tile_set_tool->m_lpDDSs = g_pTEng.SurfaceCreateWithBMP(szBMPFN + "obm", FALSE, tile_set_tool->m_HTSs.crCK);
								
								if(tile_set_tool->m_lpDDSs == NULL)
								{
									tile_set_tool->m_lpDDSs = g_pTEng.SurfaceCreateWithBMP(szBMPFN + "bmp", FALSE, tile_set_tool->m_HTSs.crCK);
									if(tile_set_tool->m_lpDDSs)
										TRACE("%s ����\n", szBMPFN + "bmp");
								}
								else
								{
									if(tile_set_tool->m_lpDDSs)
										TRACE("BackLoading:%s ����(%ld)\n", szBMPFN + "obm", g_vRenderTime);
								}
							}
						}
					}
					// Object �б�
					nData = MapObj.DataGet(j, i);
					nSet = nData >> 8;
					if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) continue;
					nSubSet = nData & 0x00ff;
					// Object �б�
					int nSpr = MapAniObjs[nSet].FrmGetAnimated(nSubSet);
					MapAniObjs[nSet].SprGet(nSpr, &pSpr);
					if(pSpr == NULL)
					{
						CString szFN = "map\\object\\";
						szFN += CChildView::MapObj.m_Header.szRegObjAniFNs[nSet];
						MapAniObjs[nSet].AniLoad(szFN);
						MapAniObjs[nSet].AniCtrlAlloc(256);
						szFN = "map\\object\\";
						szFN += CChildView::MapObj.m_Header.szRegObjSprFNs[nSet];
						MapAniObjs[nSet].SprLoad(szFN, g_pTEng.m_nPF);
						nSpr = MapAniObjs[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
						MapAniObjs[nSet].SprGet(nSpr, &pSpr);
						if(pSpr == NULL) continue;
					}
					// �׸��� �б�
					nData = MapShadowObj.DataGet(j, i);
					nSet = nData >> 8;
					if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) continue;
					nSubSet = nData & 0x00ff;
					// �׸��� �б�
					nSpr = MapShadowAniObjs[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
					MapShadowAniObjs[nSet].SprGet(nSpr, &pSpr);
					if(pSpr == NULL)
					{
						if(CChildView::MapShadowObj.m_Header.szRegObjSprFNs[nSet][0] == 0) continue;

						CString szFN = "map\\object\\";
						szFN += CChildView::MapShadowObj.m_Header.szRegObjAniFNs[nSet];
						MapShadowAniObjs[nSet].AniLoad(szFN);
						MapShadowAniObjs[nSet].AniCtrlAlloc(256);
						szFN = "map\\object\\";
						szFN += CChildView::MapShadowObj.m_Header.szRegObjSprFNs[nSet];

						if( DirectXMng.m_bHalEnabled )
						{
							DirectXMng.m_p3D->D3DCreateTextureEx( szFN.GetBuffer(0) );
							MapShadowAniObjs[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
						}
						else
							MapShadowAniObjs[nSet].SprLoad(szFN, 0);
						nSpr = MapShadowAniObjs[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
						MapShadowAniObjs[nSet].SprGet(nSpr, &pSpr);
						if(pSpr == NULL) continue;
					}
				}
			}
		}
	}
}
/*
static int t_count = 0;

void T_Draw()
{
	CString t_str;

	t_count++;
	if(t_count > 100)
	{
		t_count = 0;
		t_time2[10] = 0;
		for(int i = 1; i < 10; i++)
		{
			t_time2[i] = t_time1[i];
			t_time2[10] += t_time2[i];
			t_time1[i] = 0;
		}
	}

	t_str.Format("[%.6d] %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d %.4d", t_time2[10], t_time2[1], t_time2[2],
		t_time2[3], t_time2[4], t_time2[5], t_time2[6], t_time2[7], t_time2[8], t_time2[9]);

	CRect r(0, 80, 800, 100);
	CDC *pDC = CChildView::DirectXMng.m_pDrawSurface->GetDC();
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));
	pDC->DrawText(t_str, &r, DT_SINGLELINE|DT_VCENTER);
	CChildView::DirectXMng.m_pDrawSurface->ReleaseDC(pDC);
}*/

void CChildView::DrawNight1(BOOL bRight)
{
	int nNightState = Weather.GetNightState(); 
	if( nNightState == 4 && g_vMapNumber == 1)
	{
		CChildView::m_ptLightPos.RemoveAll();
		return;
	}
	DWORD dwNowTime = GetTickCount();
/*	
	static int nNightState = 1;
	static DWORD dwTime = GetTickCount();
	//if( dwNowTime > dwTime + 3300 )
	if( dwNowTime > dwTime + 9900 )
	{
		nNightState++;
		TRACE("NIGHTSTATE %d\n",nNightState);
		//if( nNightState > 8 ) nNightState = 1;
		if( nNightState > 4 ) nNightState = 1;
		dwTime = dwNowTime;
		//nNightState = 8;
	}
	if( nNightState == 4 ) return;
*/
	CArray<CPoint,CPoint> m_ptLight;
	CRect  rc;
	CPoint ptLightPos;
	CPoint ptMapOffset;
	CRect  rcScreen(-300,-300,1100,700);
	_LIGHT_SOURCE_DATA* pLSData = NULL;

	ptMapOffset = CChildView::MapManager.GetMapStartPos();

	int place = 0;
	CUser *pMe = UserManager.GetMe();
	if( pMe )
	{
		LIGHT_INFO LI;
		if( dwNowTime <= pMe->m_dwTorchlight )
			LI.m_kind = 0;
		else 
			LI.m_kind = 1;
		LI.m_pt = pMe->GetPosition() - ptMapOffset;
		CChildView::m_ptLightPos.Add( LI );

		CPoint ptPos = MapManager.PixelToCell(pMe->GetPosition());
		place = CChildView::MapManager.GetAreaNumber(ptPos);
	}

	if(g_vMapNumber != 1)
	{
		nNightState = 2;
		place = 1;
	}
	DirectXMng.m_Night->SetNightStateEx( nNightState, place );  

	for( int i =0 ; i < m_LightSource.m_Header.nQt ; i++ )
	{
		pLSData = m_LightSource.DataGet(i); 
		if( pLSData == NULL )     continue;
		rc = pLSData->rc;
		ptLightPos =  rc.CenterPoint();
		ptLightPos -= ptMapOffset;
		if( rcScreen.PtInRect( ptLightPos ) )
		{
			LIGHT_INFO LI;
			LI.m_kind = 2;
			LI.m_pt = ptLightPos;
			CChildView::m_ptLightPos.Add( LI );
		}
	}

	DirectXMng.m_Night->DrawNight( DirectXMng.m_pDrawSurface, &CChildView::m_ptLightPos,g_vDispPixSize.cy, bRight );
	CChildView::m_ptLightPos.RemoveAll();

}

BOOL CChildView::IdleProcess(LONG turn)
{
	if (m_iMyId!=-1 && UserManager.m_ReadyOK == 1) 
	{
		CUser *ptmp = UserManager.GetMe();	
		if(ptmp == NULL) return TRUE;

		g_vRenderTime = GetTickCount();

		bDlgIn = MouseProcess();	//���콺 �Է�ó��

		UserManager.Move();	//ĳ���͸� �̵���Ŵ (�̵������� User�����Ͱ� ��������)
		
		if(DirectXMng.m_pDirectSound)
		{
			if(g_vMapNumber != g_vOldMapNumber || g_vOldMapNumber == -1)
			{
				int t_num;
				if(g_vMapNumber == 1)
				{
					int area_num = MapManager.GetAreaNumber(UserManager.GetMyCellPos());
					if(area_num == 1)
					{
						t_num = 2;
					}
					else
					{
						t_num = 100;
					}
					g_vStartMapTime = g_vRenderTime;
				}
				else t_num = g_vMapNumber+1;
				char *value;
				if(g_MusicName.Lookup(t_num, value))
				{
					if(g_mainSoundIndex != -1) DirectXMng.m_pDirectSound->MusicStop(g_vCurMusicNumber, g_mainSoundIndex, TRUE);
					g_mainSoundIndex = DirectXMng.m_pDirectSound->MusicPlay(value, t_num, TRUE);
					g_vCurMusicNumber = t_num;
				}
				g_vOldMapNumber = g_vMapNumber;
			}
			else if(g_vMapNumber == 1 && g_vRenderTime-g_vStartMapTime > 5000)
			{
				int t_num;

				int area_num = MapManager.GetAreaNumber(UserManager.GetMyCellPos());
				if(area_num == 1)
				{
					t_num = 2;
				}
				else
				{
					t_num = 100;
				}
				if(t_num != g_vCurMusicNumber)
				{
					char *value;
					if(g_MusicName.Lookup(t_num, value))
					{
						if(g_mainSoundIndex != -1)
						{
							if(DirectXMng.m_pDirectSound->IsMusicPlaying(t_num, g_mainSoundIndex) == FALSE)
							{
								DirectXMng.m_pDirectSound->MusicStop(g_vCurMusicNumber, g_mainSoundIndex, FALSE);
								g_mainSoundIndex = DirectXMng.m_pDirectSound->MusicPlay(value, t_num, TRUE);
							}
						}
						else
						{
							g_mainSoundIndex = DirectXMng.m_pDirectSound->MusicPlay(value, t_num, TRUE);
						}
						g_vCurMusicNumber = t_num;
					}
					g_vStartMapTime = g_vRenderTime;
				}
			}
		}
		int MyIn = MapManager.IsHouse(UserManager.GetMyCellPos());
		m_house.SetHouseIndex( MyIn ); 

		if(g_pShowDialog)
		{
			if(g_pShowDialog->GetPosMode() == POS_LEFT)
			{
				MapManager.ShowMapType(2);// �����ʺ��� �����ؾ��Ѵ�..����..
				if(g_pShowDialog != &Dialog_Chat)
				{
					m_pChatOuter->ShowMode(1);
				}
				if(Dialog_DeadMain.IsVisible() == FALSE)
				{
					SetMainMode(0);
				}
			}
			else if(g_pShowDialog->GetPosMode() == POS_NORMAL)
			{
				MapManager.ShowMapType(0);// ������� �����ؾ��Ѵ�..����..
				m_pChatOuter->ShowMode(0);
				if(Dialog_DeadMain.IsVisible() == FALSE)
				{
					SetMainMode(g_vMainMode);
				}
			}
		}
		else
		{
			MapManager.ShowMapType(0);// �⺻
			m_pChatOuter->ShowMode(0);
			if(Dialog_DeadMain.IsVisible() == FALSE)
			{
				SetMainMode(g_vMainMode);
			}
		}

		m_ptMapOffset = MapManager.SetCenterPos(UserManager.GetMyPos()); //���� ȭ���߽ɿ� ��ġ��Ű���� ���� �׸�

		POINT p;
		p.x = (m_ptMapOffset.x >> 5);
		p.y = (m_ptMapOffset.y >> 5);
//		if(!g_vLoadingRect.PtInRect(p))	BackLoading(m_ptMapOffset);
//		if(!g_vLoadingRect.PtInRect(p))	BackLoadingEx(m_ptMapOffset);

//8.27		
//		CPoint Viewpos = MapManager.DrawTile(DirectXMng.m_pDrawSurface);		//Ÿ�� �׸���

		// ȭ��� ��ȿ�� ������...

//		DrawTile();
		m_limit_old_y = p.y-9;// ������Ʈ�� ��Ʈ�ؼ� �Ѹ��� ���ؼ�...���� �־���.
		if(g_BaseDraw.IsChangePos(p) == TRUE)
			g_BaseDraw.DrawChangeTile(p);
		g_BaseDraw.DrawSurface(DirectXMng.m_pDrawSurface, m_ptMapOffset);

//		DrawRainDrops();//������� �׷��ش�.
		
		if(MyIn != -1)
		{
			int trans_degree = m_house.TransDegree();
			//UserManager.OutHouseDrawObj(DirectXMng.m_pDrawSurface, m_ptMapOffset);
			DrawNight1(g_pShowDialog && g_pShowDialog->GetPosMode() == POS_LEFT);
//			DrawTile(2);// �� ���θ� �����ش�.
			UserManager.InHouseRenderUsers(DirectXMng.m_pDrawSurface, m_ptMapOffset);
		}
/*		
		int size = UserManager.m_arrDrawUsersize;
		CPoint CelPos;
		MapManager.m_UserSize = 0;
		int me=0;// ���� ���ֱ� ���ؼ� �÷��׷� ����..
		for(int i = 0; i< size;i++)
		{
			CUser *pMe = UserManager.GetMe();// ���� ���� ��Ű�� ���ؼ�..
			if(pMe != UserManager.m_arrDrawUser[i])
			{
				CelPos = UserManager.m_arrDrawUser[i]->GetCellPosition();
				MapManager.SetUserPos(CelPos, i-me);
			}
			else
				me=1;
		}*/

		DrawHousePlace();

		// ĳ���͹� ����� �ѷ��ش�.
		if(MyIn == -1)
		{
			int trans_degree = m_house.TransDegree();
//			int trans_degree = m_house.GetTransDegree();
			if( trans_degree == 32 )
				DrawObject();
			else
				UserManager.InHouseRenderUsers(DirectXMng.m_pDrawSurface, m_ptMapOffset);
			DrawTile(1);// ĳ���� ���� ��� ���
		}
/*
		if( MyIn == -1 && UserManager.m_bMyCovered && UserManager.m_nCoverDegree !=0 )
		{
			int skip_line = 10*(8-UserManager.m_nCoverDegree);
			CUser* me = UserManager.GetUserWithUid( m_iMyId ); 
			me->DrawLine(DirectXMng.m_pDrawSurface, me->GetPosition()-MapManager.GetMapStartPos(), skip_line);
			UserManager.m_nCoverDegree = 0;
			UserManager.m_bMyCovered = FALSE;
		}
*/


	 	if(g_vMapNumber == 1) DrawRains();//�� �׷��ش�...
//		DrawNight();//���� �׷��ش�...
		if(MyIn == -1)
		{
			DrawNight1(g_pShowDialog && g_pShowDialog->GetPosMode() == POS_LEFT);
		}

		RemoveUnUseLSP();

		CPoint ptScale = ptmp->GetPosition() - MapManager.GetMapStartPos(); 
		DirectXMng.m_pDirectSound->SetScale( ptScale );

		Dialog_SmallMain.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Chat.Draw(DirectXMng.m_pDrawSurface);
		if (m_pChatOuter) 
			m_pChatOuter->DrawChat(DirectXMng.m_pDrawSurface);	//ä��ǥ���� ������ ���̱�

		Dialog_BoardCtrl.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Status.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Inv.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Shop.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Storage.Draw(DirectXMng.m_pDrawSurface);
		Dialog_MakeItem.Draw(DirectXMng.m_pDrawSurface);
		Dialog_GuildMenu1.Draw(DirectXMng.m_pDrawSurface);
		Dialog_GuildMenu2.Draw(DirectXMng.m_pDrawSurface);
		Dialog_GuildMenu3.Draw(DirectXMng.m_pDrawSurface);
		Dialog_GuildName.Draw(DirectXMng.m_pDrawSurface);
		Dialog_GuildApply.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Guild.Draw(DirectXMng.m_pDrawSurface);
		Dialog_GuildJoin.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Repair.Draw(DirectXMng.m_pDrawSurface);
		Dialog_MemoCtrl.Draw(DirectXMng.m_pDrawSurface);
		Dialog_MagicCtrl.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Exchange.Draw(DirectXMng.m_pDrawSurface);
		Dialog_AuctionSell.Draw(DirectXMng.m_pDrawSurface);
		Dialog_AuctionBuy.Draw(DirectXMng.m_pDrawSurface);
		Dialog_AuctionDetail.Draw(DirectXMng.m_pDrawSurface);
		Dialog_TaxRate.Draw(DirectXMng.m_pDrawSurface);
		Dialog_GuildPositionName.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Message.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Message2.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Message3.Draw(DirectXMng.m_pDrawSurface);
		Dialog_HowMuch.Draw(DirectXMng.m_pDrawSurface);
		Dialog_HowMany.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Name.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Quit.Draw(DirectXMng.m_pDrawSurface);

		Dialog_EventMessage.Draw(DirectXMng.m_pDrawSurface); //�̺�Ʈ.
		Dialog_EventMessage1.Draw(DirectXMng.m_pDrawSurface); //�̺�Ʈ.
		Dialog_EventMessage2.Draw(DirectXMng.m_pDrawSurface); //�̺�Ʈ.

		Dialog_DeadMain.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Main.Draw(DirectXMng.m_pDrawSurface);
		Dialog_Option.Draw(DirectXMng.m_pDrawSurface);

		if(g_pCaptureDialog)
			g_pCaptureDialog->DragDraw(DirectXMng.m_pDrawSurface);
/////////////////////////////////////////////////////////////		
		if(g_bDisplayDate) DisplayDate();

		if (m_pBBDX_Editor && m_pBBDX_Editor == CWnd::GetFocus())
		{
			CRect rc(21,g_vDispPixSize.cy-35,g_vDispPixSize.cx-21,g_vDispPixSize.cy-17);
			CPoint editor_pos(30, g_vDispPixSize.cy-35);
			//CUser::BltLSPChat( DirectXMng.m_pDrawSurface );  
			CUser::BltBlackTrans(DirectXMng.m_pDrawSurface, rc);
			//DirectXMng.m_p3D->D3DRenderChat();  
			m_pBBDX_Editor->DCDrawPosCurText(DirectXMng.m_pDrawSurface, editor_pos);	//�����Ϳ� ������ �� �׸���(Editor �� ���� �Ⱥ��̴µ� ����)
		}
		// Ÿ�� ����
/*		POSITION pos = TileSetTool.m_mapData.GetStartPosition();
		int key;
		_TILE_SET_TOOL *value;
		
		while(pos)
		{
			TileSetTool.m_mapData.GetNextAssoc(pos, key, value);
			if(value->m_lpDDSs && g_vRenderTime - value->m_vUseTime > 100000)
			{
				TRACE("%s ����\n", value->m_HTSs.szBMPFN);
				value->m_lpDDSs->Release();
				value->m_lpDDSs = NULL;
			}
		}*/

		if(m_LoadinView) SAFE_DELETE(m_LoadinView); //�켮..

//		T_Draw();
//		LogFrameRate(DirectXMng, MapManager.PixelToCell(DirectXMng.GetMouseInfoPtr()->m_posMouse+m_ptMapOffset));
#ifdef _DEBUG
		LogFrameRate(DirectXMng, MapManager.PixelToCell(DirectXMng.GetMouseInfoPtr()->m_posMouse+m_ptMapOffset));
//		DisplayRRStats(DirectXMng);
#endif
		DirectXMng.Flip(); //ȭ�� ����������� ��ȯ

		ArrangeTileResource();
	}
	else
	{
		MouseProcess();	//���콺 �Է�ó��
		LoginView();// �ι�° ȭ������..ĳ���� ����.. �ε�ȭ���� ���ϸ��̼� �����ָ� ��..
	}

	return TRUE;
}

BOOL CChildView::NFocusIdleProcess(LONG turn)
{
	UserManager.Move();//�ϴ� ��ġ���̶� ����
	return TRUE;
}

BOOL CChildView::SocketInit()
{
	return SocketMng.InitManage();
}

BOOL CChildView::SocketRelease()
{
	return SocketMng.EndManage();
}

void CChildView::PacketProcess()
{
	DP_PtrList &ReceivedDataList = SocketMng.m_listReceiveDataPack;
	POSITION pos = ReceivedDataList.GetHeadPosition();
	DataPack*	dp;
	while (pos)
	{
		dp = ReceivedDataList.GetNext(pos);
		ReceivedDataList.RemoveHead();
		//������ ó��
		PacketParser.PacketProcess(dp->m_pData, dp->m_Size);
		//������ ����
		SAFE_DELETE(dp);
	}
}

//��Ŷ�� ��������
LRESULT CChildView::OnPacketProcess(WPARAM, LPARAM)
{
	if (!SocketMng.m_listReceiveDataPack.GetCount()) return 0L;//ó���� ���� ����(�ո޽����ο��� ó���Ǿ���).

	PacketProcess();
	return 0L;
}

LRESULT CChildView::OnPacketPending(WPARAM bReceive, LPARAM)
{
	if (bReceive)
	{
		SocketMng.TriggerReceive();
	}
	else //Send
	{
		SocketMng.TriggerSend();
	}
	return 0L;
}


//DirectInput ���콺 ó���Լ�
int CChildView::MouseProcess()
{
	if (DirectXMng.MouseInfoUpdate())
	{
		BBDX_MouseInformation* pMouseInfo = DirectXMng.GetMouseInfoPtr();
		ASSERT(pMouseInfo);
        
		CUser *pMe = UserManager.GetMe();
		if (pMe && pMe->IsCharDie() == FALSE)
		{
			int ret_val = 0;
			//if(Item.MouseProcess(pMouseInfo)) 
			//	return;//((���))

			if(Dialog_Main.GetCaptureStatus() == FALSE && !Dialog_Main.PtInUIRes(pMouseInfo->GetPos()))
			{
				Dialog_Main.ResetStatus();
			}
			if(g_pCaptureDialog)
			{
				ret_val |= g_pCaptureDialog->MouseProcess(pMouseInfo);
				if(ret_val > 1) return ret_val;
			}

			if(g_pFocusDialog)
			{
				ret_val |= g_pFocusDialog->MouseProcess(pMouseInfo);
				if(ret_val > 1) return ret_val;
			}
			
			ret_val |= Dialog_MemoCtrl.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_DeadMain.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_TaxRate.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_GuildPositionName.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Message.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Message2.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Message3.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_HowMuch.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_HowMany.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Name.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Option.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Main.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Quit.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_BoardCtrl.BoardMouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Shop.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Storage.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Status.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Inv.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_MakeItem.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_MagicCtrl.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Exchange.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_AuctionSell.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_AuctionBuy.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_AuctionDetail.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Chat.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_GuildMenu1.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_GuildMenu2.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_GuildMenu3.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_GuildName.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_GuildApply.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Guild.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_GuildJoin.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_Repair.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
			ret_val |= Dialog_SmallMain.MouseProcess(pMouseInfo);

			if(ret_val > 0) return ret_val;

			//game...�϶�..
			if (pMouseInfo->IsLButtonDown()) 
			{
				LBtnDown(pMouseInfo->m_posMouse);
			}
			else if (pMouseInfo->IsLButtonPressing()) LBtnPressing(pMouseInfo->m_posMouse);
			else if (pMouseInfo->IsLButtonUp()) LBtnUp(pMouseInfo->m_posMouse);

			if (pMouseInfo->IsRButtonDown()) RBtnDown(pMouseInfo->m_posMouse);
			else if (pMouseInfo->IsRButtonPressing()) RBtnPressing(pMouseInfo->m_posMouse);
			else if (pMouseInfo->IsRButtonUp()) RBtnUp(pMouseInfo->m_posMouse);

/*			if (pMouseInfo->IsMouseMove())
			{				
				MouseMove(pMouseInfo->m_posMouse, pMouseInfo->GetLButtonState());
			}*/
		}
		else
		{
			int ret_val = 0;

			ret_val |= Dialog_DeadMain.MouseProcess(pMouseInfo);
			if(ret_val > 1) return ret_val;
		}
	}

	return 0;
}

void CChildView::AccountMouseProcess(int *id_flag)
{
	if (DirectXMng.MouseInfoUpdate())
	{
		BBDX_MouseInformation* pMouseInfo = DirectXMng.GetMouseInfoPtr();

		GDialog_AccountLogin->MouseProcess( pMouseInfo , id_flag);
	}
}

void CChildView::LoginMouseProcess(CDialog_Login *Dialog_Login)
{
	if (DirectXMng.MouseInfoUpdate())
	{
		BBDX_MouseInformation* pMouseInfo = DirectXMng.GetMouseInfoPtr();

		Dialog_Login->MouseProcess(pMouseInfo);
//		Dialog_Login.LoginMouseProcess(pMouseInfo);
	}
}

void CChildView::LBtnDown(CPoint &pos)
{
	CUser *pMe = UserManager.GetMe();
	if (pMe && pMe->IsCharDie() == FALSE)
	{
		m_PathFindGap = g_vRenderTime;
		if(HousePlaceManager.IsSelectMode())
		{
			CPoint t_pos = pos;

			t_pos += m_ptMapOffset;
			t_pos.x >>= 5;
			t_pos.y >>= 5;
			HousePlaceManager.PtInPlace(t_pos);
		}
		else
		{
			if(pMe->m_BattleMode == 0)
			{
				if(UserManager.SendAttack() == FALSE)
				{
					if(Item_Field.MouseProcess(pos+m_ptMapOffset) == FALSE)
					{
						if(GetKeyState(VK_CONTROL)&0x8000)
						{
							CPoint ptCell = m_ptMapOffset;
							ptCell += pos;
							ptCell = MapManager.PixelToCell(ptCell);

							UserManager.GetMapData(ptCell);
							//PacketParser.MoveRunRequest(pMe, ptCell);

							if(pMe->m_Cur_Fa == 0) m_bCtrlUp = false;
							if(m_bCtrlUp)
								PacketParser.MoveRunRequest(pMe, ptCell);
							else
								PacketParser.MoveRequest(pMe, ptCell);
						}
						else
						{
							CPoint ptCell = m_ptMapOffset;
							ptCell += pos;
							ptCell = MapManager.PixelToCell(ptCell);

							UserManager.GetMapData(ptCell);
							PacketParser.MoveRequest(pMe, ptCell);
						}
					}
				}
			}
			else
			{
				if(UserManager.SendAttack() == FALSE)
				{
					if(Item_Field.MouseProcess(pos+m_ptMapOffset) == FALSE)
					{
						if((GetKeyState(VK_SHIFT)&0x8000) == 0)
						{
							if(GetKeyState(VK_CONTROL)&0x8000)
							{
								BYTE buf[10];
								int offset = 0;
								BYTE battletype = 0x00;
								CPacketParser::SetByte(buf, offset, PKT_BATTLEMODE);
								
								CPacketParser::SetByte(buf, offset, battletype);
								SocketMng.Send(offset, buf);		// ������ Ǭ��.

								CPoint ptCell = m_ptMapOffset;
								ptCell += pos;
								ptCell = MapManager.PixelToCell(ptCell);

								UserManager.GetMapData(ptCell);
								/*
								if(pMe->m_Cur_Fa == 0 && m_bCtrlUp)
									PacketParser.MoveRunRequest(pMe, ptCell);
								else
									PacketParser.MoveRequest(pMe, ptCell);
								*/

								if(pMe->m_Cur_Fa == 0) m_bCtrlUp = false;
								if(m_bCtrlUp)
									PacketParser.MoveRunRequest(pMe, ptCell);
								else
									PacketParser.MoveRequest(pMe, ptCell);

							}
							else
							{
								CPoint ptCell = m_ptMapOffset;
								ptCell += pos;
								ptCell = MapManager.PixelToCell(ptCell);

								UserManager.GetMapData(ptCell);
								PacketParser.MoveRequest(pMe, ptCell);
							}
						}
					}
				}
			}
		}
	}
}

void CChildView::LBtnPressing(CPoint &pos)
{
	if(g_vRenderTime - m_PathFindGap <= 500) return;
	m_PathFindGap = g_vRenderTime;

	CUser *pMe = UserManager.GetMe();
	CPoint ptCell = m_ptMapOffset + pos;
	ptCell = MapManager.PixelToCell(ptCell);

	if (pMe && pMe->IsCharDie() == FALSE)
	{
		if(HousePlaceManager.IsSelectMode())
		{
			CPoint t_pos = pos;

			t_pos += m_ptMapOffset;
			t_pos.x >>= 5;
			t_pos.y >>= 5;
			HousePlaceManager.PtInPlace(t_pos);			
		}
		else
		{
			if(pMe->m_BattleMode == 0)
			{	
				if(GetKeyState(VK_CONTROL)&0x8000)
				{
					UserManager.GetMapData(ptCell);

					if(pMe->m_Cur_Fa == 0) m_bCtrlUp = false;
					if(m_bCtrlUp)
						PacketParser.MoveRunRequest(pMe, ptCell);
					else
						PacketParser.MoveRequest(pMe, ptCell);

					//PacketParser.MoveRunRequest(pMe, ptCell,20);				
				}
				else
				{
					if(pMe->IsCharAttack()) return;

					UserManager.GetMapData(ptCell);
					PacketParser.MoveRequest(pMe, ptCell,20);
				}
			}
			else
			{
				if(GetKeyState(VK_SHIFT)&0x8000)
				{
					UserManager.SendAttack();
				}
				else
				{
					if(pMe->IsCharAttack() == FALSE)
					{
						UserManager.GetMapData(ptCell);
						PacketParser.MoveRequest(pMe, ptCell);
					}
				}
			}
		}
	}

}

void CChildView::LBtnUp(CPoint &pos)
{
}

void CChildView::RBtnDown(CPoint &pos)
{
	CUser *pMe = UserManager.GetMe();

///////////////////////////////////////////////////////
	CPoint ptMyPos;
//	CPoint ptDstPos;
	CPoint ptMapOffset;

//	int nDir;

	ptMyPos = pMe->GetPosition();
	ptMapOffset = CChildView::MapManager.GetMapStartPos();
	ptMyPos.x -= ptMapOffset.x;
	ptMyPos.y -= ptMapOffset.y;// + 100;
	
//	ptDstPos = pMe->m_bpDirectXMng->m_pMouseInfo->m_posMouse;
//	nDir = UserManager.GetClientDirection( ptMyPos, ptDstPos );
//	pMe->SetDirection( nDir );
////////////////////////////////////////////////////////
	if (pMe && pMe->IsCharDie() == FALSE)
	{
		if(HousePlaceManager.IsSelectMode())
		{
			HousePlaceManager.DeleteHousePlace();
			return;
		}
		ChatMode(1);// �븻 ä������ �����.
		if( Dialog_Main.m_vSelMagicIndex <= 3 && Dialog_Main.m_vSelMagicIndex >= 0 )
		{
			if( Dialog_Main.m_pMagicData[ Dialog_Main.m_vSelMagicIndex ] == NULL ) 
			{
				TRACE("������ ������ ����\n");
				return;
			}
			int type     = Dialog_Main.m_pMagicData[ Dialog_Main.m_vSelMagicIndex ]->m_vNumber;
			short method = Dialog_Main.m_pMagicData[ Dialog_Main.m_vSelMagicIndex ]->m_vMethod;
			_MAGIC_TABLE* pTable;
			pTable = UserManager.m_arrMagicTableInfo.GetAt(type-1); 
			if( pTable->m_nStTime )
			{
				UserManager.SendReadyMagic(type);
				return;
			}
			TRACE("���� ���̺� ��ȣ:%d ��Ŷ:%d \n",type,method); 
			UserManager.SendMagicAttack( type, method );
			return;
		}

	}
}

void CChildView::RBtnPressing(CPoint &pos)
{
}

void CChildView::RBtnUp(CPoint &pos)
{		
/*	CPoint ptSPos;
	CPoint ptEPos;
	CUser *pMe = UserManager.GetMe();
	if (pMe) 
	{
//		UserManager.SetMagic(m_iMyId, 4, MAGIC_TYPE_DOWN);
		//pMe->SetMotion(CUser::UM_Magic);
		pMe->SetMotion(CUser::UM_Attack);
		ptSPos = pMe->GetPosition();
		///////////////////////////////////////
		CPoint tmp = MapManager.GetMapStartPos();
		CPoint UserPos;
		CPoint tmp_Pos;// ������ ���� ����..

		UserPos = ptSPos - tmp;

		tmp_Pos = pos - UserPos;

		ptEPos.x = ptSPos.x + tmp_Pos.x;
		ptEPos.y = ptSPos.y + tmp_Pos.y;
		int nDir = UserManager.SetAimedMagic(ptSPos, ptEPos, 6, MAGIC_TYPE_UP);
		pMe->SetDirection(nDir);
	}
*/		
}

void CChildView::MouseMove(CPoint &pos, BOOL lClick)
{
	if(lClick)
	{
		BBDX_MouseInformation* pMouseInfo = DirectXMng.GetMouseInfoPtr();
		CUser *pMe = UserManager.GetMe();

		CPoint ptPreCell = m_ptMapOffset + pMouseInfo->m_p_posMouse;
		ptPreCell = MapManager.PixelToCell(ptPreCell);
		CPoint ptCell = m_ptMapOffset + pos;
		ptCell = MapManager.PixelToCell(ptCell);

		if(ptPreCell == ptCell) return;

		if (pMe && pMe->IsCharDie() == FALSE)
		{
			if(HousePlaceManager.IsSelectMode())
			{
				CPoint t_pos = pos;

				t_pos += m_ptMapOffset;
				t_pos.x >>= 5;
				t_pos.y >>= 5;
				HousePlaceManager.PtInPlace(t_pos);			
			}
			else
			{
				if(pMe->m_BattleMode == 0)
				{	
					if(GetKeyState(VK_CONTROL)&0x8000)
					{
						UserManager.GetMapData(ptCell);
						PacketParser.MoveRunRequest(pMe, ptCell,20);				
					}
					else
					{
						if(pMe->IsCharAttack()) return;

						UserManager.GetMapData(ptCell);
						PacketParser.MoveRequest(pMe, ptCell,20);
					}
				}
				else
				{
					if(GetKeyState(VK_SHIFT)&0x8000)
					{
						UserManager.SendAttack();
					}
					else
					{
						if(pMe->IsCharAttack() == FALSE)
						{
							UserManager.GetMapData(ptCell);
							PacketParser.MoveRequest(pMe, ptCell);
						}
					}
				}
			}
		}
	}

}
//�Ʒ��� Mouse Event�����Լ��� DirectInput�� ���Ұ��Ҷ�
void CChildView::OnLButtonDown(UINT nFlags, CPoint point) 
{
//	CUser *ptmp = UserManager.GetMe();
//	ptmp->m_Run = 1;
	if (DirectXMng.IsDirectInputValid()) return;
	DirectXMng.GetMousePos() = point;
	LBtnDown(point);
}

void CChildView::OnLButtonDblClk( UINT nFlags, CPoint point )
{
//	CUser *ptmp = UserManager.GetMe();
//	ptmp->m_Run = 2;
	if (DirectXMng.IsDirectInputValid()) return;
	DirectXMng.GetMousePos() = point;
	LBtnDown(point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	if (DirectXMng.IsDirectInputValid()) return;
	DirectXMng.GetMousePos() = point;
	LBtnUp(point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (DirectXMng.IsDirectInputValid()) return;
	DirectXMng.GetMousePos() = point;
	MouseMove(point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if (DirectXMng.IsDirectInputValid()) return;
	DirectXMng.GetMousePos() = point;
	RBtnDown(point);
}

void CChildView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	if (DirectXMng.IsDirectInputValid()) return;
	DirectXMng.GetMousePos() = point;
	RBtnUp(point);
}

//Login ������ ���� ó�� (uid:�������� �Ҵ�� user id)
void CChildView::SetMyUserId(int uid)
{
	m_iMyId = uid;
	UserManager.SetMyUserId(m_iMyId);
}

void CChildView::CreateEditor()
{
	//CRect editorRect(60, 460, 580, 480);l, t, r, b
	CRect editorRect(30, 460, 580, 480);
	CSize fontSize(14, 14);
	m_pBBDX_Editor = new BBDX_ChatEditor(this, NULL, FALSE, editorRect);

	CRect outerRect(30, 10, 610, 100);//150
	m_pChatOuter = new BBDX_ChatOuter("����", 12, outerRect, 500, 2);
// �켮
/*
	CRect editorRect_password = GDialog_AccountLogin.GetTextOutRect(11);// password.
	m_pBBDX_Editor_password = new BBDX_Editor(this, FALSE, editorRect_password, "Soma14", fontSize.cx, fontSize.cy);
	m_pBBDX_Editor_password->SetFocus();
	m_pBBDX_Editor_password->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.

	CRect editorRect_id = GDialog_AccountLogin.GetTextOutRect(10); // id.
	m_pBBDX_Editor_id = new BBDX_Editor(this, FALSE, editorRect_id, "Soma14", fontSize.cx, fontSize.cy);
	m_pBBDX_Editor_id->SetFocus();
	m_pBBDX_Editor_id->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.
*/
// �켮.
}

void CChildView::OnSetFocus(CWnd* pOldWnd) 
{
	CWnd::OnSetFocus(pOldWnd);

	if(g_pFocusDialog) g_pFocusDialog->SetFocus();
	if(g_pFocusWnd && g_pFocusWnd->GetSafeHwnd())
	{
		g_pFocusWnd->SetFocus();
		g_pFocusWnd = NULL;
	}
}

int del_test = 0;
//int del_type = 1;
//Editor���� Fowarding����
void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
//	static short hour = 18;
	// TODO: Add your message handler code here and/or call default
	if (!m_pBBDX_Editor) return;

	if(Dialog_Quit.IsVisible())
	{
		if(nChar == VK_RETURN || nChar == VK_ESCAPE)
		{
			Dialog_Quit.OnKeyDown(nChar, nRepCnt, nFlags);
			return;
		}
		return;
	}
	else if(nChar == VK_ESCAPE && g_pShowDialog && g_pShowDialog->IsVisible())
	{
//		g_pShowDialog->HideWindow();
		g_pShowDialog->OnKeyDown(nChar, nRepCnt, nFlags);
		return;
	}

	CUser *pMe = UserManager.GetMe();
	//if( nChar == VK_RETURN && !g_pFocusDialog) m_pBBDX_Editor->SetFocus();//this_chat
	if (pMe && pMe->IsCharDie() == FALSE)
	{
/*		if(g_pFocusDialog)
		{
			if(g_pFocusDialog->OnKeyDown(nChar, nRepCnt, nFlags)) return;
		}*/

		switch(nChar)
		{
		case VK_RETURN:
			m_pBBDX_Editor->SetFocus();
			break;
		case VK_ESCAPE:
			{
				m_pBBDX_Editor->ClearTexts();
			}
			break;
		case VK_TAB:
			if(m_bKeyDown[VK_TAB] == 0)
			{
				CUser *ptmp = UserManager.GetMe();
				if(ptmp == NULL) return;
				BYTE buf[10];
				int offset = 0;
				BYTE battletype = 0x00;
				CPacketParser::SetByte(buf, offset, PKT_BATTLEMODE);
				
				if(ptmp->m_BattleMode == 0)
				{
					battletype = 0x01;
				}
				else if(ptmp->m_BattleMode == 1)
				{
					battletype = 0x02;
				}
				else
				{
					battletype = 0x00;
				}
				CPacketParser::SetByte(buf, offset, battletype);
				SocketMng.Send(offset, buf);
				m_bKeyDown[VK_TAB] = 1;
			}
			break;
		case VK_F1:
			if(m_bKeyDown[VK_F1] == 0)
			{
				CUser *ptmp = UserManager.GetMe();
				if(ptmp->m_MyBeltData[0].m_vUsage > 0) Dialog_Main.SendUseItem(0);
				m_bKeyDown[VK_F1] = 1;
			}
			break;
		case VK_F2:
			if(m_bKeyDown[VK_F2] == 0)
			{
				CUser *ptmp = UserManager.GetMe();
				if(ptmp->m_MyBeltData[1].m_vUsage > 0) Dialog_Main.SendUseItem(1);
				m_bKeyDown[VK_F2] = 1;
			}
			break;
		case VK_F3:
			if(m_bKeyDown[VK_F3] == 0)
			{
				CUser *ptmp = UserManager.GetMe();
				if(ptmp->m_MyBeltData[2].m_vUsage > 0) Dialog_Main.SendUseItem(2);
				m_bKeyDown[VK_F3] = 1;
			}
			break;
		case VK_F4:
			if(m_bKeyDown[VK_F4] == 0)
			{
				CUser *ptmp = UserManager.GetMe();
				if(ptmp->m_MyBeltData[3].m_vUsage > 0) Dialog_Main.SendUseItem(3);
				m_bKeyDown[VK_F4] = 1;
			}
			break;
		case VK_F5:
			if(m_bKeyDown[VK_F5] == 0)
			{
				Dialog_Main.SetSelMagic(0);
				m_bKeyDown[VK_F5] = 1;
			}
			break;
		case VK_F6:
			if(m_bKeyDown[VK_F6] == 0)
			{
				Dialog_Main.SetSelMagic(1);
				m_bKeyDown[VK_F6] = 1;
			}
			break;
		case VK_F7:
			if(m_bKeyDown[VK_F7] == 0)
			{
				Dialog_Main.SetSelMagic(2);
				m_bKeyDown[VK_F7] = 1;
			}
			break;
		case VK_F8:
			if(m_bKeyDown[VK_F8] == 0)
			{
				Dialog_Main.SetSelMagic(3);
				m_bKeyDown[VK_F8] = 1;
			}
			break;
		case VK_F9:
			if(m_bKeyDown[VK_F9] == 0)
			{
				if(Dialog_Status.IsVisible()) Dialog_Status.HideWindow();
				else Dialog_Status.ShowWindow();
				m_bKeyDown[VK_F9] = 1;
			}
			break;
		case VK_F11:
			if(m_bKeyDown[VK_F11] == 0)
			{
				if(Dialog_MagicCtrl.IsVisible()) Dialog_MagicCtrl.HideWindow();
				else Dialog_MagicCtrl.ShowWindow();
				m_bKeyDown[VK_F11] = 1;
			}
			break;
		case VK_F12:
			if(m_bKeyDown[VK_F12] == 0)
			{
				if(Dialog_Chat.IsVisible()) Dialog_Chat.HideWindow();
				else Dialog_Chat.ShowWindow();
				m_bKeyDown[VK_F12] = 1;
			}
			break;
		case 'S':
			if(GetKeyState(VK_CONTROL)&0x8000)
			{
				if(g_vMainMode == 0) g_vMainMode = 1;
				else g_vMainMode = 0;
				SetMainMode(g_vMainMode);
			}
			break;
		case 'Q':
			if(GetKeyState(VK_CONTROL)&0x8000)
			{
				Dialog_Quit.ShowWindow(-1, NULL);
			}
			break;		
/*		case VK_NUMPAD7:
			{
				CRain::SetRain();
			}
			break;
		case VK_NUMPAD8:
			{
				CRain::SetEraseRain();
			}
			break;
		case VK_NUMPAD9:
			{
//				Weather.SetWeatherInfo( 1,1,1,hour,0);
				hour++;
				if( hour == 22 ) hour = 0;
				else if( hour == 6 ) hour = 18;

			}
			break;
*/
		default: 
			break;
		}
	}
}
#include "magiccomet.h"
void CChildView::InitStaticVariables()
{
	CUser::m_bpCharManager = &CharManager;	//CUser�� static Member �ʱ�ȭ
	CUser::m_bpDirectXMng = &DirectXMng;	//CUser�� static Member �ʱ�ȭ
	CUser::m_bpUserManager = &UserManager;	//CUser�� static Member �ʱ�ȭ
	CMagic::pMagicManager = &MagicManager;	//CMagic�� static Member �ʱ�ȭ
	CMagicComet::pMagicManager = &MagicManager;	//this_fly
	CUser::m_bpArmatureManager = &ArmatureManager;
}

void CChildView::Search_Item()// �������� �����ϰ� �������ش�..���ϸ� ���ϴµ���..����...������ �ִ°� ������..
{
	CUser *ptmp = UserManager.GetMe();

	for(int i = 0; i<50;i++)
	{
		// �̰����� �κ��丮 ����Ÿ�� ����Ÿ�� �ְ� �޴´�..���������¾�������....
		//Item_Total.m_Item_Arm.m_Item_Type[i] = ptmp->GetInv_ItemPic(i);// �׸���ȣ..
		Item_Total.m_Item_Index[i] = ptmp->GetInv_ItemIndex(i);
		Item_Total.m_Item_Type[i] = ptmp->GetInv_ItemType(i);// ���⸦ ����ִ� Ÿ�԰����� ���ؼ�..
		Item_Total.m_Item_Arm[i] = ptmp->GetInv_ItemArm(i);// ������.
		Item_Total.m_Item_Picnum[i] = ptmp->GetInv_ItemPic(i);	
		Item_Total.m_Item_Name[i] = ptmp->GetInv_ItemName(i);	



		if(ptmp->GetInv_ItemUsage(i) > 0)
		{
			Item_Total.m_Item_Small->m_Item_Pic[i] = Item_Total.m_Item_Picnum[i];// �׸��� �־��ش�..������ �κ��丮â�ȿ� �����¾��������׸�
			Item_Total.m_Item_Small->m_Item_Name[i] = Item_Total.m_Item_Name[i];// �׸��� �־��ش�..������ �κ��丮â�ȿ� �����¾��������׸�
		}
		else
		{
			Item_Total.m_Item_Small->m_Item_Pic[i] = -1;
			Item_Total.m_Item_Small->m_Item_Name[i] = _T("");// small���� ���� �ΰ��� �ۿ� ����. .�׸� ��ȣ�� �̸�..
		}
	}

	//GetItemPicIndex(i);
	// �κ��丮 ĳ���� �׸��� �׷��ش�.
	for(int type =0;type<9;type++)
	{
//		if(Item_Total.m_Item_Small->m_Item_Pic[type] > 0)
//		{
		// ���� ĳ���Ͷ� �ٸ��ٸ� �ٽ� �о�� �Ѵ�.
		if(m_Old_Item_Type[type] != Item_Total.m_Item_Small->m_Item_Pic[type])
		{
			int k = Item_Total.m_Item_Small->m_Item_Pic[type];
			
			// ������..
			// ���Ͽ��� ������ ������ �о� ����..���..
			k = GetItemPicIndex(k);
			/////////////////////////////////////
			// ���� ������ ���� ��ġ..(�������� �ƴ�..������ ���� �޴� �������� �ٸ�)
			/*switch(type)
			{
			case 0:// �Ӹ�
				if(k < 0) k=0;
				break;
			case 1:// �Ͱɸ�
				if(k < 0) k=0;
				break;
			case 2:// �����
				if(k < 0) k=0;
				break;
			case 3://��ü ����
				if(k < 0) k=0;
				else if(k==13) k=1;//�⺻1
				else if(k==14) k=2;//�⺻2
				else if(k==15) k=3;//�⺻3
				else if(k==16) k=6;//�⺻4
				else if(k==19) k=5;//ö����
				else if(k==20) k=4;//����
				else k=1;//��Ÿ..
				break;
			case 4:// ��ü ����
				if(k < 0) k=0;
				else if(k==21) k=1;//�⺻1
				else if(k==22) k=2;//�⺻2
				else if(k==23) k=3;//�⺻3
				else if(k==24) k=4;//�⺻4
				else if(k==27) k=5;//ö����
				else if(k==28) k=4;//����
				else k=1;//��Ÿ..
				break;
			case 5:// �Ź�
				if(k < 0) k=0;
				else if(k==29) k=1;//�⺻1
				else if(k==30) k=2;//�⺻2
				else if(k==31) k=5;//�⺻3
				else if(k==32) k=4;//�⺻4
				else if(k==33) k=5;//ö����
				else k=1;//��Ÿ..
				break;
			case 6:// ���м�
				if(k < 0) k=0;
				else if(k==10) k=8;// ����
				else if(k==1) k=1;// ��
				else if(k==2) k=2;//������
				else if(k==4) k=4;//Ȱ
				else if(k==5) k=5;//â
				else k=1;//��Ÿ..
				break;
			case 7://�޼�
				if(k < 0) k=0;
				else k=1;
				break;
			case 8://�����ո�
				if(k < 0) k=0;
				k=0;
				break;
			case 9://�޼ո� 
				if(k < 0) k=0;
				k=0;
				break;
			default:
				if(k < 0) k=0;
				k=0;
				break;
			}
			*/
/*			//////////////////////////////////////
			if(type != 6)// ���� �����϶���..
			{
				if(k < 0) k=0;
				else k = 1;// �ӽ�..���� �׸� ����Ÿ�� �̿��ؾ��Ѵ�..���߿���
			}
			else
			{
				//�ӽ� ���̺��� ����� �̰����� ���ؾ��Ѵ�...��..��F��..��..
				if(k < 0) k=0;
				else if(k==10) k=8;// ����
				else if(k==1) k=1;// ��
				else if(k==2) k=2;//������
				else if(k==4) k=4;//Ȱ
				else if(k==5) k=5;//â
				else k=1;//��Ÿ..
			}
*/
//�켮... �����ͷ� �ٲ�... 9�� 9��.....
			Item_Inv->Change_InvItem(type, k);//  �ӽ÷� 1�� ���� 0�� �ƹ��͵� ����.
			// ó������ ������ �������ش�.
			m_Old_Item_Type[type] = Item_Total.m_Item_Small->m_Item_Pic[type];
		}
//		}
	}

//	if(m_Arry_ItemType[1]==-1)// ó���϶�...�ӽ� ���߿��� ������ ���� �޾ƾ߰���..�̺κ���..��ġ����..
//	{
//		m_Arry_ItemType[i] = Item_Total.m_Item_Type[i];
//		m_Arry_ItemIndex[i] = Item_Total.m_Item_Index[i];
//	}
	
		

//	if(data > 0 )
//	{
//		if(Item_Total.m_Item_Arm.m_Item_Type[i] != data)
//			Item_Total.m_Item_Arm.Input(i, data);//test...
//	}
	
}

void CChildView::Item_Draw()
{
	Search_Item();// ������ ����Ÿ�� �ٽ� �����´�...
	Item_Total.m_Item_Small->InvWindowDraw(DirectXMng.m_pDrawSurface);
//�켮...�����ͷ� �ٲ�..... 9�� 9��
	Item_Inv->Draw(0, -25);// �κ��丮 ĳ����..�׸�..
}

void CChildView::ShopItem_Draw()
{
	Search_Item();// ������ ����Ÿ�� �ٽ� �����´�...
	Item_Total.m_Item_Small->ShopMeWindowDraw(DirectXMng.m_pDrawSurface);
	Item_Total.m_Item_Small->ShopWindowDraw(DirectXMng.m_pDrawSurface);
}

void CChildView::Magic_Item_Draw()
{
	// ������ ���� �ƴϸ�..��� ���� ������ �ִ� ������������ �����;� �Ѵ�.
	Item_Total.m_Magic_Item->ShopWindowDraw(DirectXMng.m_pDrawSurface);
}

void CChildView::AuctionSell_Item_Draw()
{
	Search_Item();// ������ ����Ÿ�� �ٽ� �����´�...
	Item_Total.m_Item_Small->InvWindowDraw(DirectXMng.m_pDrawSurface);
}

void CChildView::Item_Init()
{
	Item_Total.Init(DirectXMng.m_pDD);

//�켮 ���߿� �����κ�.....
//	Item_Inv.Init(0);
//	Item_Inv2.Init(0);
//	Item_Inv3.Init(0);
//�켮.

	Item_Field.InitData(DirectXMng.m_pDD);
}

BOOL CChildView::ChangeItem(int index)
{
	// �������� ���� Ŭ�� �ϸ�..Ÿ���� ����..����Ѵ�. ���� �Ұ�������..��ġ����..
	// ���� 1-8������ �������� ������ �ִ�... �̰��� �̿��ؼ�..
	// �̺κ��� �����ؾ��Ѵ�..
	// �޽����� ������ ó���ϰԲ�..��������...^^
	int arm = Item_Total.m_Item_Arm[index];// ������..

	// �ӽ�
	if(arm == 8)
		arm = 6;
	else if(arm == 9)// �������� �Ѿ� ���� �������� ���� ����ϴ� ���� �������� Ʋ���� ������ �̷��� ����� �ش�.
		arm = 8;//�Ǵ� 7 ����ִ��ʿ� ���� �Ǵµ�..��� ��������?


	if(arm == 10)// �������� �������� ���� �شٴ���..��Ÿ���..
	{
		TRACE("��� �������� Ŭ���ߴ�.");
		return TRUE;
	}
	else if(arm == 11)//���� ����
	{
		TRACE("��Ḧ Ŭ���ߴ�.");
		return TRUE;
	}

	if(index >= 0 && index < 10)
	{
		// �������� ������..
		UserManager.SendChang_Item(index, -1);//
		return TRUE;
	}
	else
	{
		// ������ ���� �Ǵ� ���..
		UserManager.SendChang_Item(index, arm);
		return TRUE;
	}

}

void CChildView::AttackMagic(int suid, int euid, int magic_type)
{
/*	// uid�� ���� ��ġ�� �����;���..��...
	CUser *pDestUser = CChildView::UserManager.GetUserWithUid(euid);
	CUser *pStartUser = CChildView::UserManager.GetUserWithUid(suid);
	CPoint ptSPos;
	CPoint ptEPos;

	if (pStartUser && pDestUser) 
	{
		pStartUser->SetMotion(CUser::UM_Attack);
		ptSPos = pStartUser->GetPosition();
		ptEPos = ppDestUser->GetPosition();

		///////////////////////////////////////
		CPoint tmp = MapManager.GetMapStartPos();
		CPoint UserPos;
		CPoint tmp_Pos;// ������ ���� ����..

		UserPos = ptSPos - tmp;

		tmp_Pos = pos - UserPos;

		ptEPos.x = ptSPos.x + tmp_Pos.x;
		ptEPos.y = ptSPos.y + tmp_Pos.y;
		int nDir = UserManager.SetAimedMagic(ptSPos, ptEPos, 6, MAGIC_TYPE_UP);
		pMe->SetDirection(nDir);
	}
*/
}

void CChildView::Rail_MagicProcess()
{

//	if(UserManager.m_Rail_Magic == 1)
//	{

//		UserManager.SetViewMagic(iSorUid, nMagicIndex, nMagicType, bDir, i);
//	}

}


////////////////////////////////////////////////////////////////////////////////
//login ���� �Լ���...
///////////////////////////////////////////////////////////////////////////////

BOOL CChildView::LoginAcount(CString id, CString password)
{
	// ���ǰ� ����
	//CString szIP = _T("192.203.143.85");
//	CString szIP = _T("192.203.141.4");//���� �켮 ���Ƴ���.. ����� ip���...
//	CString szIP = _T("192.203.141.140");// �׽�Ʈ
//	CString szID = _T("soma");
//	CString szPasswd = _T("soma");

	CString szID = id;
	CString szPasswd = password;

//	SocketMng.m_szDestIp = szIP; //�켮..
	SocketMng.m_szDestIp = m_conIP; 
	SocketMng.m_iPort = 4110;

//	SocketMng.m_szLoginId = szID;//�ӽ�
	SocketMng.m_szAcountLoginId = szID;
	SocketMng.m_szPasswd = szPasswd;

	BOOL bOk = FALSE;

	if(m_S_Connection != 1)
	{		
		if (SocketMng.ConnectSocket())
		{
			bOk = TRUE;
			m_S_Connection = 1;
		}
		else 
		{
			return bOk;
		}
	}

	//Session�� �ʱ� ��Ŷ�� ����
	CMsg cmsg;
	cmsg.ID(SM_GAMEINFO2_REQ);

	SocketMng.SendRawPacket(cmsg.GetSize(), (PBYTE)cmsg.GetBuf());
	
	Sleep(300);// ���� �ɶ����� ���� ������ ������...???
//	TRACE("9\n");//del

/*	MSG msg;
	while (TRUE==PacketParser.GetSessionLoginStatus())// && GetSafeHwnd()) //Session�� ����� ���������� ���������� ���� (Cancel��ư ��밡��)
	{
		Sleep(300);
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
			if (msg.message==WM_QUIT)
			{
				bOk = FALSE;
				break;
			}
		}
	}
*/	return bOk;
}

BOOL CChildView::LoginAcountNew()
{
	// ���ǰ� ����
	SocketMng.m_szDestIp = m_conIP; //�켮..����� ip���...
	SocketMng.m_iPort = 4110;
	SocketMng.m_szAcountLoginId = m_New_Account_ID;;
	SocketMng.m_szPasswd = m_New_Account_Passwd;

	BOOL bOk = FALSE;
	if(m_S_Connection != 1)
	{
		if (SocketMng.ConnectSocket())
		{
			bOk = TRUE;
			m_S_Connection = 1;// ������ �ι� ���� �ʱ� �ϱ����ؼ�..
		}
		else 
		{
			LogIn();
			return bOk;
		}
	}

	//Session�� �ʱ� ��Ŷ�� ����
	CMsg cmsg;
	cmsg.ID(SM_REGUSER_REQ);
	cmsg << (CString)m_New_Account_ID;
	cmsg << (CString)m_New_Account_Passwd;
	cmsg << (CString)m_New_Account_Name;
	cmsg << (CString)m_New_Account_SocNo;
	cmsg << (CString)m_New_Account_Address;
	cmsg << (CString)m_New_Account_TellNo;
	cmsg << (CString)m_New_Account_Email;

	SocketMng.SendRawPacket(cmsg.GetSize(), (PBYTE)cmsg.GetBuf());
	return bOk;
}

BOOL CChildView::LogIn()
{
	SocketMng.SendLogin();

	m_test_Flag = 13;//�α�����..


	m_LoadinView = new SLoadingView;
	m_LoadinView->Create(DirectXMng.m_pDD, "S_Load", 0);
	m_LoadinView->Draw(DirectXMng.m_pDrawSurface);

	DirectXMng.Flip();
//	ClearScreen();

	return 0;
}

void CChildView::Login_Window()
{
	m_First_Menu = TRUE;// 

	int id_flag = 1;
	CString str_id;
	CString str_password;

	for(int type =0;type<9;type++)// �ӽ�
	{
//�켮... �����ͷ� �ٲ�... 9�� 9��....
		Item_Inv->Change_InvItem(type, 0);
		Item_Inv2->Change_InvItem(type, 0);
		Item_Inv3->Change_InvItem(type, 0);
//�켮.
	}

//�켮.. �����ͷ� �ٲ�... 9�� 9��....
	Item_Inv->Change_InvItem(4, 0);

	int Chang_Char = 0;
	int Chang_Count = 0;
	int Next_view = 0;
	CPoint pos1, pos2, pos3;
	pos1.x = 150; pos1.y = -100;
	pos2.x = 250; pos2.y = 0;
	pos3.x = 350; pos3.y = -100;

//	while(!GetAsyncKeyState(VK_ESCAPE)) 

	if(1)
	{
		MouseProcess();
//		Dialog_Login.Draw(DirectXMng.m_pDrawSurface, Next_view);
		if(GetAsyncKeyState(VK_F1) & 0x8000)
		{
			Chang_Char = 1;
		}

		if(GetAsyncKeyState(VK_F2) & 0x8000)// ���� ȭ������ �Ѿ�� �Ѵ�.
		{
			if(Next_view != 1)
				LogIn();
			Next_view = 1;
			
		}

		if(Chang_Char == 1)
		{
			if(Chang_Count == 0)
			{
				pos1.x += 2; pos1.y += 2;
				pos2.x += 2; pos2.y -= 2;
				pos3.x -= 4; 
			}
			else if(Chang_Count == 1)
			{
				pos3.x += 2; pos3.y += 2;
				pos1.x += 2; pos1.y -= 2;
				pos2.x -= 4; 
			}
			else if(Chang_Count == 2)
			{
				pos2.x += 2; pos2.y += 2;
				pos3.x += 2; pos3.y -= 2;
				pos1.x -= 4; 
			}

			if(pos1.x == 150 || pos2.x == 150 || pos3.x == 150)
			{
				Chang_Char = 0;
				Chang_Count ++;
				if(Chang_Count > 3) Chang_Count =0;
			}
		}
		//int x = 95 + tmp_x;//74;
		//int y = 360 + tmp_y;


//�켮.. �����ͷ� �ٲ�... 9�� 9��....
		if(Next_view == 1)// �ι�° ȭ�鿡�� ĳ���͵��� ���̰�..
		{
			switch(Chang_Count)
			{
			case 0:
				Item_Inv3->Draw(pos3.x,pos3.y);
				Item_Inv->Draw(pos1.x,pos1.y);
				Item_Inv2->Draw(pos2.x,pos2.y);
				break;
			case 1:
				Item_Inv2->Draw(pos2.x,pos2.y);
				Item_Inv3->Draw(pos3.x,pos3.y);
				Item_Inv->Draw(pos1.x,pos1.y);
				break;
			case 2:
				Item_Inv->Draw(pos1.x,pos1.y);
				Item_Inv2->Draw(pos2.x,pos2.y);
				Item_Inv3->Draw(pos3.x,pos3.y);
				break;
			default:
				Item_Inv->Draw(pos1.x,pos1.y);
				Item_Inv3->Draw(pos3.x,pos3.y);
				Item_Inv2->Draw(pos2.x,pos2.y);
				break;
			}
		}
//�켮..
		else
		{
			if (m_pBBDX_Editor_id) 
				m_pBBDX_Editor_id->DCDrawOffsetedCurText(DirectXMng.m_pDrawSurface);	//�����Ϳ� ������ �� �׸���(Editor �� ���� �Ⱥ��̴µ� ����)
//			if (m_pBBDX_Editor_password) 
//				//m_pBBDX_Editor_password->DrawOffsetedCurText(DirectXMng.m_pDrawSurface);	//�����Ϳ� ������ �� �׸���(Editor �� ���� �Ⱥ��̴µ� ����)
		}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             



		if(GetAsyncKeyState(VK_TAB) & 0x8000)
		{
			if(id_flag == 1)
			{
				Sleep(200);
				m_pBBDX_Editor_id->SetFocus();
				id_flag = 0;
				m_pBBDX_Editor_id->GetText();
				str_id =  m_pBBDX_Editor_id->GetCurEditorText();
			}
			else 
			{
				Sleep(200);
				m_pBBDX_Editor_password->SetFocus();
				id_flag = 1;
				m_pBBDX_Editor_password->GetText();
				str_password =  m_pBBDX_Editor_password->GetCurEditorText();
			}
		}

		DirectXMng.Flip();
	}

	//LogIn();

	ClearScreen();// ȭ���� �����ش�.
	
//�켮.. �����ͷ� �ٲ�.. 9�� 9��..
	Item_Inv->Init();

	SetFocus();
}

BOOL CChildView::InitLogin()
{
	int view_mode = 0;
	int id_flag = 0;
	CString str_id;
	CString str_password;
	MSG msg;
	CRect txRect;

	GDialog_AccountLogin = new CDialog_AccountLogin;
	//GDialog_AccountLogin = GDialog_AccountLogin;
	GDialog_AccountLogin->Create(DirectXMng.m_pDD, "Account.lib", 0);
	GDialog_AccountLogin->CreateEditor(this,view_mode);

	int spr_number = 0;
	
	ClearScreen();

	int NewAccountSelect=0;
	BOOL bRet = TRUE;
	BOOL key_return = FALSE, key_esc = FALSE;
	int key_tab = 0;

 	GDialog_AccountLogin->SetViewMode(0);
	while(id_flag != 10 && bRet == TRUE) 
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			switch(msg.message)
			{
			case WM_QUIT:
				AfxPostQuitMessage(0);
				//�켮
				if(GDialog_AccountLogin) {delete GDialog_AccountLogin; GDialog_AccountLogin = NULL;}
				bRet = FALSE;
				break;
			case WM_KEYDOWN:
				if(msg.wParam == VK_RETURN)
				{
					key_return = TRUE;
					continue;
				}
				else if(msg.wParam == VK_TAB)
				{
					if(GetKeyState(VK_SHIFT)&0x8000)
					{
						key_tab = -1;
					}
					else
					{
						key_tab = 1;
					}
					continue;
				}
				else if(msg.wParam == VK_ESCAPE)
				{
					key_esc = TRUE;
					continue;
				}
				break;
			}
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			AccountMouseProcess(&id_flag);
			GDialog_AccountLogin->Draw(DirectXMng.m_pDrawSurface);
// �켮de = GDialog_AccountLogin->GetViewMode();
			switch(view_mode)
			{
			case 0:
				if(GDialog_AccountLogin->m_vOk == 3)
				{
					if(!str_id.IsEmpty( ) && !str_password.IsEmpty() && m_bLoginOk)// ���� �α���..����...
					{	
						unsigned char *name = (unsigned char*)str_id.GetBuffer(str_id.GetLength());
						bool ret = true;
						int len = strlen((const char*)name);
						WORD str = 0;
						for(int ii=0; ii < len; ii++)
						{
							if( !((name[ii] >= 0x30 && name[ii] <= 0x39) || 
								  (name[ii] >= 0x41 && name[ii] <= 0x5a) || 
								  (name[ii] >= 0x61 && name[ii] <= 0x7a)) )
								{
									if ( name[ii] & 0x80 )                  // �ֻ��� ��Ʈ�� 1�̸� �ѱ۷� �Ǵ�
									{
										str = (name[ii] << 8) | name[ii + 1];
										if((str >= 0xb0a0) && (str <= 0xc8ff))
										{
											if((name[ii + 1] == 0xa0) || (name[ii + 1] == 0xff))
											{
												GDialog_AccountLogin->SetMessage("����� �� ���� ���̵��Դϴ�.");
												GDialog_AccountLogin->m_vViewMode += 3;
												GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTextBuffer();
												GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTexts();
												m_New_Account_ID.Empty();
												ret = false;
												break;
											}
										}
										else
										{
											GDialog_AccountLogin->SetMessage("����� �� ���� ���̵��Դϴ�.");
											GDialog_AccountLogin->m_vViewMode += 3;
											GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTextBuffer();
											GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTexts();
											m_New_Account_ID.Empty();
											ret = false;
											break;
										}
										ii++;
									}
									else 
									{
									   if(name[ii] == 0x5f) continue;
									   GDialog_AccountLogin->SetMessage("����� �� ���� ���̵��Դϴ�.");
									   GDialog_AccountLogin->m_vViewMode += 3;
									   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTextBuffer();
									   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTexts();
									   m_New_Account_ID.Empty();
									   ret = false;											
									   break;
									}
								}
						}
						if(ret) 
						{
							//�ٽ�ȣ�� �ϴ� ���� ����.
							GDialog_AccountLogin->m_vOk = 0;
							m_bLoginOk = false;
							LoginAcount(str_id, str_password);								
						}

					}
					else
					{
						if(m_bLoginOk)
						{
							GDialog_AccountLogin->SetMessage(_T("���̵�� �н����带\n��� �־� �ּ���."));
							view_mode += 3;
							GDialog_AccountLogin->SetViewMode(view_mode);
						}
					}
				}
				else if(GDialog_AccountLogin->m_vOk == 4)// ���..
				{
					//GDialog_AccountLogin->m_vOk = 0;
					// ���..
					AfxPostQuitMessage(0);
					//Sleep(300);
				}
				else if(GDialog_AccountLogin->m_vOk == 5)//new ���ο� ���� ����� â
				{
//					STARTUPINFO si;
//					PROCESS_INFORMATION pi;
//					HKEY key;
//					BYTE buff[100];
					DWORD leng = 100;

					AfxPostQuitMessage(0);
					ShellExecute(NULL, "open", "Iexplore.exe", "http://www.netsoma.com/membership/join/default.htm", NULL, SW_SHOWDEFAULT);
/*
					::RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\IE4\\Setup",0,KEY_QUERY_VALUE | KEY_READ,&key);					
					::RegQueryValueEx(key, "Path", NULL, NULL, buff, &leng);
					::RegCloseKey(key);

					strcat((char *)buff,"\\Iexplore.exe www.netsoma.com/membership/join/default.htm"); 

					ZeroMemory(&si, sizeof(si));
					si.cb = sizeof(si);
					si.wShowWindow = SW_SHOWMAXIMIZED;
					
					AfxPostQuitMessage(0);
					::CreateProcess(NULL,(LPTSTR)buff,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS ,NULL,NULL,&si,&pi);
*/
/*
					delete GDialog_AccountLogin; GDialog_AccountLogin = NULL;
					GDialog_AccountLogin = new CDialog_AccountLogin;
					GDialog_AccountLogin = GDialog_AccountLogin;

					view_mode = 1; id_flag = 0; key_tab = 0;

					GDialog_AccountLogin->SetViewMode(view_mode);
					GDialog_AccountLogin->Create(DirectXMng.m_pDD, "NewAcc.lib", 0); 
					GDialog_AccountLogin->CreateEditor(this,view_mode);
*/
				}
				else if(GDialog_AccountLogin->m_vOk == 6)
				{
//					STARTUPINFO si;
//					PROCESS_INFORMATION pi;
//					HKEY key;
//					BYTE buff[100];
					DWORD leng = 100;

					AfxPostQuitMessage(0);
					ShellExecute(NULL, "open", "Iexplore.exe", "http://www.netsoma.com/membership/privacy/default.htm", NULL, SW_SHOWDEFAULT);

/*
					::RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Software\\Microsoft\\IE4\\Setup",0,KEY_QUERY_VALUE | KEY_READ,&key);					
					::RegQueryValueEx(key, "Path", NULL, NULL, buff, &leng);
					::RegCloseKey(key);

					strcat((char *)buff,"\\Iexplore.exe www.netsoma.com/membership/privacy/default.htm"); 

					ZeroMemory(&si, sizeof(si));
					si.cb = sizeof(si);
					si.wShowWindow = SW_SHOWMAXIMIZED;
					
					AfxPostQuitMessage(0);
					::CreateProcess(NULL,(LPTSTR)buff,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS ,NULL,NULL,&si,&pi);
*/
/*
					view_mode = 2; id_flag = 0; key_tab = 0;
					GDialog_AccountLogin->SetViewMode(view_mode);
					GDialog_AccountLogin->CreateEditor(this,view_mode);
*/
				}

				break;
			case 1:
				if(GDialog_AccountLogin->m_vOk == 3)
				{
					if(!m_New_Account_ID.IsEmpty() && !m_New_Account_Passwd.IsEmpty() && !m_New_Account_Passwd2.IsEmpty() &&
						!m_New_Account_Name.IsEmpty() && !m_New_Account_SocNo.IsEmpty() && !m_New_Account_Address.IsEmpty() &&
						!m_New_Account_TellNo.IsEmpty() && !m_New_Account_Email.IsEmpty() && m_bAccountNewOk)
					{
						if(!m_New_Account_Passwd.Compare(m_New_Account_Passwd2))
						{
							unsigned char *name = (unsigned char*)m_New_Account_ID.GetBuffer(m_New_Account_ID.GetLength());
//-----------------------------------------
							bool ret = true;
							int len = strlen((const char*)name);
							WORD str = 0;
							for(int ii=0; ii < len; ii++)
							{
								if( !((name[ii] >= 0x30 && name[ii] <= 0x39) || 
									  (name[ii] >= 0x41 && name[ii] <= 0x5a) || 
									  (name[ii] >= 0x61 && name[ii] <= 0x7a)) )
									{
										if ( name[ii] & 0x80 )                  // �ֻ��� ��Ʈ�� 1�̸� �ѱ۷� �Ǵ�
										{
											str = (name[ii] << 8) | name[ii + 1];
											if((str >= 0xb0a0) && (str <= 0xc8ff))
											{
												if((name[ii + 1] == 0xa0) || (name[ii + 1] == 0xff))
												{
												   GDialog_AccountLogin->SetMessage("����� �� ���� ���̵��Դϴ�.");
												   GDialog_AccountLogin->m_vViewMode += 3;
												   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTextBuffer();
												   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTexts();
												   m_New_Account_ID.Empty();
												   ret = false;
												   break;
												}
											}
											else
											{
											   GDialog_AccountLogin->SetMessage("����� �� ���� ���̵��Դϴ�.");
											   GDialog_AccountLogin->m_vViewMode += 3;
											   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTextBuffer();
											   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTexts();
											   m_New_Account_ID.Empty();
											   ret = false;
											   break;
											}
											ii++;
										}
										else 
										{
										   if(name[ii] == 0x5f) continue;
										   GDialog_AccountLogin->SetMessage("����� �� ���� ���̵��Դϴ�.");
										   GDialog_AccountLogin->m_vViewMode += 3;
										   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTextBuffer();
										   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTexts();
										   m_New_Account_ID.Empty();
										   ret = false;
										   break;
										}
									}
							}
//----------------------------------------
							if(ret) 
							{
								//�ٽ�ȣ�� �ϴ� ���� ����.
								GDialog_AccountLogin->m_vOk = 0;
								m_bLoginOk = false;
								LoginAcount(str_id, str_password);								
							}
						}
						else
						{
							if(m_bAccountNewOk)
							{
								GDialog_AccountLogin->SetMessage(_T("��й�ȣ�� ��й�ȣ\nȮ���� ���� Ʋ���ϴ�.\n���� �ٽ� ���ֽʽÿ�."));
								view_mode += 3;
								GDialog_AccountLogin->SetViewMode(view_mode);
							}
						}
					}
					else
					{
						if(m_bAccountNewOk)
						{
							GDialog_AccountLogin->SetMessage(_T("      ��� ������\n      ä���ּ���."));
							view_mode += 3;
							GDialog_AccountLogin->SetViewMode(view_mode);
						}
					}
				}
				else if(GDialog_AccountLogin->m_vOk == 4)//���
				{
					delete GDialog_AccountLogin; GDialog_AccountLogin = NULL;
					GDialog_AccountLogin = new CDialog_AccountLogin;
					//GDialog_AccountLogin = GDialog_AccountLogin;

					view_mode = 0; id_flag = 0; key_tab = 0;

					GDialog_AccountLogin->SetViewMode(view_mode);
					GDialog_AccountLogin->Create(DirectXMng.m_pDD, "Account.lib", 0); //�켮.
					GDialog_AccountLogin->CreateEditor(this,view_mode);
					GDialog_AccountLogin->Draw(DirectXMng.m_pDrawSurface);
//					DirectXMng.MouseInfoUpdate();

				}
				break;

			case 2:
				if(GDialog_AccountLogin->m_vOk == 7)
				{					
					if(!m_New_Account_Name.IsEmpty() && !m_New_Account_SocNo.IsEmpty())// �̸��� �ֹι�ȣ üũ.
					{
						//�ٽ�ȣ�� �ϴ� ���� ����.
						GDialog_AccountLogin->m_vOk = 0;
						//LoginAcount(str_id, str_password);
//						GDialog_AccountLogin->m_PersonalCheckOK = 1; // �׽�Ʈ.......
					}
					else
					{
						GDialog_AccountLogin->SetMessage(_T("�̸��� �ֹε�Ϲ�ȣ\n��� �־��ּ���."));
						view_mode += 3;
						GDialog_AccountLogin->SetViewMode(view_mode);
					}
				}
				else if(GDialog_AccountLogin->m_vOk == 8)// ���..
				{
					//GDialog_AccountLogin->m_vOk = 0;
					// ���..
					GDialog_AccountLogin->DeletePersonalCheck();
					view_mode = 0; id_flag = 0; key_tab = 0;
					GDialog_AccountLogin->SetViewMode(view_mode);
					//Sleep(300);
				}
				break;
			}

//���ο� ������ ���������� ����� ������ üũ.
//����� ������ �ٽ� ó�� ȭ������ ����.
			view_mode = GDialog_AccountLogin->GetViewMode();
			if(view_mode == 1 && GDialog_AccountLogin->m_SuccessNewChar >= 1)
			{
				switch(GDialog_AccountLogin->m_SuccessNewChar)
				{
				case 1:
						GDialog_AccountLogin->SetMessage(_T("���������� ��ϵǾ����ϴ�.\n ����Ű�� ��������!"));
						view_mode += 3;
						GDialog_AccountLogin->SetViewMode(view_mode);
						break;
				case 2:					
						delete GDialog_AccountLogin; GDialog_AccountLogin = NULL;
						GDialog_AccountLogin = new CDialog_AccountLogin;
						//GDialog_AccountLogin = GDialog_AccountLogin;

						view_mode = 0; id_flag = 0; key_tab = 0;

						GDialog_AccountLogin->SetViewMode(view_mode);
						GDialog_AccountLogin->Create(DirectXMng.m_pDD, "Account.lib", 0); //�켮.
						GDialog_AccountLogin->CreateEditor(this,view_mode);
						GDialog_AccountLogin->Draw(DirectXMng.m_pDrawSurface);
						//ĳ���� ������ �����ϸ�...^^
						//GDialog_AccountLogin.SetViewMode(0); // �����·� ������.
						GDialog_AccountLogin->m_SuccessNewChar = 0;
						m_bAccountNewOk = true;

						break;
				}
			}

			// ������ �����ϸ� �ʱ� ȭ���� ����������.
			if(view_mode == 0 && GDialog_AccountLogin->m_SuccessLogin >= 1)
			{
				switch( GDialog_AccountLogin->m_SuccessLogin )
				{
					case 1: id_flag = 10; m_bLoginOk = true; break;
					case 2: 
							GDialog_AccountLogin->SetMessage(_T("�̵�� ���̵��Դϴ�\n ����Ű�� ��������!"));
							view_mode += 3;
							GDialog_AccountLogin->SetViewMode(view_mode);
						   break;
					case 3:
							GDialog_AccountLogin->SetMessage(_T("��й�ȣ�� Ʋ�Ƚ��ϴ�.\n ����Ű�� ��������!"));
							view_mode += 3;
							GDialog_AccountLogin->SetViewMode(view_mode);
						   break;
					case 4:
							GDialog_AccountLogin->SetMessage(_T("�̹̻������ ���̵��Դϴ�.\n ����Ű�� ��������!"));
							view_mode += 3;
							GDialog_AccountLogin->SetViewMode(view_mode);
						   break;
				}
			}

			// Personal Check�� �����ϸ�.
			if(GDialog_AccountLogin->m_PersonalCheckOK == 1)
			{
				delete GDialog_AccountLogin; GDialog_AccountLogin = NULL;
				GDialog_AccountLogin = new CDialog_AccountLogin;
				//GDialog_AccountLogin = GDialog_AccountLogin;

				view_mode = 1; id_flag = 0; key_tab = 0;

				GDialog_AccountLogin->SetViewMode(view_mode);
				GDialog_AccountLogin->Create(DirectXMng.m_pDD, "NewAcc.lib", 0); //�켮.
				GDialog_AccountLogin->CreateEditor(this,view_mode);
			}




// �켮
			if(key_tab == 1)
			{
				key_tab = 0;
				view_mode = GDialog_AccountLogin->GetViewMode();
				if(view_mode == 0)
				{
					id_flag++;
					if(id_flag > 1) id_flag = 0;
				}
				else if(view_mode == 1)
				{
					id_flag++;
					if(id_flag > 8) id_flag = 0;
				}
				else if(view_mode == 2)
				{
					id_flag++;
					if(id_flag > 2) id_flag = 0;
				}
			}
			else if(key_tab == -1)
			{
				key_tab = 0;
				view_mode = GDialog_AccountLogin->GetViewMode();
				if(view_mode == 0)
				{
					id_flag--;
					if(id_flag < 0) id_flag = 1;
				}
				else if(view_mode == 1)
				{
					id_flag--;
					if(id_flag < 0) id_flag = 8;
				}
				else if(view_mode == 2)
				{
					id_flag--;
					if(id_flag < 0) id_flag = 2;
				}
			}

//ESCŰ�� ����  ó��.
			if(key_esc == TRUE)
			{
				key_esc = FALSE;
				view_mode = GDialog_AccountLogin->GetViewMode();

				if(view_mode > 2)
				{
					view_mode -= 3;
					GDialog_AccountLogin->SetViewMode(view_mode);

					if(GDialog_AccountLogin->m_pBBDX_Editor_id)
					{
						GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTextBuffer();
						GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTexts();
						if(GDialog_AccountLogin->m_pBBDX_Editor_password)
						{
							GDialog_AccountLogin->m_pBBDX_Editor_password->ClearTextBuffer();
							GDialog_AccountLogin->m_pBBDX_Editor_password->ClearTexts();
						}
					}
					if(GDialog_AccountLogin->m_SuccessLogin > 1)
					{
						GDialog_AccountLogin->m_SuccessLogin = 0;
						m_bLoginOk = true;

						if(GDialog_AccountLogin->m_pBBDX_Editor_password)
						{
							GDialog_AccountLogin->m_pBBDX_Editor_password->ClearTextBuffer();
							GDialog_AccountLogin->m_pBBDX_Editor_password->ClearTexts();
						}
					}
					if(GDialog_AccountLogin->m_KorlangMode)
					{
						if(GDialog_AccountLogin->m_pBBDX_Editor_password)
							GDialog_AccountLogin->m_pBBDX_Editor_password->ClearTexts();
						if(GDialog_AccountLogin->m_pBBDX_Editor_password2)
							GDialog_AccountLogin->m_pBBDX_Editor_password2->ClearTexts();
						GDialog_AccountLogin->m_KorlangMode = false;
						GDialog_AccountLogin->m_KorlangMode2 = false;
					}
					if(GDialog_AccountLogin->m_KorlangMode2)
					{
						if(GDialog_AccountLogin->m_pBBDX_Editor_password2)
							GDialog_AccountLogin->m_pBBDX_Editor_password2->ClearTexts();
						GDialog_AccountLogin->m_KorlangMode2 = false;
					}
					if(GDialog_AccountLogin->m_JuMinCheck)
					{
						if(GDialog_AccountLogin->m_pBBDX_Editor_number1)
							GDialog_AccountLogin->m_pBBDX_Editor_number1->ClearTexts();
						if(GDialog_AccountLogin->m_pBBDX_Editor_number2)
							GDialog_AccountLogin->m_pBBDX_Editor_number2->ClearTexts();
						GDialog_AccountLogin->m_JuMinCheck = false;
						GDialog_AccountLogin->m_JuMinCheck2 = false;
					}
					if(GDialog_AccountLogin->m_JuMinCheck2)
					{
						if(GDialog_AccountLogin->m_pBBDX_Editor_number2)
							GDialog_AccountLogin->m_pBBDX_Editor_number2->ClearTexts();
						GDialog_AccountLogin->m_JuMinCheck2 = false;
					}
				}
			}
//ESCŰ�� ���� ó����.

//Ű���� �Է¹��ڿ� ó��....
			if(view_mode == 0)// ù ȭ��..
			{ 
				LPTSTR	check = NULL;
				unsigned int i = 0;

				str_id = GDialog_AccountLogin->m_pBBDX_Editor_id->GetCurEditorText();
				GDialog_AccountLogin->m_pBBDX_Editor_password->GetText();
				str_password = GDialog_AccountLogin->m_pBBDX_Editor_password->GetCurEditorText();
				check = str_password.GetBuffer(8);
				
				while( i <= strlen(check) )
				{
					if(check[i] & 0x80)
					{					
						GDialog_AccountLogin->m_KorlangMode = true;
						GDialog_AccountLogin->m_pBBDX_Editor_password->ClearTextBuffer();
						GDialog_AccountLogin->m_pBBDX_Editor_password->ClearTexts();					
						GDialog_AccountLogin->SetMessage(_T("�ѱ��� ����Ҽ� �����ϴ�.\n����Ű�� ��������!"));
						view_mode += 3;
						GDialog_AccountLogin->SetViewMode(view_mode);
						TRACE("�ѱ��̴�.\n");
						break;
					}
					else i++;
				}

				GDialog_AccountLogin->DrawEditorText(DirectXMng.m_pDrawSurface,view_mode, id_flag);
			}
			else if(view_mode == 1)// ���� ����� â..
			{
				LPTSTR	check = NULL;
				unsigned int i = 0;

				m_New_Account_ID = GDialog_AccountLogin->m_pBBDX_Editor_id->GetCurEditorText();

//				GDialog_AccountLogin->m_pBBDX_Editor_password->GetText();
				m_New_Account_Passwd = GDialog_AccountLogin->m_pBBDX_Editor_password->GetCurEditorText();
/*				check = m_New_Account_Passwd.GetBuffer(8);

				while( i <= strlen(check) )
				{
					if(check[i] & 0x80)
					{
						GDialog_AccountLogin->m_KorlangMode = true;
						GDialog_AccountLogin->m_pBBDX_Editor_password->ClearTextBuffer();
						GDialog_AccountLogin->m_pBBDX_Editor_password->ClearTexts();					
						GDialog_AccountLogin->SetMessage(_T("�ѱ��� ����Ҽ� �����ϴ�.\n����Ű�� ��������!"));
						view_mode += 3;
						GDialog_AccountLogin->SetViewMode(view_mode);
						TRACE("�ѱ��̴�.\n");
						break;
					}
					else i++;
				}


				GDialog_AccountLogin->m_pBBDX_Editor_password2->GetText();
*/				m_New_Account_Passwd2 = GDialog_AccountLogin->m_pBBDX_Editor_password2->GetCurEditorText();
/*				check = m_New_Account_Passwd2.GetBuffer(8);

				i = 0;
				while( view_mode == 1 && i <= strlen(check) )
				{
					if(check[i] & 0x80)
					{
						GDialog_AccountLogin->m_KorlangMode2 = true;
						GDialog_AccountLogin->m_pBBDX_Editor_password2->ClearTextBuffer();
						GDialog_AccountLogin->m_pBBDX_Editor_password2->ClearTexts();					
						GDialog_AccountLogin->SetMessage(_T("�ѱ��� ����Ҽ� �����ϴ�.\n����Ű�� ��������!"));
						view_mode += 3;
						GDialog_AccountLogin->SetViewMode(view_mode);
						TRACE("�ѱ��̴�.\n");
						break;
					}
					else i++;
				}
*/
				m_New_Account_Name = GDialog_AccountLogin->m_pBBDX_Editor_name->GetCurEditorText();

				CString num_temp1,num_temp2;
				num_temp1 = GDialog_AccountLogin->m_pBBDX_Editor_number1->GetCurEditorText();
				check = num_temp1.GetBuffer(6);

				i = 1;
				while( i <= strlen(check) && view_mode == 1 )
				{
					if(check[i-1] < 0x30 || check[i-1] > 0x39)
					{
						GDialog_AccountLogin->m_JuMinCheck = true;
						GDialog_AccountLogin->m_pBBDX_Editor_number1->ClearTextBuffer();
						GDialog_AccountLogin->m_pBBDX_Editor_number1->ClearTexts();					
						GDialog_AccountLogin->SetMessage(_T("���ڸ� ����Ҽ� �ֽ��ϴ�.\n����Ű�� ��������!"));
						view_mode += 3;
						GDialog_AccountLogin->SetViewMode(view_mode);
						TRACE("���ڰ��ƴϴ�.\n");
						break;
					}
					else i++;
				}


				num_temp2 = GDialog_AccountLogin->m_pBBDX_Editor_number2->GetCurEditorText();
				check = num_temp2.GetBuffer(7);

				i = 1;
				while( i <= strlen(check) && view_mode == 1 )
				{
					if(check[i-1] < 0x30 || check[i-1] > 0x39)
					{
						GDialog_AccountLogin->m_JuMinCheck2 = true;
						GDialog_AccountLogin->m_pBBDX_Editor_number2->ClearTextBuffer();
						GDialog_AccountLogin->m_pBBDX_Editor_number2->ClearTexts();					
						GDialog_AccountLogin->SetMessage(_T("���ڸ� ����Ҽ� �ֽ��ϴ�.\n����Ű�� ��������!"));
						view_mode += 3;
						GDialog_AccountLogin->SetViewMode(view_mode);
						TRACE("���ڰ��ƴϴ�.\n");
						break;
					}
					else i++;
				}

				if(!GDialog_AccountLogin->m_JuMinCheck && !GDialog_AccountLogin->m_JuMinCheck2)
				{
					m_New_Account_SocNo = num_temp1 + "-" + num_temp2;
					if(!num_temp1.IsEmpty() && !num_temp2.IsEmpty()) m_New_Account_SocNo = num_temp1 + "-" + num_temp2;
					else m_New_Account_SocNo.Empty();
				}
				else m_New_Account_SocNo.Empty();

				m_New_Account_Address = GDialog_AccountLogin->m_pBBDX_Editor_address->GetCurEditorText();
				m_New_Account_TellNo = GDialog_AccountLogin->m_pBBDX_Editor_phonenumber->GetCurEditorText();
				m_New_Account_Email = GDialog_AccountLogin->m_pBBDX_Editor_email->GetCurEditorText();

				GDialog_AccountLogin->DrawEditorText(DirectXMng.m_pDrawSurface,view_mode, id_flag);
			}
			else if(view_mode == 2)
			{
				LPTSTR	check = NULL;
				unsigned int i = 0;

				m_New_Account_Name = GDialog_AccountLogin->m_pBBDX_Editor_name->GetCurEditorText();

				CString num_temp1,num_temp2;
				num_temp1 = GDialog_AccountLogin->m_pBBDX_Editor_number1->GetCurEditorText();
				check = num_temp1.GetBuffer(6);

				i = 1;
				while( i <= strlen(check) && view_mode == 2 )
				{
					if(check[i-1] < 0x30 || check[i-1] > 0x39)
					{
						GDialog_AccountLogin->m_JuMinCheck = true;
						GDialog_AccountLogin->m_pBBDX_Editor_number1->ClearTextBuffer();
						GDialog_AccountLogin->m_pBBDX_Editor_number1->ClearTexts();					
						GDialog_AccountLogin->SetMessage(_T("���ڸ� ����Ҽ� �ֽ��ϴ�.\n����Ű�� ��������!"));
						view_mode += 3;
						GDialog_AccountLogin->SetViewMode(view_mode);
						TRACE("���ڰ��ƴϴ�.\n");
						break;
					}
					else i++;
				}


				num_temp2 = GDialog_AccountLogin->m_pBBDX_Editor_number2->GetCurEditorText();
				check = num_temp2.GetBuffer(7);

				i = 1;
				while( i <= strlen(check) && view_mode == 2 )
				{
					if(check[i-1] < 0x30 || check[i-1] > 0x39)
					{
						GDialog_AccountLogin->m_JuMinCheck2 = true;
						GDialog_AccountLogin->m_pBBDX_Editor_number2->ClearTextBuffer();
						GDialog_AccountLogin->m_pBBDX_Editor_number2->ClearTexts();					
						GDialog_AccountLogin->SetMessage(_T("���ڸ� ����Ҽ� �ֽ��ϴ�.\n����Ű�� ��������!"));
						view_mode += 3;
						GDialog_AccountLogin->SetViewMode(view_mode);
						TRACE("���ڰ��ƴϴ�.\n");
						break;
					}
					else i++;
				}

				if(!GDialog_AccountLogin->m_JuMinCheck && !GDialog_AccountLogin->m_JuMinCheck2)
				{
					m_New_Account_SocNo = num_temp1 + "-" + num_temp2;
					if(!num_temp1.IsEmpty() && !num_temp2.IsEmpty()) m_New_Account_SocNo = num_temp1 + "-" + num_temp2;
					else m_New_Account_SocNo.Empty();
				}
				else m_New_Account_SocNo.Empty();

				GDialog_AccountLogin->DrawEditorText(DirectXMng.m_pDrawSurface,view_mode, id_flag);
			}
//Ű���� �Է¹��ڿ� ó����..

//�켮. ����Ű�� ���� ó��.
			if(key_return == TRUE)
			{
				key_return = FALSE;

				view_mode = GDialog_AccountLogin->GetViewMode();
				if(view_mode == 1)
				{
		       		if(!m_New_Account_ID.IsEmpty() && !m_New_Account_Passwd.IsEmpty() && !m_New_Account_Passwd2.IsEmpty() &&
						!m_New_Account_Name.IsEmpty() && !m_New_Account_SocNo.IsEmpty() && !m_New_Account_Address.IsEmpty() &&
						!m_New_Account_TellNo.IsEmpty() && !m_New_Account_Email.IsEmpty() && m_bAccountNewOk)
					{
						if(!m_New_Account_Passwd.Compare(m_New_Account_Passwd2))
						{
							unsigned char *name = (unsigned char*)m_New_Account_ID.GetBuffer(m_New_Account_ID.GetLength());
//-----------------------------------------
							bool ret = true;
							int len = strlen((const char*)name);
							WORD str = 0;
							for(int ii=0; ii < len; ii++)
							{
								if( !((name[ii] >= 0x30 && name[ii] <= 0x39) || 
									  (name[ii] >= 0x41 && name[ii] <= 0x5a) || 
									  (name[ii] >= 0x61 && name[ii] <= 0x7a)) )
									{
										if ( name[ii] & 0x80 )                  // �ֻ��� ��Ʈ�� 1�̸� �ѱ۷� �Ǵ�
										{
											str = (name[ii] << 8) | name[ii + 1];
											if((str >= 0xb0a0) && (str <= 0xc8ff))
											{
												if((name[ii + 1] == 0xa0) || (name[ii + 1] == 0xff))
												{
												   GDialog_AccountLogin->SetMessage("����� �� ���� ���̵��Դϴ�.");
												   GDialog_AccountLogin->m_vViewMode += 3;
												   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTextBuffer();
												   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTexts();
												   m_New_Account_ID.Empty();
												   ret = false;
												   break;
												}
											}
											else
											{
											   GDialog_AccountLogin->SetMessage("����� �� ���� ���̵��Դϴ�.");
											   GDialog_AccountLogin->m_vViewMode += 3;
											   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTextBuffer();
											   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTexts();
											   m_New_Account_ID.Empty();
											   ret = false;
											   break;
											}
											ii++;
										}
										else 
										{
										   if(name[ii] == 0x5f) continue;
										   GDialog_AccountLogin->SetMessage("����� �� ���� ���̵��Դϴ�.");
										   GDialog_AccountLogin->m_vViewMode += 3;
										   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTextBuffer();
										   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTexts();
										   m_New_Account_ID.Empty();
										   ret = false;
										   break;
										}
									}
							}
//----------------------------------------
							if(ret) 
							{
								//�ٽ�ȣ�� �ϴ� ���� ����.
								GDialog_AccountLogin->m_vOk = 0;
								m_bLoginOk = false;
								LoginAcount(str_id, str_password);								
							}
						}
						else
						{
							if(m_bAccountNewOk)
							{
								GDialog_AccountLogin->SetMessage(_T("��й�ȣ�� ��й�ȣ\nȮ���� ���� Ʋ���ϴ�.\n���� �ٽ� ���ֽʽÿ�."));
								view_mode += 3;
								GDialog_AccountLogin->SetViewMode(view_mode);
							}
						}
					}
					else
					{
						if(m_bAccountNewOk)
						{
							GDialog_AccountLogin->SetMessage(_T("      ��� ������\n      ä���ּ���."));
							view_mode += 3;
							GDialog_AccountLogin->SetViewMode(view_mode);
						}
					}
				}
				else if(view_mode == 0)
				{
					if(!str_id.IsEmpty( ) && !str_password.IsEmpty() && m_bLoginOk)// ���� �α���..����...
					{
						unsigned char *name = (unsigned char *)str_id.GetBuffer(str_id.GetLength());
						bool ret = true;
						int len = strlen((const char*)name);
						WORD str = 0;
						for(int ii=0; ii < len; ii++)
						{
							if( !((name[ii] >= 0x30 && name[ii] <= 0x39) || 
								  (name[ii] >= 0x41 && name[ii] <= 0x5a) || 
								  (name[ii] >= 0x61 && name[ii] <= 0x7a)) )
								{
									if ( name[ii] & 0x80 )                  // �ֻ��� ��Ʈ�� 1�̸� �ѱ۷� �Ǵ�
									{
										str = (name[ii] << 8) | name[ii + 1];
										if((str >= 0xb0a0) && (str <= 0xc8ff))
										{
											if((name[ii + 1] == 0xa0) || (name[ii + 1] == 0xff))
											{
												GDialog_AccountLogin->SetMessage("����� �� ���� ���̵��Դϴ�.");
												GDialog_AccountLogin->m_vViewMode += 3;
												GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTextBuffer();
												GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTexts();
												m_New_Account_ID.Empty();
												ret = false;
												break;
											}
										}
										else
										{
											GDialog_AccountLogin->SetMessage("����� �� ���� ���̵��Դϴ�.");
											GDialog_AccountLogin->m_vViewMode += 3;
											GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTextBuffer();
											GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTexts();
											m_New_Account_ID.Empty();
											ret = false;
											break;
										}
										ii++;
									}
									else 
									{
									   if(name[ii] == 0x5f) continue;
									   GDialog_AccountLogin->SetMessage("����� �� ���� ���̵��Դϴ�.");
									   GDialog_AccountLogin->m_vViewMode += 3;
									   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTextBuffer();
									   GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTexts();
									   m_New_Account_ID.Empty();
									   ret = false;											
									   break;
									}
								}
						}
						if(ret) 
						{
							//�ٽ�ȣ�� �ϴ� ���� ����.
							GDialog_AccountLogin->m_vOk = 0;
							m_bLoginOk = false;
							LoginAcount(str_id, str_password);								
						}
					}
					else
					{
						if(m_bLoginOk)
						{
							GDialog_AccountLogin->SetMessage(_T("���̵�� �н����带\n��� �־� �ּ���."));
							view_mode += 3;
							GDialog_AccountLogin->SetViewMode(view_mode);
						}
					}
				}
				else if(view_mode == 2)
				{
					if(!m_New_Account_Name.IsEmpty() && !m_New_Account_SocNo.IsEmpty())// �̸��� �ֹι�ȣ üũ.
					{
						//LoginAcount(str_id, str_password);
					}
					else
					{
						GDialog_AccountLogin->SetMessage(_T("�̸��� �ֹε�Ϲ�ȣ\n��� �־��ּ���."));
						view_mode += 3;
						GDialog_AccountLogin->SetViewMode(view_mode);
					}
				}
				else if(view_mode >= 3)
				{
					view_mode -= 3;
					GDialog_AccountLogin->SetViewMode(view_mode);
					m_bAccountNewOk = true;
					if(GDialog_AccountLogin->m_SuccessNewChar == 1) 
						GDialog_AccountLogin->m_SuccessNewChar = 2;
					if(GDialog_AccountLogin->m_SuccessLogin > 1)
					{
						GDialog_AccountLogin->m_SuccessLogin = 0;
						m_bLoginOk = true;
					}

					if(GDialog_AccountLogin->m_pBBDX_Editor_id)
					{
						GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTextBuffer();
						GDialog_AccountLogin->m_pBBDX_Editor_id->ClearTexts();
						if(GDialog_AccountLogin->m_pBBDX_Editor_password)
						{
							GDialog_AccountLogin->m_pBBDX_Editor_password->ClearTextBuffer();
							GDialog_AccountLogin->m_pBBDX_Editor_password->ClearTexts();
						}
					}

					if(GDialog_AccountLogin->m_KorlangMode)
					{
						if(GDialog_AccountLogin->m_pBBDX_Editor_password)
							GDialog_AccountLogin->m_pBBDX_Editor_password->ClearTexts();
						if(GDialog_AccountLogin->m_pBBDX_Editor_password2)
							GDialog_AccountLogin->m_pBBDX_Editor_password2->ClearTexts();
						GDialog_AccountLogin->m_KorlangMode = false;
						GDialog_AccountLogin->m_KorlangMode2 = false;
					}
					if(GDialog_AccountLogin->m_KorlangMode2)
					{
						if(GDialog_AccountLogin->m_pBBDX_Editor_password2)
							GDialog_AccountLogin->m_pBBDX_Editor_password2->ClearTexts();
						GDialog_AccountLogin->m_KorlangMode2 = false;
					}
					if(GDialog_AccountLogin->m_JuMinCheck)
					{
						if(GDialog_AccountLogin->m_pBBDX_Editor_number1)
							GDialog_AccountLogin->m_pBBDX_Editor_number1->ClearTexts();
						if(GDialog_AccountLogin->m_pBBDX_Editor_number2)
							GDialog_AccountLogin->m_pBBDX_Editor_number2->ClearTexts();
						GDialog_AccountLogin->m_JuMinCheck = false;
						GDialog_AccountLogin->m_JuMinCheck2 = false;
					}
					if(GDialog_AccountLogin->m_JuMinCheck2)
					{
						if(GDialog_AccountLogin->m_pBBDX_Editor_number2)
							GDialog_AccountLogin->m_pBBDX_Editor_number2->ClearTexts();
						GDialog_AccountLogin->m_JuMinCheck2 = false;
					}

					id_flag = 0;
				}
			}
//����Ű������ ó�� ��.


			//�ӽ� 
#ifdef _DEBUG
			LogFrameRate(DirectXMng, MapManager.PixelToCell(DirectXMng.GetMouseInfoPtr()->m_posMouse+m_ptMapOffset));
//			DisplayRRStats(DirectXMng);
#endif
			DirectXMng.Flip();
		}
	}//while

//	if(bRet == TRUE) SetFocus();

	if(GDialog_AccountLogin) { delete GDialog_AccountLogin; GDialog_AccountLogin = NULL; GDialog_AccountLogin = NULL; }

	Sleep(500);// ������ �����ϴ°�찡 ����µ� �׽�Ʈ..�� ���ؼ�..
	return bRet;
}

//�켮.
void CChildView::InitChar()
{
	int i = 0;
	int type;
	int index;

	while(m_CharData[i]->userID)
	{
		switch(i)
		{
//�켮.. �����ͷ� �ٲ�... 9�� 9��...
			case 0: Item_Inv->m_bLoginMode = true;
					Item_Inv->m_MyHair = 100 + m_CharData[i]->Hair;
					Item_Inv->m_SkinColor = m_CharData[i]->Skin;
				    Item_Inv->Init(m_CharData[i]->Gender); break;
			case 1: Item_Inv2->m_bLoginMode = true;
					Item_Inv2->m_MyHair = 100 + m_CharData[i]->Hair;
					Item_Inv2->m_SkinColor = m_CharData[i]->Skin;
					Item_Inv2->Init(m_CharData[i]->Gender); break;
			case 2: Item_Inv3->m_bLoginMode = true;
					Item_Inv3->m_MyHair =100 +  m_CharData[i]->Hair;
					Item_Inv3->m_SkinColor = m_CharData[i]->Skin;
					Item_Inv3->Init(m_CharData[i]->Gender); break;
//�켮. 
		}

//�켮.. �����ͷ� �ٲ�.. 9�� 9��...
		for(type = 0; type < 10; type++)
		{
			index = m_CharData[i]->ItemCheck[type];
			switch(i)
			{
				case 0: Item_Inv->m_OK_Flag[type] = 1;
					 Item_Inv->Change_InvItem(type,GetItemPicIndex(index), index);
					 break;
				case 1: Item_Inv2->m_OK_Flag[type] = 1;
					 Item_Inv2->Change_InvItem(type,GetItemPicIndex(index), index);
					 break;
				case 2: Item_Inv3->m_OK_Flag[type] = 1;
					 Item_Inv3->Change_InvItem(type,GetItemPicIndex(index), index);
					 break;
			} //swtich
		} //for

		//�ؽ��� ���ǽ� ����..
		switch(i)
		{
			case 0: Item_Inv->CreateTexture(); Item_Inv->m_timegab = 100;
					Item_Inv->m_bCahrBlend = false;	Item_Inv->m_timegab = 110;
					break;
			case 1: Item_Inv2->CreateTexture(); Item_Inv2->m_timegab = 150;
					Item_Inv2->m_bCahrBlend = true; Item_Inv2->m_timegab = 150;
				    break;
			case 2: Item_Inv3->CreateTexture(); Item_Inv3->m_timegab = 150;
					Item_Inv3->m_bCahrBlend = true; Item_Inv3->m_timegab = 150;
				    break;
		}
//�켮.
		i++;
		if(i == 3) break;
	}// while
//�켮.
}

void CChildView::ReStart()
{
	m_ptMapOffset.x = 0;
	m_ptMapOffset.y = 0;

	m_Mouse_In = 0;// ���� ���ȿ� ����..1

	m_iMyId = -1;//Invalid State

	m_test_Flag = 1;
	m_Login_Char = 0;// �����ϴ� ĳ����..���..

	m_Chattype = 1;// �븻 ä��...

	m_CurMemoChatId = _T("");
	g_pFocusDialog = NULL;

	m_bMakeChar = false;
	m_bMakeFail = false;
	m_bMakeProcess = false;
	m_CharNum = 0; //ĳ���� ����.
	g_pFocusWnd = NULL;

	m_bAccountNewOk = true;
	m_bLoginOk = true;

//�켮.. �����ͷ� �ٲ�.. 9�� 9��..
	SAFE_DELETE(Item_Inv);
	SAFE_DELETE(Item_Inv2);
	SAFE_DELETE(Item_Inv3);
	Item_Inv = new CItem_Inv;
	Item_Inv2 = new CItem_Inv;
	Item_Inv3 = new CItem_Inv;

	m_pChatOuter->ClearString();
	Dialog_MemoCtrl.DeleteContents();
	Dialog_Main.SetBattleMode(NORMAL_MODE);

	if(CWnd::GetFocus() == m_pBBDX_Editor)
	{
		m_pBBDX_Editor->ClearTexts();
		SetFocus();
	}
	CChildView::MapObj.Release();
	CChildView::MapShadowObj.Release();
	CChildView::MapHouseIn.Release();
	CChildView::MapHouseOut.Release();
	for(int i = 0; i < MAX_MAP_OBJ_REG; i++) CChildView::MapAniObjs[i].SprRelease();
	for(i = 0; i < MAX_MAP_OBJ_REG; i++) CChildView::MapShadowAniObjs[i].SprRelease();
	for( i = 0; i < MAX_MAP_OBJ_REG; i++) CChildView::MapAniHouseIn[i].SprRelease();
	for(i = 0; i < MAX_MAP_OBJ_REG; i++) CChildView::MapAniHouseOut[i].SprRelease();

	CChildView::UserManager.RemoveAllData();
	Item_Field.RemoveAll();

	g_vOldMapNumber = g_vMapNumber = -1;
	if(DirectXMng.m_pDirectSound)
	{
		if(g_mainSoundIndex != -1) DirectXMng.m_pDirectSound->MusicStop(g_vCurMusicNumber, g_mainSoundIndex, FALSE);
		g_vCurMusicNumber = 1;
		char *value;
		if(g_MusicName.Lookup(g_vCurMusicNumber, value))
		{
			g_mainSoundIndex = CChildView::DirectXMng.m_pDirectSound->MusicPlay(value, g_vCurMusicNumber, TRUE);
		}
	}
	//Ŀ�������� �ٽû���...
	SAFE_DELETE(DirectXMng.m_pDxCursor);
	DirectXMng.m_pDxCursor = new CDxCursor();
	DirectXMng.m_pDxCursor->InitCursor();
	DirectXMng.m_pDxCursor->SetCursorIndex(0);

	m_RestartGame = true;
	g_vMapNumber = 0;

	SocketMng.m_szLoginId.Empty();
	SocketMng.m_szLoginId1.Empty();
	SocketMng.m_szLoginId2.Empty();
	SocketMng.m_szLoginId3.Empty();

	GameLogin();	

	if(DirectXMng.m_pDirectSound)
	{
		if(g_mainSoundIndex != -1) DirectXMng.m_pDirectSound->MusicStop(g_vCurMusicNumber, g_mainSoundIndex, TRUE);
		g_mainSoundIndex = -1;
	}
}

void CChildView::GameLogin()
{
	BOOL bRet = TRUE, bSuccess = FALSE;
	BOOL key_return = FALSE, key_esc = FALSE;
	int key_tab = 0;
	MSG msg;

//�켮
/*	if(m_CharData[0]) {	delete m_CharData[0]; m_CharData[0] = NULL; }
	else { m_CharData[0] = new CharData;}
	if(m_CharData[1]) { delete m_CharData[1]; 	m_CharData[1] =	NULL; }
	else { m_CharData[1] = new CharData;}
	if(m_CharData[2]) { delete m_CharData[2]; 	m_CharData[2] =	NULL; }
	else { m_CharData[2] = new CharData;}
*/
	m_CharData[0] = new CharData;
	m_CharData[1] = new CharData;
	m_CharData[2] = new CharData;

	CDialog_Login *Dialog_Login = new CDialog_Login(this);

//	GDialog_Login = Dialog_Login;

	Dialog_Login->Create(DirectXMng.m_pDD, "s_login.lib", 0);

//	Dialog_Login.InitData(DirectXMng.m_pDD, this);

//�켮... �����ͷ� �ٲ�.. 9�� 9��...
	Dialog_Login->SetCharacter(Item_Inv, Item_Inv2, Item_Inv3); // �α��� ���̾�α׿� ĳ���� ������ ����
//�켮.

	while(bSuccess == FALSE) 
	{
		if(GetSafeHwnd() == NULL)
		{
			AfxPostQuitMessage(0);
			SAFE_DELETE(Dialog_Login); //�켮.
			bRet = FALSE;
		}
		if (bRet == TRUE && ::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			switch(msg.message)
			{
			case WM_QUIT:
				AfxPostQuitMessage(0);
				SAFE_DELETE(Dialog_Login); //�켮.
				bRet = FALSE;
				break;
			case WM_KEYDOWN:
				if(msg.wParam == VK_RETURN)
				{
					key_return = TRUE;
					continue;
				}
				else if(msg.wParam == VK_TAB)
				{
					if(GetKeyState(VK_SHIFT)&0x8000)
					{
						key_tab = -1;
					}
					else
					{
						key_tab = 1;
					}
					continue;
				}
				else if(msg.wParam == VK_ESCAPE)
				{
					key_esc = TRUE;
					continue;
				}
				break;
			}
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			if(PacketParser.GetSessionLoginStatus() == FALSE)
			{
				SocketMng.SendAcountLogin();
				bSuccess = TRUE;
			}
			else
			{
				AfxPostQuitMessage(0);
				SAFE_DELETE(Dialog_Login); 
				bSuccess = TRUE;
			}

		}
	}

//�켮
	bSuccess = FALSE;
	while(bSuccess == FALSE && bRet == TRUE) 
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			switch(msg.message)
			{
			case WM_QUIT:
				AfxPostQuitMessage(0);
				SAFE_DELETE(Dialog_Login); //�켮.
				bRet = FALSE;
				break;
			case WM_KEYDOWN:
				if(msg.wParam == VK_RETURN)
				{
					key_return = TRUE;
					continue;
				}
				else if(msg.wParam == VK_TAB)
				{
					if(GetKeyState(VK_SHIFT)&0x8000)
					{
						key_tab = -1;
					}
					else
					{
						key_tab = 1;
					}
					continue;
				}
				else if(msg.wParam == VK_ESCAPE)
				{
					key_esc = TRUE;
					continue;
				}
				break;
			}
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			LoginMouseProcess(Dialog_Login);
			Dialog_Login->Draw(DirectXMng.m_pDrawSurface);
			if(Dialog_Login->m_vViewMode == 0)
			{
				switch(Dialog_Login->m_vOk)
				{
				case 3:
				case 0: AfxPostQuitMessage(0);
					    if(Dialog_Login) { delete Dialog_Login; Dialog_Login = NULL; }
					    break;

				case 1: //��ĳ���� �����..
					if(SocketMng.m_szLoginId1.IsEmpty() || SocketMng.m_szLoginId2.IsEmpty() || SocketMng.m_szLoginId3.IsEmpty())
					{
						SAFE_DELETE(Dialog_Login);
						Dialog_Login = new CDialog_Login(this);
//						GDialog_Login = Dialog_Login;
						Dialog_Login->SetMode(1);
						Dialog_Login->Create(DirectXMng.m_pDD, "s_NewCha.lib", 0);
						Dialog_Login->InitNewChar();

						//�켮.. ��ĳ���� �����... 9�� 9��....
						SAFE_DELETE(Dialog_Login->m_pNewCharItem01);
						SAFE_DELETE(Dialog_Login->m_pNewCharItem02);
						SAFE_DELETE(Dialog_Login->m_pNewCharItem03);
						SAFE_DELETE(Dialog_Login->m_pNewCharItemWoman01);
						SAFE_DELETE(Dialog_Login->m_pNewCharItemWoman02);
						SAFE_DELETE(Dialog_Login->m_pNewCharItemWoman03);
						Dialog_Login->m_pNewCharItem01 = new CItem_Inv; //����...
						Dialog_Login->m_pNewCharItem02 = new CItem_Inv; //����...
						Dialog_Login->m_pNewCharItem03 = new CItem_Inv; //����...
						Dialog_Login->m_pNewCharItemWoman01 = new CItem_Inv;//����..
						Dialog_Login->m_pNewCharItemWoman02 = new CItem_Inv;//����..
						Dialog_Login->m_pNewCharItemWoman03 = new CItem_Inv;//����..

						Dialog_Login->m_pNewCharItem01->m_bLoginMode = true;
						Dialog_Login->m_pNewCharItem02->m_bLoginMode = true;
						Dialog_Login->m_pNewCharItem03->m_bLoginMode = true;
						Dialog_Login->m_pNewCharItemWoman01->m_bLoginMode = true;
						Dialog_Login->m_pNewCharItemWoman02->m_bLoginMode = true;
						Dialog_Login->m_pNewCharItemWoman03->m_bLoginMode = true;

						Dialog_Login->m_pNewCharItem01->m_alpha = 32;
						Dialog_Login->m_pNewCharItem02->m_alpha = 0;
						Dialog_Login->m_pNewCharItem03->m_alpha = 0;
						Dialog_Login->m_pNewCharItemWoman01->m_alpha = 0;
						Dialog_Login->m_pNewCharItemWoman02->m_alpha = 0;
						Dialog_Login->m_pNewCharItemWoman03->m_alpha = 0;

						Dialog_Login->m_pNewCharItem01->m_alphastate = false;
						Dialog_Login->m_pNewCharItem02->m_alphastate = true;
						Dialog_Login->m_pNewCharItem03->m_alphastate = true;
						Dialog_Login->m_pNewCharItemWoman01->m_alphastate = true;
						Dialog_Login->m_pNewCharItemWoman02->m_alphastate = true;
						Dialog_Login->m_pNewCharItemWoman03->m_alphastate = true;

						Dialog_Login->m_pNewCharItem01->m_SkinColor = 0;
						Dialog_Login->m_pNewCharItem01->Init(0);//���ڷ� �ʱ�ȭ...
						Dialog_Login->m_pNewCharItem01->Change_InvItem(0,101);//�Ӹ� �ʱ�ȭ...
						Dialog_Login->m_pNewCharItem02->m_SkinColor = 1;
						Dialog_Login->m_pNewCharItem02->Init(0);//���ڷ� �ʱ�ȭ...
						Dialog_Login->m_pNewCharItem02->Change_InvItem(0,101);//�Ӹ� �ʱ�ȭ...
						Dialog_Login->m_pNewCharItem03->m_SkinColor = 2;
						Dialog_Login->m_pNewCharItem03->Init(0);//���ڷ� �ʱ�ȭ...
						Dialog_Login->m_pNewCharItem03->Change_InvItem(0,101);//�Ӹ� �ʱ�ȭ...
						Dialog_Login->m_pNewCharItemWoman01->m_SkinColor = 0;
						Dialog_Login->m_pNewCharItemWoman01->Init(1);//���ڷ� �ʱ�ȭ...
						Dialog_Login->m_pNewCharItemWoman01->Change_InvItem(0,101);//�Ӹ� �ʱ�ȭ...
						Dialog_Login->m_pNewCharItemWoman02->m_SkinColor = 1;
						Dialog_Login->m_pNewCharItemWoman02->Init(1);//���ڷ� �ʱ�ȭ...
						Dialog_Login->m_pNewCharItemWoman02->Change_InvItem(0,101);//�Ӹ� �ʱ�ȭ...
						Dialog_Login->m_pNewCharItemWoman03->m_SkinColor = 2;
						Dialog_Login->m_pNewCharItemWoman03->Init(1);//���ڷ� �ʱ�ȭ...
						Dialog_Login->m_pNewCharItemWoman03->Change_InvItem(0,101);//�Ӹ� �ʱ�ȭ...

						Dialog_Login->m_pNewCharItem01->CreateTexture();
						Dialog_Login->m_pNewCharItem02->CreateTexture();
						Dialog_Login->m_pNewCharItem03->CreateTexture();
						Dialog_Login->m_pNewCharItemWoman01->CreateTexture();
						Dialog_Login->m_pNewCharItemWoman02->CreateTexture();
						Dialog_Login->m_pNewCharItemWoman03->CreateTexture();
						//�켮.. �����ͷ� �ٲ�... 9�� 9��....
//						Dialog_Login->SetCharacter(Item_Inv, Item_Inv2, Item_Inv3); // �α��� ���̾�α׿� ĳ���� ������ ����
					}
					break;

				case 2:
					  //�켮..
					  switch(Dialog_Login->m_ViewCharNum)
					  {
						case 0: CChildView::SocketMng.m_szLoginId = CChildView::SocketMng.m_szLoginId1;
								break;
						case 2: CChildView::SocketMng.m_szLoginId = CChildView::SocketMng.m_szLoginId3;
							break;
						case 1: CChildView::SocketMng.m_szLoginId = CChildView::SocketMng.m_szLoginId2;
							break;
					  } // ĳ���Ͱ� 3��.

					  if(!SocketMng.m_szLoginId.IsEmpty())
					  {
					 	 LogIn();	
						 bSuccess = TRUE;
					  }
					  Dialog_Login->m_vOk = -1;
					  break;

				case 4: //�����...
					  //�켮..
					  switch(Dialog_Login->m_ViewCharNum)
					  {
						case 0: CChildView::SocketMng.m_szLoginId = CChildView::SocketMng.m_szLoginId1;
								break;
						case 2: CChildView::SocketMng.m_szLoginId = CChildView::SocketMng.m_szLoginId3;
							break;
						case 1: CChildView::SocketMng.m_szLoginId = CChildView::SocketMng.m_szLoginId2;
							break;
					  } // ĳ���Ͱ� 3��.

					  if(!SocketMng.m_szLoginId.IsEmpty())
					  {
						  if(Dialog_Login->m_bDelCheck)
						  {
							 Dialog_Login->m_bDelCheck = FALSE;
							 SendDelHero(SocketMng.m_szLoginId);							 
						  }
						  else
						  {
							 Dialog_Login->m_vViewMode += 3;
							 Dialog_Login->SetMessage(_T("���� �����Ͻðڽ��ϱ�?"));
						  }
					  }
					  Dialog_Login->m_vOk = -1;
					
					break;
/*				case 6:
					AfxPostQuitMessage(0);
					break;
*/				}
			}
			else if(Dialog_Login->m_vViewMode == 1)
			{
				switch(Dialog_Login->m_vOk)
				{
					case 0: //Ȯ��..
						{
							Dialog_Login->m_pName->GetText();
							CString str_id =  Dialog_Login->m_pName->GetCurEditorText();
							if(!str_id.IsEmpty())
							{
								unsigned char *name = (unsigned char*)Dialog_Login->m_pName->GetCurEditorText();
								bool ret = true;
								int len = strlen((const char*)name);
								WORD str = 0;
								for(int ii=0; ii < len; ii++)
								{
									if( !((name[ii] >= 0x30 && name[ii] <= 0x39) || 
										  (name[ii] >= 0x41 && name[ii] <= 0x5a) || 
										  (name[ii] >= 0x61 && name[ii] <= 0x7a)) )
										{
											if ( name[ii] & 0x80 )                  // �ֻ��� ��Ʈ�� 1�̸� �ѱ۷� �Ǵ�
											{
												str = (name[ii] << 8) | name[ii + 1];
												if((str >= 0xb0a0) && (str <= 0xc8ff))
												{
													if((name[ii + 1] == 0xa0) || (name[ii + 1] == 0xff))
													{
														Dialog_Login->SetMessage("����� �� ���� ���̵��Դϴ�.");
														Dialog_Login->m_vViewMode += 3;
														Dialog_Login->m_pName->ClearTexts();
														ret = false;
														break;
													}
												}
												else
												{
													Dialog_Login->SetMessage("����� �� ���� ���̵��Դϴ�.");
													Dialog_Login->m_vViewMode += 3;
													Dialog_Login->m_pName->ClearTexts();
													ret = false;
													break;
												}
												ii++;
											}
											else 
											{
											   if(name[ii] == 0x5f) continue;
											   Dialog_Login->SetMessage("����� �� ���� ���̵��Դϴ�.");
											   Dialog_Login->m_vViewMode += 3;
											   Dialog_Login->m_pName->ClearTexts();
											   ret = false;
											   break;
											}
										}
								}
								if(ret)
								{
									if(Dialog_Login->m_Points != 0)
									{
									   Dialog_Login->SetMessage("Points �й谡 ������ �ʾҽ��ϴ�.");
									   Dialog_Login->m_vViewMode += 3;
									}
									// ���������� ĳ���͸� �����...
									if(Dialog_Login->m_vViewMode < 3)
									{
										SendNewHero(str_id, Dialog_Login);
										m_bMakeProcess = true;
									}
								}
							}
							else
							{
								 Dialog_Login->m_vViewMode += 3;
								 Dialog_Login->SetMessage(_T("���̵� �Է��ϼ���."));
							}
							Dialog_Login->m_vOk = -1;
						}
						break;
					case 1: //���.
						   SAFE_DELETE(Dialog_Login);
						   Dialog_Login = new CDialog_Login(this);
						   Dialog_Login->SetMode(0);
						   Dialog_Login->Create(DirectXMng.m_pDD, "s_login.lib", 0);

						   //�켮.. �����ͷ� �ٲ�... 9�� 9��....
						   Dialog_Login->SetCharacter(Item_Inv, Item_Inv2, Item_Inv3); // �α��� ���̾�α׿� ĳ���� ������ ����
	   					   break;
					case 2: //����..
						   //�켮.. ��ĳ���� �����... 9�� 9��....
						   //SAFE_DELETE(Dialog_Login->m_pNewCharItem);
						   //Dialog_Login->m_pNewCharItem = new CItem_Inv;
						   //Dialog_Login->m_pNewCharItem->Init(0);//���ڷ� �ʱ�ȭ...
   						   Dialog_Login->m_vOk = -1;
						   break;
					case 3: //����..
						   //�켮.. ��ĳ���� �����... 9�� 9��....
						   //SAFE_DELETE(Dialog_Login->m_pNewCharItem);
						   //Dialog_Login->m_pNewCharItem = new CItem_Inv;
						   //Dialog_Login->m_pNewCharItem->Init(1);//���ڷ� �ʱ�ȭ...
   						   Dialog_Login->m_vOk = -1;
						   break;
					case  4: Dialog_Login->SetMakeCharData(4); // false ����. true ����.
   						   Dialog_Login->m_vOk = -1;
						   break;
					case  5: Dialog_Login->SetMakeCharData(5); // false ����. true ����.
   						   Dialog_Login->m_vOk = -1;
						   break;
					case  6: Dialog_Login->SetMakeCharData(6); // false ����. true ����.
   						   Dialog_Login->m_vOk = -1;
						   break;
					case  7: Dialog_Login->SetMakeCharData(7); // false ����. true ����.
   						   Dialog_Login->m_vOk = -1;
						   break;
					case  8: Dialog_Login->SetMakeCharData(8); // false ����. true ����.
   						   Dialog_Login->m_vOk = -1;
						   break;
					case  9: Dialog_Login->SetMakeCharData(9); // false ����. true ����.
   						   Dialog_Login->m_vOk = -1;
						   break;
					case  10: Dialog_Login->SetMakeCharData(10); // false ����. true ����.
   						   Dialog_Login->m_vOk = -1;
						   break;
					case  11: Dialog_Login->SetMakeCharData(11); // false ����. true ����.
   						   Dialog_Login->m_vOk = -1;
						   break;
					case  12: Dialog_Login->SetMakeCharData(12); // false ����. true ����.
   						   Dialog_Login->m_vOk = -1;
						   break;
					case  13: Dialog_Login->SetMakeCharData(13); // false ����. true ����.
   						   Dialog_Login->m_vOk = -1;
						   break;
					case  14: Dialog_Login->SetMakeCharData(14); // false ����. true ����.
   						   Dialog_Login->m_vOk = -1;
						   break;
					case  15: Dialog_Login->SetMakeCharData(15); // false ����. true ����.
   						   Dialog_Login->m_vOk = -1;
						   break;
				}
			}

//			Dialog_Login->m_vOk = -1;
			if(key_return == TRUE)
			{
				key_return = FALSE;

				//�켮..
				switch(Dialog_Login->m_ViewCharNum)
				{
				case 0: CChildView::SocketMng.m_szLoginId = CChildView::SocketMng.m_szLoginId1;
						break;
				case 2: CChildView::SocketMng.m_szLoginId = CChildView::SocketMng.m_szLoginId3;
					break;
				case 1: CChildView::SocketMng.m_szLoginId = CChildView::SocketMng.m_szLoginId2;
					break;
				} // ĳ���Ͱ� 3��.

				if(Dialog_Login->m_vViewMode == 0)
				{
					if(!SocketMng.m_szLoginId.IsEmpty())
					{
						LogIn();
						bSuccess = TRUE;
					}
				}
			}

//��Űó��.
			if(key_tab == 1)
			{
				key_tab = 0;
				if(Dialog_Login->m_vViewMode == 0)
				{
					Dialog_Login->ChangeCharacter(1);
					Dialog_Login->SetCharNum(); //ĳ������ ��ġ�̵�..������..
				}
			}
			else if(key_tab == -1)
			{
				key_tab = 0;
				if(Dialog_Login->m_vViewMode == 0)
				{
					Dialog_Login->ChangeCharacter(-1);
					Dialog_Login->SetCharNum(); //ĳ������ ��ġ�̵�..����...
				}
			}
//��Űó�� ��.

	//�켮 ��ĳ���� �����.....
	if(m_bMakeChar) //��ĳ���Ϳ� ���� ������ �޾�����...
	{
	   SAFE_DELETE(Dialog_Login);
	   Dialog_Login = new CDialog_Login(this);
	   Dialog_Login->SetMode(0);
	   Dialog_Login->Create(DirectXMng.m_pDD, "s_login.lib", 0);

	   //�켮.. �����ͷ� �ٲ�... 9�� 9��....
	   Dialog_Login->SetCharacter(Item_Inv, Item_Inv2, Item_Inv3); // �α��� ���̾�α׿� ĳ���� ������ ����

       m_bMakeChar = false;
	   m_bMakeProcess = false;
	}
	if(m_bMakeFail)
	{
		m_bMakeFail = false;
		Dialog_Login->m_vViewMode += 3;
		Dialog_Login->SetMessage(_T("�̹� ��ϵ� ���̵��Դϴ�."));
	}
	//�켮.

#ifdef _DEBUG
			LogFrameRate(DirectXMng, MapManager.PixelToCell(DirectXMng.GetMouseInfoPtr()->m_posMouse+m_ptMapOffset));
//			DisplayRRStats(DirectXMng);
#endif
			DirectXMng.Flip();
		}
	}

	if(bSuccess == TRUE)
	{
		SetFocus();
		//�켮

		//����ڰ� ������ ĳ���͸� �����Ѵ�.
		//���ӿ��� ���� ĳ���ʹ� �ϳ��ϱ�.....
//�켮.. �����ͷ� �ٲ�... 9�� 9��...
		CItem_Inv *Inv_temp = NULL;

		switch(Dialog_Login->m_ViewCharNum)
		{
			case 1: Inv_temp = Item_Inv;
				    Item_Inv = Item_Inv2;
					Item_Inv2 = Inv_temp;
					break;
			case 2: Inv_temp = Item_Inv;
				    Item_Inv = Item_Inv3;
					Item_Inv3 = Inv_temp;
					break;
		} // ĳ���Ͱ� 3��.
		Inv_temp = NULL;
//�켮.

		if(Dialog_Login) { delete Dialog_Login; Dialog_Login = NULL; }

		if(m_CharData[0]) { delete m_CharData[0]; 	m_CharData[0] =	NULL; }
		if(m_CharData[1]) { delete m_CharData[1]; 	m_CharData[1] =	NULL; }
		if(m_CharData[2]) { delete m_CharData[2]; 	m_CharData[2] =	NULL; }

		//9�� 24��..
		if(Item_Inv2) { delete Item_Inv2; Item_Inv2 = NULL; }
		if(Item_Inv3) { delete Item_Inv3; Item_Inv3 = NULL; }

		Item_Inv->DestoryTexSurface();
	}
//	DirectXMng.m_pDrawSurface = new CDDSurface;
//	if (!DirectXMng.m_pDrawSurface->Create(DirectXMng.m_pDD, DirectXMng.m_sizeScreen.cx, DirectXMng.m_sizeScreen.cy, FALSE))	//���� �޸𸮸� ������� �ʴ� surface����(�׸����)
//	{
//		TRACE("DRAWSURFACE ���� ����\n");
//		return;
//	}

//�켮.
}

void CChildView::LoginCharterView()
{
	if(GetAsyncKeyState(VK_TAB) & 0x8000)
	{
//�켮.
//		Dialog_Login.ChangeCharacter(1);
	}

//	Dialog_Login.LoginDraw(DirectXMng.m_pDrawSurface);
}

void CChildView::LoginView()
{
	if(GetAsyncKeyState(VK_ESCAPE) & 0x8000)
	{
		Sleep(300);
		if(!SocketMng.m_szLoginId.IsEmpty()) LogIn();
	}

	if(GetAsyncKeyState(VK_F1) & 0x8000)
		m_test_Flag = 1;
	else if(GetAsyncKeyState(VK_F2) & 0x8000)
	{
		m_test_Flag = 2;
//		SendNewHero(m_Login_Char);
//		Sleep(300);// �ӽ�..
	}
	else if(GetAsyncKeyState(VK_F3) & 0x8000)
	{
		// �ӽ�...ĳ���͸� ����� �޽����� ������..����..
		SendDelHero(m_Login_Char);
	}

	if(m_test_Flag == 1)
	{
		LoginCharterView();
	}
	else if(m_test_Flag == 2)
		NewCharter();
	else if(m_test_Flag == 13) //�α�����..
		if(m_LoadinView) m_LoadinView->Draw(DirectXMng.m_pDrawSurface);

	DirectXMng.Flip();
}



BOOL CChildView::SendNewHero(CString str_id, CDialog_Login *Dialog_Login)
{
	BYTE buf[30];
	int offset = 0;
	CPacketParser::SetByte(buf, offset, PKT_NEW_HERO); //������ ��û
	//GetLength();//��Ʈ�� ũ�� 
	//LPCTSTR();//string����..
//	SocketMng.m_szLoginId1 = name[0];
//	SocketMng.m_szLoginId2 = name[1];
//	SocketMng.m_szLoginId3 = name[2];

	CString newname = str_id;// = _T("newsoma");
	// �Է� �޾Ƽ� �־� ��� �Ѵ�.
/*	if(HeroNumber == 0)
		newname = _T("soma0");
	else if(HeroNumber == 1)
		newname = _T("soma1");
	else if(HeroNumber == 2)
		newname = _T("soma2");
*/
	short hair_index;
	int len = newname.GetLength();	
	if(len <= 0) 
		return FALSE;// �̸��� ����������..
	LPTSTR id = newname.GetBuffer(len);

	CPacketParser::SetByte(buf, offset, (BYTE)len);
	CPacketParser::SetString(buf, offset, (PBYTE)id, len); 
//�켮
	CPacketParser::SetShort(buf, offset,Dialog_Login->m_Strength);
	CPacketParser::SetShort(buf, offset,Dialog_Login->m_Dexterity);
	CPacketParser::SetShort(buf, offset,Dialog_Login->m_Inteligence);
	CPacketParser::SetShort(buf, offset,Dialog_Login->m_Charisma);
	CPacketParser::SetShort(buf, offset,Dialog_Login->m_Wisdom);
	CPacketParser::SetShort(buf, offset,Dialog_Login->m_Constitution);
	// ������ Ŭ���̾�Ʈ�� �������� �ٸ���...
	if(Dialog_Login->m_bSex) CPacketParser::SetShort(buf, offset,0); //����..
	else CPacketParser::SetShort(buf, offset,1); //����...
//�켮.

	hair_index = Dialog_Login->m_HairStyleIndex * 10 + Dialog_Login->m_HairColorIndex;
	CPacketParser::SetShort(buf, offset,hair_index);
	CPacketParser::SetShort(buf, offset,Dialog_Login->m_SkinColorChange);

	SocketMng.Send(offset, buf);
	newname.ReleaseBuffer();
	return TRUE;
}

void CChildView::SendDelHero(CString str_id)
{
	BYTE buf[20];
	int offset = 0;
	CPacketParser::SetByte(buf, offset, PKT_DEL_HERO); //������ ��û

	str_id.MakeLower();
	int len = str_id.GetLength();

	CPacketParser::SetByte(buf, offset, (BYTE)len);
	CPacketParser::SetString(buf, offset, (PBYTE)(LPCTSTR)str_id, len); 
	SocketMng.Send(offset, buf);
}

void CChildView::NewHeroProcess(PBYTE bypData)
{
	int offset=0;
	int type, index;

	switch(bypData[offset++])
	{
	case 0x01: //����
		{
			int name_len;
			CString name;
			CString str;
			short   gender;
//			BYTE count = GetByte(bypData, offset);
			for(int i=0;i<3;i++)
			{
				if(m_CharData[i]->userID == NULL)
				{
					name_len = CPacketParser::GetByte(bypData, offset);

					m_CharData[i]->IdSize = name_len; //�켮.
					m_CharData[i]->userID = new char[name_len + 1]; //�켮.


					LPSTR lpStr = str.GetBufferSetLength((int)name_len);
					CPacketParser::GetString(bypData, offset, (PBYTE)lpStr, (int)name_len);
					str.ReleaseBuffer();
					name = _T(lpStr);
					name.MakeUpper();

					strcpy(m_CharData[i]->userID, name); //�켮.	

					//�켮
					m_CharData[i]->Class = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->Level = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->Str = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->Dex = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->Inteli = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->Cha = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->Wis = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->Con = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->Hp = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->MaxHp = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->Mp = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->MaxMp = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->Stm = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->MaxStm = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->Age = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->Moral = CPacketParser::GetShort(bypData,offset);
					//������ Ŭ���̾�Ʈ�� �������� �ٸ���...
					gender = CPacketParser::GetShort(bypData,offset);
					if(gender) m_CharData[i]->Gender = 0; //����.
					else m_CharData[i]->Gender = 1; //����.

					m_CharData[i]->Hair = CPacketParser::GetShort(bypData,offset);
					m_CharData[i]->Skin = CPacketParser::GetShort(bypData,offset);
					name_len = CPacketParser::GetByte(bypData, offset);
					if(name_len > 0)
					{
						CPacketParser::GetString(bypData, offset, (PBYTE)m_CharData[i]->Group.GetBuffer(name_len), name_len);
						m_CharData[i]->Group.ReleaseBuffer();
					}
					else m_CharData[i]->Group.Empty();
					m_CharData[i]->Fame = CPacketParser::GetShort(bypData,offset);

					m_CharData[i]->SwordExp = CPacketParser::GetInt(bypData,offset);
					m_CharData[i]->SpearExp = CPacketParser::GetInt(bypData,offset);
					m_CharData[i]->BowExp = CPacketParser::GetInt(bypData,offset);
					m_CharData[i]->AxeExp = CPacketParser::GetInt(bypData,offset);
					m_CharData[i]->KnuckleExp = CPacketParser::GetInt(bypData,offset);
					m_CharData[i]->StaffExp = CPacketParser::GetInt(bypData,offset);

					m_CharData[i]->WeaponMakeExp = CPacketParser::GetInt(bypData,offset);
					m_CharData[i]->ArmorMakeExp = CPacketParser::GetInt(bypData,offset);
					m_CharData[i]->AccMakeExp = CPacketParser::GetInt(bypData,offset);
					m_CharData[i]->PotionMakeExp = CPacketParser::GetInt(bypData,offset);
					m_CharData[i]->CookingExp = CPacketParser::GetInt(bypData,offset);

					for(int j=0; j < 10; j++)
					{
						m_CharData[i]->ItemCheck[j] = CPacketParser::GetShort(bypData,offset);
					}

					//�켮.
					if(i == 0) SocketMng.m_szLoginId1 = name;
					else if(i == 1) SocketMng.m_szLoginId2 = name;
					else if(i == 2) SocketMng.m_szLoginId3 = name;


					switch(i)
					{
						//�켮.. �����ͷ� �ٲ�... 9�� 9��...
						case 0: SAFE_DELETE(Item_Inv);
							    Item_Inv = new CItem_Inv;
								Item_Inv->m_MyHair = 100 + m_CharData[i]->Hair;
								Item_Inv->m_SkinColor = m_CharData[i]->Skin;
							    Item_Inv->Init(m_CharData[i]->Gender); 
								Item_Inv3->m_bCahrBlend = true;	
								Item_Inv2->m_bCahrBlend = true;
								Item_Inv->m_bCahrBlend = false;
								Item_Inv->m_timegab = 110;
								break;
						case 1: SAFE_DELETE(Item_Inv2);
							    Item_Inv2 = new CItem_Inv;
								Item_Inv2->m_MyHair = 100 + m_CharData[i]->Hair;
								Item_Inv2->m_SkinColor = m_CharData[i]->Skin;
								Item_Inv2->Init(m_CharData[i]->Gender); 
								Item_Inv3->m_bCahrBlend = true;	
								Item_Inv2->m_bCahrBlend = true;
								Item_Inv->m_bCahrBlend = false;
								Item_Inv2->m_timegab = 150;
							    break;
						case 2: SAFE_DELETE(Item_Inv3);
							    Item_Inv3 = new CItem_Inv;
								Item_Inv3->m_MyHair = 100 + m_CharData[i]->Hair;
								Item_Inv3->m_SkinColor = m_CharData[i]->Skin;
								Item_Inv3->Init(m_CharData[i]->Gender); 
								Item_Inv3->m_bCahrBlend = true;
								Item_Inv2->m_bCahrBlend = true;
								Item_Inv->m_bCahrBlend = false;
								Item_Inv3->m_timegab = 150;
							    break;
						//�켮. 
					}

					//�켮.. �����ͷ� �ٲ�.. 9�� 9��...
					for(type = 0; type < 10; type++)
					{
						index = m_CharData[i]->ItemCheck[type];
						switch(i)
						{
							case 0: Item_Inv->m_OK_Flag[type] = 1;								 
								 Item_Inv->Change_InvItem(type,GetItemPicIndex(index), index);
								 break;
							case 1: Item_Inv2->m_OK_Flag[type] = 1;
								 Item_Inv2->Change_InvItem(type,GetItemPicIndex(index), index);
								 break;
							case 2: Item_Inv3->m_OK_Flag[type] = 1;
								 Item_Inv3->Change_InvItem(type,GetItemPicIndex(index), index);
								 break;
						} //swtich
					} //for

					switch(i)
					{
						case 0: Item_Inv->CreateTexture();	 break;
						case 1: Item_Inv2->CreateTexture(); break;
						case 2: Item_Inv3->CreateTexture(); break;
					} //swtich

					m_CharNum++;
					m_bMakeChar = true; //ĳ���� ������ �ϼ��Ǿ���...
					break;
				} // if
			} //for
		} 
		break;
	case 0x02: //����
		m_bMakeChar = false;
		m_bMakeFail = true;
		break;
	}
}

void CChildView::DelHeroProcess(PBYTE bypData)
{
	int offset=0;
	int name_len;
	CString name;
	CString str;
	BYTE count = CPacketParser::GetByte(bypData, offset);
	if(count == 0x02)
		return;// ����..

	name_len = CPacketParser::GetByte(bypData, offset);
	LPSTR lpStr = str.GetBufferSetLength((int)name_len);
	CPacketParser::GetString(bypData, offset, (PBYTE)lpStr, (int)name_len);
	str.ReleaseBuffer();
	name = _T(lpStr);
	name.MakeUpper();

	SocketMng.m_szLoginId.Empty();
	//�켮
	if(SocketMng.m_szLoginId1 == name)
	{
		SocketMng.m_szLoginId1.Empty();
		SAFE_DELETE(m_CharData[0]);
		m_CharData[0] = new CharData;
//		for(int type = 0; type < 10; type++) Item_Inv->m_OK_Flag[type] = 0;
//		SAFE_DELETE(Item_Inv);
		if(m_CharNum >0) m_CharNum--;
	}
	else if(SocketMng.m_szLoginId2 == name)
	{
		SocketMng.m_szLoginId2.Empty();
		SAFE_DELETE(m_CharData[1]);
		m_CharData[1] = new CharData;
//		for(int type = 0; type < 10; type++) Item_Inv2->m_OK_Flag[type] = 0;
//		SAFE_DELETE(Item_Inv2);
		if(m_CharNum >0) m_CharNum--;
	}
	else if(SocketMng.m_szLoginId3 == name)
	{
		SocketMng.m_szLoginId3.Empty();
		SAFE_DELETE(m_CharData[2]);
		m_CharData[2] = new CharData;
//		for(int type = 0; type < 10; type++) Item_Inv3->m_OK_Flag[type] = 0;
//		SAFE_DELETE(Item_Inv3);
		if(m_CharNum >0) m_CharNum--;
	}
	//�켮.
		//������ ���̵�� ���Ͽ� �������� �����ش�.������ �ؾߵɱ�?
}


void CChildView::NewCharter()
{
	int Select = 0;
	CPoint pos1;
	pos1.x = 505; pos1.y = 30;

//�켮.. �����ͷ� �ٲ�.. 9�� 9��...
	Item_Inv2->Draw(pos1.x,pos1.y);

	m_pBBDX_Editor_id->SetFocus();
	m_pBBDX_Editor_id->GetText();
	CString str_id =  m_pBBDX_Editor_id->GetCurEditorText();
	
	if(GetAsyncKeyState(VK_RETURN) & 0x8000)
	{
		//if(str_id)
		if(SendNewHero(str_id,NULL)) //�켮....
		{
			// �����ش�.
			SetWindowText("");
			SetCaretPos(CPoint(0,0));
			m_test_Flag = 1;// ���������� ���� �Ѵ�.			
		}
		Sleep(200);
	}

	if (m_pBBDX_Editor_id) 
		m_pBBDX_Editor_id->DCDrawOffsetedCurText(DirectXMng.m_pDrawSurface);	//�����Ϳ� ������ �� �׸���(Editor �� ���� �Ⱥ��̴µ� ����)


}

void CChildView::UseItemProcess(PBYTE bypData)
{
	int offset=0;
	char *value;

	BYTE bBelt = CPacketParser::GetByte(bypData, offset);
	short index = CPacketParser::GetShort(bypData, offset);
	BYTE item_type = CPacketParser::GetByte(bypData, offset);
	short use_time = CPacketParser::GetShort(bypData, offset);
	short torchlight = CPacketParser::GetShort(bypData, offset);

	CUser *ptmp = UserManager.GetMe();
	if(torchlight != -1 && ptmp )
	{
		ptmp->m_dwTorchlight = GetTickCount() + torchlight*1000; 
	}
	if(use_time == 0)
	{
		ptmp->Del_Item(bBelt, index);
		if(bBelt == BASIC_INV)
		{
			if(Dialog_Inv.IsVisible()) Dialog_Inv.RefreshData();
			else if(Dialog_Shop.IsVisible()) Dialog_Shop.RefreshData();
			else if(Dialog_Storage.IsVisible()) Dialog_Storage.RefreshData();
			else if(Dialog_AuctionSell.IsVisible()) Dialog_AuctionSell.RefreshData();
			else if(Dialog_Repair.IsVisible()) Dialog_Repair.RefreshData();
		}
	}
	else
	{
		CMyInvData inv_data;

		inv_data.m_vIndex = index;
		inv_data.m_vUsage = use_time;
		ptmp->ChangeItemInfo(bBelt, INFO_DUR, inv_data);
		if(bBelt == BASIC_INV)
		{
			if(Dialog_Inv.IsVisible()) Dialog_Inv.RefreshData();
			else if(Dialog_Shop.IsVisible()) Dialog_Shop.RefreshData();
			else if(Dialog_Storage.IsVisible()) Dialog_Storage.RefreshData();
			else if(Dialog_AuctionSell.IsVisible()) Dialog_AuctionSell.RefreshData();
			else if(Dialog_Repair.IsVisible()) Dialog_Repair.RefreshData();
		}
	}

	if(g_SoundName.Lookup(SOUND_DRINK, value))
	{
		CPoint ptScale = ptmp->GetPosition() - MapManager.GetMapStartPos(); 
		CChildView::DirectXMng.m_pDirectSound->SoundPlay(value, SOUND_DRINK, FALSE, ptScale);
	}
}

void CChildView::ThrowItemProcess(PBYTE bypData)
{
	// ���� �޴´�.
	int offset=0;
	BYTE success = CPacketParser::GetByte(bypData, offset);
	if(success == 0x02)
		return;// ����..

	BYTE bBelt = CPacketParser::GetByte(bypData, offset);
	short index = CPacketParser::GetShort(bypData, offset);
	short count = CPacketParser::GetShort(bypData, offset);
	// �����̸� index�� ������..������..
	
	CUser *ptmp = UserManager.GetMe();
	BYTE vType = 0, vArm = 0;
	short vPicNum = 0, vDur = 0;
	CString vName;

	if(count == 0) ptmp->Del_Item(bBelt, index);// �������� �����ش�.
	else
	{
		CMyInvData inv_data;

		inv_data.m_vIndex = index;
		inv_data.m_vUsage = count;
		ptmp->ChangeItemInfo(bBelt, INFO_DUR, inv_data);
	}
	if(bBelt == BASIC_INV)
	{
		if(Dialog_Inv.IsVisible()) Dialog_Inv.RefreshData();
		else if(Dialog_Shop.IsVisible()) Dialog_Shop.RefreshData();
		else if(Dialog_Storage.IsVisible()) Dialog_Storage.RefreshData();
		else if(Dialog_AuctionSell.IsVisible()) Dialog_AuctionSell.RefreshData();
		else if(Dialog_Repair.IsVisible()) Dialog_Repair.RefreshData();
	}
}

void CChildView::PickUpItemProcess(PBYTE bypData)
{
	int offset=0;
	BYTE success = CPacketParser::GetByte(bypData, offset);
	if(success == 0x02)
		return;// ����..

	CUser *ptmp = UserManager.GetMe();
	ptmp->Add_Item(bypData+offset);// 

	if(Dialog_Inv.IsVisible()) Dialog_Inv.RefreshData();
	else if(Dialog_Shop.IsVisible()) Dialog_Shop.RefreshData();
	else if(Dialog_Storage.IsVisible()) Dialog_Storage.RefreshData();
	else if(Dialog_AuctionSell.IsVisible()) Dialog_AuctionSell.RefreshData();
	else if(Dialog_Repair.IsVisible()) Dialog_Repair.RefreshData();
}

void CChildView::OutItemProcess(PBYTE bypData)
{
	// ���� �޴´�.
	int offset=0;
	BYTE bBelt = CPacketParser::GetByte(bypData, offset);

	short index = CPacketParser::GetShort(bypData, offset);
	
	CUser *ptmp = UserManager.GetMe();
	ptmp->Del_Item(bBelt, index);// �������� �����ش�.
}

void CChildView::GetItemProcess(PBYTE bypData)
{
	CUser *ptmp = UserManager.GetMe();
	ptmp->Add_Item(bypData);

	if(Dialog_Inv.IsVisible()) Dialog_Inv.RefreshData();
	else if(Dialog_Shop.IsVisible()) Dialog_Shop.RefreshData();
	else if(Dialog_Storage.IsVisible()) Dialog_Storage.RefreshData();
	else if(Dialog_AuctionSell.IsVisible()) Dialog_AuctionSell.RefreshData();
	else if(Dialog_Repair.IsVisible()) Dialog_Repair.RefreshData();
}

void CChildView::MoneyChangeProcess(PBYTE bypData)
{
	int offset=0;

	DWORD money = CPacketParser::GetDword(bypData, offset);
	
	CUser *ptmp = UserManager.GetMe();
	ptmp->ChangeMoney(money);
}

void CChildView::FieldInfoItemProcess(PBYTE bypData)
{
/*	Byte ITEM_FIELD_INFO 0x36
Byte INFO_MODIFY
Int uid
Short fieldpic
Short tox
Short toy
*/
	CString t_name;
	int offset=0;
	BYTE Info_modify = CPacketParser::GetByte(bypData, offset);
	short pic = CPacketParser::GetShort(bypData, offset);
	BYTE len = CPacketParser::GetByte(bypData, offset);
	CPacketParser::GetString(bypData, offset, (PBYTE)t_name.GetBuffer(len), len);
	t_name.ReleaseBuffer();
	short x = CPacketParser::GetShort(bypData, offset);
	short y = CPacketParser::GetShort(bypData, offset);

	if(Info_modify == 0x1)
	{
		CPoint pos;
		pos.x = x;
		pos.y = y;
		Item_Field.Add_F_item(pos, (int) pic, t_name);
	}
	else if(Info_modify == 0x2)
	{
		CPoint pos;
		pos.x = x;
		pos.y = y;

		Item_Field.Del_F_item(pos, (int) pic);

		// ������ ����..

	}
}

void CChildView::CharacterDataProcess(PBYTE bypData)
{
/*
	byte	�̸� ����
	string	name �̸�
    byte    Īȣ ����
	string  designation Īȣ
    byte    �Ҽ� ����
	string  position  �Ҽ�
	byte    ���� ����
	string  status

    DWORD	money ��
	short	deposition ����
    short   age ����
	short	gender ���� (0:����, 1:����)
	short   strength ��
	short   agility ��ø��
	short   intelligence ����
	short   wisdom ����
	short   charm �ŷ�
	short   constitution ü��
    

	Short ����
	DWORD �ƽ�����ġ
	DWORD �������ġ
	Short Max_Hp
	Short Cur_Hp
	Short Max_Mp
	Short Cur_Mp
	Short �ƽ�����
	Short ���繫��
	Short �ƽ��Ƿε�
	Short �Ƿε�

    skill.........
	short  sword ��
	short  spear â
	short  blunt �б�
	short  club  ��
	short  bow   ��
	short  crook ������

    short  weapon ��������
	short  armor  �� ����
	short  accessories ��ű�����
	short  reagent  �þ�����
	short  cooking  �丮
*/
	int offset=0;
	short len;
	CString str;
	BYTE bValue;

	bValue = CPacketParser::GetByte(bypData, offset);

	// ����Ÿ�� ���� �ִ´�. ���÷��̿��� �̿��ϰ���..
	CUser *ptme = UserManager.GetMe();

	if(bValue&INFO_NAMES)
	{
		CString name, designation, position, status;
		LPSTR lpStr;

		// �̸�
		len = CPacketParser::GetByte(bypData, offset);
		lpStr = ptme->m_strUserId.GetBufferSetLength((int)len);
		CPacketParser::GetString(bypData, offset, (PBYTE)lpStr, (int)len);
		ptme->m_strUserId.ReleaseBuffer();
		ptme->m_strUserId.MakeUpper();

		// Īȣ
		len = CPacketParser::GetByte(bypData, offset);
		if(len > 0)
		{
			lpStr = ptme->m_Designation.GetBufferSetLength((int)len);
			CPacketParser::GetString(bypData, offset, (PBYTE)lpStr, (int)len);
			ptme->m_Designation.ReleaseBuffer();
			ptme->m_Designation.MakeUpper();
		}
		else ptme->m_Designation.Empty();

		// �Ҽ�
		len = CPacketParser::GetByte(bypData, offset);
		if(len > 0)
		{
			lpStr = str.GetBufferSetLength((int)len);
			CPacketParser::GetString(bypData, offset, (PBYTE)lpStr, (int)len);
			str.ReleaseBuffer();
			ptme->m_Guild.MakeUpper();
		}
		else ptme->m_Guild.Empty();

		// ����
		len = CPacketParser::GetByte(bypData, offset);
		if(len > 0)
		{
			lpStr = str.GetBufferSetLength((int)len);
			CPacketParser::GetString(bypData, offset, (PBYTE)lpStr, (int)len);
			str.ReleaseBuffer();
			ptme->m_Grade.MakeUpper();
		}
		else ptme->m_Grade.Empty();
	}

	if(bValue&INFO_BASICVALUE)
	{
		DWORD Money = CPacketParser::GetDword(bypData, offset);
		short Deposition = CPacketParser::GetShort(bypData, offset);
		short Age = CPacketParser::GetShort(bypData, offset);
		short Gender = CPacketParser::GetShort(bypData, offset);
		short Strength = CPacketParser::GetShort(bypData, offset);
		short Agility = CPacketParser::GetShort(bypData, offset);
		short Intelligence = CPacketParser::GetShort(bypData, offset);
		short Wisdom = CPacketParser::GetShort(bypData, offset);
		short Charm = CPacketParser::GetShort(bypData, offset);
		short Constitution = CPacketParser::GetShort(bypData, offset);

		ptme->m_Money = Money;					// ��
		ptme->SetDeposition(Deposition);		// ����
		ptme->m_Age = Age;						// ����
		ptme->m_Gender = Gender;				// ����
		ptme->m_Str = Strength;					// ��
		ptme->m_Dex = Agility;					// ��ø
		ptme->m_Int = Intelligence;				// ����
		ptme->m_Wis = Wisdom;					// ����
		ptme->m_Cha = Charm;					// �ŷ�
		ptme->m_Con = Constitution;				// ü��
	}

	if(bValue&INFO_EXTVALUE)
	{
		short Level = CPacketParser::GetShort(bypData, offset);
		
		DWORD Max_exp = CPacketParser::GetDword(bypData, offset);//����ġ
		DWORD Cur_exp = CPacketParser::GetDword(bypData, offset);
		
		short Max_Hp = CPacketParser::GetShort(bypData, offset);
		short Cur_Hp = CPacketParser::GetShort(bypData, offset);
		
		short Max_Mp = CPacketParser::GetShort(bypData, offset);
		short Cur_Mp = CPacketParser::GetShort(bypData, offset);
		
		short Max_Weight = CPacketParser::GetShort(bypData, offset);//���湫��
		short Cur_Weight = CPacketParser::GetShort(bypData, offset);

		short Max_Fatigue = CPacketParser::GetShort(bypData, offset);
		short Cur_Fatigue = CPacketParser::GetShort(bypData, offset);//�Ƿε�

		ptme->m_Level = Level;
		ptme->m_Max_exp = Max_exp;
		ptme->m_Cur_exp = Cur_exp;
		ptme->m_Max_Hp = Max_Hp;
		ptme->m_Cur_Hp = Cur_Hp;
		ptme->m_Max_Mp = Max_Mp;
		ptme->m_Cur_Mp = Cur_Mp;
		ptme->m_Max_Weight = Max_Weight;
		ptme->m_Cur_Weight = Cur_Weight;
		ptme->m_Max_Fa = Max_Fatigue;
		ptme->m_Cur_Fa = Cur_Fatigue;
	}

	if(bValue&INFO_WEAPONEXP)
	{
		int  Sword  = CPacketParser::GetInt(bypData, offset);//Į
		int  Spear  = CPacketParser::GetInt(bypData, offset);//â
		int  Blunt  = CPacketParser::GetInt(bypData, offset);// �б�
		int  Club   = CPacketParser::GetInt(bypData, offset);// ��
		int  Bow    = CPacketParser::GetInt(bypData, offset);// ��
		int  Crook  = CPacketParser::GetInt(bypData, offset);// ������

		ptme->m_UsingSword = Sword;			// ��
		ptme->m_UsingSpear = Spear;			// â
		ptme->m_UsingAxe = Blunt;			// �б�
		ptme->m_UsingKnuckle = Club;		// ��
		ptme->m_UsingBow = Bow;				// ��
		ptme->m_UsingCrook = Crook;			// ������
	}

	if(bValue&INFO_MAKEEXP)
	{
		int  Weapon  = CPacketParser::GetInt(bypData, offset);// ��������
		int  Armor   = CPacketParser::GetInt(bypData, offset);// �� ����
		int  Accessories  = CPacketParser::GetInt(bypData, offset);// ��ű�����
		int  Reagent   = CPacketParser::GetInt(bypData, offset);// �þ�����
		int  Cooking   = CPacketParser::GetInt(bypData, offset);// �丮

		ptme->m_MakingWeapon = Weapon;		// ���� ����
		ptme->m_MakingArmor = Armor;		// �� ����
		ptme->m_MakingAccessory = Accessories; // ��ű� ����
		ptme->m_MakingPotion = Reagent;		// �þ� ����
		ptme->m_Cooking = Cooking;			// �丮
	}

	if(bValue&INFO_MAGICEXP)
	{
		ptme->m_BlackMagicExp = CPacketParser::GetInt(bypData, offset); // �渶�� ���ġ
		ptme->m_WhiteMagicExp = CPacketParser::GetInt(bypData, offset); // �鸶�� ���ġ
		ptme->m_BlueMagicExp = CPacketParser::GetInt(bypData, offset); // û���� ���ġ
	}
}

void CChildView::ClearScreen()
{
/*	COLORREF crFill = 0;
	// ����۸� ���������� ä��
	DDBLTFX ddbltfx;
//	CLEAR(ddbltfx);
	ddbltfx.dwSize = sizeof(ddbltfx);
	ddbltfx.dwFillColor = 0;
	HRESULT rval = DirectXMng.m_bpBackSurf->Blt(NULL, NULL, NULL, DDBLT_COLORFILL | DDBLT_WAIT, &ddbltfx);
	DirectXMng.Flip();
*/	
	DirectXMng.m_pDrawSurface->SurfaceFill(RGB(0, 0, 0));
	DirectXMng.m_bpBackSurf->SurfaceFill(RGB(0, 0, 0));
	DirectXMng.m_bpFrontSurf->SurfaceFill(RGB(0, 0, 0));

//	DirectXMng.Flip();

}

CPoint CChildView::PixelToCellUnit(CPoint ptPixel)
{
	CPoint p = ptPixel;

	int X = 48;
	int Y = 24;

	int k1, k2;
	k1 = (int)ceil((.5*p.x+p.y-Y)/X);
	k2 = (int)ceil((-.5*p.x+p.y+Y)/X);
	
	k1 = X*k1 + Y;
	k2 = X*k2 - Y;
	
	p.x = k1 - k2;
	p.y = (k1+k2)/2-Y;
	
	p.x = int(p.x/24.+.5)*Y;
	p.y = int(p.y/24.+.5)*Y;
	
	p.x /= X;
	p.y /= Y;
	p.x--;
	p.y--;

	return p;

}

CPoint CChildView::CellUnitToPixel(CPoint ptCell)
{
	CPoint ptPixel;
	ptPixel.x = (ptCell.x+1)*48;
	ptPixel.y = (ptCell.y+1)*24;
	return ptPixel;
}


void CChildView::DrawObject()
{
//		MapManager.DrawPreSprite(DirectXMng.m_pDrawSurface);//���� ������ �ʴ� Sprite�׸���
		UserManager.RenderUsers(DirectXMng.m_pDrawSurface, m_ptMapOffset);	//������ �׸���
//		MapManager.DrawPostSprite(DirectXMng.m_pDrawSurface);	//���� ������ Sprite�׸��� (�ϴ� ����ó���ϰ� ����(Alpha))
}

void CChildView::ChatMode(int type)
{
	if(type == 1 && m_Chattype == 2)// �븻 ä���̸�..
	{
		CRect r = CRect(30, 520, 580, 540);
		m_pBBDX_Editor->ClearTexts();
		m_pBBDX_Editor->ChangeArea(r);
	}
	m_Chattype = type;
}

void CChildView::DrawHousePlace()
{
	if(HousePlaceManager.IsSelectMode())
	{
		CDC *pDC;
		int i;
		CRect t_rect;
		CPen pen(PS_SOLID, 1, RGB(255,255,0)), *old_pen;
		CBrush *old_brush;
		
		pDC = DirectXMng.m_pDrawSurface->GetDC();
		
		old_pen = pDC->SelectObject(&pen);
		old_brush = (CBrush *)pDC->SelectStockObject(NULL_BRUSH);
		
		for(i = 0; i < HousePlaceManager.m_vPlaceCount; i++)
		{
			t_rect = HousePlaceManager.m_pPlaceRect[i];
			t_rect.left <<= 5;
			t_rect.top <<= 5;
			t_rect.right <<= 5;
			t_rect.bottom <<= 5;
			t_rect.OffsetRect(-m_ptMapOffset.x, -m_ptMapOffset.y);
			pDC->Rectangle((LPCRECT)t_rect);
		}

		pDC->SelectObject(old_pen);
		pDC->SelectObject(old_brush);
		DirectXMng.m_pDrawSurface->ReleaseDC(pDC);
	}
}

void CChildView::ViewSelectBox(CRect rBox, int color)
{
	CDC *pDC = DirectXMng.m_pDrawSurface->GetDC();
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,0));
//	pDC->DrawEdge(rBox, EDGE_BUMP, BF_RECT);
	//pDC->DrawEdge(rBox, EDGE_SUNKEN, BF_RECT);
	//::DrawText(pDC->m_hDC , m_szChatString, strlen(m_szChatString), &temp, DT_WORDBREAK);
	CChildView::DirectXMng.m_pDrawSurface->ReleaseDC(pDC);

}

// ���Ͽ��� �о�´�..������ �׸���ȣ�� ���� �׸���ȣ����...
void CChildView::ReadItemIndex()
{
//	m_Item_Pic_Index[i];
	// Item_Pic_Index[1000]; // �ӽ÷� ��ƾ���..
	//[*] *=> ������ �׸���ȣ
	//��� ���� ���� �׸���ȣ..

	CFile file;
	CString szItemFileName = _T("item.idx");

	if(!file.Open(szItemFileName, CFile::modeRead))
	{
		TRACE("������ ���� %s�� ���� �� �������ϴ�.\n", (LPCTSTR)szItemFileName);
		return;
	}

	char nItemCount[5];
	
	int nReadCount = file.Read(nItemCount, 4);
	nItemCount[4] = 0;
	int count = atoi(nItemCount);
	char Item1[5], Item2[4], Item3[3], Item4[2];//item1 ->������ �׸���ȣ, item2->�����׸���ȣ, item3->���� Ÿ��
	int  nItem1=0;
	int  nItem2=0;
	int  nItem3=0;
	int  nItem4=0;

	Item1[4] = Item2[3] = Item3[2] = Item4[1] = 0;
	for(int i=0;i<count;i++)
	{		
		file.Read(Item1, 2);// \n...�� �ι���Ʈ..
		file.Read(Item1, 4);		
		file.Read(Item2, 3);
		file.Read(Item3, 2);		
		file.Read(Item4, 1);		

		nItem1 = atoi(Item1);
		nItem2 = atoi(Item2);		
		nItem3 = atoi(Item3);// ���� Ÿ��..	
		nItem4 = atoi(Item4);// �׸��� ����..
		m_Item_Pic_Index[nItem1] = nItem2;// 1000������..����...�� �̻��� �Ǹ�..���� �ٲ�����Ѵ�.
		m_Arm_type[nItem1] = nItem3; //�켮.. 10�� 16��..
		m_Draw_Order[nItem1] = nItem4;
	}
	file.Close();
}

//ĳ������ ������ �����Ѵ�.... �켮 �߰�.. 10�� 16��..
int CChildView::GetItemArmTypeIndex(int i)
{
	if(i <= 0 || i > 1000) return 0;
	return m_Arm_type[i];
}

// �������� ��������...
int CChildView::GetItemDrawOrderIndex(int i)
{
	if(i <= 0 || i > 1000) return 0;
	return m_Draw_Order[i];
}

// ���� ������ �׸���ȣ�� ���� ������ ���� �׸� ��ȣ�� ���Եȴ�.
int CChildView::GetItemPicIndex(int i)
{
	if(i < 0 || i > 1000) return 0;
	return m_Item_Pic_Index[i];
}


static const BOOL bUCK[] = {FALSE, TRUE, TRUE, FALSE, TRUE, TRUE};
static const int nRenderType[] = {RENDER_NORMAL, RENDER_NORMAL, RENDER_NORMAL, RENDER_SHADOW, RENDER_NORMAL, RENDER_NORMAL};

void CChildView::DrawTile(int type)
{
	int start, end;
	int Cell_X = (m_ptMapOffset.x >> 5); // /32
	int Offset_X = 32 - (m_ptMapOffset.x & 0x1f); // %32
	int Cell_Y = (m_ptMapOffset.y >> 5); // /32
	int Offset_Y = 32 - (m_ptMapOffset.y & 0x1f); // %32
	SIZE half_size;

	half_size.cx = (int)(g_vDispCellSize.cx / 2.0 + 0.5);
	half_size.cy = (int)(g_vDispCellSize.cy / 2.0 + 0.5);

	switch(type)
	{
	case 0:
		m_limit_old_y = Cell_Y-9;// ������Ʈ�� ��Ʈ�ؼ� �Ѹ��� ���ؼ�...���� �־���.
		start = 0;
		end = 2;
		break;
	case 1:
		start = 4;
		end = 4;
		break;
	default:
		start = 0;
		end = 2;
		break;
	}

	m_limit_old_y = Cell_Y-half_size.cy;// ������Ʈ�� ��Ʈ�ؼ� �Ѹ��� ���ؼ�...���� �־���.

	CPoint ptScroll = CPoint(Cell_X+1, Cell_Y+1);

	for(int nLayer = start; nLayer <= end; nLayer++)
	{
		int x, y;

		IDirectDrawSurface7 *destSurface = DirectXMng.m_pDrawSurface->GetInterface();
		for(y = Cell_Y; y < Cell_Y+g_vDispCellSize.cy; y++) // �ٴڿ� �򸮴� �� //���� �ִ� ���� �ҽ�
		{
			for(x = Cell_X; x < Cell_X+g_vDispCellSize.cx; x++)
			{
				const _TILE_MAP_DATA_TOOL* pTMData = TileMapTool.ToolDataGet(nLayer, x, y);
				if(pTMData == NULL) continue;
				_TILE_SET_TOOL *tile_set_tool;

				tile_set_tool = TileSetTool.GetTileSet(pTMData->snTS);
				if(tile_set_tool == NULL) continue;
				if(tile_set_tool->m_lpDDSs == NULL)
				{// ���� ���� �����̽��̹Ƿ� �о� ���δ�. 
					CString szBMPFN = tile_set_tool->m_HTSs.szBMPFN;
					if(szBMPFN.GetLength() > 0)
					{
						szBMPFN = szBMPFN.Left(szBMPFN.GetLength() - 3);
						g_pTEng.PathSetCur("BMP");
						
						//  9.15 ���� obm�� �о�� �ȵǸ� bmp �� �д´�.
						if( type == 1 || type == 2 )
							tile_set_tool->m_lpDDSs = g_pTEng.SurfaceCreateWithBMP(szBMPFN + "obm", FALSE, tile_set_tool->m_HTSs.crCK, TRUE);
						else
							tile_set_tool->m_lpDDSs = g_pTEng.SurfaceCreateWithBMP(szBMPFN + "obm", FALSE, tile_set_tool->m_HTSs.crCK);
						if(tile_set_tool->m_lpDDSs == NULL)
						{
							tile_set_tool->m_lpDDSs = g_pTEng.SurfaceCreateWithBMP(szBMPFN + "bmp", FALSE, tile_set_tool->m_HTSs.crCK);
							if(tile_set_tool->m_lpDDSs)
							{
								TRACE("%s ����\n", szBMPFN + "bmp");
							}
							else continue;
						}
						else
						{
							TRACE("DrawTile:%s ����(%ld)\n", szBMPFN + "obm", g_vRenderTime);
						}
					}
					////////////////////////////
				}
				tile_set_tool->m_vUseTime = g_vRenderTime;
				POINT *t_pos = TileSetTool.DataGetPos(pTMData->snTS, pTMData->snTSS, pTMData->snNum);

				if(t_pos == NULL ||
					t_pos->x < 0 ||
					t_pos->x >= MAX_TILE_SET_WIDTH ||
					t_pos->y < 0 ||
					t_pos->y >= MAX_TILE_SET_HEIGHT) continue; // ���� �ʴ� Ÿ���̸� ��������..

				CRect rcSrc;
				rcSrc.left = t_pos->x << 5; // *32
				rcSrc.top = t_pos->y << 5; // *32
				rcSrc.right = rcSrc.left + TILE_SIZE;
				rcSrc.bottom = rcSrc.top + TILE_SIZE;
				
				if( type == 1 )
				{
					CRect rc(((x-ptScroll.x)<<5)+Offset_X,
							 ((y-ptScroll.y)<<5)+Offset_Y,
							 ((x-ptScroll.x)<<5)+Offset_X+TILE_SIZE,
							 ((y-ptScroll.y)<<5)+Offset_Y+TILE_SIZE);
					
					CUser* me = UserManager.GetUserWithUid( m_iMyId ); 
					BOOL bCheck;
					CPoint pt =  me->GetPosition()-MapManager.GetMapStartPos();
//					bCheck = rc.PtInRect( pt );
//					if( bCheck ) UserManager.m_bMyCovered = TRUE;
					bCheck = rc.PtInRect( pt );
					if( bCheck )
					{
						CPoint ptRegion;
						for( int ii = 1; ii < 9 ; ii++ )
						{
							ptRegion.x = pt.x;
							ptRegion.y = pt.y - 10*ii;
							UserManager.m_nCoverDegree = ii;
						}
						UserManager.m_bMyCovered = TRUE;
					}
				}
				g_pTEng.BltNormal(tile_set_tool->m_lpDDSs, 
					((x-ptScroll.x)<<5)+Offset_X,
					((y-ptScroll.y)<<5)+Offset_Y,
					rcSrc, bUCK[nLayer], nRenderType[nLayer], 16, 0, destSurface);
			}
		}
	}
}

void CChildView::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == 0)
	{
		SendLivePacket();
	}
	else if(nIDEvent == 10)
	{
		Dialog_DeadMain.CountDown();
	}
	
	CWnd ::OnTimer(nIDEvent);
}

void SendMagicBelt()
{
	BYTE buf[10];
	int offset = 0;

	CChildView::SocketMng.MP_AddByte(buf, offset, PKT_MAGIC_BELT);
	for(int i = 0; i < 4; i++)
	{
		if(Dialog_Main.m_pMagicData[i])
		{
			CChildView::SocketMng.MP_AddShort(buf, offset, Dialog_Main.m_pMagicData[i]->m_vNumber);
		}
		else
		{
			CChildView::SocketMng.MP_AddShort(buf, offset, -1);
		}
	}
	CChildView::SocketMng.Send(offset, buf);
}

void CChildView::OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(m_iMyId!=-1 && UserManager.m_ReadyOK == 1)
	{
		if(nChar == VK_F10)
		{
			if(m_bKeyDown[VK_F10] == 0)
			{
				if(Dialog_Inv.IsVisible()) Dialog_Inv.HideWindow();
				else Dialog_Inv.ShowWindow();
				m_bKeyDown[VK_F10] = 1;
			}
			return;
		}
	}
	
	CWnd::OnSysKeyDown(nChar, nRepCnt, nFlags);
}
//	CDDSurface* GetSurface(){return m_pBaseSurface;}

void CChildView::DrawShawdowObj(CDDSurface *pSurface)
{
	int Cell_X = (m_ptMapOffset.x >> 5); // /32
	int Offset_X = 32 - (m_ptMapOffset.x & 0x1f); // %32
	int Cell_Y = (m_ptMapOffset.y >> 5); // /32
	int Offset_Y = 32 - (m_ptMapOffset.y & 0x1f); // %32
	CPoint ptScroll = CPoint(Cell_X+1, Cell_Y+1);
	int start_x, end_x, start_y, end_y;
	SIZE half_size;

	short int nData, nSet = 0, nSubSet = 0;
	const _SPR_LSP* pSpr = NULL;

	half_size.cx = (int)(g_vDispCellSize.cx / 2.0 + 0.5);
	half_size.cy = (int)(g_vDispCellSize.cy / 2.0 + 0.5);

	if(Cell_X-half_size.cx < 0) start_x = 0;
	else start_x = Cell_X - half_size.cx;
	if(Cell_X+g_vDispCellSize.cx+half_size.cx >= MapObj.m_Header.nWidth) end_x = MapObj.m_Header.nWidth;
	else end_x = Cell_X + g_vDispCellSize.cx + half_size.cx;

	if(Cell_Y-half_size.cy < 0) start_y = 0;
	else start_y = Cell_Y - half_size.cy;
	if(Cell_Y+g_vDispCellSize.cy+half_size.cy >= MapObj.m_Header.nWidth) end_y = MapObj.m_Header.nHeight;
	else end_y = Cell_Y + g_vDispCellSize.cy + half_size.cy;
	
	for(int y = start_y; y < end_y; y++) // �ٴڿ� �򸮴� ��
	{
		for(int x = start_x; x < end_x; x++)
		{
			nData = MapShadowObj.DataGet(x, y);
			nSet = nData >> 8; // ��Ʈ ��ȣ�� ���� ����Ʈ �̴�.
			if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) continue; // �迭 ���� üũ
			nSubSet = nData & 0x00ff; // ���� ��Ʈ ��ȣ�� ���� ����Ʈ

			// ani....�Ʒ� ���� ���Ҵ�...�̻��ؼ�..
//				MapAniObjs[nSet].AniSet(nSubSet, FL_ANI_LOOP, nSubSet); // ���ϸ��̼� �������ְ�
//				MapAniObjs[nSet].SprGetAnimated(&pSpr, nSubSet);
//				if(pSpr == NULL) continue; // ��������Ʈ �����Ͱ� ������ ��������.

			//����..
			int nSpr = MapShadowAniObjs[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
			MapShadowAniObjs[nSet].SprGet(nSpr, &pSpr);
			if(pSpr == NULL) // 9.28 �� ������Ʈ ��������Ʈ�� ������ �б⸦ �õ��Ѵ�.
			{
				if(CChildView::MapShadowObj.m_Header.szRegObjSprFNs[nSet][0] == 0) continue;

				CString szFN = "map\\object\\";
				szFN += CChildView::MapShadowObj.m_Header.szRegObjAniFNs[nSet]; // ���ϸ��̼� ���� �б�
				MapShadowAniObjs[nSet].AniLoad(szFN);
				MapShadowAniObjs[nSet].AniCtrlAlloc(256);
				szFN = "map\\object\\";
				szFN += CChildView::MapShadowObj.m_Header.szRegObjSprFNs[nSet];

				MapShadowAniObjs[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
				//MapShadowAniObjs[nSet].SprLoad(szFN, 0); // ��������Ʈ ���� �б�.
				// �ٽ� �ѹ� ��������Ʈ �����͸� �������� �õ�. 
				nSpr = MapShadowAniObjs[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
				MapShadowAniObjs[nSet].SprGet(nSpr, &pSpr);
				if(pSpr == NULL) continue;
			}
		
			RECT rcV = pSpr->rcV;
			// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
			CUser *tmpUser = UserManager.GetMe();
			PWORD wpV = pSpr->pwV;	
			tmpUser->BltLSPShadowEx(pSurface, (x-ptScroll.x)*TILE_SIZE+16+Offset_X+g_vDispPixSize.cx, (y-ptScroll.y)*TILE_SIZE+16+Offset_Y+g_vDispPixSize.cy, &rcV, wpV, DirectXMng.m_dwHalf16Mask, DirectXMng.m_dwHalf32Mask );
		}
	}
}


void CChildView::DrawShawdowObj()
{
	return;
	int Cell_X = (m_ptMapOffset.x >> 5); // /32
	int Offset_X = 32 - (m_ptMapOffset.x & 0x1f); // %32
	int Cell_Y = (m_ptMapOffset.y >> 5); // /32
	int Offset_Y = 32 - (m_ptMapOffset.y & 0x1f); // %32
	CPoint ptScroll = CPoint(Cell_X+1, Cell_Y+1);
	int start_x, end_x, start_y, end_y;

	short int nData, nSet = 0, nSubSet = 0;
	const _SPR_LSP* pSpr = NULL;
	SIZE half_size;

	half_size.cx = (int)(g_vDispCellSize.cx / 2.0 + 0.5);
	half_size.cy = (int)(g_vDispCellSize.cy / 2.0 + 0.5);

	if(Cell_X-half_size.cx < 0) start_x = 0;
	else start_x = Cell_X - half_size.cx;
	if(Cell_X+g_vDispCellSize.cx+half_size.cx >= MapObj.m_Header.nWidth) end_x = MapObj.m_Header.nWidth;
	else end_x = Cell_X + g_vDispCellSize.cx + half_size.cx;

	if(Cell_Y-half_size.cy < 0) start_y = 0;
	else start_y = Cell_Y - half_size.cy;
	if(Cell_Y+g_vDispCellSize.cy+half_size.cy >= MapObj.m_Header.nWidth) end_y = MapObj.m_Header.nHeight;
	else end_y = Cell_Y + g_vDispCellSize.cy + half_size.cy;
	
	for(int y = start_y; y < end_y; y++) // �ٴڿ� �򸮴� ��
	{
		for(int x = start_x; x < end_x; x++)
		{
			nData = MapShadowObj.DataGet(x, y);
			nSet = nData >> 8; // ��Ʈ ��ȣ�� ���� ����Ʈ �̴�.
			if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) continue; // �迭 ���� üũ
			nSubSet = nData & 0x00ff; // ���� ��Ʈ ��ȣ�� ���� ����Ʈ

			// ani....�Ʒ� ���� ���Ҵ�...�̻��ؼ�..
//				MapAniObjs[nSet].AniSet(nSubSet, FL_ANI_LOOP, nSubSet); // ���ϸ��̼� �������ְ�
//				MapAniObjs[nSet].SprGetAnimated(&pSpr, nSubSet);
//				if(pSpr == NULL) continue; // ��������Ʈ �����Ͱ� ������ ��������.

			//����..
			int nSpr = MapShadowAniObjs[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
			MapShadowAniObjs[nSet].SprGet(nSpr, &pSpr);
			if(pSpr == NULL) // 9.28 �� ������Ʈ ��������Ʈ�� ������ �б⸦ �õ��Ѵ�.
			{
				if(CChildView::MapShadowObj.m_Header.szRegObjSprFNs[nSet][0] == 0) continue;

				CString szFN = "map\\object\\";
				szFN += CChildView::MapShadowObj.m_Header.szRegObjAniFNs[nSet]; // ���ϸ��̼� ���� �б�
				MapShadowAniObjs[nSet].AniLoad(szFN);
				MapShadowAniObjs[nSet].AniCtrlAlloc(256);
				szFN = "map\\object\\";
				szFN += CChildView::MapShadowObj.m_Header.szRegObjSprFNs[nSet];

				MapShadowAniObjs[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
				//MapShadowAniObjs[nSet].SprLoad(szFN, 0); // ��������Ʈ ���� �б�.
				// �ٽ� �ѹ� ��������Ʈ �����͸� �������� �õ�. 
				nSpr = MapShadowAniObjs[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
				MapShadowAniObjs[nSet].SprGet(nSpr, &pSpr);
				if(pSpr == NULL) continue;
			}
		
			RECT rcV = pSpr->rcV;
			// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
			CUser *tmpUser = UserManager.GetMe();
			PWORD wpV = pSpr->pwV;	
			//tmpUser->BltLSPShadow(DirectXMng.m_pDrawSurface, (x-ptScroll.x)*TILE_SIZE+16+Offset_X, (y-ptScroll.y)*TILE_SIZE+16+Offset_Y, &rcV, wpV, 16);
			tmpUser->BltLSPShadowEx(DirectXMng.m_pDrawSurface, (x-ptScroll.x)*TILE_SIZE+16+Offset_X, (y-ptScroll.y)*TILE_SIZE+16+Offset_Y, &rcV, wpV, DirectXMng.m_dwHalf16Mask, DirectXMng.m_dwHalf32Mask );
			//tmpUser->BltLSPNormal(DirectXMng.m_pDrawSurface, (x-ptScroll.x)*TILE_SIZE+16+Offset_X, (y-ptScroll.y)*TILE_SIZE+16+Offset_Y, &rcV, wpV);
		}
	}
}

void CChildView::DrawShawdowObjEx()
{
	int Cell_X = (m_ptMapOffset.x >> 5); // /32
	int Offset_X = 32 - (m_ptMapOffset.x & 0x1f); // %32
	int Cell_Y = (m_ptMapOffset.y >> 5); // /32
	int Offset_Y = 32 - (m_ptMapOffset.y & 0x1f); // %32
	CPoint ptScroll = CPoint(Cell_X+1, Cell_Y+1);
	int start_x, end_x, start_y, end_y;

	short int nData, nSet = 0, nSubSet = 0;
	const _SPR_LSP* pSpr = NULL;
	SIZE half_size;

	half_size.cx = (int)(g_vDispCellSize.cx / 2.0 + 0.5);
	half_size.cy = (int)(g_vDispCellSize.cy / 2.0 + 0.5);

	if(Cell_X-half_size.cx < 0) start_x = 0;
	else start_x = Cell_X - half_size.cx;
	if(Cell_X+g_vDispCellSize.cx+half_size.cx >= MapObj.m_Header.nWidth) end_x = MapObj.m_Header.nWidth;
	else end_x = Cell_X + g_vDispCellSize.cx + half_size.cx;

	if(Cell_Y-half_size.cy < 0) start_y = 0;
	else start_y = Cell_Y - half_size.cy;
	if(Cell_Y+g_vDispCellSize.cy+half_size.cy >= MapObj.m_Header.nWidth) end_y = MapObj.m_Header.nHeight;
	else end_y = Cell_Y + g_vDispCellSize.cy + half_size.cy;
	
	for(int y = start_y; y < end_y; y++) // �ٴڿ� �򸮴� ��
	{
		for(int x = start_x; x < end_x; x++)
		{
			nData = MapShadowObj.DataGet(x, y);
			nSet = nData >> 8; // ��Ʈ ��ȣ�� ���� ����Ʈ �̴�.
			if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) continue; // �迭 ���� üũ
			nSubSet = nData & 0x00ff; // ���� ��Ʈ ��ȣ�� ���� ����Ʈ

			int nSpr = MapShadowAniObjs[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
			MapShadowAniObjs[nSet].SprGet(nSpr, &pSpr);
			if(pSpr == NULL) // 9.28 �� ������Ʈ ��������Ʈ�� ������ �б⸦ �õ��Ѵ�.
			{
				if(CChildView::MapShadowObj.m_Header.szRegObjSprFNs[nSet][0] == 0) continue;

				CString szFN = "map\\object\\";
				szFN += CChildView::MapShadowObj.m_Header.szRegObjAniFNs[nSet]; // ���ϸ��̼� ���� �б�
				MapShadowAniObjs[nSet].AniLoad(szFN);
				MapShadowAniObjs[nSet].AniCtrlAlloc(256);
				szFN = "map\\object\\";
				szFN += CChildView::MapShadowObj.m_Header.szRegObjSprFNs[nSet];

				DirectXMng.m_p3D->D3DCreateTextureEx( szFN.GetBuffer(0) );
				MapShadowAniObjs[nSet].SprLoad(szFN, 1); // ��������Ʈ ���� �б�.
//				MapShadowAniObjs[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
				
				// �ٽ� �ѹ� ��������Ʈ �����͸� �������� �õ�. 
				nSpr = MapShadowAniObjs[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
				MapShadowAniObjs[nSet].SprGet(nSpr, &pSpr);
				if(pSpr == NULL) continue;
			}
		
			CString szFN = "map\\object\\";
			szFN += CChildView::MapShadowObj.m_Header.szRegObjSprFNs[nSet];
			// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
			DirectXMng.m_p3D->D3DRenderShadow( szFN.GetBuffer(0),  (x-ptScroll.x)*TILE_SIZE+16+Offset_X, (y-ptScroll.y)*TILE_SIZE+16+Offset_Y, nSpr );
		}
	}
}

//m_limit_old_yó���� ���� ���� �ִ´�.
void CChildView::DrawObj(int limit_y)
{
	limit_y += m_ptMapOffset.y;
	limit_y = limit_y >> 5;

	int Cell_X = (m_ptMapOffset.x >> 5); // /32
	int Offset_X = 32 - (m_ptMapOffset.x & 0x1f); // %32
	int Cell_Y = (m_ptMapOffset.y >> 5); // /32
	int Offset_Y = 32 - (m_ptMapOffset.y & 0x1f); // %32
	CPoint ptScroll = CPoint(Cell_X+1, Cell_Y+1);
	int start_x, end_x;

	short int nData, nSet = 0, nSubSet = 0;
	const _SPR_LSP* pSpr = NULL;
	int half_size_x;

	half_size_x = (int)(g_vDispCellSize.cx / 2.0 + 0.5);

	if(Cell_X-half_size_x < 0) start_x = 0;
	else start_x = Cell_X - half_size_x;
	if(Cell_X+g_vDispCellSize.cx+half_size_x >= MapObj.m_Header.nWidth) end_x = MapObj.m_Header.nWidth;
	else end_x = Cell_X + g_vDispCellSize.cx + half_size_x;

	//for(int y = Cell_Y-1; y < Cell_Y + 17+10; y++) // �ٴڿ� �򸮴� ��
	for(int y = m_limit_old_y; y < limit_y; y++) // �ٴڿ� �򸮴� ��
	{
		for(int x = start_x; x < end_x; x++)
		{
			nData = MapObj.DataGet(x, y);
			nSet = nData >> 8; // ��Ʈ ��ȣ�� ���� ����Ʈ �̴�.
			if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) continue; // �迭 ���� üũ
			nSubSet = nData & 0x00ff; // ���� ��Ʈ ��ȣ�� ���� ����Ʈ

			// ani....�Ʒ� ���� ���Ҵ�...�̻��ؼ�..
//				MapAniObjs[nSet].AniSet(nSubSet, FL_ANI_LOOP, nSubSet); // ���ϸ��̼� �������ְ�
//				MapAniObjs[nSet].SprGetAnimated(&pSpr, nSubSet);
//				if(pSpr == NULL) continue; // ��������Ʈ �����Ͱ� ������ ��������.

			//����..
//			int nSpr = MapAniObjs[nSet].FrmGetByAniAndDirAndSeq(, 0, 0);
			// ���ϸ��̼�
			int nSpr = MapAniObjs[nSet].FrmGetAnimated(nSubSet);
			MapAniObjs[nSet].SprGet(nSpr, &pSpr);
			if(pSpr == NULL) // 9.28 �� ������Ʈ ��������Ʈ�� ������ �б⸦ �õ��Ѵ�.
			{
				CString szFN = "map\\object\\";
				szFN += CChildView::MapObj.m_Header.szRegObjAniFNs[nSet]; // ���ϸ��̼� ���� �б�
				MapAniObjs[nSet].AniLoad(szFN);
				MapAniObjs[nSet].AniCtrlAlloc(256);
				szFN = "map\\object\\";
				szFN += CChildView::MapObj.m_Header.szRegObjSprFNs[nSet];
				MapAniObjs[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
				// �ٽ� �ѹ� ��������Ʈ �����͸� �������� �õ�. 
				nSpr = MapAniObjs[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
				MapAniObjs[nSet].SprGet(nSpr, &pSpr);
				if(pSpr == NULL) continue;
			}
		
			RECT rcV = pSpr->rcV;
			// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
			CUser *tmpUser = UserManager.GetMe();
			PWORD wpV = pSpr->pwV;				
			tmpUser->BltLSPNormal(DirectXMng.m_pDrawSurface, (x-ptScroll.x)*TILE_SIZE+16+Offset_X, (y-ptScroll.y)*TILE_SIZE+16+Offset_Y, &rcV, wpV);
		}
	}
	m_limit_old_y = limit_y;
}

void CChildView::DisplayDate()
{
	CString t_str;
	short year, month, day, hour;
	BYTE rain;
	CFont *old_font;
	CRect r, r1;

	Weather.GetWeatherInfo(year, month, day, hour, rain);
	t_str.Format("�Ҹ��� %d�� %d�� %d�� %d��", year, month, day, hour);

	CDC *pDC = DirectXMng.m_pDrawSurface->GetDC();
	
	pDC->SetBkMode(TRANSPARENT);
	
	old_font = pDC->SelectObject(pAppFont);
	
	CSize size = pDC->GetTextExtent(t_str);

	if(Dialog_SmallMain.IsVisible())
	{
		size.cx += Dialog_SmallMain.m_mainRect.Width();
		r.SetRect(g_vDispPixSize.cx-(size.cx+5), g_vDispPixSize.cy - 20, g_vDispPixSize.cx, g_vDispPixSize.cy - 5);
	}
	else
	{
		r.SetRect(g_vDispPixSize.cx-(size.cx+5), g_vDispPixSize.cy - 20, g_vDispPixSize.cx, g_vDispPixSize.cy - 5);
	}
	
	// �� �׸���
	pDC->SetTextColor(RGB(5,5,5));
	pDC->DrawText(t_str, &r, DT_TOP|DT_SINGLELINE);

	// ��
	pDC->SetTextColor(RGB(0,255,255));
	r1 = r;
	r1.OffsetRect(-1, -1);
	pDC->DrawText(t_str, &r1, DT_TOP|DT_SINGLELINE);
	
	pDC->SelectObject(old_font);
	CChildView::DirectXMng.m_pDrawSurface->ReleaseDC(pDC);
}

void DisplayRRStats(DirectXMng &dxMng)
{
	int mem;	
	int sx1 = 15, sx2 = 320, sy = 70;
	char  buffer[255];
	char  buf2[255];
	LPTSTR buffer2;
	LPDIRECTDRAW7 lpDD7;
	DDSCAPS2    ddsCaps2; 
	DWORD		total_video_memory;
	DWORD		free_video_memory;
	HRESULT     hr; 
	MEMORYSTATUS memStatus;

	CDC *pDC = dxMng.m_pDrawSurface->GetDC();

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));
	memStatus.dwLength=sizeof(MEMORYSTATUS);
	GlobalMemoryStatus(&memStatus);
		
	mem=(int)memStatus.dwAvailPhys;
	mem = mem / 1024;
	itoa(mem,buffer,10);
	buffer2 = lstrcat(buffer, " KB");
	strcpy(buf2, "Free Physical Memory :");
	pDC->TextOut(sx1, sy, buf2);
	pDC->TextOut(sx2, sy, buffer); 
	sy +=20;

	mem=(int)memStatus.dwTotalPhys;
	mem = mem /1024;
	itoa(mem, buffer,10);
	strcat(buffer, " KB");
	strcpy(buf2, "Total system memory :");
	pDC->TextOut(sx1, sy, buf2);
	pDC->TextOut(sx2, sy, buffer); 
	sy +=20;
			
 
	hr = dxMng.m_pDD->GetInterface()->QueryInterface(IID_IDirectDraw7, (void **)&lpDD7);   
	if (FAILED(hr))
		return; 
 
	// Initialize the structure.
	ZeroMemory(&ddsCaps2, sizeof(ddsCaps2));
  
	ddsCaps2.dwCaps = DDSCAPS_VIDEOMEMORY  ; 
	hr = dxMng.m_pDD->GetInterface()->GetAvailableVidMem(&ddsCaps2, &total_video_memory, &free_video_memory); 
	if (FAILED(hr))
		return;

	mem= total_video_memory;
	mem = mem /1024;
	itoa(mem,buffer,10);
	strcat(buffer, " KB");
	strcpy(buf2, "Total video memory :");
	pDC->TextOut(sx1, sy, buf2);
	pDC->TextOut(sx2, sy, buffer); 
	sy +=20;

	mem= free_video_memory;
	mem = mem /1024;
	itoa(mem,buffer,10);
	strcat(buffer, " KB");
	strcpy(buf2, "Free video memory :");
	pDC->TextOut(sx1, sy, buf2);
	pDC->TextOut(sx2, sy, buffer); 
	sy +=20;
			
	dxMng.m_pDrawSurface->ReleaseDC(pDC);
}

BOOL CChildView::FieldCheck(CPoint pt, int x, int y, RECT* pRC, WORD* data)
{
	CPoint ptCheck;
	ptCheck = pt - CPoint( 10, 80);
	if(LineCheck(ptCheck, x, y, pRC, data))return TRUE;
	ptCheck = pt - CPoint( -10, 80);
	if(LineCheck(ptCheck, x, y, pRC, data))return TRUE;

	return FALSE;
}

BOOL CChildView::LineCheck(CPoint pt, int x, int y, RECT* pRC, WORD* data)
{
	if(data == NULL) return FALSE;
	if(pRC == NULL) return FALSE;

	CRect rcScreen = CRect(0,0,800,600);
	if( !rcScreen.PtInRect(pt) ) return FALSE; 
	if(pRC->right - pRC->left <= 0 || pRC->bottom - pRC->top <= 0) return FALSE; // ��ȿ�� �ȼ��� ������ ���ư���..
	CRect rc = CRect(x+pRC->left, y+pRC->top, x+pRC->right, y+pRC->bottom);

	int width = pt.x - rc.left;
	int height = rc.bottom - rc.top;

	int nNode; // �Ѷ��δ� ����..
	int nZeroCount = 0; // �ǳʶٴ� �ȼ��� ����
	int nCopyCount = 0; // ������ �ȼ��� ����
	int Sgap=0;
	int Egap=0;

	const WORD* pSrc = data; 

	int clip_height= pt.y - rc.top;

	if( clip_height > 0 )
	{
		for(int i = 0; i < clip_height; i++) // ��ŵ �ټ�..
		{
			nNode = *pSrc; pSrc++; // ����;
			for(;nNode; nNode--)
			{
				pSrc++; // 0 �� ����
				pSrc += *pSrc + 1; // ��ȿ �ȼ� ����
			}
		}
	}
	for( int ii = 0 ; ii < 90 ; ii++ )
	{
		pt.y += 1;
		if( !rc.PtInRect( pt ) ) continue;
		else
		{
			nNode = *pSrc;pSrc++;
			Sgap = *pSrc;
			for(;nNode; nNode-- )
			{
				nZeroCount = *pSrc;pSrc++;
				nCopyCount = *pSrc;pSrc += *pSrc + 1;
				Egap += (nZeroCount + nCopyCount);
			}
			if( Sgap < width && width <= Egap ) return TRUE;
			nZeroCount = nCopyCount = Egap = 0;
		}

	}
	return FALSE;


}


void CChildView::DrawObjEx(int limit_y, CPoint org_pos, CPoint offset_pos, CPoint x_range, BOOL bAbove)
{
	short int nData, nSet = 0, nSubSet = 0, nComparison_nData = 0;
	const _SPR_LSP* pSpr = NULL;

	//for(int y = Cell_Y-1; y < Cell_Y + 17+10; y++) // �ٴڿ� �򸮴� ��
	for(int y = m_limit_old_y; y < limit_y; y++) // �ٴڿ� �򸮴� ��
	{
		for(int x = x_range.x; x < x_range.y; x++)
		{
			nData = MapObj.DataGet(x, y);
			nSet = nData >> 8; // ��Ʈ ��ȣ�� ���� ����Ʈ �̴�.
			if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) continue; // �迭 ���� üũ
			nSubSet = nData & 0x00ff; // ���� ��Ʈ ��ȣ�� ���� ����Ʈ

			// ani....�Ʒ� ���� ���Ҵ�...�̻��ؼ�..
//				MapAniObjs[nSet].AniSet(nSubSet, FL_ANI_LOOP, nSubSet); // ���ϸ��̼� �������ְ�
//				MapAniObjs[nSet].SprGetAnimated(&pSpr, nSubSet);
//				if(pSpr == NULL) continue; // ��������Ʈ �����Ͱ� ������ ��������.

			//����..
//			int nSpr = MapAniObjs[nSet].FrmGetByAniAndDirAndSeq(, 0, 0);
			// ���ϸ��̼�
			int nSpr = MapAniObjs[nSet].FrmGetAnimated(nSubSet);
			MapAniObjs[nSet].SprGet(nSpr, &pSpr);
			if(pSpr == NULL) // 9.28 �� ������Ʈ ��������Ʈ�� ������ �б⸦ �õ��Ѵ�.
			{
//				CString szPreFN;
				CString szFN = "map\\object\\";
				szFN += CChildView::MapObj.m_Header.szRegObjAniFNs[nSet]; // ���ϸ��̼� ���� �б�
				MapAniObjs[nSet].AniLoad(szFN);
				MapAniObjs[nSet].AniCtrlAlloc(256);
				szFN = "map\\object\\";
//				szPreFN = CChildView::MapObj.m_Header.szRegObjSprFNs[nSet];
				szFN += CChildView::MapObj.m_Header.szRegObjSprFNs[nSet];

/*
//				CString szFHN = "bld";
//				if( szPreFN.Left(3) == szFHN )
				if(MapObj.GetAddAlpha( nSet )) 
				{
					//DirectXMng.m_p3D->D3DCreateTextureEx( szFN.GetBuffer(0) );
					//MapAniObjs[nSet].SprLoad(szFN, 1); // ��������Ʈ ���� �б�.
					//MapShadowAniObjs[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
					MapAniObjs[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
				}
				else
					MapAniObjs[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
*/
				MapAniObjs[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
				// �ٽ� �ѹ� ��������Ʈ �����͸� �������� �õ�. 
				nSpr = MapAniObjs[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
				MapAniObjs[nSet].SprGet(nSpr, &pSpr);
				if(pSpr == NULL) continue;
			}
			
//			CString szFHN = "bld";//this
//			CString szPreFN = CChildView::MapObj.m_Header.szRegObjSprFNs[nSet];
//			szPreFN.MakeLower(); 

			CUser *pSorUser = UserManager.GetUserWithUid( m_iMyId );
			if( pSorUser )
			{
				CRect rc = pSpr->rcV;
				CPoint pt =  pSorUser->GetPosition() - MapManager.GetMapStartPos() ; 
				CPoint ptRegion;
				CPoint ptOffset;
				ptOffset.x = ((x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16);
				ptOffset.y = ((y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16);
				//rc.OffsetRect( ((x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16) , ((y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16) );
				rc.OffsetRect( ptOffset.x , ptOffset.y );
				//rc.SetRect( rc.left, rc.top + 15, rc.right, rc.bottom - 20 );
				rc.SetRect( rc.left, rc.top, rc.right, rc.bottom - 20 );
				BOOL bCovered = rc.PtInRect( pt );
				if( bCovered && !bAbove )
				{
					for( int ii = 1 ; ii < 9 ; ii++ )
					{
						ptRegion.x = pt.x;
						ptRegion.y = pt.y - 10*ii;
						if( rc.PtInRect(ptRegion) )
						{
							if( UserManager.m_nCoverDegree < ii )
								UserManager.m_nCoverDegree = ii;
//							UserManager.m_nCoverDegree = ii;
						}
						else break;
					}
				}
				
				RECT rcV = pSpr->rcV;
				if( bCovered && FieldCheck( pt, ptOffset.x, ptOffset.y, &rcV, pSpr->pwV ))
				{
					nComparison_nData = nData;
					UserManager.m_bMyCovered = bCovered; 
				}
			}

//			if( szPreFN.Left(3) == szFHN )//this
			if(MapObj.GetAddAlpha( nSet )) 
			{
//				CString szFN = "map\\object\\";
//				szFN += CChildView::MapObj.m_Header.szRegObjSprFNs[nSet];
				// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
//				DirectXMng.m_p3D->D3DRenderEx( szFN.GetBuffer(0),  (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, nSpr );
				RECT rcV = pSpr->rcV;
				// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
				CUser *tmpUser = UserManager.GetMe();
				PWORD wpV = pSpr->pwV;				
				//tmpUser->BltLSPTrans(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV,16);
				tmpUser->BltLSPAlphaAdd(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);

			}
			else
			{
				RECT rcV = pSpr->rcV;
				// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
				CUser *tmpUser = UserManager.GetMe();
				PWORD wpV = pSpr->pwV;
				if( UserManager.m_bMyCovered && nComparison_nData == nData )
				{
					if( MapObj.GetHalfAlpha( nSet ) )
					{
						UserManager.m_bMyCovered = FALSE;
						tmpUser->BltLSPHalfAlpha(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV,DirectXMng.m_dwHalf16Mask, DirectXMng.m_dwHalf32Mask);
					}
					else
						//tmpUser->BltLSPNormal(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);
						tmpUser->BltLSPDrawObj(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);
				}
				else
					//tmpUser->BltLSPNormal(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);
					tmpUser->BltLSPDrawObj(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);
			}
		}//for(int x = x_range.x; x < x_range.y; x++)
	}
//	m_limit_old_y = limit_y;
}

void CChildView::DrawHouseIn(int x, int y, CPoint org_pos, CPoint offset_pos, BOOL bAbove)
{
	short int nData, nSet = 0, nSubSet = 0, nComparison_nData = 0;
	const _SPR_LSP* pSpr = NULL;

	nData = MapHouseIn.DataGet(x, y);
	nSet = nData >> 8; // ��Ʈ ��ȣ�� ���� ����Ʈ �̴�.
	if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) return; // �迭 ���� üũ
	nSubSet = nData & 0x00ff; // ���� ��Ʈ ��ȣ�� ���� ����Ʈ

	// ���ϸ��̼�
	int nSpr = MapAniHouseIn[nSet].FrmGetAnimated(nSubSet);
	MapAniHouseIn[nSet].SprGet(nSpr, &pSpr);
	if(pSpr == NULL) // 9.28 �� ������Ʈ ��������Ʈ�� ������ �б⸦ �õ��Ѵ�.
	{
//#ifdef _DEBUG
//		DWORD STLOAD = GetTickCount();
//#endif
		CString szFN = "map\\object\\";
		szFN += CChildView::MapHouseIn.m_Header.szRegObjAniFNs[nSet]; // ���ϸ��̼� ���� �б�
		MapAniHouseIn[nSet].AniLoad(szFN);
		MapAniHouseIn[nSet].AniCtrlAlloc(256);
		szFN = "map\\object\\";
		szFN += CChildView::MapHouseIn.m_Header.szRegObjSprFNs[nSet];

		MapAniHouseIn[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
		// �ٽ� �ѹ� ��������Ʈ �����͸� �������� �õ�. 
		nSpr = MapAniHouseIn[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
		MapAniHouseIn[nSet].SprGet(nSpr, &pSpr);
		if(pSpr == NULL) return;
//#ifdef _DEBUG
//		DWORD ENDLOAD = GetTickCount();
//		TRACE("���ε��ð� %d%s\n",ENDLOAD-STLOAD,szFN);
//#endif
	}

	CPoint ptMapOffset = CChildView::MapManager.GetMapStartPos();
	CPoint pt_house_center;

	pt_house_center.x = x << 5;
	pt_house_center.y = y << 5;

	LIGHT_INFO LI;
	LI.m_kind = 2;
	LI.m_pt = pt_house_center - ptMapOffset;
	CChildView::m_ptLightPos.Add( LI );
	
	CUser *pSorUser = UserManager.GetUserWithUid( m_iMyId );
	if( pSorUser )
	{
		CRect rc = pSpr->rcV;
		CPoint pt =  pSorUser->GetPosition() - MapManager.GetMapStartPos() ; 
		CPoint ptRegion;
		CPoint ptOffset;
		ptOffset.x = ((x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16);
		ptOffset.y = ((y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16);
		rc.OffsetRect( ptOffset.x , ptOffset.y );
		rc.SetRect( rc.left, rc.top, rc.right, rc.bottom - 20 );
		BOOL bCovered = rc.PtInRect( pt );
/*
		if( bCovered && !bAbove )
		{
			for( int ii = 1 ; ii < 9 ; ii++ )
			{
				ptRegion.x = pt.x;
				ptRegion.y = pt.y - 10*ii;
				if( rc.PtInRect(ptRegion) )
				{
					if( UserManager.m_nCoverDegree < ii )
						UserManager.m_nCoverDegree = ii;
//					UserManager.m_nCoverDegree = ii;
				}
				else break;
			}
		}
*/		
		RECT rcV = pSpr->rcV;
		if( bCovered && FieldCheck( pt, ptOffset.x, ptOffset.y, &rcV, pSpr->pwV ))
		{
			nComparison_nData = nData;
			UserManager.m_bMyCovered = bCovered; 
		}
	}

	if(MapHouseIn.GetAddAlpha( nSet )) 
	{
		RECT rcV = pSpr->rcV;
		CUser *tmpUser = UserManager.GetMe();
		PWORD wpV = pSpr->pwV;				
		tmpUser->BltLSPAlphaAdd(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);

	}
	else
	{
		RECT rcV = pSpr->rcV;
		// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
		CUser *tmpUser = UserManager.GetMe();
		PWORD wpV = pSpr->pwV;
		if( UserManager.m_bMyCovered && nComparison_nData == nData )
		{
			if( MapHouseIn.GetHalfAlpha( nSet ) )
			{
				UserManager.m_bMyCovered = FALSE;
				tmpUser->BltLSPHalfAlpha(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV,DirectXMng.m_dwHalf16Mask, DirectXMng.m_dwHalf32Mask);
			}
			else
				tmpUser->BltLSPDrawObj(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);
		}
		else
			tmpUser->BltLSPDrawObj(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);
	}

	m_limit_old_y = y+1;
}


void CChildView::BackLoadingEx(CPoint pos)
{
	int Cell_X = (pos.x >> 5);
	int Cell_Y = (pos.y >> 5);
	int i, j, k, l;
	short int nData, nSet = 0, nSubSet = 0;
	const _SPR_LSP* pSpr = NULL;
	CRect t_rect;

	for(l = 0; l < g_MapPosCount; l++)
	{
		if(Cell_X >= g_MapPos[l].left &&
			Cell_Y >= g_MapPos[l].top &&
			Cell_X < g_MapPos[l].right &&
			Cell_Y < g_MapPos[l].bottom)
		{
			t_rect.left = g_MapPos[l].left - 25;
			t_rect.top = g_MapPos[l].top - 16;
			t_rect.right = g_MapPos[l].right;
			t_rect.bottom = g_MapPos[l].bottom;

			g_vLoadingRect.left = g_MapPos[l].left;
			g_vLoadingRect.top = g_MapPos[l].top;
			g_vLoadingRect.right = g_MapPos[l].right;
			g_vLoadingRect.bottom = g_MapPos[l].bottom;

			if(g_MapLoading[l] == TRUE)
			{
				int a_size = g_MapRsc[l].GetSize();
				for(int a = 0; a < a_size; a++)
				{
					_TILE_SET_TOOL *tile_set_tool;
					
					tile_set_tool = TileSetTool.GetTileSet(g_MapRsc[l][a]);
					if(tile_set_tool->m_lpDDSs == NULL)
					{
						CString szBMPFN = tile_set_tool->m_HTSs.szBMPFN;
						CString szHFN = "house";
						if(szBMPFN.GetLength() > 0)
						{
							szBMPFN = szBMPFN.Left(szBMPFN.GetLength() - 3);
							g_pTEng.PathSetCur("BMP");
							
							if( szBMPFN.Left(5) == szHFN )
							tile_set_tool->m_lpDDSs = g_pTEng.SurfaceCreateWithBMP(szBMPFN + "obm", FALSE, tile_set_tool->m_HTSs.crCK,TRUE);
							else
							tile_set_tool->m_lpDDSs = g_pTEng.SurfaceCreateWithBMP(szBMPFN + "obm", FALSE, tile_set_tool->m_HTSs.crCK);
							if(tile_set_tool->m_lpDDSs == NULL)
							{
								tile_set_tool->m_lpDDSs = g_pTEng.SurfaceCreateWithBMP(szBMPFN + "bmp", FALSE, tile_set_tool->m_HTSs.crCK);
								if(tile_set_tool->m_lpDDSs)
								{
									TRACE("%s ����\n", szBMPFN + "bmp");
								}
								else continue;
							}
							else
							{
								TRACE("BackLoadingEx:%s ����(%ld)\n", szBMPFN + "obm", g_vRenderTime);
							}
						}
					}
					tile_set_tool->m_vUseTime = g_vRenderTime;
				}
				break;
			}
			g_MapLoading[l] = TRUE;
			for(i = t_rect.top; i < t_rect.bottom; i++)
			{
				for(j = t_rect.left; j < t_rect.right; j++)
				{
					// Ÿ�� �б�
					for(k = 0; k < 3; k++)
					{
						const _TILE_MAP_DATA_TOOL* pTMData = TileMapTool.ToolDataGet(k, j, i);
						if(pTMData == NULL) continue;
						_TILE_SET_TOOL *tile_set_tool = TileSetTool.GetTileSet(pTMData->snTS);
						if(tile_set_tool == NULL) continue;
						if(tile_set_tool->m_lpDDSs == NULL)
						{
							CString szBMPFN = tile_set_tool->m_HTSs.szBMPFN;
							CString szHFN = "house";
							if(szBMPFN.GetLength() > 0)
							{
								g_MapRsc[l].Add(pTMData->snTS);
								szBMPFN = szBMPFN.Left(szBMPFN.GetLength() - 3);
								g_pTEng.PathSetCur("BMP");
								
								if( szBMPFN.Left(5) == szHFN )
								tile_set_tool->m_lpDDSs = g_pTEng.SurfaceCreateWithBMP(szBMPFN + "obm", FALSE, tile_set_tool->m_HTSs.crCK,TRUE);
								else
								tile_set_tool->m_lpDDSs = g_pTEng.SurfaceCreateWithBMP(szBMPFN + "obm", FALSE, tile_set_tool->m_HTSs.crCK);
								if(tile_set_tool->m_lpDDSs == NULL)
								{
									tile_set_tool->m_lpDDSs = g_pTEng.SurfaceCreateWithBMP(szBMPFN + "bmp", FALSE, tile_set_tool->m_HTSs.crCK);
									if(tile_set_tool->m_lpDDSs)
									{
										TRACE("%s ����\n", szBMPFN + "bmp");
									}
									else continue;
								}
								else
								{
									TRACE("BackLoadingEx:%s ����(%ld)\n", szBMPFN + "obm", g_vRenderTime);
								}
							}
						}
						tile_set_tool->m_vUseTime = g_vRenderTime;
					}
					// Object �б�
					nData = MapObj.DataGet(j, i);
					nSet = nData >> 8;
					if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) continue;
					nSubSet = nData & 0x00ff;
					// Object �б�
					int nSpr = MapAniObjs[nSet].FrmGetAnimated(nSubSet);
					MapAniObjs[nSet].SprGet(nSpr, &pSpr);
					if(pSpr == NULL)
					{
						CString szPreFN;
						CString szFN = "map\\object\\";
						szFN += CChildView::MapObj.m_Header.szRegObjAniFNs[nSet]; // ���ϸ��̼� ���� �б�
						MapAniObjs[nSet].AniLoad(szFN);
						MapAniObjs[nSet].AniCtrlAlloc(256);
						szFN = "map\\object\\";
						szPreFN = CChildView::MapObj.m_Header.szRegObjSprFNs[nSet];
						szFN += CChildView::MapObj.m_Header.szRegObjSprFNs[nSet];


						CString szFHN = "bld";//this
						szPreFN.MakeLower(); 
						if( szPreFN.Left(3) == szFHN )//this
						{
							DirectXMng.m_p3D->D3DCreateTextureEx( szFN.GetBuffer(0) );
							MapAniObjs[nSet].SprLoad(szFN, 1);
//							MapAniObjs[nSet].SprLoad(szFN, g_pTEng.m_nPF);
						}
						else
							MapAniObjs[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
						// �ٽ� �ѹ� ��������Ʈ �����͸� �������� �õ�. 
						nSpr = MapAniObjs[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
						MapAniObjs[nSet].SprGet(nSpr, &pSpr);
						if(pSpr == NULL) continue;
					}
					nData = MapShadowObj.DataGet(j, i);
					nSet = nData >> 8;
					if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) continue;
					nSubSet = nData & 0x00ff;
					// �׸��� �б�
					nSpr = MapAniObjs[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
					MapAniObjs[nSet].SprGet(nSpr, &pSpr);
					if(pSpr == NULL)
					{
						if(CChildView::MapShadowObj.m_Header.szRegObjSprFNs[nSet][0] == 0) continue;

						CString szFN = "map\\object\\";
						szFN += CChildView::MapShadowObj.m_Header.szRegObjAniFNs[nSet];
						MapShadowAniObjs[nSet].AniLoad(szFN);
						MapShadowAniObjs[nSet].AniCtrlAlloc(256);
						szFN = "map\\object\\";
						szFN += CChildView::MapShadowObj.m_Header.szRegObjSprFNs[nSet];

						if( DirectXMng.m_bHalEnabled )
						{
							DirectXMng.m_p3D->D3DCreateTextureEx( szFN.GetBuffer(0) );
							MapShadowAniObjs[nSet].SprLoad(szFN, 1); // ��������Ʈ ���� �б�.
//							MapShadowAniObjs[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
						}
						else
							MapShadowAniObjs[nSet].SprLoad(szFN, 0);
						nSpr = MapShadowAniObjs[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
						MapShadowAniObjs[nSet].SprGet(nSpr, &pSpr);
						if(pSpr == NULL) continue;
					}
				}
			}
			break;
		}
	}
/*
	// Ÿ�� ����
	POSITION position = TileSetTool.m_mapData.GetStartPosition();
	int key;
	_TILE_SET_TOOL *value;
	
	while(position)
	{
		TileSetTool.m_mapData.GetNextAssoc(position, key, value);
		if(value->m_lpDDSs && g_vRenderTime - value->m_vUseTime > 100000)
		{
			TRACE("%s ����\n", value->m_HTSs.szBMPFN);
			value->m_lpDDSs->Release();
			value->m_lpDDSs = NULL;
		}
	}
*/	
}

void CChildView::ArrangeTileResource()
{
	DWORD cur_tick = GetTickCount();
	static DWORD old_tick = cur_tick;

	if(cur_tick - old_tick > 30000)
	{
		POSITION position = TileSetTool.m_mapData.GetStartPosition();
		int key;
		_TILE_SET_TOOL *value;
		
		while(position)
		{
			TileSetTool.m_mapData.GetNextAssoc(position, key, value);
			if(value->m_lpDDSs && cur_tick - value->m_vUseTime > 600000)
			{
				TRACE("%s ����(%ld,%ld)\n", value->m_HTSs.szBMPFN, cur_tick, value->m_vUseTime);
				value->m_lpDDSs->Release();
				value->m_lpDDSs = NULL;
			}
		}
		old_tick = cur_tick;
	}
}

void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(m_pBBDX_Editor->GetFocusStatus() == FALSE)
	{
		if(nChar >= 32 && nChar <= 126)
		{
			m_pBBDX_Editor->SetFocus();
			m_pBBDX_Editor->PostMessage(WM_CHAR, (WPARAM)nChar, MAKELPARAM(nFlags, nRepCnt));
			return;
		}
	}
	
	CWnd ::OnChar(nChar, nRepCnt, nFlags);
}

LRESULT CChildView::OnImeStartComposition(WPARAM wParam, LPARAM lParam)
{
	if(m_pBBDX_Editor->GetFocusStatus() == FALSE)
	{
		m_pBBDX_Editor->SetFocus();
		m_pBBDX_Editor->PostMessage(WM_IME_STARTCOMPOSITION, wParam, lParam);
	}

	return 1;
}

LRESULT CChildView::OnImeComposition(WPARAM wParam, LPARAM lParam)
{
	if(m_pBBDX_Editor->GetFocusStatus() == TRUE)
	{
		m_pBBDX_Editor->PostMessage(WM_IME_COMPOSITION, wParam, lParam);
	}

	return 1;
}

LRESULT CChildView::OnImeEndComposition(WPARAM wParam, LPARAM lParam)
{
	if(m_pBBDX_Editor->GetFocusStatus() == TRUE)
	{
		m_pBBDX_Editor->PostMessage(WM_IME_ENDCOMPOSITION, wParam, lParam);
	}

	return 1;
}

LRESULT CChildView::OnImeCompositionFull(WPARAM wParam, LPARAM lParam)
{
	if(m_pBBDX_Editor->GetFocusStatus() == TRUE)
	{
		m_pBBDX_Editor->PostMessage(WM_IME_COMPOSITIONFULL, wParam, lParam);
	}

	return 1;
}

void CChildView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar < 255) m_bKeyDown[nChar] = 0;

	switch(nChar)
	{
		case VK_CONTROL: m_bCtrlUp = true;	break;
		default:
			    break;
	}
	
	CWnd ::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CChildView::OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if(nChar < 255) m_bKeyDown[nChar] = 0;
	
	CWnd ::OnSysKeyUp(nChar, nRepCnt, nFlags);
}

void CChildView::SendLivePacket()
{
	CMsg msgSend;
	msgSend.ID(SM_ALIVE_ACK);
	CChildView::SocketMng.SendRawPacket(msgSend.GetSize(), (PBYTE)msgSend.GetBuf());
}

void CChildView::Notice(PBYTE bypData)
{
	MSG msg;
	bool bSuccess = false;
//	if(GDialog_AccountLogin) SAFE_DELETE(GDialog_AccountLogin);
	CNotice *notice = new CNotice;

	notice->ShowWindow();
	notice->AddString(bypData);
	bool  bOk = true;

	BBDX_MouseInformation* pMouseInfo = NULL;

	while(bOk) 
	{
		if (::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			switch(msg.message)
			{
			case WM_QUIT:
				AfxPostQuitMessage(0);
				SAFE_DELETE(notice); //�켮.
				bOk = false;
				break;

			case WM_KEYDOWN:
				if(msg.wParam == VK_RETURN)
				{
					bOk = false; bSuccess = true;
				}
				break;
			}
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}
		else
		{
			if (DirectXMng.MouseInfoUpdate())
			{
				pMouseInfo = DirectXMng.GetMouseInfoPtr();
				ASSERT(pMouseInfo);
			}
			notice->MouseProcess(pMouseInfo);
			notice->Draw(CChildView::DirectXMng.m_pDrawSurface);
			if(notice->m_bExit) { bOk = false; bSuccess = true; }

			DirectXMng.Flip();
		}
	}

	CMsg t_msg;

	t_msg.ID(SM_UPGRADING_ACK);
	CChildView::SocketMng.SendRawPacket(t_msg.GetSize(), (PBYTE)t_msg.GetBuf());

//	SetFocus();
	if(notice) { delete notice; notice = NULL; }
}

void CChildView::RemoveUnUseLSP()
{
	for( int i =0 ; i < MAX_MAP_OBJ_REG ; i++ )
	{
		MapAniObjs[i].RemoveUnUseSpr();
		MapShadowAniObjs[i].RemoveUnUseSpr();
		MapAniHouseIn[i].RemoveUnUseSpr();
		MapAniHouseOut[i].RemoveUnUseSpr();
	}
}
CPoint CChildView::DrawMyInObj(int limit_y, CPoint org_pos, CPoint offset_pos, CPoint x_range, BOOL bAbove)
{
	CPoint pt = CPoint(-1,-1);
	CPoint ptCheck;
	for(int y = m_limit_old_y; y < limit_y; y++) // �ٴڿ� �򸮴� ��
	{
		DrawCommonObj( y, org_pos, offset_pos, x_range, bAbove);
		ptCheck = DrawMyInHouseAndInCheck( y, org_pos, offset_pos, x_range, bAbove);
		if( ptCheck != pt )
		{
			m_limit_old_y = y+1;
			return ptCheck;
		}
	}
	m_limit_old_y = limit_y;
	return ptCheck;
}

void CChildView::DrawCommonObj(int y, CPoint org_pos, CPoint offset_pos, CPoint x_range, BOOL bAbove)
{
	short int nData, nSet = 0, nSubSet = 0, nComparison_nData = 0;
	const _SPR_LSP* pSpr = NULL;

	for(int x = x_range.x; x < x_range.y; x++)
	{
		nData = MapObj.DataGet(x, y);
		nSet = nData >> 8;
		if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) continue;
		nSubSet = nData & 0x00ff;

		int nSpr = MapAniObjs[nSet].FrmGetAnimated(nSubSet);
		MapAniObjs[nSet].SprGet(nSpr, &pSpr);
		if(pSpr == NULL)
		{
			CString szFN = "map\\object\\";
			szFN += CChildView::MapObj.m_Header.szRegObjAniFNs[nSet]; // ���ϸ��̼� ���� �б�
			MapAniObjs[nSet].AniLoadEx(szFN,TRUE);
			MapAniObjs[nSet].AniCtrlAllocEx(256,TRUE);
			szFN = "map\\object\\";
			szFN += CChildView::MapObj.m_Header.szRegObjSprFNs[nSet];
			nSpr = MapAniObjs[nSet].FrmGetAnimated(nSubSet);
			MapAniObjs[nSet].SprLoadEx(szFN, g_pTEng.m_nPF, nSpr); // ��������Ʈ ���� �б�.
			MapAniObjs[nSet].SprGet(nSpr, &pSpr);
			if(pSpr == NULL) continue;
		}
		
		CUser *pSorUser = UserManager.GetUserWithUid( m_iMyId );
		if( pSorUser )
		{
			CRect rc = pSpr->rcV;
			CPoint pt =  pSorUser->GetPosition() - MapManager.GetMapStartPos() ; 
			CPoint ptRegion;
			CPoint ptOffset;
			ptOffset.x = ((x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16);
			ptOffset.y = ((y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16);
			rc.OffsetRect( ptOffset.x , ptOffset.y );
			rc.SetRect( rc.left, rc.top, rc.right, rc.bottom - 20 );
			BOOL bCovered = rc.PtInRect( pt );
			if( bCovered && !bAbove )
			{
				for( int ii = 1 ; ii < 9 ; ii++ )
				{
					ptRegion.x = pt.x;
					ptRegion.y = pt.y - 10*ii;
					if( rc.PtInRect(ptRegion) )
					{
						if( UserManager.m_nCoverDegree < ii )
							UserManager.m_nCoverDegree = ii;
					}
					else break;
				}
			}
			
			RECT rcV = pSpr->rcV;
			if( bCovered && FieldCheck( pt, ptOffset.x, ptOffset.y, &rcV, pSpr->pwV ))
			{
				nComparison_nData = nData;
				UserManager.m_bMyCovered = bCovered; 
			}
		}

		if(MapObj.GetAddAlpha( nSet )) 
		{
			RECT rcV = pSpr->rcV;
			// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
			CUser *tmpUser = UserManager.GetMe();
			PWORD wpV = pSpr->pwV;				
			tmpUser->BltLSPAlphaAdd(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);

		}
		else
		{
			RECT rcV = pSpr->rcV;
			// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
			CUser *tmpUser = UserManager.GetMe();
			PWORD wpV = pSpr->pwV;
			if( UserManager.m_bMyCovered && nComparison_nData == nData && !bAbove )
			{
				UserManager.m_bMyCovered = FALSE;

				int key = x*1000 + y;
				BOOL bHalfed = FALSE;
				int trans_degree;
				if( m_TrnasObj.TransDegree(key,&trans_degree,&bHalfed,TRUE) )
				{
					if( !bHalfed )
					{
						tmpUser->BltLSPBitStepTrans(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV, trans_degree, 32 - trans_degree);
					}
					else
						tmpUser->BltLSPHalfAlphaEx(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV,DirectXMng.m_dwHalf16Mask, DirectXMng.m_dwHalf32Mask);
				}
				else
					tmpUser->BltLSPHalfAlphaEx(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV,DirectXMng.m_dwHalf16Mask, DirectXMng.m_dwHalf32Mask);
			}
			else
			{
				int key = x*1000 + y;
				BOOL bHalfed = FALSE;
				int trans_degree;
				if( m_TrnasObj.TransDegree(key,&trans_degree,&bHalfed,FALSE) )
				{
					tmpUser->BltLSPBitStepTrans(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV, trans_degree, 32 - trans_degree);
				}
				else
					tmpUser->BltLSPDrawObj(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);
			}
		}
	}//for(int x = x_range.x; x < x_range.y; x++)
}

CPoint CChildView::DrawMyInHouseAndInCheck(int y, CPoint org_pos, CPoint offset_pos, CPoint x_range, BOOL bAbove)
{
	short int nData, nSet = 0, nSubSet = 0, nComparison_nData = 0;
	const _SPR_LSP* pSpr = NULL;

	for(int x = x_range.x; x < x_range.y; x++)
	{
		nData = MapHouseOut.DataGet(x, y);
		nSet = nData >> 8; // ��Ʈ ��ȣ�� ���� ����Ʈ �̴�.
		if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) continue; // �迭 ���� üũ
		nSubSet = nData & 0x00ff; // ���� ��Ʈ ��ȣ�� ���� ����Ʈ

		// ���ϸ��̼�
		int nSpr = MapAniHouseOut[nSet].FrmGetAnimated(nSubSet);
		MapAniHouseOut[nSet].SprGet(nSpr, &pSpr);
		if(pSpr == NULL) // 9.28 �� ������Ʈ ��������Ʈ�� ������ �б⸦ �õ��Ѵ�.
		{
//#ifdef _DEBUG
//			DWORD STLOAD = GetTickCount();
//#endif
			CString szFN = "map\\object\\";
			szFN += CChildView::MapHouseOut.m_Header.szRegObjAniFNs[nSet]; // ���ϸ��̼� ���� �б�
			MapAniHouseOut[nSet].AniLoad(szFN);
			MapAniHouseOut[nSet].AniCtrlAlloc(256);
			szFN = "map\\object\\";
			szFN += CChildView::MapHouseOut.m_Header.szRegObjSprFNs[nSet];

			MapAniHouseOut[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
			// �ٽ� �ѹ� ��������Ʈ �����͸� �������� �õ�. 
			nSpr = MapAniHouseOut[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
			MapAniHouseOut[nSet].SprGet(nSpr, &pSpr);
			if(pSpr == NULL) continue;
//#ifdef _DEBUG
//			DWORD ENDLOAD = GetTickCount();
//			TRACE("���ε��ð� %d%s\n",ENDLOAD-STLOAD,szFN);
//#endif
		}
		
		CUser *pSorUser = UserManager.GetUserWithUid( m_iMyId );
		if( pSorUser )
		{
			CRect rc = pSpr->rcV;
			CPoint pt =  pSorUser->GetPosition() - MapManager.GetMapStartPos() ; 
			CPoint ptRegion;
			CPoint ptOffset;
			ptOffset.x = ((x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16);
			ptOffset.y = ((y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16);
			rc.OffsetRect( ptOffset.x , ptOffset.y );
			rc.SetRect( rc.left, rc.top, rc.right, rc.bottom - 20 );
			BOOL bCovered = rc.PtInRect( pt );
			
			if( bCovered )
			{
				if( m_house.IsChange() )
				{
					CPoint pt = CPoint(x,y);
					m_house.SetHousePoint( pt );
				}
				CPoint ptHouseCellPos(x,y);
				if( m_house.GetHousePoint() == ptHouseCellPos )
				{
					CPoint ptObjCenterPoint(x,y);
					return ptObjCenterPoint;
				}

			}
/*
			if( bCovered && !bAbove )
			{
				for( int ii = 1 ; ii < 9 ; ii++ )
				{
					ptRegion.x = pt.x;
					ptRegion.y = pt.y - 10*ii;
					if( rc.PtInRect(ptRegion) )
					{
						if( UserManager.m_nCoverDegree < ii )
							UserManager.m_nCoverDegree = ii;
					}
					else break;
				}
			}
*/			
			RECT rcV = pSpr->rcV;
			if( bCovered && FieldCheck( pt, ptOffset.x, ptOffset.y, &rcV, pSpr->pwV ))
			{
				nComparison_nData = nData;
				UserManager.m_bMyCovered = bCovered; 
			}
		}

		if(MapHouseOut.GetAddAlpha( nSet ))
		{
			RECT rcV = pSpr->rcV;
			CUser *tmpUser = UserManager.GetMe();
			PWORD wpV = pSpr->pwV;
			tmpUser->BltLSPAlphaAdd(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);
		}
		else
		{
			RECT rcV = pSpr->rcV;
			// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
			CUser *tmpUser = UserManager.GetMe();
			PWORD wpV = pSpr->pwV;
			if( UserManager.m_bMyCovered && nComparison_nData == nData )
			{
//				if( MapHouseOut.GetHalfAlpha( nSet ) )
//				{
					UserManager.m_bMyCovered = FALSE;
					tmpUser->BltLSPHalfAlpha(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV,DirectXMng.m_dwHalf16Mask, DirectXMng.m_dwHalf32Mask);
//				}
//				else
//					tmpUser->BltLSPDrawObj(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);
			}
			else
				tmpUser->BltLSPDrawObj(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);
		}
	}//for(int x = x_range.x; x < x_range.y; x++)

	CPoint pt(-1,-1);
	return pt;
}

void CChildView::DrawMyOutObj(int limit_y, CPoint org_pos, CPoint offset_pos, CPoint x_range, BOOL bAbove)
{
	for(int y = m_limit_old_y; y < limit_y; y++) // �ٴڿ� �򸮴� ��
	{
		DrawCommonObj( y, org_pos, offset_pos, x_range,bAbove);
		DrawMyOutHouse( y, org_pos, offset_pos, x_range,bAbove);
	}
	m_limit_old_y = limit_y;
}

void CChildView::DrawTransOutHouse(int x, int y, CPoint org_pos, CPoint offset_pos, int nAlphaSrc, int nAlphaDst)
{
	short int nData, nSet = 0, nSubSet = 0, nComparison_nData = 0;
	const _SPR_LSP* pSpr = NULL;

	nData = MapHouseOut.DataGet(x, y);
	nSet = nData >> 8; // ��Ʈ ��ȣ�� ���� ����Ʈ �̴�.
	if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) return; // �迭 ���� üũ
	nSubSet = nData & 0x00ff; // ���� ��Ʈ ��ȣ�� ���� ����Ʈ

	// ���ϸ��̼�
	int nSpr = MapAniHouseOut[nSet].FrmGetAnimated(nSubSet);
	MapAniHouseOut[nSet].SprGet(nSpr, &pSpr);
	if(pSpr == NULL) // 9.28 �� ������Ʈ ��������Ʈ�� ������ �б⸦ �õ��Ѵ�.
	{
		CString szFN = "map\\object\\";
		szFN += CChildView::MapHouseOut.m_Header.szRegObjAniFNs[nSet]; // ���ϸ��̼� ���� �б�
		MapAniHouseOut[nSet].AniLoad(szFN);
		MapAniHouseOut[nSet].AniCtrlAlloc(256);
		szFN = "map\\object\\";
		szFN += CChildView::MapHouseOut.m_Header.szRegObjSprFNs[nSet];

		MapAniHouseOut[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
		// �ٽ� �ѹ� ��������Ʈ �����͸� �������� �õ�. 
		nSpr = MapAniHouseOut[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
		MapAniHouseOut[nSet].SprGet(nSpr, &pSpr);
		if(pSpr == NULL) return;
	}
	
	RECT rcV = pSpr->rcV;
	// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
	CUser *tmpUser = UserManager.GetMe();
	PWORD wpV = pSpr->pwV;
	tmpUser->BltLSPBitStepTrans(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV, nAlphaSrc, nAlphaDst);
	//tmpUser->BltLSPHalfAlphaEx(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV,DirectXMng.m_dwHalf16Mask, DirectXMng.m_dwHalf32Mask);

}

void CChildView::DrawMyOutHouse(int y, CPoint org_pos, CPoint offset_pos, CPoint x_range, BOOL bAbove)
{
	short int nData, nSet = 0, nSubSet = 0, nComparison_nData = 0;
	const _SPR_LSP* pSpr = NULL;

		for(int x = x_range.x; x < x_range.y; x++)
		{
			nData = MapHouseOut.DataGet(x, y);
			nSet = nData >> 8; // ��Ʈ ��ȣ�� ���� ����Ʈ �̴�.
			if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) continue; // �迭 ���� üũ
			nSubSet = nData & 0x00ff; // ���� ��Ʈ ��ȣ�� ���� ����Ʈ

			// ���ϸ��̼�
			int nSpr = MapAniHouseOut[nSet].FrmGetAnimated(nSubSet);
			MapAniHouseOut[nSet].SprGet(nSpr, &pSpr);
			if(pSpr == NULL) // 9.28 �� ������Ʈ ��������Ʈ�� ������ �б⸦ �õ��Ѵ�.
			{
//#ifdef _DEBUG
//				DWORD STLOAD = GetTickCount();
//#endif
				CString szFN = "map\\object\\";
				szFN += CChildView::MapHouseOut.m_Header.szRegObjAniFNs[nSet]; // ���ϸ��̼� ���� �б�
				MapAniHouseOut[nSet].AniLoad(szFN);
				MapAniHouseOut[nSet].AniCtrlAlloc(256);
				szFN = "map\\object\\";
				szFN += CChildView::MapHouseOut.m_Header.szRegObjSprFNs[nSet];

				MapAniHouseOut[nSet].SprLoad(szFN, g_pTEng.m_nPF); // ��������Ʈ ���� �б�.
				// �ٽ� �ѹ� ��������Ʈ �����͸� �������� �õ�. 
				nSpr = MapAniHouseOut[nSet].FrmGetByAniAndDirAndSeq(nSubSet, 0, 0);
				MapAniHouseOut[nSet].SprGet(nSpr, &pSpr);
				if(pSpr == NULL) continue;
//#ifdef _DEBUG
//				DWORD ENDLOAD = GetTickCount();
//				TRACE("���ε��ð� %d%s\n",ENDLOAD-STLOAD,szFN);
//#endif
			}
			
			CUser *pSorUser = UserManager.GetUserWithUid( m_iMyId );
			if( pSorUser )
			{
				CRect rc = pSpr->rcV;
				CPoint pt =  pSorUser->GetPosition() - MapManager.GetMapStartPos() ; 
				CPoint ptRegion;
				CPoint ptOffset;
				ptOffset.x = ((x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16);
				ptOffset.y = ((y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16);
				rc.OffsetRect( ptOffset.x , ptOffset.y );
				rc.SetRect( rc.left, rc.top, rc.right, rc.bottom - 20 );
				BOOL bCovered = rc.PtInRect( pt );
/*
				if( bCovered && !bAbove )
				{
					for( int ii = 1 ; ii < 9 ; ii++ )
					{
						ptRegion.x = pt.x;
						ptRegion.y = pt.y - 10*ii;
						if( rc.PtInRect(ptRegion) )
						{
							if( UserManager.m_nCoverDegree < ii )
								UserManager.m_nCoverDegree = ii;
						}
						else break;
					}
				}
*/				
				RECT rcV = pSpr->rcV;
				if( bCovered && FieldCheck( pt, ptOffset.x, ptOffset.y, &rcV, pSpr->pwV ))
				{
					nComparison_nData = nData;
					UserManager.m_bMyCovered = bCovered; 
				}
			}

			if(MapObj.GetAddAlpha( nSet )) 
			{
				RECT rcV = pSpr->rcV;
				CUser *tmpUser = UserManager.GetMe();
				PWORD wpV = pSpr->pwV;				
				tmpUser->BltLSPAlphaAdd(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);

			}
			else
			{
				RECT rcV = pSpr->rcV;
				// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
				CUser *tmpUser = UserManager.GetMe();
				PWORD wpV = pSpr->pwV;
				if( UserManager.m_bMyCovered && nComparison_nData == nData && !bAbove )
				{
					UserManager.m_bMyCovered = FALSE;

//					int key = nData;
					int key = x*1000 + y;

					BOOL bHalfed = FALSE;
					int trans_degree;
					if( m_TrnasObj.TransDegree(key,&trans_degree,&bHalfed,TRUE) )
					{
						if( !bHalfed )
						{
							tmpUser->BltLSPBitStepTrans(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV, trans_degree, 32 - trans_degree);
						}
						else
							tmpUser->BltLSPHalfAlphaEx(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV,DirectXMng.m_dwHalf16Mask, DirectXMng.m_dwHalf32Mask);
					}
					else
						tmpUser->BltLSPHalfAlphaEx(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV,DirectXMng.m_dwHalf16Mask, DirectXMng.m_dwHalf32Mask);
				}
				else
				{
					int key = x*1000 + y;
//					int key = nData;
					BOOL bHalfed = FALSE;
					int trans_degree;
					if( m_TrnasObj.TransDegree(key,&trans_degree,&bHalfed,FALSE) )
					{
						tmpUser->BltLSPBitStepTrans(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV, trans_degree, 32 - trans_degree);
					}
					else
						tmpUser->BltLSPDrawObj(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);
				}
			}
		}//for(int x = x_range.x; x < x_range.y; x++)
}

void CChildView::SetMainMode(int mode)
{
	if(g_vCurMainMode == mode) return;

	g_vCurMainMode = mode;
	if(g_vCurMainMode == 0)
	{
		g_vDispPixSize.cx = 800;
		g_vDispPixSize.cy = 495;
		g_vDispCellSize.cx = (int)(g_vDispPixSize.cx / 32.0 + 0.5) + 1;
		g_vDispCellSize.cy = (int)(g_vDispPixSize.cy / 32.0 + 0.5) + 1;

		Dialog_SmallMain.HideWindow();
		Dialog_Main.ShowWindow();
	}
	else
	{
		g_vDispPixSize.cx = 800;
		g_vDispPixSize.cy = 600;
		g_vDispCellSize.cx = (int)(g_vDispPixSize.cx / 32.0 + 0.5) + 1;
		g_vDispCellSize.cy = (int)(g_vDispPixSize.cy / 32.0 + 0.5) + 1;

		Dialog_Main.HideWindow();
		Dialog_SmallMain.ShowWindow();
	}
}

typedef HRESULT(WINAPI * DIRECTDRAWCREATE)( GUID*, LPDIRECTDRAW*, IUnknown* );
typedef HRESULT(WINAPI * DIRECTDRAWCREATEEX)( GUID*, VOID**, REFIID, IUnknown* );
typedef HRESULT(WINAPI * DIRECTINPUTCREATE)( HINSTANCE, DWORD, LPDIRECTINPUT*,
                                             IUnknown* );

VOID GetDXVersion( DWORD* pdwDXVersion, DWORD* pdwDXPlatform )
{
    HRESULT              hr;
    HINSTANCE            DDHinst = 0;
    HINSTANCE            DIHinst = 0;
    LPDIRECTDRAW         pDDraw  = 0;
    LPDIRECTDRAW2        pDDraw2 = 0;
    DIRECTDRAWCREATE     DirectDrawCreate   = 0;
    DIRECTDRAWCREATEEX   DirectDrawCreateEx = 0;
    DIRECTINPUTCREATE    DirectInputCreate  = 0;
    OSVERSIONINFO        osVer;
    LPDIRECTDRAWSURFACE  pSurf  = 0;
    LPDIRECTDRAWSURFACE3 pSurf3 = 0;
    LPDIRECTDRAWSURFACE4 pSurf4 = 0;

    // First get the windows platform
    osVer.dwOSVersionInfoSize = sizeof(osVer);
    if( !GetVersionEx( &osVer ) )
    {
        (*pdwDXPlatform) = 0;
        (*pdwDXVersion)  = 0;
        return;
    }

    if( osVer.dwPlatformId == VER_PLATFORM_WIN32_NT )
    {
        (*pdwDXPlatform) = VER_PLATFORM_WIN32_NT;

        // NT is easy... NT 4.0 is DX2, 4.0 SP3 is DX3, 5.0 is DX5
        // and no DX on earlier versions.
        if( osVer.dwMajorVersion < 4 )
        {
            (*pdwDXVersion) = 0; // No DX on NT3.51 or earlier
            return;
        }

        if( osVer.dwMajorVersion == 4 )
        {
            // NT4 up to SP2 is DX2, and SP3 onwards is DX3, so we are at least DX2
            (*pdwDXVersion) = 0x200;

            // We're not supposed to be able to tell which SP we're on, so check for dinput
            DIHinst = LoadLibrary( "DINPUT.DLL" );
            if( DIHinst == 0 )
            {
                // No DInput... must be DX2 on NT 4 pre-SP3
                OutputDebugString( "Couldn't LoadLibrary DInput\r\n" );
                return;
            }

            DirectInputCreate = (DIRECTINPUTCREATE)GetProcAddress( DIHinst,
                                                                 "DirectInputCreateA" );
            FreeLibrary( DIHinst );

            if( DirectInputCreate == 0 )
            {
                // No DInput... must be pre-SP3 DX2
                OutputDebugString( "Couldn't GetProcAddress DInputCreate\r\n" );
                return;
            }

            // It must be NT4, DX2
            (*pdwDXVersion) = 0x300;  // DX3 on NT4 SP3 or higher
            return;
        }
        // Else it's NT5 or higher, and it's DX5a or higher: Drop through to
        // Win9x tests for a test of DDraw (DX6 or higher)
    }
    else
    {
        // Not NT... must be Win9x
        (*pdwDXPlatform) = VER_PLATFORM_WIN32_WINDOWS;
    }

    // Now we know we are in Windows 9x (or maybe 3.1), so anything's possible.
    // First see if DDRAW.DLL even exists.
    DDHinst = LoadLibrary( "DDRAW.DLL" );
    if( DDHinst == 0 )
    {
        (*pdwDXVersion)  = 0;
        (*pdwDXPlatform) = 0;
        FreeLibrary( DDHinst );
        return;
    }

    // See if we can create the DirectDraw object.
    DirectDrawCreate = (DIRECTDRAWCREATE)GetProcAddress( DDHinst, "DirectDrawCreate" );
    if( DirectDrawCreate == 0 )
    {
        (*pdwDXVersion)  = 0;
        (*pdwDXPlatform) = 0;
        FreeLibrary( DDHinst );
        OutputDebugString( "Couldn't LoadLibrary DDraw\r\n" );
        return;
    }

    hr = DirectDrawCreate( NULL, &pDDraw, NULL );
    if( FAILED(hr) )
    {
        (*pdwDXVersion)  = 0;
        (*pdwDXPlatform) = 0;
        FreeLibrary( DDHinst );
        OutputDebugString( "Couldn't create DDraw\r\n" );
        return;
    }

    // So DirectDraw exists.  We are at least DX1.
    (*pdwDXVersion) = 0x100;

    // Let's see if IID_IDirectDraw2 exists.
    hr = pDDraw->QueryInterface( IID_IDirectDraw2, (VOID**)&pDDraw2 );
    if( FAILED(hr) )
    {
        // No IDirectDraw2 exists... must be DX1
        pDDraw->Release();
        FreeLibrary( DDHinst );
        OutputDebugString( "Couldn't QI DDraw2\r\n" );
        return;
    }

    // IDirectDraw2 exists. We must be at least DX2
    pDDraw2->Release();
    (*pdwDXVersion) = 0x200;


    ///////////////////////////////////////////////////////////////////////////
    // DirectX 3.0 Checks
    ///////////////////////////////////////////////////////////////////////////

    // DirectInput was added for DX3
    DIHinst = LoadLibrary( "DINPUT.DLL" );
    if( DIHinst == 0 )
    {
        // No DInput... must not be DX3
        OutputDebugString( "Couldn't LoadLibrary DInput\r\n" );
        pDDraw->Release();
        FreeLibrary( DDHinst );
        return;
    }

    DirectInputCreate = (DIRECTINPUTCREATE)GetProcAddress( DIHinst,
                                                        "DirectInputCreateA" );
    if( DirectInputCreate == 0 )
    {
        // No DInput... must be DX2
        FreeLibrary( DIHinst );
        FreeLibrary( DDHinst );
        pDDraw->Release();
        OutputDebugString( "Couldn't GetProcAddress DInputCreate\r\n" );
        return;
    }

    // DirectInputCreate exists. We are at least DX3
    (*pdwDXVersion) = 0x300;
    FreeLibrary( DIHinst );

    // Can do checks for 3a vs 3b here


    ///////////////////////////////////////////////////////////////////////////
    // DirectX 5.0 Checks
    ///////////////////////////////////////////////////////////////////////////

    // We can tell if DX5 is present by checking for the existence of
    // IDirectDrawSurface3. First, we need a surface to QI off of.
    DDSURFACEDESC ddsd;
    ZeroMemory( &ddsd, sizeof(ddsd) );
    ddsd.dwSize         = sizeof(ddsd);
    ddsd.dwFlags        = DDSD_CAPS;
    ddsd.ddsCaps.dwCaps = DDSCAPS_PRIMARYSURFACE;

    hr = pDDraw->SetCooperativeLevel( NULL, DDSCL_NORMAL );
    if( FAILED(hr) )
    {
        // Failure. This means DDraw isn't properly installed.
        pDDraw->Release();
        FreeLibrary( DDHinst );
        (*pdwDXVersion) = 0;
        OutputDebugString( "Couldn't Set coop level\r\n" );
        return;
    }

    hr = pDDraw->CreateSurface( &ddsd, &pSurf, NULL );
    if( FAILED(hr) )
    {
        // Failure. This means DDraw isn't properly installed.
        pDDraw->Release();
        FreeLibrary( DDHinst );
        *pdwDXVersion = 0;
        OutputDebugString( "Couldn't CreateSurface\r\n" );
        return;
    }

    // Query for the IDirectDrawSurface3 interface
    if( FAILED( pSurf->QueryInterface( IID_IDirectDrawSurface3,
                                       (VOID**)&pSurf3 ) ) )
    {
        pDDraw->Release();
        FreeLibrary( DDHinst );
        return;
    }

    // QI for IDirectDrawSurface3 succeeded. We must be at least DX5
    (*pdwDXVersion) = 0x500;


    ///////////////////////////////////////////////////////////////////////////
    // DirectX 6.0 Checks
    ///////////////////////////////////////////////////////////////////////////

    // The IDirectDrawSurface4 interface was introduced with DX 6.0
    if( FAILED( pSurf->QueryInterface( IID_IDirectDrawSurface4,
                                       (VOID**)&pSurf4 ) ) )
    {
        pDDraw->Release();
        FreeLibrary( DDHinst );
        return;
    }

    // IDirectDrawSurface4 was create successfully. We must be at least DX6
    (*pdwDXVersion) = 0x600;
    pSurf->Release();
    pDDraw->Release();


    ///////////////////////////////////////////////////////////////////////////
    // DirectX 6.1 Checks
    ///////////////////////////////////////////////////////////////////////////

    // Check for DMusic, which was introduced with DX6.1
    LPDIRECTMUSIC pDMusic = NULL;
    CoInitialize( NULL );
    hr = CoCreateInstance( CLSID_DirectMusic, NULL, CLSCTX_INPROC_SERVER,
                           IID_IDirectMusic, (VOID**)&pDMusic );
    if( FAILED(hr) )
    {
        OutputDebugString( "Couldn't create CLSID_DirectMusic\r\n" );
        FreeLibrary( DDHinst );
        return;
    }

    // DirectMusic was created successfully. We must be at least DX6.1
    (*pdwDXVersion) = 0x601;
    pDMusic->Release();
    CoUninitialize();
    

    ///////////////////////////////////////////////////////////////////////////
    // DirectX 7.0 Checks
    ///////////////////////////////////////////////////////////////////////////

    // Check for DirectX 7 by creating a DDraw7 object
    LPDIRECTDRAW7 pDD7;
    DirectDrawCreateEx = (DIRECTDRAWCREATEEX)GetProcAddress( DDHinst,
                                                       "DirectDrawCreateEx" );
    if( NULL == DirectDrawCreateEx )
    {
        FreeLibrary( DDHinst );
        return;
    }

    if( FAILED( DirectDrawCreateEx( NULL, (VOID**)&pDD7, IID_IDirectDraw7,
                                    NULL ) ) )
    {
        FreeLibrary( DDHinst );
        return;
    }

    // DDraw7 was created successfully. We must be at least DX7.0
    (*pdwDXVersion) = 0x700;
    pDD7->Release();

    
    ///////////////////////////////////////////////////////////////////////////
    // End of checks
    ///////////////////////////////////////////////////////////////////////////

    // Close open libraries and return
    FreeLibrary( DDHinst );
    
    return;
}
/*
void CChildView::DrawCommonObj(int y, CPoint org_pos, CPoint offset_pos, CPoint x_range, BOOL bAbove)
{
	short int nData, nSet = 0, nSubSet = 0, nComparison_nData = 0;
	const _SPR_LSP* pSpr = NULL;

	for(int x = x_range.x; x < x_range.y; x++)
	{
		nData = MapObj.DataGet(x, y);
		nSet = nData >> 8;
		if(nSet < 0 || nSet > MAX_MAP_OBJ_REG) continue;
		nSubSet = nData & 0x00ff;

		int nSpr = MapAniObjs[nSet].FrmGetAnimated(nSubSet);
		MapAniObjs[nSet].SprGet(nSpr, &pSpr);
		if(pSpr == NULL)
		{
//#ifdef _DEBUG
//			DWORD STLOAD = GetTickCount();
//#endif
			CString szFN = "map\\object\\";
			szFN += CChildView::MapObj.m_Header.szRegObjAniFNs[nSet]; // ���ϸ��̼� ���� �б�
			MapAniObjs[nSet].AniLoadEx(szFN,TRUE);
			MapAniObjs[nSet].AniCtrlAllocEx(256,TRUE);
			szFN = "map\\object\\";
			szFN += CChildView::MapObj.m_Header.szRegObjSprFNs[nSet];
			nSpr = MapAniObjs[nSet].FrmGetAnimated(nSubSet);
			MapAniObjs[nSet].SprLoadEx(szFN, g_pTEng.m_nPF, nSpr); // ��������Ʈ ���� �б�.
			MapAniObjs[nSet].SprGet(nSpr, &pSpr);
			if(pSpr == NULL) continue;
//#ifdef _DEBUG
//			DWORD ENDLOAD = GetTickCount();
//			TRACE("������Ʈ�ε��ð� %d%s\n",ENDLOAD-STLOAD,szFN);
//#endif
		}
		
		CUser *pSorUser = UserManager.GetUserWithUid( m_iMyId );
		if( pSorUser )
		{
			CRect rc = pSpr->rcV;
			CPoint pt =  pSorUser->GetPosition() - MapManager.GetMapStartPos() ; 
			CPoint ptRegion;
			CPoint ptOffset;
			ptOffset.x = ((x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16);
			ptOffset.y = ((y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16);
			rc.OffsetRect( ptOffset.x , ptOffset.y );
			rc.SetRect( rc.left, rc.top, rc.right, rc.bottom - 20 );
			BOOL bCovered = rc.PtInRect( pt );
			if( bCovered && !bAbove )
			{
				for( int ii = 1 ; ii < 9 ; ii++ )
				{
					ptRegion.x = pt.x;
					ptRegion.y = pt.y - 10*ii;
					if( rc.PtInRect(ptRegion) )
					{
						if( UserManager.m_nCoverDegree < ii )
							UserManager.m_nCoverDegree = ii;
					}
					else break;
				}
			}
			
			RECT rcV = pSpr->rcV;
			if( bCovered && FieldCheck( pt, ptOffset.x, ptOffset.y, &rcV, pSpr->pwV ))
			{
				nComparison_nData = nData;
				UserManager.m_bMyCovered = bCovered; 
			}
		}

		if(MapObj.GetAddAlpha( nSet )) 
		{
			RECT rcV = pSpr->rcV;
			// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
			CUser *tmpUser = UserManager.GetMe();
			PWORD wpV = pSpr->pwV;				
			tmpUser->BltLSPAlphaAdd(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);

		}
		else
		{
			RECT rcV = pSpr->rcV;
			// ���� �Լ��� �̿��Ϸ��� �ӽ÷� �̿��Ѵ�.
			CUser *tmpUser = UserManager.GetMe();
			PWORD wpV = pSpr->pwV;
//			if( UserManager.m_bMyCovered && nComparison_nData == nData )
			if( UserManager.m_bMyCovered && nComparison_nData == nData && !bAbove )
			{
//				if( MapObj.GetHalfAlpha( nSet ) )
//				{
					UserManager.m_bMyCovered = FALSE;
					tmpUser->BltLSPHalfAlpha(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV,DirectXMng.m_dwHalf16Mask, DirectXMng.m_dwHalf32Mask);
//				}
//				else
//					tmpUser->BltLSPDrawObj(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);
			}
			else
				tmpUser->BltLSPDrawObj(DirectXMng.m_pDrawSurface, (x-org_pos.x-1)*TILE_SIZE+offset_pos.x+16, (y-org_pos.y-1)*TILE_SIZE+offset_pos.y+16, &rcV, wpV);
		}
	}//for(int x = x_range.x; x < x_range.y; x++)
}
*/
