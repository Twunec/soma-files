// Item_Inv.h: interface for the CItem_Inv class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ITEM_INV_H__C0B77F61_F5A0_11D3_B175_00105A735718__INCLUDED_)
#define AFX_ITEM_INV_H__C0B77F61_F5A0_11D3_B175_00105A735718__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "Soma.h"

//#include "ChildView.h"
#include "DManage/BB_Direct.h"
//#include "DManage/AlphaProcess.h"
//#include "illstruct.h"
//#include "DManage/AlphaProcess.h"
//#include "DManage/BBDX_MouseInformation.h"
//�κ��丮 ĳ���Ϳ� ���� ��ų �����۵�...���⼭ ���ฦ �����ұ??�׷��ʿ�� ������..

#ifndef _INV_SPR_DATA
#define _INV_SPR_DATA
class INV_SPR_DATA
{
public:
	_SPR_HEADER		m_HSpr;
	_SPR_LSP		*m_arrSprData;
	WORD			**m_arrVData;

public:
	INV_SPR_DATA();
	~INV_SPR_DATA();
};
#endif

#ifndef _INV_ANI_DATA
#define _INV_ANI_DATA
class INV_ANI_DATA
{
public:
	_ANI_HEADER		m_HAni;
	_ANI_DATA		m_AniData;

public:
	INV_ANI_DATA();
	~INV_ANI_DATA();
};
#endif

#define INV_KIND_HELMET	0//
#define INV_KIND_BODY   1
#define INV_KIND_ARMOR	3
#define INV_KIND_JEAN	4
#define INV_KIND_BOOT	5
#define INV_KIND_ARMS	6
#define INV_KIND_SHIELD	7

#define INV_KIND_NUM	8

#define  ANI_FRAME_COUNT	6

class CItem_Inv  
{
public:
	void LoadAni(LPCTSTR szAniFileName);
	void Load_spl(LPSTR szFileName, int type, int file_index, int arrindex);// select�� �������� �������� �������� ����..���� �����̽��� ������ �����������Ƿ�..
	void Init(int Sex=0);
	CItem_Inv();
	virtual ~CItem_Inv();

public:	
	void Draw_Man(int tmp_x =0, int tmp_y = 0);
	void Draw_Shield(int tmp_x =0, int tmp_y = 0);
	void Draw_Arm(int tmp_x =0, int tmp_y = 0);
	void Draw_Boot(int tmp_x =0, int tmp_y = 0);
	void Draw_Jean(int tmp_x =0, int tmp_y = 0);
	void Draw_Armor(int tmp_x =0, int tmp_y = 0);
	void Draw_Helmet(int tmp_x =0, int tmp_y = 0);

	void HairDraw(int tmp_x = 0, int tmp_y = 0, int hairstyle = 0, int hairindex = 0);
	void HairStyleDraw(int tmp_x = 0, int tmp_y = 0, int hairindex = 0);

	void Draw(int tmp_x = 0, int tmp_y = 0);
	
	void Change_InvItem(int type, int index,  int PicNum = 0);
	void SetHair(int style,int color);

	//�켮
	int			 m_pre_AniCount;
	int			 m_timegab;
	bool		 m_CharDrawDir;//ĳ���� ���ϸ��̼� ������ �������̸� ��.. �ƴ� ����..
	INV_SPR_DATA			*m_arrInv[INV_KIND_NUM];
	INV_ANI_DATA			m_aniInv;
	int  GetGender() { return m_Gender; }
	int  GetAniCount() { return m_pre_AniCount; }
	void SetAniCount(int count) { m_AniCount = count; }

	bool		 m_bLoginMode;
	char         *m_texName[ANI_FRAME_COUNT]; //ĳ������ ���ϸ��̼� �����Ӽ���ŭ ���ǽ� ����.
	void         CreateTexture();
	void         DrawPrimitiveChar(int x = 0, int y = 0);
	void		 DestoryTexSurface();
	bool         m_bCahrBlend;

	CDDSurface*  m_pTargetSurface[ANI_FRAME_COUNT];
	int			 m_alpha;
	bool         m_alphastate; // true: +  false: -
	void         PutPixelTrans(const WORD* pDest, const WORD* pSrc, int nCopyCount, int alpha, DWORD dwRBBitMask,DWORD dwGBitMask);
	void         BltLSPNormal(CDDSurface *pSurface, int x, int y, RECT* pRC, WORD* data);

	int          m_SkinColor;

	int          m_Draw_Order[10]; //�켮..

	int          m_AniCount;// ���� �ѹ�..
	DWORD        m_dwTick;
	int          m_Gender;
	int          m_MyHair;

	BOOL				m_OK_Flag[11];
};


inline void CItem_Inv::PutPixelTrans(const WORD* pDest, const WORD* pSrc, int nCopyCount, int alpha, DWORD dwRBBitMask,DWORD dwGBitMask)
{
	int nAlphaDest = 32 - alpha;

	__asm // RGB ������ ���� ���..
	{
		mov edi, pDest;
		mov esi, pSrc;
		mov ecx, nCopyCount;
COPY_LOOP:
		push ecx; // ī��Ʈ ����..
		
		mov ebx, 0; // ���� ���� �ʱ�ȭ
		
		mov ecx, [esi]; // Spr Pixel
		
		jecxz DONT_COPY; // ��������Ʈ ������ 0 �̸�... ó�� ����..
		
		mov eax, ecx; // Spr - R B
		and eax, dwRBBitMask;
		mul alpha;
		shr eax, 5;
		and eax, dwRBBitMask;
		add ebx, eax;
		
		mov eax, ecx; // Spr - G
		and eax, dwGBitMask;
		mul alpha;
		shr eax, 5;
		and eax, dwGBitMask;
		add ebx, eax;
		
		mov ecx, [edi]; // Bkg Pixel
		
		mov eax, ecx; // Bkg - R B
		and eax, dwRBBitMask;
		mul nAlphaDest;
		shr eax, 5;
		and eax, dwRBBitMask;
		add ebx, eax;
		
		mov eax, ecx; // Bkg - G
		and eax, dwGBitMask;
		mul nAlphaDest;
		shr eax, 5;
		and eax, dwGBitMask;
		add ebx, eax;
		
		mov [edi], bx;
		
DONT_COPY:
		
		add edi, 2;
		add esi, 2;
		
		pop ecx; // ī��Ʈ ����..
		dec ecx;
		jnz COPY_LOOP;
	}
};

#endif // !defined(AFX_ITEM_INV_H__C0B77F61_F5A0_11D3_B175_00105A735718__INCLUDED_)
