// Magic.cpp: implementation of the CMagic class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "soma.h"
#include "Magic.h"
#include "MagicRes.h"
#include "MagicManager.h"
#include "DManage/BB_Direct.h"
#include "illstruct.h"
#include "ChildView.h"
#include "MapManager/SM_MapManager.h"
#include "UserManager.h"
#include "User.h"
#include "MainFrm.h"
#include "DirectXMng.h"
#include "DManage/Direct3D.h"
#include "DManage/DirectSound.h"
#include "SoundDef.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CMagicManager* CMagic::pMagicManager = NULL;
DWORD CMagic::dwMagicMoveDelay = 80L;
const double	MoveStep = 80.;

extern CMap<int, int, char *, char *&> g_SoundName;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMagic::CMagic()
{
	INIT_PTR(m_bpMagicRes);
	m_nFrame = 0;
	m_nCurFrame = 0;
	m_dwLastTick = 0L;
	m_nResIndex = 0;
	m_nCurDir = 0;
	m_bTypeFlying = FALSE;
	m_dwLastMoveTick = 0L;
	m_nDstUid = -1;
	m_Pos.x = 0;
	m_Pos.y = 0;
	m_height = 0;
}

CMagic::~CMagic()
{
	ASSERT(pMagicManager);
	if (m_bpMagicRes) pMagicManager->UnloadMagicRes(m_nResIndex);
	m_bpMagicRes = NULL;
	MAGIC_INFO *pMagicInfo;
	for( int i = 0 ; i < m_arrMagicInfo.GetSize(); i++ )
	{
		pMagicInfo = m_arrMagicInfo.GetAt(i);
		SAFE_DELETE( pMagicInfo );
	}
	m_arrMagicInfo.RemoveAll();
	m_lstMagicRoutingCell.RemoveAll();

	MAGIC3D_INFO *p3DMagicInfo;
	int num = m_arr3DMagicInfo.GetSize();
	for( i = 0; i < num; i++ )
	{
		p3DMagicInfo = m_arr3DMagicInfo.GetAt(i);
		SAFE_DELETE( p3DMagicInfo );
	}
	m_arr3DMagicInfo.RemoveAll();

}
void CMagic::SetMagicInfo( int index, int MagicType )
{
	int ArrSize = m_arrMagicInfo.GetSize();
	MAGIC_INFO *pMagicInfo;
	for( int i = 0 ; i < ArrSize ; i++ )
	{
		pMagicInfo = m_arrMagicInfo.GetAt(i);
		if( index == pMagicInfo->m_nMagicIndex )
		{
//			pMagicInfo->m_nMagicIndex = index;
//			pMagicInfo->m_nFrame = m_nFrame;
//			pMagicInfo->m_nCurFrame = 0;
//			pMagicInfo->m_nMagicType = MagicType;
			pMagicInfo->m_bShowContinue = TRUE;
//			pMagicInfo->m_nHeight = m_height;
			return;
		}
		
	}
	pMagicInfo = new MAGIC_INFO; 
	pMagicInfo->m_nMagicIndex = index;
	pMagicInfo->m_nFrame = m_nFrame;
	pMagicInfo->m_nCurFrame = 0;
	pMagicInfo->m_nMagicType = MagicType;
	pMagicInfo->m_bShowContinue = TRUE;
	pMagicInfo->m_nHeight = m_height;
	m_arrMagicInfo.Add( pMagicInfo );
}//dspring_0720a

BOOL CMagic::SetMagicRes(int nIndex, int MagicType)	//���� Resource�� ������//dspring_0720a
{	
	ASSERT(pMagicManager);
	if (pMagicManager->LoadMagicRes(nIndex))
	{
		m_bpMagicRes = pMagicManager->GetIndexedMagic(nIndex);
		m_nFrame = m_bpMagicRes->GetMagicFrameNum();
		m_nResIndex = nIndex;
		SetMagicInfo( nIndex, MagicType );			  //dspring_0720a ������ ������ �ִ� ������ ������ �ִ� ������ �ε����� ���� �ϰ� �Ѵ�.
		return TRUE;
	}
	return FALSE;
}

BOOL CMagic::SetFly3DMagicRes(TCHAR* strName, CPoint startPos, CPoint EndPos, int &nFirstDir, int nMagicType) //��ǥ�� �ʻ��� ��ǥ
{
	Set3DMagic(strName, nMagicType);
	nFirstDir = 0;

	m_bTypeFlying = TRUE;
	RoutePositon(startPos, EndPos);
	if (m_lstMagicRoutingCell.GetCount())	//���ư� ��ΰ� �־�?
	{
		nFirstDir = m_lstMagicRoutingCell.GetHead().m_nDir;
	}
	return TRUE;
}

