// User.h: interface for the CUser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USER_H__5A5901E5_3853_11D3_8422_00105A6B97E2__INCLUDED_)
#define AFX_USER_H__5A5901E5_3853_11D3_8422_00105A6B97E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "illstruct.h"

#include "MyInvData.h"
#include "MyMagicData.h"

class DirectXMng;
class CCharManager;
class CCharRes;
class CDDSurface;
class CUserManager;
class CMagic;
class CArmatureManager;
class CArmature;

//class CMyInvData;

#define MOVEPOS_KIND_NEXT	0
#define MOVEPOS_KIND_END	1

#define AM_KIND_NUM		7

//0:�Ǽ�,��Ŭ, ������ 1:�Ѽհ� 2:��հ� 3: â 4:Ȱ 5:����,�ظ�, ���� 6:������ 7: ���� 8:��Į(����)
#define NOTHINGARM      0
#define SINGLESWORD     1
#define BIGSWORD        2 // ��հ�
#define SPEAR           3 // Ȱ
#define BOW             4
#define AX              5
#define WAND            6 //������ ������
#define CROSSBOW        7
#define DOUBLESWORD     8 //��Į

typedef struct
{
	int kind;
	CPoint ptPos;
} MOVEPOS;		//Move�� ��û�� Routing Data�������

typedef struct _TAG_FLY_END_MAGIC
{
	int		m_nMagicIndex	;//���� �ε���
	BOOL	m_bType			;//���� Ÿ��
	int		m_nPoisonKind	;//������ ����
	int		m_nTableNum		;//���� ���̺� ��ȣ
} FLY_END_MAGIC;

typedef struct _TAG_APPLIED_CON_MAGIC
{
	DWORD		m_dwContime	;//���ӽð�
	short		m_nTableNum	;//���� ���̺� ��ȣ
} APPLIED_CON_MAGIC;

#define		SPECIAL_MAGIC		0
#define		BLUE_MAGIC			1
#define		WHITE_MAGIC			2
#define		BLACK_MAGIC			3

typedef CTypedPtrArray<CPtrArray, CMyMagicData *> CMyMagicDataArray;
typedef CMap<int, int, CMyMagicData *, CMyMagicData *> CMyMagicDataMap;

#define	INV_COUNT				50
#define BELT_COUNT				4

//�������� ó�� Ŭ����(�Ѹ��� User�� �ش�)
class CUser  
{
public:
	short GetInv_ItemUsage(int index);
	int GetInv_ItemIndex(int index);
	int GetInv_ItemType(int index);
	int GetInv_ItemPic(int index);
	int GetInv_ItemArm(int index);
	CString GetInv_ItemName(int index);

	int GetJangchk_Item(int index);
	void Change_View_item(short index, short picnum);
	void Chang_Item(short fromindex, short toindex);
	void SetInvAll(PBYTE bypData);
	void			SetWearItem(int nType, int nIndex, int btype = -1, int barm = -1);
	void ChangeItemInfo(BYTE bBelt, BYTE nSpec, CMyInvData& inv_data);

	void			SetMagic(int nIndex, int nMagicType, int height =0);	//������ü�� �ɸ��� ���� (���ư��� ������ UserManager������)
	void			Set3DMagic(TCHAR* strName, int nMagicType, int nHeight=0, int nWidth=0);//dspring_0731_3dxx
	void			Set3DMagicEx(int index, int nMagicType, int nHeight=0, int nWidth=0);//dspring_0731_3dxx

	void			SendNextMoveReq(CPoint ptPosAllowed);	//���� �̵��� ��û
	void			SetMoveFirst(CPoint ptDst, CPoint ptFirst);	//������ ������ �㰡, ����
	void			SetMoveMiddle(CPoint ptDst);					//������ ó��
	void			SetMoveEnd(CPoint ptDst);					//������ �������� ���

	void			SendNextRunMoveReq(CPoint ptPosAllowed, CPoint nextpt);	//���� �̵��� ��û
	void			SetRunMoveFirst(CPoint ptDst, CPoint ptFirstv, CPoint ptNext);	//������ ������ �㰡, ����
	void			SetRunMoveMiddle(CPoint ptDst, CPoint ptNext);					//������ ó��
	void			SetRunMoveEnd(CPoint ptDst, CPoint ptNext);					//������ �������� ���

	void			SetMoveList(CList<CPoint, CPoint>* pRoute);					//�̵� ��û ���
	static CList<CPoint, CPoint>* CalcMoveList(CPoint ptStart, CPoint ptEnd, int Direction = 0);	//�̵� ��� Ž��
	//�켮.. 10�� 11��..
	CList<CPoint, CPoint>* CalcMoveList2(CPoint ptStart, CPoint ptEnd, int FindStep);
	int				GetUserId(){return m_iUserId;}								//���� Id(������ ����ȭ)
	void			SetUserId(int id) {m_iUserId = id;}							//	"

	int             m_MeDraw_Order[AM_KIND_NUM]; //�켮..

	int             m_AniSprNumber;
	BOOL			m_bDying;
	BOOL			m_bDeadFlag;
	int				m_bDead;
	int				m_vMoveStep;
	enum UserMotion //������ ���Ǵ� lgt3�� animation�׸��� ó���� ����(Animation Index)
	{
		UM_Stop = 0, 
		UM_Walk, 
		UM_Attack,// ���� ���Ӱ� ����..�Ҳ�..
		UM_Beated,
		UM_Magic,
		UM_Die,
		UM_RUN,


/*		UM_StopInAttack,
		UM_WalkInAttack,
		UM_Run,
		UM_AttackSecond,
		
		UM_Push,
		UM_Dash,
		UM_Defence,
		UM_Ko,
		

/*		UM_Stop = 0, 
		UM_StopInAttack,
		UM_Walk, 
		UM_WalkInAttack,
		UM_Run,
		UM_Attack,
		UM_AttackSecond,
		UM_Magic,
		UM_Push,
		UM_Dash,
		UM_Defence,
		UM_Ko,
		UM_Die,
		UM_Beated,
*/	} m_AnimationIndex, m_prevAnimation;
	BOOL	SetMotion(enum UserMotion um);	//Animation ����: �̵�, ����, ����, ���� ���
//	void	ActionMotion(enum UserMotion um, int delay_time);	//Animation ����: �̵�, ����, ����, ���� ���

