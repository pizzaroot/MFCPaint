#pragma once
#include "CMyShape.h"
class CMyCircle :
    public CMyShape
{
	CPoint center;
	int radius;
	virtual void draw(CDC& pDC);
	virtual void mouseDown(CPoint& pt);
	virtual void mouseUp(CPoint& pt);
};