BOOL CMagic::SetFly3DMagicResEx(int index, CPoint startPos, CPoint EndPos, int &nFirstDir, int nMagicType, int nSeries) //��ǥ�� �ʻ��� ��ǥ
{
	//SetMagicRes(index);//this_fly
	Set3DMagicEx( index, nMagicType);
	nFirstDir = 0;

	m_bTypeFlying = TRUE;
	RoutePositon(startPos, EndPos, nSeries);
	if (m_lstMagicRoutingCell.GetCount())	//���ư� ��ΰ� �־�?
	{
		nFirstDir = m_lstMagicRoutingCell.GetHead().m_nDir;
	}
	return TRUE;
}
BOOL CMagic::SetCycloneMagicRes(int index, CPoint ptSPos, int nMagicType, int nSRadians )
{
	Set3DMagicEx( index, nMagicType );
	RouteCyclone( ptSPos, nSRadians );
	return TRUE;
}
/*
BOOL CMagic::SetViolentRainRes(int index, CPoint ptSPos, int nMagicType, int nSRadians )
{
	Set3DMagicEx( index, nMagicType );
	RouteCyclone( ptSPos, nSRadians );
	return TRUE;
}
void CMagic::RouteRain()
{

}
*/
#include <math.h>
void CMagic::RouteCyclone( CPoint ptSPos, int nSRadians )
{
	double pi = 3.1415926535;
	double radians = pi / 180;
	double radius = 50;
	MR_CELL mrc;

	for(int i = 0; i < 36; i++ )
	{
		mrc.m_nDir = 1;
		mrc.m_ptPos.x = ptSPos.x + (int)(radius*cos( 30*(i+nSRadians)*radians ) );
		mrc.m_ptPos.y = ptSPos.y + (int)(radius*sin( 30*(i+nSRadians)*radians ) )*2/3;
		switch( (i + nSRadians)%12 )
		{
		case 0:
			mrc.m_nDir = 4;
			break;
		case 1: case 2:
			mrc.m_nDir = 5;
			break;
		case 3:
			mrc.m_nDir = 1;
			break;
		case 4: case 5:
			mrc.m_nDir = 9;
			break;
		case 6:
			mrc.m_nDir = 8;
			break;
		case 7: case 8:
			mrc.m_nDir = 10;
			break;
		case 9:
			mrc.m_nDir = 2;
			break;
		case 10: case 11:
			mrc.m_nDir = 6;
			break;
		}
		m_lstMagicRoutingCell.AddTail(mrc);
		radius+=10;
	}

}
//xxxxx
BOOL CMagic::SetDirFly3DMagicResEx(int index, CPoint startPos, int nDir, int nMagicType) //��ǥ�� �ʻ��� ��ǥ
{
	Set3DMagicEx( index, nMagicType);

	m_bTypeFlying = TRUE;
	RouteDirPositon(startPos, nDir);
	return TRUE;
}

