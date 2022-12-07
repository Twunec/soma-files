// TileGroup.h: interface for the CTileGroup class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TILEGROUP_H__A64CCB40_1348_11D3_8422_0020AF9F40BD__INCLUDED_)
#define AFX_TILEGROUP_H__A64CCB40_1348_11D3_8422_0020AF9F40BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTileVary;
typedef CTypedPtrArray<CPtrArray, CTileVary*> AP_TILEVARY;

class CTileGroup  
{
public:
	void			DarkenProcess(COLORREF rgb);			//��ӱ� ó��
	AP_TILEVARY&	GetApTileVary() {return m_apTileVary;}	//TileVary�� array
	BOOL			Load(CArchive &ar, BYTE *bypBitmapInfo, DWORD dwBitmapInfoSize); //Load�� bitmapinfo�� ����ؼ� �̹��� ����

	CTileGroup();
	virtual ~CTileGroup();

protected:
	void			RemoveAllData();

protected:
	int				m_nPiece;								//Vary �� ��� ����?
	AP_TILEVARY		m_apTileVary;							//Vary Array
};

#endif // !defined(AFX_TILEGROUP_H__A64CCB40_1348_11D3_8422_0020AF9F40BD__INCLUDED_)
