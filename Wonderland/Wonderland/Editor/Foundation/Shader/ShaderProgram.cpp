////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderProgram.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ShaderProgram.h"

#include "ShaderShard.h"

#include <fstream>
using namespace std;

///////////////
// NAMESPACE //
///////////////

ShaderProgram::ShaderProgram()
{
}

ShaderProgram::ShaderProgram(const ShaderProgram& other)
{
}

ShaderProgram::~ShaderProgram()
{
}

bool ShaderProgram::MakeProgram()
{
	// Create the program object
	m_ProgramId = glCreateProgram();

	return true;
}

void ShaderProgram::AttachShard(ShaderShard* _shader)
{
	glAttachShader(m_ProgramId, _shader->GetShardId());
}

void ShaderProgram::SetInputVariable(unsigned int _location, char* _name)
{
	glBindAttribLocation(m_ProgramId, _location, _name);
}

unsigned int ShaderProgram::GetId()
{
	return m_ProgramId;
}

bool ShaderProgram::CompileProgram()
{
	int status;

	// Link the program
	glLinkProgram(m_ProgramId);

	// Get the status
	glGetProgramiv(m_ProgramId, GL_LINK_STATUS, &status);
	if (status != 1)
	{
		// If it did not link then write the syntax error message out to a text file for review.
		OutputLinkerErrorMessage(m_ProgramId);

		return false;
	}

	return true;
}

void ShaderProgram::UseProgram()
{
	glUseProgram(m_ProgramId);
}

unsigned int ShaderProgram::GetUniformLocation(char* _uniformName)
{
	return glGetUniformLocation(m_ProgramId, _uniformName);
}

void ShaderProgram::OutputLinkerErrorMessage(unsigned int _programId)
{
	int logSize, i;
	char* infoLog;
	ofstream fout;

	// Get the size of the string containing the information log for the failed shader compilation message.
	glGetProgramiv(_programId, GL_INFO_LOG_LENGTH, &logSize);

	// Increment the size by one to handle also the null terminator.
	logSize++;

	// Create a char buffer to hold the info log.
	infoLog = new char[logSize];
	if (!infoLog)
	{
		return;
	}

	// Now retrieve the info log.
	glGetProgramInfoLog(_programId, logSize, NULL, infoLog);

	// Open a file to write the error message to.
	fout.open("linker-error.txt");

	// Write out the error message.
	for (i = 0; i<logSize; i++)
	{
		fout << infoLog[i];
	}

	// Close the file.
	fout.close();

	return;
}