	enum UserDirection	//User�� ����
	{
		UD_Down = 0,
		UD_DownLeft,
		UD_Left,
		UD_UpLeft,
		UD_Up,
		UD_UpRight,
		UD_Right,
		UD_DownRight
	} m_Direction;
	void			SetDirection(enum UserDirection ud) {m_Direction = ud;}		//ĳ������ ���⼳��(8����)

	//LSP ó����ƾ
	static  void    PutPixelNormal2(const WORD* pDest, const WORD* pSrc, int nCopyCount,const DWORD color, int alpha, DWORD dwRBBitMask,DWORD dwGBitMask);

	static	void	PutPixelNormal(const WORD* pDest, const WORD* pSrc, int nCopyCount);
	static	void	PutPixelAlphaAdd(const WORD* pDest, const WORD* pSrc, int nCopyCount, DWORD dwRBitMask, DWORD dwGBitMask, DWORD dwBBitMask);
	static	void	PutPixelAlphaSoft(const WORD* pDest, const WORD* pSrc, int nCopyCount, DWORD dwRBitMask, DWORD dwGBitMask, DWORD dwBBitMask);
	static	void	PutPixelTrans(const WORD* pDest, const WORD* pSrc, int nCopyCount, int nAlphaDest, int nAlphaSrc, DWORD dwRBBitMask, DWORD dwGBitMask); // nAlphaSrc �� nAlphaDest �� ���� �ݵ�� 32 �̾�� �Ѵ�..
	static	void	PutPixelDark(const WORD* pDest, const WORD* pSrc, int nCopyCount, int nAlphaSrc, DWORD dwRBBitMask, DWORD dwGBitMask); // nAlphaSrc - 0 �� �� ��Ŀ�ݴ�.. 32 �� ���� ���.
	static	void	PutPixelShadow(const WORD* pDest, int nCopyCount, int nAlphaDest, DWORD dwRBBitMask, DWORD dwGBitMask); // 0 ��Ŀ�� �׸���.. 32 �׸��� ����..
	static	void	PutPixelColor(const WORD* pDest, const WORD* pSrc, int nCopyCount, int nAlphaSrc, DWORD dwDestColor, DWORD dwRBBitMask, DWORD dwGBitMask); // nAlphaSrc - ��������Ʈ�� ��� ��. dwDestColor - �÷��� 32��Ʈ ��. (�ݵ�� "32-nAlphaSrc"�� ������ ��ġ�Ͽ��� �Ѵ�.
	static	void	PutPixelHalf(const WORD* pDest, const WORD* pSrc, int nCopyCount, DWORD dwHalf16Mask, DWORD dwHalf32Mask);
	static  void	PutPixelShadowEx(const WORD* pDest, int nCopyCount, DWORD dwHalf16Mask, DWORD dwHalf32Mask);
	static	void	PutPixelBitStepTrans(const WORD* pDest, const WORD* pSrc, int nCopyCount, int nAlphaDestBit, int nAlphaSrcBit, DWORD dwRBGBitMask, DWORD dwGRBBitMask);

	static	void	BltLSPShadow(CDDSurface *pSurface, int x, int y, RECT* pRC, WORD* data,	int alpha);
	static	void	BltLSPShadowEx(CDDSurface *pSurface, int x, int y, RECT* pRC, WORD* data, DWORD dwHalf16Mask, DWORD dwHalf32Mask);
	static	void	BltLSPTrans(CDDSurface *pSurface, int x, int y, RECT* pRC, WORD* data, int alpha, BOOL bFocus=FALSE);
	static	void	BltLSPAlphaAdd(CDDSurface *pSurface, int x, int y, RECT* pRC, WORD* data);
	static	void	BltLSPNormal(CDDSurface *pSurface, int x, int y, RECT* pRC, WORD* data, BOOL bFocus=FALSE, int nPoisonKind = 0, int nFocusColor = 3);
	static	void	BltLSPDark(CDDSurface *pSurface, int x, int y, RECT* pRC, WORD* data, int strength = 1);
	static	void	BltLSPHalfAlpha(CDDSurface *pSurface, int x, int y, RECT* pRC, WORD* data, DWORD dwHalf16Mask, DWORD dwHalf32Mask);
	static	void	BltLSPHalfAlphaEx(CDDSurface *pSurface, int x, int y, RECT* pRC, WORD* data, DWORD dwHalf16Mask, DWORD dwHalf32Mask);
	static  void	BltLSPDrawLine(CDDSurface *pSurface, int x, int y, RECT* pRC, WORD* data,int skip_line = 0);
	static  void	BltLSPDrawObj(CDDSurface *pSurface, int x, int y, RECT* pRC, WORD* data);
	static  void	BltLSPBitStepTrans(CDDSurface *pSurface, int x, int y, RECT* pRC, WORD* data, int nAlphaSrc, int nAlphaDst);

	static	BOOL	GetClippedRect(RECT *pRC, RECT* pRCClip);
	static  void	BltLSPChat(CDDSurface *pSurface);
	static  void	BltBlackTrans(CDDSurface *pSurface,CRect rc);


	static	CPoint	PixelToCellUnit(CPoint ptPixel);	//pixel��ǥ�� Cell��ǥ��(Cell��ǥ�� ������ �����)
	static	CPoint	CellUnitToPixel(CPoint ptCell);		//Cell��ǥ�� Pixel��ǥ��

