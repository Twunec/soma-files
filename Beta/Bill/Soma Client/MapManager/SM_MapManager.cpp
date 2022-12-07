// SM_MapManager.cpp: implementation of the SM_MapManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SM_MapManager.h"
#include "../DManage/BB_Direct.h"
#include "SgrRes.h"
#include "MapCell.h"
#include "SpriteUnit.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//�ִ� ���������� SGR�� ���� ����
#define MAX_SGRNUM	1024

#define TILE_ANIMATION		0
#define SPRITE_ANIMATION	1

BYTE g_vBitMask[8] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80};

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDirectDraw* SM_MapManager::sm_bpDirectDraw = NULL;
HWND SM_MapManager::sm_bRelatedHwnd = NULL;

SM_MapManager::SM_MapManager()
{
	m_apSgrRes.SetSize(MAX_SGRNUM);
	m_dimMap.cx = m_dimMap.cy = 0;
	m_bLoadStatusOk = FALSE;
	m_dwTickAniTileStart = GetTickCount();
	m_dwTickAniSpriteStart = m_dwTickAniTileStart;

	m_MapStartIndex.x = 0;
	m_MapStartIndex.y = 0;
	m_posCenter.x = 400;
	m_posCenter.y = 300;
	m_offsetMap.x = 0;
	m_offsetMap.y = 0;
	m_iAbsDarkLevel = 100;

	m_ppTable = NULL;
	m_ppHiddenTable = NULL;
	m_ppEventTable = NULL;
	m_ppHouseTable = NULL;
	m_ppAreaNumber = NULL;

	m_View_Flag = 0;// 0-Ǯ 1-�� 2-��

	m_PreSprCount = 0;
	m_PostSprCount = 0;

	for(int i =0;i<500;i++)
	{
		m_Spr_Y[i] = -1;
		m_Spr_Sky[i] = -1;
	}

}

SM_MapManager::~SM_MapManager()
{
	EndManager();
//	#define SAFE_DELETE(p)  { if(p) { delete (p);     (p)=NULL; } }
//	#define SAFE_DELETES(p) { if(p) { delete[] (p);	  (p)=NULL; } }

	//m_ppHiddenTable;
}

CSgrRes* SM_MapManager::GetSgrRes(int index)
{
	return m_apSgrRes[index];
}

BOOL SM_MapManager::LoadSgr(int index)
{
	if (m_apSgrRes[index]) return TRUE;

	//�ӽ�..
//	if(index == 18) index = 1;// ���� �̻��ؼ�..�̷��� �ѹ� �о�پ���..

	CString szFileName = GetSgrFileName(index);
	CSgrRes *pSgrRes = new CSgrRes;
	if (pSgrRes->Load(szFileName))
	{
		m_apSgrRes.SetAt(index, pSgrRes);
		return TRUE;
	}
	delete pSgrRes;
	return FALSE;
}

CString	SM_MapManager::GetSgrFileName(int index)
{
	ASSERT(!m_szExePath.IsEmpty());
	CString szFileName = m_szExePath;
	CString szTmp;
	//szTmp.Format("SGRES\\SG-%d.SGR", index);	//���ؽ��� Sgr���� �̸����� ��ȯ
	szTmp.Format("SGRES\\SG-%d.SGR", index);	//���ؽ��� Sgr���� �̸����� ��ȯ
	szFileName += szTmp;
	return szFileName;
}

BOOL SM_MapManager::LoadMap(CString szFileName, BOOL bFileNameContainPath)
{
	EndManager();
	m_apSgrRes.SetSize(MAX_SGRNUM);

	ASSERT(!m_szExePath.IsEmpty());

	CFile file;
	CString szFullPath;
	//if (!bFileNameContainPath) szFullPath.Format("%sSGRES\\%s", (LPCTSTR) m_szExePath, (LPCTSTR) szFileName); //����� �н��ΰ�� : Application���۽� Current���丮�� Exe������ ��ġ�� �����ϹǷ� ��밡��
/*	if (!bFileNameContainPath) szFullPath.Format("%sSGRES\\%s.mmf", (LPCTSTR) m_szExePath, "test"); //����� �н��ΰ�� : Application���۽� Current���丮�� Exe������ ��ġ�� �����ϹǷ� ��밡��
	else szFullPath = szFileName;
	if (!file.Open(szFullPath, CFile::modeRead|CFile::typeBinary))
	{
		TRACE("������ ���� %s Open����\n");
		return FALSE;
	}
//	TRACE("mmf ���� ���..");

	CArchive ar(&file, CArchive::load);

	int sgrCount;
	int vVersion;
	ar >> sgrCount;		//����ϴ� Sgr�� ����

/////////////////////////////////////////////////////�߰�
	if(sgrCount < 0)// ������ �߰����ø�...�ι�°�� sgr���̴�...
	{
		vVersion = sgrCount;
		ar >> sgrCount;
	}
	else vVersion = 0;
/////////////////////////////////////////////////////

	

	CList<int, int> SgrList;
	int	sgrnumber;
	int t_count;
	CString t_str;

	while (sgrCount)      
	{
		ar >> sgrnumber;
		
		sgrCount--;
//	}

//		if (!InitializeSgrs(SgrList))	//SgrList������ �ʿ��� Sgr Resource�� �ε���. (������� �ʴ� Sgr�� ����)
//		{
//			ar.Close();
//			file.Close();
//			return FALSE;
//		}
		// �̺κ��� ���Ϸ��� �������? �ӽ�
		ar >> t_count;
		for(int i=0; i < t_count;i++)
		{
			ar >> t_str;
		}
		ar >> t_count;
		for(i=0; i < t_count;i++)
		{
			ar >> t_str;
		}
	}

	CSize mapSize;
	ar >> mapSize.cx >> mapSize.cy;	//���� ũ�� �ε�
	SetMapDimension(mapSize);		//���� ũ�� ��ŭ MapCell�� ����

	//(���)�ٲ����...�� ����Ÿ�� �о� ���϶�..
	for (int i=0; i<=mapSize.cx; i++)
	{
		for (int j=0; j<=mapSize.cy; j++)
		{
			m_apaMapCell[i][j].Load(ar);	//MapCell�� �ε���
		}
	}

	ar.Close();
	file.Close();

*/	///////////////////////////////////////////////////
	//smf ������ ������ �ǰڳ�...^^
 
//	LoadSmf(szFileName, bFileNameContainPath);
	/////////////////////////////////////////////////////
	//imf...
	LoadImf(szFileName, bFileNameContainPath);
	////////////////////////////////////////////////////

	m_bLoadStatusOk = TRUE;
//	m_szMapName = szFullPath;
	return TRUE;
}

