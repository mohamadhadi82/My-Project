#pragma once
#include "afxdialogex.h"


// CShapeDlg dialog

class CShapeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CShapeDlg)

public:
	CShapeDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CShapeDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHAPE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_lineStyle;
	int m_rValue;
	int m_gValue;
	int m_bValue;
	int m_lineWidth;
	int m_shapeType;
	int m_startX;
	int m_startY;
	int m_endX;
	int m_endY;
	COLORREF m_lineColor;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonColor();
	CSliderCtrl m_sliderWidth;
	afx_msg void OnNMCustomdrawSliderWidth(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeWidthEdit();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	CStatic m_colorBox;
};
