// CCourseDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "CCourseDlg.h"
#include "afxdialogex.h"


// CCourseDlg 对话框

IMPLEMENT_DYNAMIC(CCourseDlg, CDialogEx)

CCourseDlg::CCourseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCourseDlg::IDD, pParent)
	, m_strCNo_Q(_T(""))
	, m_strCName_Q(_T(""))
	, m_strCNo(_T(""))
	, m_strCName(_T(""))
	, m_strCRedit(_T(""))
	, m_bAdd(false)
	, m_bEdit(false)
	, m_bEmpty(false)
	, m_bFirst(false)
	, m_bLast(false)
{

}

CCourseDlg::~CCourseDlg()
{
}

void CCourseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CNo_Q, m_strCNo_Q);
	DDX_Text(pDX, IDC_EDIT_CNAME_Q, m_strCName_Q);
	DDX_Text(pDX, IDC_EDIT_CNo, m_strCNo);
	DDX_Text(pDX, IDC_EDIT_CNAME, m_strCName);
	DDX_Text(pDX, IDC_EDIT_CREDIT, m_strCRedit);
}
/*对话框初始化代码（打开对话框时，需要完成的工作包括打开记录集，并根据打开的状态完成记录的显
示及“滚动记录指针”按钮状态和编辑框状态的设置。这些代码应该添加在对话框的初始化函数中*/
BOOL CCourseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_rsCourseSet.Open(AFX_DB_USE_DEFAULT_TYPE);
	if(!m_rsCourseSet.IsOpen())
	{
		AfxMessageBox("数据库打开失败!");
		return TRUE;
	}
	else if(m_rsCourseSet.IsBOF())
	{
		AfxMessageBox("数据集空！");
		m_bEmpty=true;
		ClearEditData();
		SetMoveBNState();
		SetEditState();
	}
	else
	{
		m_bEmpty=false;
		m_rsCourseSet.MoveFirst();
		m_bFirst=true;
		m_bLast=false;
		ReadRecord();
		SetMoveBNState();
		SetEditState();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
//在BEGIN_MESSAGE_MAP()和END_MESSAGE_MAP()之间添加你的消息响应函数,为每个消息处理函数加入一个入口
BEGIN_MESSAGE_MAP(CCourseDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BN_FIRST, &CCourseDlg::OnBnClickedBnFirst)
	ON_BN_CLICKED(IDC_BN_PREV, &CCourseDlg::OnBnClickedBnPrev)
	ON_BN_CLICKED(IDC_BN_NEXT, &CCourseDlg::OnBnClickedBnNext)
	ON_BN_CLICKED(IDC_BN_LAST, &CCourseDlg::OnBnClickedBnLast)
	ON_BN_CLICKED(IDC_BN_QUERY, &CCourseDlg::OnBnClickedBnQuery)
	ON_BN_CLICKED(IDC_BN_ADD, &CCourseDlg::OnBnClickedBnAdd)
	ON_BN_CLICKED(IDC_BN_EDIT, &CCourseDlg::OnBnClickedBnEdit)
	ON_BN_CLICKED(IDC_BN_DELETE, &CCourseDlg::OnBnClickedBnDelete)
	ON_BN_CLICKED(IDC_BN_SAVE, &CCourseDlg::OnBnClickedBnSave)
	ON_BN_CLICKED(IDC_BN_CANCEL, &CCourseDlg::OnBnClickedBnCancel)
	ON_BN_CLICKED(IDC_BN_EXIT, &CCourseDlg::OnBnClickedBnExit)
END_MESSAGE_MAP()


// CCourseDlg 消息处理程序

//清空对话框中显示学生信息的编辑框控件
void CCourseDlg::ClearEditData(void)
{
	m_strCNo="";
	m_strCName="";
	m_strCRedit="";
	
	UpdateData(FALSE);
	return;
}
//将域数据成员的值传递给对话框控件显示出来

void CCourseDlg::ReadRecord(void)
{
	m_strCNo=m_rsCourseSet.m_CNo;
	m_strCName=m_rsCourseSet.m_CName;
	m_strCRedit.Format("%d",m_rsCourseSet.m_CRedit);
	
	UpdateData(FALSE);
	return;
}

//将控件中显示的信息传递给域数据成员
void CCourseDlg::WriteRecord(void)
{
	UpdateData(TRUE);

	m_rsCourseSet.m_CNo=m_strCNo;
	m_rsCourseSet.m_CName=m_strCName;
	
	int nRedit=atoi(m_strCRedit);
	m_rsCourseSet.m_CRedit=nRedit;
	return;
	
}



//根据记录集是否为空，记录指针的位置及对数据库的操作类型，来设置“滚动记录指针”按钮的使用状态。
void CCourseDlg::SetMoveBNState(void)
{
	CWnd *pWnd;
	if(m_bEmpty||m_bEdit)
	{
		pWnd=GetDlgItem(IDC_BN_FIRST);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_BN_PREV);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_BN_LAST);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_BN_NEXT);
		pWnd->EnableWindow(FALSE);
		return;
	}
	if(m_bFirst)
	{
		pWnd=GetDlgItem(IDC_BN_FIRST);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_BN_PREV);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_BN_LAST);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_BN_NEXT);
		pWnd->EnableWindow(TRUE);
	}
	else if(m_bLast)
	{
		pWnd=GetDlgItem(IDC_BN_FIRST);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_BN_PREV);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_BN_LAST);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_BN_NEXT);
		pWnd->EnableWindow(FALSE);
	}
	else
	{
		pWnd=GetDlgItem(IDC_BN_FIRST);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_BN_PREV);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_BN_LAST);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_BN_NEXT);
		pWnd->EnableWindow(TRUE);
	}
	return;
}

