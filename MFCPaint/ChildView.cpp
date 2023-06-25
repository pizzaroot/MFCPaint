
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCPaint.h"
#include "ChildView.h"
#include "CMyShape.h"
#include "CMyRect.h"
#include "CMyCircle.h"
#include "CMyCurve.h"
#include "CMyStar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CChildView::CChildView()
{
	mode = 1; mouseDown = false;
	isSingleSelect = false;
	curSelectedCnt = 0;
	shapes = new CMyGroup();
}

CChildView::~CChildView()
{
	delete shapes;
}

void CChildView::unselectAll(bool redraw)
{
	for (auto& shape : shapes->children) shape->isSelected = false;
	if (redraw) Invalidate();
}

void CChildView::updateAlignUI(CCmdUI* pCmdUI)
{
	int selectedCnt = 0;
	for (auto& shape : shapes->children) selectedCnt += shape->isSelected;
	pCmdUI->Enable(selectedCnt);
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_COMMAND(ID_DRAW_RECTANGLE, &CChildView::OnDrawRectangle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_RECTANGLE, &CChildView::OnUpdateDrawRectangle)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_CIRCLE, &CChildView::OnDrawCircle)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CIRCLE, &CChildView::OnUpdateDrawCircle)
	ON_COMMAND(ID_DRAW_CURVE, &CChildView::OnDrawCurve)
	ON_UPDATE_COMMAND_UI(ID_DRAW_CURVE, &CChildView::OnUpdateDrawCurve)
	ON_COMMAND(ID_DRAW_STAR, &CChildView::OnDrawStar)
	ON_UPDATE_COMMAND_UI(ID_DRAW_STAR, &CChildView::OnUpdateDrawStar)
	ON_COMMAND(ID_ACTION_SELECT, &CChildView::OnActionSelect)
	ON_UPDATE_COMMAND_UI(ID_ACTION_SELECT, &CChildView::OnUpdateActionSelect)
	ON_COMMAND(ID_DELETE_SHAPE, &CChildView::OnDeleteShape)
	ON_COMMAND(ID_ALIGN_BRINGBACK, &CChildView::OnAlignBringback)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_ALIGN_BRINGFRONT, &CChildView::OnAlignBringfront)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_BRINGBACK, &CChildView::OnUpdateAlignBringback)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_BRINGFRONT, &CChildView::OnUpdateAlignBringfront)
	ON_COMMAND(ID_ACTION_GROUP, &CChildView::OnActionGroup)
	ON_UPDATE_COMMAND_UI(ID_ACTION_GROUP, &CChildView::OnUpdateActionGroup)
	ON_COMMAND(ID_ACTION_UNGROUP, &CChildView::OnActionUngroup)
	ON_UPDATE_COMMAND_UI(ID_ACTION_UNGROUP, &CChildView::OnUpdateActionUngroup)
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);
	
	CRect rect;
	GetClientRect(&rect);
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap bitmap;
	width = rect.Width(), height = rect.Height();
	bitmap.CreateCompatibleBitmap(&dc, width, height);
	memDC.SelectObject(&bitmap);

	memDC.SelectStockObject(WHITE_PEN);
	memDC.Rectangle(0, 0, width, height);

	int selectedCnt = 0;
	for (auto& shape : shapes->children) {
		shape->draw(memDC);
		if (shape->isSelected) {
			memDC.SelectStockObject(NULL_BRUSH);
			CPen selectPen(PS_DOT, 1, RGB(255, 0, 0));
			memDC.SelectObject(&selectPen);
			memDC.Rectangle(shape->topLeft.x - 5, shape->topLeft.y - 5, shape->bottomRight.x + 5, shape->bottomRight.y + 5);
			selectedCnt++;
		}
		
	}

	curSelectedCnt = selectedCnt;

	if (mode == 5 && mouseDown && !isSingleSelect) {
		memDC.SelectStockObject(NULL_BRUSH);
		CPen selectPen(PS_DOT, 1, RGB(0, 0, 0));
		memDC.SelectObject(&selectPen);
		memDC.Rectangle(start.x, start.y, end.x, end.y);
	}

	CString info; info.Format(_T("Number of Shapes: %d"), (int)shapes->children.size());
	CString info2; info2.Format(_T("Number of Selected: %d"), selectedCnt);

	memDC.TextOut(0, 0, info);
	memDC.TextOut(0, 20, info2);

	dc.BitBlt(0, 0, width, height, &memDC, 0, 0, SRCCOPY);
}



BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void CChildView::OnDrawRectangle()
{
	unselectAll();
	mode = 1;
}


