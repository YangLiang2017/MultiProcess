
// multitestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "multitest.h"
#include "multitestDlg.h"
#include "afxdialogex.h"
#include "channel.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CmultitestDlg 对话框




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


// CmultitestDlg 消息处理程序

BOOL CmultitestDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmultitestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmultitestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmultitestDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码

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
		printf("新进程的进程ID号：%d\n",pi.dwProcessId);
		printf("新进程的主线程的ID号：%d\n",pi.dwThreadId);

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
		printf("新进程的进程ID号：%d\n",pi.dwProcessId);
		printf("新进程的主线程的ID号：%d\n",pi.dwThreadId);

	}







}


UINT  myproc(LPVOID  lParam)  
{  
   CmultitestDlg *pWnd = (CmultitestDlg *)lParam;         //将窗口指针赋给无类型指针  
                        //要执行的函数 
   bool fma=false,avx=false;
	runtime_check(&fma,&avx);
	if(fma)
		MessageBoxW(pWnd->GetSafeHwnd(), _T("suss"),_T(""),0);
    return 1;  
}  
  
 


void CmultitestDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码

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
	subthreaddata *pWnd = (subthreaddata *)lParam;         //将窗口指针赋给无类型指针  
	bool fma=false,avx=false;
	runtime_check(&fma,&avx);
	char str[2];
	int a=pWnd->threadid;//int(lParam);
	wchar_t szBuf[4]=_T("YL");
    wsprintf(szBuf, L"%d", a);
    LPCTSTR lpText   = (LPCTSTR)(szBuf);
   // AfxMessageBox(lpText);
	g_value[a]=a;
	delete lParam;    //记得删除
    lParam = NULL;
	return 1;//((DWORD)pWnd->threadid);
}



void CmultitestDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码

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


