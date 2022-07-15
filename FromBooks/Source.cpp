#include <afxwin.h>
#include "resource.h"

class CResFrame : public CFrameWnd
{
public:
	CResFrame()
	{
		HCURSOR hCursor;
		HICON hIcon;
		hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR1);
		hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
		const char* RWC = AfxRegisterWndClass(CS_VREDRAW | CS_HREDRAW, hCursor, (HBRUSH)GetStockObject(BLACK_BRUSH), hIcon);
		Create(RWC, "Custom Resources", WS_OVERLAPPEDWINDOW, CRect(200, 120, 640, 400), NULL);
	}
};
class CResApp : public CWinApp
{
public:
	BOOL InitInstance()
	{
		CWinApp::InitInstance();

		
		m_pMainWnd = new CResFrame;
		m_pMainWnd->ShowWindow(SW_SHOW);
		m_pMainWnd->UpdateWindow();
		return TRUE;
	}
};

CResApp app;