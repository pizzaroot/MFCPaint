#pragma once
#include "CMyShape.h"
class CMyStar :
    public CMyShape
{
	CPoint center, pts[10];
	int radius;
	virtual void draw(CDC& pDC);
	virtual void mouseDown(CPoint& pt);
	virtual void mouseUp(CPoint& pt);
	virtual bool isInside(CPoint& pt);

	virtual void moveVector(CPoint& before, CPoint& after);
};