BOOL SM_MapManager::LoadSpriteUnit(CArchive &ar)	//Resource�� �ƴ� Sprite �� ��ġ�� ���� �ε�
{
	RemoveSpriteUnit();

	CSpriteUnit::m_bpMapManager = this;

	int		iSpriteCount;
	BOOL	bErrorOccur = FALSE;

	ar >> iSpriteCount;				//Sprite Unit �?
	TRACE("iSpriteCount = %d\n", iSpriteCount);

	m_apSpriteUnit.SetSize(iSpriteCount);

	
	CSpriteUnit *pSpriteUnit;
	for (int i=0; i<iSpriteCount; i++)
	{
//		TRACE("��� ���� �ǳ�? %d \n", i);
		pSpriteUnit = new CSpriteUnit;
		if (pSpriteUnit->Load(ar, i))
		{
			m_apSpriteUnit.SetAt(i, pSpriteUnit);
		}
		else
		{
			delete pSpriteUnit;
			bErrorOccur = TRUE;
		}
	}

	//Draw�� ����� �׸���� Array
	m_apPreDrawSpriteUnit.SetSize(iSpriteCount+1);		//NULL ����
	m_apPostDrawSpriteUnit.SetSize(iSpriteCount+1);		//NULL ����
	return bErrorOccur? FALSE:TRUE;	
}

BOOL SM_MapManager::InitializeSgrs(CList<int, int> &SgrList)
{
	POSITION pos = SgrList.GetHeadPosition();
	int iSgrIndex;
	while (pos)
	{
		iSgrIndex = SgrList.GetNext(pos);
		if (!LoadSgr(iSgrIndex))			//����Ʈ�� �����ϴ� ��� SgrResource�� �ε���(�ִ� ���� �ٽ� �ε����� ����)
		{
			TRACE("%d Sgr�ε����\n");
			return FALSE;
		}
	}
	TRACE("sgr ���� ���..");

	//�ʿ����� ���� SgrRes�ı�
	int size = m_apSgrRes.GetSize();
	for (int i=0; i<size; i++)
	{
		if (m_apSgrRes[i]&&!IsInSgrList(SgrList, i))
		{
			delete m_apSgrRes[i];
			m_apSgrRes.SetAt(i, NULL);
		}
	}

	return TRUE;
}

BOOL SM_MapManager::IsInSgrList(CList<int, int> &SgrList, int iSgrIdx)
{
	POSITION pos = SgrList.GetHeadPosition();
	int iTmp;
	while (pos)
	{
		iTmp = SgrList.GetNext(pos);
		if (iTmp==iSgrIdx) return TRUE;
	}
	return FALSE;
}

void SM_MapManager::RemoveMapCellData()
{
	int size = m_apaMapCell.GetSize();
	for (int i=0; i<size; i++)
	{
		if (m_apaMapCell[i])
		{
			delete[] m_apaMapCell[i];
		}
	}
	m_apaMapCell.RemoveAll();
}

void SM_MapManager::RemoveSpriteUnit()
{
	int size = m_apSpriteUnit.GetSize();
	for (int i=0; i<size; i++)
	{
		if (m_apSpriteUnit.GetAt(i)) delete m_apSpriteUnit.GetAt(i);
	}
	m_apSpriteUnit.RemoveAll();

	m_apPreDrawSpriteUnit.RemoveAll();	//m_apPreDrawSpriteUnit�� ���� �����͸� ��� �ִ°��� �ƴ϶� m_apSpriteUnit�� �����͸� ��� ������ ����(�����͸�)
	m_apPostDrawSpriteUnit.RemoveAll();	//m_apPostDrawSpriteUnit�� ���� �����͸� ��� �ִ°��� �ƴ϶� m_apSpriteUnit�� �����͸� ��� ������ ����(�����͸�)
}

void SM_MapManager::SetMapDimension(CSize dimMap)
{
	RemoveMapCellData();
/*	m_apaMapCell.SetSize(dimMap.cx+1);		//X������ �Ҵ�
	CMapCell *pMapCell = NULL;
	CMapCell::m_bpMapManager = this;
	for (int i=0; i<=dimMap.cx; i++)
	{
		m_apaMapCell[i] = new CMapCell[dimMap.cy+1];	//Y������ �Ҵ�
	}
*/	m_dimMap.cx = dimMap.cx/2;
	if(dimMap.cx%2) m_dimMap.cx++;
	m_dimMap.cy = dimMap.cy/2;
	if(dimMap.cy%2) m_dimMap.cy++;
}

