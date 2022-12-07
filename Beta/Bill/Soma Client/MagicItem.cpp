// MagicItem.cpp: implementation of the CMagicItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MagicItem.h"
#include "ChildView.h"
#include "Item_Total.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//extern CItem_sArm    Item_sArm;
extern CItem_Total         Item_Total;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMagicItem::CMagicItem()
{
	m_Caption = 0;// ������ ���� ĸ���� �߰� �ϴ� �ɼ� �÷���..
	m_lpSurface2 = NULL;
	m_SprData2 = NULL;
	m_lpSurf = NULL;
}

CMagicItem::~CMagicItem()
{
	if(m_lpSurf)
	{
		m_lpSurf->Release();
		m_lpSurf = NULL;
	}
	SAFE_DELETE(m_lpSurface2);
	SAFE_DELETES(m_SprData2);
}

void CMagicItem::InitItem(CDirectDraw *pDirectDraw)
{
	InitData(pDirectDraw);
	for(int i=0;i<50;i++)
		m_Item_Fixpos[i] = m_Item_pos[i];// �ڸ��� ������Ų��.����..

	m_UpDown=0;
	m_UpDown_Shop=0;
	m_UpDown_Shopme=0;
	m_ShopSelect=-1;

	m_Item_Pic[0] = 0;// �ӽ�  ��������..
	m_Item_Pic[1] = 1;

	m_UserItem[0] = -1;
	m_UserItem[1] = -1;
	m_UserItem[2] = -1;

//	Load_image("Magic-B.bmp");// �ӽ÷� ������ �Ѵ�..���� �����ϱ�..��..
	LoadObm("Magic-B.obm");
	LoadSpr("Magic-B.spr");
//	Load_image2("Magic-S.bmp");
	LoadObm2("Magic-S.obm");
	LoadSpr2("Magic-S.spr");
}

void CMagicItem::Load_image2(LPCSTR szFileName)
{
	CString szTmpFileName;// = szFileName;
	BOOL test;

	const CString szExePath = CDirectDraw::GetExecutionPath();
	szTmpFileName.Format("%sitem\\%s", (LPCTSTR)szExePath ,szFileName);

	m_lpSurface2 = new CDDSurface;

	test = m_lpSurface2->CreateFromImage(m_pDirectDraw, szTmpFileName, 0);

	m_lpSurface2->SetColorKey(RGB(255, 0, 255));
}

void CMagicItem::LoadSpr2(LPCSTR szFileName)
{
	int i;
	CString szTmpFileName;
	_SPR_HEADER hSpr;

	const CString szExePath = CDirectDraw::GetExecutionPath();
	szTmpFileName.Format("%sspr\\%s", (LPCTSTR)szExePath ,szFileName);

	CFile* pFile = new CFile(szTmpFileName, CFile::modeRead);
	pFile->Read(&hSpr, sizeof(_SPR_HEADER)); // ��� �б�
	
	// ��������Ʈ ���� - �������� ���̴� �ΰ����� ������.
	//_SPR_NORMAL spr;
	m_SprData2 = new _SPR_NORMAL[hSpr.nQt];
	for(i = 0; i < hSpr.nQt; i++)
	{
		pFile->Read(&m_SprData2[i], sizeof(_SPR_NORMAL));
	}
	pFile->Close();
	delete pFile;
}

BOOL CMagicItem::MouseProcess(BBDX_MouseInformation *pMouseInfo, int Dlg_Pos, int Select_Box, int MoveFlag)
{
	// ������ �÷��׸� ������.m_Item_Flag
	// ��� �̻���...� �޴�..��� �־��� ��� �޴�..�̷�������..��..
	// ���콺�� �����϶� ����..
	int i;

/*	if(m_Select_Item >= 0)
	{
		i = m_Select_Item;
		if(m_Move_Flag[i] )// = TRUE;// �巡�׸� �Ҷ�..����ؾ�¡..
		{
			// �̰����� �������� � ��ҿ��ٰ� ���Ҵ��� �Ǵ��ؾߵȴ�..
			if(pMouseInfo->IsLButtonDobleDown())
			{
				TRACE("���� ������ ����Ŭ��..\n");
			}
			/*
			if(pMouseInfo->IsLButtonUp())
			{
				m_Move_Flag[i] = FALSE;
				m_Caption = 0;// ���� â�� ���� ������.
//				CString str;
//				str.Format("item�� %d�����̾�α��� %d�� ���ڿ� ���Ҵ�11111111.", Dlg_Pos, Select_Box);
//				CChildView::SocketMng.SendChat(str);		

				// ���� �ڸ��� ���� ���� �����...���߿� �̵��� �ϰ� �ϴ��� �ؾ߰���..��..
				// ���� ��ġ�� ���Ŀ� ����..
				m_Select_Item = -1;
				if(MoveFlag == 0) return TRUE;

				m_Item_pos[i] = m_Item_Fixpos[i];

				if(Dlg_Pos != 0)
				{
					//m_Item_Type[i] += 1;
					//Output(i);// ��ȯ ������� �ڱ�.ū�̹��� �ϳ� �����̹��� �ϳ�..�̷�������...����..
				//	Item_sArm.Input(4);
				}
				else
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
			*/
//			return TRUE;
//		}
//	}


	for(i=0; i<50;i++)
	{
		if(InMousePos(pMouseInfo->m_posMouse, m_BoxRect[i]) || m_Move_Flag[i])
		{//�޴������� �ִ�..
			if(pMouseInfo->IsLButtonDobleDown())
			{
				m_Current_Item = i;
				
				if(i < 47)
				{
					if(m_UserItem[0] == -1)
						m_UserItem[0] = m_Item_Pic[i];
					else if(m_UserItem[1] == -1)
						m_UserItem[1] = m_Item_Pic[i];
					else if(m_UserItem[2] == -1)
						m_UserItem[2] = m_Item_Pic[i];
					else
						TRACE("������ �ڽ��� �����ִ�.\n");
				}
				else// ���� �Ǿ� �ִ�...����������.
				{
					m_UserItem[i-47] = -1;// �����Ѵ�. 
				}

				//TRACE("���� ������ ����Ŭ��..\n");
			}
			else if (pMouseInfo->IsLButtonDown()) 
			{
			}
/*				m_Move_Flag[i] = TRUE;// �巡�׸� �Ҷ�..����ؾ�¡..
				m_Old_Pos = pMouseInfo->m_posMouse;c
				m_Current_Item = i;// ���� ���õǾ��ִ�..������..��ȣ..
//				CString str;
//				str.Format(" %d�� item�� ����", m_Current_Item);
//				CChildView::SocketMng.SendChat(str);		
				m_Select_Item = i;// ���콺�� ������ �ʱ�ȭ ��.
				m_ShopSelect = i;// �������� ���õ� �������� �����ǰ� �ϱ����ؼ�..
				m_Caption = 1;// ���� â�� �߰� �Ѵ�.

//				ViewCaption(pMouseInfo->m_posMouse, "���������� ^^");

			}
*/
			m_Item_Flag = i;
			return TRUE;
			
		}
		else if(m_Item_Flag == i)
			m_Item_Flag = -1;
	}
	return FALSE;
}

