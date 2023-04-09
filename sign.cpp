// sign.cpp: 구현 파일
//
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include "pch.h"
#include "5_7.h"
#include "sign.h"
#include "afxdialogex.h"
#include "5_7Doc.h"
#include "5_7View.h"
#include <Windows.h>
#include <atlstr.h>

#define MAX_PASS 32 
#define MY_PASS "HAHAHA"

using namespace std;
// sign 대화 상자

IMPLEMENT_DYNAMIC(sign, CDialogEx)

sign::sign(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG3, pParent)
{

	check = 0;
	success = 0;
}

sign::~sign()
{
}

void sign::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_id);
	DDX_Control(pDX, IDC_EDIT2, m_pw);
	DDX_Control(pDX, IDC_EDIT3, m_pw1);
	DDX_Control(pDX, IDC_EDIT4, m_name);
	DDX_Control(pDX, IDC_EDIT5, m_farmname);
	DDX_Control(pDX, IDC_RADIO1, m_farmer);
	DDX_Control(pDX, IDC_RADIO2, m_reservefarmer);
	DDX_Control(pDX, IDC_RADIO3, m_farm);
}


BEGIN_MESSAGE_MAP(sign, CDialogEx)
	ON_BN_CLICKED(IDOK, &sign::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &sign::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &sign::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &sign::OnBnClickedButton2)
END_MESSAGE_MAP()


// sign 메시지 처리기


void sign::PostNcDestroy()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CDialogEx::PostNcDestroy();
	view->cre = NULL;
	delete this;
}


void sign::OnBnClickedOk()
{
	if (check == 0) {
		CString type;
		int check1state = IsDlgButtonChecked(IDC_RADIO1);//farmer
		int check2state = IsDlgButtonChecked(IDC_RADIO2);//reservefarmer
		int check3state = IsDlgButtonChecked(IDC_RADIO3);//farm

		CString id = _T("");
		m_id.GetWindowText(id);

		CString pwd = _T("");
		m_pw.GetWindowText(pwd);

		CString pwd1 = _T("");
		m_pw1.GetWindowText(pwd1);

		if (pwd.Compare(pwd1) == 0) {
			CString name = _T("");
			m_name.GetWindowText(name);

			CString farmname = _T("");
			m_farmname.GetWindowText(farmname);

			if (check1state) {
				type = _T("farmer");

			}
			if (check2state) {
				type = _T("reservefarmer");

			}
			if (check3state) {
				type = _T("farm");

			}
			
			char szWork[MAX_PASS];
			pwd.Format(L"%s", szWork);
			EnCode(szWork);
			CString strWork;
			printf("Encoded : %s\n", szWork);
			
			m_db.BeginTrans();
			try {
				CString str;
				str.Format(L"insert into s2020116063.account(id, pwd, name, farmname, type) values('%s', '%s', '%s', '%s', '%s')", id, strWork, name, farmname, type);
				m_db.ExecuteSQL(str);
				MessageBox(L"회원가입 성공! 스마트팜과 함께 하는 즐거운 농사!");
			}

			catch (CException* e) {
				e->ReportError();
			}
			m_db.CommitTrans();

		}//pwd 비교
	}//check
}


void sign::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	DestroyWindow();
}


BOOL sign::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	BOOL bopen = m_db.OpenEx(_T("DSN=2020116063;SERVER=155.230.235.248;PORT=34056;UID=2020116063;PWD=whgdkdy22!!;DATABASE=s2020116063;"), CDatabase::noOdbcDialog);
	if (bopen)
		m_prs = new CRecordset(&m_db);


	return TRUE;  
}

//중복검사
void sign::OnBnClickedButton1()
{
	CString id = _T("");
	m_id.GetWindowText(id);
	int check = 0;
	CString str;
	CString str1;
	str1.Format(L"select count(id) from s2020116063.account where id='%s';", id);
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
				int i = 0;
				CString info;
				m_prs->SetAbsolutePosition(row);
				m_prs->GetFieldValue(i, info);//i번째 값 : info
				str = str + " " + info;
				str += "\n";
				row++;
			} // for m_prs
		} // if 
		//AfxMessageBox(str);
		int n = _tstoi(str);
		if (n == 0) {//아이디 중복 없음
			MessageBox(L"아이디가 중복되지 않았습니다. 비밀번호를 설정해 주세요.");
		}
		else {
			MessageBox(L"아이디가 중복되었습니다. 다시 입력하세요.");
			m_id.Clear();
			check++;
		}
		m_prs->Close();
	}

}

//비밀번호 중복검사
void sign::OnBnClickedButton2()
{
	CString pwd = _T("");
	m_pw.GetWindowText(pwd);

	CString pwd1 = _T("");
	m_pw1.GetWindowText(pwd1);

	if (pwd.Compare(pwd1) == 1) {
		check++;
		MessageBox(L"비밀번호 입력 실패, 다시 입력하세요.");
		
	}
	else
		MessageBox(L"비밀번호 입력 성공");
}


int sign::EnCode(char* pszCode)
{
	HCRYPTPROV hProv;
	HCRYPTHASH hHash;
	HCRYPTKEY hKey;
	BYTE pbCode[MAX_PASS];
	DWORD dwDataLen;
	ZeroMemory(pbCode, MAX_PASS);
	sprintf((char*)pbCode, "%s", pszCode);
	dwDataLen = (DWORD)strlen((char*)pbCode) + 1; // CSP(Crystographic Service Provider) 핸들 얻기 
	if (CryptAcquireContext(&hProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, 0)) { // 해쉬 만들기 
		if (CryptCreateHash(hProv, CALG_SHA, 0, 0, &hHash)) { // 해쉬 값 계산 
			if (CryptHashData(hHash, (BYTE*)MY_PASS, (DWORD)strlen(MY_PASS), 0)) { // 키 만들기 
				if (CryptDeriveKey(hProv, CALG_RC4, hHash, CRYPT_EXPORTABLE, &hKey)) { // 암호화\tab 
					if (CryptEncrypt(hKey, 0, TRUE, 0, pbCode, &dwDataLen, MAX_PASS)) { sprintf(pszCode, "%s", (char*)pbCode); }
					else {
						return 5; // 암호화 에러
					}
				}
				else {
					return 4; // 키 만들기 에러 
				}
			}
			else {
				return 3; // 해쉬 값 계산 에러
			}
		}
		else {
			return 2; // 해쉬 만들기 에러 
		}
	}
	else { // 유저용 키 컨테이너 만들기 
		if (!CryptAcquireContext(&hProv, NULL, MS_ENHANCED_PROV, PROV_RSA_FULL, CRYPT_NEWKEYSET)) {
			return 1; // 유저용 키 켄테이너 만들기 에러
		}
	} // 해쉬 없애기 
	CryptDestroyHash(hHash); // CSP 핸들 풀어주기 
	CryptReleaseContext(hProv, 0);
	return 0;
}
