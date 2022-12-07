// Dialog_AccountLogin.cpp: implementation of the CDialog_AccountLogin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Dialog_AccountLogin.h"
#include "ChildView.h"
#include "Item_Total.h"
#include "BBDX_TextOuter.h"
#include "BBDX_Editor.h"
#include "./DManage/BB_Direct.h"
#include "TWFont.h"
#include "MainFrm.h"

extern CItem_Total   Item_Total;

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDialog_AccountLogin::CDialog_AccountLogin()
{
	m_bEnableFocus = FALSE;
	m_Dialog_AccountLogin_Del = 0;
//	m_lpSurface = NULL;
	m_vSex = FALSE;
	m_vViewMode = 0;

	m_aniIndex = 0;
	m_TickCount = GetTickCount();
	m_id_flag = NULL;
	m_vOk = 0;
	m_PersonalCheckOK = 0;

	m_KorlangMode = false;
	m_KorlangMode2 = false;
	m_JuMinCheck = false;
	m_JuMinCheck2 = false;

	m_pBBDX_Editor_id = NULL;
	m_pBBDX_Editor_password = NULL;
	m_pBBDX_Editor_password2 = NULL;//3 �н����� Ȯ��
	m_pBBDX_Editor_name = NULL;//4
	m_pBBDX_Editor_email = NULL;//5
	m_pBBDX_Editor_number1 = NULL;//6 �ֹι�ȣ
	m_pBBDX_Editor_number2 = NULL;//6 �ֹι�ȣ
	m_pBBDX_Editor_address = NULL;//7 �ּ�
	m_pBBDX_Editor_phonenumber = NULL;//8��ȭ��ȣ
}

CDialog_AccountLogin::~CDialog_AccountLogin()
{
	if(__GetMainWnd())  __GetMainWnd()->m_wndView.SetFocus();

	SAFE_DELETE(m_pBBDX_Editor_id);
	SAFE_DELETE(m_pBBDX_Editor_password);
	SAFE_DELETE(m_pBBDX_Editor_password2);//3 �н����� Ȯ��
	SAFE_DELETE(m_pBBDX_Editor_name);//4
	SAFE_DELETE(m_pBBDX_Editor_email);//5
	SAFE_DELETE(m_pBBDX_Editor_number1);//6 �ֹι�ȣ
	SAFE_DELETE(m_pBBDX_Editor_number2);//6 �ֹι�ȣ
	SAFE_DELETE(m_pBBDX_Editor_address);//7 �ּ�
	SAFE_DELETE(m_pBBDX_Editor_phonenumber);//8��ȭ��ȣ
}

void CDialog_AccountLogin::KillFocus()
{
}

void CDialog_AccountLogin::SetFocus()
{
}