void CMagic::Set3DMagic(TCHAR* strName, int nMagicType, int nHeight, int nWidth)
{
	MAGIC3D_INFO *pMagicInfo;
	for( int i = 0 ; i < m_arr3DMagicInfo.GetSize(); i++ )
	{
		pMagicInfo = m_arr3DMagicInfo.GetAt(i);
		if( 0 == strcmp( pMagicInfo->m_strName , strName  ) )
		{
			pMagicInfo->m_bShowContinue = TRUE;
			return;
		}
	}

	int   *pFrame	 = NULL;
	int   *pCurFrame = NULL;
	float *pTu	     = NULL;
	float *pTv       = NULL;
	int	  *pWidth    = NULL;
	int	  *pHeight   = NULL;
	int   *pTime     = NULL;
	int   *pX		 = NULL;
	int   *pY		 = NULL;

	pMagicInfo = new MAGIC3D_INFO;
	pMagicInfo->m_nMagicType = nMagicType;
	pMagicInfo->m_strName = strName;
	pMagicInfo->m_bShowContinue = TRUE;
	CChildView::DirectXMng.m_p3D->D3DCreateTextureSpl(strName);
	__GetMainWnd()->m_wndView.DirectXMng.m_p3D->D3DTexturInfo( strName, &pFrame, &pCurFrame, &pTu, &pTv, &pWidth, &pHeight, &pTime, &pX,&pY );
	pMagicInfo->m_nWidth   = *pWidth;
	pMagicInfo->m_nHeight  = *pHeight;
	m_arr3DMagicInfo.Add(pMagicInfo);

}
void CMagic::Set3DMagicEx(int index, int nMagicType, int nHeight, int nWidth)
{
	CString szTmpFileName;
	const CString szExePath = CDirectDraw::GetExecutionPath();
	szTmpFileName.Format(".\\MagicRes\\mgr_%03d.mrf", index);

	DWORD dwNowTime = GetTickCount();
	MAGIC3D_INFO *pMagicInfo;
	int nArrSize = m_arr3DMagicInfo.GetSize();

	BOOL bSkip = FALSE;

	for( int i = 0 ; i < nArrSize ; i++ )
	{
		pMagicInfo = m_arr3DMagicInfo.GetAt(i);
		if( 0 == strcmp( pMagicInfo->m_strName.GetBuffer(0), szTmpFileName.GetBuffer(0)  ) )
		{
//			pMagicInfo->m_dwTime = dwNowTime;
//			pMagicInfo->m_nCurFrame = 0;
			pMagicInfo->m_bShowContinue = TRUE;
			bSkip = TRUE;
			//return;
		}
		else
		{
			if( dwNowTime >= pMagicInfo->m_dwTime + 10000 )
			{
				CChildView::DirectXMng.m_p3D->DestroySeriesTexture
				( pMagicInfo->m_strName.GetBuffer(0), pMagicInfo->m_nFrame );  
				SAFE_DELETE( pMagicInfo );
				m_arr3DMagicInfo.RemoveAt(i);
				i--; nArrSize--;
			}
		}
	}
	if( bSkip ) return;
/*
	int   *pFrame	 = NULL;
	int   *pCurFrame = NULL;
	float *pTu	     = NULL;
	float *pTv       = NULL;
	int   *pWidth    = NULL;
	int   *pHeight   = NULL;
	int   *pTime     = NULL;
	int   *pX		 = NULL;
	int   *pY		 = NULL;
*/

	CFile file;
	if (!file.Open(szTmpFileName.GetBuffer(0), CFile::modeRead))
	{
		TRACE("���� Resource : %s Load����\n", (LPCTSTR)szTmpFileName.GetBuffer(0));
		return;
	}
	_SPR_HEADER stHSpr;
	UINT nReadCount;
	nReadCount = file.Read(&stHSpr, sizeof(_SPR_HEADER));
	ASSERT(nReadCount==sizeof(_SPR_HEADER));
	file.Close();

	pMagicInfo = new MAGIC3D_INFO;
	if( pMagicInfo == NULL )
		return;
	pMagicInfo->m_nMagicType = nMagicType;
	pMagicInfo->m_strName = szTmpFileName;
	pMagicInfo->m_bShowContinue = TRUE;
//	CChildView::DirectXMng.m_p3D->D3DCreateTextureSpl( szTmpFileName.GetBuffer(0) );
//	__GetMainWnd()->m_wndView.DirectXMng.m_p3D->D3DTexturInfo( szTmpFileName.GetBuffer(0), &pFrame, &pCurFrame, &pTu, &pTv, &pWidth, &pHeight, &pTime , &pX,&pY);
	CChildView::DirectXMng.m_p3D->D3DCreateTextureEx( szTmpFileName.GetBuffer(0) );  
//this_fly
//	ASSERT(pMagicManager);
//	if (pMagicManager->LoadMagicRes(index))
//	{
//		m_bpMagicRes = pMagicManager->GetIndexedMagic(index);
//		m_nFrame = m_bpMagicRes->GetMagicFrameNum();
//		m_nResIndex = index;
//		SetMagicInfo( index, nMagicType );			  //dspring_0720a ������ ������ �ִ� ������ ������ �ִ� ������ �ε����� ���� �ϰ� �Ѵ�.

//	}

//	pMagicInfo->m_nWidth   = *pWidth;
//	pMagicInfo->m_nHeight  = *pHeight;
	pMagicInfo->m_nCurFrame = 0;
	pMagicInfo->m_nFrame = stHSpr.nQt;
//	pMagicInfo->m_nFrame = *pFrame;
	pMagicInfo->m_dwTime = dwNowTime;
	m_arr3DMagicInfo.Add(pMagicInfo);

}

BOOL CMagic::Draw3DMagic( int x, int y, BOOL bNext )
{
	DWORD dwNowTime = GetTickCount();
	MAGIC3D_INFO *pMagicInfo;
	int num = m_arr3DMagicInfo.GetSize();
	for(int i = 0; i < num; i++ )
	{
		pMagicInfo = m_arr3DMagicInfo.GetAt(i);
		if( bNext )
		{
			if( pMagicInfo->m_nMagicType == MAGIC_TYPE_DOWN ) continue;
			if( pMagicInfo->m_bShowContinue == FALSE ) continue;
			if( __GetMainWnd()->m_wndView.DirectXMng.m_p3D->D3DRenderEx( pMagicInfo->m_strName.GetBuffer(0) , x, y, pMagicInfo->m_nCurFrame) )
			{
				pMagicInfo->m_nCurFrame = 0;
				pMagicInfo->m_bShowContinue = FALSE;
			}
		}
		else
		{
			if( pMagicInfo->m_nMagicType == MAGIC_TYPE_UP || pMagicInfo->m_nMagicType == MAGIC_TYPE_LOOP
				|| pMagicInfo->m_nMagicType== MAGIC_TYPE_NOTALPHA_UP) continue;
			if( pMagicInfo->m_bShowContinue == FALSE ) continue;
			if( __GetMainWnd()->m_wndView.DirectXMng.m_p3D->D3DRenderEx( pMagicInfo->m_strName.GetBuffer(0) , x, y, pMagicInfo->m_nCurFrame ) )
			{
				pMagicInfo->m_nCurFrame = 0;
				pMagicInfo->m_bShowContinue = FALSE;
			}
		}
		if( 100 <= dwNowTime - pMagicInfo->m_dwTime )
		{
			pMagicInfo->m_nCurFrame++; 
			pMagicInfo->m_dwTime = dwNowTime;
		}
	}
	return TRUE;
}

