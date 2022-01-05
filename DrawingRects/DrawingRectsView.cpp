
// DrawingRectsView.cpp : implementation of the CDrawingRectsView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DrawingRects.h"
#endif

#include "DrawingRectsDoc.h"
#include "DrawingRectsView.h"
#include "PersonInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include <optional>


// CDrawingRectsView

IMPLEMENT_DYNCREATE(CDrawingRectsView, CView)

BEGIN_MESSAGE_MAP(CDrawingRectsView, CView)
    ON_WM_CONTEXTMENU()
    ON_WM_RBUTTONUP()
    ON_WM_CREATE()
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CDrawingRectsView construction/destruction

void CDrawingRectsView::CreateRectangles()
{
    const CPoint topleft{ 50,10 };
    const int vertSpace{ 5 };
    const CSize sz(100, 50);
    for (size_t i = 0; i < 5; i++)
    {
        CRect rect;
        rect.left = topleft.x;
        rect.top = topleft.y + sz.cy * i + vertSpace;
        rect.right = rect.left + sz.cx;
        rect.bottom = rect.top + sz.cy;
        m_rectangles.push_back(std::move(rect));
    }
}

void CDrawingRectsView::DrawRectangles(CDC* pDC)
{
    // TODO: add draw code for native data here
    CPen bluePen;
    bluePen.CreatePen(PS_SOLID, 3, RGB(0, 0, 200));
    CPen* pOldPen = pDC->SelectObject(&bluePen);

    for (size_t i = 0; i < 5; i++)
    {
        pDC->Rectangle(&m_rectangles[i]);
    }
    pDC->SelectObject(pOldPen);
}

CDrawingRectsView::CDrawingRectsView() noexcept
{
    // TODO: add construction code here

}

CDrawingRectsView::~CDrawingRectsView()
{
}

BOOL CDrawingRectsView::PreCreateWindow(CREATESTRUCT& cs)
{
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    return CView::PreCreateWindow(cs);
}

// CDrawingRectsView drawing

void CDrawingRectsView::OnDraw(CDC* pDC)
{
    CDrawingRectsDoc* pDoc = GetDocument();
    ASSERT_VALID(pDoc);
    if (!pDoc)
        return;

    // TODO: add draw code for native data here
    DrawRectangles(pDC);
}

void CDrawingRectsView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
    ClientToScreen(&point);
    OnContextMenu(this, point);
}

void CDrawingRectsView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
    theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDrawingRectsView diagnostics

#ifdef _DEBUG
void CDrawingRectsView::AssertValid() const
{
    CView::AssertValid();
}

void CDrawingRectsView::Dump(CDumpContext& dc) const
{
    CView::Dump(dc);
}

CDrawingRectsDoc* CDrawingRectsView::GetDocument() const // non-debug version is inline
{
    ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDrawingRectsDoc)));
    return (CDrawingRectsDoc*)m_pDocument;
}
#endif //_DEBUG


// CDrawingRectsView message handlers


int CDrawingRectsView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CView::OnCreate(lpCreateStruct) == -1)
        return -1;

    // TODO:  Add your specialized creation code here
    m_button.Create(_T("Hi"), BS_PUSHBUTTON,
        CRect(300, 100, 380, 150), this, 101);

    CreateRectangles();
    return 0;
}


void CDrawingRectsView::OnLButtonDown(UINT nFlags, CPoint point)
{
    std::optional<size_t> hitIndex;
    for (size_t i = 0; i < m_rectangles.size(); i++)
    {
        if (m_rectangles[i].PtInRect(point)) {
            hitIndex = i;
            break;
        }
    }
    if (hitIndex)
    {
        CRect hitrect = m_rectangles[hitIndex.value()];
        CRect rect;
        rect.left = hitrect.right + 10;
        rect.top = hitrect.top;
        rect.right = rect.left + 80;
        rect.bottom = hitrect.top + 40;


        PersonInfo* info = new PersonInfo{ .details = _T("Hi"), .point = point, .rect = rect};

        m_button.SendMessageW(WM_SHOWINFO, 0, reinterpret_cast<LPARAM>(&info));
        // or just use this m_button.Show(point, rect);
    }
    else
    {
        m_button.Hide();
    }

    CView::OnLButtonDown(nFlags, point);
}