void SM_MapManager::InitManager(CDirectDraw* pDD, HWND hwnd)
{
	sm_bpDirectDraw = pDD;
	m_szExePath = CDirectDraw::GetExecutionPath();
	sm_bRelatedHwnd = hwnd;
}

void SM_MapManager::EndManager()
{
	int size = m_apSgrRes.GetSize();
	for (int i=0; i<size; i++)
	{
		if (m_apSgrRes[i]) delete m_apSgrRes[i];	//SgrResource �ı�
	}
	m_apSgrRes.RemoveAll();

	RemoveMapCellData();
	RemoveSpriteUnit();
	if(m_ppTable)
	{
		for(i = 0; i < m_cell_width; i++)
		{
			delete[] m_ppTable[i];
		}
		delete[] m_ppTable;
		m_ppTable = NULL;
	}
	if(m_ppHiddenTable)
	{
		for(i = 0; i < m_cell_width; i++)
		{
			delete[] m_ppHiddenTable[i];
		}
		delete[] m_ppHiddenTable;
		m_ppHiddenTable = NULL;
	}
	if(m_ppEventTable)
	{
		for(i = 0; i < m_cell_width; i++)
		{
			delete[] m_ppEventTable[i];
		}
		delete[] m_ppEventTable;
		m_ppEventTable = NULL;
	}
	if(m_ppHouseTable)
	{
		for(i = 0; i < m_cell_width; i++)
		{
			delete[] m_ppHouseTable[i];
		}
		delete[] m_ppHouseTable;
		m_ppHouseTable = NULL;
	}
	if(m_ppAreaNumber)
	{
		for(i = 0; i < m_cell_width; i++)
		{
			delete[] m_ppAreaNumber[i];
		}
		delete[] m_ppAreaNumber;
		m_ppAreaNumber = NULL;
	}
}

CPoint SM_MapManager::DrawTile(CDDSurface* pDestSurf)
{
	CPoint pos;
	int		xmax;
	int		ymax;

	//���ȭ���̵�
	xmax = 15;	//640*480�� 10*15�̹Ƿ�  �׸���ô� �Ѱ� �� �ʿ��� (�̵��� �϶� ����� ���ؼ�)
	ymax = 18;


	BOOL bAnimation = IsAnimationTime(TILE_ANIMATION); //�ִϸ��̼� �ð��� �ƴ°�? ������ Ÿ���� �ٲپ�� ��
	CMapCell *pMapCell;

	xmax = 14;	//640*480�� 10*15�̹Ƿ�  �׸���ô� �Ѱ� �� �ʿ��� (�̵��� �϶� ����� ���ؼ�)
	ymax = 17;

	int ViewMove = 0;
	if(m_View_Flag == 2)//������
		ViewMove = 6;

//	if (m_offsetMap.x==0) xmax = 13;	//�̵��ߵ� �ƴϰ� �� �´� ��� (X����)
//	if (m_offsetMap.x==0) xmax = 6;	//�̵��ߵ� �ƴϰ� �� �´� ��� (X����)
//	if (m_offsetMap.y==0) ymax = 16;	//�̵��ߵ� �ƴϰ� �� �´� ��� (Y����)
//	if (m_offsetMap.y==0) ymax = 11;	//�̵��ߵ� �ƴϰ� �� �´� ��� (Y����)

	CPoint ptMapStartPos;
	ptMapStartPos.x = m_MapStartIndex.x*64+m_offsetMap.x;	//���� Resource�� 64X32�� (�̵������� 32X32�� : ȥ������ �� ��)
	ptMapStartPos.y = m_MapStartIndex.y*32+m_offsetMap.y;

//	TRACE("��� ��ũ���� �������ؼ�...�� ��ġ x = %d, y = %d\n", ptMapStartPos.x, ptMapStartPos.y);

	for (int i=m_MapStartIndex.x + ViewMove; i<m_MapStartIndex.x+xmax; i++)
	{
		//6
		//pos.x = (i-m_MapStartIndex.x + ViewMove )*64-m_offsetMap.x;// ȭ���� �����϶�..�Ѹ��� ��ġ �ٲٱ�..
		pos.x = (i-m_MapStartIndex.x )*64-m_offsetMap.x;// ȭ���� �����϶�..�Ѹ��� ��ġ �ٲٱ�..
		pMapCell = m_apaMapCell[i];

		//for (int j=m_MapStartIndex.y+ 3; j<m_MapStartIndex.y+ymax; j++)
		for (int j=m_MapStartIndex.y; j<m_MapStartIndex.y+ymax; j++)
		{
//			if(j==30)
//				j=30;
			//5
			pos.y = (j-m_MapStartIndex.y )*32-m_offsetMap.y;
			if (bAnimation) pMapCell[j].RotateAnimation();	//Animation�̸� Ÿ�� �ٲٰ�
			pMapCell[j].Draw(pDestSurf, pos);				//���� ��ġ�� �׸�
		}
	}
	return ptMapStartPos;
}

