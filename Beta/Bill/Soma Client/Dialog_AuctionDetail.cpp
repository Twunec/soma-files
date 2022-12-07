// Dialog_AuctionDetail.cpp: implementation of the CDialog_AuctionDetail class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "soma.h"
#include "Dialog_AuctionDetail.h"
#include "BBDX_Editor.h"
//#include "BBDX_TextOuter.h"
//#include "TWFont.h"
#include "Item_Total.h"
#include "ChildView.h"
#include "User.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CItem_Total			Item_Total;
extern CUIRes *g_pShowDialog;
extern CChildView			*g_pChildView;

static const char TYPE_NAME[][7] = {"Į", "����", "Ȱ", "â", "��Ŭ", "������", "����", "��", "��ű�", "����", "����", "���"};
static const char SPECIAL_NAME[][4] = {"Str", "Dex", "Int", "Atk", "Def", "HP", "MP"};
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDialog_AuctionDetail::CDialog_AuctionDetail()
{
//	INIT_PTR(m_pTWFont);
//	INIT_PTR(m_pDetailOuter);
//	INIT_PTR(m_pCostOuter);
//	INIT_PTR(m_pUserOuter);
	m_pFont = NULL;
	m_bEnableFocus = TRUE;
}

CDialog_AuctionDetail::~CDialog_AuctionDetail()
{
//	DELETE_SAFE(m_pTWFont);
//	DELETE_SAFE(m_pDetailOuter);
//	DELETE_SAFE(m_pCostOuter);
//	DELETE_SAFE(m_pUserOuter);
	if(m_pFont) delete m_pFont;
}

BOOL CDialog_AuctionDetail::OnButtonAction(int nSpec, int nIndex) 
{
	CUIRes::OnButtonAction(nSpec, nIndex);

	if(nSpec == BTN_CTRL)
	{
		switch(nIndex)
		{
		case 0:			// ��� ����
			{
				CString t_str;
				BOOL bValid;
				m_pMainEditor->GetWindowText(t_str);
				if(t_str.IsEmpty()) return TRUE;
				bValid = TRUE;
				for(int i = 0; i < t_str.GetLength(); i++)
				{
					if(t_str[i] < '0' || t_str[i] > '9')
					{
						bValid = FALSE;
						break;
					}
				}
				if(bValid == FALSE) return TRUE;
				m_vValue = atoi((LPCTSTR)t_str);
				if(m_vValue == 0 || m_vValue <= m_pAuctionItem->m_vCost) return TRUE;

				HideWindow();
				if(m_pParent) m_pParent->CallBack_MessageBox(m_vId, 1);
			}
			break;
		case 1:			// ���
			HideWindow();
			if(m_pParent) m_pParent->CallBack_MessageBox(m_vId, 2);
			break;
		}
	}

	return TRUE;
}

BOOL CDialog_AuctionDetail::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CUIRes::OnKeyDown(nChar, nRepCnt, nFlags);

	if(nChar == VK_RETURN)
	{
		CString t_str;
		BOOL bValid;
		t_str = m_pMainEditor->GetCurEditorText();
		if(t_str.IsEmpty()) return TRUE;
		bValid = TRUE;
		for(int i = 0; i < t_str.GetLength(); i++)
		{
			if(t_str[i] < '0' || t_str[i] > '9')
			{
				bValid = FALSE;
				break;
			}
		}
		if(bValid == FALSE) return TRUE;
		m_vValue = atoi((LPCTSTR)t_str);
		if(m_vValue == 0) return TRUE;
		
		HideWindow();
		if(m_pParent) m_pParent->CallBack_MessageBox(m_vId, 1);

		return TRUE;
	}
	else if(nChar == VK_ESCAPE)
	{
		HideWindow();
		if(m_pParent) m_pParent->CallBack_MessageBox(m_vId, 2);

		return TRUE;
	}

	return FALSE;
}

BOOL CDialog_AuctionDetail::Draw(CDDSurface *pDest)
{
	if(m_bShow == FALSE) return TRUE;

	CUIRes::Draw(pDest);

	DWORD dwTrans;
	CRect rtDst, rtSrc;
	CPoint s_pos;

	Draw3ButtonCtrl(pDest, 0, 1);

	// ������ �׸�
	dwTrans = DDBLTFAST_WAIT|DDBLTFAST_SRCCOLORKEY;
	s_pos = m_arrArea[0]->m_vRect.TopLeft();
	s_pos.Offset(m_ptOffset);
	rtSrc = Item_Total.m_Item_Small->m_SprData[m_pAuctionItem->m_vPicNum].rcV;
	pDest->BltFast(s_pos, Item_Total.m_Item_Small->m_lpSurface, &rtSrc, dwTrans);

	CDC *pDC = pDest->GetDC();
	CFont *old_font = (CFont *)pDC->SelectObject(m_pFont);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(255,255,255));

	// ������ ����
	rtDst = m_arrArea[1]->m_vRect;
	rtDst.OffsetRect(m_ptOffset);
