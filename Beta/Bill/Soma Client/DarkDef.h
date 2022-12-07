#ifndef _DARKDEF_H_
#define _DARKDEF_H_

#define ITEM_ALL		0
#define	ITEM_WOMAN		1
#define ITEM_MAN		2

class ITEM_ME
{
public:
	int			m_vIndex;			// ��ȣ
	BYTE		m_vType;			// ����
	BYTE		m_vGender;			// ����(0:�߼�, 1:����, 2:����)
	int			m_vPicNum;			// �׸� ��ȣ
	short		m_vMinDamage;		// �ּ� ����
	short		m_vMaxDamage;		// �ִ� ����
	short		m_vLimitStr;		// �ּ� Str
	short		m_vLimitInt;		// �ּ� Int
	short		m_vLimitSkill;		// �ּ� ���õ�
	CString		m_strMagic;			// ���� �̸�
	CString		m_strSNum;			// S�׸�
	short		m_vSpecial[7];		// Ư�� �ɷ�(Str,Dex,Int,Atk,Def,HP,MP)
	DWORD		m_vValue;			// ����
	CString		m_vName;		// �̸�
	int			m_vUsage;			// ���ȸ��
	short		m_vMaxUsage;		// �ִ� ���ȸ��
	short		m_vOrgMaxUsage;		// ���� �ִ� ���ȸ��

	ITEM_ME()
	{
		m_vIndex = m_vPicNum = -1;
		m_vGender = ITEM_ALL;
		m_vType = 0;
		m_vUsage = m_vMaxUsage = m_vOrgMaxUsage = 0;
		m_vMinDamage = 0;
		m_vMaxDamage = 0;
		m_vName.Empty();
		for(int i = 0; i < 7; i++)
		{
			m_vSpecial[i] = 0;
		}
		m_vValue = 0;
	};
};

class ITEM_SHOP
{
public:
	int				m_vItemNumber;		// ��ȣ
	short			m_vUsage;			// ���ȸ��
	short			m_vMaxUsage;		// �ִ� ���ȸ��
	short			m_vOrgMaxUsage;		// ���� �ִ� ���ȸ��
	int				m_vPicNum;			// �׸� ��ȣ
	BYTE			m_vGender;			// ����(0:�߼�, 1:����, 2:����)
	short			m_vMinDamage;		// �ּ� ����
	short			m_vMaxDamage;		// �ִ� ����
	short			m_vLimitStr;		// �ּ� Str
	short			m_vLimitInt;		// �ּ� Int
	short			m_vLimitSkill;		// �ּ� ���õ�
	CString			m_strMagic;			// ���� �̸�
	CString			m_strSNum;			// S�׸�
	short			m_vSpecial[7];		// Ư�� �ɷ�(Str,Dex,Int,Atk,Def,HP,MP)
	DWORD			m_vValue;			// ��
	CString			m_vName;		// �̸�

	ITEM_SHOP()
	{
		m_vGender = ITEM_ALL;
		m_vItemNumber = m_vPicNum = m_vValue = 0;
		m_vUsage = m_vMaxUsage = m_vOrgMaxUsage = 0;
		m_vMinDamage = 0;
		m_vMaxDamage = 0;
		m_vName.Empty();
		for(int i = 0; i < 7; i++)
		{
			m_vSpecial[i] = 0;
		}
	};
};

class ITEM_INV
{
public:
	int			m_vPicNum;			// �׸� ��ȣ
	BYTE		m_vType;			// ����
	BYTE		m_vArmPos;			// ������
	BYTE		m_vGender;			// ����(0:�߼�, 1:����, 2:����)
	short		m_vMinDamage;		// �ּ� ����
	short		m_vMaxDamage;		// �ִ� ����
	short		m_vLimitStr;		// �ּ� Str
	short		m_vLimitInt;		// �ּ� Int
	short		m_vLimitSkill;		// �ּ� ���õ�
	CString		m_strMagic;			// ���� �̸�
	CString		m_strSNum;			// S�׸�
	short		m_vSpecial[7];		// Ư�� �ɷ�(Str,Dex,Int,Atk,Def,HP,MP)
	CString		m_vName;		// �̸�
	short		m_vUsage;			// ���ȸ��
	short		m_vMaxUsage;		// �ִ� ���ȸ��
	short		m_vOrgMaxUsage;		// ���� �ִ� ���ȸ��

