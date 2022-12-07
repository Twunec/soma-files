// _TILE_SUB_SET_DATA_TOOL.h: interface for the _TILE_SUB_SET_DATA_TOOL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX__TILE_SUB_SET_DATA_TOOL_H__569DFAC3_63A3_11D4_98B0_00C02615866B__INCLUDED_)
#define AFX__TILE_SUB_SET_DATA_TOOL_H__569DFAC3_63A3_11D4_98B0_00C02615866B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAX_ANI_COUNT		20

class _TILE_SUB_SET_DATA_TOOL  
{
public:
	_TILE_SUB_SET_DATA_TOOL();
	virtual ~_TILE_SUB_SET_DATA_TOOL();

	int GetSafe(int x, int y)
	{
		if(nWidth > 0 && nHeight > 0 && x >= 0 && x < nWidth && y >= 0 && y < nHeight)
		{
			if(pptSrcs[0][y*nWidth+x].x < 0 || pptSrcs[0][y*nWidth+x].y < 0) return -1;
			else return y*nWidth+x;
		}
		else return -1;
	};

	POINT *GetPosCur(int index)
	{
		if(nWidth > 0 && nHeight > 0 && index >= 0 && index < nWidth*nHeight)
		{
			return &pptSrcs[nCurAni][index];
		}
		else return NULL;
	}

	int *GetFlagCur(int index)
	{
		if(nWidth > 0 && nHeight > 0 && index >= 0 && index < nWidth*nHeight)
		{
			return &pnFlags[nCurAni][index];
		}
		else return NULL;
	}

	POINT *GetPos(int index, int nAniNum = 0)
	{
		if(nWidth > 0 && nHeight > 0 && index >= 0 && index < nWidth*nHeight)
		{
			return &pptSrcs[nAniNum][index];
		}
		else return NULL;
	}

	POINT *GetPos(POINT p, int nAniNum = 0)
	{
		if(nWidth > 0 && nHeight > 0 && p.x >= 0 && p.x < nWidth && p.y >= 0 && p.y < nHeight)
		{
			return &pptSrcs[nAniNum][p.y*nWidth+p.x];
		}
		else return NULL;
	}

	void Save(CFile& file);
	void Load(CFile& file);

	int Alloc(int width, int height);
	void Release();

	int Increase(int index);
	int Decrease(int index);

	void Increase();
	void Decrease();

	_TILE_SUB_SET_DATA_TOOL& operator=(_TILE_SUB_SET_DATA_TOOL& other);
public:
	char			szRemark[64]; // ����� �̸�..
	int				nWidth; // Ÿ�ϼ� �ʺ�
	int				nHeight; // Ÿ�ϼ� ����..
	int				nAniCount; // �� ��ġ�� Ÿ�� ����
	int				*pnFlags[MAX_ANI_COUNT]; // 0 - �ƹ��Ӽ� ����. 1 - �浹, 2 - ����� ���� ���
	POINT			*pptSrcs[MAX_ANI_COUNT]; // Ÿ�ϼ� ��Ʈ�� ���� ��ġ..
	int				nCurAni;
};

#endif // !defined(AFX__TILE_SUB_SET_DATA_TOOL_H__569DFAC3_63A3_11D4_98B0_00C02615866B__INCLUDED_)
