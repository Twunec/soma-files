#ifndef _OBJECTCLASS_H_
#define _OBJECTCLASS_H_

#define		AREA_CTRL		0
#define		BTN_CTRL		1
#define		BTN_CTRL_EX		2

class MAreaCtrl
{
public:
	CRect	m_vRect;
	
	BOOL	m_bFocus;
	int		m_vSpec;
	int		m_vIndex;

	MAreaCtrl();

	virtual void	Save(CArchive& ar);
	virtual void	Load(CArchive& ar);
};

class MBtnCtrl : public MAreaCtrl
{
public:
	CRect	m_vFocusRect;		// ��Ŀ��
	CRect	m_vDownRect;		// �ٿ�.
	BOOL	m_bTransparent;		// Transparent ���
	int		m_vStyle;			// ��ư ��Ÿ��(TOGGLE, PUSH, ...)
	int		m_vState;

	MBtnCtrl();

	virtual void	Save(CArchive& ar);
	virtual void	Load(CArchive& ar);
};

class MBtnCtrlEx : public MAreaCtrl
{
public:
	CRect	m_vNormalRect;		// ����
	CRect	m_vFocusRect;		// ��Ŀ��
	CRect	m_vDownRect;		// �ٿ�.
	BOOL	m_bTransparent;		// Transparent ���
	int		m_vStyle;			// ��ư ��Ÿ��(TOGGLE, PUSH, ...)
	int		m_vState;

	MBtnCtrlEx();

	virtual void	Save(CArchive& ar);
	virtual void	Load(CArchive& ar);
};

class MRectManager
{
public:
	CRect		*m_pRect;
	MAreaCtrl	*m_pCtrl;
	int			m_vIndex;

	MRectManager();
};

typedef CTypedPtrArray<CPtrArray, MBtnCtrl*> CBtnCtrlArray;
typedef CTypedPtrArray<CPtrArray, MBtnCtrlEx*> CBtnCtrlExArray;
typedef CTypedPtrArray<CPtrArray, MAreaCtrl*> CAreaCtrlArray;
typedef CTypedPtrArray<CPtrArray, MRectManager*> CRectManagerArray;

#endif