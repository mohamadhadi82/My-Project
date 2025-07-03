
// ShapesDoc.h : interface of the CShapesDoc class
//


#pragma once
#include "CShape.h"

class CShapesDoc : public CDocument
{
protected: // create from serialization only
	CShapesDoc() noexcept;
	DECLARE_DYNCREATE(CShapesDoc)

// Attributes
public:
	CArray<CShape*, CShape*> m_shapeArray;

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CShapesDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
