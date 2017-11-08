// CSCChoiceSet.h : CSCChoiceSet ���ʵ��



// CSCChoiceSet ʵ��

// ���������� 2015��6��6��, 17:55

#include "stdafx.h"
#include "CSCChoiceSet.h"
IMPLEMENT_DYNAMIC(CSCChoiceSet, CRecordset)

CSCChoiceSet::CSCChoiceSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_CNo = "";
	m_SNo = "";
	m_SCGrade = 0;
	m_CourseName = "";
	m_nFields = 4;
	m_nDefaultType = snapshot;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CSCChoiceSet::GetDefaultConnect()
{
	return _T("DSN=Student;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=SDWM-20150509II;DATABASE=teaching;");
}

CString CSCChoiceSet::GetDefaultSQL()
{
	return _T("[dbo].[SC]");
}

void CSCChoiceSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[CNo]"), m_CNo);
	RFX_Text(pFX, _T("[SNo]"), m_SNo);
	RFX_Long(pFX, _T("[SCGrade]"), m_SCGrade);
	RFX_Text(pFX, _T("[CourseName]"), m_CourseName);

}
/////////////////////////////////////////////////////////////////////////////
// CSCChoiceSet ���

#ifdef _DEBUG
void CSCChoiceSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSCChoiceSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


