// TabSheet.cpp: 实现文件
//

#include "stdafx.h"
#include "FiveInRow.h"
#include "TabSheet.h"
#include "afxdialogex.h"


// CTabSheet 对话框

IMPLEMENT_DYNAMIC(CTabSheet, CDialogEx)

CTabSheet::CTabSheet(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FIVEINROW_DIALOG, pParent)
{

}

CTabSheet::~CTabSheet()
{
}

void CTabSheet::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTabSheet, CDialogEx)
END_MESSAGE_MAP()


// CTabSheet 消息处理程序
