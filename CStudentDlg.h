#pragma once
#include "CStudentSet.h"

// CStudentDlg 对话框

class CStudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentDlg)

public:
	CStudentDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CStudentDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_STUDENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_strSNo_Q;
	CString m_strSNAME_Q;
	CString m_strSNo;
	CString m_strSName;
	CString m_strSSex;
	CString m_strSMajor;
	CString m_strSBDate;
	CString m_strSSDate;
	bool m_bAdd;
	bool m_bEdit;
	bool m_bEmpty;
	bool m_bFirst;
	bool m_bLast;
	CStudentSet m_rsStudentSet;
	void ClearEditData(void);
	void ReadRecord(void);
	void WriteRecord(void);
	void SetMoveBNState(void);
	void SetEditState(void);
	afx_msg void OnBnClickedBnQuery();
	afx_msg void OnBnClickedBnFirst();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBnPrev();
	afx_msg void OnBnClickedBnNext();
	afx_msg void OnBnClickedBnLast();
	afx_msg void OnBnClickedBnAdd();
	afx_msg void OnBnClickedBnEdit();
	afx_msg void OnBnClickedBnDelete();
	afx_msg void OnBnClickedBnSave();
	afx_msg void OnBnClickedBnCancel();
	afx_msg void OnBnClickedBnExit();
	
};
