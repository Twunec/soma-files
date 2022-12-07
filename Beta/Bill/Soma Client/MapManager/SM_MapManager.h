// SM_MapManager.h: interface for the SM_MapManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SM_MAPMANAGER_H__0CAC0DD9_11ED_11D3_8422_0020AF9F40BD__INCLUDED_)
#define AFX_SM_MAPMANAGER_H__0CAC0DD9_11ED_11D3_8422_0020AF9F40BD__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSgrRes;
typedef CTypedPtrArray <CPtrArray, CSgrRes*> AP_SGRRES;

class CMapCell;
typedef CTypedPtrArray <CPtrArray, CMapCell*> APA_MAPCELL;

class CSpriteUnit;
typedef CTypedPtrArray <CPtrArray, CSpriteUnit*> AP_SPRITEUNIT;

typedef CTypedPtrArray <CPtrArray, CPoint*> AP_USERPOS;

class CDirectDraw;
class CDDSurface;


//��ü �� ������
class AFX_EXT_CLASS SM_MapManager  
{
public:
	CPoint					PixelToCell(CPoint ptPixel);	//Pixel��ǥ�� 32X32�� �� ��ǥ��...
	CPoint					CellToPixel(CPoint ptCell);		//32X32�� ����ǥ�� pixel��ǥ��

	//���ο� �޸𸮸� �Ҵ��ϰ� �ǹǷ� �ݵ�� �θ������� ������ �־����.
	BYTE**					GetMoveableTable(int &dimx, int &dimy);	//�̵������θ� ������ ���ο� Set �����
	short					**GetHouseTable(int &dimx, int &dimy);	//�ǹ������θ� ������ ���ο� Set �����

	int						SetDarkLevel(int iPercent, BOOL bAbsolute=TRUE);	//���� ��ӱ� ���� ����: bAbsolute�̸� ���� ���, �ƴϸ� ���� ����� ����� ���
	CPoint					SetCenterPos(CPoint pos);	//Map�� ������ġ�� Pixel������ return�� : �ʱ׸����� �߽��� �� ��ġ ����(�ڽ��� ���̵� ��ġ�� �߽��� ��)
	CPoint					GetMapStartPos();			//Map�� ������ġ�� Pixel������ return��
	void					DrawPreSprite(CDDSurface* pDestSurf);	//ĳ���ͺ��� ���� �׸� Sprite�׸���
	void					DrawPostSprite(CDDSurface* pDestSurf);	//ĳ���ͺ��� ���߿� �׸� Sprite�׸���
	void					DrawAllSprite(CDDSurface* pDestSurf, int Number);	//0509 ���Ӱ� ������ �ٲٴ� �Լ� ���� �Լ� �ΰ��� ��ü..

	void					DecidePrePostSprite();					//����, Ȥ�� ���߿� �׸��� ����
	BOOL					IsPreCondition(CRect r, CSpriteUnit *pSpriteUnit);	//���� �׸� �����ΰ�? (pSpriteUnit)
	BOOL					IsPostCondition(CRect r, CSpriteUnit *pSpriteUnit); //���߿� �׸� �����̰�? (pSpriteUnit)

	CPoint					DrawTile(CDDSurface* pDestSurf);		//Ÿ�� �׸��� : ��ǥ�� ������ SetCenterPos�� ���� �̸� ������ ����
	BOOL					LoadMap(CString szFileName, BOOL bFileNameContainPath=FALSE); //Map������ Load�� (mmf���� �ε�: �ڵ����� �ʿ��� Sgr���ϵ� �ε���)
	BOOL					GetMapStatus() {return m_bLoadStatusOk;}	//Load�� ���������� �̷�� ���°�?
	void					InitManager(CDirectDraw* pDD, HWND hwnd);	//MapManager�ʱ�ȭ (DirectDraw�� MainWindow�� Handle
	void					EndManager();								//MapManager��� ����

	//Sgr���÷�ƾ
	CString					GetSgrFileName(int index);					//������ Index�� �ش��ϴ� Sgr������ �̸���?
	BOOL					LoadSgr(int index);							//������ Index�� Sgr���� �ε�
	CSgrRes*				GetSgrRes(int index);						//Index�� �̿��� CSgrResŬ���� ��������

