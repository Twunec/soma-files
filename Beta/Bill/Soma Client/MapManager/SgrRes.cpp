// SgrRes.cpp: implementation of the CSgrRes class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SgrRes.h"
#include "Tile.h"
#include "Sprite.h"
#include "CustomTile.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSgrRes::CSgrRes()
{
	m_iDarkLevel = 100;
	m_iTileCount = 0;// Ÿ�� sgr�� ���� ������Ű�� ������...�Ʒ� 3��.
	m_iSpriteCount = 0;
	m_iCustomTileCount = 0;
}

CSgrRes::~CSgrRes()
{
	RemoveAllData();
}

BOOL CSgrRes::Load(CString szFileName)
{
	RemoveAllData();

	CFile file;

	if (!file.Open(szFileName, CFile::modeRead|CFile::typeBinary))
	{
		TRACE("������ ������ �������� ����\n");
		return FALSE;
	}
	CArchive ar(&file, CArchive::load);

	TRACE("sgr res ����..\n");

	int				iTileCount;
	int				iSpriteCount;
	int				iCustomTileCount;
	CTile*			pTile = NULL;
	CSprite*		pSprite = NULL;
	CCustomTile*	pCustomTile = NULL;

	BOOL			bErrorOccur = FALSE;


//	ar >> iTileCount;					//Ÿ���� ������?
///////////////////////////////////////////
	int tileCount;
	int vVersion;
//	int uniquenumber;
	
	ar >> vVersion;
//	ar >> uniquenumber;
	ar >> tileCount;

	
//////////////////////////////////////////////
	iTileCount = tileCount;
	m_iTileCount += tileCount;
		
	m_apTile.SetSize(m_iTileCount);
	for (int i=0; i<iTileCount; i++)
	{
		pTile = new CTile;
		if (pTile->Load(ar))// ���Ⱑ ������.....���ľ� �Һκ�...2�� 29��...�ذ�..
		{
			m_apTile.SetAt(i, pTile);
		}
		else
		{
			delete pTile;
			bErrorOccur = TRUE;
		}
	}

	TRACE("sgr res iSpriteCount �б���...\n");
	ar >> iSpriteCount;					//Sprite�� ������?
	
	m_iSpriteCount += iSpriteCount;// �����ǰ� �Ϸ���..

	m_apSprite.SetSize(m_iSpriteCount);
	for (i=0; i<iSpriteCount; i++)
	{
		pSprite = new CSprite;
		if (pSprite->Load(ar))
		{
			m_apSprite.SetAt(i, pSprite);
		}
		else
		{
			delete pSprite;
			bErrorOccur = TRUE;
		}
	}

	TRACE("sgr res iCustomTileCount �б���...\n");
	ar >> iCustomTileCount;				//CustomTile�� ������?
	m_iCustomTileCount += iCustomTileCount;

	m_apCustomTile.SetSize(m_iCustomTileCount);
	for (i=0; i<iCustomTileCount; i++)
	{
		pCustomTile = new CCustomTile;
		if (pCustomTile->Load(ar))
		{
			m_apCustomTile.SetAt(i, pCustomTile);
		}
		else
		{
			delete pCustomTile;
			bErrorOccur = TRUE;
		}
	}

	ar.Close();
	file.Close();
	m_szFileName = szFileName;

	TRACE("sgr res ��..\n");
	return bErrorOccur? FALSE : TRUE;
}

void CSgrRes::RemoveAllData()
{
	int size = m_apTile.GetSize();
	for (int i=0; i<size; i++)
	{
		if (m_apTile[i]) delete m_apTile[i];
	}
	m_apTile.RemoveAll();			//Tile����

	size = m_apSprite.GetSize();
	for (i=0; i<size; i++)
	{
		if (m_apSprite[i]) delete m_apSprite[i];
	}
	m_apSprite.RemoveAll();			//Sprite����

	size = m_apCustomTile.GetSize();
	for (i=0; i<size; i++)
	{
		if (m_apCustomTile[i]) delete m_apCustomTile[i];
	}
	m_apCustomTile.RemoveAll();		//CustomTile����
}

void CSgrRes::ReloadResource()
{
	BOOL bResult = Load(m_szFileName);		//�ٽ� ��ε�
	if (!bResult)
	{
		TRACE("SGR Reload ����\n");
	}
}

BOOL CSgrRes::SetDarkLevel(int iPercent, BOOL bAbsolute)	//Resource�� ��ӱ� ���� 100Percent�� ����, 0Percent �̸� ��İ�
{															//���� ���� : bAbsolute�� TRUE�� ���
	BOOL bReloadOccur = FALSE;								//bAbsolute�� False�� ���� ������ ���¿��� ��� ����

	if(iPercent == 0)
	{
		m_iDarkLevel = 100;
		ReloadResource();
		return TRUE;
	}

	if (bAbsolute)
	{
		if (iPercent==m_iDarkLevel) return bReloadOccur;

		ReloadResource();		//���� ��� �̹Ƿ� Resource ��ε�, �ѹ��̶� ��ο����� ���� �̹��� �ջ�
		bReloadOccur = TRUE;
		if (iPercent==100) return bReloadOccur;

		m_iDarkLevel = iPercent;
		DarkenProcess();
	}
	else
	{
		if (iPercent==100) return bReloadOccur;
		m_iDarkLevel = MulDiv(m_iDarkLevel, iPercent, 100);
		DarkenProcess();
	}
	return bReloadOccur;
}

//������ Resource�� m_iDarkLeve�� �����Ͽ� ��Ӱ� ����
void CSgrRes::DarkenProcess()
{
	COLORREF rgb;
	int darkrgbtone = MulDiv(64, m_iDarkLevel, 100);
	rgb = RGB(darkrgbtone, darkrgbtone, darkrgbtone);
	
	int size = m_apTile.GetSize();
	for (int i=0; i<size; i++)
	{
		if (m_apTile.GetAt(i))
			m_apTile.GetAt(i)->DarkenProcess(rgb);
	}
	
	size = m_apSprite.GetSize();
	for (i=0; i<size; i++)
	{
		if (m_apSprite.GetAt(i))
			m_apSprite.GetAt(i)->DarkenProcess(rgb);
	}

	size = m_apCustomTile.GetSize();
	for (i=0; i<size; i++)
	{
		if (m_apCustomTile.GetAt(i))
			m_apCustomTile.GetAt(i)->DarkenProcess(rgb);
	}
}