// Sprite.cpp: implementation of the CSprite class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Sprite.h"
#include "TileSurface.h"
#include "../DManage/BB_Direct.h"
#include "../DManage/AlphaProcess.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSprite::CSprite()
{
	m_vCellSize.cx = m_vCellSize.cy = 0;
	m_sizeSprite.cx = 0;
	m_sizeSprite.cy = 0;
	m_nAnimation = 0;
	m_pSpriteCell = NULL;
}

CSprite::~CSprite()
{
	RemoveAllData();
}

BOOL CSprite::Load(CArchive &ar)
{
	RemoveAllData();

	LoadSpriteAttr(ar);
	//ar >> m_nAnimation;						//Animation �?// 
	//m_apTileSurface.SetSize(m_nAnimation);

	/////////////////////��������..
	int count;
	ar >> count;
	if(count)
	{
		// ���� ������ �д� �κ� �߰�..������ ���°� ������..



	}

////////////////////////////////////////////////////////////////
	// ���߿� ���� ������..

	CPoint *pDibPos;							// �� DIB�� ��ġ(���� DIB�� ���� ���� ���)
	CSize vDibCount;
	ar >> vDibCount;
	count = vDibCount.cx * vDibCount.cy;
	pDibPos = new CPoint[count];
	for(int i = 0; i < count; i++)
	{
		ar >> pDibPos[i];
	}
	delete[] pDibPos;
	/////////////////////////////////////////////////////////////


	ar >> m_nAnimation;						//Animation �?// 
	m_apTileSurface.SetSize(m_nAnimation);
	///////////////////////////

	CTileSurface*	pTileSurface = NULL;
	BOOL			bErrorOccur = FALSE;
	for (i=0; i<m_nAnimation; i++)
	{
		pTileSurface = new CTileSurface;
		if (pTileSurface->Load(ar))
		{
			m_apTileSurface.SetAt(i, pTileSurface);
		}
		else
		{
			delete pTileSurface;
			bErrorOccur = TRUE;
		}
	}

	FillApCDDSurface();
	if (!bErrorOccur)
	{
		m_sizeSprite.cx = m_apCDDSurface[0]->GetWidth();
		m_sizeSprite.cy = m_apCDDSurface[0]->GetHeight();
	}

	return bErrorOccur ? FALSE:TRUE;
}

void CSprite::RemoveAllData()
{
	if(m_pSpriteCell) {
		for(int i = 0; i < m_vCellSize.cx; i++) {
			delete[] m_pSpriteCell[i];
		}
		delete[] m_pSpriteCell;
		m_pSpriteCell = NULL;
	}
	m_vCellSize.cx = m_vCellSize.cy = 0;

	int size = m_apTileSurface.GetSize();
	for (int i=0; i<size; i++)
	{
		if (m_apTileSurface[i]) delete m_apTileSurface[i];
	}
	m_apTileSurface.RemoveAll();

	m_apCDDSurface.RemoveAll();	//m_apCDDSurface�� ���� ������ ������Ұ� �ƴ϶� ������� Pointer�� ������ ����(�׷��Ƿ� �޸� ���� ���� ������ �ȵ�)
}

void CSprite::LoadSpriteAttr(CArchive &ar)	//Load�� ������� �ʴ� Sprite������ Pass�� ���߿� ����� �� ����� �̰����� ������
{	
	int iStrLen;
	ar >> iStrLen;									// ��������Ʈ �̸��� ���� Skip
//	BYTE *bypTmp = new BYTE[iStrLen];				// ��������Ʈ �̸� Skip
	LPTSTR buf = m_SpriteName.GetBuffer(iStrLen);
	ar.Read((void *)buf, iStrLen);
	m_SpriteName.ReleaseBuffer();
	
//	ar.Read((void *)buf, length);										// ��������Ʈ �̸�
//	m_vName.ReleaseBuffer();

	int i;

	ar >> m_vCellSize.cx >> m_vCellSize.cy;
	if (m_vCellSize.cx==0&&m_vCellSize.cy==0) return;

	ar >> m_vPatternCount;						//Animation �?// �ۿ� �־��µ� ������ ������ ����..

	if(m_vPatternCount)//���ϸ��̼� ����...
	{
		// ������ ��� ���� �Ǵµ�..����..
		char start_frame;
		char end_frame;
		char direction;
		char repeat_count;
		for(i=0; i< m_vPatternCount;i++)
		{
			// �ӽ� ���߿� �����ؾߵȴ�..������ �ϳ��� ��������ԵǾ�����..
			ar >> start_frame;
			ar >> end_frame;
			ar >> direction;
			ar >> repeat_count;
		}
	}

	m_pSpriteCell = new SPRITECELL *[m_vCellSize.cx];
	for(i = 0; i < m_vCellSize.cx; i++) {
		m_pSpriteCell[i] = new SPRITECELL[m_vCellSize.cy];
	}
	
	//////////////////////
	// ���ض����� ���߿� �߰��Һκ�
	BYTE sky;
	ar >> sky;

	m_Sky = (int)sky;

	//l, t, r, b
	CRect SpriteRect;
	ar >> SpriteRect.left;
	ar >> SpriteRect.top;
	ar >> SpriteRect.right;
	ar >> SpriteRect.bottom;

	m_RectSprite = SpriteRect;

	int length;
	int x, y;
	CPoint p;

	ar.Read((void *)&length, sizeof(int));								// Hide Character Cell ����
	if(length > 0) {
		for(i = 0; i < length; i++) {
			ar.Read((void *)&(p.x), sizeof(int));						// Hide Character Cell�� X ��ǥ
			ar.Read((void *)&(p.y), sizeof(int));						// Hide Character Cell�� Y ��ǥ
			m_pSpriteCell[p.x][p.y].m_bHideCharacter = TRUE;
		}
	}

	for(y = 0; y < m_vCellSize.cy; y++) {								// ������ Cell�� ����
		for(x = 0; x < m_vCellSize.cx; x++) {
			ar.Read((void *)&(m_pSpriteCell[x][y].m_vLayer), sizeof(int));// �Ʒ��� ��ġ�� �ٲ�..
			ar.Read((void *)&(m_pSpriteCell[x][y].m_bMovable), sizeof(BOOL));
			
		}
	}
}

