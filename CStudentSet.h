// CStudentSet.h : CStudentSet ������

#pragma once

// ���������� 2015��6��6��, 18:03

class CStudentSet : public CRecordset
{
public:
	CStudentSet(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CStudentSet)

// �ֶ�/��������

// �����ַ�������(�������)��ӳ���ݿ��ֶ�(ANSI �������͵� CStringA �� Unicode
// �������͵� CStringW)��ʵ���������͡�
//  ����Ϊ��ֹ ODBC ��������ִ�п���
// ����Ҫ��ת�������ϣ�������Խ���Щ��Ա����Ϊ
// CString ���ͣ�ODBC ��������ִ�����б�Ҫ��ת����
// (ע��: ����ʹ�� 3.5 �����߰汾�� ODBC ��������
// ��ͬʱ֧�� Unicode ����Щת��)��

	CStringA	m_SNo;
	CStringA	m_SName;
	CStringA	m_SSex;
	CStringA	m_ClassNo;
	CTime	m_SBirthDate;
	CStringA	m_Status;
	CStringA	m_Hometown;
	CTime	m_SSchoolDate;
	CStringA	m_Telephone;
	CStringA	m_Resume;
	CStringW	m_SMajor;

// ��д
	// �����ɵ��麯����д
	public:
	virtual CString GetDefaultConnect();	// Ĭ�������ַ���

	virtual CString GetDefaultSQL(); 	// ��¼����Ĭ�� SQL
	virtual void DoFieldExchange(CFieldExchange* pFX);	// RFX ֧��

// ʵ��
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

};


