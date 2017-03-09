////////////////////////////////////////////////////////////////////////////////
// Filename: StaticArray.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <stdio.h>
#include <string.h>

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: StaticArray
////////////////////////////////////////////////////////////////////////////////
template <typename ObjectType, int FixedSize>
class StaticArray
{
public:
	StaticArray()
	{
		// Set the initial data
		m_CurrentSize = 0;

		// Zero the static array
		memset(m_ObjectArray, 0, sizeof(ObjectType) * FixedSize);
	}

	StaticArray(const StaticArray&) {}
	~StaticArray() {}

	// Add an object
	bool Add(ObjectType _object)
	{
		// Check if there is enough space
		if (m_CurrentSize >= FixedSize)
		{
			return false;
		}

		// Insert into the next valid position
		m_ObjectArray[m_CurrentSize] = _object;

		// Increment the number of objects
		m_CurrentSize++;

		return true;
	}

	// Remove an object from the array
	bool Remove(unsigned int _index)
	{
		// Check if the target is valid
		if (_index >= m_CurrentSize)
		{
			return false;
		}

		// Remove the object
		memset(&m_ObjectArray[_index], 0, sizeof(ObjectType));

		// Set the number of objects we need to move
		unsigned int numberObjectsMove = m_CurrentSize - _index - 1;
		if (numberObjectsMove <= 0)
		{
			// Decrement the number of objects
			m_CurrentSize--;

			return true;
		}

		// Move all other objects
		memcpy(&m_ObjectArray[_index], &m_ObjectArray[_index + 1], sizeof(ObjectType) * numberObjectsMove);

		// Decrement the number of objects
		m_CurrentSize--;

		return true;
	}

	// Return an object
	ObjectType Get(unsigned int _index)
	{
		// Check if the index is valid
		if (_index >= m_CurrentSize)
		{
			// Problem!!
			// ...
		}

		return m_ObjectArray[_index];
	}

	// Return the current size
	unsigned int Size()
	{
		return m_CurrentSize;
	}

private:

	// The current size
	unsigned int m_CurrentSize;

	// The object array
	ObjectType m_ObjectArray[FixedSize];

};