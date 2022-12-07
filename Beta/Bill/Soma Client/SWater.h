// SWater.h: interface for the SWater class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SWATER_H__0ADA3FA4_79AF_11D4_826D_00D0B769A081__INCLUDED_)
#define AFX_SWATER_H__0ADA3FA4_79AF_11D4_826D_00D0B769A081__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define  POING_SIZE   25

typedef struct tgWATER
{
	int		speed; //�ӵ�.
	int		r_max; //�ִ� ������.
	int		r_cur; //���� ������.
	bool	bIsPong;//�ĵ��� �������ΰ�.
	int		x_center;//x �߽���.
	int     y_center;//y �߽���.
} WATER;


class SWater  
{
protected:
	WATER	m_pWater[POING_SIZE];

public:
	SWater();
	~SWater(){};

	void InputData(int x, int y);
	void Draw(DDSURFACEDESC2 ddsd);
};

#endif // !defined(AFX_SWATER_H__0ADA3FA4_79AF_11D4_826D_00D0B769A081__INCLUDED_)
