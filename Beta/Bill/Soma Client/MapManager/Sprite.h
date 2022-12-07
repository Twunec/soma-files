// Sprite.h: interface for the CSprite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRITE_H__A64CCB3C_1348_11D3_8422_0020AF9F40BD__INCLUDED_)
#define AFX_SPRITE_H__A64CCB3C_1348_11D3_8422_0020AF9F40BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//CTilePiece���� ����Ǿ�����
class CTileSurface;
typedef CTypedPtrArray <CPtrArray, CTileSurface*> AP_TILESURFACE;
class CDDSurface;
typedef CTypedPtrArray <CPtrArray, CDDSurface*> AP_CDDSURFACE;

class SPRITECELL {
public:
	SPRITECELL() {
		m_bMovable = FALSE;
		m_bHideCharacter = FALSE;
		m_vLayer = 0;
	};

public:
	BOOL m_bMovable;				// �̵� ���� �÷���(����(TRUE), �Ұ���(FALSE))
	BOOL m_bHideCharacter;			// ĳ���͸� ������ �Ӽ�(ĳ���͸� ������(TRUE), ĳ���Ͱ� ���δ�(FALSE))
	int m_vLayer;					// �� ��ȣ(0(1��), 1(1-2��), 2(2��))
};

class CSprite  
{
public:
	BYTE m_vPatternCount;
	void			DarkenProcess(COLORREF rgb);
	int				GetAnimationNum(){return m_nAnimation;}
	CSize			GetSpriteSize(){return m_sizeSprite;}
	void			FillApCDDSurface();
	void			Draw(CDDSurface* pDestSurface, 
						CPoint pos, 
						CPoint MapStartPos, 
						CPoint MapOffset, 
						int iAnimationIndex, 
						BOOL bTrans=FALSE);
	void			LoadSpriteAttr(CArchive &ar);	//������� �ʴ� Sprite���� Pass�� Load�Լ����� ���
	void			RemoveAllData();
	BOOL			Load(CArchive &ar);	//���� �ε�
	BOOL			GetMovable(int x, int y);
	int				GetLayer(int x, int y);
	BOOL			GetHideCharacter(int x, int y);

	CSprite();
	virtual ~CSprite();

	CSize			m_vCellSize;		// ��ü 32x32 ���� ����
	CString         m_SpriteName;
	int             m_Sky;
	CRect           m_RectSprite;

protected:
	SPRITECELL		**m_pSpriteCell;	// �� ���� �Ӽ�(2���� �迭�� �����Ǿ� ����)
	AP_TILESURFACE	m_apTileSurface;	//������ ������� CTileSurface�� Ptr Array�� ����
	AP_CDDSURFACE	m_apCDDSurface;		//���� ������ ���ؼ� (���� CDDSurface����)
	CSize			m_sizeSprite;		//Sprite�� ũ�� (pixel����)
	int				m_nAnimation;		//Animation�� �� �ִ� ������ �?
};

#endif // !defined(AFX_SPRITE_H__A64CCB3C_1348_11D3_8422_0020AF9F40BD__INCLUDED_)
