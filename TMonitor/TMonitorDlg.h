
// TMonitorDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CTMonitorDlg 对话框
class CTMonitorDlg : public CDialogEx
{
// 构造
public:
	CTMonitorDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_TMONITOR_DIALOG };

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
	// window of t-wave
	CStatic m_waveWin;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawGrids(CDC* pDC, CRect& rect);
};
