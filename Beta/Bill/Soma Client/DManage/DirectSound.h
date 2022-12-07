// DirectSound.h: interface for the CDirectSound class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRECTSOUND_H__27149001_5A32_11D3_8424_00105A6B96E7__INCLUDED_)
#define AFX_DIRECTSOUND_H__27149001_5A32_11D3_8424_00105A6B96E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define WAVEVERSION 1

#ifndef ER_MEM
#define ER_MEM 				0xe000
#endif

#ifndef ER_CANNOTOPEN
#define ER_CANNOTOPEN 		0xe100
#endif

#ifndef ER_NOTWAVEFILE
#define ER_NOTWAVEFILE 		0xe101
#endif

#ifndef ER_CANNOTREAD
#define ER_CANNOTREAD 		0xe102
#endif

#ifndef ER_CORRUPTWAVEFILE
#define ER_CORRUPTWAVEFILE	0xe103
#endif

#ifndef ER_CANNOTWRITE
#define ER_CANNOTWRITE		0xe104
#endif

class CDirectSound;

class AFX_EXT_CLASS CDSoundBuffer
{
public:
	VOID				SetObjectProperties( CPoint ptSoundPos );

	VOID				SetAllParameters( FLOAT fMinDistance,   FLOAT fMaxDistance );
	BOOL				IsPlaying(int sub_index = -1);
	void				SetVolume(long volume);
	long				GetVolume();
	int					NewDirectSoundBuffer(long volume = DSBVOLUME_MAX);
	BOOL				Load(CString szFileName, long volume = DSBVOLUME_MAX);	//������ ������ SoundBuffer�� ���� �ø�
	int					Play(BOOL bLoop);			//Load�� SoundBuffer ���
	BOOL				Stop(int sub_index = -1);	//���߱�
	void				SetIndex(int index){m_iIndexInDS = index;}	//DirectSound���� �Ҵ�� Resource��ȣ

	HANDLE				GetNotifyHandle(){return m_hNotifyEvent;}	//Notify�� ����� ���
	void				SoundPlayEndProcess();						//Notify�� ����� ���, Play�� �������� �˷���

	static	UINT		SoundStopProc(LPVOID lParam);

	//Load�� ���õ� �Լ���
	static	int			WaveOpenFile(char *pszFileName, HMMIO *phmmioIn, WAVEFORMATEX **ppwfxInfo, MMCKINFO *pckInRIFF);
	static	int			WaveStartDataRead(HMMIO *phmmioIn, MMCKINFO *pckIn, MMCKINFO *pckInRIFF);
	static	int			WaveReadFile(HMMIO hmmioIn, UINT cbRead, BYTE *pbDest, MMCKINFO *pckIn, UINT *cbActualRead);
	static	int			WaveCloseReadFile(HMMIO *phmmio, WAVEFORMATEX **ppwfxSrc);
	static	int			WaveCreateFile(char *pszFileName, HMMIO *phmmioOut, WAVEFORMATEX *pwfxDest, MMCKINFO *pckOut, MMCKINFO *pckOutRIFF);
	static	int			WaveStartDataWrite(HMMIO *phmmioOut, MMCKINFO *pckOut, MMIOINFO *pmmioinfoOut);
	static	int			WaveWriteFile(HMMIO hmmioOut, UINT cbWrite, BYTE *pbSrc, MMCKINFO *pckOut, UINT *cbActualWrite, MMIOINFO *pmmioinfoOut);
	static	int			WaveCloseWriteFile(HMMIO *phmmioOut, MMCKINFO *pckOut, MMCKINFO *pckOutRIFF, MMIOINFO *pmmioinfoOut, DWORD cSamples);
	static	int			WaveCopyUselessChunks(HMMIO *phmmioIn, MMCKINFO *pckIn, MMCKINFO *pckInRiff, HMMIO *phmmioOut, MMCKINFO *pckOut, MMCKINFO *pckOutRiff);
	static	BOOL		riffCopyChunk(HMMIO hmmioSrc, HMMIO hmmioDst, const LPMMCKINFO lpck);
	static	int			WaveLoadFile(char *pszFileName, UINT *cbSize, DWORD *pcSamples, WAVEFORMATEX **ppwfxInfo, BYTE **ppbData);
	static	int			WaveSaveFile(char *pszFileName, UINT cbSize, DWORD cSamples, WAVEFORMATEX *pwfxDest, BYTE *pbData);


