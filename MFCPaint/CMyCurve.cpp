#include "pch.h"
#include "CMyCurve.h"

void CMyCurve::draw(CDC& pDC)
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

	for (int i = 1; i < pts.size(); i++) {
		pDC.MoveTo(pts[i - 1]);
		pDC.LineTo(pts[i]);
	}
}

void CMyCurve::mouseDown(CPoint& pt)
{
	topLeft = pt; bottomRight = pt;
	pts.push_back(pt);
}

void CMyCurve::mouseUp(CPoint& pt)
{
	topLeft.x = min(topLeft.x, pt.x);
	topLeft.y = min(topLeft.y, pt.y);
	bottomRight.x = max(bottomRight.x, pt.x);
	bottomRight.y = max(bottomRight.y, pt.y);
	pts.push_back(pt);
}

bool CMyCurve::isInside(CPoint& pt)
{
	for (int i = 1; i < pts.size(); i++) {
		int newx = pts[i].y - pts[i - 1].y, newy = pts[i - 1].x - pts[i].x;
		double div = sqrt(newx * newx + newy * newy);
		if (div <= 1) {
			if (distance(pts[i], pt) <= 8 || distance(pts[i - 1], pt) <= 8) return true;
		}
		else {
			newx = newx * 8 / div; newy = newy * 8 / div;
			CPoint closeStart(pt.x + newx, pt.y + newy);
			CPoint closeEnd(pt.x - newx, pt.y - newy);
			if (intersect(pts[i - 1], pts[i], closeStart, closeEnd)) {
				return true;
			}
		}
	}
	return false;
}

void CMyCurve::moveVector(CPoint& before, CPoint& after)
{
	for (auto& p : pts) {
		p.x += after.x - before.x;
		p.y += after.y - before.y;
	}
	moveFrame(before, after);
}
