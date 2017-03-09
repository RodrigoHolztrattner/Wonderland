////////////////////////////////////////////////////////////////////////////////
// Filename: TLinkedList.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TLinkedList_H_
#define _TLinkedList_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: TLinkedList
////////////////////////////////////////////////////////////////////////////////
template<typename ObjectType>
class TLinkedList
{
public:

	// The node type
	struct Node
	{
		// The object itself
		ObjectType object;

		// The next node
		Node* next;
	};

public:
	TLinkedList()
	{
	}

	TLinkedList(const TLinkedList& other)
	{
	}

	~TLinkedList()
	{
	}
	/*

	// Create a new node and return a pointer to the object
	ObjectType* Create()
	{
		// Create a new node
		// ...

		// Link the new node
		// ...
	}

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

	// Remove the selected value
	void Remove(int index)
	{
		m_Array.Remove(index);
	}
	*/

private:

public:

//	TArray<Bucket> m_Array;
};

#endif
