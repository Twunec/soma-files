// AniObjTool.cpp: implementation of the CAniObjTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AniObjTool.h"
#include "DDEngineTool4.h"

#include "GlobalVar.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CAniObjTool::CAniObjTool()
{
	m_lpDDS = NULL;
	m_pRGBTbls = NULL;
	MAKE_ZERO(m_SprExs);

	AniCtrlAlloc(MAX_ANI_CTRL/2);
}

CAniObjTool::~CAniObjTool()
{
	RELEASE_SAFE(m_lpDDS);
	if(m_pRGBTbls) { delete [] m_pRGBTbls; m_pRGBTbls = NULL; }
}

void CAniObjTool::SprExGetData(int index, _SPR_TOOL *pSprDataEx)
{
	if(index < 0 || index >= m_HSpr.nQt || index >= MAX_SPR || pSprDataEx == NULL)
	{
		MAKE_ZERO(*pSprDataEx);
		return;
	}
	*pSprDataEx = m_SprExs[index];
}

void CAniObjTool::SprExSetData(int index, _SPR_TOOL *pSprDataEx)
{
	if(index < 0 || index >= m_HSpr.nQt || pSprDataEx == NULL) return;
	m_SprExs[index] = *pSprDataEx;
}

void CAniObjTool::SprNew()
{
	SprRelease();
	MAKE_ZERO(m_SprExs);
	RELEASE_SAFE(m_lpDDS);
	if(m_pRGBTbls) { delete [] m_pRGBTbls; m_pRGBTbls = NULL; }

	m_nSprWorkQt = 0;
}