void SM_MapManager::DrawAllSprite(CDDSurface* pDestSurf, int Number)
{
	CRect r(0, 0, 800, 500);
	r.OffsetRect(m_MapStartIndex.x*64+m_offsetMap.x, m_MapStartIndex.y*32+m_offsetMap.y);
	CSpriteUnit *pSpriteUnit = NULL;
	pSpriteUnit = m_apPreDrawSpriteUnit.GetAt(Number);	//���� �׸��� Array���� ������ �����ͼ� �׸�
	if (NULL==pSpriteUnit) return;
	pSpriteUnit->Draw(r, m_MapStartIndex, m_offsetMap, pDestSurf, FALSE);//�ǳ��� False�� ����(Alpha)���� �ʰ���

}

void SM_MapManager::DrawPreSprite(CDDSurface* pDestSurf)
{
	DecidePrePostSprite();			//�׸������� �����׸���, ���߱׸��� ����

	int size = m_apSpriteUnit.GetSize();
	CSpriteUnit *pSpriteUnit = NULL;
//	CRect r(0, 0, 640, 480);
	CRect r(0, 0, 800, 500);
	r.OffsetRect(m_MapStartIndex.x*64+m_offsetMap.x, m_MapStartIndex.y*32+m_offsetMap.y);

	for (int i=0; i<size; i++)
	{
		pSpriteUnit = m_apPreDrawSpriteUnit.GetAt(i);	//���� �׸��� Array���� ������ �����ͼ� �׸�
		if (NULL==pSpriteUnit) break;
		pSpriteUnit->Draw(r, m_MapStartIndex, m_offsetMap, pDestSurf, FALSE);//�ǳ��� False�� ����(Alpha)���� �ʰ���
	}
}

void SM_MapManager::DrawPostSprite(CDDSurface* pDestSurf)
{
	int size = m_apSpriteUnit.GetSize();
	CSpriteUnit *pSpriteUnit = NULL;
	CDDSurface*  lpPostSprite_Surface=NULL;

//	pSurface = new CDDSurface;
//	pSurface->Create(pDirectDraw, imageSize.cx, imageSize.cy, FALSE);

//	CRect r(0, 0, 640, 480);
	CRect r(0, 0, 800, 500);
	r.OffsetRect(m_MapStartIndex.x*64+m_offsetMap.x, m_MapStartIndex.y*32+m_offsetMap.y);

	for (int i=0; i<size; i++)
	{
		pSpriteUnit = m_apPostDrawSpriteUnit.GetAt(i);
		if (NULL==pSpriteUnit) break;
		pSpriteUnit->Draw(r, m_MapStartIndex, m_offsetMap, pDestSurf, TRUE);//�ǳ��� True�� ����(Alpha) �ϰ���
	}
}

void SM_MapManager::DecidePrePostSprite()
{
	BOOL bRotateAni = IsAnimationTime(SPRITE_ANIMATION);
	int size = m_apSpriteUnit.GetSize();
	CSpriteUnit *pSpriteUnit = NULL;

	//���� �׸��� ������ġ
//	CRect r(0, 0, 640, 480);
	CRect r(0, 0, 800, 600);
	int x,y;
	x=m_MapStartIndex.x;
	y=m_MapStartIndex.y;
	r.OffsetRect(x*64+m_offsetMap.x, y*32+m_offsetMap.y);
	//r.OffsetRect(m_MapStartIndex.x*64+m_offsetMap.x, m_MapStartIndex.y*32+m_offsetMap.y);

	int preCount = 0;
	int postCount = 0;
	int test = 0;
	m_PreSprCount = 0;
	m_PostSprCount = 0;

	CRect rSprite;
	CRect rTemp;

	for (int i=0; i<size; i++)
	{
		pSpriteUnit = m_apSpriteUnit.GetAt(i);
		if (NULL==pSpriteUnit) break;
		
		rSprite = pSpriteUnit->GetSpriteRect();
		rTemp = r;
		rTemp.IntersectRect(&r, rSprite);
		//r.IntersectRect(&rTemp, rSprite);

		if(rTemp.right > 0 && rTemp.bottom > 0) 
		{
			if (bRotateAni) pSpriteUnit->RotateAnimation();

			pSpriteUnit->m_House_In = 1;
			CPoint p = m_posCenter;// ���� ���� ��ġ�� ���� �ִ´�.
			p = PixelToCell(p);
			
			test = IsHouse(p);

			//if(test >= 0)
			pSpriteUnit->m_House_In = test;

			int pos_wide;

			if(pSpriteUnit->m_House_In == 205)// �� �ۿ� ������..
			{
				if(pSpriteUnit->m_House_Spec == NORMAL_SPRITE || pSpriteUnit->m_House_Spec == DOOR_HOUSE_SPRITE)// �ӽ�  ��� ���� �ȱ׸��� ��ƾ
				{
					if (IsPreCondition(r, pSpriteUnit)) 
					{
						if(m_PreSprCount > 500)
						{
							TRACE(" ������ ���� ����.. m_Spr_Y ũ�� ����\n");
							return;
						}						
						if(pSpriteUnit->m_House_Number != -1 )
						{
							pos_wide = pSpriteUnit->GetSpriteWide(r);
							pos_wide /= 3;
							m_Spr_Y[m_PreSprCount] = pSpriteUnit->GetSpriteY(r)-pos_wide;
							m_Spr_Sky[m_PreSprCount] = pSpriteUnit->m_Sky;
						}
						else
						{
							m_Spr_Y[m_PreSprCount] = pSpriteUnit->GetSpriteY(r);
							m_Spr_Sky[m_PreSprCount] = pSpriteUnit->m_Sky;
						}

						m_PreSprCount++;
						m_apPreDrawSpriteUnit.SetAt(preCount++, pSpriteUnit);
					}
					else if (IsPostCondition(r, pSpriteUnit))//  
					{
						// �ϳ��� ����..���߿� ���� ������� ���ַ���...
						if(m_PreSprCount > 500)
						{
							TRACE(" ������ ���� ����.. m_Spr_Y ũ�� ����\n");
							return;
						}
						m_Spr_Y[m_PreSprCount] = pSpriteUnit->GetSpriteY(r);
						m_Spr_Sky[m_PreSprCount] = pSpriteUnit->m_Sky;

						m_PreSprCount++;
						m_apPreDrawSpriteUnit.SetAt(preCount++, pSpriteUnit);
					}
				/*	if (IsPreCondition(r, pSpriteUnit)) 
					{
						m_PreSprNumber[m_PreSprCount] = i;// 
						m_PreSprCount++;
						m_apPreDrawSpriteUnit.SetAt(preCount++, pSpriteUnit);
					}
					else if (IsPostCondition(r, pSpriteUnit))//  
					{
						m_PostSprNumber[m_PostSprCount] = i;// 
						m_PostSprCount++;
						m_apPostDrawSpriteUnit.SetAt(postCount++, pSpriteUnit);
					}
					*/
				}
			}
			else// ���ȿ� �ִٸ�..���� �ִ� ���� �Ѳ��� ������ �������� ���� �״�� �ؾ߰���...--;;
			{
				if(pSpriteUnit->m_House_Number == pSpriteUnit->m_House_In)
				{
					if(pSpriteUnit->m_House_Spec == INNER_HOUSE_SPRITE)// || pSpriteUnit->m_House_Spec == DOOR_HOUSE_SPRITE)// 
					{			
						m_PreSprCount++;
						m_apPreDrawSpriteUnit.SetAt(preCount++, pSpriteUnit);//������ ��� ������.
					}
				}
						
			}
		}
	}
	m_apPreDrawSpriteUnit.SetAt(preCount, NULL);	//���߿� �׸���, ���� ���� Break�� ���� ������ ���ؼ�
	m_apPostDrawSpriteUnit.SetAt(postCount, NULL);	//���߿� �׸���, ���� ���� Break�� ���� ������ ���ؼ�
}

