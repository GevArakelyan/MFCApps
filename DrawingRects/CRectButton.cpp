// CRectButton.cpp : implementation file
//

#include "pch.h"
#include "DrawingRects.h"
#include "CRectButton.h"
#include "PersonInfo.h"


// CRectButton

IMPLEMENT_DYNAMIC(CRectButton, CButton)

CRectButton::CRectButton()
{

}

CRectButton::~CRectButton()
{
}

void CRectButton::Show(CPoint point, CRect rect)
{
    CString text;
    text.Format(_T("%d , %d"), point.x, point.y);

    this->SetWindowTextW(text);

    // position
    this->MoveWindow(rect);


    this->ShowWindow(SW_SHOW);
}

void CRectButton::Hide()
{
    this->ShowWindow(SW_HIDE);
}

LRESULT CRectButton::OnMyMessage(WPARAM wParam, LPARAM lParam)
{
    PersonInfo* Info = reinterpret_cast<PersonInfo*>(lParam);
    Show(Info->point, Info->rect);

    return LRESULT();
}


BEGIN_MESSAGE_MAP(CRectButton, CButton)
    ON_MESSAGE(WM_SHOWINFO, OnMyMessage)
END_MESSAGE_MAP()



// CRectButton message handlers