//	m_pDetailOuter->DrawTexts(pDest, rtDst);
	pDC->DrawText(m_strDetail, &rtDst, DT_TOP|DT_LEFT|DT_EXTERNALLEADING);

	// �����
	rtDst = m_arrArea[3]->m_vRect;
	rtDst.OffsetRect(m_ptOffset);
//	m_pUserOuter->DrawTexts(pDest, rtDst);
	pDC->DrawText(m_strUser, &rtDst, DT_TOP|DT_LEFT|DT_SINGLELINE);

	// �ְ�
	rtDst = m_arrArea[4]->m_vRect;
	rtDst.OffsetRect(m_ptOffset);
//	m_pCostOuter->DrawTexts(pDest, rtDst);
	pDC->DrawText(m_strCost, &rtDst, DT_TOP|DT_LEFT|DT_SINGLELINE);

	pDC->SelectObject(old_font);
	pDest->ReleaseDC(pDC);

	// ������ ���� ����
	m_pMainEditor->DCDrawOffsetedCurText(pDest, m_ptOffset);

	return TRUE;
}

BOOL CDialog_AuctionDetail::Create(CDirectDraw *pDD, CString szLibName, int nType, BOOL bModal, BOOL bMoveable, BOOL bTrans)
{
	if (!CUIRes::Create(pDD, szLibName, nType, bModal, bMoveable, bTrans)) {
		return FALSE;
	}

/*	m_pTWFont = new CTWFont();
	if (!m_pTWFont->CreateFontWithoutPath("Soma14", 14, 14))
	{
		delete m_pTWFont; m_pTWFont=NULL;
		TRACE("####### Dialog AuctionSell Init ����.. ############ \n");
		return FALSE;
	}
	m_pDetailOuter = new BBDX_TextOuter(m_pTWFont, 14, 14);
	m_pUserOuter = new BBDX_TextOuter(m_pTWFont, 14, 14);
	m_pCostOuter = new BBDX_TextOuter(m_pTWFont, 14, 14);*/
	m_pFont = new CFont();
	m_pFont->CreateFont(-12, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH, "����");

	m_pMainEditor = new BBDX_Editor(m_pWnd, this, FALSE, m_arrArea[2]->m_vRect);

	return TRUE;
}