	BOOL			IsArrivedInCell() {return m_bCellArrive;}	//Cell�� �߽ɿ� ����?
	BOOL			IsCharStop() {return m_AnimationIndex==UM_Stop;}	//ĳ���Ͱ� ������ ������ ����(�̵��� ���ݵ����� �ƴ�)
	BOOL			IsCharAttack() {return m_AnimationIndex==UM_Attack;}	//
	BOOL			IsCharDie() {return m_bDead == TRUE || m_bDeadFlag == TRUE;}	//
	void			Pause(BOOL tf) {m_bPauseChar = tf;}	//ĳ������ ���� �Ͻ����� OR �Ͻ����� ����
	BOOL			GetFocus() {return m_bFocus;}		//������ Focus����
	void			SetFocus(BOOL tf) {m_bFocus = tf;}	//�׸��� �ڵ����� Ǯ�� (Ŀ���� ������� �ִ� ��� Focus������)
	void			SetDirection(int direction);		//direction�� illstruct.h �� define��
	void			MoveNextStep_New2();					// Frame��ȭ�� �����̵���,

	void			Move();								// �̵�ó�� (���� �Լ���� MoveXY, MoveX, MoveY)
	CRect&			GetCharRect() {return m_rCurCharRect;} //ȭ����� ǥ�ÿ��� (ĳ������ ǥ�ÿ���)
//	BOOL			GetSpr(_SPR_LSP** spr, PWORD* pV1, PWORD* pV2, PWORD* pS, PWORD* pFX); //Frame�� ��ȭ�� ������ TRUE
	BOOL			GetSpr(_SPR_LSP** spr, PWORD* pV); //Frame�� ��ȭ�� ������ TRUE
	void			RenderChar(CDDSurface* pSurface, CPoint PosMapOffset);	//ĳ���͸� �׸�
	void			DrawLine(CDDSurface* pSurface, CPoint PosMapOffsetint, int skip_line);

//	void			RenderBodyAndArmature(CDDSurface *pSurface, CPoint ptScreen, RECT rcV1, RECT rcV2);
	void			RenderBodyAndArmature(CDDSurface *pSurface, CPoint ptScreen, RECT rcV1);

	void			SetDstPos(CPoint ptDstPos);			//�̵��� ������ ���� , Pixel���� ��ǥ
	void			SetPosition(CPoint pos);			//�ʱ���ǥ ����(������ Warp����), Pixel���� ��ǥ

	void			SetCellPosition(CPoint ptPosCell);	//������ Cell�� ĳ���� ��ġ��Ŵ
	void			SetCellDstPos(CPoint ptPosDstCell);	//�̵��� ������ Cell����

	CPoint&			GetPosition(){return m_Position;}	//������ ��ġ(Pixel����)
	CPoint			GetCellPosition() {return PixelToCellUnit(m_Position);}	//������ ��ġ(Cell ��ġ)
	void			SetCharRes(int index, int nChar=0);		//ĳ������ Resource����

	void			SetChatString(CString &str);		//ä�� ���� (���߿� �Ӹ����� ����)
	void			SetIdNameString(CString &str);		//ä�� ���� (���߿� �Ӹ����� ����)

	CUser();
	virtual ~CUser();

	static	CCharManager*		m_bpCharManager;		//ĳ���� ������ (CChildView::CharManager)
	static	DirectXMng*			m_bpDirectXMng;			//DirectX ������ (CChildView::DirectXMng)
	static	CUserManager*		m_bpUserManager;		//���� ������ (CChildView::UserManager)
	static	CArmatureManager*	m_bpArmatureManager;	//���������� ������

	static	DWORD m_dwRBBitMask; // ��Ʈ ����ũ...	//LSPó����ƾ���� ���
	static	DWORD m_dwRBitMask;
	static	DWORD m_dwGBitMask;
	static	DWORD m_dwBBitMask;
	static	DWORD m_dwRBGBitMask;//r0b0g0
	static	DWORD m_dwGRBBitMask;//0g0r0b
	static	WORD  m_CheckKey;							 //�ȼ� ���� üũ��
	static	WORD  m_LineKey;


	//(���)
	CString m_strUserId;// �̰� �ۺ����� ������ �ϴ°���..��..

	///////////////////////////////



/*	int Get_Type() { return m_sType;}
	int Get_Hp() { return m_Hp;}
	int Get_Mp() { return m_Mp;}
	int Get_MaxHp() { return m_MaxHp;}
	int Get_MaxMp() { return m_MaxMp;}
	int Get_Fa() { return m_Fa;}//�Ƿε�
	int Get_At() { return m_At;}//���ݷ�
	int Get_Wg() { return m_Wg;}//�ٷ�
	int Get_Dx() { return m_Dx;}// �ӵ�
	int Get_Int() { return m_Int;}//����
	int Get_Luck() { return m_Luck;}//��
	int Get_Fame() { return m_Fame;}//��
	int Get_Mone() { return m_Money;}
	int Get_Style() { return m_Style;}//�� ����.
	int Get_Gender() { return m_Gender;}//����?����?
*/

//protected:
public:
	void ChangeMoney(DWORD money);

	void AddMagic(short number, BYTE method1, BYTE method2, short start_time, BYTE type, BYTE target, CString name, CString explain, short distance, short use_mp, int use_time, short damage, short game_pic);
	void DelMagic(short number);

	void Add_Item(short index, BYTE type, BYTE arm, short picnum, BYTE gender, short min_damage, short max_damage, short limit_str, short limit_int, short limit_skill, CString magic_name, CString s_num, short special[7], DWORD value, short use_count, short max_use_count, short org_max_use_count, CString name);
	void Add_Item(PBYTE bypData);
	void Del_Item(BYTE bBelt, short index);

	BOOL MoveItemToBelt(short from, short to);
	BOOL MoveItemToInv(short from, short to);
	void View_BubbleChat(CPoint bgpos);
	void View_Id(CDC *pDC, CPoint bgpos);
	void SendRevival(int type);
	void SetFlyEndMagic(int index, BOOL bType, int nTableNum, int nPoisonKind = 0);

	int m_Run;
	int m_Run_Flag;
	int m_Walk;// ���ƴ� ���� �������� ���¸� �˱����ؼ�..end��Ŷ���� 0���� �����. 

	CArray<CMagic*, CMagic*>	m_arrMagic;	//������ ������ ����Ʈ//dspring_0720a
	CArray<CString , CString>	m_arrMagicName;//���������� ������ ��ĳ���Ϳ� ������ ���� �̸�dspring_0802_3dxx
	CArray<int , int>			m_nMagicIndex;//���������� ������ ��ĳ���Ϳ� ������ ���� �ε���dspring_0724
	CArray< FLY_END_MAGIC	 , FLY_END_MAGIC>		m_arrFlyEndMagic;
	CArray< APPLIED_CON_MAGIC, APPLIED_CON_MAGIC>	m_arrACM;

