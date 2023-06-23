#include "pch.h"
#include "CMyCircle.h"

void CMyCircle::draw(CDC& pDC)
{
	CPen pen(PS_SOLID, lineWidth, color);
	COLORREF nextColor = RGB(
		GetRValue(color) + 50,
		GetGValue(color) + 50,
		GetBValue(color) + 50
	);
	CBrush brush(nextColor);
	pDC.SelectObject(&pen);
	pDC.SelectObject(&brush);

	pDC.Ellipse(center.x - radius, center.y - radius, center.x + radius, center.y + radius);
}

void CMyCircle::mouseDown(CPoint& pt)
{
	center = pt;
}

void CMyCircle::mouseUp(CPoint& pt)
{
	radius = distance(center, pt);
}
