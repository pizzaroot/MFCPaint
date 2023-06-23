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
	topLeft = pt; bottomRight = pt;
	start = pt; end = pt;
}

void CMyRect::mouseUp(CPoint& pt)
{
	end = pt;
	topLeft.x = min(start.x, end.x);
	topLeft.y = min(start.y, end.y);
	bottomRight.x = max(start.x, end.x);
	bottomRight.y = max(start.y, end.y);
}

bool CMyRect::isInside(CPoint& pt)
{
	return topLeft.x <= pt.x && topLeft.y <= pt.y
		&& bottomRight.x >= pt.x && bottomRight.y >= pt.y;
}

void CMyRect::moveVector(CPoint& before, CPoint& after)
{
	start.x += after.x - before.x;
	start.y += after.y - before.y;
	end.x += after.x - before.x;
	end.y += after.y - before.y;
	moveFrame(before, after);
}
