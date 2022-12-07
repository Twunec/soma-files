// Item_Small.cpp: implementation of the CItem_Small class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Item_Small.h"
#include "ChildView.h"
#include "Item_Total.h"

//extern CItem_sArm    Item_sArm;
extern CItem_Total         Item_Total;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CItem_Small::CItem_Small()
{
	m_Caption = 0;// ������ ���� ĸ���� �߰� �ϴ� �ɼ� �÷���..
}

CItem_Small::~CItem_Small()
{
}


void CItem_Small::InitItem(CDirectDraw *pDirectDraw)
{
	InitData(pDirectDraw);
	for(int i=0;i<50;i++)
	{
		m_Item_Fixpos[i] = m_Item_pos[i];// �ڸ��� ������Ų��.����..
		m_Shop_Pic[i] = -1;
		m_Shop_pos[i] = CPoint(0,0);		
		m_Shop_Name[i] = _T("");
		m_ItemTableNumber[i] = -1;
	}

	m_UpDown=0;
	m_UpDown_Shop=0;
	m_UpDown_Shopme=0;
	m_ShopSelect=-1;
	m_ShopMeSelect = -1;

	m_ShopNumber=-1;//������ȣ

//	Load_image("item.bmp");// �ӽ÷� ������ �Ѵ�..���� �����ϱ�..��..
	LoadObm("item.obm");
	LoadSpr("item.spr");
//	Load_image("item_test.bmp");// �ӽ÷� ������ �Ѵ�..���� �����ϱ�..��..
//	LoadSpr("item_test.spr");

}

BOOL CItem_Small::MouseProcess(BBDX_MouseInformation *pMouseInfo, int Dlg_Pos, int Select_Box, int MoveFlag)
{
	// ������ �÷��׸� ������.m_Item_Flag
	// ��� �̻���...� �޴�..��� �־��� ��� �޴�..�̷�������..��..
	// ���콺�� �����϶� ����..
	int i;

	if(m_Select_Item >= 0)
	{
		i = m_Select_Item;
		if(m_Move_Flag[i] )// = TRUE;// �巡�׸� �Ҷ�..����ؾ�¡..
		{
			// �̰����� �������� � ��ҿ��ٰ� ���Ҵ��� �Ǵ��ؾߵȴ�..
			if(pMouseInfo->IsLButtonUp())
			{
				m_Move_Flag[i] = FALSE;
				m_Caption = 0;// ���� â�� ���� ������.
//				CString str;
//				str.Format("item�� %d�����̾�α��� %d�� ���ڿ� ���Ҵ�11111111.", Dlg_Pos, Select_Box);
//				CChildView::SocketMng.SendChat(str);
				//Dlg_Pos : 1 ���� â 2 : �κ��丮â 3 : 

				// ���� �ڸ��� ���� ���� �����...���߿� �̵��� �ϰ� �ϴ��� �ؾ߰���..��..
				// ���� ��ġ�� ���Ŀ� ����..
				m_Select_Item = -1;
				if(MoveFlag == 0) return TRUE;

				m_Item_pos[i] = m_Item_Fixpos[i];

				if(Dlg_Pos == 2)
				{
					if(Select_Box ==0)
					{
						CChildView::ChangeItem(i);
						Output(i);
					}
				}
				else if(Dlg_Pos == 0)// ������. 
				{
//					CString str;
//					str.Format("�ٴڿ� %d��item�� ���ȴ�.", i);
//					CChildView::SocketMng.SendChat(str);	
					CPoint MyPos = CChildView::UserManager.GetMyCellPos();
					
					BYTE buf[10];
					int offset = 0;
					CPacketParser::SetByte(buf, offset, PKT_ITEM_THROW); //������ ��û
					CPacketParser::SetShort(buf, offset, (short)i);
					CPacketParser::SetShort(buf, offset, (short)MyPos.x);
					CPacketParser::SetShort(buf, offset, (short)MyPos.y);
					CChildView::SocketMng.Send(offset, buf);

					Output(i);// �ٴڿ��� ������..��...
				}
			}
			else if (pMouseInfo->IsLButtonPressing())
			{
				if(m_Move_Flag[i])// = TRUE;// �巡�׸� �Ҷ�..����ؾ�¡..
				{
					// ������ ����....
					int move_x, move_y;
					move_x = m_Old_Pos.x - pMouseInfo->m_posMouse.x;
					move_y = m_Old_Pos.y - pMouseInfo->m_posMouse.y;

					m_Item_pos[i].x -= move_x;
					m_Item_pos[i].y -= move_y;

					m_Old_Pos = pMouseInfo->m_posMouse;
				}
			}
			return TRUE;
		}
	}


	for(i=0; i<100;i++)
	{
		if(InMousePos(pMouseInfo->m_posMouse, m_BoxRect[i]) || m_Move_Flag[i])
		{//�޴������� �ִ�..
//			if(pMouseInfo->IsLButtonDobleDown()&& MoveFlag == 1)
//			{
//				CChildView::ChangeItem(i);
//				Output(i);
//			}
//			else
			
			if(pMouseInfo->IsRButtonDown())// ������ �����Ǵ� ����Ҷ�..
			{
				CChildView::ChangeItem(i);
				Output(i);
			}

			if (pMouseInfo->IsLButtonDown()) 
			{
				m_Move_Flag[i] = TRUE;// �巡�׸� �Ҷ�..����ؾ�¡..
				m_Old_Pos = pMouseInfo->m_posMouse;
				m_Current_Item = i;// ���� ���õǾ��ִ�..������..��ȣ..
				m_Select_Item = i;// ���콺�� ������ �ʱ�ȭ ��.
				
				if(i < 50)	m_ShopMeSelect = i; 
				else m_ShopSelect = i;// �������� ���õ� �������� �����ǰ� �ϱ����ؼ�..

				m_Caption = 1;// ���� â�� �߰� �Ѵ�.
			}
			m_Item_Flag = i;
			return TRUE;
			
		}
		else if(m_Item_Flag == i)
			m_Item_Flag = -1;
	}
	return FALSE;
}

