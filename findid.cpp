// findid.cpp: 구현 파일
//

#include "pch.h"
#include "5_7.h"
#include "findid.h"
#include "afxdialogex.h"

#include "5_7Doc.h"
#include "5_7View.h"

// findid 대화 상자

IMPLEMENT_DYNAMIC(findid, CDialogEx)

findid::findid(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG4, pParent)
{

	success = 0;
}

findid::~findid()
{
}

void findid::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_name);
	DDX_Control(pDX, IDC_EDIT2, m_farmname);
}


BEGIN_MESSAGE_MAP(findid, CDialogEx)
	ON_BN_CLICKED(IDOK, &findid::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &findid::OnBnClickedCancel)
END_MESSAGE_MAP()


// findid 메시지 처리기

//아이디찾기
void findid::OnBnClickedOk()
{
	CString id = _T("");
	CString name = _T("");
	m_name.GetWindowText(name);
	CString farmname = _T("");
	m_farmname.GetWindowText(farmname);
	CString str = _T("");
	CString sIndexValue = _T("");
	//원하는 DB 테이블에 연결한다.
	CString str1;
	str1.Format(L"select id from s2020116063.account where name='%s' and farmname='%s';", name, farmname);
	BOOL bopen = m_prs->Open(CRecordset::snapshot, str1);
	{
		//첫 번째 줄부터 읽어온다
		int row = 1;
		//파일이 끝나는 줄
		BOOL beof = m_prs->IsEOF();
		DWORD dwsize = m_prs->GetRowsetSize();
		if (!beof) {
			for (m_prs->MoveFirst(); !m_prs->IsEOF(); m_prs->MoveNext()) {
				//파일의 속성의 개수
				int fieldc = m_prs->GetODBCFieldCount();
				for (int i = 0; i < fieldc; i++) {
					CString info;
					m_prs->SetAbsolutePosition(row);
					m_prs->GetFieldValue(i, info);//i번째 값 : info
					str = str + " " + info;
				} 
				str += "\n";
				row++;
			} // for m_prs
		} // if 
		AfxMessageBox(str);
		m_prs->Close();
	}
	
}


BOOL findid::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	BOOL bopen = m_db.OpenEx(_T("DSN=2020116063;SERVER=155.230.235.248;PORT=34056;UID=2020116063;PWD=whgdkdy22!!;DATABASE=s2020116063;"), CDatabase::noOdbcDialog);
	if (bopen)
		m_prs = new CRecordset(&m_db);


	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void findid::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CDialogEx::PostNcDestroy();
	view->fid = NULL;
	delete this;
}


void findid::OnBnClickedCancel()
{
	DestroyWindow();
}