BOOL SM_MapManager::IsPreCondition(CRect r, CSpriteUnit *pSpriteUnit)
{
	//ĳ������ ��ġ: m_posCenter, Map�� �׸��� ������ġ : r
	ASSERT(pSpriteUnit);
	CRect rSprite = pSpriteUnit->GetSpriteRect();

	if (!r.IntersectRect(&r, rSprite)) return FALSE;
	int x;
	int y;

	CPoint p = m_posCenter;// ���� ���� ��ġ�� ���� �ִ´�.
	CPoint value;
	value = PixelToCell(p);
	x = value.x; y = value.y;

	if(!m_ppHiddenTable[x][y])// ������ �ƴϸ�..
	{
		// �ڽ��� ���翡 �ȼ�������...
		// ���� �������� �̰����� üũ�� �Ѵ�...���ķδ� �ȻѸ� ��������Ʈ��...
		//m_UsersPos[];
		for(int i=0; i<m_UserSize;i++)
		{
			if(pSpriteUnit->IsPosBehindSprite2(m_UsersPos[i].x, m_UsersPos[i].y)) 
				return FALSE;
		}
		return TRUE;
	}
	else
	{
		for(int i=0; i<m_UserSize;i++)
		{
			if(pSpriteUnit->IsPosBehindSprite2(m_UsersPos[i].x, m_UsersPos[i].y)) 
				return FALSE;
		}
	}


	if (pSpriteUnit->IsPosBehindSprite2(x, y)) return FALSE;
	
	return TRUE;
}

BOOL SM_MapManager::IsPostCondition(CRect r, CSpriteUnit *pSpriteUnit)
{
	ASSERT(pSpriteUnit);
	CRect rSprite = pSpriteUnit->GetSpriteRect();

	if (!r.IntersectRect(&r, rSprite)) return FALSE;
	int x;
	int y;

	CPoint p = m_posCenter;
	CPoint value;
	value = PixelToCell(p);
	x = value.x; y = value.y;

	if(m_ppHiddenTable[x][y])// �����̸�..
	{
		if (pSpriteUnit->IsPosBehindSprite2(x, y)) 
		{
			pSpriteUnit->m_Alpha_True = 1;
			return TRUE;
		}

		// ���� �����̶� �� ��� ����..
		for(int i=0; i<m_UserSize;i++)
		{
			if(pSpriteUnit->IsPosBehindSprite2(m_UsersPos[i].x, m_UsersPos[i].y)) 
			{
				pSpriteUnit->m_Alpha_True = 0;
				return TRUE;
			}
		}
	}
	else
	{
		for(int i=0; i<m_UserSize;i++)
		{
			if(pSpriteUnit->IsPosBehindSprite2(m_UsersPos[i].x, m_UsersPos[i].y)) 
			{
				pSpriteUnit->m_Alpha_True = 0;
				return TRUE;
			}
		}
	}
	pSpriteUnit->m_Alpha_True = 0;
	return FALSE;
}

