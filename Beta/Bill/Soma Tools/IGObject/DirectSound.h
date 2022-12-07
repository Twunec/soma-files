// DirectSound.h: interface for the CDirectSound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTSOUND_H__01D43004_1A98_11D2_B0C7_0060970DBAD5__INCLUDED_)
#define AFX_DIRECTSOUND_H__01D43004_1A98_11D2_B0C7_0060970DBAD5__INCLUDED_

const int MAX_SOUND_CHANNEL = 64; // ���� ����
const int MAX_SOUND_DUPLICATE  = 8; // �ߺ� ���� ����..

//#include <mmreg.h>
#include <mmsystem.h>
#include <DSound.h>

class CDirectSound
{
protected:
	int WaveOpenFile(const char* pszFileName, HMMIO *phmmioIn, WAVEFORMATEX* ppwfxInfo, MMCKINFO* pckInRIFF);
	int WaveStartReadData(HMMIO* phmmioIn, MMCKINFO* pckIn);
	int WaveReadFile(HMMIO hmmioIn, UINT cbRead, BYTE* pbDest, MMCKINFO* pckIn, UINT* cbActualRead);
	int WaveCloseReadFile(HMMIO* phmmio);
	void FillBufferWithSilence(LPDIRECTSOUNDBUFFER lpdsb);
	
	LPDIRECTSOUNDBUFFER		CreateStaticBuffer(int nCh, int nBit, DWORD dwRate, DWORD dwBytes); // ä��, ��Ʈ��, ���ø�, ����Ʈ��..

protected:
	HWND					m_hWnd; 			//application's window handle
	LPDIRECTSOUND m_lpDS;
	LPDIRECTSOUNDBUFFER		m_lpPDSB; // 1 �� ���� ����
	
	LPDIRECTSOUNDBUFFER		m_lpDSBs[MAX_SOUND_CHANNEL]; // 2�� ���� ����
	LPDIRECTSOUNDBUFFER		m_lpDSBDups[MAX_SOUND_CHANNEL][MAX_SOUND_DUPLICATE]; // �ְ� ���� ����..

	char	m_szSoundFileName[MAX_SOUND_CHANNEL][128];	// 2�� ���� ���ۿ� �Ҵ�� ���� ���� �̸���
	
	LPDIRECTSOUNDBUFFER	m_lpDSBStream;		// ��Ʈ���� ���� ����
	HMMIO				m_hmmio;			// ��Ʈ���� ���� �ڵ�..
	DWORD				m_dwMidBuffer;		// ��Ʈ���� ���� �������� ��Ȯ�� �߰�.
	DWORD				m_dwLastPlayPos;	// ��Ʈ���� ���� �������� ������.
	MMCKINFO			m_mmckinfo;			// ��Ʈ���� ûũ ����

	float 	m_fVolStream; // ������� ����.. 0 ~ 99;
	float 	m_fVolStatic; // ȿ���� ����..(��ü ä�ο� ����ȴ�.); 0 ~ 99;

public:
	float 	GetVolumeStream();
	void 	SetVolumeStream(float fVol);
	float 	GetVolumeStatic();
	void 	SetVolumeStatic(float fVol);
	
	void	SetupStream(const char* szFileName);
	void	StopStream();
	void	StreamProc();

	CDirectSound();
	virtual ~CDirectSound();
	
	void Init(HWND hwnd);
	void UnloadAllWave();
	BOOL LoadWave(int nSChn, const char* szFileName);
	void UnloadWave(int nSChn);
	void Play(int nSChn, BOOL bLooping = FALSE, float fVol = 1.0f);
	void Stop(int channel);
	void StopAllChannel();
};

#endif // !defined(AFX_DIRECTSOUND_H__01D43004_1A98_11D2_B0C7_0060970DBAD5__INCLUDED_)
