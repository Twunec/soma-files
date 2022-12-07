// UserManager.h: interface for the CUserManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USERMANAGER_H__A8E67521_39D1_11D3_8422_00105A6B97E2__INCLUDED_)
#define AFX_USERMANAGER_H__A8E67521_39D1_11D3_8422_00105A6B97E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class NODE;
class CPathFind;
class CDDSurface;
class SM_MapManager;
class CUser;
class CMagic;
class CMagicComet;
class CBlood;
class CArrowManager;

typedef CMap<int, int, CUser *, CUser *> MAP_USER;
typedef CTypedPtrArray<CPtrArray, CUser*> ARR_USER;
typedef CTypedPtrList<CPtrList, CMagic*> LST_MAGIC;

#define	UM_UID_INVALID		-1

#define BEATEDMOTION         1
#define BEATEDSOUND          2
#define BEATEDEFFECT         3
#define ATTACKMOTION         4
#define ATTACKSOUND          5
#define ATTACKEFFECT         6
#define ATTACKFAIL           7

//////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ���̺�� �����͸� ���� ����ü
typedef struct _TAG_MAGIC_TABLE
{
	int		m_nTableNum		; //���̺� ���� ����
//	CString m_strMagicName	; //�����̸�
	int		m_nAttackType	; //��������
							  //1)ĳ���Ϳ� ȿ�� 2)�߻�Ǿ� ��ǥ���� ���ư��� ���� 3)ĳ���Ϳ� ȿ�� �� ���ӵǴ� ����

	short   m_vMethod		; //��Ŷ����
							  //1)PKT_ATTACK_ARROW 2)PKT_ATTACK_MAGIC_RAIL 3)PKT_MAGIC_CIRCLE	
	int		m_nDes			; //������ �� ��� ����
							  //1)�ڽ� 2)�ڽ�/Ÿ�� 3)Ÿ��
	int		m_nStPreMagic	; //ĳ���� ���ʿ� �׷��� �׸�
	int		m_nStPostMagic	; //ĳ���� ���ʿ� �׷��� �׸�. 0�̸� ������ ����..
	int		m_nStTime		; //���ư��� ������ ���� �ð�....

	int		m_nFlyMagic		; //���ư��� ����...
	int		m_nEffecKind	; 
							  
	int		m_nFireNum		; //���󰡴� ����

	int		m_nEndPreMagic	; //��� ĳ���� ���ʿ� �׷��� �׸�
	int		m_nEndPostMagic	; //��� ĳ���� ���ʿ� �׷��� �׸�
//	int		m_nEndTime		;

//	int		m_nConPreMagic	;
//	int		m_nConPostMagic	;
	int		m_nConType		; //���ӵǴ� ������ Ÿ��...
	int		m_nConTime		;
} _MAGIC_TABLE;

//////////////////////////////////////////////////////////////////////////////////////////////////
// ���� ������ ���� ������ ����Ʈ�� ������ ����ü
typedef struct _TAG_SET_MAGIC_INFO
{
	_MAGIC_TABLE		m_stMagicTable;
	int					m_nSorUid	  ;
	CArray<int , int>	m_arrDestUid  ;
	DWORD				m_dwNowTime   ;
	BOOL				m_bReady	  ; //�����غ� �ʿ��� �����ΰ�? 
	int 				m_nSIndex	  ; //��Ŷ�� ���´°�?
	int					m_nDir		  ; //����������� 100�̸� ���⿡ ������� ����
	CMagicComet*		m_Comet		  ; //������ �ٸ� 
} _SET_MAGIC_INFO;

typedef struct _TAG_ACTION_INFO
{
	int  m_ActionId;
	int  m_ActionType;
	DWORD m_ActionTickTime;
} ACTION_INFO;

typedef struct _TAG_DEAD_INFO
{
	DWORD	m_dwDeadTime;	//���� �ð�
	CPoint	m_ptDeadPos;	//���� ��ġ
	int		m_nDeadUserId;	//���̵�
} DEAD_INFO;

typedef CTypedPtrArray<CPtrArray, ACTION_INFO *> ARR_ACTION_INFO;

class CUserManager  //���� ������
{
public:
	void Set3DMagic(int uid, TCHAR* strName, int nMagicType, int nHeight=0, int nWidth=0);//dspring_0731_3dxx

	void ChangItem(int uid, short fromindex, short toindex);// ���� ĳ���Ͱ� ������ �ٲپ�����..���� ���ε� ����..
	void ChangItem(short fromindex, short toindex);// ���� �κ��丮���� ���� �κ��丮��..�Ǵ� �ݴ�..
	BOOL SendChang_Item(short fromindex, short toindex);
	void Set_MyInv_Data_All(int uid, PBYTE bypData);