	BOOL m_bCellChange;
	CMagic*			m_pMagic;				//������ ����
	CString			m_szChatString;			//���� �ڽ��� ä��

	_SPR_LSP*		m_bpSprData;			//�׸��⿡ ����� Sprite Data (ILL Struct�� ���ǵ�)
	PWORD			m_wpV;					//ĳ���� ����1
//	PWORD			m_wpV1;					//ĳ���� ����1
//	PWORD			m_wpV2;					//ĳ���� ����2
//	PWORD			m_wpS;					//�׸��� ����
//	PWORD			m_wpFX;					//Ư��ȿ�� ���� (���� ������� ����)

	CRect			m_rCurCharRect;			//���� ĳ������ ȭ��ǥ�ÿ���(ȭ����� ��ǥ)
	DWORD			m_dwTick;				
	int				m_iSpriteIndex;			//SpriteIndex

	int				m_iCharResIndex;		//ĳ������ Resource�ε���
	int				m_nChar;		//CharRes���� Char Index (_CHR_HEADER �� nQt->ĳ���� ����)
	int				m_nCharRes;		//ĳ������ Resource��ȣ
	CCharRes*		m_bpCharRes;	//������ ��ȣ������ Setting�� Resource

	CPoint			m_Position;			//���� ĳ������ ��ġ	(Pixel Unit)
	CPoint			m_ptDstPos;			//���� �������� ��ǥ			(Pixel Unit)
	CPoint          m_ptDestFinalPos; // �̵��� ���� ��ǥ��...��ǥ..

	CPoint			m_ptCellPrev;
	CPoint			m_ptCellPos;		//Map�� Cell���� ��ġ
	CPoint			m_ptDestCellPos;	//Map�� ���� Cell���� ��ġ
	
	int             m_RunEnd;
//	DWORD			m_dwMoveTick;
	DWORD           m_dwTickPrev;
	int				m_nFocusColor;

	////////////////////////////////////
	// ���Ӱ� �����̴°� ��ȭ�� �ຸ�� ���ؼ�..�ߺ������� ���̴°��� �����ϱ����ؼ� �ٽ� ����..
	CPoint			m_ptStartCellPos;   //���� ����� �� ��ġ
//	CPoint			m_ptPreMyCellPos;		//���� ���� �ִ� Cell ��ġ
	CPoint			m_ptPostCellPos;	//�̵� �� �� ��ġ
	CPoint          m_ptNextCellPos;    //�ٴ°� ������ ����.

	CPoint			m_ptMoveStep;		//�̵��� ��ǥ����

	BOOL			m_bFocus;			//Cursor������ Focus���� �ǹ�
	BOOL			m_bPauseChar;		//������ ���ۿ��� �Ͻ�����
	BOOL			m_bCellArrive;		//Cell������ ��ġ�� ��������
	int				m_nMotionStep;		//Walk�� Stop�� ������ �������� Step;
	int				m_nPoisonKind;		//������ ����
	BOOL			m_bPoisoning;		//�ߵ����ΰ�
	DWORD			m_dwPoisonTime;		//�ߵ��ð�
	DWORD			m_dwTorchlight;		//ȶ�������ð�
	int				m_iUserId;			//�������� �Ҵ���� User Id

	CList<CPoint, CPoint>*	m_pRoute;	//�ڱ��ڽ��� ������ �����ؼ� ������ ����
	int				m_nMagicType;		//������ ���� (�ٴ� Ÿ��? ���� Ÿ��?)

	CArmature*		m_pArmature;			//���� ������ �ε���

	//(���)
	// ���� ��ġ���� ����ü�� ������ ������? �ƴϸ�..������ ����Ÿ�� ������ ������ ����..
	//�ϴ��� ������ ��ġ��..
//public:
	int m_nType;// ĳ������ ����....0 ����Ȳ�� 1 ���� ���� 2 ���� ���� 3 ����Ȳ 4, 5.....11 npc....
	int m_Me;
	int m_InHouse;// -1�̸� ���̰�...��Ÿ ��ȣ��..����ȣ�̴�.

	int m_Level;

	DWORD m_Max_exp;
	DWORD m_Cur_exp;

	int m_Cur_Hp;
	int m_Max_Hp;

	int m_Cur_Mp;
	int m_Max_Mp;

	int m_Max_Fa;
	int m_Cur_Fa;//�Ƿε�

	int m_Max_Weight;//����ִ� ���湫��.. 
	int m_Cur_Weight;

	int m_At;//���ݷ�
	DWORD m_Money;
	int m_Style;//�� ����.
	int m_Gender;
	BYTE m_bDeadEnable;

	//���� ���..
	int m_Armor;// ��ü ����
	int m_Helmet;// ���� �� �Ӹ�
	int m_Boot;//�Ź�
	int m_Jean;// ����
	int m_Shield;// ����
	int m_Sword;// ����
	int m_item_1;
	int m_item_2;
	int m_item_3;
	int m_item_4;
	int m_Skin;
	int m_Hair;

	int m_Arm_type;// ���� ������ �ִ� ������ Ÿ�� 0:�Ǽ� 1:�Ѽհ� 2:��հ�, 3: â, 4: Ȱ, 5:����,6:��Į(����)

	int m_BattleMode;// 0 : ���⸦ ���� �ִ�. 1 : �Ϲ� ���� ��� 2 : PK ���

	int m_PkRecive_Flag;// ������Ŷ�� ������ ������ ���� �ʾҴٸ� ���ο���� ������ �ʰ� �ϱ����ؼ�..
	int m_PkRecive_Attack_Flag;// ���� ��Ŷ�� ������..
	DWORD m_PkRecive_Attack_Time;// ������ �ð�

	DWORD m_dwBubbleTick;// ����ä�ÿ� ����Ҳ�..
	COLORREF m_vIdColor;

