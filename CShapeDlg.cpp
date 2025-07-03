// CShapeDlg.cpp : implementation file
//

#include "pch.h"
#include "Shapes.h"
#include "afxdialogex.h"
#include "CShapeDlg.h"


// CShapeDlg dialog

IMPLEMENT_DYNAMIC(CShapeDlg, CDialogEx)

CShapeDlg::CShapeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SHAPE_DIALOG, pParent)
	, m_lineStyle(0)
	, m_rValue(0)
	, m_gValue(0)
	, m_bValue(0)
	, m_lineWidth(0)
	, m_shapeType(0)
	, m_startX(0)
	, m_startY(0)
	, m_endX(0)
	, m_endY(0)
{

}

CShapeDlg::~CShapeDlg()
{
}

void CShapeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_SOLID, m_lineStyle);
	DDX_Text(pDX, IDC_REDIT, m_rValue);
	DDX_Text(pDX, IDC_GEDIT, m_gValue);
	DDX_Text(pDX, IDC_BEDIT, m_bValue);
	DDX_Text(pDX, IDC_WIDTH_EDIT, m_lineWidth);
	DDV_MinMaxInt(pDX, m_lineWidth, 1, 10);
	DDX_CBIndex(pDX, IDC_COMBO_SHAPE, m_shapeType);
	DDX_Text(pDX, IDC_EDIT_STARTX, m_startX);
	DDX_Text(pDX, IDC_EDIT_STARTY, m_startY);
	DDX_Text(pDX, IDC_EDIT_ENDX, m_endX);
	DDX_Text(pDX, IDC_EDIT_ENDY, m_endY);

	DDV_MinMaxInt(pDX, m_startX, 0, 1920);
	DDV_MinMaxInt(pDX, m_startY, 0, 1080);
	DDV_MinMaxInt(pDX, m_endX, 0, 1920);
	DDV_MinMaxInt(pDX, m_endY, 0, 1080);

	DDX_Control(pDX, IDC_SLIDER_WIDTH, m_sliderWidth);
	DDX_Control(pDX, IDC_COLOR_BOX, m_colorBox);
}


BEGIN_MESSAGE_MAP(CShapeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_COLOR, &CShapeDlg::OnBnClickedButtonColor)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_WIDTH, &CShapeDlg::OnNMCustomdrawSliderWidth)
	ON_EN_CHANGE(IDC_WIDTH_EDIT, &CShapeDlg::OnEnChangeWidthEdit)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CShapeDlg message handlers

BOOL CShapeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	CComboBox* pShape = (CComboBox*)GetDlgItem(IDC_COMBO_SHAPE);
	pShape->SetCurSel(0);

	m_sliderWidth.SetRange(1, 10);
	m_sliderWidth.SetPos(1);

	m_lineWidth = 1;

	UpdateData(FALSE);

	m_lineColor = RGB(0, 0, 0);
	m_rValue = 0;
	m_gValue = 0;
	m_bValue = 0;

	GetDlgItem(IDC_COLOR_BOX)->ModifyStyle(0, SS_OWNERDRAW);


	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CShapeDlg::OnBnClickedButtonColor()
{
	UpdateData(TRUE);
	CColorDialog dlg(m_lineColor);
	if (dlg.DoModal() == IDOK)
	{
		m_lineColor = dlg.GetColor();

		m_rValue = GetRValue(m_lineColor);
		m_gValue = GetGValue(m_lineColor);
		m_bValue = GetBValue(m_lineColor);
		m_colorBox.Invalidate();

		UpdateData(FALSE);
	}
}

void CShapeDlg::OnNMCustomdrawSliderWidth(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData(TRUE);
	m_lineWidth = m_sliderWidth.GetPos();
	UpdateData(FALSE);

	*pResult = 0;
}

void CShapeDlg::OnEnChangeWidthEdit()
{
	UpdateData(TRUE);

	if (m_lineWidth < 1) m_lineWidth = 1;
	if (m_lineWidth > 10) m_lineWidth = 10;

	m_sliderWidth.SetPos(m_lineWidth);

	UpdateData(FALSE);
}

void CShapeDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if (nIDCtl == IDC_COLOR_BOX)
	{
		CDC dc;
		dc.Attach(lpDrawItemStruct->hDC);

		CBrush brush(m_lineColor);
		dc.FillRect(&lpDrawItemStruct->rcItem, &brush);

		dc.DrawEdge(&lpDrawItemStruct->rcItem, EDGE_SUNKEN, BF_RECT);

		dc.Detach();
	}

	//CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