	SM_MapManager();
	virtual ~SM_MapManager();

protected:
	BOOL					IsAnimationTime(int iAnimationMode);		//���� Animation��ų �ð��ΰ�?
	BOOL					IsInSgrList(CList<int, int> &SgrList, int iSgrIdx); //iSgrIdx�� SgrList�� ������ �ִ°�?
	BOOL					InitializeSgrs(CList<int, int> &SgrList);	//�־��� SgrList�� �̿��ؼ� SgrResource�� ����(������ Load�ϰ�, �ִµ� List�� ������ Unload)...
	BOOL					LoadSpriteUnit(CArchive &ar);				//SpriteUnit �� Load��
	void					RemoveSpriteUnit();							//SpriteUnit �� ������
	void					RemoveMapCellData();						//MapCell������ ����
	void					SetMapDimension(CSize dimMap);				//���� Dimension�����ϰ� �׸�ŭ MapCell����


public:
	BYTE GetAreaNumber(CPoint posCell);
	int  IsHouse(CPoint PosCell);
	void ShowMapType(int type);
	void SetUserPos(CPoint UserPos, int index);
	BOOL IsHidden(CPoint PosCell);
	CSize GetMapDimension();
	BOOL LoadSmf(CString szFileName, BOOL bFileNameContainPath);// 
	BOOL LoadImf(CString szFileName, BOOL bFileNameContainPath);//imf..�ʵ���Ÿ�� �о� ���δ�.

	static	CDirectDraw*	sm_bpDirectDraw;							//DiretDraw ��ü�� ��� ������ �������
	static	HWND			sm_bRelatedHwnd;							//����� MainWindow Handle

	PBYTE*                  m_ppTable;
	PBYTE*                  m_ppHiddenTable;
	PBYTE*                  m_ppEventTable;
	PBYTE*					m_ppAreaNumber;
	short					**m_ppHouseTable;
	int						m_cell_width;								// ���� �� ������..
	int						m_cell_height;

	int                     m_View_Flag;// Ǯȭ������ ���� ȭ������ �÷��� ������ �ϰ��Ѵ�. 0 - Ǯȭ�� 1 - ���� ����ȭ�� 2 - ������ ����ȭ��
	AP_USERPOS				m_apUsersPos;//Pixel ����					// ȭ��� �ִ� �������� ��ġ�� ��������Ʈ�� ������ ���� �ذ�
	CPoint                  m_UsersPos[500];// �� ȭ��� ������ ĳ���� ��ġ ����..��������Ʈ ������ ����������..
	int                     m_UserSize;// ���� �迭�� ����� ��� �ִ��� üũ..

	int                     m_PreSprCount;
	int                     m_PostSprCount;
	int                     m_Spr_Y[500];
	int                     m_Spr_Sky[500];
//	int						m_PreSprNumber[500];// ���Ƿ� 500
//	int						m_PostSprNumber[500];


protected:
public:
	CString					m_szExePath;								//���� ���丮
	AP_SGRRES				m_apSgrRes;									//SgrRes�� �������
	APA_MAPCELL				m_apaMapCell;								//MapCell�� �������(Dimensionũ��)
	AP_SPRITEUNIT			m_apSpriteUnit;								//SpriteUnit�� �������(Sgr�� Sprite�ʹ� �ٸ�, �ʿ����Ϳ��� ��������Ʈ�� ���� ��ġ���� ����� Sprite����)
	AP_SPRITEUNIT			m_apPreDrawSpriteUnit;						//Backup�� ������ ���� ���(���� �׸���)
	AP_SPRITEUNIT			m_apPostDrawSpriteUnit;						//Backup�� ������ ���� ���(���� �׸���)
	CSize					m_dimMap;									//���� ũ��// ���̾Ƹ�� �� ũ�� ����..����..�̻�Ÿ.
	CString					m_szMapName;								//���� �̸�(*.mmf)
	BOOL					m_bLoadStatusOk;							//Load���� ����
	CPoint					m_posCenter;//Pixel ����					//�׸��� �߽��� �� ��ġ(ĳ������ Center��ġ)
	CPoint					m_MapStartIndex;							//m_posCenter�� �������� ������ LeftTop�� �׷��� Cell�� Index
	CPoint					m_offsetMap;								//��Ʈ ������ MapStartIndex�� �󸶳� �������� ���� �ϴ°�? (���� cell������ ������ ���� �ƴ϶� Pixel������ ����: m_posCenter����)
	DWORD					m_dwTickAniTileStart;						//Tile Animation �ð� ô��
	DWORD					m_dwTickAniSpriteStart;						//Sprite Animation �ð� ô��
	int						m_iAbsDarkLevel;							//�������� ���(100: ���� 50: ��� ������ ����)
};

#endif // !defined(AFX_SM_MAPMANAGER_H__0CAC0DD9_11ED_11D3_8422_0020AF9F40BD__INCLUDED_)
