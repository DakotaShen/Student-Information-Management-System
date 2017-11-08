// CSCChoiceSet.h : CSCChoiceSet 类的实现



// CSCChoiceSet 实现

// 代码生成在 2015年6月6日, 17:55

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
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
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
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[CNo]"), m_CNo);
	RFX_Text(pFX, _T("[SNo]"), m_SNo);
	RFX_Long(pFX, _T("[SCGrade]"), m_SCGrade);
	RFX_Text(pFX, _T("[CourseName]"), m_CourseName);

}
/////////////////////////////////////////////////////////////////////////////
// CSCChoiceSet 诊断

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


