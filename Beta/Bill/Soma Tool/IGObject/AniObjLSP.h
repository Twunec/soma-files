// AniObj.h: interface for the CAniObjLSP class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ANIOBJLSP_H_INCLUDED_)
#define AFX_ANIOBJLSP_H_INCLUDED_

#include "AniObj.h"

class CAniObjLSP : public CAniObj
{
public:
	_SPR_HEADER			m_HSpr;
protected:
	_SPR_LSP*	m_pSprs[MAX_SPR];

	virtual void	SprAlloc(int nQt);
	BOOL	Convert8PixelTo16Pixel(BYTE* p8Pixels, WORD *p16Pixels, RGBQUAD* pRGBTbls, int nQt); // 8��Ʈ �ε��� �ȼ��� 16��Ʈ �ȼ��� �ٲ۴�.
	WORD	RGB16(WORD r, WORD g, WORD b) { return ((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3); } // 565 �����϶��� �ζ��� �Լ��� ����

public:
	void		SprRelease(); // ��������Ʈ ������ ������
	COLORREF	SrcCKGet() { return m_HSpr.SrcCK; } // �ҽ� �÷�Ű ��������

	void	Decode2_555(_SPR_LSP* pSpr); // 565 LSP �� 555 LSP �� �ٲپ��ش�..
	void	Decode2_565(_SPR_LSP* pSpr); // 555 LSP �� 565 LSP �� �ٲپ��ش�..
	BOOL	SprGet(int index, const _SPR_LSP** ppSpr); // ��������Ʈ ������ ������ ��������
	int		SprGetAnimated(const _SPR_LSP** ppSpr, int nCtrl = 0); // ���ϸ��̼� �ǰ� �ִ� ��������Ʈ�� �����´�.
	virtual void SprLoad(const char* szFileName, int nPF); // ��������Ʈ ���� �ҷ�����
	
	CAniObjLSP();
	virtual ~CAniObjLSP();
};

#endif // !defined(AFX_ANIOBJLSP_H_INCLUDED_)
