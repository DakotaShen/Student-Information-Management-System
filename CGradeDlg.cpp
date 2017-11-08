// CGradeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "CGradeDlg.h"
#include "afxdialogex.h"


// CGradeDlg 对话框

IMPLEMENT_DYNAMIC(CGradeDlg, CDialogEx)

CGradeDlg::CGradeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGradeDlg::IDD, pParent)
	, m_strSNo_Q(_T(""))
	, m_strCCount(_T(""))
	, m_strCReditS(_T(""))
	, m_strCAvg(_T(""))
	, m_strConnCondition(_T(""))
{

}

CGradeDlg::~CGradeDlg()
{
}

void CGradeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SNo_Q, m_strSNo_Q);
	DDX_Text(pDX, IDC_EDIT_CCOUNT, m_strCCount);
	DDX_Text(pDX, IDC_EDIT_CReditS, m_strCReditS);
	DDX_Text(pDX, IDC_EDIT_CAVG, m_strCAvg);
	DDX_Control(pDX, IDC_LIST_DISP, m_listDisp);
}


BEGIN_MESSAGE_MAP(CGradeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BN_QUERY, &CGradeDlg::OnBnClickedBnQuery)
	ON_BN_CLICKED(IDC_BN_EXIT, &CGradeDlg::OnBnClickedBnExit)
END_MESSAGE_MAP()


// CGradeDlg 消息处理程序


BOOL CGradeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// TODO:  在此添加额外的初始化
	m_strConnCondition="STUDENT.SNo=SCCHOICE.SNo AND COURSE.CNo=SCCHOICE.CNo";
	m_rsGradeSet.m_strFilter=m_strConnCondition;
	if(!m_rsGradeSet.Open(AFX_DB_USE_DEFAULT_TYPE))
	{
		AfxMessageBox("数据库打开失败！");
		return TRUE;
	}
	m_listDisp.InsertColumn(0,"姓名");
	m_listDisp.InsertColumn(1,"课程号");
	m_listDisp.InsertColumn(2,"课程名");
	m_listDisp.InsertColumn(3,"学分");
	m_listDisp.InsertColumn(4,"成绩");

	RECT rect;
	m_listDisp.GetWindowRect(&rect);
	int wid=rect.right-rect.left;
	m_listDisp.SetColumnWidth(0,wid/5);
	m_listDisp.SetColumnWidth(1,wid/5);
	m_listDisp.SetColumnWidth(2,wid/5);
	m_listDisp.SetColumnWidth(3,wid/5);
	m_listDisp.SetColumnWidth(4,wid/5);

	m_listDisp.SetExtendedStyle(LVS_EX_FULLROWSELECT
		|LVS_EX_GRIDLINES);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	
}


void CGradeDlg::OnBnClickedBnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	
	m_rsGradeSet.m_strFilter=m_strConnCondition+" AND STUDENT.SNo='"+m_strSNo_Q+"'";
	m_rsGradeSet.Requery();	

	m_listDisp.DeleteAllItems();
	m_listDisp.SetRedraw(FALSE);
	UpdateData(TRUE);
	if(m_strSNo_Q.IsEmpty())
	{
		AfxMessageBox("请输入学生的学号!");
		m_strCCount="";
		m_strCReditS="";
		m_strCAvg="";

		UpdateData(FALSE);
		return;
	}

	if(m_rsGradeSet.IsBOF())
	{
		AfxMessageBox("该学生没有选课！");
		m_strCCount="";
		m_strCReditS="";
		m_strCAvg="";

		UpdateData(FALSE);
		return;
	}
	

	m_rsGradeSet.MoveFirst();
	int i=0;
	int iCCount=0;
	int iCReditS=0;
	int iCSum=0;
	CString strNum;
	while(!m_rsGradeSet.IsEOF())
	{
		m_listDisp.InsertItem(i,m_rsGradeSet.m_STUDENTSName);
		m_listDisp.SetItemText(i,1,m_rsGradeSet.m_COURSECNo);
		m_listDisp.SetItemText(i,2,m_rsGradeSet.m_COURSECName);
		strNum.Format("%d",m_rsGradeSet.m_COURSECRedit);
		m_listDisp.SetItemText(i,3,strNum);
		strNum.Format("%d",m_rsGradeSet.m_SCCHOICESCGrade);
		m_listDisp.SetItemText(i,4,strNum);

		iCCount++;
		iCReditS+=m_rsGradeSet.m_COURSECRedit;
		iCSum+=m_rsGradeSet.m_SCCHOICESCGrade;
		
		m_rsGradeSet.MoveNext();
		i++;
	}
	m_listDisp.SetRedraw(TRUE);
	m_strCCount.Format("%d",iCCount);
	m_strCReditS.Format("%d",iCReditS);
	m_strCAvg.Format("%.2f",(float)iCSum/iCCount);
	UpdateData(FALSE);
}

void CGradeDlg::OnBnClickedBnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
