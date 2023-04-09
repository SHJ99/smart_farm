#pragma once


// report 대화 상자
#include<afxdb.h>
class CMy57View;
class report : public CDialogEx
{
	DECLARE_DYNAMIC(report)

public:
	report(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~report();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CMy57View* view;
	CListCtrl m_report;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton3();
	CDateTimeCtrl m_start;
	CDateTimeCtrl m_end;
	CDatabase my_db;
	CRecordset* my_prs;
};
