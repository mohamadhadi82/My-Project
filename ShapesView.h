
// ShapesView.h : interface of the CShapesView class
//

#pragma once


class CShapesView : public CView
{
protected: // create from serialization only
	CShapesView() noexcept;
	DECLARE_DYNCREATE(CShapesView)

// Attributes
public:
	CShapesDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CShapesView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawShape();
};

#ifndef _DEBUG  // debug version in ShapesView.cpp
inline CShapesDoc* CShapesView::GetDocument() const
   { return reinterpret_cast<CShapesDoc*>(m_pDocument); }
#endif

