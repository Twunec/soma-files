// MyInvData.h: interface for the CMyInvData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYINVDATA_H__A0ECA1A1_E9F8_11D3_B175_00105A735718__INCLUDED_)
#define AFX_MYINVDATA_H__A0ECA1A1_E9F8_11D3_B175_00105A735718__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyInvData  
{
public:
	CMyInvData();
	virtual ~CMyInvData();

	void Init();

	CMyInvData& operator=(CMyInvData& other);

public:
	short m_vIndex;
	BYTE m_vType;//���� Ÿ�� ��� ������ ���ؼ�...
	BYTE m_vArmPos;// ������
	short m_vPicNum;//�׸� ��ȣ..
	BYTE m_vGender;//����
	short m_vMinDamage;		// �ּ� ����
	short m_vMaxDamage;		// �ִ� ����
	short m_vLimitStr;		// �ʿ� Str
	short m_vLimitInt;		// �ʿ� Int
	short m_vLimitSkill;	// �ʿ� ���õ�
	CString m_strMagic;	// ����
	CString m_strSNum;		// S �׸�
	short m_vUsage;
	short m_vMaxUsage;		// ���� �ִ� ���ȸ��
	short m_vOrgMaxUsage;	// ���� �ִ� ���ȸ��
	short m_vSpecial[7];		// Ư�� �ɷ�(Str,Dex,Int,Atk,Def,HP,MP)
	DWORD m_vValue;			// ����
	CString m_vName;
};

#endif // !defined(AFX_MYINVDATA_H__A0ECA1A1_E9F8_11D3_B175_00105A735718__INCLUDED_)