void CItem_Small::ViewCaption(CPoint pos, CString str, int tmp_y)
{
	DWORD cur = GetTickCount();
	int DEFAULT_BUBBLECHAT_WIDTH = 300;
	int len = str.GetLength();

	pos.x += 20;
	pos.y += 10;

	pos.y -= tmp_y;

//	CPoint pos;
//	pos.x = m_Position.x - bgpos.x - 50;
//	pos.y = m_Position.y - bgpos.y - 80;

	len = len/14 + 1;
	//ASSERT (line >= 1);			
	CDC *pDC = CChildView::DirectXMng.m_pDrawSurface->GetDC();
	
	pDC->SetBkMode(TRANSPARENT);
	CFont pFont, *old_font;
	CRect r;

	////////////////////////
	pFont.CreateFont(-12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH, "����");
	old_font = pDC->SelectObject(&pFont);
	/////////////////////////

	CSize size = pDC->GetTextExtent(str);
	int line = size.cx / DEFAULT_BUBBLECHAT_WIDTH + 1;
	
	if(size.cx < DEFAULT_BUBBLECHAT_WIDTH)
		DEFAULT_BUBBLECHAT_WIDTH = size.cx;

	r.SetRect(pos.x , pos.y, pos.x+DEFAULT_BUBBLECHAT_WIDTH, pos.y+line*size.cy);
	
	//r.OffsetRect(-DEFAULT_BUBBLECHAT_WIDTH/2 , -100 - (line)*size.cy);
	r.OffsetRect(0 , - (line)*size.cy);

	// ������
	pDC->SetTextColor(RGB(5,5,5));
	//pDC->DrawText(m_szChatString, &r, DT_WORDBREAK|DT_CENTER|DT_TOP);
	pDC->DrawText(str, &r, DT_SINGLELINE|DT_CENTER|DT_VCENTER);
	
	// �����		
	//pDC->SetTextColor(RGB(255,255,0));
	//pDC->SetTextColor(RGB(181,181, 255));

	

	CRect temp = r;
	CRect temp2 = r;
	
	temp.OffsetRect(-1, -1);

	temp2.OffsetRect(-3, -4);
	temp2.right +=6;
	temp2.bottom += 7;

	//pDC->DrawText(m_szChatString, &temp, DT_WORDBREAK|DT_CENTER|DT_TOP);
	
	//pDC->FillSolidRect(temp2, RGB(181,181, 255));// �ڽ��� ä���� �׸���.
	pDC->FillSolidRect(temp2, RGB(247,202,26));// �ڽ��� ä���� �׸���.

	//pDC->DrawEdge(temp2, EDGE_BUMP, BF_RECT);
	//pDC->DrawEdge(temp2, EDGE_SUNKEN, BF_RECT);
	pDC->DrawText(str, &temp, DT_SINGLELINE|DT_CENTER|DT_VCENTER);//|DT_CENTER);
	//::DrawText(pDC->m_hDC , m_szChatString, strlen(m_szChatString), &temp, DT_WORDBREAK);

	pDC->SelectObject(old_font);
	pFont.DeleteObject();
	CChildView::DirectXMng.m_pDrawSurface->ReleaseDC(pDC);
	
/////////////////////////////////////////////////////////
}