void CAniObjTool::AniNew()
{
	AniRelease();
	m_nCurAnis[0] = 0;
	m_nCurDirs[0] = 0;
	m_nCurFrms[0] = 0;
}
/*
void CAniObjTool::Load2(const char* szFileName, int nType)
{
	if(nType != SAVE_ANI) if(m_pRGBTbls) { delete [] m_pRGBTbls; m_pRGBTbls = NULL; }

	////////////////////////////////////////////////////////////////////////////////
	// ��������Ʈ...................................................................
	if(nType == SAVE_SPR_NORMAL) // �ܼ� ����
	{
		int i;
		CFile file; if(file.Open(szFileName, CFile::modeRead) == FALSE) { MessageBox(NULL, szFileName, "���� ���� ����", MB_OK); return; }
		file.Read(&m_HSpr, sizeof(_SPR_HEADER)); // ��� �б�
		
		// ��������Ʈ ���� - �������� ���̴� �ΰ����� ������.
		for(i = 0; i < m_HSpr.nQt; i++)
		{
			file.Read(&m_SprExs[i], sizeof(_SPR_TOOL));
		}

		_SPR_NORMAL spr;
		for(i = 0; i < m_HSpr.nQt; i++)
		{
			file.Read(&spr, sizeof(_SPR_NORMAL));
			ConvSprNormalToSprToolEx(&spr, &m_SprExs[i]);
		}

		RELEASE_SAFE(m_lpdds);
		g_pTEng->ChangePath("BMP");
		m_lpdds = g_pTEng->LoadBMP(m_HSpr.szBMPFN, FALSE, m_HSpr.SrcCK); // ���ǽ� �ε�...
		RECT rcT = g_pTEng->GetSurfaceSize(m_lpdds); // ��� ����
		m_HSpr.nWidth = rcT.right; m_HSpr.nHeight = rcT.bottom;
		file.Close();
	}
	else if(nType == SAVE_SPR_LSP)
	{
		CFile file; if(file.Open(szFileName, CFile::modeRead) == FALSE) { MessageBox(NULL, szFileName, "���� ���� ����", MB_OK); return; }

		file.Read(&m_HSpr, sizeof(_SPR_HEADER)); // ��������Ʈ ��� �б�.
		
		RELEASE_SAFE(m_lpdds);
		g_pTEng->ChangePath("BMP");
		m_lpdds = g_pTEng->LoadBMP(m_HSpr.szBMPFN, FALSE, m_HSpr.SrcCK); // ���ǽ� �ε�...
		if(m_lpdds)
		{
			int i;
			// ��������Ʈ ���� - �������� ���̴� �ΰ����� ������.
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				file.Read(&m_SprExs[i], sizeof(_SPR_TOOL));
			}

			RECT rcT = g_pTEng->GetSurfaceSize(m_lpdds); // ��� ����
			m_HSpr.nWidth = rcT.right; m_HSpr.nHeight = rcT.bottom;
		}
		else // ��Ʈ�ʷε��� �����ϸ� �ڵ� ����� �����̴�..
		{
			int i = 0;
			
			_SPR_HEADER m_HSpr = m_HSpr; // ���� �ϱ����� ����� ����� ���´�.
			SprRelease();
			m_HSpr = m_HSpr; // ����� ������� ���� ���´�.

			file.Seek(sizeof(_SPR_TOOL)*m_HSpr.nQt, CFile::current); // �� ������ ��ŭ �ǳʶٰ�..

			SprExAlloc(m_HSpr.nQt);
			_SPR_LSP spr;
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				file.Read(&spr, sizeof(_SPR_LSP));
				m_pSprExs[i]->rcV1 = spr.rcV;
			}
			
			int nPF = g_pTEng->GetPixelFormat();
			for(i = 0; i < m_HSpr.nQt; i++) 	// ���� ��������Ʈ ������
			{
				file.Read(&m_pLSPExs[i]->nV1, 4); // ĳ���� ���� - Part 1
				if(m_pLSPExs[i]->nV1 > 640000) { MessageBox(NULL, szFileName, "���������� ��������Ʈ", MB_OK); exit(-1); }
				if(m_pLSPExs[i]->nV1 > 0)
				{
					m_pLSPExs[i]->pV1 = new WORD[m_pLSPExs[i]->nV1/2];
					file.Read(m_pLSPExs[i]->pV1, m_pLSPExs[i]->nV1);
					if(nPF == 555) Decode2_555(m_pLSPExs[i]->pV1);
				}
			}
		}
		file.Close();
	}
	else if(nType == SAVE_SPR_LSP_EX)
	{
		CFile file; if(file.Open(szFileName, CFile::modeRead) == FALSE) { MessageBox(NULL, szFileName, "���� ���� ����", MB_OK); return; }

		file.Read(&m_HSpr, sizeof(_SPR_HEADER)); // ��������Ʈ ��� �б�.

		RELEASE_SAFE(m_lpdds);
		g_pTEng->ChangePath("BMP");
		m_lpdds = g_pTEng->LoadBMP(m_HSpr.szBMPFN, FALSE, m_HSpr.SrcCK); // ���ǽ� �ε�...
		
		if(m_lpdds)
		{
			// ��������Ʈ ���� - �������� ���̴� �ΰ����� ������.
			int i;
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				file.Read(&m_SprExs[i], sizeof(_SPR_TOOL));
			}
			RECT rcT = g_pTEng->GetSurfaceSize(m_lpdds); // ��� ����
			m_HSpr.nWidth = rcT.right; m_HSpr.nHeight = rcT.bottom;

		}
		else // ��Ʈ�� ���� �̸��� ������ �ڵ� ����� ��������Ʈ�̴�..
		{
			int i = 0;

			_SPR_HEADER m_HSpr = m_HSpr; // ���� �ϱ����� ����� ����� ���´�.
			SprRelease();
			m_HSpr = m_HSpr; // ����� ������� ���� ���´�.
			
			file.Seek(sizeof(_SPR_TOOL)*m_HSpr.nQt, CFile::current); // �� ������ ��ŭ �ǳʶٰ�..

			SprExAlloc(m_HSpr.nQt);
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				file.Read(m_pSprExs[i], sizeof(_SPR_LSP_EX));
			}
			
			int nPF = g_pTEng->GetPixelFormat();
			for(i = 0; i < m_HSpr.nQt; i++) 	// ���� ��������Ʈ ������
			{
				file.Read(&m_pLSPExs[i]->nV1, 4); // ĳ���� ���� - Part 1
				if(m_pLSPExs[i]->nV1 > 640000) { MessageBox(NULL, szFileName, "���������� ��������Ʈ", MB_OK); exit(-1); }
				if(m_pLSPExs[i]->nV1 > 0)
				{
					m_pLSPExs[i]->pV1 = new WORD[m_pLSPExs[i]->nV1/2];
					file.Read(m_pLSPExs[i]->pV1, m_pLSPExs[i]->nV1);
					if(nPF == 555) Decode2_555(m_pLSPExs[i]->pV1);
				}
				file.Read(&m_pLSPExs[i]->nV2, 4); // ĳ���� ���� - Part 2
				if(m_pLSPExs[i]->nV2 > 640000) { MessageBox(NULL, szFileName, "���������� ��������Ʈ", MB_OK); exit(-1); }
				if(m_pLSPExs[i]->nV2 > 0)
				{
					m_pLSPExs[i]->pV2 = new WORD[m_pLSPExs[i]->nV2/2];
					file.Read(m_pLSPExs[i]->pV2, m_pLSPExs[i]->nV2);
					if(nPF == 555) Decode2_555(m_pLSPExs[i]->pV2);
				}
				file.Read(&m_pLSPExs[i]->nSH, 4); // �׸��� ����
				if(m_pLSPExs[i]->nSH > 640000) { MessageBox(NULL, szFileName, "���������� ��������Ʈ", MB_OK); exit(-1); }
				if(m_pLSPExs[i]->nSH > 0)
				{
					m_pLSPExs[i]->pSH = new WORD[m_pLSPExs[i]->nSH/2];
					file.Read(m_pLSPExs[i]->pSH, m_pLSPExs[i]->nSH);
					if(nPF == 555) Decode2_555(m_pLSPExs[i]->pSH);
				}
				file.Read(&m_pLSPExs[i]->nFX, 4); // ���� ����
				if(m_pLSPExs[i]->nFX > 640000) { MessageBox(NULL, szFileName, "���������� ��������Ʈ", MB_OK); exit(-1); }
				if(m_pLSPExs[i]->nFX > 0)
				{
					m_pLSPExs[i]->pFX = new WORD[m_pLSPExs[i]->nFX/2];
					file.Read(m_pLSPExs[i]->pFX, m_pLSPExs[i]->nFX);
					if(nPF == 555) Decode2_555(m_pLSPExs[i]->pFX);
				}
				for(int j = 0; j < MAX_PART; j++) // ��Ʈ ����
				{
					file.Read(&m_pLSPExs[i]->nPs[j], 4);
					if(m_pLSPExs[i]->nPs[j] > 640000) { MessageBox(NULL, szFileName, "���������� ��������Ʈ", MB_OK); exit(-1); }
					if(m_pLSPExs[i]->nPs[j] > 0)
					{
						m_pLSPExs[i]->pPs[j] = new WORD[m_pLSPExs[i]->nPs[j]/2];
						file.Read(m_pLSPExs[i]->pPs[j], m_pLSPExs[i]->nPs[j]);
						if(nPF == 555) Decode2_555(m_pLSPExs[i]->pPs[j]);
					}
				}
			}
		}
		file.Close();
	}
	else if(nType == SAVE_SPR_LSP_INDEXED) // 8��Ʈ �ε��� ��������Ʈ
	{
		CFile file; if(file.Open(szFileName, CFile::modeRead) == FALSE) { MessageBox(NULL, szFileName, "���� ���� ����", MB_OK); return; }

		file.Read(&m_HSpr, sizeof(_SPR_HEADER)); // ��������Ʈ ��� �б�.
		
		RELEASE_SAFE(m_lpdds);
		g_pTEng->ChangePath("BMP");
		m_lpdds = g_pTEng->LoadBMP(m_HSpr.szBMPFN, FALSE, m_HSpr.SrcCK); // ���ǽ� �ε�...
		if(m_lpdds)
		{
			int i;
			// ��������Ʈ ���� - �������� ���̴� �ΰ����� ������.
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				file.Read(&m_SprExs[i], sizeof(_SPR_TOOL));
			}

			RECT rcT = g_pTEng->GetSurfaceSize(m_lpdds); // ��� ����
			m_HSpr.nWidth = rcT.right; m_HSpr.nHeight = rcT.bottom;
		}
		else // ��Ʈ�ʷε��� �����ϸ� �ڵ� ����� �����̴�..
		{
			int i = 0;
			
			_SPR_HEADER m_HSpr = m_HSpr; // ���� �ϱ����� ����� ����� ���´�.
			SprRelease();
			m_HSpr = m_HSpr; // ����� ������� ���� ���´�.

			SprExAlloc(m_HSpr.nQt);

			file.Seek(sizeof(_SPR_TOOL)*m_HSpr.nQt, CFile::current); // �� ������ ��ŭ �ǳʶٰ�..

			// ��������Ʈ �ȷ�Ʈ ����
			if(m_pRGBTbls == NULL) m_pRGBTbls = new RGBQUAD[256];
			file.Read(m_pRGBTbls, sizeof(RGBQUAD)*256); // �÷� ���̺� ����

			_SPR_LSP spr;
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				file.Read(&spr, sizeof(_SPR_LSP));
				m_pSprExs[i]->rcV1 = spr.rcV;
			}
			
			int nPF = g_pTEng->GetPixelFormat();

			for(i = 0; i < m_HSpr.nQt; i++) 	// ���� ��������Ʈ ������
			{
				file.Read(&m_pLSPExs[i]->nV1, 4); // ĳ���� ���� - Part 1
				if(m_pLSPExs[i]->nV1 > 640000) { MessageBox(NULL, szFileName, "���������� ��������Ʈ", MB_OK); exit(-1); }
				if(m_pLSPExs[i]->nV1 > 0)
				{
					m_pLSPExs[i]->pV1 = new WORD[m_pLSPExs[i]->nV1/2];
					WORD* pTemp = m_pLSPExs[i]->pV1;
					WORD wLineCount;
					file.Read(&wLineCount, 2); *pTemp = wLineCount; pTemp++;// ���� ī��Ʈ..
					for(int j = 0; j < wLineCount; j++)
					{
						WORD wNodeCount;
						file.Read(&wNodeCount, 2); *pTemp = wNodeCount; *pTemp++;// ��� ī��Ʈ..
						for(int k =0; k < wNodeCount; k++)
						{
							WORD wSkip, wPixelCount;
							file.Read(&wSkip, 2); *pTemp = wSkip; pTemp++;// �ǳʶٴ� �ȼ� ī��Ʈ..
							file.Read(&wPixelCount, 2); *pTemp = wPixelCount; pTemp++;// ��ȿ �ȼ� ī��Ʈ..
							BYTE* pbyTemp = new BYTE[wPixelCount];
							file.Read(pbyTemp, wPixelCount); // 8��Ʈ �ȼ��� �о�´�...
							Convert8PixelTo16Pixel(pbyTemp, pTemp, m_pRGBTbls, wPixelCount); pTemp+= wPixelCount;
							delete [] pbyTemp; pbyTemp = NULL;
						}
					}
					if(nPF == 555) Decode2_555(m_pLSPExs[i]->pV1);
				}
			}
		}
		file.Close();
	}
	// ��������Ʈ...................................................................
	////////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
	// ���ϸ��̼�...................................................................
	else if(nType == SAVE_ANI)
	{
		CFile file; if(file.Open(szFileName, CFile::modeRead) == FALSE) { MessageBox(NULL, szFileName, "���� ���� ����", MB_OK); return; }

		file.Read(&m_HAni, sizeof(_ANI_HEADER)); // ���ϸ��̼� ��� �б�
		AniAlloc(m_HAni.nQt); // �Ҵ�..
		int i;
		for(i = 0; i < m_HAni.nQt; i++) // ���ϸ��̼� ������ �б�
		{
			file.Read(m_pAnis[i], sizeof(_ANI_DATA));
		}

		file.Close();
	}
	// ���ϸ��̼�...................................................................
	////////////////////////////////////////////////////////////////////////////////
}
*/
/*
void CAniObjTool::Save(const char* szFileName, int nType)
{
////////////////////////////////////////////////////////////////////////////////
// ��������Ʈ...................................................................
	// ��������Ʈ ��� ����.
	if(nType == SAVE_SPR_NORMAL) // ���� ��������Ʈ
	{
		CFile file; file.Open(szFileName, CFile::modeCreate | CFile::modeWrite);

		int i;
		wsprintf(m_HSpr.szID, "�ܼ� Sprite : %s | Sprite - %d", szFileName, m_HSpr.nQt); // ��������Ʈ ����
		file.Write(&m_HSpr, sizeof(_SPR_HEADER));
		
		// ��������Ʈ ���� - �������� ���̴� �ΰ����� ������.
		for(i = 0; i < m_HSpr.nQt; i++)
		{
			file.Write(&m_SprExs[i], sizeof(_SPR_TOOL));
		}
		
		// ��������Ʈ ���� - ���� ���ӿ����� ���̴� ������.
		_SPR_NORMAL spr;
		for(i = 0; i < m_HSpr.nQt; i++)
		{
			ConvSprToolExToSprNormal(&m_SprExs[i], &spr);
			file.Write(&spr, sizeof(_SPR_NORMAL));
		}
		file.Close();
	}
	else if(nType == SAVE_SPR_LSP) // �ܼ����� LSP ��������Ʈ
	{
		CFile file; file.Open(szFileName, CFile::modeCreate | CFile::modeWrite);
	
		int i;
		wsprintf(m_HSpr.szID, "�ܼ����� LSP Sprite : %s | Sprite - %d", szFileName, m_HSpr.nQt); // ��������Ʈ ����
		file.Write(&m_HSpr, sizeof(_SPR_HEADER));
		
		// ��������Ʈ ���� - �������� ���̴� �ΰ����� ������.
		for(i = 0; i < m_HSpr.nQt; i++)
		{
			file.Write(&m_SprExs[i], sizeof(_SPR_TOOL));
		}
		
		if(m_lpdds)
		{
			// ��������Ʈ ���� - ���� ���ӿ����� ���̴� ������.
			_SPR_LSP_EX spr;
			_SPR_LSP spr2;
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				ConvSprToolExToSprLSPEx(&m_SprExs[i], &spr); // ������ ���� Ȯ�� ��������Ʈ�� ���ӿ��� ���� ��������Ʈ�� ��ȯ
				spr2.rcV = spr.rcV1;
				file.Write(&spr2, sizeof(_SPR_LSP));
			}

			// ���� ��������Ʈ ������
			WORD* pwBuff = NULL;
			CRect rc;
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				_SPR_TOOL sprex = m_SprExs[i];

				m_pLSPExs[i]->nV1 = 0;
				rc = sprex.rcV1; // ĳ���� ���̴� ���� - Part 1
				if((rc.right-rc.left)*(rc.bottom-rc.top) > 0) // ������ �־�߸� ó���Ѵ�.
				{
					g_pTEng->EncodeToLSP(m_lpdds, m_HSpr.SrcCK, rc, &m_pLSPExs[i]->nV1, &pwBuff);
					file.Write(&m_pLSPExs[i]->nV1, 4);
					file.Write(pwBuff, m_pLSPExs[i]->nV1);
					if(pwBuff) delete [] pwBuff; pwBuff = NULL;
				}
				else // ������ ������ 0 �� ����´�.
				{
					file.Write(&m_pLSPExs[i]->nV1, 4);
				}
			}
		}
		else
		{
			// ��������Ʈ ���� - ���� ���ӿ����� ���̴� ������.
			_SPR_LSP spr;
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				spr.rcV = m_pSprExs[i]->rcV1;
				file.Write(&spr, sizeof(_SPR_LSP));
			}

			// ���� ��������Ʈ ������
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				file.Write(&m_pLSPExs[i]->nV1, 4);
				if(m_pLSPExs[i]->nV1 > 0) file.Write(m_pLSPExs[i]->pV1, m_pLSPExs[i]->nV1);
			}
		}
		file.Close();
	}
	else if(nType == SAVE_SPR_LSP_EX) // ���ձ��� LSP ��������Ʈ
	{
		CFile file; file.Open(szFileName, CFile::modeCreate | CFile::modeWrite);
	
		int i;
		wsprintf(m_HSpr.szID, "�Ҹ���ȭ���� 8���� ���� Sprite : %s | Sprite - %d", szFileName, m_HSpr.nQt); // ��������Ʈ ����
		file.Write(&m_HSpr, sizeof(_SPR_HEADER));
		
		// ��������Ʈ ���� - �������� ���̴� �ΰ����� ������.
		for(i = 0; i < m_HSpr.nQt; i++)
		{
			file.Write(&m_SprExs[i], sizeof(_SPR_TOOL));
		}
		
		if(m_lpdds)
		{
			// ��������Ʈ ���� - ���� ���ӿ����� ���̴� ������.
			_SPR_LSP_EX spr;
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				// ������ ���� Ȯ�� ��������Ʈ�� ���ӿ��� ���� ��������Ʈ�� ��ȯ
				ConvSprToolExToSprLSPEx(&m_SprExs[i], &spr);
				file.Write(&spr, sizeof(_SPR_LSP_EX));
			}

			// ���� ��������Ʈ ������
			WORD* pwBuff = NULL;
			CRect rc;
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				_SPR_TOOL sprex = m_SprExs[i];

				m_pLSPExs[i]->nV1 = 0;
				rc = sprex.rcV1; // ĳ���� ���̴� ���� - Part 1
				if((rc.right-rc.left)*(rc.bottom-rc.top) > 0) // ������ �־�߸� ó���Ѵ�.
				{
					g_pTEng->EncodeToLSP(m_lpdds, m_HSpr.SrcCK, rc, &m_pLSPExs[i]->nV1, &pwBuff);
					file.Write(&m_pLSPExs[i]->nV1, 4);
					file.Write(pwBuff, m_pLSPExs[i]->nV1);
					if(pwBuff) delete [] pwBuff; pwBuff = NULL;
				}
				else // ������ ������ 0 �� ����´�.
				{
					file.Write(&m_pLSPExs[i]->nV1, 4);
				}

				m_pLSPExs[i]->nV2 = 0;
				rc = sprex.rcV2; // ĳ���� ���̴� ���� - Part 2
				if((rc.right-rc.left)*(rc.bottom-rc.top) > 0) // ������ �־�߸� ó���Ѵ�.
				{
					g_pTEng->EncodeToLSP(m_lpdds, m_HSpr.SrcCK, rc, &m_pLSPExs[i]->nV2, &pwBuff);
					file.Write(&m_pLSPExs[i]->nV2, 4);
					file.Write(pwBuff, m_pLSPExs[i]->nV2);
					if(pwBuff) delete [] pwBuff; pwBuff = NULL;
				}
				else // ������ ������ 0 �� ����´�.
				{
					file.Write(&m_pLSPExs[i]->nV2, 4);
				}

				m_pLSPExs[i]->nSH = 0;
				rc = sprex.rcSH; // �׸��� ����
				if((rc.right-rc.left)*(rc.bottom-rc.top) > 0) // ������ �־�߸� ó���Ѵ�.
				{
					g_pTEng->EncodeToLSP(m_lpdds, m_HSpr.SrcCK, rc, &m_pLSPExs[i]->nSH, &pwBuff);
					file.Write(&m_pLSPExs[i]->nSH, 4);
					file.Write(pwBuff, m_pLSPExs[i]->nSH);
					if(pwBuff) delete [] pwBuff; pwBuff = NULL;
				}
				else // ������ ������ 0 �� ����´�.
				{
					file.Write(&m_pLSPExs[i]->nSH, 4);
				}

				m_pLSPExs[i]->nFX = 0;
				rc = sprex.rcFX; // ���� ȿ�� ����
				if((rc.right-rc.left)*(rc.bottom-rc.top) > 0) // ������ �־�߸� ó���Ѵ�.
				{
					g_pTEng->EncodeToLSP(m_lpdds, m_HSpr.SrcCK, rc, &m_pLSPExs[i]->nFX, &pwBuff);
					file.Write(&m_pLSPExs[i]->nFX, 4);
					file.Write(pwBuff, m_pLSPExs[i]->nFX);
					if(pwBuff) delete [] pwBuff; pwBuff = NULL;
				}
				else // ������ ������ 0 �� ����´�.
				{
					file.Write(&m_pLSPExs[i]->nFX, 4);
				}

				for(int j = 0; j < MAX_PART; j++) // ����, �����۵� ��Ʈ ����
				{
					m_pLSPExs[i]->nPs[j] = 0;
					rc = sprex.rcParts[j];
					if((rc.right-rc.left)*(rc.bottom-rc.top) > 0) // ������ �־�߸� ó���Ѵ�.
					{
						g_pTEng->EncodeToLSP(m_lpdds, m_HSpr.SrcCK, rc, &m_pLSPExs[i]->nPs[j], &pwBuff);
						file.Write(&m_pLSPExs[i]->nPs[j], 4);
						file.Write(pwBuff, m_pLSPExs[i]->nPs[j]);
						delete [] pwBuff; pwBuff = NULL;
					}
					else // ������ ������ 0 �� ����´�.
					{
						file.Write(&m_pLSPExs[i]->nPs[j], 4);
					}
				}
			}
		}	
		else
		{
			// ��������Ʈ ���� - ���� ���ӿ����� ���̴� ������.
			for(i = 0; i < m_HSpr.nQt; i++)
				file.Write(m_pSprExs[i], sizeof(_SPR_LSP_EX));

			for(i = 0; i < m_HSpr.nQt; i++)
			{
				file.Write(&m_pLSPExs[i]->nV1, 4);
				if(m_pLSPExs[i]->nV1 > 0) file.Write(m_pLSPExs[i]->pV1, m_pLSPExs[i]->nV1);
				file.Write(&m_pLSPExs[i]->nV2, 4);
				if(m_pLSPExs[i]->nV2 > 0) file.Write(m_pLSPExs[i]->pV2, m_pLSPExs[i]->nV2);
				file.Write(&m_pLSPExs[i]->nSH, 4);
				if(m_pLSPExs[i]->nSH > 0) file.Write(m_pLSPExs[i]->pSH, m_pLSPExs[i]->nSH);
				file.Write(&m_pLSPExs[i]->nFX, 4);
				if(m_pLSPExs[i]->nFX > 0) file.Write(m_pLSPExs[i]->pFX, m_pLSPExs[i]->nFX);
				for(int j = 0; j < MAX_PART; j++) // ����, �����۵� ��Ʈ ����
				{
					file.Write(&m_pLSPExs[i]->nPs[j], 4);
					if(m_pLSPExs[i]->nPs[j] > 0) file.Write(m_pLSPExs[i]->pPs[j], m_pLSPExs[i]->nPs[j]);
				}
			}
		}
		file.Close();
	}
	else if(nType == SAVE_SPR_LSP_INDEXED && m_pRGBTbls)
	{
		CFile file; file.Open(szFileName, CFile::modeCreate | CFile::modeWrite);

		int i;
		wsprintf(m_HSpr.szID, "�ܼ����� 256LSP : %s | Sprite - %d", szFileName, m_HSpr.nQt); // ��������Ʈ ����
		file.Write(&m_HSpr, sizeof(_SPR_HEADER));
		
		// ��������Ʈ ���� - �������� ���̴� �ΰ����� ������.
		for(i = 0; i < m_HSpr.nQt; i++)
		{
			file.Write(&m_SprExs[i], sizeof(_SPR_TOOL));
		}

		// �ȷ�Ʈ ���̺� ����..
		file.Write(m_pRGBTbls, sizeof(RGBQUAD)*256);
		
		if(m_lpdds)
		{
			// ��������Ʈ ���� - ���� ���ӿ����� ���̴� ������.
			_SPR_LSP_EX spr;
			_SPR_LSP spr2;
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				// ������ ���� Ȯ�� ��������Ʈ�� ���ӿ��� ���� ��������Ʈ�� ��ȯ
				ConvSprToolExToSprLSPEx(&m_SprExs[i], &spr);
				spr2.rcV = spr.rcV1;
				file.Write(&spr2, sizeof(_SPR_LSP));
			}

			// ���� ��������Ʈ ������
			WORD* pwBuff = NULL;
			CRect rc;
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				_SPR_TOOL sprex = m_SprExs[i];

				m_pLSPExs[i]->nV1 = 0; // Byte ��..
				rc = sprex.rcV1; // ĳ���� ���̴� ���� - Part 1
				if((rc.right-rc.left)*(rc.bottom-rc.top) > 0) // ������ �־�߸� ó���Ѵ�.
				{
					g_pTEng->EncodeToLSP(m_lpdds, m_HSpr.SrcCK, rc, &m_pLSPExs[i]->nV1, &pwBuff);
					file.Write(&m_pLSPExs[i]->nV1, 4);
					WORD* pTemp = pwBuff;
					WORD wLine = *pTemp; pTemp++;
					file.Write(&wLine, 2); // ���� ī��Ʈ
					for(int j = 0; j < wLine; j++)
					{
						WORD wNode = *pTemp; pTemp++;
						file.Write(&wNode, 2); // ��� ī��Ʈ
						for(int k = 0; k < wNode; k++)
						{
							WORD wSkip = *pTemp; pTemp++;
							WORD wPixelCount = *pTemp; pTemp++;
							file.Write(&wSkip, 2); // �ǳʶٴ� �ȼ� ī��Ʈ
							file.Write(&wPixelCount, 2); // ���� �ȼ� ī��Ʈ
							// �ȷ�Ʈ ó��...
							BYTE* p8Pixels = new BYTE[wPixelCount];
							g_pTEng->Convert16PixelTo8Pixel(pTemp, p8Pixels, m_pRGBTbls, wPixelCount); pTemp += wPixelCount;
							file.Write(p8Pixels, wPixelCount);
							delete [] p8Pixels; p8Pixels = NULL;
						}
					}
					if(pwBuff) delete [] pwBuff; pwBuff = NULL;
				}
				else
				{
					file.Write(&m_pLSPExs[i]->nV1, 4);
				}
			}
		}
		else
		{
			// ��������Ʈ ���� - ���� ���ӿ����� ���̴� ������.
			_SPR_LSP spr;
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				spr.rcV = m_pSprExs[i]->rcV1;
				file.Write(&spr, sizeof(_SPR_LSP));
			}

			for(i = 0; i < m_HSpr.nQt; i++)
			{
				file.Write(&m_pLSPExs[i]->nV1, 4);
				if(m_pLSPExs[i]->nV1 > 0)
				{
					WORD* pTemp = m_pLSPExs[i]->pV1;
					WORD wLine = *pTemp; pTemp++;
					file.Write(&wLine, 2); // ���� ī��Ʈ
					for(int j = 0; j < wLine; j++)
					{
						WORD wNode = *pTemp; pTemp++;
						file.Write(&wNode, 2); // ��� ī��Ʈ
						for(int k = 0; k < wNode; k++)
						{
							WORD wSkip = *pTemp; pTemp++;
							WORD wPixelCount = *pTemp; pTemp++;
							file.Write(&wSkip, 2); // �ǳʶٴ� �ȼ� ī��Ʈ
							file.Write(&wPixelCount, 2); // ���� �ȼ� ī��Ʈ
							// �ȷ�Ʈ ó��...
							BYTE* p8Pixels = new BYTE[wPixelCount];
							g_pTEng->Convert16PixelTo8Pixel(pTemp, p8Pixels, m_pRGBTbls, wPixelCount); pTemp += wPixelCount;
							file.Write(p8Pixels, wPixelCount);
							delete [] p8Pixels; p8Pixels = NULL;
						}
					}
				}
			}
		}
		file.Close();
	}
	// ��������Ʈ...................................................................
	////////////////////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////
	// ���ϸ��̼�...................................................................
	else if(nType == SAVE_ANI)
	{
		// ���ϸ��̼� ����
		CFile file; file.Open(szFileName, CFile::modeCreate | CFile::modeWrite);
		int tmp = m_HAni.nQt;
		m_HAni.nQt = 0;
		int i = 0;
		for(i = 0; i < tmp; i++) // ��ȿ�� ���� ����..
		{
			if(m_pAnis[i]) m_HAni.nQt++;
		}

		wsprintf(m_HAni.szID, "�Ҹ���ȭ����AniFile : %s | %d ��", szFileName, m_HAni.nQt);
		file.Write(&m_HAni, sizeof(_ANI_HEADER));
		
		for(i = 0; i < tmp; i++)
		{
			if(m_pAnis[i]) file.Write(m_pAnis[i], sizeof(_ANI_DATA));
		}
		file.Close();
	}
	// ���ϸ��̼�...................................................................
	////////////////////////////////////////////////////////////////////////////////
}
*/

