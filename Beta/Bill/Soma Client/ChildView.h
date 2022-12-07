// ChildView.h : interface of the CChildView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHILDVIEW_H__180690AB_F9A1_11D2_8421_0020AF9F40BD__INCLUDED_)
#define AFX_CHILDVIEW_H__180690AB_F9A1_11D2_8421_0020AF9F40BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//

#include "DirectXMng.h"
#include "SocketMng.h"
#include "CharManager.h"
#include "UserManager.h"
#include "PacketParser.h"
#include "MapManager/SM_MapManager.h"
#include "MagicManager.h"
#include "ArmatureManager.h"
#include "Weather.h"

//#include "IGObject\\DDEngine.h"
#include "IGObject\\DDEngineLSP.h"
#include "IGObject\\MapObj.h"
#include "IGObject\\AniObjLsp.h"
//#include "TestEngine.h"
#include "TileMapTool.h"
#include "TileSetTool.h"

#include "Dialog_AccountLogin.h"
#include "Dialog_Login.h"
#include "SLoadingView.h"

#include "Rain.h"
#include "LightSource.h"
#include "house.h"
#include "TransObj.h"

#define MAX_RAIN 150
//#include "FogEffect.h"


//((���))
//#include "Item.h"
//#include "Item_Arm.h"
//#include "Item_sArm.h"

class BBDX_Editor;
class BBDX_ChatEditor;
class BBDX_ChatOuter;
//�켮.
class CDialog_Login;

//�켮
typedef struct  _tgCharData 
{
	BYTE   IdSize;
	char   *userID;
	short  Class;
	short  Level;
	short  Str;
	short  Dex;
	short  Inteli;
	short  Cha;
	short  Wis;
	short  Con;
	short  Hp;
	short  MaxHp;
	short  Mp;
	short  MaxMp;
	short  Stm;
	short  MaxStm;
	short  Age;
	short  Moral;
	short  Gender;
	short  Hair;
	short  Skin;
	CString  Group;
	short  Fame;
	int    SwordExp;
	int    SpearExp;
	int    BowExp;
	int    AxeExp;
	int    KnuckleExp;
	int    StaffExp;
	int    WeaponMakeExp;
	int    ArmorMakeExp;
	int    AccMakeExp;
	int    PotionMakeExp;
	int    CookingExp;
	short  ItemCheck[10];

public:
	_tgCharData()
	{
		userID = NULL;
	}
	~_tgCharData()
	{
		if(userID) { delete [] userID; userID = NULL; }
	}
}CharData;
//�켮.
#ifndef LIGHTINFO
#define LIGHTINFO
typedef struct TAG_LIGHT_INFO
{
	int m_kind;
	CPoint m_pt;
}LIGHT_INFO;
#endif



/////////////////////////////////////////////////////////////////////////////
// CChildView window

class CChildView : public CWnd
{
// Construction
public:
	CChildView();
	virtual ~CChildView();

// Attributes
public:
	static CUserManager		UserManager;		//User ������ (Server�� ���������� �������-������ ����ȭ)
	static CCharManager		CharManager;		//ĳ���� Resource������
	static DirectXMng		DirectXMng;			//DirctX ������
	static SocketMng		SocketMng;			//Socket ������
	static SM_MapManager	MapManager;			//Map ������
	static CPacketParser	PacketParser;		//������ ���� ���� ��Ŷ �м���
	static CMagicManager	MagicManager;		//Magic Resource ������
	static CArmatureManager	ArmatureManager;	//���� ������ ������
	static CWeather			Weather;

	static CDDEngineNew     g_pTEng;            // ���� ����..
//	static CDDEngineLSP     g_pTEng;            // ���� ����..
	static CTileMapTool     TileMapTool;
	static CTileSetTool     TileSetTool;
	static CMapObj          MapObj;
	static CMapObj          MapShadowObj;
	static CMapObj			MapHouseIn;
	static CMapObj			MapHouseOut;
	static CAniObjLSP		MapAniObjs[MAX_MAP_OBJ_REG];
	static CAniObjLSP		MapShadowAniObjs[MAX_MAP_OBJ_REG];
	static CAniObjLSP		MapAniHouseIn[MAX_MAP_OBJ_REG];
	static CAniObjLSP		MapAniHouseOut[MAX_MAP_OBJ_REG];

	CRain					m_Rain[MAX_RAIN];
	CTransObj				m_TrnasObj;
	static CLightSource		m_LightSource;
	static CArray<LIGHT_INFO,LIGHT_INFO> m_ptLightPos;
	static CFont			*pAppFont;
	static int				bDlgIn;
//	static CFogEffect       FogEffect;          //�Ȱ� ȿ��...

//	static CItem            Item;
//	static CItem_Arm        Item_Arm;

//public:
//	static CItem_Arm        Item_Arm;
//	static CItem_sArm        Item_sArm;

// Operations
	int m_nQtObjNeededRender; // �������� �Ǿ�� ��(ȭ�鳻�� �־�� ��) ������Ʈ ���� : ���� 9.7
	struct _OBJECT_DATA // ĳ���� �����ϰ� �׻��̿� ������Ʈ�� �������ҷ��� ���� ����ü : ���� 9.7
	{
		POINT pt; // ����Ʈ ���� ����ǥ
		int nSet; // ��Ʈ ��ȣ
		int nSubSet; // ����� ��ȣ
	};
	_OBJECT_DATA m_ObjStructs[256]; // ��ȭ�鿡 256 �� ���Ϸ� ����
public:
    int m_S_Connection;// ���ǿ� ����Ǿ� �ִ°�?

