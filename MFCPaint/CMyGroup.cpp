#include "pch.h"
#include "CMyGroup.h"
#define INF 0x3f3f3f3f

CMyGroup::CMyGroup()
{
	shape = NULL; isSelected = false;
	resetFrame();
}

CMyGroup::~CMyGroup()
{
	for (auto& g : children) delete g;
	delete shape;
}

void CMyGroup::draw(CDC& pDC)
{
	if (shape) {
		shape->draw(pDC);
		return;
	}
	for (auto& child : children) child->draw(pDC);
}

void CMyGroup::mouseDown(CPoint& pt)
{
	shape->mouseDown(pt); updateFrame();
}

void CMyGroup::mouseUp(CPoint& pt)
{
	shape->mouseUp(pt); updateFrame();
}

bool CMyGroup::isInside(CPoint& pt)
{
	if (shape) return shape->isInside(pt);
	bool inside = false;
	for (auto& child : children) {
		inside = inside || child->isInside(pt);
	}
	return inside;
}

void CMyGroup::updateFrame()
{
	topLeft = shape->topLeft;
	bottomRight = shape->bottomRight;
}

void CMyGroup::resetFrame()
{
	topLeft.x = INF, topLeft.y = INF;
	bottomRight.x = -INF, bottomRight.y = -INF;
}

void CMyGroup::setShape(CMyShape* shape)
{
	this->shape = shape;
}

void CMyGroup::push_back(CMyGroup* g)
{
	children.push_back(g);
	topLeft.x = min(topLeft.x, g->topLeft.x);
	topLeft.y = min(topLeft.y, g->topLeft.y);
	bottomRight.x = max(bottomRight.x, g->bottomRight.x);
	bottomRight.y = max(bottomRight.y, g->bottomRight.y);
}

void CMyGroup::erase(std::list<CMyGroup*>::iterator iter)
{
	children.erase(iter);
}

void CMyGroup::moveVector(CPoint& before, CPoint& after)
{
	moveFrame(before, after);
	if (shape) {
		shape->moveVector(before, after);
		return;
	}
	for (auto& child : children) child->moveVector(before, after);
}