BOOL CAniObjTool::AniAdd()
{
	if(m_HAni.nQt >= MAX_ANI) return FALSE;
	if(!m_pAnis[m_HAni.nQt]) m_pAnis[m_HAni.nQt] = new _ANI_DATA;
	MAKE_ZERO(*m_pAnis[m_HAni.nQt]);
	lstrcpy(m_pAnis[m_HAni.nQt]->szName, "�߰� ���ϸ��̼�");
	m_HAni.nQt++;
	return TRUE;
}

BOOL CAniObjTool::AniInsert(int index) // ����
{
	if(index < 0 || index >= MAX_ANI-1) return FALSE;

	if(!m_pAnis[m_HAni.nQt]) m_pAnis[m_HAni.nQt] = new _ANI_DATA; // ���� �ϳ� �����

	m_HAni.nQt++;
	for(int i = m_HAni.nQt-1; i > index; i--) // �ڷ� �ϳ��� �з��� ����.
	{
		*m_pAnis[i] = *m_pAnis[i-1];
	}
	MAKE_ZERO(*m_pAnis[index]);
	return TRUE;
}

BOOL CAniObjTool::AniDelete(int index) // �߰� ����.
{
	if(index < 0 || index >= MAX_ANI) return FALSE;
	if(m_HAni.nQt <= 0) return FALSE;
	
	for(int i = index; i < m_HAni.nQt-2; i++) // ������ �ϳ��� �з� ����..
	{
		*m_pAnis[i] = *m_pAnis[i+1];
	}

	if(m_pAnis[m_HAni.nQt])
	{
		delete m_pAnis[m_HAni.nQt];
		m_pAnis[m_HAni.nQt] = NULL; // ���� �ϳ� ����
	}
	m_HAni.nQt--;

	return TRUE;
}

