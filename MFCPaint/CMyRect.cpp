#include "pch.h"
#include "CMyRect.h"

void CMyRect::draw(CDC& pDC)
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

	pDC.Rectangle(start.x, start.y, end.x, end.y);

}

void CMyRect::mouseDown(CPoint& pt)
{
	start = pt; end = pt;
}

void CMyRect::mouseUp(CPoint& pt)
{
	end = pt;
}