//根据数据库的操作类型设置编辑框控件的可编辑状态
void CCourseDlg::SetEditState(void)
{
	CWnd *pWnd;
	if(m_bEdit)
	{
		pWnd=GetDlgItem(IDC_BN_ADD);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_BN_EDIT);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_BN_DELETE);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_BN_QUERY);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_BN_SAVE);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_BN_CANCEL);
		pWnd->EnableWindow(TRUE);

		pWnd=GetDlgItem(IDC_EDIT_CNo);
		if(m_bAdd)
			pWnd->EnableWindow(TRUE);
		else
			pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_EDIT_CNAME);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_EDIT_CREDIT);
		pWnd->EnableWindow(TRUE);	
	}
	else
	{
		pWnd=GetDlgItem(IDC_BN_ADD);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_BN_EDIT);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_BN_DELETE);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_BN_QUERY);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_BN_SAVE);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_BN_CANCEL);
		pWnd->EnableWindow(FALSE);

		pWnd=GetDlgItem(IDC_EDIT_CNo);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_EDIT_CNAME);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_EDIT_CREDIT);
		pWnd->EnableWindow(FALSE);
		
	}
	return;
}




/*按钮功能实现代码， 在对话框模板资源中，双击按钮控件，在其对应的函数中编写单击事件处理代码*/

//上一条按钮
void CCourseDlg::OnBnClickedBnFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsCourseSet.MoveFirst();
	m_bFirst=true;
	m_bLast=false;
	SetMoveBNState();
	ReadRecord();

}

//第一条按钮
void CCourseDlg::OnBnClickedBnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst=false;
	m_bLast=false;
	m_rsCourseSet.MovePrev();
	if(m_rsCourseSet.IsBOF())
	{
		m_rsCourseSet.MoveFirst();
		m_bFirst=TRUE;
	}
	SetMoveBNState();
	ReadRecord();

}

//下一条按钮
void CCourseDlg::OnBnClickedBnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst=false;
	m_bLast=false;
	m_rsCourseSet.MoveNext();
	if(m_rsCourseSet.IsEOF())
	{
		m_rsCourseSet.MoveLast();
		m_bLast=true;
	}
	SetMoveBNState();
	ReadRecord();
}

//末一条按钮
void CCourseDlg::OnBnClickedBnLast()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsCourseSet.MoveLast();
	m_bFirst=false;
	m_bLast=true;
	SetMoveBNState();
	ReadRecord();

}
//查询按钮

