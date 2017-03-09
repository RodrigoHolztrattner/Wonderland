////////////////////////////////////////////////////////////////////////////////
// Filename: GlobalList.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

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
// #define EXPAND_SIZE				4

// The foreach macro
// #define foreach(object, ofType, from)	for(ofType object, int i=0; object = from[i], i<from.Size(); i++)

template<typename ObjectType>
struct GlobalListNode
{
	// The object itself
	ObjectType* object;

	// The next node
	GlobalListNode* next;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: GlobalList
////////////////////////////////////////////////////////////////////////////////
template<typename ObjectType>
class GlobalList
{
private:


public:
	GlobalList()
	{
	}

	GlobalList(const GlobalList& other)
	{
	}

	~GlobalList()
	{
	}

	// Create a new object for this list
	static ObjectType* Create()
	{
		GlobalListNode<ObjectType>* newNode;

		// Check if we can use a component from the empty list
		if (m_EmptyList != nullptr)
		{
			// Get the new node
			newNode = m_EmptyList;

			// Set the empty list top
			m_EmptyList = m_EmptyList->next;
		}
		else
		{
			// Create a new node
			newNode = new GlobalListNode<ObjectType>;

			// Create a new object
			newNode->object = new ObjectType;
		}
		
		// Link the new node
		newNode->next = m_ObjectList;
		m_ObjectList = newNode;
		m_TotalElements++;

		return newNode->object;
	}

	// Remove a node from the list
	static void RemoveNode(GlobalListNode<ObjectType>* _lastNode, GlobalListNode<ObjectType>* _currentNode)
	{
		// Check if the last node is valid
		if (_lastNode != nullptr)
		{
			// Set the next reference
			_lastNode->next = _currentNode->next;
		}

		// Check if the current node is the root node
		if (m_ObjectList == _currentNode)
		{
			m_ObjectList = _currentNode->next;
		}

		// Insert the current node into the empty list
		_currentNode->next = m_EmptyList;
		m_EmptyList = _currentNode;
	}

	// Initialize the iterator
	static ObjectType* InitializeIterator()
	{
		// Get the component list
		m_Iterator = m_ObjectList;

		// Set the last node
		m_IteratorHelper = nullptr;

		return nullptr;
	}

	// Return the next object from the current iterator position
	static ObjectType* GetNextObject()
	{
		// If its valid
		if (m_Iterator != nullptr)
		{
			// Set the return object
			ObjectType* object = m_Iterator->object;

			// Set the new current node
			// m_Iterator = m_Iterator->next;

			return object;
		}

		return nullptr;
	}

	// Increment the iterator
	static void IncrementIterator()
	{
		// Check if we deleted an object
		if (m_ElementDeleted)
		{
			// Set to false
			m_ElementDeleted = false;
		}
		else
		{
			// Set the last node
			m_IteratorHelper = m_Iterator;

			// Set the new current node
			m_Iterator = m_Iterator->next;
		}
	}

	// Remove a node from the list
	static void RemoveCurrentNode()
	{
		// Get the next current node
		GlobalListNode<ObjectType>* nextCurrentNode = m_Iterator->next;

		// Remove this node
		RemoveNode(m_IteratorHelper, m_Iterator);

		// Set the new current node
		m_Iterator = nextCurrentNode;

		// We deleted an object
		m_ElementDeleted = true;
		m_TotalElements--;
	}		

	// Return the total number of elements
	static unsigned int Size()
	{
		return m_TotalElements;
	}

private:

	// The component list
	static GlobalListNode<ObjectType>* m_ObjectList;

	// The empty list
	static GlobalListNode<ObjectType>* m_EmptyList;

	// The iterator list
	static GlobalListNode<ObjectType>* m_Iterator;

	// The iterator helper
	static GlobalListNode<ObjectType>* m_IteratorHelper;

	// The total number of elements
	static unsigned int m_TotalElements;

	// If we deleted an element
	static bool m_ElementDeleted;
};

template<typename ObjectType>
GlobalListNode<ObjectType>* GlobalList<ObjectType>::m_ObjectList = nullptr;

template<typename ObjectType>
GlobalListNode<ObjectType>* GlobalList<ObjectType>::m_EmptyList = nullptr;

template<typename ObjectType>
GlobalListNode<ObjectType>* GlobalList<ObjectType>::m_Iterator = nullptr;

template<typename ObjectType>
GlobalListNode<ObjectType>* GlobalList<ObjectType>::m_IteratorHelper = nullptr;

template<typename ObjectType>
unsigned int GlobalList<ObjectType>::m_TotalElements = 0;

template<typename ObjectType>
bool GlobalList<ObjectType>::m_ElementDeleted = false;