// Magic.h: interface for the CMagic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAGIC_H__652BC4ED_5F86_11D3_8424_00105A6B96E7__INCLUDED_)
#define AFX_MAGIC_H__652BC4ED_5F86_11D3_8424_00105A6B96E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMagicManager;
class CMagicRes;
class CDDSurface;

#define MAGIC_TYPE_UP		0
#define MAGIC_TYPE_DOWN		1
#define MAGIC_TYPE_POSION   2 // ������ ��ġ�� ��Ÿ���� �Ѵ�.
#define MAGIC_TYPE_LOOP     3 // ������ ���� ����.
#define MAGIC_TYPE_NOTALPHA_UP		4
#define MAGIC_TYPE_NOTALPHA_DOWN	5



typedef struct
{
	CPoint	m_ptPos;	//���ư��� ������ ����� ��ǥ
	int		m_nDir;		//	"                    ����
} MR_CELL;	//Magic Routing cell

typedef struct
{
	int		m_nMagicIndex;	//������ �ε���
	int		m_nCurFrame;	//������ �׷����� ���� ������
	int		m_nFrame;		//���� ���ҽ��� �� ������
	int		m_nMagicType;	//������ Ÿ��
	DWORD	m_dwLastTick;	
	BOOL	m_bShowContinue;//������ �ݺ��ؼ� �ٽ� �׸�������.....
	int		m_nHeight;
} MAGIC_INFO;//dspring_0720	

typedef struct
{
	CString	m_strName;
	int		m_nMagicType;
	BOOL	m_bShowContinue;
	int		m_nWidth;
	int		m_nHeight;
	DWORD	m_dwTime;
	int		m_nCurFrame;
	int		m_nFrame;
} MAGIC3D_INFO;//dspring_3dxx	

class CMagic  
{
public:
	//*********************************************
	//�ڽ��� User��ü�� ������ ��� ����ϴ� �Լ���
	//*********************************************
	//������ Frame�� �׸����  True �� return��
	BOOL					DrawMagic(CDDSurface *pSurface);
	BOOL					DrawMagic(CDDSurface *pSurface, int x, int y, int Alpha = 1, BOOL bNext = FALSE);//dspring_0721
	BOOL					DrawFlying3DMagic();//dspring_0802_3dxx
	BOOL					DrawFlying3DMagic(int nDir, int x, int y);//dspring_0802_3dxx
//	BOOL					DrawMagic(CDDSurface *pSurface, int x, int y, int Alpha = 1);//soma_0721
	//BOOL					SetMagicRes(int nIndex);//soma_0720
	BOOL					SetMagicRes(int nIndex,int MagicType=0);//dspring_0720
	void					SetMagicInfo( int index , int MagicType );//dspring_0720
	BOOL					SetFly3DMagicRes(TCHAR* strName, CPoint startPos, CPoint EndPos, int &nFirstDir, int nMagicType);//dspring_0802_3dxx
	BOOL					SetFly3DMagicResEx(int index, CPoint startPos, CPoint EndPos, int &nFirstDir, int nMagicType, int nSeries = 0); //��ǥ�� �ʻ��� ��ǥ
	void					Set3DMagicEx(int index, int nMagicType, int height = 0, int nWidth=0);//dspring_0802_3dxx
	void					Set3DMagic(TCHAR* strName, int nMagicType, int height = 0, int nWidth=0);//dspring_0802_3dxx
	BOOL					Draw3DMagic( int x, int y, BOOL bNext = FALSE);//dspring_0802_3dxx

	int						GetMagicAttackDesUid(){ return m_nDstUid;}//dspring_0722
	void					SetMagicAttackDesUid( int uid ){ m_nDstUid = uid;}//dspring_0722
	//*******************************************************
	//��ü�� ������ ����Ǵ� ������ �׸� ��� ����ϴ� �Լ���
	//*******************************************************
	BOOL					SetDirFly3DMagicResEx(int index, CPoint startPos, int nDir, int nMagicType); //��ǥ�� �ʻ��� ��ǥ
	void					RouteDirPositon(CPoint ptStart, int nDir);
	BOOL					SetCycloneMagicRes(int index, CPoint ptSPos, int nMagicType, int nSRadians );
	void					RouteCyclone( CPoint ptSPos, int nSRadians );

	//�ٱ׸���� TRUE return
	BOOL					DrawFlyingMagic(CDDSurface *pSurface);
	//Cell�̵��� �Ǹ� TRUE return
	BOOL					DrawFlyingMagic(CDDSurface *pSurface, int nDir, int x, int y); //���� �Լ����� ���
	int						DirStartFrame(int nDir, int nResMaxFrame);
	BOOL					SetFlyMagicRes(int nIndex, CPoint ptStart, CPoint ptEnd, int &nFirstDir,int nSeries);	//����Resource Load�� �ʱ����� ����
	void					RoutePositon(CPoint ptStart, CPoint ptEnd, int nSeries = 0);	//���ư��� ���� ��������(����:����)
	BOOL					IsFlyingMagic() {return m_bTypeFlying;}		

	BOOL					IsDownMagic() {return (BOOL)(m_nType==MAGIC_TYPE_DOWN);}	//�Ʒ� �򸮴� �����ΰ�?
	void					SetMagicType(int nType) {m_nType = nType;}					//���� Type����
	int                     GetMagicType() { return m_nType; }

	void					SetLastBeatEffect(int nDstUid);//���� ������ �´� ȿ�� ������ ��� ����
	CMagic();
	virtual ~CMagic();

	static	CMagicManager*	pMagicManager;					//���� Resource������ backup ptr(CChildView::MagicManager)
	static	DWORD			dwMagicMoveDelay;				//���ư��� �ӵ� Delay

public:
	CPoint                  m_Pos;// 
	int                     m_nsUid;//������ ����� ��� �Ƶ�..
	int                     m_nDir;
	int                     m_nCount;
	int                     m_height;
	CArray<MAGIC_INFO* ,MAGIC_INFO*> m_arrMagicInfo;//dspring_0720���������� ������ �ִ� array

protected:
	int						m_nDstUid;
	int						m_nType;	//������ ���⼺ (�Ʒ� �򸮴� �����ΰ� , ���� ���� �����ΰ�?);
	BOOL					m_bTypeFlying;
	DWORD					m_dwLastMoveTick;	//������ �̵��ӵ��� �����ϴ� �ð�
	int						m_nCurDir; //���ư��� ������ ��� ���ư��� ����
	int						m_nFrame;	//������ Frame��(��ü �� Frame)
	int						m_nCurFrame;	//���� �׸��� ������ Frame
	CMagicRes*				m_bpMagicRes;	//���� Resource�� ���� ������(���ҽ��� MagicManager�� ����)
	DWORD					m_dwLastTick;	//������ Frame��ȭ�� ����
	int						m_nResIndex;	//MagicManager������ Resource Index
	
	CArray<MAGIC3D_INFO*, MAGIC3D_INFO*>	m_arr3DMagicInfo;//3dxx
	CList<MR_CELL, MR_CELL>	m_lstMagicRoutingCell;	//������ ������� ��(���ư��� ���� �� ���)
};

#endif // !defined(AFX_MAGIC_H__652BC4ED_5F86_11D3_8424_00105A6B96E7__INCLUDED_)