void  CDialog_AccountLogin::DrawEditorText(CDDSurface *pSurface, int view_mode, int id_flag)
{
	switch(view_mode)
	{
		case 0:
			  if(id_flag == 0)
			  {
			 	 m_pBBDX_Editor_id->SetFocus();
				 m_pBBDX_Editor_id->GetText();
			  }
			  else if(id_flag == 1)
			  {
			 	 m_pBBDX_Editor_password->SetFocus();
				 m_pBBDX_Editor_password->GetText();
			  }
			
			  if(m_pBBDX_Editor_id) 
			  	m_pBBDX_Editor_id->DCDrawOffsetedCurText(pSurface);	//�����Ϳ� ������ �� �׸���(Editor �� ���� �Ⱥ��̴µ� ����)
			  if(m_pBBDX_Editor_password)
				m_pBBDX_Editor_password->DCDrawOffsetedCurText(pSurface, CPoint(0,0), RGB(255,255,0), TRUE);
			  break;

		case 1:
			  if(id_flag== 0)
			  {
			 	 m_pBBDX_Editor_id->SetFocus();
				 m_pBBDX_Editor_id->GetText();
			  }
			  else if(id_flag== 1)
			  {
			 	 m_pBBDX_Editor_password->SetFocus();
				 m_pBBDX_Editor_password->GetText();
			  }
			  else if(id_flag== 2)
			  {
			 	 m_pBBDX_Editor_password2->SetFocus();
				 m_pBBDX_Editor_password2->GetText();
			  }
			  else if(id_flag== 3)
			  {
			 	 m_pBBDX_Editor_name->SetFocus();
				 m_pBBDX_Editor_name->GetText();
			  }
			  else if(id_flag== 4)
			  {
			 	 m_pBBDX_Editor_email->SetFocus();
				 m_pBBDX_Editor_email->GetText();
			  }
			  else if(id_flag== 5)
			  {
				 m_pBBDX_Editor_number1->SetFocus();
				 m_pBBDX_Editor_number1->GetText();
			  }
			  else if(id_flag== 6)
			  {
				 m_pBBDX_Editor_number2->SetFocus();
				 m_pBBDX_Editor_number2->GetText();
			  }
			  else if(id_flag== 7)
			  {
				 m_pBBDX_Editor_address->SetFocus();
				 m_pBBDX_Editor_address->GetText();
			  }
			  else if(id_flag== 8)
			  {
			 	 m_pBBDX_Editor_phonenumber->SetFocus();
				 m_pBBDX_Editor_phonenumber->GetText();
			  } 

		      m_pBBDX_Editor_id->DCDrawOffsetedCurText(pSurface);	//�����Ϳ� ������ �� �׸���(Editor �� ���� �Ⱥ��̴µ� ����)
			  m_pBBDX_Editor_password->DCDrawOffsetedCurText(pSurface, CPoint(0,0), RGB(255,255,0), TRUE);
			  m_pBBDX_Editor_password2->DCDrawOffsetedCurText(pSurface, CPoint(0,0), RGB(255,255,0), TRUE);
			  m_pBBDX_Editor_name->DCDrawOffsetedCurText(pSurface);
			  m_pBBDX_Editor_email->DCDrawOffsetedCurText(pSurface);
			  m_pBBDX_Editor_number1->DCDrawOffsetedCurText(pSurface);
			  m_pBBDX_Editor_number2->DCDrawOffsetedCurText(pSurface);
			  m_pBBDX_Editor_address->DCDrawOffsetedCurText(pSurface);
			  m_pBBDX_Editor_phonenumber->DCDrawOffsetedCurText(pSurface);
			  break;
		case 2:
			  if(id_flag== 0)
			  {
			 	 m_pBBDX_Editor_name->SetFocus();
				 m_pBBDX_Editor_name->GetText();
			  }
			  else if(id_flag== 1)
			  {
				 m_pBBDX_Editor_number1->SetFocus();
				 m_pBBDX_Editor_number1->GetText();
			  }
			  else if(id_flag== 2)
			  {
				 m_pBBDX_Editor_number2->SetFocus();
				 m_pBBDX_Editor_number2->GetText();
			  }
			  m_pBBDX_Editor_name->DCDrawOffsetedCurText(pSurface);
			  m_pBBDX_Editor_number1->DCDrawOffsetedCurText(pSurface);
			  m_pBBDX_Editor_number2->DCDrawOffsetedCurText(pSurface);
			  break;
	}
}

