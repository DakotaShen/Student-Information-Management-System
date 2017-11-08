// CStudentSet.h : CStudentSet ���ʵ��



// CStudentSet ʵ��

// ���������� 2015��6��6��, 18:03

#include "stdafx.h"
#include "CStudentSet.h"
IMPLEMENT_DYNAMIC(CStudentSet, CRecordset)

CStudentSet::CStudentSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_SNo = "";
	m_SName = "";
	m_SSex = "";
	m_ClassNo = "";
	m_SBirthDate;
	m_Status = "";
	m_Hometown = "";
	m_SSchoolDate;
	m_Telephone = "";
	m_Resume = "";
	m_SMajor = L"";
	m_nFields = 11;
	m_nDefaultType = snapshot;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CStudentSet::GetDefaultConnect()
{
	return _T("DSN=Student;Trusted_Connection=Yes;APP=Microsoft\x00ae Visual Studio\x00ae 2013;WSID=SDWM-20150509II;DATABASE=teaching;");
}

CString CStudentSet::GetDefaultSQL()
{
	return _T("[dbo].[Student]");
}

void CStudentSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[SNo]"), m_SNo);
	RFX_Text(pFX, _T("[SName]"), m_SName);
	RFX_Text(pFX, _T("[SSex]"), m_SSex);
	RFX_Text(pFX, _T("[ClassNo]"), m_ClassNo);
	RFX_Date(pFX, _T("[SBirthDate]"), m_SBirthDate);
	RFX_Text(pFX, _T("[Status]"), m_Status);
	RFX_Text(pFX, _T("[Hometown]"), m_Hometown);
	RFX_Date(pFX, _T("[SSchoolDate]"), m_SSchoolDate);
	RFX_Text(pFX, _T("[Telephone]"), m_Telephone);
	RFX_Text(pFX, _T("[Resume]"), m_Resume);
	RFX_Text(pFX, _T("[SMajor]"), m_SMajor);

}
/////////////////////////////////////////////////////////////////////////////
// CStudentSet ���

#ifdef _DEBUG
void CStudentSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStudentSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


