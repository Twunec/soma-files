// MapCell.h: interface for the CMapCell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAPCELL_H__831A048E_1378_11D3_8422_0020AF9F40BD__INCLUDED_)
#define AFX_MAPCELL_H__831A048E_1378_11D3_8422_0020AF9F40BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTilePiece;
class SM_MapManager;
class CDDSurface;

#define MC_LEFT		0
#define MC_RIGHT	1

class CMapCell  
{
public:
	BOOL					IsMoveable(int iOpt) {return m_bMoveable[iOpt];}	//�̵����ɿ��� opt:mc_left or mc_right
	void					RotateAnimation();									//Animation �� �ñ��̹Ƿ� ���� Animation Tile�� �غ�
	void					Draw(CDDSurface *pDestSurface, CPoint pos);			
	BOOL					Load(CArchive &ar);

	struct {
		unsigned	m_idxCustomTile	:	8;	// 16��
		unsigned	m_posCustom_x	:	12;	// 4096��
		unsigned	m_posCustom_y	:	12;	// 4096��
	} TileInfo2;

	//Setting�� �ʿ��� �⺻ ����
	struct {
		unsigned	m_bIsCustomTile	:	1;	// TRUE/FALSE
		unsigned	m_idxVaryTile	:	4;	// 16��
		unsigned	m_idxVary		:	6;	// 64��
		unsigned	m_idxTileGroup	:	4;	// 16��
		unsigned	m_idxTile		:	8;	// 256��
		unsigned	m_idxSgr		:	6;	// 64��
	} TileInfo1;


	CMapCell();
	virtual ~CMapCell();

	static	SM_MapManager*	m_bpMapManager;

protected:
	BYTE			m_iLayer[2];					//���� �ʿ��� Cell����
	BYTE			m_bMoveable[2];
	BYTE			m_iEventNum;

	CTilePiece*		m_bpTilePiece;
	int				m_iAnimationOrder;				//Animation Index
};

#endif // !defined(AFX_MAPCELL_H__831A048E_1378_11D3_8422_0020AF9F40BD__INCLUDED_)
