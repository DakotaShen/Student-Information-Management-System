// CStudentDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "CStudentDlg.h"
#include "afxdialogex.h"


// CStudentDlg �Ի���

IMPLEMENT_DYNAMIC(CStudentDlg, CDialogEx)

CStudentDlg::CStudentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CStudentDlg::IDD, pParent)
	, m_strSNo_Q(_T(""))
	, m_strSNAME_Q(_T(""))
	, m_strSNo(_T(""))
	, m_strSName(_T(""))
	, m_strSSex(_T(""))
	, m_strSMajor(_T(""))
	, m_strSBDate(_T(""))
	, m_strSSDate(_T(""))
	, m_bAdd(false)
	, m_bEdit(false)
	, m_bEmpty(false)
	, m_bFirst(false)
	, m_bLast(false)
{

}

CStudentDlg::~CStudentDlg()
{
}

void CStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SNo_Q, m_strSNo_Q);
	DDX_Text(pDX, IDC_EDIT_SNAME_Q, m_strSNAME_Q);
	DDX_Text(pDX, IDC_EDIT_SNo, m_strSNo);
	DDX_Text(pDX, IDC_EDIT_SNAME, m_strSName);
	DDX_Text(pDX, IDC_EDIT_SSEX, m_strSSex);
	DDX_Text(pDX, IDC_EDIT_SMAJOR, m_strSMajor);
	DDX_Text(pDX, IDC_EDIT_SBDATE, m_strSBDate);
	DDX_Text(pDX, IDC_EDIT_SSDATE, m_strSSDate);
}


BEGIN_MESSAGE_MAP(CStudentDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BN_QUERY, &CStudentDlg::OnBnClickedBnQuery)
	ON_BN_CLICKED(IDC_BN_FIRST, &CStudentDlg::OnBnClickedBnFirst)
	ON_BN_CLICKED(IDC_BN_PREV, &CStudentDlg::OnBnClickedBnPrev)
	ON_BN_CLICKED(IDC_BN_NEXT, &CStudentDlg::OnBnClickedBnNext)
	ON_BN_CLICKED(IDC_BN_LAST, &CStudentDlg::OnBnClickedBnLast)
	ON_BN_CLICKED(IDC_BN_ADD, &CStudentDlg::OnBnClickedBnAdd)
	ON_BN_CLICKED(IDC_BN_EDIT, &CStudentDlg::OnBnClickedBnEdit)
	ON_BN_CLICKED(IDC_BN_DELETE, &CStudentDlg::OnBnClickedBnDelete)
	ON_BN_CLICKED(IDC_BN_SAVE, &CStudentDlg::OnBnClickedBnSave)
	ON_BN_CLICKED(IDC_BN_CANCEL, &CStudentDlg::OnBnClickedBnCancel)
	ON_BN_CLICKED(IDC_BN_EXIT, &CStudentDlg::OnBnClickedBnExit)
	
END_MESSAGE_MAP()


// CStudentDlg ��Ϣ�������


void CStudentDlg::ClearEditData(void)
{
	m_strSNo="";
	m_strSName="";
	m_strSSex="";
	m_strSMajor="";
	m_strSBDate="";
	m_strSSDate="";

	UpdateData(FALSE);
	return;
}


void CStudentDlg::ReadRecord(void)
{
	m_strSNo=m_rsStudentSet.m_SNo;
	m_strSName=m_rsStudentSet.m_SName;
	m_strSSex=m_rsStudentSet.m_SSex;
	m_strSMajor=m_rsStudentSet.m_SMajor;
	m_strSBDate=m_rsStudentSet.m_SBirthDate.Format("%Y-%m-%d");
	m_strSSDate=m_rsStudentSet.m_SSchoolDate.Format("%Y-%m-%d");
	
	UpdateData(FALSE);
	return;
}


void CStudentDlg::WriteRecord(void)
{
	UpdateData(TRUE);

	m_rsStudentSet.m_SNo=m_strSNo;
	m_rsStudentSet.m_SName=m_strSName;
	m_rsStudentSet.m_SSex=m_strSSex;
	m_rsStudentSet.m_SMajor=m_strSMajor;
	
	int a,b,c;
	CString   timestrB=m_strSBDate;   
	sscanf(timestrB.GetBuffer(timestrB.GetLength()),"%d-%d-%d",&a,&b,&c);   
	CTime   timeB(a,b,c,0,0,0);
	m_rsStudentSet.m_SBirthDate=timeB;
	CString   timestrS=m_strSSDate; 
	sscanf(timestrS.GetBuffer(timestrS.GetLength()),"%d-%d-%d",&a,&b,&c);   
	CTime   timeS(a,b,c,0,0,0);
	m_rsStudentSet.m_SSchoolDate=timeS;
}


void CStudentDlg::SetMoveBNState(void)
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


void CStudentDlg::SetEditState(void)
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

		pWnd=GetDlgItem(IDC_EDIT_SNo);
		if(m_bAdd)
			pWnd->EnableWindow(TRUE);
		else
			pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_EDIT_SNAME);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_EDIT_SSEX);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_EDIT_SMAJOR);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_EDIT_SBDATE);
		pWnd->EnableWindow(TRUE);
		pWnd=GetDlgItem(IDC_EDIT_SSDATE);
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

		pWnd=GetDlgItem(IDC_EDIT_SNo);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_EDIT_SNAME);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_EDIT_SSEX);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_EDIT_SMAJOR);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_EDIT_SBDATE);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_EDIT_SSDATE);
		pWnd->EnableWindow(FALSE);
	}
	return;
}