BOOL CMagic::DrawFlying3DMagic(int nDir, int x, int y)
{
	MAGIC3D_INFO *pMagicInfo;
	int num = m_arr3DMagicInfo.GetSize();
	for(int i = 0; i < num; i++ )
	{
		pMagicInfo = m_arr3DMagicInfo.GetAt(i);

		if (nDir!=m_nCurDir)
		{
//			*pCurFrame = DirStartFrame(nDir, *pFrame);
//			pMagicInfo->m_nCurFrame = DirStartFrame(nDir, *pFrame);
			m_nCurDir = nDir;
		}

//		if ( *pFrame % 8 != 0 )
		if ( pMagicInfo->m_nFrame  % 8 != 0 )
		{
//			if( *pFrame >= pMagicInfo->m_nCurFrame )
			if( pMagicInfo->m_nFrame <= pMagicInfo->m_nCurFrame )
				pMagicInfo->m_nCurFrame = 0;
		}
//		else if ((*pCurFrame)%(*pFrame/8)==0) 
		else if ((pMagicInfo->m_nCurFrame)%(pMagicInfo->m_nFrame/8)==0) 
		{
//			*pCurFrame = DirStartFrame(m_nCurDir, *pFrame);
//			pMagicInfo->m_nCurFrame = DirStartFrame(m_nCurDir, *pFrame);
			pMagicInfo->m_nCurFrame = DirStartFrame(m_nCurDir, pMagicInfo->m_nFrame);
		}
		//�׸��� Frame ��ȭ�ð��ΰ�?
		if (GetTickCount()-m_dwLastTick>CMagicRes::dwMagicDelay)
		{
			m_dwLastTick = GetTickCount();
			pMagicInfo->m_nCurFrame++;
		}
		//���ư��� ���� ��ġ�� �ٲ� �ð��ΰ�?
		if (GetTickCount()-m_dwLastMoveTick>dwMagicMoveDelay)
		{
			m_dwLastMoveTick = GetTickCount();
			return TRUE;
		}
	}

//��ǥ�� �ʻ��� ��ǥ�̹Ƿ� Map�� Offset�� ���־����
	CPoint ptMapOffset = CChildView::MapManager.GetMapStartPos();
	x -= ptMapOffset.x;
	y -= ptMapOffset.y;// + 100;
	//�׸���� ȭ����� ��ġ���
	Draw3DMagic( x, y, TRUE );//this_fly
	//DrawMagic( CChildView::DirectXMng.m_pDrawSurface, x, y, 1, TRUE);  
		  return FALSE;
}
//�׸��Ⱑ ��� ������ true �� ������
BOOL CMagic::DrawFlying3DMagic()
{
	if (m_lstMagicRoutingCell.GetCount()==0) return TRUE;

	MR_CELL mrc = m_lstMagicRoutingCell.GetHead();

	if (DrawFlying3DMagic(mrc.m_nDir, mrc.m_ptPos.x, mrc.m_ptPos.y))
	{
		//��ǥ�� �̵����Ѿ� �� ���
		m_lstMagicRoutingCell.RemoveHead();
	}

	if (m_lstMagicRoutingCell.GetCount()==0)
	{
		//���� ���� ��� ������ �´� ȿ��,
		if (m_nDstUid!=-1)
		{		
			// ������ �Ѿ� ������..���⼭ ������ ���Ѿ� �ǰڱ�..����..
			//CUser *pDstUser = CChildView::UserManager.GetUserWithUid(m_nDstUid);
			//if (pDstUser) pDstUser->BeatedDir();
			//dspring_0802_3dxx_start
			int num;
			static int nSoundManIndex = -1;
			static int nSoundWomanIndex = -1;
			static int nSoundMonIndex = -1;
			CUser *pDstUser = CChildView::UserManager.GetUserWithUid(m_nDstUid);
			if( pDstUser == NULL ) return TRUE;
//			num = pDstUser->m_arrMagicName.GetSize();
			num = pDstUser->m_arrFlyEndMagic.GetSize();
			FLY_END_MAGIC stFlyEndMagic;
			for( int i = 0; i < num; i++ )
			{
				if( pDstUser->m_AnimationIndex != CUser::UM_Die ) 
					pDstUser->SetMotion(CUser::UM_Beated);
				stFlyEndMagic = pDstUser->m_arrFlyEndMagic.GetAt(i); 
				if( stFlyEndMagic.m_nPoisonKind )
					pDstUser->m_nPoisonKind = stFlyEndMagic.m_nPoisonKind; 
//				CChildView::UserManager.Set3DMagicEx(m_nDstUid, stFlyEndMagic.m_nMagicIndex , stFlyEndMagic.m_bType );
				CChildView::UserManager.SetMagic(m_nDstUid, stFlyEndMagic.m_nMagicIndex , MAGIC_TYPE_UP);//this_fly

				CPoint ptSoundPos = pDstUser->GetPosition() - CChildView::MapManager.GetMapStartPos();

				char *value;
				int key = SOUND_MAGIC+(stFlyEndMagic.m_nTableNum-1)*3+2;
				if(g_SoundName.Lookup(key, value))
				{
					CChildView::DirectXMng.m_pDirectSound->SoundPlay(value, key, FALSE, ptSoundPos);
				}

				if(pDstUser->m_nType < 10) // ����
				{
					if(pDstUser->m_Gender == 1) // ����
					{
						if(g_SoundName.Lookup(SOUND_SCREAM1, value))
							if(!CChildView::DirectXMng.m_pDirectSound->IsSoundPlaying(SOUND_SCREAM1, nSoundManIndex))
							{
								nSoundManIndex = CChildView::DirectXMng.m_pDirectSound->SoundPlay(value, SOUND_SCREAM1, FALSE, ptSoundPos);
							}
					}
					else
					{
						if(g_SoundName.Lookup(SOUND_SCREAM2, value))
							if(!CChildView::DirectXMng.m_pDirectSound->IsSoundPlaying(SOUND_SCREAM2, nSoundWomanIndex))
							{
								nSoundWomanIndex = CChildView::DirectXMng.m_pDirectSound->SoundPlay(value, SOUND_SCREAM2, FALSE, ptSoundPos);
							}
					}
				}
				else // NPC
				{
					key = SOUND_MONSTER+(pDstUser->m_nType-10-1)*4+3;
					if(g_SoundName.Lookup(key, value))
						if(!CChildView::DirectXMng.m_pDirectSound->IsSoundPlaying(key, nSoundMonIndex))
						{
							nSoundMonIndex = CChildView::DirectXMng.m_pDirectSound->SoundPlay(value, key, FALSE, ptSoundPos);
						}
				}
			}
			pDstUser->m_arrFlyEndMagic.RemoveAll();  
//			pDstUser->m_arrMagicName.RemoveAll();//�ѹ� ����� ������ ���ؼ��� ���Ÿ� ���ش�.  
			//dspring_0802_3dxx_end
			m_nDstUid = -1;
		}
		return TRUE;	//�� �Դ�. (������ ���� ��ġ�� ��������)
	}
	return FALSE;
}