void CMagicItem::ViewCaption(CPoint pos, CString str, int tmp_y)
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

void CMagicItem::Draw(CDDSurface* pDestSurf, int count, int tmp_y,  int index)
{
	CItem::Draw(pDestSurf, count, tmp_y, index);
	
	if(m_Caption == 1)
	{
		CString str = _T("�� ��������"); str += m_Item_Name[m_Select_Item]; str += _T("�̴�.");
		ViewCaption(m_Item_pos[m_Select_Item], str, tmp_y);
	}
}

void CMagicItem::DrawShop(int x, int y, CDDSurface* pDestSurf, int count,  int index)
{
	CItem::Draw(x, y, pDestSurf, count, index);
	
//	CPoint pos = CPoint(x,y);
//	if(m_ShopSelect == index)

//	ViewSelectBox(pos,0);

/*	if(m_Caption == 1 && m_Select_Item == index)
	{

		CString str = _T("�� ��������"); str += m_Item_Name[m_Select_Item]; str += _T("�̴�.");
		ViewCaption(pos, str, 0);
	}
*/
}

void CMagicItem::InvWindowDraw(CDDSurface *pDrawSurface)
{
	// �迭�� �����..�켱 ������ ���ؼ� ���⼭ �ѷ��ش�..����..
	int count = 0;//m_UpDown;
	int tmp = 33;
	for(int i=0;i<50;i++)
		m_BoxRect[i] = CRect(0,0,0,0);// �ʱ�ȭ..
	for(i=4*count;i<8+count*4;i++)// �ӽ�...
	{
		Draw(pDrawSurface,0, count*40+15, i);
	}
}

void CMagicItem::ShopMeWindowDraw(CDDSurface *pDrawSurface)
{
	int x, y, count=0;
	for(int i=0;i<50;i++)
		m_BoxRect[i] = CRect(0,0,0,0);// �ʱ�ȭ..
	for(i=m_UpDown_Shopme;i<m_UpDown_Shopme+5;i++)
	{
		x = 85;
		y = 199+count*46;
		DrawShop(x, y, pDrawSurface,0,  i);
		count++;
	}
}

void CMagicItem::ShopWindowDraw(CDDSurface *pDrawSurface)
{
	int x, y, count=0;
	for(int i=m_UpDown_Shop;i<m_UpDown_Shop+5;i++)
	{
		x = 50;
		y = 153+count*75;
		DrawShop(x, y, pDrawSurface,0,  i);
		count++;
	}

	for(i=0;i<3;i++)
	{
		x = 474 + 47*i;
		y = 542;
		if(m_UserItem[i] >= 0)
			ViewItemBox(x, y, 47+i, m_UserItem[i], pDrawSurface);
		//m_UserItem[i]
	}
}

void CMagicItem::InvItemUp()
{
	m_UpDown--;
	if(m_UpDown < 0) m_UpDown = 0;
}

void CMagicItem::InvItemDown()
{
	m_UpDown++;
	if(m_UpDown >= 4) m_UpDown = 3;
}

void CMagicItem::ShopItemUp()
{
	m_UpDown_Shop--;
	if(m_UpDown_Shop < 0) m_UpDown_Shop = 0;
}

void CMagicItem::ShopItemDown()
{
	m_UpDown_Shop++;
	if(m_UpDown_Shop < 0) m_UpDown_Shop = 0;
}

void CMagicItem::ShopMeItemUp()
{
	m_UpDown_Shopme--;
	if(m_UpDown_Shopme < 0) m_UpDown_Shopme = 0;
}

void CMagicItem::ShopMeItemDown()
{
	m_UpDown_Shopme++;
	if(m_UpDown_Shopme > 45) m_UpDown_Shopme = 45;
}

void CMagicItem::ViewSelectBox(CPoint pos, int collar)
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

void CMagicItem::LoadObm2(LPCTSTR szFileName)
{
	CString szTmpFileName;

	const CString szExePath = CDirectDraw::GetExecutionPath();
	szTmpFileName.Format("%sitem\\%s", (LPCTSTR)szExePath ,szFileName);

	m_lpSurf2 = CChildView::g_pTEng.SurfaceCreateWith16BMP(szTmpFileName, FALSE, RGB(255, 0, 255), TRUE);

	m_lpSurface2 = new CDDSurface(m_lpSurf2);
}