// TestDllHost.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <windows.h>
#include <stdio.h>
#include <iostream>


BOOL CALLBACK EnumWindowsProc(
	_In_ HWND   hWnd,
	_In_ LPARAM lParam
) {
	printf("EnumWindowsProc hWnd: %08p\n", hWnd);
	return TRUE;
}

DWORD WINAPI SomeThread(LPVOID)
{
	while (true)
	{
		std::cout << "test\n";
		Sleep(1000);
	}
	return 0;
}


int main()
{
	// LoadLibraryA("BO4_Bypass_x64.dll");
	// getchar();

	// EnumWindows(EnumWindowsProc, NULL);


	auto hThread = CreateThread(nullptr, 0, SomeThread, nullptr, 0, nullptr);
	using p_NtSetInformationThread = NTSTATUS(NTAPI*) (HANDLE, UINT, PVOID, ULONG);
	p_NtSetInformationThread NtSetInformationThread = (p_NtSetInformationThread)GetProcAddress(GetModuleHandleA("ntdll.dll"), "NtSetInformationThread");
	NtSetInformationThread(hThread, 0x11, 0, 0); // ThreadHideFromDebugger
	WaitForSingleObject(hThread, INFINITE);


	// DWORD ProcessId;
	// GetWindowThreadProcessId(GetForegroundWindow(), &ProcessId);

	getchar();
	printf("Hello World!\n");
}
