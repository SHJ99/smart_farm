#pragma once


// create 대화 상자
#include<afxdb.h>
class CMy57View;
class create : public CDialogEx
{
	DECLARE_DYNAMIC(create)

public:
	create(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~create();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	CMy57View* view;
	CDatabase m_db;
	CRecordset* m_prs;
//	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCancel();
	CComboBox m_line;
	CListCtrl m_create;
	afx_msg void OnBnClickedOk();
	CComboBox m_temp;
	CComboBox m_moist;
	CComboBox m_light;
	CComboBox m_cycle;
	CEdit m_name;
	int check2;
	afx_msg void OnBnClickedButton1();
//	int EnCode(char* pszCode);
};
