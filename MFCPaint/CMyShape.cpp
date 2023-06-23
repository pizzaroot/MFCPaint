#include "pch.h"
#include "CMyShape.h"

CMyShape::CMyShape()
{
	isSelected = false;
	lineWidth = 3;
	color = RGB(rand() % 206, rand() % 206, rand() % 206);
}

double CMyShape::distance(CPoint& p1, CPoint& p2)
{
	return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
