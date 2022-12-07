#ifndef _ILLSTRUCT_H
#define _ILLSTRUCT_H

const unsigned long	DIR_LEFT =	0X00000001;
const unsigned long	DIR_RIGHT = 0X00000002;
const unsigned long	DIR_UP =	0X00000004;
const unsigned long	DIR_DOWN =	0X00000008;

#define MAX_RES_COUNT		19
#define MAX_ANI_COUNT		19

#endif
/**
#ifndef _ILLSTRUCT_H
#define _ILLSTRUCT_H

const int MAX_FRM = 32;		// ���ϸ��̼Ǵ� �ִ� 32 �� ������
const int PF_555 = 555;
const int PF_565 = 565;
const int MAX_PART = 10; 	// �ִ� 10 ���� ��Ʈ ��������Ʈ ó��

const unsigned long	DIR_LEFT =	0X00000001;
const unsigned long	DIR_RIGHT = 0X00000002;
const unsigned long	DIR_UP =	0X00000004;
const unsigned long	DIR_DOWN =	0X00000008;


typedef struct _ANI_HEADER
{
	char	szID[4];		// 'A' 'N' 'I' ���� ����(1,8) ���
	char	szRemark[64];	// �ּ�
	int		nDirQt;			// ����
	int		nQt;			// Animation ����
	_ANI_HEADER const & operator = (_ANI_HEADER const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _ANI_HEADER;

typedef struct _ANI_DATA // 8���� ���ϸ��̼� ������
{
	char		szName[32];	// ���ϸ��̼� �̸�
	int			nFlag;		// ���ϸ��̼� �÷���..
	float		fSpd;		// ���ǵ�.. ������ Frame/Sec
	short int 	nMaxFrm;	// ���⺰ �ִ� ������
	short int*	pnFrms;		// ���⺰ ������ �迭
} _ANI_DATA;

typedef struct _SPR_HEADER
{
	char	szID[4];		// 'SPLN' ���� LSP Sprite | 'SPLC' Ȯ��� LSP Sprite || 'SPRN' ���� Sprite
	char	szRemark[64];	// �ּ�
	char	szBMPFN[64];	// ��Ʈ�� ���� �̸� - �����͸� ���� ������ �� ����.
	int		nWidth;			// �ʺ�
	int		nHeight; 		// ����
	COLORREF SrcCK;			// �ҽ� �÷�Ű
	int		nQt;			// ��������Ʈ ��
	_SPR_HEADER const & operator = (_SPR_HEADER const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _SPR_HEADER;
/*
typedef struct _SPR_NORMAL
{
	POINT	ptCV;			// ������
	POINT	ptCSH;			// ������ - �׸���
	POINT	ptCFX;			// ������ - ���� ȿ��
	RECT	rcV;			// ĳ���� ���� - Part1
	RECT	rcSH;			// �׸��� ����
	RECT	rcFX;			// ���� ȿ�� ����
	_SPR_NORMAL const & operator = (_SPR_NORMAL const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _SPR_NORMAL;
*/

/**
typedef struct _SPR_TOOL
{
	RECT	rcV;			// ĳ���� ���� - ��Ʈ 1
	POINT	ptCV;			// ������ - ��Ʈ 1.
	_SPR_TOOL const & operator = (_SPR_TOOL const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}

} _SPR_NORMAL;

typedef struct _SPR_LSP
{
	RECT	rcV;	// ���̴� ���� - Clipping �� ����
	int 	nLine;	// LSP �ټ�
	int		nDataSize;	// LSP Data Size
	WORD*	pwV;		// LSP Data
	_SPR_LSP const & operator = (_SPR_LSP const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _SPR_LSP;




#endif
*/