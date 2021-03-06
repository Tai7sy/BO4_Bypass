// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
#include "Bypass.hpp"


VOID OnAttach(HMODULE hDll) {
	bool Error = true;
	char szError[1024] = { 0 };
	Error = Bypass::GetInstance()->Init(hDll);
	if (Error != true)
	{
		sprintf_s(szError, 1024, "[Bypass] Failed to initialize (errorcode : %i)\n", GetLastError());
		DbgLog::Log(szError);
		MessageBoxA(0, szError, "ERROR", MB_ICONERROR);
	}
	else {
		DbgLog::Log("[Bypass] Initialized successfully, hModule: %016llX.\n", (DWORD_PTR)hDll);
	}
	ModuleHidden::OnAttach(hDll);
}

VOID OnDetach() {
	bool Error = true;
	char szError[1024] = { 0 };
	Error = Bypass::GetInstance()->Uninit();
	if (Error != true)
	{
		sprintf_s(szError, 1024, "[Bypass] Failed to uninitialize (errorcode : %i)\n", GetLastError());
		DbgLog::Log(szError);
		MessageBoxA(0, szError, "ERROR", MB_ICONERROR);
	}
	ModuleHidden::OnDetach();
}



BOOL APIENTRY DllMain(
	HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		DbgLog::Log("[Bypass] DLL_PROCESS_ATTACH\n");
		OnAttach(hModule);
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		DbgLog::Log("[Bypass] DLL_PROCESS_DETACH\n");
		MessageBoxA(NULL, "BYPASS DLL_PROCESS_DETACH", NULL, MB_OK);
		OnDetach();
		break;
	}
	return TRUE;
}