void CSprite::Draw(CDDSurface* pDestSurface, CPoint pos, CPoint MapStartPos, CPoint MapOffset, int iAnimationIndex, BOOL bTrans)
{
	ASSERT(m_nAnimation>iAnimationIndex);

//	CRect sRect(0, 0, 640, 480);
	CRect sRect(0, 0, 800, 600);
	sRect.OffsetRect(MapStartPos.x*64+ MapOffset.x, MapStartPos.y*32+MapOffset.y);
	CRect sr(0, 0, m_sizeSprite.cx, m_sizeSprite.cy);
	CRect r = sr;
	r.OffsetRect(pos);
	r &= sRect;

	if (r.IsRectEmpty()) //�׸� �ڸ��� ����
	{
		TRACE("��ȣ�ڵ� �ɸ�: Error\n");
		return;
	}

	sr = r;
	sr.OffsetRect(-pos.x, -pos.y);
	r.OffsetRect(-MapStartPos.x*64-MapOffset.x, -MapStartPos.y*32-MapOffset.y);

	if (bTrans) 
	{
		//������ ���·� ��(���� Sprite�� �ݹݾ� ����)
		CAlphaProcess::MixHalf(pDestSurface, r, m_apCDDSurface.GetAt(iAnimationIndex), sr);
	}
	else 
	{
		CPoint point;
		point.x = r.left;
		point.y = r.top;

		pDestSurface->BltFast(point, m_apCDDSurface.GetAt(iAnimationIndex), &sr, DDBLTFAST_SRCCOLORKEY);
		//pDestSurface->Blt(&r, m_apCDDSurface.GetAt(iAnimationIndex), &sr, DDBLT_KEYSRC|DDBLT_ASYNC);
	}
}

void CSprite::FillApCDDSurface()
{
	int size = m_apTileSurface.GetSize();
	m_apCDDSurface.SetSize(size);
	for (int i=0; i<size; i++)
	{
		m_apCDDSurface[i] = m_apTileSurface[i]->GetSurface(); //Pointer�� �޾Ƶ�
	}
}

void CSprite::DarkenProcess(COLORREF rgb)
{
	int size = m_apTileSurface.GetSize();
	m_apCDDSurface.SetSize(size);
	for (int i=0; i<size; i++)
	{
		if (m_apCDDSurface.GetAt(i))
			m_apCDDSurface.GetAt(i)->DrawFogLayer(NULL, rgb, TRUE);
	}
}

BOOL CSprite::GetMovable(int x, int y)
{
	ASSERT(x >= 0 && x < m_vCellSize.cx);
	ASSERT(y >= 0 && y < m_vCellSize.cy);

	return m_pSpriteCell[x][y].m_bMovable;
}

int CSprite::GetLayer(int x, int y)
{
	ASSERT(x >= 0 && x < m_vCellSize.cx);
	ASSERT(y >= 0 && y < m_vCellSize.cy);

	return m_pSpriteCell[x][y].m_vLayer;
}

BOOL CSprite::GetHideCharacter(int x, int y)
{
	ASSERT(x >= 0 && x < m_vCellSize.cx);
	ASSERT(y >= 0 && y < m_vCellSize.cy);

	return m_pSpriteCell[x][y].m_bHideCharacter;
}
