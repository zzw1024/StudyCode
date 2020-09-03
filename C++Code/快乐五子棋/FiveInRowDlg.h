﻿
// FiveInRowDlg.h: 头文件
//

#pragma once


// CFiveInRowDlg 对话框
class CFiveInRowDlg : public CDialogEx
{
// 构造
public:
	CFiveInRowDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FIVEINROW_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:


	afx_msg void OnEnChangeEdit1();
//	afx_msg void OnBnClickedButton1();
	CStatic m_label;
//	afx_msg void OnStnClickedStaticLabel();
//	afx_msg void OnBnDoubleclickedButton1();
	CEdit m_Edit;
private:
	CString m_editDouble;
public:
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	CComboBox m_Combox;
//	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CTabCtrl m_TabSheet;
};