void  CDialog_AccountLogin::CreateEditor(CWnd *pParent, int view_mode)
{
	CSize fontSize(12, 12);
    CRect editorRect;

	m_KorlangMode = false;
	m_KorlangMode2 = false;
	m_JuMinCheck = false;
	m_JuMinCheck2 = false;

	switch(view_mode)
	{
	   case 0: 
   			 editorRect = GetTextOutRect(10); // id.
			 SAFE_DELETE(m_pBBDX_Editor_id);
			 m_pBBDX_Editor_id = new BBDX_Editor(pParent, NULL, FALSE, editorRect);
			 m_pBBDX_Editor_id->SetFocus();
			 m_pBBDX_Editor_id->LimitText(12);
			 m_pBBDX_Editor_id->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.

			 editorRect = GetTextOutRect(11);// password.
			 SAFE_DELETE(m_pBBDX_Editor_password);
			 m_pBBDX_Editor_password = new BBDX_Editor(pParent, NULL, FALSE, editorRect, FALSE, 0, ES_PASSWORD);
			 m_pBBDX_Editor_password->LimitText(12); 
			 m_pBBDX_Editor_password->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.

			 //�����޼����� ��ġ����.
		 	 m_vMsgDlgPos = CPoint( GetTextOutRect(13).left - GetTextOutRect(12).left,
				                    GetTextOutRect(13).top - GetTextOutRect(12).top);
			 m_vMsgDlgPos.Offset(301,161);
	         m_vMsgRect = GetTextOutRect(13);
			 m_vMsgRect.OffsetRect(-m_vMsgRect.left,-m_vMsgRect.top);
			 m_vMsgRect.OffsetRect(m_vMsgDlgPos.x,m_vMsgDlgPos.y);
			 break;

	   case 1:
			 //1
			 editorRect = GetTextOutRect(0);
			 SAFE_DELETE(m_pBBDX_Editor_id);
			 m_pBBDX_Editor_id = new BBDX_Editor(pParent, NULL, FALSE, editorRect);
			 m_pBBDX_Editor_id->LimitText(12);
			 m_pBBDX_Editor_id->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.
			 //2
			 editorRect = GetTextOutRect(1);
			 SAFE_DELETE(m_pBBDX_Editor_password);
			 m_pBBDX_Editor_password = new BBDX_Editor(pParent, NULL, FALSE, editorRect, FALSE, 0, ES_PASSWORD);
			 m_pBBDX_Editor_password->LimitText(8);
			 m_pBBDX_Editor_password->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.
			 //3
			 editorRect = GetTextOutRect(2);
			 SAFE_DELETE(m_pBBDX_Editor_password2);
			 m_pBBDX_Editor_password2 = new BBDX_Editor(pParent, NULL, FALSE, editorRect, FALSE, 0, ES_PASSWORD);
			 m_pBBDX_Editor_password2->LimitText(8);
			 m_pBBDX_Editor_password2->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.
			 //4
			 editorRect = GetTextOutRect(3);
			 SAFE_DELETE(m_pBBDX_Editor_name);
			 m_pBBDX_Editor_name = new BBDX_Editor(pParent, NULL, FALSE, editorRect);
			 m_pBBDX_Editor_name->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.
			 //5
			 editorRect = GetTextOutRect(4);
			 SAFE_DELETE(m_pBBDX_Editor_email);
			 m_pBBDX_Editor_email = new BBDX_Editor(pParent, NULL, FALSE, editorRect);
			 m_pBBDX_Editor_email->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.
			 //6
			 editorRect = GetTextOutRect(5);
			 SAFE_DELETE(m_pBBDX_Editor_number1);
			 m_pBBDX_Editor_number1 = new BBDX_Editor(pParent, NULL, FALSE, editorRect);
			 m_pBBDX_Editor_number1->LimitText(6);
			 m_pBBDX_Editor_number1->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.

			 editorRect = GetTextOutRect(6);
			 SAFE_DELETE(m_pBBDX_Editor_number2);
			 m_pBBDX_Editor_number2 = new BBDX_Editor(pParent, NULL, FALSE, editorRect);
			 m_pBBDX_Editor_number2->LimitText(7);
			 m_pBBDX_Editor_number2->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.

			 //7
			 editorRect = GetTextOutRect(7);
			 SAFE_DELETE(m_pBBDX_Editor_address);
			 m_pBBDX_Editor_address = new BBDX_Editor(pParent, NULL, FALSE, editorRect);
			 m_pBBDX_Editor_address->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.
			 //8
			 editorRect = GetTextOutRect(8);
			 SAFE_DELETE(m_pBBDX_Editor_phonenumber);
			 m_pBBDX_Editor_phonenumber = new BBDX_Editor(pParent, NULL, FALSE, editorRect);
			 m_pBBDX_Editor_phonenumber->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.

			 m_pBBDX_Editor_id->SetFocus();

			 //�����޼����� ��ġ����.
		 	 m_vMsgDlgPos = CPoint( GetTextOutRect(10).left - GetTextOutRect(9).left,
				                    GetTextOutRect(10).top - GetTextOutRect(9).top);
			 m_vMsgDlgPos.Offset(301,161);
	         m_vMsgRect = GetTextOutRect(10);
			 m_vMsgRect.OffsetRect(-m_vMsgRect.left,-m_vMsgRect.top);
			 m_vMsgRect.OffsetRect(m_vMsgDlgPos.x,m_vMsgDlgPos.y);

		     break;

	   case 2:
			 editorRect = GetTextOutRect(15);
			 SAFE_DELETE(m_pBBDX_Editor_name);
			 m_pBBDX_Editor_name = new BBDX_Editor(pParent, NULL, FALSE, editorRect);
			 m_pBBDX_Editor_name->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.

 			 editorRect = GetTextOutRect(16);
			 SAFE_DELETE(m_pBBDX_Editor_number1);
			 m_pBBDX_Editor_number1 = new BBDX_Editor(pParent, NULL, FALSE, editorRect);
			 m_pBBDX_Editor_number1->LimitText(6);
			 m_pBBDX_Editor_number1->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.

			 editorRect = GetTextOutRect(17);
			 SAFE_DELETE(m_pBBDX_Editor_number2);
			 m_pBBDX_Editor_number2 = new BBDX_Editor(pParent, NULL, FALSE, editorRect);
			 m_pBBDX_Editor_number2->LimitText(7);
			 m_pBBDX_Editor_number2->m_bChat = 0;// ä���忡 ���ȵɲ�..����Ű������ ����.

			 m_pBBDX_Editor_name->SetFocus();

		     break;
	}
}