//dspring_0731_3dxx_end

BOOL CMagic::DrawMagic(CDDSurface *pSurface)
{
	CPoint tmp = CChildView::MapManager.GetMapStartPos();

	int x = m_Pos.x-tmp.x;
	int y = m_Pos.y-tmp.y;

	if(DrawMagic(pSurface, x, y))
	{
		return TRUE;
	}
	return FALSE;
}


//CUser������ �󿡼� �׸��Ƿ� Map�� Offset�� ����Ǿ��ִ�.
BOOL CMagic::DrawMagic(CDDSurface *pSurface, int x, int y, int Alpha, BOOL bNext)
{

	int dY = y;
	CMagicRes *pMagicRes = NULL;
	MAGIC_INFO *pMagicInfo;
	int ArrSize = m_arrMagicInfo.GetSize();
	for( int i = 0 ; i < ArrSize ; i++ )							  //�迭�� ��� ���� ������
	{
		int index = 0;
		pMagicInfo = m_arrMagicInfo.GetAt(i);
		index = pMagicInfo->m_nMagicIndex; 
		if( bNext )
		{	
			pMagicRes = pMagicManager->GetIndexedMagic(index);		  //�迭�� Res�����͸� ���ͼ� 
			if( pMagicRes )
			{
				y += pMagicInfo->m_nHeight;// ���������ش�..�ӽ� ���߿��� ĳ������ Ű���� ������ �ؼ� �ؾߵǰڱ�... 
				if( !pMagicInfo->m_bShowContinue ) continue;
				if( pMagicInfo->m_nMagicType == MAGIC_TYPE_DOWN ) continue;
				pMagicRes->DrawMagic(pSurface, x, y, pMagicInfo->m_nCurFrame, Alpha); //������ ������ �׷��ش�......
				
				CPoint pt(x,y);
				LIGHT_INFO LI;
				LI.m_kind = 1;
				LI.m_pt = pt;
				CChildView::m_ptLightPos.Add(LI);    
//				CChildView::m_ptLightPos.Add(pt);    

				y = dY;
				if (GetTickCount()-pMagicInfo->m_dwLastTick>CMagicRes::dwMagicDelay)
	//				if (GetTickCount()-m_dwLastTick>CMagicRes::dwMagicDelay)
				{
					pMagicInfo->m_dwLastTick = GetTickCount();
					pMagicInfo->m_nCurFrame++;
					pMagicInfo->m_nCurFrame %= pMagicInfo->m_nFrame ;
					if(pMagicInfo->m_nMagicType == MAGIC_TYPE_LOOP)
					{
		//				if (m_nCurFrame==0) 
		//					m_nCurFrame = DirStartFrame(m_nCurDir, m_nFrame);
					}
					else
						if (pMagicInfo->m_nCurFrame == 0 ) 
						{
							//return TRUE;
							pMagicInfo->m_bShowContinue = FALSE; 
							//pMagicManager->Release(i); 
							//SAFE_DELETE( pMagicRes );//�� �̰� ������ ����ų��...������ 
							//pMagicManager->GetMagicResArr()->SetAt(i,NULL);
							//pMagicManager->UnloadMagicRes(i);
							//
						}
				}
			}//if( pMagicRes )
		}
		else
		{
			pMagicRes = pMagicManager->GetIndexedMagic(index);		  //�迭�� Res�����͸� ���ͼ� 
			if( pMagicRes )
			{
				y += pMagicInfo->m_nHeight;// ���������ش�..�ӽ� ���߿��� ĳ������ Ű���� ������ �ؼ� �ؾߵǰڱ�... 
				if( !pMagicInfo->m_bShowContinue ) continue;
				if( pMagicInfo->m_nMagicType == MAGIC_TYPE_UP || pMagicInfo->m_nMagicType == MAGIC_TYPE_LOOP
					|| pMagicInfo->m_nMagicType== MAGIC_TYPE_NOTALPHA_UP) continue;
				pMagicRes->DrawMagic(pSurface, x, y, pMagicInfo->m_nCurFrame, Alpha); //������ ������ �׷��ش�......
				CPoint pt(x,y);
				LIGHT_INFO LI;
				LI.m_kind = 1;
				LI.m_pt = pt;
				CChildView::m_ptLightPos.Add(LI);    
//				CChildView::m_ptLightPos.Add(pt);    
				y = dY;
				if (GetTickCount()-pMagicInfo->m_dwLastTick>CMagicRes::dwMagicDelay)
	//				if (GetTickCount()-m_dwLastTick>CMagicRes::dwMagicDelay)
				{
					pMagicInfo->m_dwLastTick = GetTickCount();
					pMagicInfo->m_nCurFrame++;
					pMagicInfo->m_nCurFrame %= pMagicInfo->m_nFrame ;
					if (pMagicInfo->m_nCurFrame == 0 ) 
					{
						pMagicInfo->m_bShowContinue = FALSE; 
					}
				}
			}//if( pMagicRes )

		}
	}//dspring_0718_end											  //������ �������ҽ��� �������� �𸣴� �װſ� ���� ����Ͽ� ���α׷��� �ؾ� �ڱ�	
	return FALSE;
}