	BOOL MagicChar( _SET_MAGIC_INFO* stSetMagicInfo );
	void ApplyMagicEx();
	void ApplyConMagic();
	void ApplyConMagic( int t_index, CUser* pUser );
	void UserAppliedMagic( int uid, BYTE num, short* magic_index, DWORD* dwConTime );
	void ReadMagicTable(int bSuccess, int iSorUid, short Mp, DWORD exp, int *iDestUid,short *pHP,int nDstUidNum, int magicindex, DWORD dwConTime, int Dir = 100);
	void ReadMagicTable(int bSuccess, int iSorUid, int nDestUid, int magicindex, DWORD dwStartTime, int Dir = 100);
	void MagicTableInit();
	void DeleteMagic(int iDestUid);
	void PoisonAffect(int nDesUid,short HP);
	void CharStateChange( int nDestUid, DWORD dwStatus );
	void MagicAttackKind( _SET_MAGIC_INFO* stSetMagicInfo, int nSorUid, int* pDesUid, int nDestNum );
	void SetMagicComet(  _SET_MAGIC_INFO* stSetMagicInfo, int nSorUid, int* pDesUid, int nDestNum );

	BOOL FlyMagicChar( _SET_MAGIC_INFO* stSetMagicInfo );
	BOOL ConMagicChar( _SET_MAGIC_INFO* stSetMagicInfo );
	BOOL FlyMagicComet( _SET_MAGIC_INFO* stSetMagicInfo );
	void Set3DMagicEx(int uid, int index, int nMagicType, int nHeight = 0, int nWidth = 0);
	int	 SetAimed3DMagicEx(CPoint ptSor, CPoint ptDst, int index, int nMagicType, int euid, int nSeries = 0);
	void Attack3DMagicEx(int suid, int euid, int index, int nSeries = 0);
	void Cyclone(int suid, int index);
	void AttackDir3DMagicEx(int suid, int nDir, int index, int nDestUid);
	int  SetDirAimed3DMagicEx(CPoint ptSor, int index, int nMagicType, int nDir, int nDestUid);

//void AttackDir3DMagicEx(int suid, int nDir, int index);
//int SetDirAimed3DMagicEx(CPoint ptSor, int index, int nMagicType, int nDir);
	
	//�������� ó���Լ� (uid�� ���� �������� nIndex�� ������ �ɾ���)
	int					SetAimedMagic(int nSorUid, int nDstUid, int nMagicIndex, int nMagicType);
	int					SetAimedMagic(CPoint ptSor, CPoint ptnDstUid, int nMagicIndex, int nMagicType, int nDesUid = -1,int nSeries = 1);
	int					SetAimed3DMagic(CPoint ptSor, CPoint ptDst, TCHAR* strName, int nMagicType, int euid);//dspring_0802_3dxx
	void				DrawDownMagics(CDDSurface *pSurface);	//�ٴڿ� �򸮴� ���� �׸���
	void				DrawUpMagics(CDDSurface *pSurface);		//������ ���� �׸���
	void				DrawUp3DMagics();//dspring_0802_3dxx

	void				SetMagic(int uid, int nIndex, int nMagicType, int height = 0);	//ĳ���Ϳ� ���� ���� ��
	void				RailAttackMagic(int bSuccess, int iSorUid, int bDir, int bLen, int nMagicType);
	int					SetViewMagic(int uid, int nMagicIndex, int nMagicType, int iDir, int iLen);
	//���ݰ��� ó���Լ�
	BOOL				SendAttack(int type = 0);							//������ �� (Focus�� �ִ� User�� ���������)
	BOOL				SendReadyMagic(int type);
	BOOL				SendMagicAttack(int type, short method, int nDestUid = -1, BYTE dir = 100);
	void				AttackChar(BYTE bSuccess, int iSorUid, CPoint ptSorPos, int iDestUid, CPoint ptDestPos);	//ȭ��ǥ��(Source�� Destination����)
	void                AttackMagic(int suid, int euid, int magic_type,int nSeries = 1);// ���� ���� �Ŵ��� �����ش�..����..���Լ��� ����..
	void				Attack3DMagic(int suid, int euid, TCHAR* strName);


	//�̵����� ��Ŷó�� �Լ�
	void				SetMoveFirst(CUser *pUser, CPoint ptDst, CPoint ptFirst);	//�������� �� ����ó��(Move First)
	void				SetMoveMid(CUser *pUser, CPoint ptDst);					//			"		  (Move Middle)
	void				SetMoveEnd(CUser *pUser, CPoint ptDst);					//			"		  (Move End)

	void				SetRunMoveFirst(CUser *pUser, CPoint ptDst, CPoint ptFirst, CPoint ptNext);	//�������� �� ����ó��(Move First)
	void				SetRunMoveMid(CUser *pUser, CPoint ptDst, CPoint ptNext);					//			"		  (Move Middle)
	void				SetRunMoveEnd(CUser *pUser, CPoint ptDst, CPoint ptNext);					//			"		  (Move End)

	void				ModifyUser(int uid, BYTE bDeadEnable, CString t_name, CString t_guild, int picnum, short moral, BYTE live, BYTE battle_mode, int x, int y, short item[10], BOOL bIsI=FALSE, short hair = 101 , short skin = 0);		//����� �������� (������ ����, ������ �߰�)
	void				DeleteUser(int uid, int x, int y);						//����� ���� ���ֱ�

