#pragma once
#include "CSCChoiceSet.h"
#include "afxwin.h"


// CSCChoiceDlg 对话框

class CSCChoiceDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSCChoiceDlg)

public:
	CSCChoiceDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSCChoiceDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SCCHOICE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	bool m_bAdd;
	bool m_bEdit;
	bool m_bEmpty;
	bool m_bFirst;
	bool m_bLast;
	CSCChoiceSet m_rsSCChoiceSet;
	void ClearEditData(void);
	void ReadRecord(void);
	void WriteRecord(void);
	void SetMoveBNState(void);
	void SetEditState(void);
	//CEdit m_strSNo_Q;
	CString m_strSNo_Q;
	CString m_strCNo_Q;
	CString m_strSNo;
	CString m_strCNo;
	CString m_strSCGrade;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBnFirst();
	afx_msg void OnBnClickedBnPrev();
	afx_msg void OnBnClickedBnNext();
	afx_msg void OnBnClickedBnLast();
	afx_msg void OnBnClickedBnQuery();
	afx_msg void OnBnClickedBnAdd();
	afx_msg void OnBnClickedBnEdit();
	afx_msg void OnBnClickedBnDelete();
	afx_msg void OnBnClickedBnSave();
	afx_msg void OnBnClickedBnCancel();
	afx_msg void OnBnClickedBnExit();
};
