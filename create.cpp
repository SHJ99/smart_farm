// create.cpp: 구현 파일
//

#include "pch.h"
#include "5_7.h"
#include "create.h"
#include "afxdialogex.h"

#include "5_7Doc.h"
#include "5_7View.h"

// create 대화 상자

IMPLEMENT_DYNAMIC(create, CDialogEx)

create::create(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

create::~create()
{
}

void create::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_line);
	DDX_Control(pDX, IDC_LIST1, m_create);
	DDX_Control(pDX, IDC_COMBO2, m_temp);
	DDX_Control(pDX, IDC_COMBO3, m_moist);
	DDX_Control(pDX, IDC_COMBO5, m_light);
	DDX_Control(pDX, IDC_COMBO4, m_cycle);
	DDX_Control(pDX, IDC_EDIT1, m_name);
}


BEGIN_MESSAGE_MAP(create, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &create::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &create::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &create::OnBnClickedButton1)
END_MESSAGE_MAP()


// create 메시지 처리기



void create::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	CDialogEx::PostNcDestroy();
	view->cre = NULL;
	delete this;
}


BOOL create::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_create.InsertColumn(0, _T("작물이름"), LVCFMT_CENTER, 70, -1);
	m_create.InsertColumn(1, _T("라인"), LVCFMT_CENTER, 50, -1);
	m_create.InsertColumn(2, _T("적정온도"), LVCFMT_CENTER, 70, -1);
	m_create.InsertColumn(3, _T("적정습도"), LVCFMT_CENTER, 70, -1);
	m_create.InsertColumn(4, _T("적정일조량"), LVCFMT_CENTER, 90, -1);
	m_create.InsertColumn(5, _T("물주는주기"), LVCFMT_CENTER, 90, -1);


	BOOL bopen = m_db.OpenEx(_T("DSN=2020116063;SERVER=155.230.235.248;PORT=34056;UID=2020116063;PWD=whgdkdy22!!;DATABASE=s2020116063;"), CDatabase::noOdbcDialog);
	if (bopen) {
		m_prs = new CRecordset(&m_db);
		//m_prs2 = new CRecordset(&m_db);
	}

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	check2 = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

//화면 닫기
void create::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DestroyWindow();
	//CDialogEx::OnCancel();
}

//생성하기
void create::OnBnClickedOk()
{
	UpdateData(TRUE);
	CString name = _T("");
	CString db_name;
	CString get_line;
	int count;
	m_name.GetWindowText(name); //리스트 컨트롤 입력 받아오기
	int check = 0;
	//int check2 = 0;

	CString get_temp;
	CString get_moist;
	CString get_light;
	CString get_cycle;
	/*
	//화면의 combobox 값을 int 으로 받아옴.
	int line = GetDlgItemInt(IDC_COMBO1); //pk임.
	int temp = GetDlgItemInt(IDC_COMBO2);
	int moist = GetDlgItemInt(IDC_COMBO3);
	int light = GetDlgItemInt(IDC_COMBO5);
	int cycle = GetDlgItemInt(IDC_COMBO4);

	//생성하기
	m_db.BeginTrans();
	try {
		CString str;
		//str.Format(L"insert into testtable(id1, id2) values (%d, %d)",id1, id2);
		str.Format(L"insert into mfctestdb.`2020116063_t`(line, temp, moist, light, cycle, name) values(%d, %d, %d, %d, %d, '%s')", line, temp, moist, light, cycle, name);
		m_db.ExecuteSQL(str);

		//CString str1;
		//str.Format(L"insert into testtable(id1, id2) values (%d, %d)",id1, id2);
		//st1r.Format(L"create  mfctestdb.`2020116063_t`(line, temp, moist, light, cycle, name) values(%d, %d, %d, %d, %d, '%s')", DATE);
		//m_db.ExecuteSQL(str1);
	}
	catch (CException* e) {
		e->ReportError();
	}
	m_db.CommitTrans();
	*/

	//listcontrol에서 불러오기
	CString str, today;
	BOOL bopen = m_prs->Open(CRecordset::snapshot, _T("SELECT * FROM s2020116063.rule"));
	BOOL beof = m_prs->IsEOF();
	DWORD dwsize = m_prs->GetRowsetSize();
	CString id = view->user_id;
	CTime m_time;
	view->view_date.GetTime(m_time);
	today = m_time.Format(L"%Y-%m-%d");
	//if (!beof) {
	for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {
		check = 0;
		count = m_create.GetItemCount(); //현재 리스트 컨트롤에 있는원소 개수
		m_prs->GetFieldValue(L"name", db_name);//DB 작물이름 받아오기

		if (!name.Compare(db_name)) {
			//AfxMessageBox(db_name); //테스트
			m_create.InsertItem(count, name);
			m_line.GetWindowText(get_line); //라인 번호 받아오기
			m_create.SetItemText(count, 1, get_line);
			for (int i = 1; i < 5; i++) {
				m_prs->GetFieldValue(i, str);
				m_create.SetItemText(count, i + 1, str);
			}
			check++;
			//심은 작물 리포트에 넣기
			str.Format(L"insert into s2020116063.report(ID, day, line, name, disease, health, growth) values('%s', '%s', %d, '%s', '%s', %d, %d)",
				id, today, _ttoi(get_line), name, L"-", 0, 100);
			m_db.ExecuteSQL(str);

			break;
		}

	} //for
	//check2 = 0;
	if (!check && !check2) { //데이터베이스에 해당 작물이 없을 경우
		//check2 = 0;
		//if (!check2) {
		if (IDYES == AfxMessageBox(L"작물정보 없음. \n새로 등록하시겠습니까?", MB_YESNO))
			check2++;
		//}

	}
	else if (check2) {
		//m_line.GetWindowText(get_line);
		m_temp.GetWindowText(get_temp); //습도 입력 받아오기
		m_moist.GetWindowText(get_moist);
		m_light.GetWindowText(get_light);
		m_cycle.GetWindowText(get_cycle);
		str.Format(L"insert into s2020116063.rule(name, temp, moist, light, cycle) values('%s', %d, %d, %d, %d)",
			name, _tstoi(get_temp), _tstoi(get_moist), _tstoi(get_light), _tstoi(get_cycle));
		m_db.ExecuteSQL(str);
		check2 = 0;
		AfxMessageBox(L"성공적으로 등록됨");
		//AfxMessageBox(str);
	}


	//count = m_create.GetItemCount();
//}

	m_prs->Close();
	UpdateData(FALSE);
	
	
	//listcontrol에서 불러오기
}

