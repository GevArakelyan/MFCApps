// FolderPickerCtrl.cpp : implementation file
//

#include "pch.h"
#include "FolderPicker.h"
#include "FolderPickerCtrl.h"


// FolderPickerCtrl

IMPLEMENT_DYNAMIC(FolderPickerCtrl, CMFCEditBrowseCtrl)

FolderPickerCtrl::FolderPickerCtrl()
{

}

FolderPickerCtrl::~FolderPickerCtrl()
{
}

void FolderPickerCtrl::OnBrowse()
{
    CFolderPickerDialog folder;
    folder.m_ofn.lpstrInitialDir = _T("C:\\");
    if (folder.DoModal() == IDOK)
    {
        this->SetWindowTextW(folder.GetPathName());
    }
}


BEGIN_MESSAGE_MAP(FolderPickerCtrl, CMFCEditBrowseCtrl)
END_MESSAGE_MAP()



// FolderPickerCtrl message handlers


