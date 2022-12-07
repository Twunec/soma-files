// Item_Small.h: interface for the CItem_Small class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Item_Small_H__870BC321_DF02_11D3_B175_00105A735718__INCLUDED_)
#define AFX_Item_Small_H__870BC321_DF02_11D3_B175_00105A735718__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Item.h"

class CItem_Small  : public CItem
{
public:	
	int m_ShopSelect;
	int m_ShopMeSelect;
	void ViewSelectBox(CPoint pos, int collar );
	void ShopMeItemDown();
	void ShopMeItemUp();
	void ShopItemDown();
	void ShopItemUp();
	int m_UpDown;// �κ��丮 ���ѹ�
	int m_UpDown_Shop;//���� ��ũ�ѹ�
	int m_UpDown_Shopme;//���� ���� ��ũ�ѹ�

	int m_Shop_Pic[50];
	CPoint m_Shop_pos[50];
	int m_Shop_Number[50];
	CString m_Shop_Name[50];
	int m_ItemTableNumber[50];//������ ���̺��ȣ
	int m_ShopNumber;//������ȣ

	void ShopItemNumber(CPoint pos, int index);
	void InvItemDown();
	void InvItemUp();
	void InvWindowDraw(CDDSurface* pDrawSurface);
	void ShopMeWindowDraw(CDDSurface* pDrawSurface);
	void ShopWindowDraw(CDDSurface* pDrawSurface);
	int m_Caption;
	void ViewCaption(CPoint pos, CString str, int tmp_y = 0);
	virtual BOOL MouseProcess(BBDX_MouseInformation* pMouseInfo, int Dlg_Pos = 0, int Select_Box = 0, int MoveFlag = 1);
	virtual void Draw(CDDSurface* pDestSurf, int count=0, int tmp_y=0, int index=0);
	virtual void DrawShop(int x, int y, CDDSurface* pDestSurf, int count=0, int index=0);
	virtual void DrawShopMe(int x, int y, CDDSurface* pDestSurf, int count=0, int index=0);
	void InitItem(CDirectDraw *pDirectDraw);
	CItem_Small();
	virtual ~CItem_Small();


};

#endif // !defined(AFX_Item_Small_H__870BC321_DF02_11D3_B175_00105A735718__INCLUDED_)
