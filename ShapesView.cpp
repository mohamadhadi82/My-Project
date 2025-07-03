
// ShapesView.cpp : implementation of the CShapesView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Shapes.h"
#endif

#include "ShapesDoc.h"
#include "ShapesView.h"
#include "CShapeDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CShapesView

IMPLEMENT_DYNCREATE(CShapesView, CView)

BEGIN_MESSAGE_MAP(CShapesView, CView)
	ON_COMMAND(ID_DRAW_SHAPE, &CShapesView::OnDrawShape)
END_MESSAGE_MAP()

// CShapesView construction/destruction

CShapesView::CShapesView() noexcept
{
	// TODO: add construction code here

}

CShapesView::~CShapesView()
{
}

BOOL CShapesView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CShapesView drawing

void CShapesView::OnDraw(CDC* pDC)
{
	CShapesDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

    for (int i = 0; i < pDoc->m_shapeArray.GetSize(); i++)
    {
        CShape* s = pDoc->m_shapeArray[i];

        int penStyle = s->lineStyle == 0 ? PS_SOLID :
            s->lineStyle == 1 ? PS_DASHDOT :
            s->lineStyle == 2 ? PS_DASHDOTDOT :
            s->lineStyle == 3 ? PS_DASH : PS_DOT;

        CPen pen(penStyle, s->lineWidth, s->lineColor);
        CPen* pOldPen = pDC->SelectObject(&pen);

        CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

        CRect rect(s->startX, s->startY, s->endX, s->endY);
        rect.NormalizeRect();

        if (s->shapeType == 0)
            pDC->Rectangle(rect);
        else
            pDC->Ellipse(rect);

        pDC->SelectObject(pOldBrush);
        pDC->SelectObject(pOldPen);
    }

	// TODO: add draw code for native data here
}


// CShapesView diagnostics

#ifdef _DEBUG
void CShapesView::AssertValid() const
{
	CView::AssertValid();
}

void CShapesView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CShapesDoc* CShapesView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CShapesDoc)));
	return (CShapesDoc*)m_pDocument;
}
#endif //_DEBUG


// CShapesView message handlers

void CShapesView::OnDrawShape()
{
    CShapeDlg dlg;
    if (dlg.DoModal() == IDOK)
    {
        CClientDC dc(this);

        int penStyle;
        switch (dlg.m_lineStyle)
        {
        case 0: penStyle = PS_SOLID; break;
        case 1: penStyle = PS_DASHDOT; break;
        case 2: penStyle = PS_DASHDOTDOT; break;
        case 3: penStyle = PS_DASH; break;
        case 4: penStyle = PS_DOT; break;
        default: penStyle = PS_SOLID; break;
        }

        CPen pen(penStyle, dlg.m_lineWidth, dlg.m_lineColor);
        CPen* pOldPen = dc.SelectObject(&pen);

        CBrush* pOldBrush = (CBrush*)dc.SelectStockObject(NULL_BRUSH);

        CRect rect(dlg.m_startX, dlg.m_startY, dlg.m_endX, dlg.m_endY);
        rect.NormalizeRect();

        if (dlg.m_shapeType == 0)
            dc.Rectangle(rect);
        else if (dlg.m_shapeType == 1) 
            dc.Ellipse(rect);

        dc.SelectObject(pOldBrush);
        dc.SelectObject(pOldPen);

        CShapesDoc* pDoc = GetDocument();

        CShape* pShape = new CShape(
            dlg.m_shapeType,
            dlg.m_startX,
            dlg.m_startY,
            dlg.m_endX,
            dlg.m_endY,
            dlg.m_lineStyle,
            dlg.m_lineWidth,
            dlg.m_lineColor
        );

        pDoc->m_shapeArray.Add(pShape);
        pDoc->SetModifiedFlag(TRUE);

        Invalidate();

    }
}
