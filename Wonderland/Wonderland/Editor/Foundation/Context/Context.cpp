////////////////////////////////////////////////////////////////////////////////
// Filename: Context.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Context.h"

///////////////
// NAMESPACE //
///////////////

Context::Context()
{
}

Context::Context(const Context& other)
{
}

Context::~Context()
{
}

bool Context::Initialize()
{
	// Set the screen dimension data
	m_ScreenWidth = 1600; // 1900
	m_ScreenHeight = 1024; // 1000

	// Create the world, view and ortho matrices
	m_WorldMatrix.BuildIdentity();
	m_ViewMatrix.BuildView(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 1), Vector3(0, 1, 0));
	m_OrthoMatrix.BuildOrtho(3.14159265358979323846f / 4.0f, m_ScreenWidth, m_ScreenHeight, 0.1, 1000.0f);
	m_OrthoMatrix = m_ViewMatrix = m_WorldMatrix;

	return true;
}