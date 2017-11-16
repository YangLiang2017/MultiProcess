


#ifdef _MSC_VER
#include <windows.h>
#include <tchar.h>
#ifdef  UNICODE   
#define _tcscpy     wcscpy  
#define _tcslen     wcslen  
#define _tcscat     wcscat  
#else  
#define _tcscpy     strcpy  
#define _tcslen     strlen  
#define _tcscat     strcat  
#endif 
// 获取系统实际支持的指令集:
// 使用FMA/AVX参数依次运行runtime_check.exe, 若输出中包含"true", 则表示支持该指令集
#include"string"
using namespace std;
static bool runtime_check(bool *fma, bool *avx) {
	if (!fma || !avx) {
		return false;
	}
	*fma = false;
	*avx = false;
#ifdef  UNICODE   
	wchar_t exe[] = _T("runtime_check.exe ");
	wchar_t arg[2][4] = {_T("FMA"), _T("AVX")};
#else  
	char exe[] = "runtime_check.exe ";
	char arg[2][4] = {"FMA", "AVX"};
#endif 

	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	memset(&pi, 0, sizeof(PROCESS_INFORMATION));
	memset(&si, 0, sizeof(STARTUPINFO));
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags |= STARTF_USESTDHANDLES;	// STARTF_USESTDHANDLES is Required.
	si.dwFlags |= STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	int i;
	for (i = 0; i < 2; i++) {
		SECURITY_ATTRIBUTES saAttr;
		saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
		saAttr.bInheritHandle = TRUE;
		saAttr.lpSecurityDescriptor = NULL;

		HANDLE hChildStdoutRd = NULL; // Read-side, used in calls to ReadFile() to get child's stdout output.
		HANDLE hChildStdoutWr = NULL; // Write-side, given to child process using si struct.

		// Create a pipe to get results from child's stdout.
		if (!CreatePipe(&hChildStdoutRd, &hChildStdoutWr, &saAttr, 0)) {
			printf("cannot create pipe\n");
			return false;
		}
		// Ensure the read handle to the pipe for STDOUT is not inherited.
		if (!SetHandleInformation(hChildStdoutRd, HANDLE_FLAG_INHERIT, 0)) {
			printf("Stdout SetHandleInformation");
			return false;
		}

		si.hStdOutput = hChildStdoutWr;		// Requires STARTF_USESTDHANDLES in dwFlags.
		si.hStdError = hChildStdoutWr;		// Requires STARTF_USESTDHANDLES in dwFlags.


#ifdef  UNICODE   
		wchar_t *cmd = new wchar_t[_tcslen(exe) + _tcslen(arg[i]) + 1];
#else  
		char *cmd = new char[_tcslen(exe) + _tcslen(arg[i]) + 1];
#endif 
		_tcscpy(cmd, exe);
		_tcscat(cmd, arg[i]);
		BOOL bSuccess = CreateProcess(
			NULL,	// No module name (use command line)
			cmd,	// Command line
			NULL,	// Process handle not inheritable
			NULL,	// Thread handle not inheritable
			TRUE,	// Set handle inheritance to TRUE
			0,		// No creation flags
			NULL,	// Use parent's environment block
			NULL,	// Use parent's starting directory
			&si,	// Pointer to STARTUPINFO structure
			&pi);	// Pointer to PROCESS_INFORMATION structure

		delete[] cmd;
		if (bSuccess) {
			WaitForSingleObject(pi.hProcess, INFINITE);
			// Close the write end of the pipe before reading from the read end of the pipe.
			if (!CloseHandle(hChildStdoutWr)) {
				printf("cannot close handle");
				return false;
			}

			std::string strResult;
			// Read output from the child process.
			for (;;) {
				DWORD dwRead;
				char chBuf[64];
				// Read from pipe that is the standard output for child process.
				bSuccess = ReadFile(hChildStdoutRd, chBuf, 64, &dwRead, NULL);
				if (!bSuccess || 0 == dwRead) {
					break;
				}
				strResult += std::string(chBuf, dwRead);
			}
			if (strResult.length() > 0) {
				std::size_t pos = strResult.find(":");
				strResult = strResult.substr(pos + 2, 4);
				if (strResult == "true") {
					if (0 == i) *fma = true;
					if (1 == i) *avx = true;
				}
			}

			CloseHandle(hChildStdoutRd);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		} else {
			printf("CreateProcess failed: %d\n", GetLastError());

			
			return false;
		}
	}
	return true;
}
#endif // _MSC_VER




