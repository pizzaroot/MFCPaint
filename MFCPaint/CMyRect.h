#pragma once
#include "CMyShape.h"
class CMyRect :
    public CMyShape
{
	CPoint start, end;
	virtual void draw(CDC& pDC);
	virtual void mouseDown(CPoint& pt);
	virtual void mouseUp(CPoint& pt);
};

