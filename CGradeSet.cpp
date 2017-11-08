// CGradeSet.h : CGradeSet 类的实现



// CGradeSet 实现

// 代码生成在 2014年9月29日星期一, 17:19

#include "stdafx.h"
#include "CGradeSet.h"
IMPLEMENT_DYNAMIC(CGradeSet, CRecordset)

CGradeSet::CGradeSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_COURSECNo = L"";
	m_COURSECName = L"";
	m_COURSECRedit = 0;
	m_SCCHOICESNo = L"";
	m_SCCHOICECNo = L"";
	m_SCCHOICESCGrade = 0;
	m_STUDENTSNo = L"";
	m_STUDENTSName = L"";
	m_STUDENTSSex = L"";
	m_STUDENTSMajor = L"";
	m_STUDENTSBirthDate;
	m_STUDENTSSchoolDate;
	m_nFields =12; //9;	//12;
	m_nDefaultType = snapshot;
}
//#error 安全问题：连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CGradeSet::GetDefaultConnect()
{
	return _T("DSN=StudentInfo;DBQ=D:\\程序设计实践教材\\SCDB.accdb;DriverId=25;FIL=MS Access;MaxBufferSize=2048;PageTimeout=5;UID=admin;");
}

CString CGradeSet::GetDefaultSQL()
{
	return _T("[COURSE],[SCCHOICE],[STUDENT]");
}

void CGradeSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[COURSE].[CNo]"), m_COURSECNo);
	RFX_Text(pFX, _T("[COURSE].[CName]"), m_COURSECName);
	RFX_Int(pFX, _T("[COURSE].[CRedit]"), m_COURSECRedit);
	RFX_Text(pFX, _T("[SCCHOICE].[SNo]"), m_SCCHOICESNo);
	RFX_Text(pFX, _T("[SCCHOICE].[CNo]"), m_SCCHOICECNo);
	RFX_Int(pFX, _T("[SCCHOICE].[SCGrade]"), m_SCCHOICESCGrade);
	RFX_Text(pFX, _T("[STUDENT].[SNo]"), m_STUDENTSNo);
	RFX_Text(pFX, _T("[STUDENT].[SName]"), m_STUDENTSName);
	RFX_Text(pFX, _T("[STUDENT].[SSex]"), m_STUDENTSSex);
	RFX_Text(pFX, _T("[STUDENT].[SMajor]"), m_STUDENTSMajor);
	RFX_Date(pFX, _T("[STUDENT].[SBirthDate]"), m_STUDENTSBirthDate);
	RFX_Date(pFX, _T("[STUDENT].[SSchoolDate]"), m_STUDENTSSchoolDate);

}
/////////////////////////////////////////////////////////////////////////////
// CGradeSet 诊断

#ifdef _DEBUG
void CGradeSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CGradeSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