//////////////////////////////////
CPoint SM_MapManager::SetCenterPos(CPoint pos)
{
	// ���� ��ġ�� ��...
//	pos = CellToPixel(pos);
	int X = 96;
	int Y = 48;

	m_posCenter = pos;

	//m_View_Flag = type;// 0-full 1-�� 2-��
	if(m_View_Flag == 0)
	{
		m_offsetMap.x = (pos.x-400)%X;
		m_offsetMap.y = (pos.y-300)%Y;
	}
	else if(m_View_Flag == 1)
	{
		m_offsetMap.x = (pos.x-220)%X;
		m_offsetMap.y = (pos.y-300)%Y;
	}
	else
	{
		m_offsetMap.x = (pos.x-580)%X;
		m_offsetMap.y = (pos.y-300)%Y;
	}


	if (m_offsetMap.x<0) m_offsetMap.x = 0;	//Offset�� ������ �� �� ����
	if (m_offsetMap.y<0) m_offsetMap.y = 0;	//Offset�� ������ �� �� ����

	if(m_View_Flag == 0)
	{
		m_MapStartIndex.x = (pos.x-400)/X;//800*600
		m_MapStartIndex.y = (pos.y-300)/Y;
	}
	else if(m_View_Flag == 1)
	{
		m_MapStartIndex.x = (pos.x-220)/X;//800*600
		m_MapStartIndex.y = (pos.y-300)/Y;
	}
	else
	{
		m_MapStartIndex.x = (pos.x-580)/X;//800*600
		m_MapStartIndex.y = (pos.y-300)/Y;
	}

	if (m_dimMap.cx==9) //���� X ���� ȭ�鿡 �� �´� ũ����
	{
		m_MapStartIndex.x = 0;
		m_offsetMap.x = 0;
	}
	else
	{
		if (m_MapStartIndex.x<0) 
		{
			m_MapStartIndex.x = 0;
			m_offsetMap.x = 0;
		}
		if (m_MapStartIndex.x>=m_dimMap.cx-9) 
		{
			m_MapStartIndex.x = m_dimMap.cx-9;
			m_offsetMap.x = 0;
		}
	}

	if (m_dimMap.cy==13) //���� Y���� ȭ�鿡 �� �´� ũ����
	{
		m_MapStartIndex.y = 0;
		m_offsetMap.y = 0;
	}
	else
	{
		if (m_MapStartIndex.y<0) 
		{
			m_MapStartIndex.y = 0;
			m_offsetMap.y = 0;
		}
		if (m_MapStartIndex.y>=m_dimMap.cy-13) 
		{
			m_MapStartIndex.y = m_dimMap.cy-13;
			m_offsetMap.y = 0;
		}
	}

	return GetMapStartPos();

}

CPoint SM_MapManager::GetMapStartPos() //ȭ��󿡼� LeftTop(0,0)�� ���� �ʿ��� Pixel�� ��X�� �� ��ġ�ϴ°�.
{
	CPoint ptMapStartPixel;
	int X = 96;
	int Y = 48;
	ptMapStartPixel.x = m_MapStartIndex.x*X+m_offsetMap.x;
	ptMapStartPixel.y = m_MapStartIndex.y*Y+m_offsetMap.y;

//	ptMapStartPixel.x = m_MapStartIndex.x*64+m_offsetMap.x;
//	ptMapStartPixel.y = m_MapStartIndex.y*32+m_offsetMap.y;
	return ptMapStartPixel;
}


BOOL SM_MapManager::IsAnimationTime(int iAnimationMode)
{
	DWORD curTick = GetTickCount();
	if (iAnimationMode==TILE_ANIMATION)
	{
		if (curTick-m_dwTickAniTileStart>300)
		{
			m_dwTickAniTileStart = curTick;
			return TRUE;
		}
		return FALSE;
	}
	else
	{
		if (curTick-m_dwTickAniSpriteStart>300)
		{
			m_dwTickAniSpriteStart = curTick;
			return TRUE;
		}
		return FALSE;
	}
}

// ////////////////////////////////////
// iPercent == 100 �϶� ����ȭ��
// iPercent == 0�϶� ����
// ////////////////////////////////////

int SM_MapManager::SetDarkLevel(int iPercent, BOOL bAbsolute)
{
	BOOL bReload = FALSE;

//	if(iPercent == 0)	m_iAbsDarkLevel = 100;

	if (bAbsolute && m_iAbsDarkLevel==iPercent) return m_iAbsDarkLevel;

	if (bAbsolute) m_iAbsDarkLevel = iPercent;
	else
	{
		if (iPercent==100) return m_iAbsDarkLevel;
		m_iAbsDarkLevel = MulDiv(m_iAbsDarkLevel, iPercent, 100);
	}

	for (int i=0; i<MAX_SGRNUM; i++)
	{
		if (m_apSgrRes[i]) 
		{
			bReload |= m_apSgrRes[i]->SetDarkLevel(iPercent, bAbsolute);
		}
	}
	if (bReload)
	{
		LoadMap(m_szMapName, TRUE);
	}
	return m_iAbsDarkLevel;
}