	ITEM_INV()
	{
		m_vType = 0;
		m_vGender = ITEM_ALL;
		m_vUsage = m_vMaxUsage = m_vOrgMaxUsage = 0;
		m_vArmPos = 0;
		m_vMinDamage = 0;
		m_vMaxDamage = 0;
		m_vPicNum = -1;
		m_vName.Empty();
		for(int i = 0; i < 7; i++)
		{
			m_vSpecial[i] = 0;
		}
	};
};

class ITEM_STORAGE
{
public:
	int			m_vIndex;			// ������ �ε���
	int			m_vPicNum;			// ������ �׸� ��ȣ
	BYTE		m_vType;			// ����
	BYTE		m_vGender;			// ����(0:�߼�, 1:����, 2:����)
	short		m_vMinDamage;		// �ּ� ����
	short		m_vMaxDamage;		// �ִ� ����
	short		m_vLimitStr;		// �ּ� Str
	short		m_vLimitInt;		// �ּ� Int
	short		m_vLimitSkill;		// �ּ� ���õ�
	CString		m_strMagic;			// ���� �̸�
	CString		m_strSNum;			// S�׸�
	short		m_vSpecial[7];		// Ư�� �ɷ�(Str,Dex,Int,Atk,Def,HP,MP)
	short		m_vUsage;			// ������ ��� ȸ��
	short		m_vMaxUsage;		// �ִ� ���ȸ��
	short		m_vOrgMaxUsage;		// ���� �ִ� ���ȸ��
	CString		m_vName;		// ������ �̸�

	ITEM_STORAGE()
	{
		m_vGender = ITEM_ALL;
		m_vType = 0;
		m_vMinDamage = 0;
		m_vMaxDamage = 0;
		m_vIndex = m_vPicNum = -1;
		m_vUsage = m_vMaxUsage = m_vOrgMaxUsage = 0;
		m_vName.Empty();
		for(int i = 0; i < 7; i++)
		{
			m_vSpecial[i] = 0;
		}
	};
};

class ITEM_DETAIL
{
public:
	int			m_vIndex;			// ������ �ε���
	int			m_vPicNum;			// �׸� ��ȣ
	BYTE		m_vType;			// ����
	BYTE		m_vArmPos;			// ������
	BYTE		m_vGender;			// ����(0:�߼�, 1:����, 2:����)
	short		m_vMinDamage;		// �ּ� ����
	short		m_vMaxDamage;		// �ִ� ����
	short		m_vLimitStr;		// �ּ� Str
	short		m_vLimitInt;		// �ּ� Int
	short		m_vLimitSkill;		// �ּ� ���õ�
	CString		m_strMagic;			// ���� �̸�
	CString		m_strSNum;			// S�׸�
	short		m_vSpecial[7];		// Ư�� �ɷ�(Str,Dex,Int,Atk,Def,HP,MP)
	short		m_vUsage;			// ��� ����
	short		m_vMaxUsage;		// �ִ� ���ȸ��
	short		m_vOrgMaxUsage;		// ���� �ִ� ���ȸ��
	CString		m_vName;		// �̸�

	ITEM_DETAIL()
	{
		m_vGender = ITEM_ALL;
		m_vMinDamage = m_vMaxDamage = 0;
		m_vType = m_vArmPos = 0;
		m_vIndex = m_vPicNum = -1;
		m_vUsage = m_vMaxUsage = m_vOrgMaxUsage = 0;
		for(int i = 0; i < 7; i++)
		{
			m_vSpecial[i] = 0;
		}
		m_vName.Empty();
	};
};

