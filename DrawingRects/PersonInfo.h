#pragma once
#include <afxstr.h>
#include <atltypes.h>


struct PersonInfo
{
    CString details;
    CPoint point;
    CRect rect;
};

#define WM_SHOWINFO (WM_USER + 100)