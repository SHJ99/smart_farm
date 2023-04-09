// report.cpp: 구현 파일
//

#include "pch.h"
#include "5_7.h"
#include "report.h"
#include "afxdialogex.h"

#include "5_7Doc.h"
#include "5_7View.h"

// report 대화 상자

IMPLEMENT_DYNAMIC(report, CDialogEx)

report::report(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

report::~report()
{
}

void report::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_report);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_start);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_end);
}


BEGIN_MESSAGE_MAP(report, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &report::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &report::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON3, &report::OnBnClickedButton3)
END_MESSAGE_MAP()


// report 메시지 처리기


void report::OnBnClickedButton1()
{

	// 체크박스 1, 비료줬는지
	// 체크박스 2, 물 줬는지
	// 
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);
	CString str, str2, start_time, end_time;
	CTime m_time, m_time2;
	m_start.GetTime(m_time);
	start_time = m_time.Format(L"%Y-%m-%d");	
	m_end.GetTime(m_time2);
	end_time=m_time2.Format(L"%Y-%m-%d");
	CString id = view->user_id;

	//str.Format(L"%Y-%m-%d", m_time.GetYear(), m_time.GetMonth(), m_time.GetDay());
	//AfxMessageBox(str);
	//end_time = m_time.Format(L"%Y-%m-%d");
	//AfxMessageBox(end_time);
	//typeid('2022-10-01').name()
	//AfxMessageBox(L"%s",typeid('2022-10-01').name());
	// and (day>'2022-04-01' or day<'2022-06_01')  and day>'2022-10-01' and day<'2022-10-15'
	//and day<('%d'-'%d'-'%d')", m_time.GetYear(), m_time.GetMonth(), m_time.GetDay() ));
	str2.Format(L"SELECT * FROM s2020116063.report WHERE ID='%s' and DATE(day) BETWEEN '%s' AND '%s'; ", id, start_time, end_time);

	BOOL bopen = my_prs->Open(CRecordset::snapshot, str2);
	DWORD dwsize = my_prs->GetRowsetSize();
	//my_prs->GetFieldValue(L"day", str2);

	int index = m_report.GetItemCount();;
	/*
	m_report.InsertItem(0, index);
	m_report.SetItemText(0, 1, str2);
	m_report.SetItemText(0, 2, L"ss");
	m_report.SetItemText(0, 3, L"dd");
	m_report.SetItemText(0, 4, L"ff");
	m_report.SetItemText(0, 5, L"gg");
	m_report.SetItemText(0, 6, L"hh");
	*/
	for (my_prs->MoveFirst(); !my_prs->IsEOF(); my_prs->MoveNext()) {
		//for (int i = 1; i < 2; i++) {
		str2.Format(L"%d", index);
		m_report.InsertItem(0, str2);

		my_prs->GetFieldValue(L"day", str);
		m_report.SetItemText(index, 1, str);
		my_prs->GetFieldValue(L"line", str);
		m_report.SetItemText(index, 2, str);
		my_prs->GetFieldValue(L"name", str);
		m_report.SetItemText(index, 3, str);
		my_prs->GetFieldValue(L"disease", str);
		m_report.SetItemText(index, 4, str);
		my_prs->GetFieldValue(L"health", str);
		m_report.SetItemText(index, 5, str);
		my_prs->GetFieldValue(L"growth", str);
		m_report.SetItemText(index, 6, str);

		//}
	}
	my_prs->Close();
	UpdateData(FALSE);
}

//로그
BOOL report::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_report.InsertColumn(0, _T("인덱스"), LVCFMT_CENTER, 70, -1);
	m_report.InsertColumn(1, _T("날짜"), LVCFMT_CENTER, 100, -1);
	m_report.InsertColumn(2, _T("라인"), LVCFMT_CENTER, 50, -1);
	m_report.InsertColumn(3, _T("작물이름"), LVCFMT_CENTER, 80, -1);
	m_report.InsertColumn(4, _T("병충해"), LVCFMT_CENTER, 70, -1); // 습도가 높을 시 곰팡이감염, 온도가 높을 시  저해, 일조량 높을시 : 마름병 
	m_report.InsertColumn(5, _T("건강도"), LVCFMT_CENTER, 70, -1); //습도, 일조량, 온도 다 통합해서 범위에 벗어나는것 1개씩 있으면 25%씩 깎음(건강 최상: 100%)
	m_report.InsertColumn(6, _T("성장률"), LVCFMT_CENTER, 70, -1);//(100% 넘어가면 수확함)

	BOOL bopen = my_db.OpenEx(_T("DSN=2020116063;SERVER=155.230.235.248;PORT=34056;UID=2020116063;PWD=whgdkdy22!!;DATABASE=s2020116063;"), CDatabase::noOdbcDialog);
	if (bopen)
		my_prs = new CRecordset(&my_db);




	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void report::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::PostNcDestroy();
	view->rep = NULL;
	delete this;
}


void report::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DestroyWindow();
	//CDialogEx::OnCancel();
}


void report::OnBnClickedButton3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}
