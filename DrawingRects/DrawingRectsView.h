
// DrawingRectsView.h : interface of the CDrawingRectsView class
//

#pragma once
#include <vector>
#include "CRectButton.h"


class CDrawingRectsView : public CView
{
private:
	CRectButton m_button;
	std::vector<CRect> m_rectangles;
	void CreateRectangles();

	void DrawRectangles(CDC* pDC);

protected: // create from serialization only
	CDrawingRectsView() noexcept;
	DECLARE_DYNCREATE(CDrawingRectsView)

// Attributes
public:
	CDrawingRectsDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CDrawingRectsView();
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
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in DrawingRectsView.cpp
inline CDrawingRectsDoc* CDrawingRectsView::GetDocument() const
   { return reinterpret_cast<CDrawingRectsDoc*>(m_pDocument); }
#endif

