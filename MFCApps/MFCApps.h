
// MFCApps.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCAppsApp:
// See MFCApps.cpp for the implementation of this class
//

class CMFCAppsApp : public CWinApp
{
public:
	CMFCAppsApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCAppsApp theApp;