void CChildView::OnUpdateDrawRectangle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mode == 1);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDown(nFlags, point);
	CMyGroup* p = new CMyGroup();
	switch (mode) {
	case 1:
		p->setShape(new CMyRect());
		break;
	case 2:
		p->setShape(new CMyCircle());
		break;
	case 3:
		p->setShape(new CMyCurve());
		break;
	case 4:
		p->setShape(new CMyStar());
		break;
	case 5:
		start = point; end = point;
		if (!(nFlags & MK_SHIFT)) unselectAll(false);
		isSingleSelect = false;
		for (std::list<CMyGroup*>::reverse_iterator iter = shapes->children.rbegin(); iter != shapes->children.rend(); iter++) {
			if ((*iter)->isInside(point)) {
				(*iter)->isSelected = true;
				isSingleSelect = true;
				break;
			}
		}

	}
	if (p->shape) {
		p->mouseDown(point);
		shapes->push_back(p);
	}
	mouseDown = true;
	SetCapture();
	Invalidate();
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	switch (mode) {
	case 1:
	case 2:
	case 3:
	case 4:
		shapes->children.back()->mouseUp(point);
		break;
	case 5:
		if (isSingleSelect) {
			end = point;
			for (auto& shape : shapes->children) {
				if (shape->isSelected) {
					shape->moveVector(start, end);
				}
			}
			isSingleSelect = false;
		} else {
			end = point;
			for (auto& shape : shapes->children) {
				if (min(start.x, end.x) <= shape->topLeft.x
					&& min(start.y, end.y) <= shape->topLeft.y
					&& max(start.x, end.x) >= shape->bottomRight.x
					&& max(start.y, end.y) >= shape->bottomRight.y) {
					shape->isSelected = true;
				}
			}
		}
		break;
	}
	mouseDown = false;
	ReleaseCapture();
	Invalidate();
	CWnd::OnLButtonUp(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	switch (mode) {
	case 1:
	case 2:
	case 3:
	case 4:
		if (mouseDown) {
			shapes->children.back()->mouseUp(point);
		}
		break;
	case 5:
		if (isSingleSelect) {
			end = point;
			for (auto& shape : shapes->children) {
				if (shape->isSelected) {
					shape->moveVector(start, end);
				}
			}
			start = point;
		}
		else end = point;
		break;
	}
	Invalidate();

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnDrawCircle()
{
	unselectAll();
	mode = 2;
}


void CChildView::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mode == 2);
}


void CChildView::OnDrawCurve()
{
	unselectAll();
	mode = 3;
}


void CChildView::OnUpdateDrawCurve(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mode == 3);
}


void CChildView::OnDrawStar()
{
	unselectAll();
	mode = 4;
}


void CChildView::OnUpdateDrawStar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mode == 4);
}


void CChildView::OnActionSelect()
{
	mode = 5;
}


void CChildView::OnUpdateActionSelect(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mode == 5);
}


void CChildView::OnDeleteShape()
{
	for (std::list<CMyGroup*>::iterator iter = shapes->children.begin(); iter != shapes->children.end();) {
		if ((*iter)->isSelected) {
			delete* iter;
			shapes->erase(iter++);
		}
		else iter++;
	}
	Invalidate();
}


void CChildView::OnAlignBringback()
{
	std::list<CMyGroup*> tmpShapes;
	for (std::list<CMyGroup*>::reverse_iterator iter = shapes->children.rbegin(); iter != shapes->children.rend();) {
		if ((*iter)->isSelected) {
			tmpShapes.push_back(*iter);
			shapes->children.erase(--iter.base());
		}
		else iter++;
	}
	for (auto& s : tmpShapes) shapes->children.push_front(s);
	Invalidate();
}


void CChildView::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CMenu* pMenu = AfxGetMainWnd()->GetMenu()->GetSubMenu(4);
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, point.x, point.y, AfxGetMainWnd());
}


void CChildView::OnAlignBringfront()
{
	std::list<CMyGroup*> tmpShapes;
	for (std::list<CMyGroup*>::iterator iter = shapes->children.begin(); iter != shapes->children.end();) {
		if ((*iter)->isSelected) {
			tmpShapes.push_back(*iter);
			shapes->children.erase(iter++);
		}
		else iter++;
	}
	for (auto& s : tmpShapes) shapes->push_back(s);
	Invalidate();
}


void CChildView::OnUpdateAlignBringback(CCmdUI* pCmdUI)
{
	updateAlignUI(pCmdUI);
}


void CChildView::OnUpdateAlignBringfront(CCmdUI* pCmdUI)
{
	updateAlignUI(pCmdUI);
}


void CChildView::OnActionGroup()
{
	if (curSelectedCnt < 2) return;
	CMyGroup* grouped = new CMyGroup();
	grouped->isSelected = true;
	for (std::list<CMyGroup*>::iterator iter = shapes->children.begin(); iter != shapes->children.end();) {
		if ((*iter)->isSelected) {
			grouped->push_back(*iter);
			shapes->erase(iter++);
		}
		else iter++;
	}
	shapes->push_back(grouped);
	Invalidate();
}


void CChildView::OnUpdateActionGroup(CCmdUI* pCmdUI)
{
	pCmdUI->Enable(curSelectedCnt >= 2);
}


void CChildView::OnActionUngroup()
{
	std::list<CMyGroup*> tmpShapes;
	for (std::list<CMyGroup*>::iterator iter = shapes->children.begin(); iter != shapes->children.end();) {
		if ((*iter)->isSelected && (*iter)->shape == NULL) {
			for (auto& child : (*iter)->children) {
				tmpShapes.push_back(child);
			}
			(*iter)->children.clear();
			delete *iter;
			shapes->erase(iter++);
		}
		else iter++;
	}
	for (auto& g : tmpShapes) {
		shapes->push_back(g);
	}
	Invalidate();
}


void CChildView::OnUpdateActionUngroup(CCmdUI* pCmdUI)
{
	bool hasChild = false;
	for (auto& g : shapes->children) {
		if (g->isSelected && g->shape == NULL) { hasChild = true; break; }
	}
	pCmdUI->Enable(hasChild);
}
