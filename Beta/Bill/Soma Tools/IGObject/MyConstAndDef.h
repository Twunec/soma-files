#if !defined(AFX_MYCONSTANDDEF_H_INCLUDED_)
#define AFX_MYCONSTANDDEF_H_INCLUDED_

// ��ũ��Ʈ �� �޽���
// ��� ĳ���� �����ʹ� ��ũ���Ϳ��� ĳ���� ��ȣ�� ��ġ�� ���� �ִ�.
const int SCT_TALK = 1000; // wParam ���ڿ� ������ lParam - LOWORD,F1:ĳ���� ��ȣ|HIWORD:�÷��� ... F2:0:ǳ��,1:��ȭâ,2:�޽���â,4:��ũ�� ����,8:�ʿ�����,16:������ĳ���Ϳ� ����

const int SCT_IMAGE_OUTPUT = 2000; // ��Ʈ�� �̹��� ��� wParam - ���� �̸� ���ڿ� ������, Pt,lParam - POINT �� ������
const int SCT_AVI_PLAY = 2100; // ������ ���� ��� wParam - ���� �̸� ���ڿ� ������, Rect,lParam - RECT�� ������

const int SCT_GAME_PAUSE = 2200; // ���� ��� ���� F1,wParam - 0:�ð�,1:���콺Ŭ��,2:����������, Time,lParam - �ð��� ��� DWORD ���� mSec
const int SCT_GAME_RESUME = 2300; // ���� ��� ���� ����. ���� ����

const int SCT_LOAD = 3000; // ��ũ��Ʈ �ε� wParam - ���� �̸� ���ڿ� ������
const int SCT_PAUSE = 3100; // ��ũ��Ʈ ��� ���� F1,wParam - 0:�ð�,1:���콺Ŭ��,2:����������, Time,lParam - �ð��� ��� DWORD ���� mSec
const int SCT_RESUME = 3200; // ��ũ��Ʈ ��� ���� ����. ���� ����
const int SCT_END = 3300; // ��ũ��Ʈ �� - ���� ����

const int SCT_PROCESS_NEXT = 3400; // ���� ��ũ��Ʈ ����
const int SCT_JUMP = 3500; // ���� ��ġ���� ��ũ��Ʈ ���� F1,wParam - ��ũ��Ʈ ��ȣ
const int SCT_JUMP_IF = 3600; // ���������� ���� ���� ��ũ��Ʈ ���� F1,wParam - �Ǵ��� �ٰŰ� �Ǵ� ��ũ��Ʈ ��ȣ F2,F3, lParam - LOWORD:���϶�|HIWORD:�����϶�
const int SCT_SET_GLOBAL_VAR = 3700; // F1,wParam - ���� ��ȣ F2,lParam - ��,����
const int SCT_JUMP_RANDOM = 3800; // ���� ��ġ���� ������ ��ġ�� ��ũ��Ʈ ���� F1,F2,wParam - HIWORD, LOWORD, F3,lParam - HIWORD ��ũ��Ʈ ��ȣ

const int SCT_SOUND_PLAY = 4000; // ���� ��� wParam - ���� �̸� ���ڿ� ������. lParam - LOWORD,F1-0:�ӽ�ä�����,1:��Ʈ������� HIWORD,F2-0:����,1:�ѹ���
const int SCT_SOUND_STOP = 4100; // ���� ��� ���� lParam,F1-0:��Ʈ����ä��,1:�ӽ� ä�� 

const int SCT_MODE_CHANGE = 5000;

const int SCT_MAP_LOAD_ATTR = 6000; // �� �Ӽ�(��ã�� �� ������Ʈ������ ����) �ε� wParam - ���� �̸� ���ڿ� ������ F1,lParam - 0:���ι�� 1:������
const int SCT_MAP_LOAD_SETTING = 6100; // �� ����(ĳ���� ��ġ �� ���� ��ġ ����) �ε� wParam - ���� �̸� ���ڿ� ������ F1,lParam - 0:���ι�� 1:�� ������
const int SCT_MAP_RETURN = 6200; // �� ������� ����
const int SCT_MAP_SCROLL = 6300; // �� ��ũ�� F1,wParam - 0:���� 1:�����̵� Pt,lParam - POINT �� ������

