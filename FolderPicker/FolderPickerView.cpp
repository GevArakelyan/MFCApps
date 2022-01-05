
// FolderPickerView.cpp : implementation of the CFolderPickerView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "FolderPicker.h"
#endif

#include "FolderPickerDoc.h"
#include "FolderPickerView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFolderPickerView

IMPLEMENT_DYNCREATE(CFolderPickerView, CFormView)

BEGIN_MESSAGE_MAP(CFolderPickerView, CFormView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFolderPickerView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_BN_CLICKED(IDC_FOLDER3, &CFolderPickerView::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_PRINTBUTTON, &CFolderPickerView::OnBnClickedPrintbutton)
END_MESSAGE_MAP()

// CFolderPickerView construction/destruction

CFolderPickerView::CFolderPickerView()
	: CFormView(IDD_FOLDERPICKER_FORM)
	, m_folder3(_T(""))
	, m_folder2(_T(""))
	, m_folder1(_T(""))
{
	// TODO: add construction code here

}

CFolderPickerView::~CFolderPickerView()
{
}

void CFolderPickerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Folder2, m_folderPicker);
	DDX_Text(pDX, IDC_FOLDER3_EDIT, m_folder3);
	DDX_Text(pDX, IDC_Folder2, m_folder2);
	DDX_Text(pDX, IDC_FOLDER1, m_folder1);
}

BOOL CFolderPickerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CFolderPickerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CFolderPickerView printing


void CFolderPickerView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFolderPickerView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFolderPickerView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFolderPickerView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFolderPickerView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

void CFolderPickerView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFolderPickerView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFolderPickerView diagnostics

#ifdef _DEBUG
void CFolderPickerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFolderPickerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CFolderPickerDoc* CFolderPickerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFolderPickerDoc)));
	return (CFolderPickerDoc*)m_pDocument;
}
#endif //_DEBUG


// CFolderPickerView message handlers


void CFolderPickerView::OnBnClickedButton1()
{
	UpdateData();
	CFolderPickerDialog folder;
	if (folder.DoModal() == IDOK)
	{
		m_folder3 = folder.GetPathName();
	}
	UpdateData(FALSE);
}


void CFolderPickerView::OnBnClickedPrintbutton()
{
	UpdateData();
	CString Folders = (m_folder1 + _T("\n") + m_folder2 + _T("\n") + m_folder3);
	AfxMessageBox(Folders);
}