/*
void CAniObjTool::ConvSprToolExToSprLSPEx(_SPR_TOOL *pSprEx, _SPR_LSP_EX *pSpr)
{
	if(pSprEx == NULL || pSpr == NULL) return;

	MAKE_ZERO(*pSpr); // �ϴ� ������!

	CRect rc;
	CPoint pt;

	rc = pSprEx->rcV1;
	if(rc.Width() && rc.Height()) // View Part1
	{
		rc -= pSprEx->ptCV1;
		pSpr->rcV1 = rc;
	}

	rc = pSprEx->rcV2;
	if(rc.Width() && rc.Height()) // View Part2
	{
		rc -= pSprEx->ptCV2;
		pSpr->rcV2 = rc;
	}

	rc = pSprEx->rcSH;
	if(rc.Width() && rc.Height())
	{
		rc -= pSprEx->ptCSH;
		pSpr->rcSH = rc;
	}

	rc = pSprEx->rcFX;
	if(rc.Width() && rc.Height())
	{
		rc -= pSprEx->ptCFX;
		pSpr->rcFX = rc;
	}
	
	for(int i = 0; i < MAX_PART; i++)
	{
		rc = pSprEx->rcParts[i];
		if(rc.Width() && rc.Height())
		{
			rc -= pSprEx->ptParts[i];
			pSpr->rcPs[i] = rc;
		}
	}

	rc = pSprEx->rcD;
	if(rc.Width() && rc.Height())
	{
		rc -= pSprEx->ptCV1;
		pSpr->rcD = rc;
	}
	
	rc = pSprEx->rcA;
	if(rc.Width() && rc.Height())
	{
		rc -= pSprEx->ptCV1;
		pSpr->rcA = rc;
	}
}

void CAniObjTool::ConvSprToolExToSprNormal(_SPR_TOOL *pSprEx, _SPR_NORMAL *pSpr)
{
	if(pSprEx == NULL || pSpr == NULL) return;

	pSpr->ptCV = pSprEx->ptCV1;
	pSpr->ptCSH = pSprEx->ptCSH;
	pSpr->ptCFX = pSprEx->ptCFX;
	pSpr->rcV = pSprEx->rcV1;
	pSpr->rcSH = pSprEx->rcSH;
	pSpr->rcFX = pSprEx->rcFX;
}

void CAniObjTool::ConvSprNormalToSprToolEx(_SPR_NORMAL *pSpr, _SPR_TOOL *pSprEx)
{
	if(pSprEx == NULL || pSpr == NULL) return;

	pSprEx->ptCV1 = pSpr->ptCV;
	pSprEx->ptCSH = pSpr->ptCSH;
	pSprEx->ptCFX = pSpr->ptCFX;
	pSprEx->rcV1 = pSpr->rcV;
	pSprEx->rcSH = pSpr->rcSH;
	pSprEx->rcFX = pSpr->rcFX;
}
*/
int CAniObjTool::HitTest(CPoint point, _SPR_TOOL** ppSprEx)
{
	for(int i = 0; i < m_HSpr.nQt; i++)
	{
		if(PtInRect(&m_SprExs[i].rcV, point) == TRUE)
		{
			*ppSprEx = &m_SprExs[i];
			return i;
		}
	}
	*ppSprEx = NULL;
	return -1;
}

