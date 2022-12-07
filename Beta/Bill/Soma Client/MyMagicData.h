// MyMagicData.h: interface for the CMyMagicData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MyMagicData_H__A0ECA1A1_E9F8_11D3_B175_00105A735718__INCLUDED_)
#define AFX_MyMagicData_H__A0ECA1A1_E9F8_11D3_B175_00105A735718__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMyMagicData  
{
public:
	CMyMagicData();
	virtual ~CMyMagicData();

public:
	void Init();

	short m_vNumber;	// ���� ��ȣ
	BYTE m_vMethod;		// ���� ���� ���
	BYTE m_vCharOrAxis;	// ���� ���� ���(ĳ���� ������� ��ǥ �������)
	short m_vStartTime;	// ���� �ߵ� �ð�
	BYTE m_vType;		// ���� Ÿ��
	BYTE m_vTgtMethod;	// ���� ��ǥ Ÿ��
	CString m_vName;	// ���� �̸�
	CString m_vExplain;	// ���� ����
	short m_vDistance;	// ���� �Ÿ�
	short m_vUseMp;		// ������ ���ҷ�
	int m_vUseTime;		// ���� ���� �ð�
	short m_vDamage;	// ���� ����
	short m_vGamePic;	// ���ӻ� ���Ǵ� �׸� ��ȣ
};

#endif // !defined(AFX_MyMagicData_H__A0ECA1A1_E9F8_11D3_B175_00105A735718__INCLUDED_)
