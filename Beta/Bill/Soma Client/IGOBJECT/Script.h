// Script.h: interface for the CScript class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCT_H__4F1571A3_BCDF_11D2_B0A3_0060970DBAD5__INCLUDED_)
#define AFX_SCT_H__4F1571A3_BCDF_11D2_B0A3_0060970DBAD5__INCLUDED_

class CScript
{
public:
	const _SCT_DATA* Get();
	const _SCT_DATA* Get(int index);
	void Release(); // ��ũ��Ʈ �ʱ�ȭ..
	
	int GetQuantity() { return m_Header.nQt; }
	void Load(const char* szFileName);
	CScript();
	virtual ~CScript();

protected:
	_SCT_HEADER m_Header;				// ��������Ʈ ���
	_SCT_DATA* m_pDatas[MAX_SCT];	// ���̸� �����Ͱ� ���� �����̴�.
	int m_nIndex; // ���� ó������ �ε���..
	
	DWORD 	m_dwTickDelay; // ���� �ð� ����
	char		m_szFileName[256]; // �ֱ� �ε��� ���� �̸�..

private:
	void Alloc(int nQt);
};

#endif // !defined(AFX_SCT_H__4F1571A3_BCDF_11D2_B0A3_0060970DBAD5__INCLUDED_)