void CDialog_AccountLogin::DeletePersonalCheck()
{
	if(__GetMainWnd())  __GetMainWnd()->m_wndView.SetFocus();
	SAFE_DELETE(m_pBBDX_Editor_name);//4
	SAFE_DELETE(m_pBBDX_Editor_number1);//6 �ֹι�ȣ
	SAFE_DELETE(m_pBBDX_Editor_number2);//6 �ֹι�ȣ
}

BOOL CDialog_AccountLogin::Create(CDirectDraw *pDD, CString szLibName, int nType, BOOL bMoveable, BOOL bTrans)
{
	if(m_pDDSurface) { delete m_pDDSurface; m_pDDSurface =	NULL; }
	if(!CUIRes::Create(pDD, szLibName, nType, bMoveable, bTrans)) {
	   return FALSE;
	}

	//�ִϸ��̼� �Ǵ°��� rect�� ����.
	if(m_vViewMode == 0)
	{
		m_aniPoint = m_arrArea[9]->m_vRect.TopLeft();
	}

	return TRUE;
}

CRect CDialog_AccountLogin::GetTextOutRect(int index)
{
	CRect rect;

	rect = m_arrArea[index]->m_vRect; 

	return rect;
}

BOOL CDialog_AccountLogin::MouseProcess(BBDX_MouseInformation *pMouseInfo, int *id_flag)
{
	ASSERT(pMouseInfo);
	
	m_id_flag = id_flag;

	if(pMouseInfo->IsLButtonDown())
	{
		OnLButtonDown(pMouseInfo);
		TRACE0("LButtonDown\n");
	}
	if(pMouseInfo->IsMouseMove())
	{
		OnMouseMove(pMouseInfo);
	}
	if(pMouseInfo->IsLButtonUp())
	{
		OnLButtonUp(pMouseInfo);
		TRACE0("LButtonUp\n");
	}

	return TRUE;
}

BOOL CDialog_AccountLogin::Draw( CDDSurface* pDestSurf )
{
	CUIRes::Draw(pDestSurf);

	DWORD dwTrans = DDBLTFAST_SRCCOLORKEY|DDBLTFAST_WAIT;

	if(m_vViewMode == 0 || m_vViewMode == 2 || m_vViewMode == 3 || m_vViewMode == 5)
	{
		if((GetTickCount() - m_TickCount) > 100)
		{
		   m_TickCount = GetTickCount();
		   pDestSurf->BltFast(m_aniPoint, m_pDDSurface, &m_arrArea[m_aniIndex]->m_vRect, dwTrans);
		   m_aniIndex++;
		   m_aniIndex %= 9;
		}
		else pDestSurf->BltFast(m_aniPoint, m_pDDSurface, &m_arrArea[m_aniIndex]->m_vRect, dwTrans);

		 Draw3ButtonCtrl(pDestSurf, 0, 3);
	}
	else if(m_vViewMode == 1) Draw3ButtonCtrl(pDestSurf, 0, 3);

	if(m_vViewMode == 2) 
	{
		CPoint point(220,180);

		pDestSurf->BltFast( point, m_pDDSurface, &m_arrArea[14]->m_vRect, DDBLTFAST_SRCCOLORKEY );
		Draw3ButtonCtrl(pDestSurf, 4, 5);
	}

	// error message dlg...
	if( m_vViewMode > 2 )
	{
		CPoint point(301,161);

		if(m_vViewMode == 3)
			pDestSurf->BltFast( point, m_pDDSurface, &m_arrArea[12]->m_vRect, DDBLTFAST_SRCCOLORKEY );
		else if(m_vViewMode == 4)
			pDestSurf->BltFast( point, m_pDDSurface, &m_arrArea[9]->m_vRect, DDBLTFAST_SRCCOLORKEY );	
		else if(m_vViewMode == 5)
			pDestSurf->BltFast( point, m_pDDSurface, &m_arrArea[12]->m_vRect, DDBLTFAST_SRCCOLORKEY );
	}

	DDSURFACEDESC2 ddsd;
	pDestSurf->Lock();
	ddsd = pDestSurf->GetDescription();
	if( m_vViewMode > 2 ) DrawErrorText(ddsd); //���� �޼��� ���.
	m_water.Draw(ddsd); // ����� ���.
	pDestSurf->Unlock();

	return TRUE;

}