	DWORD m_dwMoveTick;
	DWORD m_dwnewMoveTick;


	DWORD m_dwAttackTick;
	DWORD m_dwBeatedTick;
	DWORD m_dwMagicTick;
	DWORD m_dwDieTick;

	DWORD m_FaTickCount;
	//�κ��丮....
	CMyInvData m_MyInvData[INV_COUNT];
	CMyInvData m_MyBeltData[BELT_COUNT];
	int		m_vInvCount;

	//������ �ִ� ���� ǥ��.
	CMyMagicDataArray m_arrSpecialMagic;// 00 8.16�߰� ���...
	CMyMagicDataArray m_arrBlueMagic;
	CMyMagicDataArray m_arrWhiteMagic;
	CMyMagicDataArray m_arrBlackMagic;
	CMyMagicDataMap m_mapMyMagicData;			// ���� ����

	CString	m_Designation;		// Īȣ
	CString	m_Guild;			// �Ҽ�
	CString	m_Grade;			// ����
	short	m_Age;				// ����
	short	m_Deposition;		// ����
	short	m_Str;				// ��
	short	m_Int;				// ����
	short	m_Dex;				// ��ø
	short	m_Wis;				// ����
	short	m_Cha;				// �ŷ�
	short	m_Con;				// ü��
	int		m_UsingSword;		// �˼�
	int		m_UsingSpear;		// â��
	int		m_UsingAxe;			// �б��
	int		m_UsingKnuckle;		// �Ǽ�
	int		m_UsingBow;			// �ü�
	int		m_UsingCrook;		// ������
	int		m_MakingWeapon;		// ���� ���ۼ�
	int		m_MakingArmor;		// �� ���ۼ�
	int		m_MakingAccessory;	// ��ű� ���ۼ�
	int		m_MakingPotion;		// �þ� ���ۼ�
	int		m_Cooking;			// �丮
	int		m_BlackMagicExp;	// �渶�� ���ġ
	int		m_WhiteMagicExp;	// �鸶�� ���ġ
	int		m_BlueMagicExp;		// û���� ���ġ

	short	m_BloodType;

	void	SetDeposition(short deposition);

	int     m_prediff;
	bool    m_bFa;
//	int     m_HpRecoveryTime;
//	DWORD   m_HpTickCount;	
//	int     m_MpRecoveryTime;
//	DWORD   m_MpTickCount;	

//	void	HpRecovery();
//	void	MpRecovery();
};

inline void CUser::SetDeposition(short deposition)
{
	m_Deposition = deposition;
	if(m_Deposition <= -50) m_vIdColor = RGB(255, 0, 0);
	else if(m_Deposition >= -49 && m_Deposition <= -30) m_vIdColor = RGB(255, 70, 70);
	else if(m_Deposition >= -29 && m_Deposition <= -11) m_vIdColor = RGB(255, 140, 140);
	else if(m_Deposition >= -10 && m_Deposition <= -4) m_vIdColor = RGB(255, 200, 200);
	else if(m_Deposition >= -3 && m_Deposition <= 3) m_vIdColor = RGB(211, 237, 251);
	else if(m_Deposition >= 4 && m_Deposition <= 10) m_vIdColor = RGB(187, 230, 244);
	else if(m_Deposition >= 11 && m_Deposition <= 30) m_vIdColor = RGB(158, 208, 246);
	else if(m_Deposition >= 30 && m_Deposition <= 49) m_vIdColor = RGB(167, 190, 248);
	else if(m_Deposition >= 50) m_vIdColor = RGB(150, 150, 255);
}


inline void CUser::PutPixelNormal2(const WORD* pDest, const WORD* pSrc, int nCopyCount,const DWORD color, int alpha, DWORD dwRBBitMask,DWORD dwGBitMask)
{
	int dstalpha = 32 - alpha;

	__asm // RGB ������ ���� ���..
	{
		mov edi, pDest;
		mov esi, pSrc;
		mov ecx, nCopyCount;
COPY_LOOP:
		push ecx; // ī��Ʈ ����..
		
		mov ebx, 0; // ���� ���� �ʱ�ȭ
		
		mov ecx, color; // Spr Pixel
		
		jecxz DONT_COPY; // ��������Ʈ ������ 0 �̸�... ó�� ����..
		
		mov eax, ecx; // Spr - R B
		and eax, dwRBBitMask;
		shr eax, 5;
		mul alpha;		
		and eax, dwRBBitMask;
		add ebx, eax;
		
		mov eax, color; // Spr - G
		and eax, dwGBitMask;
		mul alpha;
		shr eax, 5;
		and eax, dwGBitMask;
		add ebx, eax;
		
		mov ecx, [esi]; // Bkg Pixel
		
		mov eax, ecx; // Bkg - R B
		and eax, dwRBBitMask;
		shr eax, 5;
		mul dstalpha;		
		and eax, dwRBBitMask;
		add ebx, eax;
		
		mov eax, [esi]; // Bkg - G
		and eax, dwGBitMask;
		mul dstalpha;
		shr eax, 5;
		and eax, dwGBitMask;
		add ebx, eax;
		
		mov [edi], ebx;
		
DONT_COPY:
		
		add edi, 2;
		add esi, 2;
		
		pop ecx; // ī��Ʈ ����..
		dec ecx;		
		jnz COPY_LOOP;
	}
}


// ��û�� ũ���� �ζ��� �Լ�.. �ӵ��� �ſ� �ΰ��ϴ�. - BltAlphaAdd.
inline void CUser::PutPixelNormal(const WORD* pDest, const WORD* pSrc, int nCopyCount)
{
/*	__asm
	{
		mov edi, pDest;
		mov esi, pSrc;
		mov ecx, nCopyCount;
MOV_LOOP:
		movsw;
		dec ecx;
		jnz MOV_LOOP;
	}*/
	__asm
	{
		push edi;
		push esi;
		cld;
		mov edi, pDest;
		mov esi, pSrc;
		mov ebx, nCopyCount;
		mov eax, ebx;
		shr eax, 1;
		mov ecx, eax;
		rep movsd;
		mov eax, ebx;
		and eax, 1;
		mov ecx, eax;
		rep movsw;
		pop esi;
		pop edi;
	}
};

