// CStudentSet.h : CStudentSet 类的实现



// CStudentSet 实现

// 代码生成在 2015年6月6日, 18:03

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
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
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
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
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
// CStudentSet 诊断

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


