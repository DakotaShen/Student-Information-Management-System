#pragma once
#include "cgradeset.h"
#include "afxcmn.h"


// CGradeDlg �Ի���

class CGradeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGradeDlg)

public:
	CGradeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGradeDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_GRADE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSNo_Q;
	CString m_strCCount;
	CString m_strCReditS;
	CString m_strCAvg;
	CGradeSet m_rsGradeSet;
	CString m_strConnCondition;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBnQuery();
	CListCtrl m_listDisp;
	afx_msg void OnBnClickedBnExit();
};
