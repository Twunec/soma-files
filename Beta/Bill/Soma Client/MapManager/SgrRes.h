// SgrRes.h: interface for the CSgrRes class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SGRRES_H__A64CCB3A_1348_11D3_8422_0020AF9F40BD__INCLUDED_)
#define AFX_SGRRES_H__A64CCB3A_1348_11D3_8422_0020AF9F40BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTile;
typedef CTypedPtrArray<CPtrArray, CTile*> AP_TILE;
class CSprite;
typedef CTypedPtrArray<CPtrArray, CSprite*> AP_SPRITE;
class CCustomTile;
typedef CTypedPtrArray<CPtrArray, CCustomTile*> AP_CUSTOMTILE;

//Sgr ������ Resource�� ���� (CSgrRes class 1���� 1���Ͽ� �ش�)
class CSgrRes  
{
public:
	BOOL			SetDarkLevel(int iPercent, BOOL bAbsolute=TRUE);//Map�� Reload�� ������ TRUE, �ƴϸ� FALSE
	void			RemoveAllData();
	BOOL			Load(CString szFileName);

	AP_TILE&		GetApTile() {return m_apTile;}				//Tile�� ��������
	AP_SPRITE&		GetApSprite() {return m_apSprite;}			//Sprite�� ��������
	AP_CUSTOMTILE&	GetApCustomTile() {return m_apCustomTile;}	//CustomTile�� ��������

	CSgrRes();
	virtual ~CSgrRes();

protected:
	void			DarkenProcess();		//��Ӱ� ����
	void			ReloadResource();		//�ٽ� �ε���(�ʿ��� ��쿡)

protected:
	CString			m_szFileName;			//Sgr������ �̸�
	AP_TILE			m_apTile;
	AP_SPRITE		m_apSprite;
	AP_CUSTOMTILE	m_apCustomTile;
	int				m_iDarkLevel;			//��ӱ� ���� ����


public:
	int				m_iTileCount;
	int				m_iSpriteCount;
	int				m_iCustomTileCount;
};

#endif // !defined(AFX_SGRRES_H__A64CCB3A_1348_11D3_8422_0020AF9F40BD__INCLUDED_)