	BOOL				IsMoveable(CPoint pt);									//�̵����� ��ġ�ΰ�?(�ʻ󿡼�)
	void				SetMoveableTable(SM_MapManager* pMapManager);			//PathFinder���� ����� Map Table ������ ���� (PathFinder������� �ʰ� ����)
	BOOL				IsInRange(CRect r, CUser *pUser, CPoint ptPos);			//Rect�� ������ ���ԵǴ°�(ȭ�鿡 ����?) ptPos�� ���� �׸��� Offset
	CPoint				GetMyPos();												//���� ��ġ ��������(Pixel)
	void				Move();													//������ �̵�ó��
	static	int			compare(const void *arg1, const void *arg2);			//ȭ�� �׸��� ���� User Quick Sort ���Լ�
	void				DrawUserSortY(int count);								//�׸� User�� Sorting��(Y�࿡ ���ؼ�)
	void				RenderUsers(CDDSurface *pSurface, CPoint ptMapOffset);	//������ �׸���
	void				InHouseRenderUsers(CDDSurface *pSurface, CPoint ptMapOffset);
	//void				OutHouseDrawObj(CDDSurface *pSurface, CPoint ptMapOffset);

	CUser*				GetUserWithPos(CPoint ptPixelPos, CPoint ptMapOffset);	//������ ��ġ�� �ִ� ������ ����?(Pixel����)
	CUser*				GetUserWithCellPos(CPoint ptCellPos);					//				"				(Cell����)
	CUser*				GetUserWithUid(int uid);								//User Id�� �̿��� User��������
	int					GetUserNum() {return m_mapUser.GetCount();}				// ���?
	CUser*				GetMe();												//������ ��������
	int					GetFocusedUidInOthers() {return m_iCurFocusUidInOthers;}//Focus�� ������� ����? (�� ����)
	void				RemoveUser(int index);									//������ Index�� ���� ����
	void				SetMyUserId(int iUid){m_iMyUserId = iUid;}				//���� ���� Id����
	BYTE				GetDirection(CPoint ptMyPos, CPoint ptDstPos);
	int					GetClientDirection(CPoint ptStart, CPoint ptEnd);		//Ŭ���̾�Ʈ�� ����

	void				RemoveAllData();
	void				RemoveAllDataWithoutMe();
	void                HpMpRecovery(PBYTE bypData);
	
	CUserManager();
	virtual ~CUserManager();

//protected:
public:
	BOOL m_bMyCovered;
	int  m_nCoverDegree;
	int m_ReadyOK;
	// �����̸� �ָ鼭 ���۽�Ű�� �κе�.
	void ActionProcess();
	void ActionMotion(int uid, int type, int delay_time);
	int m_ActionCount;
	int  m_ActionId[50];// ���Ǵ�� 50���� ��Ҵ�. �þ߿��� �����ϴ� ���۵��� �������� �˳��Ҳ� ���Ƽ�..
	int  m_ActionType[50];
	DWORD m_ActionTickTime[50];




	CPoint GetMyCellPos();
	void				UserDead(int uid, int  x, int y);
	void				PreUserDead(int uid, int x, int y);
	void				SetUserDead();

	int					GetMapData(CPoint pt);
	int					GetHouseMapData(CPoint pt);
	int					m_iMyUserId;		//�ڽ��� UserId
	int					m_iCurFocusUidInOthers; //Focus����? (������) Index

	CUser*				m_pMe;
	CUser*				m_arrDrawUser[500];	//������ �������� �ƴ�(�׸������ѿ�) (��ȭ�鿡 �ʿ��� ����: 300(20*15))
	CUser*				m_arrDrawDeadUser[1000];	//������ �������� �ƴ�(�׸������ѿ�)
	MAP_USER			m_mapUser;			// ���� ������ ���� ���
	BOOL				m_bCursorInRange;	//������ ���콺 ��ǥ�� ������ġ�� �ִ��� �˻�.
	CBlood*				m_Blood;
	CArrowManager*		m_Arrow;

	LST_MAGIC			m_lstMagic;	//���ο��� �ɸ��� ������ �ƴ϶� ������� �ɸ��� ����
	CMagicComet*		m_Comet;	
	CPathFind*			m_pPathFind;//���� ������� ����(�ʼӼ� ������)
	NODE*				m_pNode;	//������� ����
	CArray< _SET_MAGIC_INFO*, _SET_MAGIC_INFO* > m_arrSetMagicInfo;
	CArray< _MAGIC_TABLE*	, _MAGIC_TABLE*	   > m_arrMagicTableInfo;
	CArray< DEAD_INFO       , DEAD_INFO        > m_arrDeadUserInfo;
	ARR_ACTION_INFO		m_arrActionInfo;
};

#endif // !defined(AFX_USERMANAGER_H__A8E67521_39D1_11D3_8422_00105A6B97E2__INCLUDED_)
