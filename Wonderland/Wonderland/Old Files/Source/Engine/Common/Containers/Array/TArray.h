////////////////////////////////////////////////////////////////////////////////
// Filename: TArray.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TArray_H_
#define _TArray_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include <string.h> // memcpy
#include <stdlib.h> //realloc

/////////////
// DEFINES //
/////////////

// The base expand size
#define EXPAND_SIZE				4

// The foreach macro
#define foreach(object, ofType, from)	for(ofType object, int i=0; object = from[i], i<from.Size(); i++)

////////////////////////////////////////////////////////////////////////////////
// Class name: TArray
////////////////////////////////////////////////////////////////////////////////
template<typename T>
class TArray
{
private:

public:
	TArray()
	{
		// Set the initial data
		expandSize = EXPAND_SIZE;
		numberUnits = 0;
		currentSize = 0;
	}

	TArray(const TArray& other)
	{
		// Set the data
		currentSize = other.currentSize;
		numberUnits = other.numberUnits;
		expandSize = other.expandSize;
		data = other.data;
	}

	~TArray()
	{
		// Delete the old array if we have at last 1 on it
		if (numberUnits)
		{
			delete[] data;
			data = 0;
			numberUnits = 0;
			currentSize = 0;
		}
	}

	void* operator new[](unsigned int size)
	{
		size = size;
	}

	void SetExpandSize(int size)
	{
		expandSize = size;
	}

	// Add a value to the array
	void Add(T& value)
	{
		T* tempArray;

		// Check if the size its ok
		if ((numberUnits + 1) >= currentSize)
		{
			// Set the new current size
			currentSize += expandSize;

			// Alocate space for the tempArray
			tempArray = new T[currentSize];

			// Copy the old array
			memcpy(tempArray, data, sizeof(T) * numberUnits);

			// Delete the old array if we have at last 1 on it
			if (numberUnits)
			{
				delete[] data;
				data = 0;
			}

			// Set the new array
			data = tempArray;
		}

		// Set the value
		data[numberUnits] = value;

		// Increment the size
		numberUnits++;
	}

	// Add x values to the array
	void Add(T* from, int quantity)
	{
		T* tempArray;

		// Check if the size its ok
		if ((numberUnits + quantity) >= currentSize)
		{
			// Set the new current size
			currentSize += (quantity / expandSize) * expandSize + expandSize;

			// Alocate space for the tempArray
			tempArray = new T[currentSize];

			// Copy the old array
			memcpy(tempArray, data, sizeof(T) * numberUnits);

			// Delete the old array if we have at last 1 on it
			if (numberUnits)
			{
				delete[] data;
				data = 0;
			}

			// Set the new array
			data = tempArray;
		}

		// Copy the new data
		memcpy(&data[numberUnits], from, sizeof(T) * quantity);

		// Increment the size
		numberUnits += quantity;
	}

	// Return a value from the array
	T Get(int pos)
	{
		return data[pos];
	}

	// Zero the array
	void Zero()
	{
		// Delete the old array if we have at last 1 on it
		if (numberUnits)
		{
			delete[] data;
			data = 0;
		}

		// Set the values
		numberUnits = 0;
		currentSize = 0;
	}

	// Get the number of units
	int Size()
	{
		return numberUnits;
	}

	// Return the index value
	T& operator [] (int index)
	{
		return data[index];
	}

	// Insert a value at the selected position
	void Insert(T value, int pos)
	{
		T* tempArray;

		// Check if the size its ok
		if ((numberUnits + 1) >= currentSize)
		{
			// Set the new current size
			currentSize += expandSize;

			// Alocate space for the tempArray
			tempArray = new T[currentSize];

			// Copy the old array - part 1
			memcpy(&tempArray[0], &data[0], sizeof(T) * pos);

			// Copy the old array - part 2
			memcpy(&tempArray[pos + 1], &data[pos], sizeof(T) * (numberUnits - pos));

			// Set the value
			tempArray[pos] = value;

			// Delete the old array if we have at last 1 on it
			if (numberUnits)
			{
				delete[] data;
				data = 0;
			}

			// Set the new array
			data = tempArray;

			// Increment the size
			numberUnits++;

			return;
		}

		// Copy the old array
		memcpy(&data[pos + 1], &data[pos], sizeof(T) * (numberUnits - pos));

		// Set the value
		data[pos] = value;

		// Increment the size
		numberUnits++;
	}

	void Move(int from, int to)
	{
		T temp;
		int size;

		// Check if the position are the same
		if (from == to)
		{
			return;
		}

		// Set the temp variable
		temp = data[from];

		// Check if the from is bigger then to
		if (from > to)
		{
			// Set the size
			size = from - to;

			// Copy the values
			memcpy(&data[to + 1], &data[to], sizeof(T) * size);
		}
		else
		{
			// Set the size
			size = to - from;

			// Copy the values
			memcpy(&data[from], &data[from + 1], sizeof(T) * size);
		}

		// Set the temp value
		data[to] = temp;
	}

	// Clean every member inside this (but dont reduce the expanded size)
	void Clean()
	{
		// Set the values
		numberUnits = 0;
	}

	// Remove the selected value
	void Remove(int index)
	{
		T* tempArray;
		int from;

		// Set the from variable
		from = numberUnits - index - 1; // -1 ?

		// Check if the size its ok
		if ((numberUnits - 1) < (currentSize - expandSize))
		{
			// Set the new current size
			currentSize -= expandSize;

			// Alocate space for the tempArray
			tempArray = new T[currentSize];

			// Copy the first part from the array
			memcpy(tempArray, data, sizeof(T) * index);

			// Copy the second part
			memcpy(&tempArray[index], &data[index + 1], sizeof(T) * from);

			// Delete the old array if we have at last 1 on it
			if (numberUnits)
			{
				delete[] data;
				data = 0;
			}

			// Set the new array
			data = tempArray;
		}
		else
		{
			// Just overlap the item
			memcpy(&data[index], &data[index + 1], sizeof(T) * from);
		}

		// Increment the size
		numberUnits--;
	}

	// Return the data array
	T* GetArray()
	{
		return data;
	}

	// Return the last object
	T Last()
	{
		return data[numberUnits - 1];
	}

private:

	int currentSize;
	int numberUnits;
	int expandSize;

private:

	T* data;
};

#endif
