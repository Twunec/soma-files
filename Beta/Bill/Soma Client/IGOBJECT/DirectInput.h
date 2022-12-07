#ifndef CDirectInput_H
#define CDirectInput_H

// CDX Input Types. Applies to keyboard keys, mouse & joystick buttons.
#include <DInput.h>

const int DK_NONE = 0;
const int DK_RELEASE = 1;
const int DK_PRESS = 2;
const int DK_REPEAT = 4;
const int NUMDIKEYS = 256;

//////////////////////////////////////////////////////////////////////////////////
// CDirectInput is a class wrapper for DirectInput and contains functions to receive 
// data from the mouse, keyboard and joystick.
//////////////////////////////////////////////////////////////////////////////////
class CDirectInput
{
private:
	void AcquireMouse();
	void UnacquireMouse();
	void AcquireKeyboard();
	void UnacquireKeyboard();
//	void AcquireJoystick();
//	void UnacquireJoystick();
	//BYTE Keys[NUMDIKEYS];

protected:
	LPDIRECTINPUT        m_lpDI;
	LPDIRECTINPUTDEVICE  m_lpDIDKeyboard;
	LPDIRECTINPUTDEVICE  m_lpDIDMouse;

#if DIRECTINPUT_VERSION >= CDX_DIVER
//	LPDIRECTINPUTDEVICE2 m_lpDIDJoystick;
#endif
	HWND m_hWnd;

	BOOL m_bMouse;
	BOOL m_bKeyboard;
//	BOOL m_bJoystick;

	int m_nMouseFlag, m_nMouseFlagOld; // ���콺 ��ư ���� �÷���
	DWORD m_dwTickLBDown; // ���콺 ���� ��ư ���� Ŭ�� ������
	DWORD m_dwTickRBDown; // ���콺 ������ ��ư ���� Ŭ�� ������

	POINT	m_ptCurMouse; // ���� ���콺 ������
	POINT	m_ptOldMouse; // ���� ���콺 ������

	RECT	m_rcLBDrag; // �巡�� ����
	RECT	m_rcMBDrag; // �巡�� ����
	RECT	m_rcRBDrag; // �巡�� ����

//	DWORD m_JoystickType;

//	float m_joystickSensitivity;
	
	RECT m_rcMLimit; // ���콺 ������ ���� ����

//	int m_joystickMinX;
//	int m_joystickMinY;
//	int m_joystickMaxX;
//	int m_joystickMaxY;

//	int m_joystickX, m_joystickY;
//	int m_joystickFreeX, m_joystickFreeY;
//	int m_joystickDeltaX, m_joystickDeltaY;

	BYTE m_byCurKeys[NUMDIKEYS]; // ���� Ű ����
	BYTE m_byOldKeys[NUMDIKEYS]; // ���� Ű ����
	BOOL m_bKeyPresses[NUMDIKEYS]; // Ű�� ���� ��������
	BOOL m_bKeyPresseds[NUMDIKEYS]; // Ű�� ������ ���� ��������
	BOOL m_bNoKeyDown; // �ƹ� Ű�Էµ� ������
	

	DWORD m_dwTickKeyPress[NUMDIKEYS];
	
public:
	void KeyboardClearKeyInput();
	void MouseClearClick();
	BOOL IsNoKeyDown() { return m_bNoKeyDown; }
	BOOL IsKeyDown(int index) { if(index < 0 || index >= NUMDIKEYS) return FALSE; return m_byCurKeys[index]; }
	BOOL IsKeyPress(int index) { if(index < 0 || index >= NUMDIKEYS) return FALSE; return m_bKeyPresses[index]; }
	BOOL IsKeyPressed(int index) { if(index < 0 || index >= NUMDIKEYS) return FALSE; return m_bKeyPresseds[index]; }
	
	CDirectInput(void);
	~CDirectInput(void);

	BOOL Init(HINSTANCE hInst, HWND hWnd, BOOL ExclusiveMouseAccess = TRUE );

	void Update(void);
	void KeyboardFlushData();
	void RunMouseControlPanel(HWND hWnd);
//	void RunJoystickControlPanel(HWND hWnd);

	//HRESULT SetMouseCooperative(DWORD inFlags);
	//void SetMouseExclusive(BOOL exclusive);
//	void JoystickSetLimits(int x1, int y1, int x2, int y2);
	void MouseSetLimits(int x1, int y1, int x2, int y2);
//	void JoystickSetSensitivity(float factor);
	void SetActiveDevices(BOOL bKeyboard, BOOL bMouse, BOOL bJoystick);
//	void JoystickSetAbs(void);
	void MouseSetPos(int x, int y);
//	void JoystickSetPos(int x, int y);
//	void JoystickSetFreePos(int x, int y);

	BOOL KeyboardGetKeyState(int nDIKey); // �ֱ� ������ Ű �˻�..

	const POINT MouseGetPos() { return m_ptCurMouse; }
	const POINT MouseGetPosOld() { return m_ptOldMouse; }
	
//	void GetJoystickPos(LONG* x, LONG* y);
//	void GetJoystickFreePos(LONG* x, LONG* y);
//	void GetJoystickDeltas(LONG* x, LONG* y);
//	float GetJoystickSensitivity();

//Janni
//  BOOL HasJoystick( void ) { return m_bJoystick; }
//  BOOL HasMouse( void )    { return m_bMouse; }
//  int  JoystickGetNumberOfButtons( void );
//  BOOL JoystickIsGamePad( void );
//    DWORD JoystickGetType( void ) { return m_JoystickType; }
        // DIDEVTYPEJOYSTICK_UNKNOWN,DIDEVTYPEJOYSTICK_TRADITIONAL,
        // DIDEVTYPEJOYSTICK_FLIGHTSTICK,DIDEVTYPEJOYSTICK_GAMEPAD 
        // DIDEVTYPEJOYSTICK_RUDDER,DIDEVTYPEJOYSTICK_WHEEL 
        // DIDEVTYPEJOYSTICK_HEADTRACKER 

	RECT MouseGetLBDragRect() { return m_rcLBDrag; }
	RECT MouseGetMBDragRect() { return m_rcMBDrag; }
	RECT MouseGetRBDragRect() { return m_rcRBDrag; }

	int MouseGetFlag() { return m_nMouseFlag; }
	int MouseGetFlagOld() { return m_nMouseFlagOld; }
};

#endif // end of #define CDXInput..
