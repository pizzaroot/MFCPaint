#pragma once
#include "CMyShape.h"
#include <vector>
class CMyCurve :
    public CMyShape
{
    std::vector<CPoint> pts;
	virtual void draw(CDC& pDC);
	virtual void mouseDown(CPoint& pt);
	virtual void mouseUp(CPoint& pt);
	virtual bool isInside(CPoint& pt);
};