class ITEM_AUCTION
{
public:
	int			m_vIndex;			// �ε���
	BYTE		m_vType;			// ����
	BYTE		m_vGender;			// ����(0:�߼�, 1:����, 2:����)
	short		m_vMinDamage;		// �ּ� ����
	short		m_vMaxDamage;		// �ִ� ����
	short		m_vWeight;			// ����
	short		m_vPicNum;			// �׸� ��ȣ
	CString		m_vName;			// �̸�
	short		m_vLimitStr;		// �ʿ� Str
	short		m_vLimitInt;		// �ʿ� Int
	short		m_vLimitSkill;		// �ʿ� ���õ�
	CString		m_strMagic;			// ���� �̸�
	CString		m_strSNum;			// S�׸�
	short		m_vUsage;			// ���ȸ��(������)
	short		m_vMaxUsage;		// �ִ� ���ȸ��
	short		m_vOrgMaxUsage;		// ���� �ִ� ���ȸ��
	short		m_vSpecial[7];		// Ư�� �ɷ�(Str,Dex,Int,Atk,Def,HP,MP)
	DWORD		m_vCost;			// ��� ����
	CString		m_vRegistrant;		// ����

	ITEM_AUCTION()
	{
		m_vIndex = -1;
		m_vType = 0;
		m_vGender = ITEM_ALL;
		m_vMinDamage = m_vMaxDamage = m_vWeight = m_vPicNum = -1;
		m_vLimitStr = m_vLimitInt = m_vLimitSkill = 0;
		m_vUsage = m_vMaxUsage = m_vOrgMaxUsage = 0;
		for(int i = 0; i < 7; i++)
		{
			m_vSpecial[i] = 0;
		}
		m_vCost = 0;
	};
};

typedef CTypedPtrArray<CPtrArray, ITEM_ME *> CItemMeArray;
typedef CMap< int, int, ITEM_ME *, ITEM_ME *&> CItemMeMap;
typedef CMap< int, int, ITEM_INV *, ITEM_INV *&> CItemInvMap;
typedef CTypedPtrArray<CPtrArray, ITEM_DETAIL *> CItemDetailArray;
typedef CTypedPtrArray<CPtrArray, ITEM_SHOP *> CItemShopArray;
typedef CTypedPtrArray<CPtrArray, ITEM_STORAGE *> CItemStorageArray;
typedef CTypedPtrArray<CPtrArray, ITEM_AUCTION *> CItemAuctionArray;

#define TYPE_SWORD				0
#define TYPE_AXE				1
#define TYPE_BOW				2
#define TYPE_SPEAR				3
#define TYPE_KNUCKLE			4
#define TYPE_STAFF				5
#define TYPE_ACC				8
#define TYPE_POTION				9
#define TYPE_FOOD				10
#define TYPE_MTR				11
#define TYPE_TOKEN				12

#define MTR_METAL				1
#define MTR_WOOD				2
#define MTR_LEATHER				3
#define MTR_BONE				4
#define MTR_CLOTH				5
#define MTR_PLANTS				6
#define MTR_MEAT				7
#define MTR_POWDER				8
#define MTR_SPICE				9
#define MTR_GEMS				10
#define MTR_ETC					11

#define TYPE_WEAPON				6
#define TYPE_ARMOR				7

#define ARM_HEAD				0
#define ARM_EAR					1
#define ARM_NECK				2
#define ARM_CHEST				3
#define ARM_LEG					4
#define ARM_FOOT				5
#define ARM_RHAND				6
#define ARM_LHAND				7
#define ARM_HANDS				8
#define ARM_WRIST				9
#define ARM_USE					10
#define ARM_CON					11

#define BELT_INV				0
#define BASIC_INV				1

#define INFO_ALL				0xff
#define INFO_TYPE				0x01
#define INFO_ARM				0x02
#define INFO_PICNUM				0x04
#define INFO_DUR				0x08
#define INFO_NAME				0x10
#define INFO_DAMAGE				0x20
#define INFO_LIMIT				0x40
#define INFO_SPECIAL			0x80

#define DEFAULT_FONT			"����ü"
#endif