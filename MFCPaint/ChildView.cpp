
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCPaint.h"
#include "ChildView.h"
#include "CMyShape.h"
#include "CMyRect.h"
#include "CMyCircle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	mode = 1; mouseDown = false;
}

CChildView::~CChildView()
{
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
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
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

	for (auto& shape : shapes) {
		shape->draw(memDC);
	}

	dc.BitBlt(0, 0, width, height, &memDC, 0, 0, SRCCOPY);
}



BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void CChildView::OnDrawRectangle()
{
	mode = 1;
}


void CChildView::OnUpdateDrawRectangle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mode == 1);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CWnd::OnLButtonDown(nFlags, point);
	CMyShape* p = NULL;
	switch (mode) {
	case 1:
		p = new CMyRect();
		break;
	case 2:
		p = new CMyCircle();
		break;
	}
	if (p) {
		p->mouseDown(point);
		shapes.push_back(p);
	}
	mouseDown = true;
	SetCapture();
	Invalidate();
}


void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	switch (mode) {
	case 1:
		shapes.back()->mouseUp(point);
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
			shapes.back()->mouseUp(point);
		}
		break;
	}
	Invalidate();

	CWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnDrawCircle()
{
	mode = 2;
}


void CChildView::OnUpdateDrawCircle(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(mode == 2);
}
