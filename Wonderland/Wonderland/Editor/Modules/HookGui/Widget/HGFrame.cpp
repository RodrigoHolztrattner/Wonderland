////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFrame.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HGFrame.h"

HookGui::HGFrame::HGFrame() : x(0), y(0), width(0), height(0)
{

}

HookGui::HGFrame::HGFrame(float _x, float _y, float _width, float _height) : x(_x), y(_y), width(_width), height(_height)
{

}

HookGui::HGFrame::~HGFrame()
{
}

bool HookGui::HGFrame::PointIsInside(float _x, float _y)
{
	// Bounds check
	if (_x < x || _x >= (x + width) || _y < y || _y >= (y + height))
	{
		return false;
	}

	return true;
}