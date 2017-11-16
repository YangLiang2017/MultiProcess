
// multitestDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "multitest.h"
#include "multitestDlg.h"
#include "afxdialogex.h"
#include "channel.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmultitestDlg �Ի���




CmultitestDlg::CmultitestDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmultitestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmultitestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmultitestDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CmultitestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CmultitestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CmultitestDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CmultitestDlg ��Ϣ�������

BOOL CmultitestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CmultitestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmultitestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmultitestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmultitestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	#ifdef  UNICODE   
	wchar_t szCommandLine[]=_T("cmd"); 
#else  
	char szCommandLine[]="cmd";
#endif 

	STARTUPINFO si={sizeof(si)};
	PROCESS_INFORMATION pi;
	si.dwFlags=STARTF_USESHOWWINDOW;
	si.wShowWindow=true;

	bool bRet=::CreateProcess(
		NULL,
		szCommandLine,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi);
	if(bRet)
	{
		::CloseHandle(pi.hThread);
		::CloseHandle(pi.hProcess);
		printf("�½��̵Ľ���ID�ţ�%d\n",pi.dwProcessId);
		printf("�½��̵����̵߳�ID�ţ�%d\n",pi.dwThreadId);

	}

	   bRet=::CreateProcess(
		NULL,
		szCommandLine,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi);
	if(bRet)
	{
		::CloseHandle(pi.hThread);
		::CloseHandle(pi.hProcess);
		printf("�½��̵Ľ���ID�ţ�%d\n",pi.dwProcessId);
		printf("�½��̵����̵߳�ID�ţ�%d\n",pi.dwThreadId);

	}







}


UINT  myproc(LPVOID  lParam)  
{  
   CmultitestDlg *pWnd = (CmultitestDlg *)lParam;         //������ָ�븳��������ָ��  
                        //Ҫִ�еĺ��� 
   bool fma=false,avx=false;
	runtime_check(&fma,&avx);
	if(fma)
		MessageBoxW(pWnd->GetSafeHwnd(), _T("suss"),_T(""),0);
    return 1;  
}  
  
 


void CmultitestDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	bool fma=false,avx=false;
	runtime_check(&fma,&avx);
	if(fma)
		MessageBoxW(_T("suss"));

		runtime_check(&fma,&avx);
	if(avx)
		MessageBoxW(_T("suss2"));


}






#define THREAD_POOL_SIZE 3
#define NUM_TASKS 3


typedef struct subthreaddata {
   CmultitestDlg* point;    
   int threadid;  
};

int g_value[10];

DWORD WINAPI ThreadFunc(LPVOID lParam)
{
	subthreaddata *pWnd = (subthreaddata *)lParam;         //������ָ�븳��������ָ��  
	bool fma=false,avx=false;
	runtime_check(&fma,&avx);
	char str[2];
	int a=pWnd->threadid;//int(lParam);
	wchar_t szBuf[4]=_T("YL");
    wsprintf(szBuf, L"%d", a);
    LPCTSTR lpText   = (LPCTSTR)(szBuf);
   // AfxMessageBox(lpText);
	g_value[a]=a;
	delete lParam;    //�ǵ�ɾ��
    lParam = NULL;
	return 1;//((DWORD)pWnd->threadid);
}



void CmultitestDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	HANDLE  hThrds[THREAD_POOL_SIZE];
    int     slot = 0;
    DWORD   threadId;
    int     i;
    DWORD   rc;
    for (i=0; i<NUM_TASKS; i++)
    {
		subthreaddata*pSParam=new subthreaddata; 
	    pSParam->point=this;
		pSParam->threadid=i;
        hThrds[i] = CreateThread(NULL,
            0,
            ThreadFunc,
            (LPVOID)pSParam,
            0,
            &threadId );
    }

    /* Now wait for all threads to terminate */
    rc = WaitForMultipleObjects(
        NUM_TASKS,
        hThrds,
        TRUE,
        INFINITE );
    assert( rc >= WAIT_OBJECT_0
             && rc < WAIT_OBJECT_0+NUM_TASKS);
    for (slot=0; slot<NUM_TASKS; slot++)
         CloseHandle(hThrds[slot]) ;

	CString   theString; 
	  for (i=0; i<NUM_TASKS; i++)
    {
		
	    CString   theStringtemp; 
		theStringtemp.Format(_T( "%d "),   g_value[i]); 
		theString+=theStringtemp;
		
    }

	  LPCTSTR   lpText; 
	  lpText   =   (LPCTSTR)theString;
      MessageBoxW(lpText);
      MessageBoxW(_T("All  terminated"));


}