	// newAccount 
	CString m_New_Account_ID;
	CString m_New_Account_Passwd, m_New_Account_Passwd2;
	CString m_New_Account_Name;
	CString m_New_Account_SocNo;
	CString m_New_Account_Address;
	CString m_New_Account_TellNo;
	CString m_New_Account_Email;

	bool    m_bAccountNewOk;
	bool    m_bLoginOk;

	// �켮
	SLoadingView	 *m_LoadinView;
	CharData		*m_CharData[3];
	bool			 m_bMakeChar;
	bool			 m_bMakeFail;
	bool			 m_bMakeProcess;
	int				 m_CharNum; //������� ĳ���� ����.

	CString			 m_conIP; //������ ip...

	void  InitChar();
	// �켮.

/*
	BBDX_Editor*	pBBDX_Editor_id;//1
	BBDX_Editor*	pBBDX_Editor_password;//2
	BBDX_Editor*	pBBDX_Editor_password2;//3 �н����� Ȯ��
	BBDX_Editor*	pBBDX_Editor_name;//4
	BBDX_Editor*	pBBDX_Editor_email;//5
	BBDX_Editor*	pBBDX_Editor_number;//6 �ֹι�ȣ
	BBDX_Editor*	pBBDX_Editor_address;//7 �ּ�
	BBDX_Editor*	pBBDX_Editor_phonenumber;//8�� ��ȭ��ȣ
	BBDX_Editor*	pBBDX_Editor_phonenumber2;//9 ����Ǵ� �ڵ���...
*/
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildView)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_limit_old_y;
	void SetOld_limit_y( int limit_y ){ m_limit_old_y = limit_y; }

	void ArrangeTileResource();

	void RemoveUnUseLSP();
	void DrawShawdowObj();
	void DrawShawdowObj(CDDSurface *pSurface);

	void DrawShawdowObjEx();

	void DrawObj(int limit_y);
	void DrawObjEx(int limit_y, CPoint org_pos, CPoint offset_pos, CPoint x_range, BOOL bAbove = FALSE);

	void DrawHouseIn(int x, int y, CPoint org_pos, CPoint offset_pos, BOOL bAbove = FALSE);//���ȳ��� �׷��ֱ�
	CPoint DrawMyInHouseAndInCheck(int y, CPoint org_pos, CPoint offset_pos, CPoint x_range, BOOL bAbove = FALSE);//�� �׷��ֱ� �� �ȿ� ������
	void DrawCommonObj(int y, CPoint org_pos, CPoint offset_pos, CPoint x_range, BOOL bAbove = FALSE);//�Ϲ� ������Ʈ �׸��� 
	CPoint DrawMyInObj(int limit_y, CPoint org_pos, CPoint offset_pos, CPoint x_range, BOOL bAbove = FALSE);//���ȿ� ������ �׷��ִ� �Լ�
	void DrawMyOutObj(int limit_y, CPoint org_pos, CPoint offset_pos, CPoint x_range, BOOL bAbove = FALSE);//���ۿ� ������ �׷��ִ� �Լ�
	void DrawMyOutHouse(int y, CPoint org_pos, CPoint offset_pos, CPoint x_range, BOOL bAbove = FALSE);//���׷��ֱ� ���� ���ۿ� ������ 
	void DrawTransOutHouse(int x, int y, CPoint org_pos, CPoint offset_pos, int nAlphaSrc, int nAlphaDst);


	BOOL FieldCheck(CPoint pt, int x, int y, RECT* pRC, WORD* data);
	BOOL LineCheck(CPoint pt, int x, int y, RECT* pRC, WORD* data);

	CHouse m_house;
	int m_Mouse_In;
	void DrawObject();
	void DrawHousePlace();
	void DrawTile(int type =0);
    int GetItemArmTypeIndex(int i); //�켮.. 10�� 16��..
	int GetItemDrawOrderIndex(int i);
	int GetItemPicIndex(int i);
	void ReadItemIndex();
	void ViewSelectBox(CRect rBox, int color=0);
	void Magic_Draw();
	void Magic_Item_Draw();
	void ChatMode(int type);
	void DrawObjcet();
	void DrawRains();
	void DrawRainDrops();
	void DrawNight();
	void DrawNight1(BOOL bRight);
	void BackLoading(CPoint pos);
	void BackLoadingEx(CPoint pos);

	void SendLivePacket();
	void ClearScreen();
	int m_Old_Item_Type[9];
	static void FieldInfoItemProcess(PBYTE bypData);
	int m_Login_Char;
	void NewCharter();
	void LoginCharterView();
    static  void CharacterDataProcess(PBYTE bypData);
	//�켮.. static -> no static
	void DelHeroProcess(PBYTE bypData);
	void NewHeroProcess(PBYTE bypData);
	//�켮.
	static  void ThrowItemProcess(PBYTE bypData);
	static	void UseItemProcess(PBYTE bypData);
	static  void PickUpItemProcess(PBYTE bypData);
	static  void OutItemProcess(PBYTE bypData);
	static  void GetItemProcess(PBYTE bypData);
	static	void MoneyChangeProcess(PBYTE bypData);
	
	static  CPoint PixelToCellUnit(CPoint ptPixel);
	static  CPoint CellUnitToPixel(CPoint ptCell);

	int m_test_Flag;
	void SendDelHero(CString id);
	BOOL SendNewHero(CString id, CDialog_Login *Dialog_Login);
	
	BOOL LoginAcount(CString id, CString password);
	BOOL LoginAcountNew();
	BOOL InitLogin();
	void GameLogin();
	void LoginView();
	void Login_Window();
	BOOL LogIn();
	BOOL m_First_Menu;
	void Rail_MagicProcess();
	void AttackMagic(int suid, int euid, int magic_type);
	static BOOL ChangeItem(int index);
	int m_Arry_ItemIndex[50];
	int m_Arry_ItemType[50];
	void Search_Item();
	void Item_MouseProcess(BBDX_MouseInformation *pMouseInfo, int Dlg_Pos, int Select_Box, int MoveFlag = 1);
	void MagicItem_MouseProcess(BBDX_MouseInformation *pMouseInfo, int Dlg_Pos, int Select_Box, int MoveFlag = 1);
	void Item_Init();

	void Item_Draw();
	void AuctionSell_Item_Draw();

	void ShopItem_Draw();

	int m_Item_Pic_Index[1000];// �׸���ȣ�� ���߱� ���ؼ� ����.
	int m_Arm_type[1000]; //10�� 16�� �켮..
	int m_Draw_Order[1000];

	bool m_RestartGame;

	void					SetMainMode(int mode);

	//DirectInput ���콺 ó���Լ�
	int						MouseProcess();	
	void					AccountMouseProcess(int *id_flag);
	void					LoginMouseProcess(CDialog_Login *Dialog_Login);
	void					LBtnDown(CPoint &pos);
	void					LBtnPressing(CPoint &pos);
	void					LBtnUp(CPoint &pos);
	void					RBtnDown(CPoint &pos);
	void					RBtnPressing(CPoint &pos);
	void					RBtnUp(CPoint &pos);
	void					MouseMove(CPoint &pos, BOOL lClick = FALSE);

	void					InitStaticVariables();

	void					PacketProcess();
	BOOL					SocketInit();
	BOOL					SocketRelease();
	BOOL					IdleProcess(LONG turn);
	BOOL					NFocusIdleProcess(LONG turn);
	BOOL					DDRelease();	//DirectX ����	 (Application �����)
	BOOL					DDInit();		//DirectX �ʱ�ȭ (Application ���۽�)
	void					SetMyUserId(int uid);			//�ڽ��� UserId (������ ����)
	int						GetMyUserId() {return m_iMyId;}

	void					CreateEditor();							//Editor����(��ũ���̹��� ����)
	BBDX_ChatEditor*		GetEditor(){return m_pBBDX_Editor;}		//	"
	BBDX_ChatOuter*			GetChatOuter(){return m_pChatOuter;}	//	"
	BBDX_Editor*			GetChatOuterid(){return m_pBBDX_Editor_id;}	//	"
	BBDX_Editor*			GetChatOuterpassword(){return m_pBBDX_Editor_password;}	//	"
	int                     m_Chattype;// ä�� Ÿ��... 1: �븻 ä�� 2: ���� ...
	CString                 m_CurMemoChatId;
	CString                 GetCurMemoChatId(){ return m_CurMemoChatId;}
	void	                SetCurMemoChatId(CString id_name){ m_CurMemoChatId = id_name;}
	void					DisplayDate();

	void					ReStart();
	void					Notice(PBYTE bypData);

protected:
	BBDX_Editor*			m_pBBDX_Editor_id;
	BBDX_Editor*			m_pBBDX_Editor_password;
	BBDX_ChatOuter*			m_pChatOuter;
	BBDX_ChatEditor*		m_pBBDX_Editor;
	CPoint					m_ptMapOffset;		//Pixel������ Offset(����׷����� �ִ� ������ Offset
	int						m_iMyId;
	DWORD                   m_PathFindGap;

	bool                    m_bCtrlUp;

	//Ű���� ������ �������� �ƴϳ� �̰͵��� �ӽ÷� ���ɰ͵��̴�.....
	// Generated message map functions
protected:
	//{{AFX_MSG(CChildView)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg	LRESULT OnPacketProcess(WPARAM, LPARAM);
	afx_msg	LRESULT	OnPacketPending(WPARAM, LPARAM);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg LRESULT OnImeStartComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeEndComposition(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnImeCompositionFull(WPARAM wParam, LPARAM lParam);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnSysKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDVIEW_H__180690AB_F9A1_11D2_8421_0020AF9F40BD__INCLUDED_)
