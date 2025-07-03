
// ShapesDoc.cpp : implementation of the CShapesDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Shapes.h"
#endif

#include "ShapesDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CShapesDoc

IMPLEMENT_DYNCREATE(CShapesDoc, CDocument)

BEGIN_MESSAGE_MAP(CShapesDoc, CDocument)
END_MESSAGE_MAP()


// CShapesDoc construction/destruction

CShapesDoc::CShapesDoc() noexcept
{
	for (int i = 0; i < m_shapeArray.GetSize(); i++)
	{
		delete m_shapeArray[i];
	}
	m_shapeArray.RemoveAll();
}

CShapesDoc::~CShapesDoc()
{
}

BOOL CShapesDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	for (int i = 0; i < m_shapeArray.GetSize(); i++)
	{
		delete m_shapeArray[i];
	}
	m_shapeArray.RemoveAll();

	return TRUE;
}




// CShapesDoc serialization

void CShapesDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		int count = m_shapeArray.GetSize();
		ar << count;

		for (int i = 0; i < count; i++)
		{
			m_shapeArray[i]->Serialize(ar);
		}
	}
	else
	{
		int count;
		ar >> count;

		m_shapeArray.RemoveAll();

		for (int i = 0; i < count; i++)
		{
			CShape* pShape = new CShape();
			pShape->Serialize(ar);
			m_shapeArray.Add(pShape);
		}
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CShapesDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CShapesDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CShapesDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CShapesDoc diagnostics

#ifdef _DEBUG
void CShapesDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CShapesDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CShapesDoc commands
