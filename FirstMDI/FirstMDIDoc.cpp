
// FirstMDIDoc.cpp : implementation of the CFirstMDIDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "FirstMDI.h"
#endif

#include "FirstMDIDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CFirstMDIDoc

IMPLEMENT_DYNCREATE(CFirstMDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CFirstMDIDoc, CDocument)
	ON_COMMAND(ID_FILE_SEND_MAIL, &CFirstMDIDoc::OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, &CFirstMDIDoc::OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFirstMDIDoc, CDocument)
END_DISPATCH_MAP()

// Note: we add support for IID_IFirstMDI to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the
//  dispinterface in the .IDL file.

// {5467b77a-6cf6-494e-8ce7-1806f39a5acf}
static const IID IID_IFirstMDI =
{0x5467b77a,0x6cf6,0x494e,{0x8c,0xe7,0x18,0x06,0xf3,0x9a,0x5a,0xcf}};

BEGIN_INTERFACE_MAP(CFirstMDIDoc, CDocument)
	INTERFACE_PART(CFirstMDIDoc, IID_IFirstMDI, Dispatch)
END_INTERFACE_MAP()


// CFirstMDIDoc construction/destruction

CFirstMDIDoc::CFirstMDIDoc() noexcept
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CFirstMDIDoc::~CFirstMDIDoc()
{
	AfxOleUnlockApp();
}

BOOL CFirstMDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CFirstMDIDoc serialization

void CFirstMDIDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CFirstMDIDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CFirstMDIDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CFirstMDIDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CFirstMDIDoc diagnostics

#ifdef _DEBUG
void CFirstMDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CFirstMDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CFirstMDIDoc commands
