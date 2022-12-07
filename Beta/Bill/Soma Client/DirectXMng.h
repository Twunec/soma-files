// DirectXMng.h: interface for the DirectXMng class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTXMNG_H__010054CA_0204_11D3_8422_0020AF9F40BD__INCLUDED_)
#define AFX_DIRECTXMNG_H__010054CA_0204_11D3_8422_0020AF9F40BD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDirectDraw;
class CDDSurface;
class CDirectInput;
class BBDX_MouseInformation;
class CDDClipper;
class CAlphaProcess;
class CDxCursor;
class CDirectSound;
class CDirect3D;
class CNight;

class DirectXMng  
{
public:
	void						DrawCursor();			//Cursor�׸���
	void						Flip();					//ȭ�� Flip
	BOOL						IsDirectInputValid() {return (NULL!=m_pDirectInput);}	//DirectInput�� ��ȿ�� �˻�
	BBDX_MouseInformation*		GetMouseInfoPtr() {return m_pMouseInfo;}	//���콺 ����
	CPoint&						GetMousePos();								//���콺�� ������ ��ǥ
	BOOL						MouseInfoUpdate();							//���콺 ���� ����
	CSize&						GetScreenSize() {return m_sizeScreen;}
	void						SetRelatedHwnd(HWND hwnd) {m_hWnd = hwnd;}	//MainWindow�� Handle(���̷�ƮX �� MainWindow Handle�� �̿�)
	BOOL						ReleaseDirectX();							//DirectX �� ����
	BOOL						InitDirectX(int width, int height, int color_depth, BOOL bFullScreen);	//DirectX�� ����
	void						RestoreSurface();							//ȭ�� �������� (�ٸ� ���α׷��� Active� ����) ����
	long						GetGammaRate(){ return m_GammaRate;}
	void						SetGammaRate( long lGammaRate );
	void						SetRainGammaRate( int nAlphaGamma );
	void						SetInHouseGammaRate();
	void						GetVGAName();
	int 						InitMask();
	DWORD						m_dwHalf16Mask;
	DWORD						m_dwHalf32Mask;

	DirectXMng();
	virtual ~DirectXMng();
public:
	CDirectSound*				m_pDirectSound;				//DirectSound ��ü

	CDDSurface*					m_bpFrontSurf;				//Front Surface(Primary Surface)
	CDDSurface*					m_bpBackSurf;				//Back Surface(Secondary Surface)
	CDDSurface*					m_pDrawSurface;				//Drawing Surface(System Memory���) (Alpha����)
	BOOL						m_bFullScreen;				//Full Screen�ΰ�?
	HWND						m_hWnd;						//MainWindow�� Handle
	CDirectDraw*				m_pDD;						//DirectDraw ��ü
	COLORREF					m_colorTrans;				//�������� �� Color (Default: RGB(0,0,0))
	CDirectInput*				m_pDirectInput;				//DirectInput ��ü
	BBDX_MouseInformation*		m_pMouseInfo;				//DirectInput�� ���� ���콺 ������ ��� �ִ°�
	CAlphaProcess*				m_pAlphaProcess;			//Alphaó���� (���?...)
	IDirectDrawGammaControl*	m_pGammaCtrl;				//Gamma Control(Ǯȭ�鿡���� ��밡���� ��?....)
	DDGAMMARAMP					m_orgGamma;					//Gamma������ �������
	DDGAMMARAMP					m_GammaLightning;			//Gamma ���� 	

	long						m_GammaRate;
	int							m_nAlphaGamma;
	CDxCursor*					m_pDxCursor;				//Cursor�׸� ����

	CSize						m_sizeScreen;				//ȭ���� ũ��
	CDirect3D*					m_p3D;
	BOOL						m_bHalEnabled;
	CNight*						m_Night;
	CString						m_VGAcardName;
	int							m_VGAType;

};

#endif // !defined(AFX_DIRECTXMNG_H__010054CA_0204_11D3_8422_0020AF9F40BD__INCLUDED_)
