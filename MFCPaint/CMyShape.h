#pragma once
class CMyShape
{
public:
	bool isSelected;
	COLORREF color;
	CPoint topLeft, bottomRight;
	CMyShape();
	virtual void draw(CDC& pDC) = 0;
	virtual void mouseDown(CPoint& pt) = 0;
	virtual void mouseUp(CPoint& pt) = 0;
};