void CAniObjTool::SetColorKey(COLORREF ColorKey)
{
//	if(m_lpdds == NULL) return; // �÷�Ű ����
//	g_pTEng->SetColorKey(m_lpdds, ColorKey);
//	m_HSpr.SrcCK = ColorKey;
}

void CAniObjTool::GetStandLSP(RECT *prc, const WORD **pwStand)
{
	if(prc == NULL || pwStand == NULL) return;
//	if(m_pLSPExs[0] == NULL || m_pSprExs[0] == NULL)
//	{
//		MAKE_ZERO(*prc); *pwStand = NULL; return;
//	}
//	
//	*prc = m_pSprExs[0]->rcV1;
//	*pwStand = m_pLSPExs[0]->pV1;
}

void CAniObjTool::AniSave(const char *szFileName)
{
	CFile file;
	if(file.Open(szFileName, CFile::modeCreate | CFile::modeWrite) == FALSE)
	{
#ifdef _DEBUG
		OutputDebugString("���ϸ��̼� ���� ���� ���� : ");
		OutputDebugString(szFileName);
		OutputDebugString("\n");
#endif
		return;
	}
	m_HAni.szID[0] = 'A';
	m_HAni.szID[1] = 'N';
	m_HAni.szID[2] = 'I';
	m_HAni.szID[3] = NULL;
	file.Write(&m_HAni, sizeof(_ANI_HEADER)); // ���ϸ��̼� ��� �б�

	for(int i = 0; i < m_HAni.nQt; i++)
	{
		if(m_pAnis[i]->fSpd == 0.0f) m_pAnis[i]->fSpd = 10.0f; // �⺻������ ����..
		file.Write(m_pAnis[i], sizeof(_ANI_DATA)); // ���ϸ��̼� ������ ����
		if(m_pAnis[i]->nMaxFrm > 0)
		{
			file.Write(m_pAnis[i]->pnFrms, m_pAnis[i]->nMaxFrm*m_HAni.nDirQt*2); // ���ϸ��̼� ������ ������ ����
		}
	}
	file.Close();
}

