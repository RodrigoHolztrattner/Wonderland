////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderBase.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\Support\Math\Math.h"
#include "..\..\Support\Container\Array\Array.h"

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

#include "ShaderManager.h"
#include "ShaderFileLoader.h"
#include "ShaderShard.h"
#include "ShaderProgram.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

class ShaderIndirection
{
public:

	// Render an object on this frame
	virtual void RenderOnThisFrame(void* _object) = 0;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderBase
////////////////////////////////////////////////////////////////////////////////
template <typename ShaderType, typename ObjectType>
class ShaderBase : public ShaderFileLoader, public ShaderIndirection, public ShaderManager
{

public:
	ShaderBase() {}
	ShaderBase(const ShaderBase&) {}
	~ShaderBase() {}

	////////////
	// GLOBAL //
	////////////

	// Return the instance
	static ShaderType* GetInstance()
	{
		static ShaderType* shader = nullptr;

		// Check if we should initialize
		if (shader == nullptr)
		{
			// Initialize the shader
			shader = new ShaderType;
			if (!shader->Initialize())
			{
				shader = nullptr;
			}
		}

		return shader;
	}

	// Render all objects
	void Render()
	{
		// Prepare to render
		PrepareToRender();

		// Call the render aux for each object inside our queue
		for (int i = 0; i < m_RenderQueue.Size(); i++)
		{
			// Call the render aux
			RenderAux(m_RenderQueue[i]);
		}

		// Clear the render queue
		m_RenderQueue.Clean();
	}

	/////////////////////
	// VIRTUAL METHODS //
public: /////////////////

	// Initialize the UI shader
	virtual bool Initialize() = 0;

	// Prepare to render
	virtual bool PrepareToRender() = 0;

	// Process a object
	virtual void ProcessObject(ObjectType* _object) {};

	// Render an object on this frame
	virtual void RenderOnThisFrame(void* _object)
	{
		ObjectType* temp = static_cast<ObjectType*>(_object);
		AddObject(temp);
	}

protected:

	// Render all objects (aux)
	virtual void RenderAux(ObjectType* _object) = 0;

	////////////
	// MEMBER //
public: ////////

	// Add an object to the render queue
	void AddObject(ObjectType* _object)
	{
		// Add the object
		m_RenderQueue.Add(_object);

		// Process the object
		ProcessObject(_object);
	}

private:

	// The object render array
	Array<ObjectType*> m_RenderQueue;

private:

	bool SetShaderParameters(float*, float*, float*);

};