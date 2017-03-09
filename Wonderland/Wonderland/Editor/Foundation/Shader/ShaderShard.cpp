////////////////////////////////////////////////////////////////////////////////
// Filename: ShaderShard.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ShaderShard.h"

#include <fstream>
using namespace std;

ShaderShard::ShaderShard()
{
	// Set the initial data
	m_ByteData = nullptr;
}

ShaderShard::ShaderShard(char* _data)
{
	// Initialize the bytedata
	m_ByteData = _data;
}

ShaderShard::ShaderShard(const ShaderShard& other)
{
}

ShaderShard::~ShaderShard()
{
	// Delete the byte data
	if (m_ByteData != nullptr)
	{
		delete[] m_ByteData;
	}
}

void ShaderShard::SetData(char* _data)
{
	// Initialize the bytedata
	m_ByteData = _data;
}

bool ShaderShard::MakeShard(unsigned int _shardType)
{
	int status;

	// Create the shader object
	m_ShardId = glCreateShader(_shardType);

	// Set the shader data
	glShaderSource(m_ShardId, 1, &m_ByteData, NULL);

	// Compile the shader
	glCompileShader(m_ShardId);

	// Check to see if the vertex shader compiled successfully.
	glGetShaderiv(m_ShardId, GL_COMPILE_STATUS, &status);
	if (status != 1)
	{
		// Output the shard error message
		OutputShardErrorMessage(m_ShardId);
		throw std::runtime_error("Erro criando o shader!");

		return false;
	}

	return true;
}

unsigned int ShaderShard::GetShardId()
{
	return m_ShardId;
}


void ShaderShard::OutputShardErrorMessage(unsigned int shaderId)
{
	int logSize, i;
	char* infoLog;
	ofstream fout;
	wchar_t newString[128];
	unsigned int error, convertedChars;

	// Get the size of the string containing the information log for the failed shader compilation message.
	glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logSize);

	// Increment the size by one to handle also the null terminator.
	logSize++;

	// Create a char buffer to hold the info log.
	infoLog = new char[logSize];
	if (!infoLog)
	{
		return;
	}

	// Now retrieve the info log.
	glGetShaderInfoLog(shaderId, logSize, NULL, infoLog);

	// Open a file to write the error message to.
	fout.open("shader-error.txt");

	// Write out the error message.
	for (i = 0; i<logSize; i++)
	{
		fout << infoLog[i];
	}

	// Close the file.
	fout.close();

	return;
}