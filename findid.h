#pragma once


// findid 대화 상자
#include<afxdb.h>
class CMy57View;
class findid : public CDialogEx
{
	DECLARE_DYNAMIC(findid)

public:
	findid(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~findid();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CMy57View* view;
	CDatabase m_db;
	CRecordset* m_prs;
	CEdit m_name;
	CEdit m_farmname;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	afx_msg void OnBnClickedCancel();
	int success;
//	CButton m_findid;
	CEdit m_findid;
};
