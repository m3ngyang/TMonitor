
// TMonitorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include <afxtempl.h>
#define POINT_COUNT 20

// CTMonitorDlg �Ի���
class CTMonitorDlg : public CDialogEx
{
// ����
public:
	CTMonitorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TMONITOR_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// window of t-wave
	CStatic m_waveWin;
	//temperature array
	CArray<int,int> TArray;
	int m_temp[POINT_COUNT];
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawGrids(CDC* pDC, CRect& rect);
	// draw the wave line of temperature
	void DrawTWave(CDC* pDC, CRect& rect);
	CString m_tmp;
	CString m_avg;
	CString m_num;
	CString m_max;
	CString m_min;
};
