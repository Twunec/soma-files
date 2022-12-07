// TilePiece.h: interface for the CTilePiece class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TILEPIECE_H__831A0482_1378_11D3_8422_0020AF9F40BD__INCLUDED_)
#define AFX_TILEPIECE_H__831A0482_1378_11D3_8422_0020AF9F40BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTileSurface;
typedef CTypedPtrArray <CPtrArray, CTileSurface*> AP_TILESURFACE;
class CDDSurface;
typedef CTypedPtrArray <CPtrArray, CDDSurface*> AP_CDDSURFACE;

class CTilePiece  
{
public:
	void			DarkenProcess(COLORREF rgb);
	void			Draw(CDDSurface* pDestSurface, CPoint &pos, int iAnimationIndex);	//�׸��� �־��� IndexȰ��
	int				GetAnimationNum(){return m_nAnimation;}								//Animation��ΰ�?
	BOOL			Load(CArchive &ar, BYTE *bypBitmapInfo, DWORD dwBitmapInfoSize);	//Load
	int				m_nAnimation;

	CTilePiece();
	virtual ~CTilePiece();

protected:
	void			RemoveAllData();
	void			FillApCDDSurface();	//Load�� m_apCDDSurface ä���

protected:
	//int				m_nAnimation;		
	AP_TILESURFACE	m_apTileSurface;	//CTileSurface�� Array
	AP_CDDSURFACE	m_apCDDSurface;		//���� ������ ���ؼ�(�׸��� TileSurface�� CDDSurface�� ����ϹǷ�, CDDSurface�� �����͸� �޾Ƶΰ� ���� ������)
};

#endif // !defined(AFX_TILEPIECE_H__831A0482_1378_11D3_8422_0020AF9F40BD__INCLUDED_)