BOOL CMagic::DrawFlyingMagic(CDDSurface *pSurface, int nDir, int x, int y)
{
	if (m_bpMagicRes)
	{
		if (nDir!=m_nCurDir)
		{
			m_nCurFrame = DirStartFrame(nDir, m_nFrame);
			m_nCurDir = nDir;
		}

//��ǥ�� �ʻ��� ��ǥ�̹Ƿ� Map�� Offset�� ���־����
		CPoint ptMapOffset = CChildView::MapManager.GetMapStartPos();
		x -= ptMapOffset.x;
		y -= ptMapOffset.y;

		//�׸���� ȭ����� ��ġ���
		m_bpMagicRes->DrawMagic(pSurface, x, y, m_nCurFrame);
		CPoint pt(x,y);
		LIGHT_INFO LI;
		LI.m_kind = 1;
		LI.m_pt = pt;
		CChildView::m_ptLightPos.Add(LI);    
//		CChildView::m_ptLightPos.Add(pt);    

		//�׸��� Frame ��ȭ�ð��ΰ�?
		if (GetTickCount()-m_dwLastTick>CMagicRes::dwMagicDelay)
		{
			m_dwLastTick = GetTickCount();
			m_nCurFrame ++;
			if( m_nFrame%8 == 0 )
			{
				if (m_nCurFrame%(m_nFrame/8)==0) 
				{
					m_nCurFrame = DirStartFrame(m_nCurDir, m_nFrame);
				}
			}
			else if( m_nFrame <= m_nCurFrame ) m_nCurFrame = 0;
		}

		//���ư��� ���� ��ġ�� �ٲ� �ð��ΰ�?
		if (GetTickCount()-m_dwLastMoveTick>dwMagicMoveDelay)
		{
			m_dwLastMoveTick = GetTickCount();
			return TRUE;
		}
	}
	return FALSE;
}

