
// 5_7View.h: CMy57View 클래스의 인터페이스
//
#include<afxdb.h>
#pragma once
class create;
class report;
class sign;
class findid;
class findpwd;
class CMy425Doc;

class CMy57View : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CMy57View() noexcept;
	DECLARE_DYNCREATE(CMy57View)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_MY5_7_FORM };
#endif

// 특성입니다.
public:
	CMy57Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CMy57View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	CDatabase m_db;
	CRecordset* m_prs;
	create* cre;
	report* rep;
	sign* sig;
	findid* fid;
	findpwd* fpw;
	afx_msg void OnBnClickedButton5();
	CListCtrl m_current;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton3();
//	CStatic IDC_PICTURE_VIEW;
	afx_msg void OnPaint();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton7();
	CEdit m_id;
	CEdit m_pw;
	int success;
//	virtual void OnDraw(CDC* /*pDC*/);
	CDateTimeCtrl view_date;
	CString user_id;
	afx_msg void OnBnClickedButton9();
	CRecordset* m_ppt;
	CRecordset* m_paa;
	afx_msg void Oncome();
};

#ifndef _DEBUG  // 5_7View.cpp의 디버그 버전
inline CMy57Doc* CMy57View::GetDocument() const
   { return reinterpret_cast<CMy57Doc*>(m_pDocument); }
#endif

