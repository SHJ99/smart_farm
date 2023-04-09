#pragma once


// sign 대화 상자
#include<afxdb.h>
class CMy57View;
class sign : public CDialogEx
{
	DECLARE_DYNAMIC(sign)

public:

	sign(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~sign();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void PostNcDestroy();
public:
	CMy57View* view;
	CDatabase m_db;
	CRecordset* m_prs;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CEdit m_id;
	CEdit m_pw;
	CEdit m_pw1;
	CEdit m_name;
	CEdit m_farmname;
	CButton m_farmer;
	CButton m_reservefarmer;
	CButton m_farm;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	int check;
	afx_msg void OnBnClickedButton2();
	int success;
	int EnCode(char* pszCode);
};