// �̰����� ���꿡�� ���̺��� �������...imf���� �������� �����ͼ� 
// �־�� �ǰڱ�..
BYTE** SM_MapManager::GetMoveableTable(int &dimx, int &dimy)
{
	if (!m_bLoadStatusOk) 
	{
		dimx = 0;
		dimy = 0;
		return NULL;
	}
/*	PBYTE *ppTable;
	ppTable = new PBYTE [m_dimMap.cx*2];
	for (int i=0; i<m_dimMap.cx*2; i++)
	{
		ppTable[i] = new BYTE[m_dimMap.cy];
	}

	int trueMapi;
	for (i=0; i<m_dimMap.cx*2; i+=2)
	{
		trueMapi = i/2;
		for (int j=0; j<m_dimMap.cy; j++)
		{
			ppTable[i][j] = !m_apaMapCell[trueMapi][j].IsMoveable(MC_LEFT);
			ppTable[i+1][j] = !m_apaMapCell[trueMapi][j].IsMoveable(MC_RIGHT);
		}
	}

	dimx = m_dimMap.cx*2;
	dimy = m_dimMap.cy;
	return ppTable;
*/

	dimx = m_cell_width;
	dimy = m_cell_height;
	return m_ppTable;
}

short **SM_MapManager::GetHouseTable(int &dimx, int &dimy)
{
	if (!m_bLoadStatusOk) 
	{
		dimx = 0;
		dimy = 0;
		return NULL;
	}
	dimx = m_cell_width;
	dimy = m_cell_height;
	return m_ppHouseTable;
}

//Pixel��ǥ�� Cell��ǥ��
CPoint SM_MapManager::PixelToCell(CPoint ptPixel)
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

	if(p.x < 0) p.x = 0;
	if(p.y < 0) p.y = 0;

	return p;
}
//Cell��ǥ�� Pixel��ǥ��
CPoint SM_MapManager::CellToPixel(CPoint ptCell)
{
	CPoint ptPixel;
	int X = 48;
	int Y = 24;
	ptPixel.x = (ptCell.x+1)*X;
	ptPixel.y = (ptCell.y+1)*Y;
	return ptPixel;
}

BOOL SM_MapManager::LoadSmf(CString szFileName, BOOL bFileNameContainPath)
{
	ASSERT(!m_szExePath.IsEmpty());

	CFile file;
	CString szFullPath;
	//if (!bFileNameContainPath) szFullPath.Format("%sSGRES\\%s", (LPCTSTR) m_szExePath, (LPCTSTR) szFileName); //����� �н��ΰ�� : Application���۽� Current���丮�� Exe������ ��ġ�� �����ϹǷ� ��밡��
	if (!bFileNameContainPath) szFullPath.Format("%sSGRES\\%s.smf", (LPCTSTR) m_szExePath, "test"); //����� �н��ΰ�� : Application���۽� Current���丮�� Exe������ ��ġ�� �����ϹǷ� ��밡��
	else szFullPath = szFileName;
	if (!file.Open(szFullPath, CFile::modeRead|CFile::typeBinary))
	{
		TRACE("������ ���� %s Open����\n");
		return FALSE;
	}
	TRACE("smf ���� ���..");

	CArchive ar(&file, CArchive::load);

	int sprite_version;
	int unique_number;
	
	ar >> sprite_version;
	ar >> unique_number;

	//Sprite Loading
	if (!LoadSpriteUnit(ar))				//���� Sprite���� �ε� (Sprite Resource�� �ƴ�)
	{
		ar.Close();
		file.Close();
		return FALSE;
	}

	return TRUE;
}

