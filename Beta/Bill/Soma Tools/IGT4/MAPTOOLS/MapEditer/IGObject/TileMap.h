// TileMap.h: interface for the CTileMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TILEMAP_H__3180BEE7_24AA_4EF2_BEEF_8E93159D5533__INCLUDED_)
#define AFX_TILEMAP_H__3180BEE7_24AA_4EF2_BEEF_8E93159D5533__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <DDraw.h>

class CTileMap  
{
public:
	_TILE_MAP_HEADER m_HTMap; // �� ���
	LPDIRECTDRAWSURFACE m_lpDDSs[MAX_TILE_MAP_LAYER]; // �� ���ҽ� ���ǽ�

protected:
	HGLOBAL m_hDatas[MAX_TILE_MAP_LAYER]; // �� ������ �޸� �ڵ�
	short int* m_pnDatas[MAX_TILE_MAP_LAYER]; // ���� �� ������.. ���� 4��Ʈ�� �÷���.. 0-���� 1-�浹 2-������� 4-�����. ���� 12��Ʈ�� �ε���

public:
	void Alloc(int nWidth, int nHeight);
	const short int* DataGet(int nLayer, int x, int y) { return &m_pnDatas[nLayer][y*m_HTMap.nWidth + x]; }
	void Load(const char* szFileName);
	void Release();
	CTileMap();
	virtual ~CTileMap();

};

#endif // !defined(AFX_TILEMAP_H__3180BEE7_24AA_4EF2_BEEF_8E93159D5533__INCLUDED_)
