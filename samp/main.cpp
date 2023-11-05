#include <iostream>
#include <Windows.h>
#include "logger.hpp"
#include "samp.hpp"
#include "utils.hpp"

DWORD		SAMPHandle = NULL;
DWORD * pGame = NULL;
CNetGame * pNetGame = NULL;

void Start();

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		Log::Init();
		DisableThreadLibraryCalls(hModule);
		CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(Start), 0, 0, 0);
	}
	return TRUE;
}

void AddMessageJumpQ(const char* text, unsigned int time, unsigned short flag, bool bPreviousBrief) {
	((void(__cdecl*)(const char*, unsigned int, unsigned short, bool))0x69F1E0)(text, time, flag, bPreviousBrief);
}

void Start()
{
	bool Initialized = false;
	HWND SAMPWnd = NULL;
	while (!Initialized)
	{

#ifdef _DEBUG
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
#endif

		SAMPWnd = FindWindow(L"Grand theft auto San Andreas", NULL);
		if(SAMPWnd) {
			LOG << "Found GTA San Andreas window";
			while (true) 
			{
				SAMPHandle = reinterpret_cast<DWORD>(GetModuleHandle(L"samp.dll"));
				if(SAMPHandle) {

					pGame = *(DWORD **)(SAMPHandle + 0x21A10C);
					pNetGame = *(CNetGame **)(SAMPHandle + 0x21A0F8);

					if (pNetGame == nullptr) {
						Sleep(200);
						continue;
					}

					LOG << "Found an instance of CGame and CNetGame";
					AddMessageJumpQ("~b~Hello, electronjsc? Yeap, Hi!", 35000, 0, false);

					Initialized = true;
					break;
				}
			}
		};

		Sleep(200);
	}
}
