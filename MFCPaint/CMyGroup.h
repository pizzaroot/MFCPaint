#pragma once
#include "CMyShape.h"
#include <list>
class CMyGroup : public CMyShape
{
public:
	CMyGroup();
	~CMyGroup();
	CMyShape* shape;
	std::list<CMyGroup*> children;
	void draw(CDC& pDC);
	void mouseDown(CPoint& pt);
	void mouseUp(CPoint& pt);
	bool isInside(CPoint& pt);

	void updateFrame();
	void resetFrame();
	void setShape(CMyShape *shape);
	void push_back(CMyGroup* g);
	void erase(std::list<CMyGroup*>::iterator iter);
	void moveVector(CPoint& before, CPoint& after);
};

