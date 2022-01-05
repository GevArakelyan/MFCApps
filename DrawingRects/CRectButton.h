#pragma once


// CRectButton

class CRectButton : public CButton
{
	DECLARE_DYNAMIC(CRectButton)

public:
	CRectButton();
	virtual ~CRectButton();

	virtual void Show(CPoint point, CRect rect);
	virtual void Hide();
protected:
	afx_msg LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};


