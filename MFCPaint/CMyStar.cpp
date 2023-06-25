#include "pch.h"
#include "CMyStar.h"
#define M_PI 3.14159265358979323846
#define INF 0x3f3f

void CMyStar::draw(CDC& pDC)
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

	for (int i = 0; i < 10; i += 2) {
		pts[i].x = center.x + radius * sin(M_PI * i / 5);
		pts[i].y = center.y - radius * cos(M_PI * i / 5);
	}

	for (int i = 1; i < 10; i += 2) {
		pts[i].x = center.x + radius * cos(2 * M_PI / 5) / cos(M_PI / 5) * sin(M_PI * i / 5);
		pts[i].y = center.y - radius * cos(2 * M_PI / 5) / cos(M_PI / 5) * cos(M_PI * i / 5);
	}

	pDC.Polygon(pts, 10);
}

void CMyStar::mouseDown(CPoint& pt)
{
	topLeft = pt; bottomRight = pt;
	center = pt, radius = 0;
}

void CMyStar::mouseUp(CPoint& pt)
{
	radius = sqrt((pt.x - center.x) * (pt.x - center.x) + (pt.y - center.y) * (pt.y - center.y));
	topLeft.x = center.x - radius * sin(M_PI * 2 / 5);
	topLeft.y = center.y - radius;
	bottomRight.x = center.x + radius * sin(M_PI * 2 / 5);
	bottomRight.y = center.y - radius * cos(M_PI * 4 / 5);
}

bool CMyStar::isInside(CPoint& pt)
{
	int intersectCnt = 0;
	CPoint farAway(pt.x + 1, -INF);
	for (int i = 1; i <= 10; i++) {
		intersectCnt += intersect(pts[i % 10], pts[i - 1], pt, farAway);
	}
	return intersectCnt % 2 == 1;
}

void CMyStar::moveVector(CPoint& before, CPoint& after)
{
	center.x += after.x - before.x;
	center.y += after.y - before.y;
	moveFrame(before, after);
}
