#pragma once
#include "afxdialogex.h"


// ListCtrlDlg dialog

class ListCtrlDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ListCtrlDlg)

public:
	ListCtrlDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~ListCtrlDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ListCtrlDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	static int CALLBACK	CompareFunc(LPARAM lparam1,
		LPARAM lparam2,LPARAM lparamSort);
	int SortColumn;
	BOOL bSortAsc;
	CListCtrl st;
	afx_msg void OnBnClickedEditbtn();
	afx_msg void OnBnClickedDeletebtn();
	afx_msg void OnBnClickedAddbtn();

	virtual BOOL OnInitDialog();
	void FillListControl();
	afx_msg void OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnHdnItemclickList1(NMHDR* pNMHDR, LRESULT* pResult);
};