void CAniObjTool::SprAlloc(int nQt)
{
	CAniObjLSP::SprAlloc(nQt);
}

void CAniObjTool::SprSave(const char *szFileName)
{
	if(szFileName == NULL) return;
	int n = lstrlen(szFileName);
	if(n < 4) return;
	char szExt[3] = { szFileName[n-3], szFileName[n-2], szFileName[n-1] };
	
	int nPF = g_pTEng->PixelFormatGet(); // �ȼ� ����

	if(	(szExt[0] == 'S' || szExt[0] == 's') && 
		(szExt[1] == 'P' || szExt[1] == 'p') && 
		(szExt[2] == 'L' || szExt[2] == 'l') )
	{
		if(m_lpDDS) // �������� �����Ǿ� �ִٸ�..
		{
			CFile file;
			file.Open(szFileName, CFile::modeCreate | CFile::modeWrite);
			
			m_HSpr.szID[0] = 'S';
			m_HSpr.szID[1] = 'P';
			m_HSpr.szID[2] = 'L';
			m_HSpr.szID[3] = 'N';
			wsprintf(m_HSpr.szRemark, "�ܼ� LSP Sprite | Sprite - %d", m_HSpr.nQt);
			file.Write(&m_HSpr, sizeof(_SPR_HEADER));

			// ��������Ʈ ���� - �������� ���̴� �ΰ����� ������
			for(int i = 0; i < m_HSpr.nQt; i++)
				file.Write(&m_SprExs[i], sizeof(_SPR_TOOL));
				
			// ��������Ʈ ���� - ���� ���ӿ����� ���̴� ������.
			this->SprAlloc(m_HSpr.nQt);
			m_HSpr = m_HSpr;

			for(i = 0; i < m_HSpr.nQt; i++)
			{
				g_pTEng->EncodeToLSPData(m_lpDDS, m_HSpr.SrcCK, m_SprExs[i].rcV, m_SprExs[i].ptCV, m_pSprs[i]);
				if(g_pTEng->PixelFormatGet() == PF_555) this->Decode2_565(m_pSprs[i]); // �ȼ� ������ 555 ��� 565 �ٲپ� �ش�..
				file.Write(m_pSprs[i], sizeof(_SPR_LSP));
				if(g_pTEng->PixelFormatGet() == PF_555) this->Decode2_555(m_pSprs[i]); // �ȼ� ������ 555 ��� 565 �ٲپ� �ش�..
			}

			for(i = 0; i < m_HSpr.nQt; i++)
			{
				if(m_pSprs[i]->nDataSize)
				{
					if(nPF == PF_555) this->Decode2_565(m_pSprs[i]);
					file.Write(m_pSprs[i]->pwV, m_pSprs[i]->nDataSize);
					if(nPF == PF_555) this->Decode2_555(m_pSprs[i]);
				}
			}

			file.Close();
		}
		else // �ڵ� ����� �Ÿ�...
		{
			CFile file;
			file.Open(szFileName, CFile::modeCreate | CFile::modeWrite);

			m_HSpr.szID[0] = 'S';
			m_HSpr.szID[1] = 'P';
			m_HSpr.szID[2] = 'L';
			m_HSpr.szID[3] = 'N';
			wsprintf(m_HSpr.szRemark, "LSP Sprite | Sprite - %d", m_HSpr.nQt);
			file.Write(&m_HSpr, sizeof(_SPR_HEADER));
			
			// ��������Ʈ ���� - �������� ���̴� �ΰ����� ������. - 0 ���� ä���..
			_SPR_TOOL sprTemp; MAKE_ZERO(sprTemp);
			for(int i = 0; i < m_HSpr.nQt; i++)
				file.Write(&sprTemp, sizeof(_SPR_TOOL));
				
			// ��������Ʈ ���� - ���� ���ӿ����� ���̴� ������.
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				file.Write(m_pSprs[i], sizeof(_SPR_LSP));
			}
			for(i = 0; i < m_HSpr.nQt; i++)
			{
				if(m_pSprs[i]->nDataSize)
				{
					if(nPF == PF_555) this->Decode2_565(m_pSprs[i]);
					file.Write(m_pSprs[i]->pwV, m_pSprs[i]->nDataSize);
					if(nPF == PF_555) this->Decode2_555(m_pSprs[i]);
				}
			}

			file.Close();
		}
	}
	else if(	(szExt[0] == 'S' || szExt[0] == 's') && 
				(szExt[1] == 'P' || szExt[1] == 'p') && 
				(szExt[2] == 'R' || szExt[2] == 'r') )
	{
		CFile file;
		file.Open(szFileName, CFile::modeCreate | CFile::modeWrite);
		
		m_HSpr.szID[0] = 'S';
		m_HSpr.szID[1] = 'P';
		m_HSpr.szID[2] = 'R';
		m_HSpr.szID[3] = 'N';
		wsprintf(m_HSpr.szRemark, "�ܼ� Sprite : | Sprite - %d", m_HSpr.nQt);
		
		file.Write(&m_HSpr, sizeof(_SPR_HEADER));
		
		// ��������Ʈ ���� - �������� ���̴� �ΰ����� ������. - 0 ���� ä���..
		for(int i = 0; i < m_HSpr.nQt; i++)
			file.Write(&m_SprExs[i], sizeof(_SPR_TOOL));
			
		file.Close();
	}
}

