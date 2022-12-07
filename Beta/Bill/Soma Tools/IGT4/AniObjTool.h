// AniObjEx2.h: interface for the CAniObj2 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANIOBJ2_H__A17D6FE0_3883_11D3_9559_00C026EE03FC__INCLUDED_)
#define AFX_ANIOBJ2_H__A17D6FE0_3883_11D3_9559_00C026EE03FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../IGObject/AniObjLSP.h"

class CAniObjTool : public CAniObjLSP
{
public:
	LPDIRECTDRAWSURFACE m_lpDDS;		// ��������Ʈ �۾��� ���ǽ�..
	RGBQUAD* m_pRGBTbls; // 8��Ʈ �÷� �ε��� ���̺�

protected:
	int		m_nSprWorkQt;	// �۾����� ��������Ʈ ����.
	_SPR_TOOL m_SprExs[MAX_SPR]; // ���� Ȯ�� ��������Ʈ�� ���� ��� �Ѵ�.

public:
	void AniDirQtSet(int nDirQt);
	void	AniLoadOldFormat(const char* szFileName);
	void	SprLoadOldFormat(const char* szFileName);
	void	SprLoad(const char* szFileName, int nPF);
	void	SprSave(const char* szFileName);
	void	SprAlloc(int nQt); // ���Ǵ�� ���� ����.. ���̴ϱ� �����ϴٿ�..
	void	AniSave(const char* szFileName);
	void	GetStandLSP(RECT* prc, const WORD** pwStand);
	void	SetColorKey(COLORREF ColorKey);
	int		HitTest(CPoint point, _SPR_TOOL** ppSprEx);
	
	void	AniNew();
	void	SprNew();

	BOOL	AniAdd(); // ���� �߰�
	BOOL	AniInsert(int index); // �߰��� ����
	BOOL	AniDelete(int index); // �߰��� ����.
	
	void	SprExGetData(int index, _SPR_TOOL* pSprData);
	void	SprExSetData(int index, _SPR_TOOL* pSprData);

	CAniObjTool();
	virtual ~CAniObjTool();
};

#endif // !defined(AFX_ANIOBJ2_H__A17D6FE0_3883_11D3_9559_00C026EE03FC__INCLUDED_)
