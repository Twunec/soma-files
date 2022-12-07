// PacketParser.h: interface for the CPacketParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKETPARSER_H__85110601_4E72_11D3_8423_00105A6B96E7__INCLUDED_)
#define AFX_PACKETPARSER_H__85110601_4E72_11D3_8423_00105A6B96E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CChildView;
class CUser;
#include "SocketMng.h"

class CPacketParser  //��Ŷ �м���
{
public:
	void			ChangeItemInfo(PBYTE bypData);						// ������ ���� ��ȭ
	void			ChatParse(PBYTE bypData);							//ä�õ�����
	void			AttackProcess(PBYTE bypData);						//����
	void			ArrowAttackProcess(PBYTE bypData);					//ȭ����� 
	void			ZoneChange(int uid, int x, int y, int mapnum);		//Zone�� �̵�
	void			MoveRequest(CUser *pUserMe, CPoint ptDstCellPos, int FindStep = 20);	//�̵� ��û
	void			MoveProcess(PBYTE bypData, BYTE kind);				//�̵� ó��
	void			LoginProcess(PBYTE bypData);						//Login ó��

	BOOL			PacketProcess(PBYTE bypData, int size);				//�ʱ� ��Ŷó���Լ�(���� �Լ���� �б��)
	BOOL			SessionPacketProcess(PBYTE bypData, int size);		//Session���� ������϶� ó��
	
	//��Ŷ���� ������ �Լ�
	static	short&	GetShort(PBYTE bypData, int &offset);				
	static	int&	GetInt(PBYTE bypData, int &offset);
	static	BYTE&	GetByte(PBYTE bypData, int &offset);
	static	WORD&	GetWord(PBYTE bypData, int &offset);
	static	DWORD&	GetDword(PBYTE bypData, int &offset);
	static	void	GetString(PBYTE bypData, int &offset, PBYTE dest, int len);

	//��Ŷ�� ���鶧 ����ϴ� �Լ�
	static	void	SetShort(PBYTE bypData, int &offset, short data);
	static	void	SetInt(PBYTE bypData, int &offset, int data);
	static	void	SetByte(PBYTE bypData, int &offset, BYTE data);	
	static	void	SetWord(PBYTE bypData, int &offset, WORD data);
	static	void	SetDword(PBYTE bypData, int &offset, DWORD data);
	static	void	SetString(PBYTE bypData, int &offset, PBYTE sor, int len);
	static  CPoint  Conv2ServerMapPos(CPoint p);//�������忡�� �����°�..
	static  CPoint  Conv2ClientMapPos(CPoint p);//�������忡�� �����°�..


	CPacketParser();
	virtual ~CPacketParser();

	//Session���� ����ΰ� Server���� ����ΰ� ����
	void			SetSessionLoginStatus(BOOL tf) {m_bIsSessionLogin = tf;}
	BOOL			GetSessionLoginStatus() {return m_bIsSessionLogin;}
public:
	void ConnectInfoProcess(PBYTE bypData);
	void BattleModeProcess(PBYTE bypData);
	void MoveRunRequest(CUser *pUserMe, CPoint ptDstCellPos, int FindStep = 20);
	void Magic_CircleProcess(PBYTE bypData);
	void Magic_ReadyProcess(PBYTE bypData);
	void Magic_PoisonProcess(PBYTE bypData);
	void CharStateChange(PBYTE bypData);
	void AcountLoginProcess(PBYTE bypData);
	void DeadProcess(PBYTE bypData);
	void SetTimeProcess(PBYTE bypData);
	void ShowMagicProcess(PBYTE bypData);
	void ArrowMagicRailAttackProcess(PBYTE bypData);
	void ApplyWeight(PBYTE bypData);
	CChildView*		m_bpConnectedView;

	void OpenGuildMenu(PBYTE bypData);

protected:
	BOOL			m_bIsSessionLogin;

	bool            m_bPathFind;//�켮..
};

inline short& CPacketParser::GetShort(PBYTE bypData, int &offset)
{
	return SocketMng::Parse_GetShort(bypData, offset);
}

inline int& CPacketParser::GetInt(PBYTE bypData, int &offset)
{
	offset += 4;
	return *(int*)(bypData+offset-4);
}

inline BYTE& CPacketParser::GetByte(PBYTE bypData, int &offset)
{
	return SocketMng::Parse_GetByte(bypData, offset);
}

inline WORD& CPacketParser::GetWord(PBYTE bypData, int &offset)
{
	return SocketMng::Parse_GetWord(bypData, offset);
}

inline DWORD& CPacketParser::GetDword(PBYTE bypData, int &offset)
{
	return SocketMng::Parse_GetDword(bypData, offset);
}

inline void CPacketParser::GetString(PBYTE bypData, int &offset, PBYTE dest, int len)
{
	SocketMng::Parse_GetString(bypData, offset, dest, len);
}

inline void CPacketParser::SetShort(PBYTE bypData, int &offset, short data)
{
	SocketMng::MP_AddShort(bypData, offset, data);
}

inline void CPacketParser::SetInt(PBYTE bypData, int &offset, int data)
{
	SocketMng::MP_AddInt(bypData, offset, data);
}

inline void CPacketParser::SetByte(PBYTE bypData, int &offset, BYTE data)
{
	SocketMng::MP_AddByte(bypData, offset, data);
}

inline void	CPacketParser::SetString(PBYTE bypData, int &offset, PBYTE pSor, int len)
{
	SocketMng::MP_AddString(bypData, offset, pSor, len);
}

inline void CPacketParser::SetWord(PBYTE bypData, int &offset, WORD data)
{
	SocketMng::MP_AddWord(bypData, offset, data);
}

inline void CPacketParser::SetDword(PBYTE bypData, int &offset, DWORD data)
{
	SocketMng::MP_AddDword(bypData, offset, data);
}

#endif // !defined(AFX_PACKETPARSER_H__85110601_4E72_11D3_8423_00105A6B96E7__INCLUDED_)
