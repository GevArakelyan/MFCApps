// WinVersionFinder.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>

#ifndef VER_PLATFORM_WIN32_CE
#define VER_PLATFORM_WIN32_CE 3
#endif
#include <cassert>


using namespace std;

enum PLATFORM { W_NOTDEF, W32S, W_CE, W95, W98, WME, NT4, NT5, NT5_0_1, XP, NET2003, VISTA, WIN7, WIN8, WIN8_1, WIN10, WIN11 };  // bug 48801-Correct Windows version is not being sent to the transmission logs
static const std::string szPLATFORMSTRING[] = { "W_NOTDEF", "W32S", "WCE", "W95", "W98", "WME", "NT4", "NT5", "NT5.0.1", "XP", "NET2003", "VISTA", "WIN7", "WIN8", "WIN8.1", "WIN10", "WIN11" }; // bug 48801-Correct Windows version is not being sent to the transmission logs

// bug 48801-Correct Windows version is not being sent to the transmission logs
BOOL GetNtVersionNumbers(DWORD& dwMajorVer, DWORD& dwMinorVer, DWORD& dwBuildNumber)
{
	BOOL bRet = FALSE;
	HMODULE hModNtdll = NULL;
	if (hModNtdll = ::LoadLibraryW(L"ntdll.dll"))
	{
		typedef void (WINAPI* pfRTLGETNTVERSIONNUMBERS)(DWORD*, DWORD*, DWORD*);
		pfRTLGETNTVERSIONNUMBERS pfRtlGetNtVersionNumbers;
		pfRtlGetNtVersionNumbers = (pfRTLGETNTVERSIONNUMBERS)::GetProcAddress(hModNtdll, "RtlGetNtVersionNumbers");
		if (pfRtlGetNtVersionNumbers)
		{
			pfRtlGetNtVersionNumbers(&dwMajorVer, &dwMinorVer, &dwBuildNumber);
			dwBuildNumber &= 0x0ffff;
			bRet = TRUE;
		}

		::FreeLibrary(hModNtdll);
		hModNtdll = NULL;
	}

	return bRet;
}


PLATFORM GetPlatformVersion()
{
	try
	{
		OSVERSIONINFOEX osvi;
		BOOL bOsVersionInfoEx;

		ZeroMemory(&osvi, sizeof(OSVERSIONINFOEX));
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

#pragma warning(push)
#pragma warning(disable:4996)
		if (!(bOsVersionInfoEx = GetVersionEx((OSVERSIONINFO*)&osvi)))
		{
			osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
			if (!GetVersionEx((OSVERSIONINFO*)&osvi))
			{
				return W_NOTDEF;
			}
		}
#pragma warning(pop)

		switch (osvi.dwPlatformId)
		{
		case VER_PLATFORM_WIN32_NT:
		{
			if (osvi.dwMajorVersion <= 4)
			{
				return NT4;
			}

			if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
			{
				return NT5;
			}

			if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 && osvi.wServicePackMajor == 1)
			{
				return NT5_0_1;
			}

			if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
			{
				return XP;
			}

			if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
			{
				return NET2003;
			}

			if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)
			{
				return VISTA;
			}

			if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1)
			{
				return WIN7;
			}
			if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 2)
			{
				// bug 48801-Correct Windows version is not being sent to the transmission logs
				DWORD dwMajorVersion = 0, dwMinorVersion = 0, dwBuildNumber = 0;
				if (GetNtVersionNumbers(dwMajorVersion, dwMinorVersion, dwBuildNumber))
				{
					if (dwMajorVersion == 10 && dwMinorVersion >= 0)
					{
						if (dwBuildNumber >= 22000)
							return WIN11;

						return WIN10;
					}
					else
						return WIN8; // bug 49001-REGRESSION: OST will not open in Windows 8
				}
				else
					return WIN8;
			}
			if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 3)
			{
				return WIN8_1;
			}
			assert(FALSE);
			break;
		}

		case VER_PLATFORM_WIN32_WINDOWS:
		{
			if ((osvi.dwMajorVersion > 4) || ((osvi.dwMajorVersion == 4) && (osvi.dwMinorVersion > 0)))
			{
				if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
				{
					return WME;
				}
				else
				{
					return W98;
				}
			}
			else
			{
				return W95;
			}
		}
		case VER_PLATFORM_WIN32s:
		{
			return W32S;
		}
		case VER_PLATFORM_WIN32_CE:
		{
			return W_CE;
		}
		}
	}
	catch (...)
	{
		assert(FALSE);
	}
	return W_NOTDEF;
}


int main() {

	std::string version = szPLATFORMSTRING[GetPlatformVersion()];

	std::cout << "Windows Version: " << version << endl;


	return 0;
}