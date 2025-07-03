#pragma once
#include <afx.h>
class CShape :
    public CObject
{
public:
    DECLARE_SERIAL(CShape)

    int shapeType;   // 1 = Rectangle, 0 = Ellipse
    int startX;
    int startY;
    int endX;
    int endY;
    int lineStyle;
    int lineWidth;
    COLORREF lineColor;

    CShape();
    CShape(int type, int sx, int sy, int ex, int ey, int style, int width, COLORREF color);

    virtual void Serialize(CArchive& ar);
};