//���� ���ڿ� ���.
void CDialog_AccountLogin::DrawErrorText(DDSURFACEDESC2 &ddsd)
{
	m_ErrorDraw = new CTWFont;

	if (!m_ErrorDraw->CreateFontWithoutPath("soma14", 14, 14))
	{
		delete m_ErrorDraw;
		m_ErrorDraw = NULL;
	}

//	m_pMsgOuter->DrawTexts( pDestSurf, m_vMsgRect, 0xffff, 3);
	if(m_ErrorDraw)
	{
	  m_ErrorDraw->IC_TextOutClip(m_vMsgRect, m_ErrorText, 0xffff, ddsd, 0, 0, -1, 5); //�켮.
	  delete m_ErrorDraw;
	  m_ErrorDraw = NULL;
	}

	SAFE_DELETE(m_ErrorDraw);
}

void CDialog_AccountLogin::GameOpen()
{

}


void CDialog_AccountLogin::SetMessage( CString str )
{
	m_ErrorText = str;
}

BOOL CDialog_AccountLogin::OnLButtonDown(BBDX_MouseInformation *pMouseInfo)
{
	CPoint point;
	
	point = pMouseInfo->GetPos();

	// ����� ȿ��.
	m_water.InputData(point.x, point.y);

	if(m_vViewMode < 3) //����â�� ���� ��� �����츦 �ȸ԰�.
	{
		int size, i;

		size = m_arrBtn.GetSize();

		if(m_vViewMode == 2) i = 4;
		else i = 0;

		m_vSpecCtrl = -1;
		for(i; i < size; i++)
		{
			if(m_arrBtn[i]->m_vRect.PtInRect(CPoint(point-m_ptOffset)))
			{
				m_vSpecCtrl = m_arrBtn[i]->m_vSpec;
				m_vIndexCtrl = m_arrBtn[i]->m_vIndex;
				if(m_vSpecCtrl == BTN_CTRL)
				{
					m_arrBtn[i]->m_vState = BUTTON_DOWN;
				}
				break;
			}
		}


		// ���콺�� Ŭ���� ������ Ŀ���̵�.
		if(m_vViewMode == 0)
		{
			if(m_arrArea[10]->m_vRect.PtInRect(CPoint(point-m_ptOffset))) *m_id_flag = 0;
			if(m_arrArea[11]->m_vRect.PtInRect(CPoint(point-m_ptOffset))) *m_id_flag = 1;
		}
		else if(m_vViewMode == 1)
		{
			if(m_arrArea[0]->m_vRect.PtInRect(CPoint(point-m_ptOffset))) *m_id_flag = 0;
			if(m_arrArea[1]->m_vRect.PtInRect(CPoint(point-m_ptOffset))) *m_id_flag = 1;
			if(m_arrArea[2]->m_vRect.PtInRect(CPoint(point-m_ptOffset))) *m_id_flag = 2;
			if(m_arrArea[3]->m_vRect.PtInRect(CPoint(point-m_ptOffset))) *m_id_flag = 3;
			if(m_arrArea[4]->m_vRect.PtInRect(CPoint(point-m_ptOffset))) *m_id_flag = 4;
			if(m_arrArea[5]->m_vRect.PtInRect(CPoint(point-m_ptOffset))) *m_id_flag = 5;
			if(m_arrArea[6]->m_vRect.PtInRect(CPoint(point-m_ptOffset))) *m_id_flag = 6;
			if(m_arrArea[7]->m_vRect.PtInRect(CPoint(point-m_ptOffset))) *m_id_flag = 7;
			if(m_arrArea[8]->m_vRect.PtInRect(CPoint(point-m_ptOffset))) *m_id_flag = 8;
		}
		else if(m_vViewMode == 2)
		{
			if(m_arrArea[15]->m_vRect.PtInRect(CPoint(point-m_ptOffset))) *m_id_flag = 0;
			if(m_arrArea[16]->m_vRect.PtInRect(CPoint(point-m_ptOffset))) *m_id_flag = 1;
			if(m_arrArea[17]->m_vRect.PtInRect(CPoint(point-m_ptOffset))) *m_id_flag = 2;
		}
	}
	return TRUE;
}

