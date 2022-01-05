
// FirstMDIView.cpp : implementation of the CFirstMDIView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "FirstMDI.h"
#endif

#include "FirstMDIDoc.h"
#include "FirstMDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFirstMDIView

IMPLEMENT_DYNCREATE(CFirstMDIView, CView)

BEGIN_MESSAGE_MAP(CFirstMDIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFirstMDIView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CFirstMDIView construction/destruction

CFirstMDIView::CFirstMDIView() noexcept
{
	EnableActiveAccessibility();
	// TODO: add construction code here

}

CFirstMDIView::~CFirstMDIView()
{
}

BOOL CFirstMDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CFirstMDIView drawing

void CFirstMDIView::OnDraw(CDC* /*pDC*/)
{
	CFirstMDIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CFirstMDIView printing


void CFirstMDIView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFirstMDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFirstMDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFirstMDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFirstMDIView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFirstMDIView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFirstMDIView diagnostics

#ifdef _DEBUG
void CFirstMDIView::AssertValid() const
{
	CView::AssertValid();
}

void CFirstMDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFirstMDIDoc* CFirstMDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFirstMDIDoc)));
	return (CFirstMDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CFirstMDIView message handlers