inline void CUser::PutPixelAlphaAdd(const WORD* pDest, const WORD* pSrc, int nCopyCount, DWORD dwRBitMask, DWORD dwGBitMask, DWORD dwBBitMask)
{
	__asm
	{
		mov edi, pDest;	// ��׶��� �ּ� ����.
		mov esi, pSrc;	// ��������Ʈ �ּ� ����.
		
		mov ecx, nCopyCount; // ���� ����.
		
COPY_LOOP:
		push ecx;
		mov ecx, [esi]; // Spr
		
		jecxz DONT_COPY; // ��������Ʈ ������ 0 �̸�... ó�� ����..
		
		mov ebx, 0; // ���� �ȼ�
		
		mov eax, ecx; // Spr - R
		mov edx, [edi]; // Bkg - R
		and eax, dwRBitMask;
		and edx, dwRBitMask;
		add edx, eax;
		cmp edx, dwRBitMask;
		ja COPY_R1;
		jmp ADD_R1;
COPY_R1:
		mov edx, dwRBitMask;
ADD_R1:
		or ebx, edx;
		
		mov eax, ecx; // Spr - G
		mov edx, [edi]; // Bkg - G
		and eax, dwGBitMask;
		and edx, dwGBitMask;
		add edx, eax;
		cmp edx, dwGBitMask;
		ja COPY_G1;
		jmp ADD_G1;
COPY_G1:
		mov edx, dwGBitMask;
ADD_G1:
		or ebx, edx;
		
		mov eax, ecx; // Spr - B
		mov edx, [edi]; // Bkg - B
		and eax, dwBBitMask;
		and edx, dwBBitMask;
		add edx, eax;
		cmp edx, dwBBitMask;
		ja COPY_B1;
		jmp ADD_B1;
COPY_B1:
		mov edx, dwBBitMask;
ADD_B1:
		or ebx, edx;
		
		mov [edi], bx; // ����ۿ� ��
		
DONT_COPY:
		add edi, 2;
		add esi, 2;
		
		pop ecx;
		dec ecx;
		jnz COPY_LOOP;
	}
};

inline void CUser::PutPixelAlphaSoft(const WORD* pDest, const WORD* pSrc, int nCopyCount, DWORD dwRBitMask, DWORD dwGBitMask, DWORD dwBBitMask)
{
	__asm
	{
		mov edi, pDest;	// ��׶��� �ּ� ����.
		mov esi, pSrc;	// ��������Ʈ �ּ� ����.
		
		mov ecx, nCopyCount; // ���� ����.
		
COPY_LOOP:
		push ecx; // ī��Ʈ ���
		
		mov ecx, [esi]; // ��������Ʈ �ȼ�
		
		jecxz DONT_COPY; // ��������Ʈ ������ 0 �̸�... ó�� ����..
		
		mov ebx, 0; // ���� �ȼ� ��..
		
		mov ecx, [esi]; // Spr �ȼ�
		
		mov edx, [edi]; // Bkg - R
		mov eax, ecx // Spr - R
			and edx, dwRBitMask;
		and eax, dwRBitMask;
		cmp eax, edx;
		jb COPY_R1_BKG;
		mov edx, eax
COPY_R1_BKG:
		or ebx, edx;
		
		mov edx, [edi]; // Bkg - R
		mov eax, ecx // Spr - R
			and edx, dwGBitMask;
		and eax, dwGBitMask;
		cmp eax, edx;
		jb COPY_G1_BKG;
		mov edx, eax
COPY_G1_BKG:
		or ebx, edx;
		
		mov edx, [edi]; // Bkg - R
		mov eax, ecx // Spr - R
			and edx, dwBBitMask;
		and eax, dwBBitMask;
		cmp eax, edx;
		jb COPY_B1_BKG;
		mov edx, eax
COPY_B1_BKG:
		or ebx, edx;
		
		mov [edi], bx; // ����ۿ� ��
		
DONT_COPY:
		add edi, 2;
		add esi, 2;
		
		pop ecx; // ī��Ʈ ����
		dec ecx;
		jnz COPY_LOOP;
	}
};

// nAlphaSrc �� nAlphaDest �� ���� �ݵ�� 5�̾�� �Ѵ�..
inline void CUser::PutPixelBitStepTrans(const WORD* pDest, const WORD* pSrc, int nCopyCount, int nAlphaDestBit, int nAlphaSrcBit, DWORD dwRBGBitMask, DWORD dwGRBBitMask)
{
	__asm
	{
		mov edi, pDest;
		mov esi, pSrc;
		mov ecx, nCopyCount;

		mov ebx, ecx;
		and ebx, 1;
		jz	DWORD_ALPHA_MIX;
/////////////////////////////////
// ���ȼ� ó�����ִ� �κ�
/////////////////////////////////
		add edi, 2;
		add esi, 2;
		dec ecx;
		jz  END_LOOP;

DWORD_ALPHA_MIX:
		shr ecx, 1;

COPY_LOOP:
		push ecx;
//first

		mov eax, [esi];
		and eax, dwRBGBitMask;
		shr eax, 5;
		mul nAlphaSrcBit;

		and eax, dwRBGBitMask;
		mov ecx, eax;

		mov eax, [esi];
		and eax, dwGRBBitMask;
		mul nAlphaSrcBit;

		shr eax, 5;
		and eax, dwGRBBitMask;
		or  ecx, eax;
//		or  eax, ecx;


//second
		mov eax, [edi];
		and eax, dwRBGBitMask;
		shr eax, 5;
		mul nAlphaDestBit;

		and eax, dwRBGBitMask;
		mov ebx, eax;

		mov eax, [edi];
		and eax, dwGRBBitMask;

		mul nAlphaDestBit;
		shr eax, 5;
		and eax, dwGRBBitMask;
		or  eax, ebx;

		add  eax,ecx;//�λ����ϱ�

		mov [edi],eax;

		add edi, 4;
		add esi, 4;
		
		pop ecx;
		dec ecx;
		jnz COPY_LOOP;

END_LOOP:
	}
}