	static  void		SetScale( CPoint ptScale ){ m_nScale = ptScale;}
	CDSoundBuffer(CDirectSound *pDirectSound);
	virtual	~CDSoundBuffer();

	friend	class		CDirectSound;


protected:
	DWORD				m_dwDurationTime;	//Play�ð�
	DWORD				m_dwStopTick;//���� �����ð� ��� (������ �ð�)
	HANDLE				m_hNotifyEvent;
	int					m_iIndexInDS;
	LPDIRECTSOUNDNOTIFY m_lpDsNotify;
	BOOL				m_bStartDestroy;

	BOOL				m_bLoadOk;
	CDirectSound		*m_bpDirectSound;
	CTypedPtrArray<CPtrArray, LPDIRECTSOUNDBUFFER> m_arrDSB;
    LPWAVEFORMATEX		m_pWaveFormatEx;          // Pointer to waveformatex structure.
	CString				m_szFileName;

    PBYTE               m_pbData;        // Pointer to actual data of file.
    UINT                m_cbSize;        // Size of data.
	BOOL				m_bSticky;
	BOOL				m_bHardware;	//�ϵ���� ���?

	LPDIRECTSOUND3DBUFFER   m_pDS3DBuffer;   // 3D sound buffer
	DS3DBUFFER              m_dsBufferParams;           // 3D buffer properties
	DWORD                   m_dwBufferBytes;
	static CPoint			m_nScale;

};

//typedef CTypedPtrArray<CPtrArray, CDSoundBuffer*> ARR_SOUNDBUFFER;
typedef CMap<int, int, CDSoundBuffer *, CDSoundBuffer *&> MAP_SOUNDBUFFER;

class AFX_EXT_CLASS CDirectSound  
{
public:
	BOOL				IsMusicPlaying(int index, int sub_index = -1);
	void				SetMusicVolume(long volume);
	int					GetMusicVolume();
	int					MusicPlay(CString file_name, int index, BOOL bLoop = FALSE);
	BOOL				MusicStop(int index, int sub_index = -1, BOOL bDelete = FALSE);		//SoundPlay���� �Ҵ���� index �� ������Ŵ
	void				RemoveUnusedMusic();							//Load�Ȱ��� ������� ������ �ʴ°� ����

	BOOL				IsSoundPlaying(int index, int sub_index = -1);
	void				SetSoundVolume(long volume);
	int					GetSoundVolume();
	int					SoundPlay(CString file_name, int index,  BOOL bLoop = FALSE, CPoint ptSoundPos = CPoint( 400, 300), FLOAT fMinDistance = 1.0f, FLOAT fMaxDistance = 11.0f); //�Ҵ�Ǿ��� SoundBuffer�� Index�� ������(-1:����)
	BOOL				SoundStop(int index, int sub_index = -1);		//SoundPlay���� �Ҵ���� index �� ������Ŵ
	void				RemoveUnusedSound();							//Load�Ȱ��� ������� ������ �ʴ°� ����

	BOOL				InitDirectSound(HWND hwnd, BOOL bFullScreen, FLOAT fDopplerFactor = 1.0f, FLOAT fRolloffFactor = 1.0f );	//DirectSound�ʱ�ȭ
	LPDIRECTSOUND		GetInterface() {return m_pDSound;}
	VOID				SetListenerParameters( FLOAT fDopplerFactor, FLOAT fRolloffFactor );
	void				SetScale( CPoint ptScale );

	CDirectSound();
	virtual ~CDirectSound();

protected:
	int						m_vMusicVolume;
	int						m_vSoundVolume;
	BOOL					m_bFullScreen;
	HWND					m_hWnd;
	LPDIRECTSOUND			m_pDSound;
	LPDIRECTSOUNDBUFFER		m_pPrimaryBuffer;
	LPDIRECTSOUND3DLISTENER m_pDSListener;   // 3D listener object
	DS3DLISTENER            m_dsListenerParams;         // Listener properties
	
//	ARR_SOUNDBUFFER			m_arrSoundBuffer, m_arrMusicBuffer;
	MAP_SOUNDBUFFER			m_mapSoundBuffer, m_mapMusicBuffer;
	BOOL					m_bSoundEnabled;//dspring_0721 ���� ���̷�Ʈ ���尡 ��밡������ üũ�Ͽ� ��� �Ұ��� �Ұ�� ���带 �����ϰ� ������ �д�....
};

#endif // !defined(AFX_DIRECTSOUND_H__27149001_5A32_11D3_8424_00105A6B96E7__INCLUDED_)
