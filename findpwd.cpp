// findpwd.cpp: 구현 파일
//

#include "pch.h"
#include "5_7.h"
#include "findpwd.h"
#include "afxdialogex.h"


#include "5_7Doc.h"
#include "5_7View.h"
// findpwd 대화 상자

IMPLEMENT_DYNAMIC(findpwd, CDialogEx)

findpwd::findpwd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG5, pParent)
{

	success = 0;
	check = 0;
}

findpwd::~findpwd()
{
}

void findpwd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_id);
	DDX_Control(pDX, IDC_EDIT2, m_name);
	DDX_Control(pDX, IDC_EDIT3, m_farmname);
	DDX_Control(pDX, IDC_EDIT4, m_pw);
	DDX_Control(pDX, IDC_EDIT5, m_pw1);
}


BEGIN_MESSAGE_MAP(findpwd, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &findpwd::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &findpwd::OnBnClickedButton1)
	ON_BN_CLICKED(IDOK, &findpwd::OnBnClickedOk)
END_MESSAGE_MAP()


// findpwd 메시지 처리기


BOOL findpwd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	BOOL bopen = m_db.OpenEx(_T("DSN=2020116063;SERVER=155.230.235.248;PORT=34056;UID=2020116063;PWD=whgdkdy22!!;DATABASE=s2020116063;"), CDatabase::noOdbcDialog);
	if (bopen)
		m_prs = new CRecordset(&m_db);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void findpwd::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CDialogEx::PostNcDestroy();
	view->fpw = NULL;
	delete this;
}


void findpwd::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DestroyWindow();
}


void findpwd::OnBnClickedButton1()
{
	CString id = _T("");
	m_id.GetWindowText(id);
	CString name = _T("");
	m_name.GetWindowText(name);
	CString farmname = _T("");
	m_farmname.GetWindowText(farmname);
	m_db.BeginTrans();
	try {
		CString str;
		str.Format(L"select EXISTS (select id from s2020116063.account where name='%s' and farmname='%s' limit 1) as success;", name, farmname);
		m_db.ExecuteSQL(str);
		if (success == 0) {//존재한다.
			CString str1;
			MessageBox(L"회원정보가 존재합니다. 비밀번호를 재설정하세요.");
		}
		else//존재하지 않는다.
			MessageBox(L"회원정보가 존재하지 않습니다. 회원정보를 다시 입력하세요.");
	}
	catch (CException* e) {
		e->ReportError();
	}
	m_db.CommitTrans();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

//비밀번호 재설정하기 : update 로 하기
void findpwd::OnBnClickedOk()
{
	success = 0;
	CString id = _T("");
	m_id.GetWindowText(id);
	CString name = _T("");
	m_name.GetWindowText(name);
	CString farmname = _T("");
	m_farmname.GetWindowText(farmname);

	CString pw = _T("");
	m_pw.GetWindowText(pw);
	CString pw1 = _T("");
	m_pw1.GetWindowText(pw1);
		if (pw.Compare(pw1) == 0) {//같을 경우
			m_db.BeginTrans();
			try {
				CString str;
				str.Format(L"UPDATE s2020116063.account SET pwd = '%s' WHERE  id = '%s' and name='%s' and farmname='%s'", pw, id, name, farmname);
				m_db.ExecuteSQL(str);
				MessageBox(L"비밀번호를 재설정했습니다.");
			}
			catch (CException* e) {
				e->ReportError();
			}
			m_db.CommitTrans();
		}
}
