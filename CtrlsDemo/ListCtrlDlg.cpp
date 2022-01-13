// ListCtrlDlg.cpp : implementation file
//

#include "pch.h"
#include "CtrlsDemo.h"
#include "afxdialogex.h"
#include "ListCtrlDlg.h"
#include <list>


struct Student
{
	CString Id;
	CString Name;
};



// ListCtrlDlg dialog

IMPLEMENT_DYNAMIC(ListCtrlDlg, CDialogEx)

ListCtrlDlg::ListCtrlDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ListCtrlDlg, pParent)
{

}

ListCtrlDlg::~ListCtrlDlg()
{
}

void ListCtrlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, st);
}


BEGIN_MESSAGE_MAP(ListCtrlDlg, CDialogEx)
	ON_BN_CLICKED(IDC_EditBtn, &ListCtrlDlg::OnBnClickedEditbtn)
	ON_BN_CLICKED(IDC_DeleteBtn, &ListCtrlDlg::OnBnClickedDeletebtn)
	ON_BN_CLICKED(IDC_AddBtn, &ListCtrlDlg::OnBnClickedAddbtn)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &ListCtrlDlg::OnNMDblclkList1)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &ListCtrlDlg::OnHdnItemclickList1)
END_MESSAGE_MAP()

std::list<Student> Students;

// ListCtrlDlg message handlers
BOOL ListCtrlDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	st.InsertColumn(0, L"Name", LVCFMT_LEFT, 200);
	st.InsertColumn(1, L"Id", LVCFMT_LEFT, 200);
	//StudentsListCtrl.accDoDefaultAction()

	for (size_t i = 0; i < 10; i++)
	{
		CString id, sName;
		sName.Format(L"Student %d", i + 1);
		id.Format(L"%d", i + 1);
		Students.push_back(Student{ .Id = id, .Name = sName });
	}

	FillListControl();

	SortColumn = 0;
	bSortAsc = TRUE;

	return TRUE;
}

void ListCtrlDlg::FillListControl()
{
	st.DeleteAllItems();
	for (Student& s : Students) {
		int Item = st.InsertItem(st.GetItemCount(), s.Name, -1);
		st.SetItemText(Item, 1, s.Id);
		st.SetItemData(Item, (DWORD_PTR)&s);
	}
	st.SortItems(CompareFunc,(DWORD_PTR)this);
}

void ListCtrlDlg::OnBnClickedEditbtn()
{

}

void ListCtrlDlg::OnBnClickedDeletebtn()
{
	POSITION pos = st.GetFirstSelectedItemPosition();
	if (pos == NULL) {
		MessageBox(L"Select element to delete",
			L"Delete", MB_OK | MB_ICONINFORMATION);
		return;
	}
	int nIndex = st.GetNextSelectedItem(pos);
	Student* s = reinterpret_cast<Student*>(st.GetItemData(nIndex));
	if (IDYES != MessageBox(L"Remove element",
		L"Remove", MB_YESNO | MB_ICONQUESTION))
	{
		return;
	}
	std::erase_if(Students, [s](const Student& a) {
		return a.Id == s->Id;
		});
	FillListControl();
}

void ListCtrlDlg::OnBnClickedAddbtn()
{

}

void ListCtrlDlg::OnNMDblclkList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	if (st.GetSelectedCount() == 0)
	{
		OnBnClickedAddbtn();
	}
	else {
		OnBnClickedEditbtn();
	}
	*pResult = 0;
}

void ListCtrlDlg::OnHdnItemclickList1(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);

	if (SortColumn != phdr->iItem)
	{
		bSortAsc = TRUE;
	}
	else
	{
		if (bSortAsc)
			bSortAsc = FALSE;
		else bSortAsc = TRUE;
	}
	SortColumn = phdr->iItem;
	st.SortItems(CompareFunc,(DWORD_PTR)this);

	*pResult = 0;
}

int ListCtrlDlg::CompareFunc(LPARAM lparam1, LPARAM lparam2, LPARAM lparamSort)
{
	Student* a = (Student*)lparam1;
	Student* b = (Student*)lparam2;

	ListCtrlDlg* pthis= (ListCtrlDlg*)lparamSort;

	int result = 0;
	switch (pthis->SortColumn)
	{
	case 0:
		result = a->Name.Compare(b->Name);
		break;
	case 1:
		result= a->Id.Compare(b->Id);
		break;
	}
	if (pthis->bSortAsc == FALSE)
	{
		result *= -1;
	}
	return result;
}