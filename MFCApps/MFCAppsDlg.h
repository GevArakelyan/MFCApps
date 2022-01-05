
// MFCAppsDlg.h : header file
//

#pragma once


// CMFCAppsDlg dialog
class CMFCAppsDlg : public CDialogEx
{
// Construction
public:
	CMFCAppsDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPS_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CProgressCtrl m_ProgressCtrl;
	CString m_FinishText;
	afx_msg void OnBnClickedOk2();
	afx_msg void OnBnClickedCancel2();
};