void CAniObjTool::SprLoad(const char *szFileName, int nPF)
{
	CFile file;
	
	if(file.Open(szFileName, CFile::modeRead) == FALSE)
	{
		MessageBox(NULL, szFileName, "LSP ��������Ʈ ���� ���� ���� : ", MB_OK);
		return;
	}

	SprNew(); // ����...

	file.Read(&m_HSpr, sizeof(_SPR_HEADER)); // ��������Ʈ ��� �б�.
	
	for(int i = 0; i < m_HSpr.nQt; i++) // ������ ���� ������ �б�..
	{
		file.Read(&m_SprExs[i], sizeof(_SPR_TOOL));
	}
	file.Close();

	if(lstrlen(m_HSpr.szBMPFN) > 0) // ��Ʈ���� �����Ǿ� �ִٸ�..
	{
		RELEASE_SAFE(m_lpDDS);
		CString szBMPFN = g_pTEng->PathGetCur("BMP");
		szBMPFN += '\\'; // ��� ����
		szBMPFN += m_HSpr.szBMPFN; // ��� ����
		m_lpDDS = g_pTEng->SurfaceCreateWithBMP(szBMPFN, FALSE, m_HSpr.SrcCK);
	}

	if(m_HSpr.szID[0] == 'S' && m_HSpr.szID[1] == 'P' && m_HSpr.szID[2] == 'L' && m_HSpr.szID[3] == 'N' && m_lpDDS == NULL) // LSP
	{
		CAniObjLSP::SprLoad(szFileName, nPF);
		return;
	}
}