//�׸��Ⱑ ��� ������ true �� ������
BOOL CMagic::DrawFlyingMagic(CDDSurface *pSurface)
{
	if (m_lstMagicRoutingCell.GetCount()==0) return TRUE;

	MR_CELL mrc = m_lstMagicRoutingCell.GetHead();
	if (DrawFlyingMagic(pSurface, mrc.m_nDir, mrc.m_ptPos.x, mrc.m_ptPos.y))
	{
		//��ǥ�� �̵����Ѿ� �� ���
		m_lstMagicRoutingCell.RemoveHead();
	}

	if (m_lstMagicRoutingCell.GetCount()==0) 
	{
		//���� ���� ��� ������ �´� ȿ��,
		if (m_nDstUid!=-1)
		{		
			// ������ �Ѿ� ������..���⼭ ������ ���Ѿ� �ǰڱ�..����..
			//CUser *pDstUser = CChildView::UserManager.GetUserWithUid(m_nDstUid);
			//if (pDstUser) pDstUser->BeatedDir();
			//dspring_0802_3dxx_start
			int num;
			static int nSoundManIndex = -1;
			static int nSoundWomanIndex = -1;
			static int nSoundMonIndex = -1;
			CUser *pDstUser = CChildView::UserManager.GetUserWithUid(m_nDstUid);
			if( pDstUser == NULL ) return TRUE;
//			num = pDstUser->m_arrMagicName.GetSize();
			num = pDstUser->m_arrFlyEndMagic.GetSize();
			FLY_END_MAGIC stFlyEndMagic;
			for( int i = 0; i < num; i++ )
			{
				if( pDstUser->m_AnimationIndex != CUser::UM_Die ) 
					pDstUser->SetMotion(CUser::UM_Beated);
				stFlyEndMagic = pDstUser->m_arrFlyEndMagic.GetAt(i); 
				if( stFlyEndMagic.m_nPoisonKind )
					pDstUser->m_nPoisonKind = stFlyEndMagic.m_nPoisonKind; 
//				CChildView::UserManager.Set3DMagicEx(m_nDstUid, stFlyEndMagic.m_nMagicIndex , stFlyEndMagic.m_bType );
				CChildView::UserManager.SetMagic(m_nDstUid, stFlyEndMagic.m_nMagicIndex , MAGIC_TYPE_UP);//this_fly

				CPoint ptSoundPos = pDstUser->GetPosition() - CChildView::MapManager.GetMapStartPos();

				char *value;
				int key = SOUND_MAGIC+(stFlyEndMagic.m_nTableNum-1)*3+2;
				if(g_SoundName.Lookup(key, value))
				{
					CChildView::DirectXMng.m_pDirectSound->SoundPlay(value, key, FALSE, ptSoundPos);
				}

				if(pDstUser->m_nType < 10) // ����
				{
					if(pDstUser->m_Gender == 1) // ����
					{
						if(g_SoundName.Lookup(SOUND_SCREAM1, value))
							if(!CChildView::DirectXMng.m_pDirectSound->IsSoundPlaying(SOUND_SCREAM1, nSoundManIndex))
							{
								nSoundManIndex = CChildView::DirectXMng.m_pDirectSound->SoundPlay(value, SOUND_SCREAM1, FALSE, ptSoundPos);
							}
					}
					else
					{
						if(g_SoundName.Lookup(SOUND_SCREAM2, value))
							if(!CChildView::DirectXMng.m_pDirectSound->IsSoundPlaying(SOUND_SCREAM2, nSoundWomanIndex))
							{
								nSoundWomanIndex = CChildView::DirectXMng.m_pDirectSound->SoundPlay(value, SOUND_SCREAM2, FALSE, ptSoundPos);
							}
					}
				}
				else // NPC
				{
					key = SOUND_MONSTER+(pDstUser->m_nType-10-1)*4+3;
					if(g_SoundName.Lookup(key, value))
						if(!CChildView::DirectXMng.m_pDirectSound->IsSoundPlaying(key, nSoundMonIndex))
						{
							nSoundMonIndex = CChildView::DirectXMng.m_pDirectSound->SoundPlay(value, key, FALSE, ptSoundPos);
						}
				}
			}
			pDstUser->m_arrFlyEndMagic.RemoveAll();  
//			pDstUser->m_arrMagicName.RemoveAll();//�ѹ� ����� ������ ���ؼ��� ���Ÿ� ���ش�.  
			//dspring_0802_3dxx_end
			m_nDstUid = -1;
		}
		return TRUE;	//�� �Դ�. (������ ���� ��ġ�� ��������)
/*
		//���� ���� ��� ������ �´� ȿ��,
		if (m_nDstUid!=-1)
		{		
			// ������ �Ѿ� ������..���⼭ ������ ���Ѿ� �ǰڱ�..����..
			//CUser *pDstUser = CChildView::UserManager.GetUserWithUid(m_nDstUid);
			//if (pDstUser) pDstUser->BeatedDir();
			CUser *pDstUser = CChildView::UserManager.GetUserWithUid(m_nDstUid);
			for( int i = 0; i < pDstUser->m_nMagicIndex.GetSize(); i++ )
			{
				int nMagicIndex = pDstUser->m_nMagicIndex.GetAt( i ); 
				CChildView::UserManager.SetMagic(m_nDstUid, nMagicIndex, MAGIC_TYPE_UP);//dspring_0722
			}
			pDstUser->m_nMagicIndex.RemoveAll();//�ѹ� ����� ������ ���ؼ��� ���Ÿ� ���ش�.  
			m_nDstUid = -1;
		}
		return TRUE;	//�� �Դ�. (������ ���� ��ġ�� ��������)
*/
	}
	return FALSE;
}