inline void CUser::PutPixelTrans(const WORD* pDest, const WORD* pSrc, int nCopyCount, int nAlphaDest, int nAlphaSrc, DWORD dwRBBitMask, DWORD dwGBitMask) // nAlphaSrc �� nAlphaDest �� ���� �ݵ�� 32 �̾�� �Ѵ�..
{
	__asm // RGB ������ ���� ���..
	{
		mov edi, pDest;
		mov esi, pSrc;
		mov ecx, nCopyCount;
COPY_LOOP:
		push ecx; // ī��Ʈ ����..
		
		mov ebx, 0; // ���� ���� �ʱ�ȭ
		
		mov ecx, [esi]; // Spr Pixel
		
		jecxz DONT_COPY; // ��������Ʈ ������ 0 �̸�... ó�� ����..
		
		mov eax, ecx; // Spr - R B
		and eax, dwRBBitMask;
		mul nAlphaSrc;
		shr eax, 5;
		and eax, dwRBBitMask;
		add ebx, eax;
		
		mov eax, ecx; // Spr - G
		and eax, dwGBitMask;
		mul nAlphaSrc;
		shr eax, 5;
		and eax, dwGBitMask;
		add ebx, eax;
		
		mov ecx, [edi]; // Bkg Pixel
		
		mov eax, ecx; // Bkg - R B
		and eax, dwRBBitMask;
		mul nAlphaDest;
		shr eax, 5;
		and eax, dwRBBitMask;
		add ebx, eax;
		
		mov eax, ecx; // Bkg - G
		and eax, dwGBitMask;
		mul nAlphaDest;
		shr eax, 5;
		and eax, dwGBitMask;
		add ebx, eax;
		
		mov [edi], bx;
		
DONT_COPY:
		
		add edi, 2;
		add esi, 2;
		
		pop ecx; // ī��Ʈ ����..
		dec ecx;
		jnz COPY_LOOP;
	}
};

inline void CUser::PutPixelDark(const WORD* pDest, const WORD* pSrc, int nCopyCount, int nAlphaSrc, DWORD dwRBBitMask, DWORD dwGBitMask) // nAlphaSrc - 0 �� �� ��Ŀ�ݴ�.. 32 �� ���� ���.
{
	__asm // RGB ������ ���� ���..
	{
		mov edi, pDest;
		mov esi, pSrc;
		mov ecx, nCopyCount;
COPY_LOOP:
		push ecx; // ī��Ʈ ����..
		
		mov ebx, 0; // ���� ���� �ʱ�ȭ
		
		mov ecx, [esi]; // Spr Pixel
		
		jecxz DONT_COPY; // ��������Ʈ ������ 0 �̸�... ó�� ����..
		
		mov eax, ecx; // Spr - R B
		and eax, dwRBBitMask;
		mul nAlphaSrc;
		shr eax, 5;
		and eax, dwRBBitMask;
		add ebx, eax;
		
		mov eax, ecx; // Spr - G
		and eax, dwGBitMask;
		mul nAlphaSrc;
		shr eax, 5;
		and eax, dwGBitMask;
		add ebx, eax;
		
		mov [edi], bx;
		
DONT_COPY:
		
		add edi, 2;
		add esi, 2;
		
		pop ecx; // ī��Ʈ ����..
		dec ecx;
		jnz COPY_LOOP;
	}
};

inline void CUser::PutPixelShadowEx(const WORD* pDest, int nCopyCount, DWORD dwHalf16Mask, DWORD dwHalf32Mask) // nAlphaSrc - 0 �� �� ��Ŀ�ݴ�.. 32 �� ���� ���.
{
	__asm
	{
		mov edi, pDest;
		mov ecx, nCopyCount;

		// nCopyCount�� Ȧ������ ¦�������� �Ǵ�. 
		mov eax, ecx;
		and eax, 1;
		jz	DWORD_HALF_MIX;
	
		mov eax, [edi]; // Dest Spr Pixel
		and eax, dwHalf16Mask;
		shr eax, 1;
		mov [edi], ax;		// ax�� 16bit Register.
		
		add edi, 2;
		dec ecx;
		jz  END_LOOP;

		// ���⼭���ʹ� 32bit(DWORD)���.
DWORD_HALF_MIX: 
		shr ecx, 1;
		
COPY_LOOP:
		mov eax, [edi]; // 
		and eax, dwHalf32Mask;
		shr eax, 1;
		mov [edi], eax;

		add edi, 4;
		
		dec ecx;
		jnz COPY_LOOP;
END_LOOP:
	}
};

inline void CUser::PutPixelShadow(const WORD* pDest, int nCopyCount, int nAlphaDest, DWORD dwRBBitMask, DWORD dwGBitMask) // 0 ��Ŀ�� �׸���.. 32 �׸��� ����..
{
	__asm // RGB ������ ���� ���..
	{
		mov edi, pDest;
		//					mov esi, pSrc;
		mov ecx, nCopyCount;
COPY_LOOP:
		push ecx; // ī��Ʈ ����..
		
		mov ebx, 0; // ���� ���� �ʱ�ȭ
		
		mov ecx, [edi]; // Bkg Pixel
		
		mov eax, ecx; // Bkg - R B
		and eax, dwRBBitMask;
//		mul nAlphaDest;		
//		shr eax, 5;
		shr eax, 1;		// nAlphaDest = 16�ϰ��.(�׸����ϰ��)
		and eax, dwRBBitMask;
		add ebx, eax;
		
		mov eax, ecx; // Bkg - G
		and eax, dwGBitMask;
//		mul nAlphaDest;
//		shr eax, 5;
		shr eax, 1;		// nAlphaDest = 16�ϰ��.(�׸����ϰ��)
		and eax, dwGBitMask;
		add ebx, eax;
		
		mov [edi], bx;
		
		add edi, 2;
		//			add esi, 2;
		
		pop ecx; // ī��Ʈ ����..
		dec ecx;
		jnz COPY_LOOP;
	}

};