BOOL SM_MapManager::LoadImf(CString szFileName, BOOL bFileNameContainPath)
{
	ASSERT(!m_szExePath.IsEmpty());

	CFile file;
	CString szFullPath;
	//if (!bFileNameContainPath) szFullPath.Format("%sSGRES\\%s", (LPCTSTR) m_szExePath, (LPCTSTR) szFileName); //����� �н��ΰ�� : Application���۽� Current���丮�� Exe������ ��ġ�� �����ϹǷ� ��밡��
	if (!bFileNameContainPath) szFullPath.Format("%sMap\\%s.imf", (LPCTSTR) m_szExePath, "somamset"); //����� �н��ΰ�� : Application���۽� Current���丮�� Exe������ ��ġ�� �����ϹǷ� ��밡��
	else szFullPath = szFileName;
	if (!file.Open(szFullPath, CFile::modeRead|CFile::typeBinary))
	{
		TRACE("������ ���� %s Open����\n");
		return FALSE;
	}
	TRACE("imf ���� ���..");

	CArchive ar(&file, CArchive::load);

	int moveinfoversion;
	ar >> moveinfoversion;

	int cell_width;
	int cell_height;
	CPoint cell_limit;
	BYTE *t_buf;

	ar >> cell_width;
	ar >> cell_height;

	m_cell_width = cell_width;
	m_cell_height = cell_height;

	CSize mapSize;
	mapSize.cx = m_cell_width;
	mapSize.cy = m_cell_height;	    //���� ũ�� �ε�
	SetMapDimension(mapSize);		//���� ũ�� ��ŭ MapCell�� ����

	cell_limit.x = (cell_width+1)/2;
	cell_limit.y = (cell_height+1)/2;
	int tmp_int = cell_limit.x*cell_limit.y+(cell_limit.x-1)*(cell_limit.y-1);
	int load_count = tmp_int / 8;

	if(tmp_int % 8) load_count++;
	t_buf = new BYTE[load_count];

	int roll=0;
	int read_count=0;
	int x, y;

	//PBYTE *ppTable;
	m_ppTable = new PBYTE [cell_width];

	for (int i=0; i<cell_width; i++)
	{
		m_ppTable[i] = new BYTE[cell_height];
	}
	// 2���� �迭..����..

	ar.Read(t_buf, load_count);

	for(y = 0; y < cell_height-1; y++)
	{
		for(x = 0; x < cell_width-1; x++)
		{
			if((x+y)%2==0)
			{
				//pMoveable[x][y] = (t_buf[read_count] & g_vBitMask[roll]) >> roll;
				m_ppTable[x][y] = (t_buf[read_count] & g_vBitMask[roll]) >> roll;
				roll++;
				if(roll == 8)
				{
					roll = 0;
					read_count++;
				}
			}
			else
				m_ppTable[x][y] = -1;
				//pMoveable[x][y] = -1;// ������ ��...// ���� ���콺�� �������� �����ϸ� ��� �ұ� �����ؾ߰ڱ�..
		}
	}
	delete[] t_buf;
	
//	delete t_buf;
//hidden...����..m_ppHiddenTable
	roll=0;
	read_count=0;

	//PBYTE *ppTable;
/*	m_ppHiddenTable = new PBYTE [cell_width];

	for (i=0; i<cell_width; i++)
	{
		m_ppHiddenTable[i] = new BYTE[cell_height];
	}
	// 2���� �迭..����..

	ar.Read(t_buf, load_count);

	for(y = 0; y < cell_height; y++)
	{
		for(int x = 0; x < cell_width; x++)
		{
			if((x+y)%2==0)
			{
				//pMoveable[x][y] = (t_buf[read_count] & g_vBitMask[roll]) >> roll;
				m_ppHiddenTable[x][y] = (t_buf[read_count] & g_vBitMask[roll]) >> roll;
				roll++;
				if(roll == 8)
				{
					roll = 0;
					read_count++;
				}
			}
			else
				m_ppHiddenTable[x][y] = -1;
				//pMoveable[x][y] = -1;// ������ ��...// ���� ���콺�� �������� �����ϸ� ��� �ұ� �����ؾ߰ڱ�..
		}
	}

*/	//////////////////////////////////
	// �̺�Ʈ������ �о�´�.

	roll=0;
	read_count=0;

	//PBYTE *ppTable;
	m_ppEventTable = new PBYTE [cell_width];

	for (i=0; i<cell_width; i++)
	{
		m_ppEventTable[i] = new BYTE[cell_height];
		FillMemory(m_ppEventTable[i], cell_height, 0xff);
	}

	short data_x, data_y, data;
	ar >> read_count;

	for(i = 0; i < read_count; i++)
	{
		ar >> data_x;
		ar >> data_y;
		ar >> data;
		//m_ppTable[data_x][data_y].m_nHouseNumber = data;
		//m_pMoveInfo[data_x][data_y].m_nEventNumber = data;
	}


	//PBYTE *ppTable;
	m_ppHouseTable = new short *[cell_width];

	for (i=0; i<cell_width; i++)
	{
		m_ppHouseTable[i] = new short[cell_height];
		FillMemory(m_ppHouseTable[i], cell_height*sizeof(short), 0xff);
	}

	// �ǹ������� �о�´�.
	ar >> read_count;
	for(i = 0; i < read_count; i++)
	{
		ar >> data_x;
		ar >> data_y;
		ar >> data;
		//m_ppTable[data_x][data_y].m_nHouseNumber = data;
		m_ppHouseTable[data_x][data_y] = data;
	}

	m_ppAreaNumber = new PBYTE [cell_width];

	for (i=0; i<cell_width; i++)
	{
		m_ppAreaNumber[i] = new BYTE[cell_height];
		FillMemory(m_ppAreaNumber[i], cell_height, 0x0);
	}

	t_buf = new BYTE[tmp_int];
	ar.Read(t_buf, tmp_int);
	read_count = 0;
	for(y = 0; y < cell_height-1; y++)
	{
		for(x = 0; x < cell_width-1; x++)
		{
			if((x+y)%2==0)
			{
				m_ppAreaNumber[x][y] = t_buf[read_count++];
			}
		}
	}
	delete[] t_buf;

	////////////////////////////////////
	ar.Close();
	file.Close();
	return TRUE;
}

CSize SM_MapManager::GetMapDimension()
{
	CSize MapSize;
	MapSize.cx = m_dimMap.cx*2 -1;
	MapSize.cy = m_dimMap.cy*2 -1;
	return MapSize;
}

BOOL SM_MapManager::IsHidden(CPoint PosCell)
{
	int x = PosCell.x;
	int y = PosCell.y;
	if(m_ppHiddenTable[x][y])// �����̸�..
		return TRUE;
	return FALSE;
}

int SM_MapManager::IsHouse(CPoint PosCell)
{
	int x = PosCell.x;
	int y = PosCell.y;
	if(x < 0 || y < 0 || x >= m_cell_width || y >= m_cell_height) return -1;
	else return (int)m_ppHouseTable[x][y];// ���̸�..
}

void SM_MapManager::SetUserPos(CPoint UserPos, int index)
{
	m_UserSize++;//view���� 0���� ����� ����Ѵ�.
	m_UsersPos[index] = UserPos;
	return;
}

void SM_MapManager::ShowMapType(int type)
{
	m_View_Flag = type;// 0-full 1-�� 2-��
	return;
}

BYTE SM_MapManager::GetAreaNumber(CPoint posCell)
{
	if(posCell.x < 0 || posCell.y < 0 || posCell.x >= m_cell_width || posCell.y >= m_cell_height) return 0;
	else return m_ppAreaNumber[posCell.x][posCell.y];// ���̸�..
}