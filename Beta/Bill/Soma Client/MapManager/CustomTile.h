// CustomTile.h: interface for the CCustomTile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CUSTOMTILE_H__A64CCB3D_1348_11D3_8422_0020AF9F40BD__INCLUDED_)
#define AFX_CUSTOMTILE_H__A64CCB3D_1348_11D3_8422_0020AF9F40BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CCustomTileVary;
typedef CTypedPtrArray <CPtrArray, CCustomTileVary*> AP_CUSTOMTILEVARY;

class CCustomTile  
{
public:
	void				DarkenProcess(COLORREF rgb);		//���� ��� ������.
	AP_CUSTOMTILEVARY&	GetApCustomTileVary(){return m_apCustomTileVary;}
	BOOL				Load(CArchive &ar);					//Map�߿��� CustomTile Loadó����

	CCustomTile();
	virtual ~CCustomTile();

protected:
	void				RemoveAllData();

protected:
	CString				m_szTileName;						//Tile�� �̸�
	CString				m_szBaseTileName;					//Base Tile�� �̸�
	CSize				m_dimTile;							//CustomTile�� Dimension (32X32 ���� �� ����)
	BYTE*				m_bypBitmapInfo;					//Bitmap Info
	DWORD				m_dwBitmapInfoSize;					//Bitmap Info �� ũ�� : sizeof(m_bypBitmapInfo)

	AP_CUSTOMTILEVARY	m_apCustomTileVary;
};

#endif // !defined(AFX_CUSTOMTILE_H__A64CCB3D_1348_11D3_8422_0020AF9F40BD__INCLUDED_)