void CDialog_AuctionDetail::ShowWindow(int Id, CUIRes *pParent, ITEM_AUCTION *item_auction)
{
	if(!IsLoading())
	{
		SetWnd(g_pChildView);
		if(!Create(CChildView::DirectXMng.m_pDD, "Auct-D.lib", 0, TRUE, FALSE, FALSE))
		{
			return;
		}
	}

	if(g_pShowDialog && g_pShowDialog != pParent) g_pShowDialog->HideAllWindow();
	g_pShowDialog = this;

	m_vId = Id;
	m_pParent = pParent;
	if(m_pParent) m_pParent->m_pChild = this;
	m_pAuctionItem = item_auction;

	CString t_str, t_str1;

//	t_str.Format("%s ����:%s", m_pAuctionItem->m_vName, TYPE_NAME[m_pAuctionItem->m_vType]);
//	m_pDetailOuter->SetString(t_str);
	switch(m_pAuctionItem->m_vGender)
	{
	case ITEM_WOMAN:
		m_strDetail.Format("%s(��) ����:%s", m_pAuctionItem->m_vName, TYPE_NAME[m_pAuctionItem->m_vType]);
		break;
	case ITEM_MAN:
		m_strDetail.Format("%s(��) ����:%s", m_pAuctionItem->m_vName, TYPE_NAME[m_pAuctionItem->m_vType]);
		break;
	default:
		m_strDetail.Format("%s ����:%s", m_pAuctionItem->m_vName, TYPE_NAME[m_pAuctionItem->m_vType]);
		break;
	}
		
	if(m_pAuctionItem->m_vType <= TYPE_ARMOR)
	{
		CString tt_str, tt_str1;
		BOOL btrue = FALSE;
		
		if(m_pAuctionItem->m_vType == TYPE_ARMOR)
		{
			tt_str.Format("\n����:%d~%d ������:%d\n�ʿ�Str:%d �ʿ�Int:%d",
				m_pAuctionItem->m_vMinDamage, m_pAuctionItem->m_vMaxDamage, m_pAuctionItem->m_vUsage,
				m_pAuctionItem->m_vLimitStr, m_pAuctionItem->m_vLimitInt);
		}
		else if(m_pAuctionItem->m_vType < TYPE_WEAPON)
		{
			tt_str.Format("\n����:%d~%d ������:%d\n�ʿ�Str:%d �ʿ�Int:%d �ʿ���õ�:%d",
				m_pAuctionItem->m_vMinDamage, m_pAuctionItem->m_vMaxDamage, m_pAuctionItem->m_vUsage,
				m_pAuctionItem->m_vLimitStr, m_pAuctionItem->m_vLimitInt, m_pAuctionItem->m_vLimitSkill);
		}
		m_strDetail += tt_str;
		tt_str = "\n";
		for(int k = 0; k < 7; k++)
		{
			if(m_pAuctionItem->m_vSpecial[k] != 0)
			{
				if(btrue) tt_str += _T(",");
				if(m_pAuctionItem->m_vSpecial[k] > 0) tt_str1.Format("%s+%d", SPECIAL_NAME[k], m_pAuctionItem->m_vSpecial[k]);
				else tt_str1.Format("%s%d", SPECIAL_NAME[k], m_pAuctionItem->m_vSpecial[k]);
				tt_str += tt_str1;
				btrue = TRUE;
			}
		}
		if(btrue == TRUE)
		{
			m_strDetail += tt_str;
		}
		if(m_pAuctionItem->m_strMagic.IsEmpty() == FALSE)
		{
			m_strDetail += "\n";
			m_strDetail += m_pAuctionItem->m_strMagic;
		}
		if(m_pAuctionItem->m_strSNum.IsEmpty() == FALSE)
		{
			m_strDetail += "\n";
			m_strDetail += m_pAuctionItem->m_strSNum;
		}
	}
	else if(m_pAuctionItem->m_vType == TYPE_ACC)
	{
		CString tt_str, tt_str1;
		BOOL btrue = FALSE;
		
		tt_str.Format("\n������:%d",
			m_pAuctionItem->m_vUsage);
		m_strDetail += tt_str;
		tt_str = "\n";
		for(int k = 0; k < 7; k++)
		{
			if(m_pAuctionItem->m_vSpecial[k] != 0)
			{
				if(btrue) tt_str += _T(",");
				if(m_pAuctionItem->m_vSpecial[k] > 0) tt_str1.Format("%s+%d", SPECIAL_NAME[k], m_pAuctionItem->m_vSpecial[k]);
				else tt_str1.Format("%s%d", SPECIAL_NAME[k], m_pAuctionItem->m_vSpecial[k]);
				tt_str += tt_str1;
				btrue = TRUE;
			}
		}
		if(btrue == TRUE)
		{
			m_strDetail += tt_str;
		}
		if(m_pAuctionItem->m_strMagic.IsEmpty() == FALSE)
		{
			m_strDetail += "\n";
			m_strDetail += m_pAuctionItem->m_strMagic;
		}
		if(m_pAuctionItem->m_strSNum.IsEmpty() == FALSE)
		{
			m_strDetail += "\n";
			m_strDetail += m_pAuctionItem->m_strSNum;
		}
	}
	else if(m_pAuctionItem->m_vType == TYPE_POTION || m_pAuctionItem->m_vType == TYPE_FOOD)
	{
		CString tt_str, tt_str1;
		BOOL btrue = FALSE;
		
		tt_str.Format("\n����:%d", m_pAuctionItem->m_vUsage);
		m_strDetail += tt_str;

		tt_str = "\n";
		for(int k = 0; k < 7; k++)
		{
			if(m_pAuctionItem->m_vSpecial[k] != 0)
			{
				if(btrue) tt_str += _T(",");
				if(m_pAuctionItem->m_vSpecial[k] > 0) tt_str1.Format("%s+%d", SPECIAL_NAME[k], m_pAuctionItem->m_vSpecial[k]);
				else tt_str1.Format("%s%d", SPECIAL_NAME[k], m_pAuctionItem->m_vSpecial[k]);
				tt_str += tt_str1;
				btrue = TRUE;
			}
		}
		if(btrue == TRUE)
		{
			m_strDetail += tt_str;
		}
		if(m_pAuctionItem->m_strMagic.IsEmpty() == FALSE)
		{
			m_strDetail += "\n";
			m_strDetail += m_pAuctionItem->m_strMagic;
		}
		if(m_pAuctionItem->m_strSNum.IsEmpty() == FALSE)
		{
			m_strDetail += "\n";
			m_strDetail += m_pAuctionItem->m_strSNum;
		}
	}
	else
	{
		CString tt_str;

		tt_str.Format("\n����:%d", m_pAuctionItem->m_vUsage);
		m_strDetail += tt_str;
	}
	m_strUser = m_pAuctionItem->m_vRegistrant;
	m_strCost.Format("%lu", m_pAuctionItem->m_vCost);

	CUIRes::ShowWindow();
}

void CDialog_AuctionDetail::HideWindow()
{
	CUIRes::HideWindow();

	if(m_pParent)
	{
		m_pParent->m_pChild = NULL;
		if(m_pParent->IsVisible())
		{
			g_pShowDialog = m_pParent;
			m_pParent->SetFocus();
		}
		else g_pShowDialog = NULL;
	}
	else g_pShowDialog = NULL;

	m_pAuctionItem = NULL;
}

void CDialog_AuctionDetail::HideAllWindow()
{
	CUIRes::HideWindow();

	if(m_pParent)
	{
		m_pParent->m_pChild = NULL;
		m_pParent->HideAllWindow();
	}

	m_pAuctionItem = NULL;
}