void CAniObjTool::SprLoadOldFormat(const char *szFileName)
{
/*	this->SprNew();

	CFile file;
	if(file.Open(szFileName, CFile::modeRead) == FALSE)
	{
		MessageBox(NULL, szFileName, "���� ���� ����", MB_OK);
		return;
	}


// LSP Data ����
//      0000 00
//	4����Ʈ - ���� ������ ũ��... ����Ʈ��. // �� ���˿����� �Ⱦ���.
//	2����Ʈ	- ���μ� // �� ���˿����� �Ⱦ���..
//      |
//      |
//		+--- 2����Ʈ - �ٿ� ���� ����
//      |       |
//      |       +-----+--- 2����Ʈ - ��� �������(������ �ǳʶٴ±���)
//      |       |     |
//      |       |     +--- 2����Ʈ - ��� �ȼ���
//      |       |              |
//      |       |              +--- 2����Ʈ - ���� �ȼ�
//      |       |              +---        .
//      |       |              +---        . ��� �ȼ��� ��ŭ �ݺ�
//      |       |              +---        .
//      |       +--------
//      |            .
//      |            . ������ŭ �ݺ�
//      |            .
//      +-------- 
//		    .
//		    . // �� ����ŭ �ݺ�
//		    .

	struct _SPR_HEADER_OLD
	{
		char	szID[64];
		char	szBMPFN[64];	// ��Ʈ�� ���� �̸� - �����͸� ���� ������ �� ����.
		int		nWidth;				// �ʺ�
		int		nHeight; 			// ����
		COLORREF SrcCK;				// �ҽ� �÷�Ű
		int		nQt;				// ��������Ʈ ��
	};

	const int MAX_PART = 10; 	// �ִ� 10 ���� ��Ʈ ��������Ʈ ó��
	struct _SPR_TOOL_OLD
	{
		RECT	rcV1;			// ĳ���� ���� - ��Ʈ 1
		RECT	rcV2;			// ĳ���� ���� - ��Ʈ 2
		RECT	rcSH;			// �׸��� ����
		RECT	rcFX;			// ���� ȿ�� ����
		RECT	rcD;			// ���� ���� - ĳ���� ������ �������� �Ѵ�.
		RECT	rcA;			// ���� ���� - ĳ���� ������ �������� �Ѵ�.
		RECT	rcParts[MAX_PART];	// ����, ��Ÿ ������ ���̴� ����..
		
		POINT	ptCV1;			// ������ - ��Ʈ 1.
		POINT	ptCV2;			// ������ - ��Ʈ 2.
		POINT	ptCSH;			// ������ - �׸���
		POINT	ptCFX;			// ������ - ���� ȿ��
		POINT	ptParts[MAX_PART];	// ����, ��Ÿ ������ ���̴� ������...
	};
//	struct _SPR_TOOL_OLD
//	{
//		POINT	ptCV1;			// ������ - ��Ʈ 1.
//		POINT	ptCSH;			// ������ - �׸���
//		POINT	ptCFX;			// ������ - ���� ȿ��
//		RECT	rcV1;			// ĳ���� ���� - ��Ʈ 1
//		RECT	rcSH;			// �׸��� ����
//		RECT	rcFX;			// ���� ȿ�� ����
//	};
	
	struct _SPR_LSP_OLD
	{
		RECT	rcV;			// ĳ���� ���� - Part1
	};

	_SPR_HEADER_OLD m_HSpr;
	file.Read(&m_HSpr, sizeof(_SPR_HEADER_OLD)); // ��������Ʈ ��� �б�.
	this->SprAlloc(m_HSpr.nQt);

	m_HSpr.nQt = m_HSpr.nQt; // ��� ���� ����..
	m_HSpr.nWidth = m_HSpr.nWidth;
	m_HSpr.nHeight = m_HSpr.nHeight;
	lstrcpy(m_HSpr.szBMPFN, m_HSpr.szBMPFN);
	m_HSpr.SrcCK = m_HSpr.SrcCK;
	
	int i = 0;

	_SPR_TOOL_OLD sprtool;
	for(i = 0; i < m_HSpr.nQt; i++)
	{
		file.Read(&sprtool, sizeof(_SPR_TOOL_OLD)); // �� ������ �а�..
		m_SprExs[i].ptCV = sprtool.ptCV1; // �� ������ ��ȯ??
		m_SprExs[i].rcV = sprtool.rcV1;
	}

	_SPR_LSP_OLD spr;
	for(i = 0; i < m_HSpr.nQt; i++)
	{
		file.Read(&spr, sizeof(_SPR_LSP_OLD));
		m_pSprs[i]->rcV = spr.rcV;
	}
	
	int nPF = g_pTEng->PixelFormatGet();
	for(i = 0; i < m_HSpr.nQt; i++) 	// ���� ��������Ʈ ������
	{
		file.Read(&m_pSprs[i]->nDataSize, 4); // 
		if(m_pSprs[i]->nDataSize > 640000) { MessageBox(NULL, szFileName, "���������� ��������Ʈ", MB_OK); exit(-1); }
		if(m_pSprs[i]->nDataSize > 0)
		{
			file.Read(&m_pSprs[i]->nLine, 2);
			m_pSprs[i]->nDataSize -= 2; // �� .. ���μ��� LSP ����ü�� �ִ�...
			m_pSprs[i]->pwV = new WORD[m_pSprs[i]->nDataSize/2];
			file.Read(m_pSprs[i]->pwV, m_pSprs[i]->nDataSize);
			if(nPF == 555) this->Decode2_555(m_pSprs[i]);
		}
	}
	file.Close();
*/
}

void CAniObjTool::AniLoadOldFormat(const char *szFileName)
{
/*	this->AniRelease();

	struct _ANI_HEADER_OLD
	{
		char	szID[64];		// 'A' 'N' 'I' ���� ����(1,8) ���
		int		nQt;			// Animation ����
	};
	struct _ANI_DATA_OLD
	{
		char		szName[64];	// ���ϸ��̼� �̸�
		int 	nMaxFrm;
		int 	nFrms[8][32];	// ������
		float		fSpd;		// ���ǵ�.. ������ Frame/Sec
		int nAttr;
		char szSndFN[64];
		int nSndFrm;
	};

	_ANI_HEADER_OLD HAniOld;
	_ANI_DATA_OLD oldani;

	CFile file;
	file.Open(szFileName, CFile::modeRead);

	// ��� ��ȯ
	file.Read(&HAniOld, sizeof(_ANI_HEADER_OLD));
	m_HAni.nDirQt = 8;
	m_HAni.nQt = HAniOld.nQt;
	m_HAni.szID[0] = 'A'; m_HAni.szID[1] = 'N'; m_HAni.szID[2] = 'I'; m_HAni.szID[3] = NULL;
	lstrcpy(m_HAni.szRemark, HAniOld.szID);
	
	// ������ �Ҵ�
	this->AniAlloc(m_HAni.nQt);

	for(int i = 0; i < m_HAni.nQt; i++)
	{
		file.Read(&oldani, sizeof(_ANI_DATA_OLD));
		
		// ���ϸ��̼� ������ ��ȯ
		lstrcpy(m_pAnis[i]->szName, oldani.szName);
		m_pAnis[i]->fSpd = oldani.fSpd;
		m_pAnis[i]->nFlag = oldani.nAttr;
		m_pAnis[i]->nMaxFrm = oldani.nMaxFrm;
		if(m_pAnis[i]->nMaxFrm > 0)
		{
			m_pAnis[i]->pnFrms = new short int[m_pAnis[i]->nMaxFrm*m_HAni.nDirQt];
			for(int nd = 0; nd < m_HAni.nDirQt; nd++)
			{
				for(int nf = 0; nf < m_pAnis[i]->nMaxFrm; nf++)
				{
					m_pAnis[i]->pnFrms[nd * m_pAnis[i]->nMaxFrm + nf] = oldani.nFrms[nd][nf];
				}
			}
		}
	}
	file.Close();
	*/
}

void CAniObjTool::AniDirQtSet(int nDirQt)
{
	if(nDirQt <= 0) return;

	int nProcessQt = 0;
	(nDirQt < m_HAni.nDirQt) ? nProcessQt = nDirQt : nProcessQt = m_HAni.nDirQt; // �������� ��������.
	m_HAni.nDirQt = nDirQt;
	for(int i = 0; i < m_HAni.nQt; i++)
	{
		int nMaxFrm = m_pAnis[i]->nMaxFrm;
		short int* pnFrms = m_pAnis[i]->pnFrms; // ���� ������ �迭 ������ ����ϰ�..

		if(nMaxFrm > 0) // ���� �������� �ִٸ�..
		{
			m_pAnis[i]->pnFrms = new short int[nDirQt*nMaxFrm];
			memset(m_pAnis[i]->pnFrms, 0, nDirQt*m_pAnis[i]->nMaxFrm*2);
			for(int j = 0; j < nProcessQt; j++)
			{
				memcpy(&m_pAnis[i]->pnFrms[j*nMaxFrm], &pnFrms[j*nMaxFrm], nMaxFrm*2);
			}
		}

		DELETE_ARRAY_SAFE(pnFrms); // ���� �� ����..
	}
}
