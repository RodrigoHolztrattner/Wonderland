////////////////////////////////////////////////////////////////////////////////
// Filename: BinaryArray.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _BinaryArray_H_
#define _BinaryArray_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "Array.h"
/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: BinaryArray
////////////////////////////////////////////////////////////////////////////////
template<typename ObjectType, typename KeyType>
class BinaryArray
{
public:

	// The bucket object
	struct Bucket
	{
		Bucket(){}
		Bucket(ObjectType _object, KeyType _key)
		{
			object = _object;
			key = _key;
		}
		
		ObjectType object;
		KeyType key;
	};

public:
	BinaryArray()
	{
	}

	BinaryArray(const BinaryArray& other)
	{
	}

	~BinaryArray()
	{
	}

	// Add a value to the array
	void Add(ObjectType _value, KeyType _key)
	{
		AddPrivate(Bucket(_value, _key), 0, m_Array.Size(), _key);
	}

public:

	// Zero the array
	void Zero()
	{
		m_Array.Zero();
	}

	// Get the number of units
	int Size()
	{
		return m_Array.Size();
	}

	// Return an object withou using the binary search
	ObjectType& GetObject(int index)
	{
		return m_Array[index].object;
	}

	// Return the index value
	ObjectType operator [] (KeyType _key)
	{
		return BinarySearchPrivate(0, m_Array.Size(), _key);
	}

	ObjectType BinarySearchPrivate(unsigned int _startIndex, unsigned int _endIndex, KeyType _key)
	{
		unsigned int mediumIndex = (_startIndex + _endIndex) / 2;
		unsigned int range = _endIndex - _startIndex;

		// Check if we are inside the critical range
		if (range <= 3)
		{
			// From the start index to the end one
			for (int i = _startIndex; i<_endIndex; i++)
			{
				// Check if the current key is bigger then the one we are inserting
				if (m_Array[i].key == _key)
				{
					// We found it
					return m_Array[i].object;
				}
			}

			// If we are here the object does not exist
			return nullptr;
		}

		// Compare the key
		if (_key > m_Array[mediumIndex].key)
		{
			// Medium to end
			BinarySearchPrivate(mediumIndex, _endIndex, _key);
		}
		else if (_key < m_Array[mediumIndex].key)
		{
			// Start to medium
			BinarySearchPrivate(_startIndex, mediumIndex, _key);
		}
		else if (_key == m_Array[mediumIndex].key)
		{
			// We found it
			return m_Array[mediumIndex].object;
		}
		else
		{
			return nullptr;
		}
	}

	// Remove the selected value
	void Remove(int index)
	{
		m_Array.Remove(index);
	}

private:

	void AddPrivate(Bucket _bucket, unsigned int _startIndex, unsigned int _endIndex, KeyType _key)
	{
		unsigned int mediumIndex = (_startIndex + _endIndex) / 2;
		unsigned int range = _endIndex - _startIndex;

		// Check if we are inside the critical range
		if (range <= 3)
		{
			// From the start index to the end one
			for (int i = _startIndex; i<_endIndex; i++)
			{

				// Check if the current key is bigger then the one we are inserting
				if (m_Array[i].key > _key)
				{
					// Insert here
					m_Array.Insert(_bucket, i);

					return;
				}
			}

			// If we are here, we should insert at the last position
			m_Array.Insert(_bucket, _endIndex);

			return;
		}

		// Compare the key
		if (_key > m_Array[mediumIndex].key)
		{
			// Medium to end
			AddPrivate(_bucket, mediumIndex, _endIndex, _key);
		}
		else if (_key <= m_Array[mediumIndex].key)
		{
			// Start to medium
			AddPrivate(_bucket, _startIndex, mediumIndex, _key);
		}
	}

public:

	Array<Bucket> m_Array;
};

#endif
