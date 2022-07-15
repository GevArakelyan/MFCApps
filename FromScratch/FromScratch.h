
// FromScratch.h : main header file for the FromScratch application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CFromScratchApp:
// See FromScratch.cpp for the implementation of this class
//

class CFromScratchApp : public CWinApp
{
public:
	CFromScratchApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CFromScratchApp theApp;