BOOL CStudentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_rsStudentSet.Open(AFX_DB_USE_DEFAULT_TYPE);
	if(!m_rsStudentSet.IsOpen())
	{
		AfxMessageBox("���ݿ��ʧ��!");
		return TRUE;
	}
	else if(m_rsStudentSet.IsBOF())
	{
		AfxMessageBox("���ݼ��գ�");
		m_bEmpty=true;
		ClearEditData();
		SetMoveBNState();
		SetEditState();
	}
	else
	{
		m_bEmpty=false;
		m_rsStudentSet.MoveFirst();
		m_bFirst=true;
		m_bLast=false;
		ReadRecord();
		SetMoveBNState();
		SetEditState();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CStudentDlg::OnBnClickedBnFirst()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_rsStudentSet.MoveFirst();
	m_bFirst=true;
	m_bLast=false;
	SetMoveBNState();
	ReadRecord();
}

void CStudentDlg::OnBnClickedBnPrev()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bFirst=false;
	m_bLast=false;
	m_rsStudentSet.MovePrev();
	if(m_rsStudentSet.IsBOF())
	{
		m_rsStudentSet.MoveFirst();
		m_bFirst=TRUE;
	}
	SetMoveBNState();
	ReadRecord();
}

void CStudentDlg::OnBnClickedBnNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bFirst=false;
	m_bLast=false;
	m_rsStudentSet.MoveNext();
	if(m_rsStudentSet.IsEOF())
	{
		m_rsStudentSet.MoveLast();
		m_bLast=true;
	}
	SetMoveBNState();
	ReadRecord();
}

void CStudentDlg::OnBnClickedBnLast()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_rsStudentSet.MoveLast();
	m_bFirst=false;
	m_bLast=true;
	SetMoveBNState();
	ReadRecord();
}

void CStudentDlg::OnBnClickedBnQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_strSNo_Q.IsEmpty() && m_strSNAME_Q.IsEmpty())
	{	
		m_rsStudentSet.m_strFilter="";
		m_rsStudentSet.Requery();
		if(m_rsStudentSet.IsBOF())
		{
			AfxMessageBox("���ݼ��գ�");
			m_bEmpty=true;
			ClearEditData();
			SetMoveBNState();
		}
		else
		{
			m_bEmpty=false;
			m_rsStudentSet.MoveFirst();
			m_bFirst=true;
			m_bLast=false;
			ReadRecord();
			SetMoveBNState();
		}
		return;
	}
	BOOL mbSNoQInput=FALSE;
	if(!m_strSNo_Q.IsEmpty())
	{
		m_rsStudentSet.m_strFilter="SNo='"+m_strSNo_Q;
		m_rsStudentSet.m_strFilter=m_rsStudentSet.m_strFilter+"'";
		
		mbSNoQInput=TRUE;	
	}
	if(!m_strSNAME_Q.IsEmpty())
	{
		if(mbSNoQInput)
		{
			m_rsStudentSet.m_strFilter=m_rsStudentSet.m_strFilter
			                        +" AND SName='";
			m_rsStudentSet.m_strFilter=m_rsStudentSet.m_strFilter
			                        +m_strSNAME_Q;
			m_rsStudentSet.m_strFilter=m_rsStudentSet.m_strFilter
									+"'";
		}	                        							
		else
		{
			m_rsStudentSet.m_strFilter="SName='"+m_strSNAME_Q;
			m_rsStudentSet.m_strFilter=m_rsStudentSet.m_strFilter+"'";

		}
		
	}
	m_rsStudentSet.Requery();
	if(m_rsStudentSet.IsEOF())
	{
		AfxMessageBox("û�в鵽��ؼ�¼��");
		m_bEmpty=true;
		ClearEditData();
		SetMoveBNState();
	}
	else
	{
		m_bEmpty=false;
		m_rsStudentSet.MoveFirst();
		m_bFirst=true;
		ReadRecord();
		SetMoveBNState();
	}	

}



void CStudentDlg::OnBnClickedBnAdd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ClearEditData();
	m_bEdit=true;
	m_bAdd=true;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd=GetDlgItem(IDC_EDIT_SNo);
	pWnd->SetFocus();
}


void CStudentDlg::OnBnClickedBnEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bEdit=true;
	m_bAdd=false;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd=GetDlgItem(IDC_EDIT_SNAME);
	pWnd->SetFocus();
}


void CStudentDlg::OnBnClickedBnDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(AfxMessageBox("ȷ��Ҫɾ��������¼��",MB_YESNO)!=IDYES)
		return;
	m_rsStudentSet.Delete();
	//m_rsSCChoiceSet.MoveNext();
	m_rsStudentSet.Requery();
	if(m_rsStudentSet.IsBOF())
	{
		AfxMessageBox("������û�м�¼�ˣ�");
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




void CStudentDlg::OnBnClickedBnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_strSNo.IsEmpty() || m_strSName.IsEmpty())
	{
		AfxMessageBox("��������Ӧ���ݣ�");
		CWnd *pWnd;
		pWnd=GetDlgItem(IDC_EDIT_SNo);
		pWnd->SetFocus();
		return;
	}
	if(m_bAdd)
	{
		m_rsStudentSet.AddNew();
	}
	else
	{
		m_rsStudentSet.Edit();
	}
	WriteRecord();
	m_rsStudentSet.Update();
	m_rsStudentSet.Requery();
	m_rsStudentSet.MoveFirst();
	m_bFirst=true;
	m_bLast=false;
	m_bAdd=false;
	m_bEdit=false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CStudentDlg::OnBnClickedBnCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bAdd=false;
	m_bEdit=false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CStudentDlg::OnBnClickedBnExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}


