////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderProgram.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\Support\Math\Math.h"
#include "..\..\Support\Container\Array\Array.h"

#include <GLEW\glew.h>
#include <GLFW\glfw3.h>

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

// We know the shader shard class
class ShaderShard;

////////////////////////////////////////////////////////////////////////////////
// Class name: ShaderProgram
////////////////////////////////////////////////////////////////////////////////
class ShaderProgram
{
private:

public:
	ShaderProgram();
	ShaderProgram(const ShaderProgram& other);
	~ShaderProgram();

	// Make the program
	bool MakeProgram();

	// Attach a shard
	void AttachShard(ShaderShard* _shader);

	// Set a input variable
	void SetInputVariable(unsigned int _location, char* _name);

	// Compile the shader program
	bool CompileProgram();

	// Use this program to render
	void UseProgram();

	// Return an uniform location
	unsigned int GetUniformLocation(char* _uniformName);

	// Return the program id
	unsigned int GetId();

private:

	// Output a program linker error message
	void OutputLinkerErrorMessage(unsigned int _programId);

private:

	// The program id
	unsigned int m_ProgramId;
};