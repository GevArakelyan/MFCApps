
// FolderPickerView.h : interface of the CFolderPickerView class
//

#pragma once
#include "FolderPickerCtrl.h"


class CFolderPickerView : public CFormView
{
protected: // create from serialization only
	CFolderPickerView();
	DECLARE_DYNCREATE(CFolderPickerView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_FOLDERPICKER_FORM };
#endif

// Attributes
public:
	CFolderPickerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CFolderPickerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();

public:
	FolderPickerCtrl m_folderPicker;
	CString m_folder3;
	CString m_folder2;
	CString m_folder1;
	afx_msg void OnBnClickedPrintbutton();
};

#ifndef _DEBUG  // debug version in FolderPickerView.cpp
inline CFolderPickerDoc* CFolderPickerView::GetDocument() const
   { return reinterpret_cast<CFolderPickerDoc*>(m_pDocument); }
#endif

