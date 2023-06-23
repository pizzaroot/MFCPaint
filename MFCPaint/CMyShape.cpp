#include "pch.h"
#include "CMyShape.h"

CMyShape::CMyShape()
{
	isSelected = false;
	color = RGB(rand() % 206, rand() % 206, rand() % 206);
}
