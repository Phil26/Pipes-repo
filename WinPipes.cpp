#pragma
#include <Windows.h>
#include <iostream>
#define PROCESSES_NUM 10
#define ARRAY_SIZE 10000
using namespace std;

int main()
{
	HANDLE hProcess = NULL;
	HANDLE hThread = NULL;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	DWORD dwProcessId = 0;
	DWORD dwThreadId = 0;
	ZeroMemory(&si, sizeof(si));
	ZeroMemory(&pi, sizeof(pi));
	BOOL bCreateProcess = NULL;

	BOOL bCreatePipe = NULL;
	HANDLE hRead;
	HANDLE hWrite;
	int numArray[ARRAY_SIZE];
	BOOL bWritefile;
	BOOL bReadfile;
	DWORD buffersize = sizeof(numArray);
	DWORD dwNoBytesWrite;
	DWORD dwNoBytesRead;

	for (int i = 1; i < ARRAY_SIZE; i++)
	{
		numArray[i] = i;
	}

	bCreatePipe = CreatePipe
	(
		&hRead,
		&hWrite,
		NULL,
		ARRAY_SIZE
	);

		if (bCreatePipe == FALSE)
		{
			cout << "Error " << GetLastError() << " occured when creating pipe." << endl;
		}

	cout << "Creating pipe successed.\n";

	bWritefile = WriteFile
	(
		hWrite,
		numArray,
		buffersize,
		&dwNoBytesWrite,
		NULL
	);
		CloseHandle(hWrite);

		bReadfile = ReadFile
		(
			hRead,
			numArray,
			buffersize,
			&dwNoBytesRead,
			NULL
		);
		CloseHandle(hRead);
		
	return 0;
}