BOOL CDialog_AccountLogin::OnLButtonUp(BBDX_MouseInformation *pMouseInfo)
{
	if(m_vViewMode < 3) //����â�� ���� ��� �����츦 �ȸ԰�.
	{
		CPoint point, off_point;

		point = pMouseInfo->GetPos();
		off_point = point - m_ptOffset;

		if(m_vSpecCtrl == BTN_CTRL)
		{
			MBtnCtrl *btn_ctrl = m_arrBtn[m_vIndexCtrl];
			if(btn_ctrl->m_vRect.PtInRect(off_point))
			{
				if(m_vViewMode == 0)
				{
					switch(m_vIndexCtrl)	
					{
						case 0: m_vOk = 3; break; // Ȯ��.
						case 1: m_vOk = 4; break; // ���.
						case 2: m_vOk = 5; break; // ���ο� ����.
						case 3: m_vOk = 6; break; // �������������.
					}
					btn_ctrl->m_vState = BUTTON_NORMAL;
				}
				else if(m_vViewMode == 1)
				{
					switch(m_vIndexCtrl)	
					{
						case 0: m_vSex = FALSE; //����.
								btn_ctrl->m_vState = BUTTON_DOWN;
								m_arrBtn[1]->m_vState = BUTTON_NORMAL;
							   break; 
						case 1: m_vSex = TRUE; //����.
								btn_ctrl->m_vState = BUTTON_DOWN;
								m_arrBtn[0]->m_vState = BUTTON_NORMAL;
							   break; 
						case 2: m_vOk = 3; btn_ctrl->m_vState = BUTTON_NORMAL; break; // Ȯ��.
						case 3: m_vOk = 4; btn_ctrl->m_vState = BUTTON_NORMAL; break; // ���.
					}
				}
				else if(m_vViewMode == 2)
				{
					switch(m_vIndexCtrl)
					{
						case 4: m_vOk = 7; break; //Ȯ��.
						case 5: m_vOk = 8; break; //���.
					}
					btn_ctrl->m_vState = BUTTON_NORMAL;
				}
			}
		}

		m_vSpecCtrl = -1;
		m_vIndexCtrl = 0;

	}
	return TRUE;
}

BOOL CDialog_AccountLogin::OnMouseMove(BBDX_MouseInformation *pMouseInfo)
{
	CPoint point, off_point;
	int i, size;
	MBtnCtrl *btn_ctrl;

	point = pMouseInfo->GetPos();

	m_water.InputData(point.x, point.y);

	if(m_vViewMode < 3) //����â�� ���� ��� �����츦 �ȸ԰�.
	{
		off_point = point - m_ptOffset;

		if(pMouseInfo->IsLButtonPressing2())
		{
			if(m_vSpecCtrl == BTN_CTRL)
			{
				btn_ctrl = m_arrBtn[m_vIndexCtrl];
				if(btn_ctrl->m_vRect.PtInRect(off_point))
				{
					btn_ctrl->m_vState = BUTTON_DOWN;
				}
				else
				{
					if(btn_ctrl->m_vState == BUTTON_DOWN)
					btn_ctrl->m_vState = BUTTON_NORMAL;
				}
			}
		}
		else
		{
			if(m_vSpecCtrl == -1)
			{
				size = m_arrBtn.GetSize();
				if(m_vViewMode == 2) i = 4;
				else i = 0;
				for(i; i < size; i++)
				{					
					btn_ctrl = m_arrBtn[i];
					if(btn_ctrl->m_vRect.PtInRect(off_point))
					{
						if(btn_ctrl->m_vState != BUTTON_DOWN)
						btn_ctrl->m_vState = BUTTON_FOCUS;
					}
					else
					{
						if(btn_ctrl->m_vState != BUTTON_DOWN)
						btn_ctrl->m_vState = BUTTON_NORMAL;
					}
				}
			}
		}
	}

	return TRUE;
}


void CDialog_AccountLogin::SetViewMode( int view_mode )
{
	if( m_vViewMode == view_mode ) return;

	m_vViewMode = view_mode;

	switch( m_vViewMode )
	{
	case 0:
		InitAccount();
		break;
	case 1:
		InitNewAccount();
		break;
	case 2:
		InitMsg();
		break;
	}
}

void CDialog_AccountLogin::InitAccount()
{
	m_vCurOk = 0;
	m_vOk = 0;
}

void CDialog_AccountLogin::InitNewAccount()
{
	m_vCurOk = 0;
	m_vOk = 0;
}

void CDialog_AccountLogin::InitMsg()
{
	m_vCurOk = 0;
	m_vOk = 0;
}