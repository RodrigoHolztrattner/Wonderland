////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderManager.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ShaderManager.h"

// Initialize the global shader array
Array<ShaderManager*> ShaderManager::s_GlobalShaderArray;

ShaderManager::ShaderManager()
{
	// Insert this shader into the global array
	ShaderManager* temp = this;
	s_GlobalShaderArray.Add(temp);
}

ShaderManager::ShaderManager(const ShaderManager& other)
{
}

ShaderManager::~ShaderManager()
{
}

void ShaderManager::ProcessGlobalRenderPhase()
{
	// For each shader inside the global array
	for (int i = 0; i < s_GlobalShaderArray.Size(); i++)
	{
		// Prepare to render
		s_GlobalShaderArray[i]->PrepareToRender();

		// Render all objects stored inside this shader
		s_GlobalShaderArray[i]->Render();
	}
}