inline void CUser::PutPixelColor(const WORD* pDest, const WORD* pSrc, int nCopyCount, int nAlphaSrc, DWORD dwDestColor, DWORD dwRBBitMask, DWORD dwGBitMask) // nAlphaSrc - ��������Ʈ�� ��� ��. dwDestColor - �÷��� 32��Ʈ ��. (�ݵ�� "32-nAlphaSrc"�� ������ ��ġ�Ͽ��� �Ѵ�.
{
	__asm // RGB ������ ���� ���..
	{
		mov edi, pDest;
		mov esi, pSrc;
		mov ecx, nCopyCount;
COPY_LOOP:
		push ecx; // ī��Ʈ ����..
		
		mov ebx, 0; // ���� ���� �ʱ�ȭ
		
		mov ecx, [esi]; // Spr Pixel
		
		jecxz DONT_COPY; // ��������Ʈ ������ 0 �̸�... ó�� ����..
		
		mov eax, ecx; // Spr - R B
		and eax, dwRBBitMask;
		mul nAlphaSrc;
		shr eax, 5;
		and eax, dwRBBitMask;
		add ebx, eax;
		
		mov eax, ecx; // Spr - G
		and eax, dwGBitMask;
		mul nAlphaSrc;
		shr eax, 5;
		and eax, dwGBitMask;
		add ebx, eax;
		
		add ebx, dwDestColor; // �÷� ���� �����ش�.
		
		mov [edi], bx;
		
DONT_COPY:
		
		add edi, 2;
		add esi, 2;
		
		pop ecx; // ī��Ʈ ����..
		dec ecx;
		jnz COPY_LOOP;
	}
};

inline void CUser::PutPixelHalf(const WORD* pDest, const WORD* pSrc, int nCopyCount, DWORD dwHalf16Mask, DWORD dwHalf32Mask) // nAlphaSrc - 0 �� �� ��Ŀ�ݴ�.. 32 �� ���� ���.
{
	//ASSERT(dwRBMask == 0x7c1f);

	//DWORD dwMask = 0x7bde7bde;
	//DWORD  wMask = 0x00007bde;
	__asm
	{
		mov edi, pDest;
		mov esi, pSrc;
		mov ecx, nCopyCount;

		// nCopyCount�� Ȧ������ ¦�������� �Ǵ�. 
		mov ebx, ecx;
		and ebx, 1;
		jz	DWORD_HALF_MIX;

		//push ecx; // ī��Ʈ ����..
	
		mov eax, [esi]; // Spr Pixel
		mov edx, [edi]; // Dest Spr Pixel
		and eax, dwHalf16Mask;
		and edx, dwHalf16Mask;
		shr eax, 1;
		shr edx, 1;
		add eax, edx;
		//and eax, wMask;
		mov [edi], ax;		// ax�� 16bit Register.
		
		add edi, 2;
		add esi, 2;
		//pop ecx; // ī��Ʈ ����..
		dec ecx;
		jz  END_LOOP;

		// ���⼭���ʹ� 32bit(DWORD)���.
DWORD_HALF_MIX: 
		shr ecx, 1;
		
COPY_LOOP:
		//push ecx; // ī��Ʈ ����..
		//mov ebx, 0; // ���� ���� �ʱ�ȭ
		
		mov eax, [esi]; // Spr Pixel
		//jecxz DONT_COPY; // ��������Ʈ ������ 0 �̸�... ó�� ����..
		mov edx, [edi]; // 
		and eax, dwHalf32Mask;
		and edx, dwHalf32Mask;
		shr eax, 1;
		shr edx, 1;
		add eax, edx;
		//and eax, dwMask;
		mov [edi], eax;

//DONT_COPY:
		add edi, 4;
		add esi, 4;
		
		//pop ecx; // ī��Ʈ ����..
		dec ecx;
		jnz COPY_LOOP;
END_LOOP:
	}
};


#endif // !defined(AFX_USER_H__5A5901E5_3853_11D3_8422_00105A6B97E2__INCLUDED_)
/*
// nAlphaSrc �� nAlphaDest �� ���� �ݵ�� 5�̾�� �Ѵ�..
inline void CUser::PutPixelBitStepTrans(const WORD* pDest, const WORD* pSrc, int nCopyCount, int nAlphaDestBit, int nAlphaSrcBit, DWORD dwRBGBitMask, DWORD dwGRBBitMask)
{
	__asm
	{
		mov edi, pDest;
		mov esi, pSrc;
		mov ecx, nCopyCount;

		mov ebx, ecx;
		and ebx, 1;
		jz	DWORD_ALPHA_MIX;
/////////////////////////////////
// ���ȼ� ó�����ִ� �κ�
/////////////////////////////////
		add edi, 2;
		add esi, 2;
		dec ecx;
		jz  END_LOOP;

DWORD_ALPHA_MIX:
		shr ecx, 1;

COPY_LOOP:
		push ecx;
//first
		mov eax, [esi];
		and eax, dwRBGBitMask;
		shr eax, 5;
//		mov cl, byte ptr nAlphaSrcBit;
//		shl eax, cl;
		mul nAlphaSrcBit;

		and eax, dwRBGBitMask;
		mov edx, eax;

		mov eax, [esi];
		and eax, dwGRBBitMask;
//		shl eax, cl;
		mul nAlphaSrcBit;

		shr eax, 5;
		and eax, dwGRBBitMask;
		or  edx, eax;
//second
		mov eax, [edi];
		and eax, dwRBGBitMask;
		shr eax, 5;
//		mov cl, byte ptr nAlphaDestBit;
//		shl eax, cl;
		mul nAlphaDestBit;

		and eax, dwRBGBitMask;
		mov ebx, eax;

		mov eax, [edi];
		and eax, dwGRBBitMask;

		mul nAlphaDestBit;
//		shl eax, cl;
		shr eax, 5;
		and eax, dwGRBBitMask;
		or  edx, eax;

		or  edx,ebx;//�λ����ϱ�
		mov [edi],edx;

		add edi, 4;
		add esi, 4;
		
		pop ecx; // ī��Ʈ ����..
		dec ecx;
		jnz COPY_LOOP;

END_LOOP:
	}
}
*/