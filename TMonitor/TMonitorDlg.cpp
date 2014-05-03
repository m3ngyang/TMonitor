
// TMonitorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TMonitor.h"
#include "TMonitorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTMonitorDlg 对话框




CTMonitorDlg::CTMonitorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTMonitorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	TArray.RemoveAll();
	memset(m_temp,0,sizeof(int)*POINT_COUNT);
}

void CTMonitorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_WAVE_WIN, m_waveWin);
}

BEGIN_MESSAGE_MAP(CTMonitorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CTMonitorDlg 消息处理程序

BOOL CTMonitorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//my codes
	// TODO: 在此添加额外的初始化代码

	srand((unsigned)time(NULL));
	SetTimer(1,1000,NULL);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTMonitorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTMonitorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	CRect rect;
	m_waveWin.GetClientRect(&rect);
	DrawGrids(m_waveWin.GetDC(),rect);
	UpdateData(FALSE);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTMonitorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTMonitorDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int curT = rand()%100;
	TArray.Add(curT);
	for(int i=0;i<POINT_COUNT-1;i++)
	{
		m_temp[i] = m_temp[i+1];
	}
	m_temp[POINT_COUNT-1] = curT;

	CRect rect;
	m_waveWin.GetClientRect(&rect);
	DrawGrids(m_waveWin.GetDC(),rect);
	DrawTWave(m_waveWin.GetDC(),rect);

	CDialogEx::OnTimer(nIDEvent);
}


void CTMonitorDlg::DrawGrids(CDC* pDC, CRect& rect)
{
	//draw grid line
	float width = rect.Width();
	float height = rect.Height();
	float delH = height/10;
	CPen newPen;
	CPen *pOldPen;
	CBrush newBrush;
	CBrush *pOldBrush;

	newBrush.CreateSolidBrush(RGB(0,0,0));
	pOldBrush = pDC->SelectObject(&newBrush);
	pDC->Rectangle(rect);
	pDC->SelectObject(pOldBrush);
	newBrush.DeleteObject();

	newPen.CreatePen(PS_SOLID,1,RGB(255,255,255));
	pOldPen = pDC->SelectObject(&newPen);

	
	for(int i=0;i<=10;i++)
	{
		CString strT;
		strT.Format(_T("%d"),i*10);
		pDC->MoveTo(0,height-i*delH);
		pDC->LineTo(width,height-i*delH);
		pDC->TextOut(0-25,height-i*delH-10,strT);
	}
	pDC->SelectObject(pOldPen);
	newPen.DeleteObject();
}


// draw the wave line of temperature
void CTMonitorDlg::DrawTWave(CDC* pDC, CRect& rect)
{
	float width = rect.Width();
	float height = rect.Height();
	float delX = width/(POINT_COUNT-1);
	float delY = height/100;
	float nX;
	float nY;
	CPen newPen;
	CPen *pOldPen;

	newPen.CreatePen(PS_SOLID,1,RGB(0,255,0));
	pOldPen = pDC->SelectObject(&newPen);
	pDC->MoveTo(rect.left,rect.bottom);
	for(int i=0;i<POINT_COUNT;i++)
	{
		nX = rect.left + (int)i*delX;
		nY = rect.bottom - (int)m_temp[i]*delY;
		pDC->LineTo(nX,nY);
	}
	pDC->SelectObject(pOldPen);
	newPen.DeleteObject();
}
