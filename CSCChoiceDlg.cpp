// CSCChoiceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "CSCChoiceDlg.h"
#include "afxdialogex.h"


// CSCChoiceDlg �Ի���

IMPLEMENT_DYNAMIC(CSCChoiceDlg, CDialogEx)

CSCChoiceDlg::CSCChoiceDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSCChoiceDlg::IDD, pParent)
	, m_bAdd(false)
	, m_bEdit(false)
	, m_bEmpty(false)
	, m_bFirst(false)
	, m_bLast(false)
	, m_strSNo_Q(_T(""))
	, m_strCNo_Q(_T(""))
	, m_strSNo(_T(""))
	, m_strCNo(_T(""))
	, m_strSCGrade(_T(""))
{

}

CSCChoiceDlg::~CSCChoiceDlg()
{
}

BOOL CSCChoiceDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_rsSCChoiceSet.Open(AFX_DB_USE_DEFAULT_TYPE);
	if(!m_rsSCChoiceSet.IsOpen())
	{
		AfxMessageBox("���ݿ��ʧ��!");
		return TRUE;
	}
	else if(m_rsSCChoiceSet.IsBOF())
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
		m_rsSCChoiceSet.MoveFirst();
		m_bFirst=true;
		m_bLast=false;
		ReadRecord();
		SetMoveBNState();
		SetEditState();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}
void CSCChoiceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT_SNo_Q, m_strSNo_Q);
	DDX_Text(pDX, IDC_EDIT_SNo_Q, m_strSNo_Q);
	DDX_Text(pDX, IDC_EDIT_CNo_Q, m_strCNo_Q);
	DDX_Text(pDX, IDC_EDIT_SNo, m_strSNo);
	DDX_Text(pDX, IDC_EDIT_CNo, m_strCNo);
	DDX_Text(pDX, IDC_EDIT_SCGRADE, m_strSCGrade);
}


BEGIN_MESSAGE_MAP(CSCChoiceDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BN_FIRST, &CSCChoiceDlg::OnBnClickedBnFirst)
	ON_BN_CLICKED(IDC_BN_PREV, &CSCChoiceDlg::OnBnClickedBnPrev)
	ON_BN_CLICKED(IDC_BN_NEXT, &CSCChoiceDlg::OnBnClickedBnNext)
	ON_BN_CLICKED(IDC_BN_LAST, &CSCChoiceDlg::OnBnClickedBnLast)
	ON_BN_CLICKED(IDC_BN_QUERY, &CSCChoiceDlg::OnBnClickedBnQuery)
	ON_BN_CLICKED(IDC_BN_ADD, &CSCChoiceDlg::OnBnClickedBnAdd)
	ON_BN_CLICKED(IDC_BN_EDIT, &CSCChoiceDlg::OnBnClickedBnEdit)
	ON_BN_CLICKED(IDC_BN_DELETE, &CSCChoiceDlg::OnBnClickedBnDelete)
	ON_BN_CLICKED(IDC_BN_SAVE, &CSCChoiceDlg::OnBnClickedBnSave)
	ON_BN_CLICKED(IDC_BN_CANCEL, &CSCChoiceDlg::OnBnClickedBnCancel)
	ON_BN_CLICKED(IDC_BN_EXIT, &CSCChoiceDlg::OnBnClickedBnExit)
END_MESSAGE_MAP()


// CSCChoiceDlg ��Ϣ�������


void CSCChoiceDlg::ClearEditData(void)
{
	m_strSNo="";
	m_strCNo="";
	m_strSCGrade="";
	
	UpdateData(FALSE);
	return;
}


void CSCChoiceDlg::ReadRecord(void)
{
	m_strSNo=m_rsSCChoiceSet.m_SNo;
	m_strCNo=m_rsSCChoiceSet.m_CNo;
	m_strSCGrade.Format("%d",m_rsSCChoiceSet.m_SCGrade);
	
	UpdateData(FALSE);
	return;
}


void CSCChoiceDlg::WriteRecord(void)
{
	UpdateData(TRUE);

	m_rsSCChoiceSet.m_SNo=m_strSNo;
	m_rsSCChoiceSet.m_CNo=m_strCNo;
	
	int nGrade=atoi(m_strSCGrade);
	m_rsSCChoiceSet.m_SCGrade=nGrade;
	return;
}


void CSCChoiceDlg::SetMoveBNState(void)
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


void CSCChoiceDlg::SetEditState(void)
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
		
		pWnd=GetDlgItem(IDC_EDIT_CNo);
		if(m_bAdd)
			pWnd->EnableWindow(TRUE);
		else
			pWnd->EnableWindow(FALSE);
		
		pWnd=GetDlgItem(IDC_EDIT_SCGRADE);
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
		pWnd=GetDlgItem(IDC_EDIT_CNo);
		pWnd->EnableWindow(FALSE);
		pWnd=GetDlgItem(IDC_EDIT_SCGRADE);
		pWnd->EnableWindow(FALSE);
		
	}
	return;
}