const int SCT_CHR_SET_ANI_OBJ = 7000; // ĳ���Ϳ� Animation Object ������ �Ҵ� wParam - Animation Object ������ lParam - ����ִ���.. !!!��ũ��Ʈ���� �� ����.
const int SCT_CHR_SET_DATA = 7100; // ĳ���Ϳ� ������ ���� wParam - �� ��� ĳ���� ������ ����ü ������ !!!��ũ��Ʈ���� �� ����.
const int SCT_CHR_SET_ATTACK = 7200; // ĳ���� ���� ��� ���� wParam - ���� �ϴ� ĳ���� ������(��ȣ) lParam - ���� ���� ĳ���� ������(��ȣ)
const int SCT_CHR_HITTED = 7300; // ĳ���� ���� ���� wParam - ���� ��� ĳ���� ������(��ȣ)
const int SCT_CHR_SET_DIRECTION = 7400; // ĳ���� ���� �ٲ� F1,wParam - ĳ���� ��ȣ F2,lParam ���� ��ȣ
const int SCT_CHR_SET_ANIMATION = 7500; // ĳ���� ���ϸ��̼� wParam - ĳ���� ��ȣ lParam - LOWORD:���ϸ��̼� ��ȣ,HIWORD:16-����|32-�ѹ���
const int SCT_CHR_SET_MOVE = 7600; // ĳ���� �̵� wParam - F1,LOWORD-ĳ���͹�ȣ, F2,HIWORD-�̵����:0����|1�����̵�|8�پ F3:0���� ��ũ��Ʈ ���� 1:�̵� ���������� ��ٸ�. lParam(Point) - POINT�� ������
const int SCT_CHR_STOP_MOVE = 7700; // ĳ���� �̵� ���� ���� ����
const int SCT_CHR_SET_PARTY = 7800; // ��Ƽ ĳ���ͷ� ���� wParam - ĳ���� ������(��ȣ) lParam - 1 ~ 6 ��Ƽ
const int SCT_CHR_SET_CTRL = 7900; // ��Ƽ ĳ������ ��� ��Ʈ�� ����  wParam - ĳ���� ������(��ȣ) lParam - true || false

const int SCT_FX_ENV_BEGIN = 8000; // ȯ�� ������ ���� wParam - ȿ�� ��ȣ lParam - ���� �ð� DWORD mSec
const int SCT_FX_ENV_END = 8100; // ȯ�� ������ �� wParam - ȿ�� ��ȣ
const int SCT_RENDER_MAIN = 8200; // ��ü ������ ����(FadeIn,FadeOut) wParam,F1 - ��,����

const int SCT_INTF_SET = 9000; // �������̽� ���̾�� ��ư ���� ���� wParam - F1,LOWORD - �������̽� ��ȣ, F2,HIWORD ���̾� ��ȣ lParam,F3 - ��ư ��ȣ

const int MAX_SCT_COMMAND = 64;
const int MAX_SCT = 1024;

