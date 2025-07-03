#include "pch.h"
#include "CShape.h"

IMPLEMENT_SERIAL(CShape, CObject, 1)

CShape::CShape()
{
    shapeType = 0;
    startX = startY = endX = endY = 0;
    lineStyle = 0;
    lineWidth = 1;
    lineColor = RGB(0, 0, 0);
}

CShape::CShape(int type, int sx, int sy, int ex, int ey, int style, int width, COLORREF color)
{
    shapeType = type;
    startX = sx;
    startY = sy;
    endX = ex;
    endY = ey;
    lineStyle = style;
    lineWidth = width;
    lineColor = color;
}

void CShape::Serialize(CArchive& ar)
{
    if (ar.IsStoring())
    {
        ar << shapeType << startX << startY << endX << endY
            << lineStyle << lineWidth << lineColor;
    }
    else
    {
        ar >> shapeType >> startX >> startY >> endX >> endY
            >> lineStyle >> lineWidth >> lineColor;
    }
}