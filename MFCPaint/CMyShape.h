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
	virtual bool isInside(CPoint& pt) { return false; }
	
	void moveFrame(CPoint& before, CPoint& after) {
		topLeft.x += after.x - before.x;
		topLeft.y += after.y - before.y;
		bottomRight.x += after.x - before.x;
		bottomRight.y += after.y - before.y;
	}
	virtual void moveVector(CPoint& before, CPoint& after) {};

	int ccw(CPoint &p1, CPoint& p2, CPoint& p3) {
		long long tmp = p1.x * p2.y + p2.x * p3.y + p3.x * p1.y;
		tmp -= p1.y * p2.x + p2.y * p3.x + p3.y * p1.x;
		return (0 < tmp) - (tmp < 0);
	}
	bool intersect(CPoint& l1s, CPoint& l1e, CPoint& l2s, CPoint& l2e) {
		int ccw1 = ccw(l1s, l1e, l2s) * ccw(l1s, l1e, l2e);
		int ccw2 = ccw(l2s, l2e, l1s) * ccw(l2s, l2e, l1e);
		return (ccw1 < 0) && (ccw2 < 0);
	}
};

