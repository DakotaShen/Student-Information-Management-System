// CCourseSet.h : CCourseSet ���ʵ��



// CCourseSet ʵ��

// ���������� 2015��6��6��, 17:37

#include "stdafx.h"
#include "CCourseSet.h"
IMPLEMENT_DYNAMIC(CCourseSet, CRecordset)

CCourseSet::CCourseSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CNo = "";
	m_CName = "";
	m_Category = "";
	m_Major = "";
	m_Grade = "";
	m_StartTM;
	m_CRedit = 0;
	m_WeekHours = "";
	m_nFields = 8;
	m_nDefaultType = snapshot;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CCourseSet::GetDefaultConnect()
{
	return _T("DSN=Student;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=SDWM-20150509II;DATABASE=teaching;");
}

CString CCourseSet::GetDefaultSQL()
{
	return _T("[dbo].[Course]");
}

void CCourseSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[CNo]"), m_CNo);
	RFX_Text(pFX, _T("[CName]"), m_CName);
	RFX_Text(pFX, _T("[Category]"), m_Category);
	RFX_Text(pFX, _T("[Major]"), m_Major);
	RFX_Text(pFX, _T("[Grade]"), m_Grade);
	RFX_Date(pFX, _T("[StartTM]"), m_StartTM);
	RFX_Long(pFX, _T("[CRedit]"), m_CRedit);
	RFX_Text(pFX, _T("[WeekHours]"), m_WeekHours);

}
/////////////////////////////////////////////////////////////////////////////
// CCourseSet ���

#ifdef _DEBUG
void CCourseSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CCourseSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


