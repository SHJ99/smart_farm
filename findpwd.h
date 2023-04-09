#pragma once


// findpwd 대화 상자
#include<afxdb.h>
class CMy57View;
class findpwd : public CDialogEx
{
	DECLARE_DYNAMIC(findpwd)

public:
	findpwd(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~findpwd();
	CMy57View* view;
	CDatabase m_db;
	CRecordset* m_prs;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG5 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedCancel();
	CEdit m_id;
	CEdit m_name;
	CEdit m_farmname;
	afx_msg void OnBnClickedButton1();
	int success;
	int check;
	afx_msg void OnBnClickedOk();
	CEdit m_pw;
	CEdit m_pw1;
};