void CCourseDlg::OnBnClickedBnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_strCNo_Q.IsEmpty() && m_strCName_Q.IsEmpty())
	{	
		m_rsCourseSet.m_strFilter="";
		m_rsCourseSet.Requery();
		if(m_rsCourseSet.IsBOF())
		{
			AfxMessageBox("数据集空！");
			m_bEmpty=true;
			ClearEditData();
			SetMoveBNState();
		}
		else
		{
			m_bEmpty=false;
			m_rsCourseSet.MoveFirst();
			m_bFirst=true;
			m_bLast=false;
			ReadRecord();
			SetMoveBNState();
		}
		return;
	}
	BOOL mbCNoQInput=FALSE;
	if(!m_strCNo_Q.IsEmpty())
	{
		m_rsCourseSet.m_strFilter="CNo='"+m_strCNo_Q;
		m_rsCourseSet.m_strFilter=m_rsCourseSet.m_strFilter+"'";
		
		mbCNoQInput=TRUE;	
	}
	if(!m_strCName_Q.IsEmpty())
	{
		if(mbCNoQInput)
		{
			m_rsCourseSet.m_strFilter=m_rsCourseSet.m_strFilter
			                        +" AND CName='";
			m_rsCourseSet.m_strFilter=m_rsCourseSet.m_strFilter
			                        +m_strCName_Q;
			m_rsCourseSet.m_strFilter=m_rsCourseSet.m_strFilter
									+"'";
		}	                        							
		else
		{
			m_rsCourseSet.m_strFilter="CName='"+m_strCName_Q;
			m_rsCourseSet.m_strFilter=m_rsCourseSet.m_strFilter+"'";

		}
		
	}
	m_rsCourseSet.Requery();
	if(m_rsCourseSet.IsEOF())
	{
		AfxMessageBox("没有查到相关记录！");
		m_bEmpty=true;
		ClearEditData();
		SetMoveBNState();
	}
	else
	{
		m_bEmpty=false;
		m_rsCourseSet.MoveFirst();
		m_bFirst=true;
		ReadRecord();
		SetMoveBNState();
	}	

}

//添加按钮
void CCourseDlg::OnBnClickedBnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	ClearEditData();
	m_bEdit=true;
	m_bAdd=true;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd=GetDlgItem(IDC_EDIT_CNo);
	pWnd->SetFocus();
}

//修改按钮
void CCourseDlg::OnBnClickedBnEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bEdit=true;
	m_bAdd=false;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd=GetDlgItem(IDC_EDIT_CNAME);
	pWnd->SetFocus();
}

//删除按钮
void CCourseDlg::OnBnClickedBnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if(AfxMessageBox("确定要删除此条记录吗？",MB_YESNO)!=IDYES)
		return;
	m_rsCourseSet.Delete();
	//m_rsSCChoiceSet.MoveNext();
	m_rsCourseSet.Requery();
	if(m_rsCourseSet.IsBOF())
	{
		AfxMessageBox("表中已没有记录了！");
		ClearEditData();
		m_bEmpty=true;
		SetMoveBNState();
		return;
	}
	m_bFirst=true;
	m_bLast=false;
	ReadRecord();
	SetMoveBNState();
}

//保存按钮
void CCourseDlg::OnBnClickedBnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if(m_strCNo.IsEmpty() || m_strCName.IsEmpty())
	{
		AfxMessageBox("请输入相应数据！");
		CWnd *pWnd;
		pWnd=GetDlgItem(IDC_EDIT_CNo);
		pWnd->SetFocus();
		return;
	}
	if(m_bAdd)
	{
		m_rsCourseSet.AddNew();
	}
	else
	{
		m_rsCourseSet.Edit();
	}
	WriteRecord();
	m_rsCourseSet.Update();
	m_rsCourseSet.Requery();
	m_rsCourseSet.MoveFirst();
	m_bFirst=true;
	m_bLast=false;
	m_bAdd=false;
	m_bEdit=false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}

//取消按钮
void CCourseDlg::OnBnClickedBnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bAdd=false;
	m_bEdit=false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CCourseDlg::OnBnClickedBnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
