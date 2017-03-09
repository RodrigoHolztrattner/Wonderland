///////////////////////////////////////////////////////////////////////////////
// Filename: FDataSeeker.cpp
///////////////////////////////////////////////////////////////////////////////
#include "FDataSeeker.h"
#include <string.h>

FDataSeeker::FDataSeeker()
{
	// Set the initial data
	m_DataPosition = 0;
}

FDataSeeker::FDataSeeker(const FDataSeeker& other)
{
	m_DataPosition = other.m_DataPosition;
}

FDataSeeker::~FDataSeeker()
{
}

void FDataSeeker::Get(unsigned int _amount, unsigned char* _from, void* _to, bool _useMemcpy)
{
	// Check if we should use memcpy
	if (_useMemcpy)
	{
		memcpy(_to, &_from[m_DataPosition], _amount);
	}
	else
	{
		void** reinterpretedPtr = (void**)_to;
		*reinterpretedPtr = &_from[m_DataPosition];
	}

	// Advance the position
	m_DataPosition += _amount;
}

void FDataSeeker::Seek(unsigned long _position)
{
	m_DataPosition = _position;
}