typedef struct _SCT_HEADER
{
	char szID[64];
	float fVersion;
	int nQt;
	_SCT_HEADER const & operator = (_SCT_HEADER const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _SCT_HEADER;

typedef struct _SCT_DATA
{
	int		nCommand;	// ��ɾ�
	int		nFlag1;		// �÷���1
	int		nFlag2;		// �÷���2
	int		nFlag3;		// �÷���3
	POINT	pt;			// ����1
	RECT	rc;			// ����
	float	fSpeed;		// �ӵ�
	DWORD	dwTime;		// mSec ���� �ð�
	int		nText;		// �ؽ�Ʈ ������ ����
	char*	szText;		// �ؽ�Ʈ ������
	_SCT_DATA const & operator = (_SCT_DATA const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _SCT_DATA;





const int MAX_SPR = 1024; 	// �ִ� 1024 ���� ��������Ʈ ó��
const int MAX_ANI = 512;	// �ִ� 64 ���� ���ϸ��̼� ó��
const int MAX_FRM = 32;		// ���ϸ��̼Ǵ� �ִ� 32 �� ������
const int MAX_ANI_CTRL = 1024;	// �� ������Ʈ �� �ִ� 1024 ���� �������� ���ϸ��̼� ó��..

const int FL_ANI_LOOP = 0; // ���..
const int FL_ANI_ONCE = 1;  // �ѹ��� ���� ���� ���Ϸ� ���ƿ�..
const int FL_ANI_ONCE_FIX = 2; // ���ϸ��̼� �ѹ�����.. ����

const int PF_555 = 555;
const int PF_565 = 565;

const int MAX_TILE_MAP_LAYER = 6;
const int MAX_TILE_MAP_WIDTH = 2048;
const int MAX_TILE_MAP_HEIGHT = 2048;

const int NODE_TILE_SET = 1;
const int NODE_TILE_SUB_SET = 2;

const int RENDER_NORMAL = 0; // ����
const int RENDER_TRANS = 1; // ������
const int RENDER_ALPHA_ADD = 2; // 
const int RENDER_ALPHA_SOFT = 3; // 
const int RENDER_SHADOW = 4; // �׸��� ���
const int RENDER_DARK = 5; // ��Ӱ� ���
const int RENDER_COLOR = 6; //  �÷��� ÷���� ���
const int RENDER_COLOR_LEVEL = 7; // ��� ���� �������� �÷����� ���

const int MAX_OBJ_ANI = 8; //  �� ��ü�� ���� ���ϸ��̼� ��ü ��

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

typedef struct _SPR_TOOL
{
	RECT	rcV;			// ĳ���� ���� - ��Ʈ 1
	POINT	ptCV;			// ������ - ��Ʈ 1.
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

typedef struct _LSP_ENCODE_BUFF
{
	_LSP_ENCODE_BUFF* Prev; // ��ũ�� ����Ʈ ���·� �Ǿ� �ִ�.
	int QtZero;				// 0 �ȼ� ��
	int QtPixel;			// ��ȿ �ȼ� ��
	WORD Pixel[1024];		// 1024 �ȼ����� ó�� ����
	_LSP_ENCODE_BUFF* Next;
	_LSP_ENCODE_BUFF const & operator = (_LSP_ENCODE_BUFF const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _LSP_ENCODE_BUFF;

/*
// LSP Data ����
		+--- 2����Ʈ - �ٿ� ���� ����
        |       |
        |       +-----+--- 2����Ʈ - ��� �������(������ �ǳʶٴ±���)
        |       |     |
        |       |     +--- 2����Ʈ - ��� �ȼ���
        |       |              |
        |       |              +--- 2����Ʈ - ���� �ȼ�
        |       |              +---        .
        |       |              +---        . ��� �ȼ��� ��ŭ �ݺ�
        |       |              +---        .
        |       +--------
        |            .
        |            . ������ŭ �ݺ�
        |            .
        +-------- 
		    .
		    . // �� ����ŭ �ݺ�
		    .
*/

typedef struct _ANI_DATA // 8���� ���ϸ��̼� ������
{
	char		szName[32];	// ���ϸ��̼� �̸�
	int			nFlag;		// ���ϸ��̼� �÷���..
	float		fSpd;		// ���ǵ�.. ������ Frame/Sec
	short int 	nMaxFrm;	// ���⺰ �ִ� ������
	short int*	pnFrms;		// ���⺰ ������ �迭
} _ANI_DATA;

typedef struct _OBJ_HEADER // ĳ���� ���..
{
	char szID[4]; // 'O' 'B' 'J' 'D'
	char szRemark[64]; // �ּ�
	char szAniFN[64]; // ���ϸ��̼� ���� �̸�
	int nSprQt; // ��������Ʈ ���� ����
	char szSprFNs[MAX_OBJ_ANI][64]; // ��������Ʈ ���� �̸���...
	_OBJ_HEADER const & operator = (_OBJ_HEADER const &other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _OBJ_HEADER;

typedef struct _BMP16_HEADER
{
	char	szID[4]; // �ݵ�� 'B', 'M', 'P', 16
	char	szRemark[64]; // �ּ�..
	int		nWidth;
	int		nHeight;
	_BMP16_HEADER const & operator = (_BMP16_HEADER const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _BMP16_HEADER;

const int TILE_SIZE = 32; // Ÿ�� ������...
const int TILE_SHIFT = 5; // change this to reflect the the size. // Ex. 32x32 tile equals 2^5. or a TILE_SHIFT of 5

typedef struct _TILE_MAP_HEADER
{
	char szID[4]; // 'T' 'M' 'D' NULL;
	char szRemark[64]; // �̸�??
	int nWidth; // -1 �̸� ���� �ʴ´�..
	int nHeight; // -1 �̸� ���� �ʴ´�..
	char szBMPFNs[MAX_TILE_MAP_LAYER][64]; // ��Ʈ�� ���� �̸�... ���� �����Ϳ����� ���δ�.
	COLORREF crCKs[MAX_TILE_MAP_LAYER]; // �÷�Ű
	int nResrcQts[MAX_TILE_MAP_LAYER]; // Ÿ�� ���ҽ� ����..
	_TILE_MAP_HEADER const & operator = (_TILE_MAP_HEADER const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} TILE_MAP_HEADER, *LPTILE_MAP_HEADER;

typedef struct _TILE_MAP_DATA
{
	short int snIndex; // -1 �̸� ���� �ʴ´�.. Ÿ�� ���ҽ� ��ȣ.. 32 ���� �����̴�.
	short int snFlags; // 0 - �ƹ��Ӽ� ����. 1 - �浹 2 - 4 - 8 - 16 - 32 - ......
} _TILE_MAP_DATA, *LPTILE_MAP_DATA;

/*
typedef struct _TILE_MAP_OBJ_HEADER
{
	char szBMPFNs[MAX_TILE_MAP_OBJ_REG][64];
	short int nX; // -1 �̸� ���� �ʴ´�..
	short int nY; // -1 �̸� ���� �ʴ´�..
} TILE_MAP_OBJ_HEADER, *LPTILE_MAP_OBJ_HEADER;

typedef struct _TILE_MAP_OBJ_DATA
{
	short int nIndex;
	short int nX; // -1 �̸� ���� �ʴ´�..
	short int nY; // -1 �̸� ���� �ʴ´�..
} TILE_MAP_OBJ_DATA, *LPTILE_MAP_OBJ_DATA;
*/

typedef struct _TILE_SET_HEADER
{
	char	szName[64];
	char	szBMPFN[64];
	COLORREF crCK; // �÷�Ű..
	int		nQtSubSet; // Ÿ�ϼ� ����
} TILE_DATA_TOOL, *LPTILE_DATA_TOOL;

const int MAX_MAP_OBJ_REG = 64;
const int MAX_MAP_OBJ = 512;

typedef struct _MAP_OBJ_HEADER
{
	char	szID[4]; // 'M' 'P' 'O' 'D'
	char	szRemark[64]; // �ּ�
	int		nWidth; // �ʺ�
	int		nHeight; // ����
	char	szRegObjAniFNs[MAX_MAP_OBJ_REG][64];
	char	szRegObjSprFNs[MAX_MAP_OBJ_REG][64];
	_MAP_OBJ_HEADER const & operator = (_MAP_OBJ_HEADER const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _MAP_OBJ_HEADER;

typedef struct _GAME_RESOURCE_DATA
{
	char szMapFN[128];
	char szObjFN[128];
	char szCursorFN[128];
	char szItemFN[128];
	char szIntfFNs[32][128];
	char szSoundBkgFNs[8][128];
	char szSoundEffectFNs[64][128];
} _GAME_RESOURCE_DATA;

const int MAX_LOOK = 64; // �ִ� �� ǥ����
const int MAX_LOOK_PART = 64; // ǥ�� ���� �ִ� ��Ʈ�� - ��, ��, ��, ��....�Ӹ� ���...
const int MAX_LOOK_PART_ANI = 64; // �� �� ��Ʈ�� �ִ� ���� - ������ ������ 64���� �� ������ �ִ�..

typedef struct _LOOK_HEADER
{
	char		szID[4]; // 'L' 'A' 'D' 'F' �ĺ���..
	char		szRemark[64]; // �ּ�
	int			nQt;
	char		szAniFN[64]; // ���ϸ��̼� ���� �̸�..
	char		szSprFN[64]; // ��������Ʈ ���� �̸�.
	_LOOK_HEADER const & operator = (_LOOK_HEADER const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _LOOK_HEADER;

typedef struct _LOOK_DATA
{
	char szRemark[64]; // �ּ�..
	int nQtPart; // �� �κ� ����
	int nQtAnisPerParts[MAX_LOOK_PART]; // �� �κ� ���� �ִ� ����
	int nPeriods[MAX_LOOK_PART]; // ���ϸ��̼� �ֱ� - �� �ð����� �ѹ��� �ݺ�.
	int nPeriodsRnd[MAX_LOOK_PART]; // ���ϸ��̼� �ֱ� ������....
	int nAnis[MAX_LOOK_PART][MAX_LOOK_PART_ANI];
	_LOOK_DATA const & operator = (_LOOK_DATA const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _LOOK_DATA;

// �������̽�
const int MAX_LAYER = 64;
const int MAX_INTF = 256;

typedef struct _INTF_HEADER
{
	char		szID[4]; // 'I' 'N' 'T' 'F' �ĺ���..
	int			nQt; // �������̽� ����
	char		szRemark[64]; // �ּ�
	char		szAniFN[64]; // ���ϸ��̼� ���� �̸�..
	char		szSprFN[64]; // ��������Ʈ ���� �̸�.
	RECT		rcWhole; // �������̽� ����
	_INTF_HEADER const & operator = (_INTF_HEADER const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _INTF_HEADER;

typedef struct _INTF_DATA
{
	POINT		ptView;	// ��� ��ġ
	RECT		rcRgn;	// ���콺 üũ ����
	int			nParentLayer; // ������̾ �����ִ���....
	int			nType; // ����, ��ư, ��ũ�ѹ��¿�, ��ũ�ѹٻ���, �巡��, ���̾�, �÷�����, 0,1,2,4,8,16 .....
	int			nFlags[4]; // �÷��� 4��
	COLORREF	crFill;	// ä�� ��... A,B,G,R
	int			nAnis[4]; // ���ϸ��̼� ��ȣ.. �迭 ����� �������, ���콺�� ���� �ö�, ���õ�, ���� ����
	int			nRenderTypes[4]; // ��� ���.. RENDER_NORMAL, _TRANS, _ALPHA_SOFT, _ALPHA_ADD, _SHADOW, _DARK
	int			nPos1; // ��ư�϶� 0 - ����, 1 - ���콺 ��, 2 - ����, 3 - ������
	int			nPos2; // ��ư�϶� 0 - ����, 1 - ���콺 ��, 2 - ����, 3 - ������ --- �ַ� ���� ���¸� ��Ÿ���� ��..
	char		szName[32]; // ���� - ���߿� ������ ��Ÿ����.
	int			nText; // �ؽ�Ʈ ������ ����
	char*		szText; //  �ؽ�Ʈ ������
} _INTF_DATA;

const int INTF_TYPE_NORMAL = 0;
const int INTF_TYPE_BUTTON_NORMAL = 1;
const int INTF_TYPE_BUTTON_TOGGLE = 2;
const int INTF_TYPE_BUTTON_JUMP = 3;
const int INTF_TYPE_BUTTON_RADIO = 4;
const int INTF_TYPE_SCROLL_LR = 5;
const int INTF_TYPE_SCROLL_TB = 6;
const int INTF_TYPE_DIAL_LR = 7;
const int INTF_TYPE_DIAL_TB = 8;
const int INTF_TYPE_PROGRESS = 9;
const int INTF_TYPE_COLOR_BOX = 10;
const int INTF_TYPE_TEXT_IN = 11;
const int INTF_TYPE_TEXT_OUT = 12;
const int INTF_TYPE_LIST_BOX = 13;
const int INTF_TYPE_COMBO_BOX = 14;
const int INTF_TYPE_DRAG_RGN = 15;

// ���콺 �÷���
const int MOUSE_LBCLICK = 1;
const int MOUSE_LBCLICKED = 2;
const int MOUSE_LBDOWN = 4;
const int MOUSE_MBCLICK = 8;
const int MOUSE_MBCLICKED = 16;
const int MOUSE_MBDOWN = 32;
const int MOUSE_RBCLICK = 64;
const int MOUSE_RBCLICKED = 128;
const int MOUSE_RBDOWN = 256;
const int MOUSE_LBDBLCLK = 512;
const int MOUSE_MBDBLCLK = 1024;
const int MOUSE_RBDBLCLK = 2048;

const int MAX_ITEM = 1024;
typedef struct _ITEM_HEADER
{
	char	szID[4]; // 'I' 'T' 'E' 'M' �ĺ���..
	char	szRemark[64]; // �ּ�
	int		nQt;
	char	szAniFN[64]; // ���ϸ��̼� ���� �̸�..
	char	szSprFN[64]; // ��������Ʈ ���� �̸�.
	_ITEM_HEADER const & operator = (_ITEM_HEADER const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _ITEM_HEADER;

typedef struct _ITEM_DATA
{
	char		szName[32];
	int			nAni; // �Ҵ�� ���ϸ��̼�
	short int	snWidth; // ������ �ʺ�
	short int	snHeight; // ������ ����
	short int	snRemark; // ���� ����
	char*		szRemark; // ����..
	short int	snRemarkNPC; // ���� ���� �渮
	char*		szRemarkNPC; // ������ ����..
	short int	snStrength; // ü��
	short int	snSpirit; // �ټ�
	short int	snCharm; // �ŷ�
	short int	snIQ; // 
	short int	snEQ; // 
	short int	snLuck; // ���
	short int	snExtra0; // ����0
	short int	snExtra1; // ����1
	short int	snExtra2; // ����2
	short int	snExtra3; // ����3
	short int	snSpecial0; // Ư���ɷ�0
	short int	snSpecial1; // Ư���ɷ�1
	short int	snSpecial2; // Ư���ɷ�2
	short int	snSpecial3; // Ư���ɷ�3
	short int	snDurability; // ���ӽð� - mSec ����
	
	short int	snStrengthNeed; // ü��
	short int	snSpiritNeed; // �ټ�
	short int	snCharmNeed; // �ŷ�
	short int	snIQNeed; // 
	short int	snEQNeed; // 
	short int	snLuckNeed; // ���
	short int	snExtra0Need; // ����0
	short int	snExtra1Need; // ����1
	short int	snExtra2Need; // ����2
	short int	snExtra3Need; // ����3
	_ITEM_DATA const & operator = (_ITEM_DATA const & other)
	{
		memcpy(this, &other, sizeof(*this));
		return *this;
	}
} _ITEM_DATA;


const int MAX_HOUSE_DATA = 512; // �������� ����...

typedef struct _HOUSE_HEADER // ĳ���� ���..
{
	char	szID[4]; // 'M' 'H' 'D' NULL
	char	szRemark[64]; // �ּ�
	int		nQt; // ��������Ʈ ���� ����
} _HOUSE_HEADER;

typedef struct _HOUSE_DATA
{
	RECT rcRgn; // ���� - 32 ���� �̴�.
	int nNum;	// ����ȣ
} _HOUSE_DATA;
#endif // AFX_MYCONSTANDDEF_H_INCLUDED_