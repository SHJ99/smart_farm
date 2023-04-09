
// 5_7View.cpp: CMy57View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "5_7.h"
#endif

#include "5_7Doc.h"
#include "5_7View.h"

#include "create.h"
#include "sign.h"
#include "report.h"
#include "findid.h"
#include "findpwd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy57View

IMPLEMENT_DYNCREATE(CMy57View, CFormView)

BEGIN_MESSAGE_MAP(CMy57View, CFormView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFormView::OnFilePrintPreview)
	ON_BN_CLICKED(IDC_BUTTON5, &CMy57View::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON1, &CMy57View::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy57View::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy57View::OnBnClickedButton3)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON2, &CMy57View::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON6, &CMy57View::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON8, &CMy57View::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON7, &CMy57View::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON9, &CMy57View::OnBnClickedButton9)
	ON_COMMAND(ID_come, &CMy57View::Oncome)
END_MESSAGE_MAP()

// CMy57View 생성/소멸

CMy57View::CMy57View() noexcept
	: CFormView(IDD_MY5_7_FORM)
{
	// TODO: 여기에 생성 코드를 추가합니다.
	cre = NULL;
	rep = NULL;
	sig = NULL;
	fid = NULL;
	fpw = NULL;
	success = 0;
}

CMy57View::~CMy57View()
{
}

void CMy57View::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_current);
	DDX_Control(pDX, IDC_EDIT1, m_id);
	DDX_Control(pDX, IDC_EDIT2, m_pw);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, view_date);
}

BOOL CMy57View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CFormView::PreCreateWindow(cs);
}

void CMy57View::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
	
	//m_current.InsertColumn(0, _T("인덱스"), LVCFMT_CENTER, 0, -1);
	//m_current.InsertColumn(1, _T("날짜"), LVCFMT_CENTER, 0, -1);
	m_current.InsertColumn(0, _T("라인"), LVCFMT_CENTER, 50, -1);
	m_current.InsertColumn(1, _T("작물이름"), LVCFMT_CENTER, 70, -1);
	//m_current.InsertColumn(4, _T("마지막물준날"), LVCFMT_CENTER, 0, -1); //건강도에 들어가려나?? 아 하드웨어 제어니까... 필요한가?
	m_current.InsertColumn(2, _T("성장률"), LVCFMT_CENTER, 70, -1);
	m_current.InsertColumn(3, _T("건강도"), LVCFMT_CENTER, 70, -1);
	m_current.InsertColumn(4, _T("병충해"), LVCFMT_CENTER, 70, -1);
	m_current.InsertColumn(5, _T("특이사항"), LVCFMT_CENTER, 100, -1);


	BOOL bopen = m_db.OpenEx(_T("DSN=2020116063;SERVER=155.230.235.248;PORT=34056;UID=2020116063;PWD=whgdkdy22!!;DATABASE=s2020116063;"), CDatabase::noOdbcDialog);
	if (bopen)
		m_prs = new CRecordset(&m_db);
	if (bopen)
		m_ppt = new CRecordset(&m_db);
	if (bopen)
		m_paa = new CRecordset(&m_db);

}


// CMy57View 인쇄

BOOL CMy57View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy57View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy57View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMy57View::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: 여기에 사용자 지정 인쇄 코드를 추가합니다.
}


// CMy57View 진단

#ifdef _DEBUG
void CMy57View::AssertValid() const
{
	CFormView::AssertValid();
}