//str.Format(L"create table '%d' (name varchar(20), sex char(1), birth date, phone varchar(16), email varchar(32);", 1010222);
//파일 불러오기
void create::OnBnClickedButton1()
{
	UpdateData(TRUE);
	int n;
	CString str = _T("");
	CString sIndexValue = _T("");
	//원하는 DB 테이블에 연결한다.
	//str.Format(L"");
	//m_prs2->Open(CRecordset::snapshot, _T("SELECT line FROM s2020116063.report where ID='test' "));
	//m_prs2->MoveFirst();
	//for (m_prs2->MoveFirst(); !m_prs2->IsEOF(); m_prs2->MoveNext()) {

	//}
	//m_prs2->MoveNext();
	//m_prs2->MoveNext();
	//	m_prs2->GetFieldValue(L"line", str);
	//AfxMessageBox(str);
	CString id = view->user_id;
	str.Format(L"SELECT s2020116063.rule.*, s2020116063.report.line FROM s2020116063.rule, s2020116063.report where s2020116063.rule.name=s2020116063.report.name and s2020116063.report.ID = id");
	//이후 id 정보 윗줄에 추가할것
	BOOL bopen = m_prs->Open(CRecordset::snapshot, str);

	{
		//첫 번째 줄부터 읽어온다
		//int row = 1;
		//파일이 끝나는 줄
		BOOL beof = m_prs->IsEOF();
		DWORD dwsize = m_prs->GetRowsetSize();
		int fieldc = m_prs->GetRecordCount();
		//AfxMessageBox(str);
		str.Format(L"%d", fieldc);
		if (!beof) {
			for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {
				for (int i = 0; i < fieldc; i++) {
					CString info;
					m_prs->GetFieldValue(L"name", info);
					m_create.InsertItem(i, info);
					m_prs->GetFieldValue(L"line", info);
					m_create.SetItemText(i, 1, info);
					m_prs->GetFieldValue(L"temp", info);
					m_create.SetItemText(i, 2, info);
					m_prs->GetFieldValue(L"moist", info);
					m_create.SetItemText(i, 3, info);
					m_prs->GetFieldValue(L"light", info);
					m_create.SetItemText(i, 4, info);
					m_prs->GetFieldValue(L"cycle", info);
					m_create.SetItemText(i, 5, info);
				} // for i			
			} // for m_prs
		} // if 

		m_prs->Close();
	}
	UpdateData(FALSE);
}