int CMagic::DirStartFrame(int nDir, int nResMaxFrame)	//������ ������ ó�� Frame Index ���ϱ�
{
	if(nResMaxFrame%8!=0) return 0;//8������ ���� ��ü�̾����
//	ASSERT(nResMaxFrame%8==0);//8������ ���� ��ü�̾����
	int DirMaxFrame = nResMaxFrame/8;
	int nStartFrame = 0;
	switch(nDir)
	{
	case DIR_DOWN:				nStartFrame = 0;				break;
	case DIR_LEFT | DIR_DOWN:	nStartFrame = DirMaxFrame;		break;
	case DIR_LEFT:				nStartFrame = DirMaxFrame*2;	break;
	case DIR_LEFT | DIR_UP:		nStartFrame = DirMaxFrame*3;	break;
	case DIR_UP:				nStartFrame = DirMaxFrame*4;	break;
	case DIR_RIGHT | DIR_UP:	nStartFrame = DirMaxFrame*5;	break;
	case DIR_RIGHT:				nStartFrame = DirMaxFrame*6;	break;
	case DIR_RIGHT | DIR_DOWN:	nStartFrame = DirMaxFrame*7;	break;
	}
	return nStartFrame;
}
/************************************************************************************************
* NAME: SetFlyMagicRes(int nIndex, CPoint startPos, CPoint EndPos, int &nFirstDir)
* DESC: �ش� ���� �ε����� ���Ͽ��� �ε����ְ� �������� ������������ �̵���θ�(RoutePosition) �����ָ�
*       ���ư� ������ �������ش�.
*************************************************************************************************/
BOOL CMagic::SetFlyMagicRes(int nIndex, CPoint startPos, CPoint EndPos, int &nFirstDir,int nSeries) //��ǥ�� �ʻ��� ��ǥ
{
	BOOL bSetOk = SetMagicRes(nIndex);
	nFirstDir = 0;
	if (bSetOk)
	{
		//if (m_nFrame>=8 && (m_nFrame%8)==0) //�⺻ ���� �˻�(������ ������ �� �� �ִ°�)//this_fly
//		if (1)// �ӽ÷�..�׽�Ʈ..���߿� ������ ��������� �ڱ�..���󰡴� �������� �ƴ�����?
		{
			m_bTypeFlying = TRUE;
			RoutePositon(startPos, EndPos, nSeries);
			//RoutePositon(startPos, EndPos);
			if (m_lstMagicRoutingCell.GetCount())	//���ư� ��ΰ� �־�?
			{
				nFirstDir = m_lstMagicRoutingCell.GetHead().m_nDir;
			}
			return TRUE;
		}
	}

	if (m_bpMagicRes) pMagicManager->UnloadMagicRes(m_nResIndex); //Load�� ���������Ƿ� �ǰ�
	m_bpMagicRes = NULL;
	return FALSE;
}
/************************************************************************************************
* NAME: RoutePositon(CPoint ptStart, CPoint ptEnd)
* DESC:  �������� ������������ �̵���θ� �����ش�.
*************************************************************************************************/

void CMagic::RoutePositon(CPoint ptStart, CPoint ptEnd, int nSeries)
{
	m_lstMagicRoutingCell.RemoveAll();
	//������ ���� ����
	int nDir = 0;

	int deltax = ptEnd.x - ptStart.x;
	int deltay = ptEnd.y - ptStart.y;

	if (deltax==0) 
	{
		if (ptEnd.y>ptStart.y) nDir = DIR_DOWN;
		else nDir = DIR_UP;
	}
	else
	{
		double lean = (double)abs(deltay)/abs(deltax);

		if (ptEnd.y>ptStart.y) nDir |= DIR_DOWN;			//X,Y���� ���� ���� ����
		else if (ptEnd.y < ptStart.y) nDir |= DIR_UP;
		if (ptEnd.x>ptStart.x) nDir |= DIR_RIGHT;
		else if (ptEnd.x < ptStart.x) nDir |= DIR_LEFT;

		if (lean<.5) nDir &= ~(DIR_UP|DIR_DOWN);			//����� �Ǵ��� 8���� �缳��
		else if (lean>2.) nDir &= ~(DIR_LEFT|DIR_RIGHT);
	}

	int	totalDistance = abs(deltax) + abs(deltay);
	int nStep = int(totalDistance / MoveStep + .5);

	if (nStep==0) return;

	MR_CELL mrc;
	for (int i=0; i<=nStep; i++)
	{
		mrc.m_nDir = nDir;
		mrc.m_ptPos.x = ptStart.x + deltax *i/nStep;
		mrc.m_ptPos.y = ptStart.y + deltay *i/nStep;
		m_lstMagicRoutingCell.AddTail(mrc);
	}
	for( i = 0; i < nSeries; i++ )
	{
		mrc.m_nDir = nDir;
		mrc.m_ptPos.x = ptStart.x;
		mrc.m_ptPos.y = ptStart.y;
		m_lstMagicRoutingCell.AddHead(mrc);
	}
}
//xxxxx

void CMagic::RouteDirPositon(CPoint ptStart, int nDir)
{
	int deltax = 0;
	int deltay = 0;
	m_lstMagicRoutingCell.RemoveAll();
	//������ ���� ����
	switch( nDir )
	{
	case 3://DIR_LEFT
		deltax = - 30; deltay =	0;
		nDir = 1;
		break;
	case 7://DIR_RIGHT
		deltax =   30; deltay =	0;
		nDir = 2;
		break;
	case 5://DIR_UP
		deltax =	0; deltay =  -20;
		nDir = 4;
		break;
	case 1://DIR_DOWN
		deltax =	0; deltay =   20;
		nDir = 8;
		break;
	case 4://DIR_LEFT + DIR_UP
		deltax =  -25; deltay =  -15;
		nDir = 5;
		break;
	case 2://DIR_LEFT + DIR_DOWN
		deltax =  -25; deltay =   15;
		nDir = 9;
		break;
	case 6://DIR_RIGHT + DIR_UP
		deltax =   25; deltay =  -15;
		nDir = 6;
		break;
	case 0://DIR_RIGHT + DIR_DOWN
		deltax =   25; deltay =   15;
		nDir = 10;
		break;
	}

	MR_CELL mrc;
	for (int i=0; i<10; i++)
	{
		mrc.m_nDir = nDir;
		mrc.m_ptPos.x = ptStart.x + deltax * i;
		mrc.m_ptPos.y = ptStart.y + deltay * i;
		m_lstMagicRoutingCell.AddTail(mrc);
	}
}

//���� ���� ��� (������ ������)
void CMagic::SetLastBeatEffect(int nDstUid)
{
	m_nDstUid = nDstUid;
}