void CSCChoiceDlg::OnBnClickedBnFirst()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_rsSCChoiceSet.MoveFirst();
	m_bFirst=true;
	m_bLast=false;
	SetMoveBNState();
	ReadRecord();
}


void CSCChoiceDlg::OnBnClickedBnPrev()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bFirst=false;
	m_bLast=false;
	m_rsSCChoiceSet.MovePrev();
	if(m_rsSCChoiceSet.IsBOF())
	{
		m_rsSCChoiceSet.MoveFirst();
		m_bFirst=TRUE;
	}
	SetMoveBNState();
	ReadRecord();
}


void CSCChoiceDlg::OnBnClickedBnNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bFirst=false;
	m_bLast=false;
	m_rsSCChoiceSet.MoveNext();
	if(m_rsSCChoiceSet.IsEOF())
	{
		m_rsSCChoiceSet.MoveLast();
		m_bLast=true;
	}
	SetMoveBNState();
	ReadRecord();
}


void CSCChoiceDlg::OnBnClickedBnLast()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_rsSCChoiceSet.MoveLast();
	m_bFirst=false;
	m_bLast=true;
	SetMoveBNState();
	ReadRecord();
}


void CSCChoiceDlg::OnBnClickedBnQuery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_strSNo_Q.IsEmpty() && m_strCNo_Q.IsEmpty())
	{	
		m_rsSCChoiceSet.m_strFilter="";
		m_rsSCChoiceSet.Requery();
		if(m_rsSCChoiceSet.IsBOF())
		{
			AfxMessageBox("���ݼ��գ�");
			m_bEmpty=true;
			ClearEditData();
			SetMoveBNState();
		}
		else
		{
			m_bEmpty=false;
			m_rsSCChoiceSet.MoveFirst();
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
		m_rsSCChoiceSet.m_strFilter="SNo='"+m_strSNo_Q;
		m_rsSCChoiceSet.m_strFilter=m_rsSCChoiceSet.m_strFilter+"'";
		
		mbSNoQInput=TRUE;	
	}
	if(!m_strCNo_Q.IsEmpty())
	{
		if(mbSNoQInput)
		{
			m_rsSCChoiceSet.m_strFilter=m_rsSCChoiceSet.m_strFilter
			                        +" AND CNo='";
			m_rsSCChoiceSet.m_strFilter=m_rsSCChoiceSet.m_strFilter
			                        +m_strCNo_Q;
			m_rsSCChoiceSet.m_strFilter=m_rsSCChoiceSet.m_strFilter
									+"'";
		}	                        							
		else
		{
			m_rsSCChoiceSet.m_strFilter="CNo='"+m_strCNo_Q;
			m_rsSCChoiceSet.m_strFilter=m_rsSCChoiceSet.m_strFilter+"'";

		}
		
	}
	//AfxMessageBox(m_rsSCChoiceSet.m_strFilter);
	m_rsSCChoiceSet.Requery();
	if(m_rsSCChoiceSet.IsEOF())
	{
		AfxMessageBox("û�в鵽��ؼ�¼��");
		m_bEmpty=true;
		ClearEditData();
		SetMoveBNState();
	}
	else
	{
		m_bEmpty=false;
		m_rsSCChoiceSet.MoveFirst();
		m_bFirst=true;
		ReadRecord();
		SetMoveBNState();
	}	
}


void CSCChoiceDlg::OnBnClickedBnAdd()
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


void CSCChoiceDlg::OnBnClickedBnEdit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bEdit=true;
	m_bAdd=false;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd=GetDlgItem(IDC_EDIT_SCGRADE);
	pWnd->SetFocus();
}


void CSCChoiceDlg::OnBnClickedBnDelete()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(AfxMessageBox("ȷ��Ҫɾ��������¼��",MB_YESNO)!=IDYES)
		return;
	m_rsSCChoiceSet.Delete();
	//m_rsSCChoiceSet.MoveNext();
	m_rsSCChoiceSet.Requery();
	if(m_rsSCChoiceSet.IsBOF())
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




void CSCChoiceDlg::OnBnClickedBnSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if(m_strSNo.IsEmpty() || m_strCNo.IsEmpty())
	{
		AfxMessageBox("��������Ӧ���ݣ�");
		CWnd *pWnd;
		pWnd=GetDlgItem(IDC_EDIT_SNo);
		pWnd->SetFocus();
		return;
	}
	if(m_bAdd)
	{
		m_rsSCChoiceSet.AddNew();
	}
	else
	{
		m_rsSCChoiceSet.Edit();
	}
	WriteRecord();
	m_rsSCChoiceSet.Update();
	m_rsSCChoiceSet.Requery();
	m_rsSCChoiceSet.MoveFirst();
	m_bFirst=true;
	m_bLast=false;
	m_bAdd=false;
	m_bEdit=false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}



void CSCChoiceDlg::OnBnClickedBnCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_bAdd=false;
	m_bEdit=false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CSCChoiceDlg::OnBnClickedBnExit()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnOK();
}
