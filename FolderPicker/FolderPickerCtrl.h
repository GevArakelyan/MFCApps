#pragma once


// FolderPickerCtrl

class FolderPickerCtrl : public CMFCEditBrowseCtrl
{
	DECLARE_DYNAMIC(FolderPickerCtrl)

public:
	FolderPickerCtrl();
	virtual ~FolderPickerCtrl();
protected:
	virtual void OnBrowse() override;
protected:
	DECLARE_MESSAGE_MAP()
};


