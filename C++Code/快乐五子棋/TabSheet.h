#pragma once


// CTabSheet 对话框

class CTabSheet : public CDialogEx
{
	DECLARE_DYNAMIC(CTabSheet)

public:
	CTabSheet(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTabSheet();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIVEINROW_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