void CMy57View::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CMy57Doc* CMy57View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy57Doc)));
	return (CMy57Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy57View 메시지 처리기

//불러오기
void CMy57View::OnBnClickedButton5()
{
	//db 연동시킴
	/*m_db.BeginTrans();
	CString str;
	str.Format(L"select * from mfctestdb.`2020116063_t`");
	m_db.ExecuteSQL(str);
	m_db.CommitTrans();
	*/
	//select 현재날짜 from log where 농장주인이름(리포트에서 불러오기)
	// 리스트 컨트롤에서 데려옴.
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	UpdateData(TRUE);

	m_current.DeleteAllItems();

	CTime m_time;
	CString view_day, str, str2;
	view_date.GetTime(m_time);
	view_day = m_time.Format(L"%Y-%m-%d");
	CString id= user_id;

	str.Format(L"SELECT * FROM s2020116063.report WHERE DATE(day) = '%s' and ID='%s'; ", view_day, id);
	BOOL bopen = m_prs->Open(CRecordset::snapshot, str);
	int index = m_current.GetItemCount();

	for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {	
		m_prs->GetFieldValue(L"line", str2);
		m_current.InsertItem(0, str2);
		m_prs->GetFieldValue(L"name", str2);
		m_current.SetItemText(index, 1, str2);
		m_prs->GetFieldValue(L"growth", str2);
		m_current.SetItemText(index, 2, str2);
		m_prs->GetFieldValue(L"health", str2);
		m_current.SetItemText(index, 3, str2);
		m_prs->GetFieldValue(L"disease", str2);
		m_current.SetItemText(index, 4, str2);
		//m_prs->GetFieldValue(L"health", str);
		m_current.SetItemText(index, 5, L"뭐라고쓸까");	
	}
	m_prs->Close();
	UpdateData(FALSE);
}


void CMy57View::OnBnClickedButton1()
{
	//create.domodal();
	if (cre == NULL) {
		cre = new create;
		cre->view = this; //뷰 자체의 위치
		cre->Create(IDD_DIALOG1);
		cre->ShowWindow(SW_SHOW);
}
	else
		cre->SetFocus();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMy57View::OnBnClickedButton4()
{

	CString sdtr;
	CString helhel;
	int hh = 0;
	int asdasd = 100;
	sdtr.Format(L"SELECT * FROM report WHERE day in (SELECT MAX(day) FROM report) AND growth>=100");
	BOOL bopen = m_paa->Open(CRecordset::snapshot, sdtr);
	{
		int trow = 1;
		BOOL beof = m_paa->IsEOF();
		DWORD dwsize = m_paa->GetRowsetSize();
		if (!beof) {
			for (m_paa->MoveFirst(); !m_paa->IsEOF(); m_paa->MoveNext()) {
				m_paa->SetAbsolutePosition(trow);

				m_paa->GetFieldValue(5, helhel);

				hh += _ttoi(helhel);
				trow++;

			}
			sdtr.Format(L"총 수확량은 %d 입니다", hh);
			AfxMessageBox(sdtr);
		}
		else
			AfxMessageBox(L"아쉽게도 수확할수 있는 작물이 없습니다.");

	}
	m_paa->Close();

	sdtr.Format(L"DELETE FROM report WHERE growth>=100");
	m_db.ExecuteSQL(sdtr);
}


void CMy57View::OnBnClickedButton3()
{
	if (rep == NULL) {
		rep = new report;
		rep->view = this; //뷰 자체의 위치
		rep->Create(IDD_DIALOG2);
		rep->ShowWindow(SW_SHOW);
	}
	else
		//만들어졌다면 그것에 집중해
		rep->SetFocus();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CMy57View::OnPaint()
{
	CPaintDC dc(this);  // 그림을 그릴 DC 선택. 

	CDC MemDC;  // 메모리 DC 선언
	
	MemDC.CreateCompatibleDC(&dc);  //화면 DC와 동일한 메모리 DC를 만든다
	CBitmap MyBmp, * pOldBmp;  // 비트맵 객체를 선언한다
	MyBmp.LoadBitmapW(IDB_PIKACU);  // 비트맵 리소스를 읽어온다
	pOldBmp = MemDC.SelectObject(&MyBmp);  // 메모리 DC에 비트맵 선택
	dc.BitBlt(100, 100, 300*2, 300 *2, &MemDC, 0, 0, SRCCOPY);  // 비트맵을 화면에 출력
	MemDC.SelectObject(pOldBmp);  // 비트맵 객체 해제
}


void CMy57View::OnBnClickedButton2()
{
	if (sig == NULL) {
		sig = new sign;
		sig->view = this; //뷰 자체의 위치
		sig->Create(IDD_DIALOG3);
		sig->ShowWindow(SW_SHOW);
	}
	else
		sig->SetFocus();
}

//로그인 구현
void CMy57View::OnBnClickedButton6()
{
	CString id = _T("");
	m_id.GetWindowText(id);
	CString pw = _T("");
	m_pw.GetWindowText(pw);
	CString str;
	user_id = "0000"; //유저아이디 기본값. 이후 수정할것.
	/*
	m_db.BeginTrans();
	try {
		CString str;
		str.Format(L"select EXISTS (select id from s2020116063.account where id='%s' and pwd='%s' limit 1) as success;", id, pw);
		m_db.ExecuteSQL(str);
		if (success == 0) {//존재한다.
			CString str1;
			MessageBox(L"환영합니다.");
		}
		else//존재하지 않는다.
			MessageBox(L"아이디 혹은 비밀번호가 잘못되었습니다. 아이디 혹은 비밀번호를 다시 입력하세요.");
	}
	catch (CException* e) {
		e->ReportError();
	}
	m_db.CommitTrans();
	*/
	str.Format(L"select * from s2020116063.account where id='%s' and pwd='%s' ;", id, pw);
	BOOL bopen = m_prs->Open(CRecordset::snapshot, str);
	BOOL beof = m_prs->IsEOF();

	if (!beof) {
		MessageBox(L"환영합니다.");
		//현재 유저 아이디 변수에 넣기
		user_id = id;
	}
	else
		MessageBox(L"아이디 혹은 비밀번호가 잘못되었습니다. 아이디 혹은 비밀번호를 다시 입력하세요.");

	m_prs->Close();

}

//아이디 찾기
void CMy57View::OnBnClickedButton8()
{
	if (fid == NULL) {
		fid = new findid;
		fid->view = this; //뷰 자체의 위치
		fid->Create(IDD_DIALOG4);
		fid->ShowWindow(SW_SHOW);
	}
	else
		fid->SetFocus();
}

//비밀번호 찾기
void CMy57View::OnBnClickedButton7()
{
	if (fpw == NULL) {
		fpw = new findpwd;
		fpw->view = this; //뷰 자체의 위치
		fpw->Create(IDD_DIALOG5);
		fpw->ShowWindow(SW_SHOW);
	}
	else
		fpw->SetFocus();
}

#include <stdlib.h>
void CMy57View::OnBnClickedButton9()//하루보내기새거
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("");
	CString dstr;
	CString sIndexValue = _T("");
	CString info;
	CString ttemp;
	CString mmoist;
	CString llight;
	CString ccycle;
	CString xtemp;
	CString xlight;
	CString xmoist;
	int popo;//건강도
	int hehe;//성장률

	BOOL bopen = m_prs->Open(CRecordset::snapshot, _T("SELECT * FROM report WHERE 1=1 AND day IN(SELECT MAX(day) FROM report)"));
	{

		int row = 1;

		BOOL beof = m_prs->IsEOF();
		DWORD dwsize = m_prs->GetRowsetSize();
		if (!beof) {
			for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {

				m_prs->SetAbsolutePosition(row);
				m_prs->GetFieldValue(3, info);
				row++;

				CString sdtr = _T("");
				sdtr.Format(L"SELECT * FROM rule WHERE name='%s'", info);
				BOOL bopen = m_ppt->Open(CRecordset::snapshot, sdtr);


				int xrow = 1;

				BOOL beof = m_ppt->IsEOF();
				DWORD dwsize = m_ppt->GetRowsetSize();
				if (!beof) {
					for (m_ppt->MoveFirst(); !m_ppt->IsEOF(); m_ppt->MoveNext()) {

						int fieldc = m_ppt->GetODBCFieldCount();
						popo = 0;
						hehe = 0;
						m_ppt->SetAbsolutePosition(xrow);

						m_ppt->SetAbsolutePosition(xrow);//@@@@@@@@계산하는곳
						m_ppt->GetFieldValue(1, ttemp);
						m_ppt->GetFieldValue(2, mmoist);
						m_ppt->GetFieldValue(3, llight);
						m_ppt->GetFieldValue(4, ccycle);

						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

						sdtr.Format(L"SELECT * FROM weather WHERE date in (SELECT MAX(day) FROM report)");
						BOOL bopen = m_paa->Open(CRecordset::snapshot, sdtr);
						{
							int trow = 1;
							BOOL beof = m_paa->IsEOF();
							DWORD dwsize = m_paa->GetRowsetSize();
							if (!beof) {
								for (m_paa->MoveFirst(); !m_paa->IsEOF(); m_paa->MoveNext()) {
									m_paa->SetAbsolutePosition(trow);

									m_paa->GetFieldValue(1, xtemp);
									m_paa->GetFieldValue(2, xmoist);
									m_paa->GetFieldValue(3, xlight);


								}
							}

						}
						m_paa->Close();





						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//hehe = _ttoi(ttemp);
						if (abs(_ttoi(ttemp) - _ttoi(xtemp)) > 10) {//온도
							popo++;
							AfxMessageBox(L"적정 온도에서 벗어났습니다.");
						}
						else {
							hehe++;
							popo--;
						}

						if (abs(_ttoi(mmoist) - _ttoi(xmoist)) > 20) {//습도
							popo++;
							AfxMessageBox(L"적정 습도에서 벗어났습니다.");
						}
						else {
							hehe++;
							popo--;
						}

						if (abs(_ttoi(llight) - _ttoi(xlight)) > 10) {//빛
							popo++;

							AfxMessageBox(L"적정 광량에서 벗어났습니다.");
						}
						else {
							hehe++;
							popo--;
						}

						if (abs(_ttoi(ccycle) - 10) > 5)//새로넣음
							popo++;
						else
							hehe++;

						/*
						hehe = _ttoi(mmoist);
						hehe = _ttoi(llight);
						hehe = _ttoi(ccycle);
						hehe /= 4;
						*/
					}
					AfxMessageBox(str);
				}

				m_ppt->Close();



				//	hehe = 10;

				dstr.Format(L"insert into s2020116063.`report`(ID,day,line,name,disease,health,growth) SELECT ID,date_add(day,INTERVAL 1 DAY)as day,line,name,disease,health-%d,growth+%d FROM report WHERE 1=1 AND day IN(SELECT MAX(day) FROM report)", popo, hehe);

				m_db.ExecuteSQL(dstr);


				int t = row - 1;
				if (t == dwsize)
					break;


			}
		}

		m_prs->Close();
	}
}




void CMy57View::Oncome()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CString str = _T("");
	CString dstr;
	CString sIndexValue = _T("");
	CString info;
	CString ttemp;
	CString mmoist;
	CString llight;
	CString ccycle;
	CString xtemp;
	CString xlight;
	CString xmoist;
	int popo;//건강도
	int hehe;//성장률

	BOOL bopen = m_prs->Open(CRecordset::snapshot, _T("SELECT * FROM report WHERE 1=1 AND day IN(SELECT MAX(day) FROM report)"));
	{

		int row = 1;

		BOOL beof = m_prs->IsEOF();
		DWORD dwsize = m_prs->GetRowsetSize();
		if (!beof) {
			for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {

				m_prs->SetAbsolutePosition(row);
				m_prs->GetFieldValue(3, info);
				row++;

				CString sdtr = _T("");
				sdtr.Format(L"SELECT * FROM rule WHERE name='%s'", info);
				BOOL bopen = m_ppt->Open(CRecordset::snapshot, sdtr);


				int xrow = 1;

				BOOL beof = m_ppt->IsEOF();
				DWORD dwsize = m_ppt->GetRowsetSize();
				if (!beof) {
					for (m_ppt->MoveFirst(); !m_ppt->IsEOF(); m_ppt->MoveNext()) {

						int fieldc = m_ppt->GetODBCFieldCount();
						popo = 0;
						hehe = 0;
						m_ppt->SetAbsolutePosition(xrow);

						m_ppt->SetAbsolutePosition(xrow);//@@@@@@@@계산하는곳
						m_ppt->GetFieldValue(1, ttemp);
						m_ppt->GetFieldValue(2, mmoist);
						m_ppt->GetFieldValue(3, llight);
						m_ppt->GetFieldValue(4, ccycle);

						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

						sdtr.Format(L"SELECT * FROM weather WHERE date in (SELECT MAX(day) FROM report)");
						BOOL bopen = m_paa->Open(CRecordset::snapshot, sdtr);
						{
							int trow = 1;
							BOOL beof = m_paa->IsEOF();
							DWORD dwsize = m_paa->GetRowsetSize();
							if (!beof) {
								for (m_paa->MoveFirst(); !m_paa->IsEOF(); m_paa->MoveNext()) {
									m_paa->SetAbsolutePosition(trow);

									m_paa->GetFieldValue(1, xtemp);
									m_paa->GetFieldValue(2, xmoist);
									m_paa->GetFieldValue(3, xlight);


								}
							}

						}
						m_paa->Close();





						//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
						//hehe = _ttoi(ttemp);
						if (abs(_ttoi(ttemp) - _ttoi(xtemp)) > 10) {//온도
							popo++;
							AfxMessageBox(L"적정 온도에서 벗어났습니다.");
						}
						else {
							hehe++;
							popo--;
						}

						if (abs(_ttoi(mmoist) - _ttoi(xmoist)) > 20) {//습도
							popo++;
							AfxMessageBox(L"적정 습도에서 벗어났습니다.");
						}
						else {
							hehe++;
							popo--;
						}

						if (abs(_ttoi(llight) - _ttoi(xlight)) > 10) {//빛
							popo++;

							AfxMessageBox(L"적정 광량에서 벗어났습니다.");
						}
						else {
							hehe++;
							popo--;
						}

						if (abs(_ttoi(ccycle) - 10) > 5)//새로넣음
							popo++;
						else
							hehe++;

						/*
						hehe = _ttoi(mmoist);
						hehe = _ttoi(llight);
						hehe = _ttoi(ccycle);
						hehe /= 4;
						*/
					}
					AfxMessageBox(str);
				}

				m_ppt->Close();



				//	hehe = 10;

				dstr.Format(L"insert into s2020116063.`report`(ID,day,line,name,disease,health,growth) SELECT ID,date_add(day,INTERVAL 1 DAY)as day,line,name,disease,health-%d,growth+%d FROM report WHERE 1=1 AND day IN(SELECT MAX(day) FROM report)", popo, hehe);

				m_db.ExecuteSQL(dstr);


				int t = row - 1;
				if (t == dwsize)
					break;


			}
		}

		m_prs->Close();
	}

}
