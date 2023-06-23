#pragma once
class CMyShape
{
public:
	bool isSelected;
	int lineWidth;
	COLORREF color;
	CPoint topLeft, bottomRight;
	CMyShape();
	double distance(CPoint& p1, CPoint& p2);
	virtual void draw(CDC& pDC) = 0;
	virtual void mouseDown(CPoint& pt) = 0;
	virtual void mouseUp(CPoint& pt) = 0;
};