void CItem_Small::Draw(CDDSurface* pDestSurf, int count, int tmp_y,  int index)
{
	CItem::Draw(pDestSurf, count, tmp_y, index);
	
	if(m_Caption == 1)
	{
		CString str = _T("�� ��������"); str += m_Item_Name[m_Select_Item]; str += _T("�̴�.");
		ViewCaption(m_Item_pos[m_Select_Item], str, tmp_y);
	}
}

// ������ ������ �ִ� �������� �����ش�.
void CItem_Small::DrawShop(int x, int y, CDDSurface* pDestSurf, int count,  int index)
{
//	CItem::Draw(x, y, pDestSurf, count, index);

	int i = index;
	CPoint pos;
	pos = CPoint(x,y);

	if(x >= 0 && y >= 0 && m_Shop_Pic[i] >=0)
	{
		ViewItemBox(x, y, i+50, m_Shop_Pic[i], pDestSurf);// ���� �������̹Ƿ�...
		ShopItemNumber(pos, i);
	}

	if(m_ShopSelect-50 == index)
		ViewSelectBox(pos,0);


	if(m_Caption == 1 && (m_Select_Item-50) == index)
	{
		CString str = _T("�� ��������"); str += m_Shop_Name[m_Select_Item-50]; str += _T("�̴�.");
		ViewCaption(pos, str, 0);
	}
}

// �������� ���� ���� �������� �����ش�.
void CItem_Small::DrawShopMe(int x, int y, CDDSurface* pDestSurf, int count,  int index)
{
	CItem::Draw(x, y, pDestSurf, count, index);
	
	CPoint pos = CPoint(x,y);

	if(m_ShopMeSelect == index)
		ViewSelectBox(pos,0);

	if(m_Caption == 1 && m_Select_Item == index)
	{
		CString str = _T("�� ��������"); str += m_Item_Name[m_Select_Item]; str += _T("�̴�.");
		ViewCaption(pos, str, 0);
	}
}

void CItem_Small::InvWindowDraw(CDDSurface *pDrawSurface)
{
	// �迭�� �����..�켱 ������ ���ؼ� ���⼭ �ѷ��ش�..����..
	int count =m_UpDown;
	int tmp = 33;
	for(int i=0;i<50;i++)
		m_BoxRect[i] = CRect(0,0,0,0);
		//Item_Total.m_Item_Small->m_BoxRect[i] = CRect(0,0,0,0);// �ʱ�ȭ..
	for(i=8*count;i<24+count*8;i++)// �ӽ�...
	{
		Draw(pDrawSurface,0, count*30+15, i);
		//Item_Total.m_Item_Small->Draw(pDrawSurface,0, count*33+15, i);
	}
}

