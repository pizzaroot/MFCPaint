
// ChildView.h: CChildView 클래스의 인터페이스
//


#pragma once
#include <list>
#include "CMyShape.h"
// CChildView 창

class CChildView : public CWnd
{
// 생성입니다.
public:
	CChildView();

// 특성입니다.
public:
	int width, height, mode;
	bool mouseDown, isSingleSelect;
	std::list<CMyShape*> shapes;
	CPoint start, end;
// 작업입니다.
public:

// 재정의입니다.
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CChildView();
	void unselectAll(bool redraw = true);
	void updateAlignUI(CCmdUI* pCmdUI);
	// 생성된 메시지 맵 함수
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDrawRectangle();
	afx_msg void OnUpdateDrawRectangle(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawCircle();
	afx_msg void OnUpdateDrawCircle(CCmdUI* pCmdUI);
	afx_msg void OnDrawCurve();
	afx_msg void OnUpdateDrawCurve(CCmdUI* pCmdUI);
	afx_msg void OnDrawStar();
	afx_msg void OnUpdateDrawStar(CCmdUI* pCmdUI);
	afx_msg void OnActionSelect();
	afx_msg void OnUpdateActionSelect(CCmdUI* pCmdUI);
	afx_msg void OnDeleteShape();
	afx_msg void OnAlignBringback();
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAlignBringfront();
	afx_msg void OnUpdateAlignBringback(CCmdUI* pCmdUI);
	afx_msg void OnUpdateAlignBringfront(CCmdUI* pCmdUI);
};

