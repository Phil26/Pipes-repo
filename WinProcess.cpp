#define _WIN32_WINNT 0x0501
#include <windows.h>
#include <stdio.h>

int main()
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    
    if (!CreateProcess
    (
        L"D:\\An III\\SO_labs\\Pipes\\HelloWorld\\HelloWorld.exe", 
        NULL,    
        FALSE,  
        NULL,    
        FALSE,  
        0,     
        NULL,    
        NULL,   
        &si,     
        &pi
    )     
        )

        printf("\nSorry! CreateProcess() failed.\n\n");

    else
    {
        printf("\nWell, CreateProcess() looks OK.\n");
        printf("exit after 5000 ms...\n\n");
    }

    WaitForSingleObject(pi.hProcess, 5000);
    printf("\n");
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    return 0;

}