void CItem_Small::ShopMeWindowDraw(CDDSurface *pDrawSurface)
{
	int x, y, count=0;
	for(int i=0;i<50;i++)
		m_BoxRect[i] = CRect(0,0,0,0);
		//Item_Total.m_Item_Small->m_BoxRect[i] = CRect(0,0,0,0);// �ʱ�ȭ..
	for(i=m_UpDown_Shopme;i<m_UpDown_Shopme+5;i++)
	{
		x = 85;
		y = 199+count*46;
		DrawShopMe(x, y, pDrawSurface,0,  i);
		count++;
	}
}

void CItem_Small::ShopWindowDraw(CDDSurface *pDrawSurface)
{
	int x, y, count=0;
	for(int i=m_UpDown_Shop;i<m_UpDown_Shop+5;i++)
	{
		x = 255;
		y = 199+count*46;
		DrawShop(x, y, pDrawSurface,0,  i);
		count++;
	}
}

void CItem_Small::InvItemUp()
{
	m_UpDown--;
	if(m_UpDown < 0) m_UpDown = 0;
}

void CItem_Small::InvItemDown()
{
	m_UpDown++;
	if(m_UpDown >= 4) m_UpDown = 3;
}

void CItem_Small::ShopItemUp()
{
	m_UpDown_Shop--;
	if(m_UpDown_Shop < 0) m_UpDown_Shop = 0;
}

void CItem_Small::ShopItemDown()
{
	m_UpDown_Shop++;
	if(m_UpDown_Shop < 0) m_UpDown_Shop = 0;
}

void CItem_Small::ShopMeItemUp()
{
	m_UpDown_Shopme--;
	if(m_UpDown_Shopme < 0) m_UpDown_Shopme = 0;
}

void CItem_Small::ShopMeItemDown()
{
	m_UpDown_Shopme++;
	if(m_UpDown_Shopme > 45) m_UpDown_Shopme = 45;
}

void CItem_Small::ViewSelectBox(CPoint pos, int collar)
{
	CDC *pDC = CChildView::DirectXMng.m_pDrawSurface->GetDC();
	
	pDC->SetBkMode(TRANSPARENT);
	CRect r = CRect(pos.x-7, pos.y-5, pos.x+50, pos.y+33);
	//������
	//pDC->SetTextColor(RGB(5,5,5));
	//�����		
	pDC->SetTextColor(RGB(255,255,0));
	//pDC->SetTextColor(RGB(181,181, 255));
	//pDC->FillSolidRect(temp2, RGB(181,181, 255));// �ڽ��� ä���� �׸���.
	//pDC->FillSolidRect(temp2, RGB(247,202,26));// �ڽ��� ä���� �׸���.

	pDC->DrawEdge(r, EDGE_BUMP, BF_RECT);
	//pDC->DrawEdge(temp2, EDGE_SUNKEN, BF_RECT);
	//::DrawText(pDC->m_hDC , m_szChatString, strlen(m_szChatString), &temp, DT_WORDBREAK);
	CChildView::DirectXMng.m_pDrawSurface->ReleaseDC(pDC);
}

void CItem_Small::ShopItemNumber(CPoint pos, int index)
{
	CDC *pDC = CChildView::DirectXMng.m_pDrawSurface->GetDC();

	CString str;//
	str.Format("%3d", m_Shop_Number[index]);

	pDC->SetBkMode(TRANSPARENT);
	CFont pFont, *old_font;
	CRect r;
	////////////////////////
	pFont.CreateFont(-12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH, "����");
	old_font = pDC->SelectObject(&pFont);
	/////////////////////////

	pDC->SetTextColor(RGB(255,255,0));
	pDC->TextOut(pos.x+30, pos.y+20,str);

	pDC->SelectObject(old_font);
	pFont.DeleteObject();
	CChildView::DirectXMng.m_pDrawSurface->ReleaseDC(pDC);


}
