////////////////////////////////////////////////////////////////////////////////
// Filename: TQuadtree.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TQuadtree_H_
#define _TQuadtree_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\Math\WMath.h"
#include "..\Array\TArray.h"

/////////////
// DEFINES //
/////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: TQuadtree
////////////////////////////////////////////////////////////////////////////////
template<typename ObjectType, int width, int height, int depth>
class TQuadtree
{
private:

	// The maximum pick lenght for this quadtree
	static const unsigned int MaximumPickLenght = 100;

private:

	// The object tuple type
	struct QuadtreeObjectTuple
	{
		QuadtreeObjectTuple(){}
		QuadtreeObjectTuple(ObjectType* _object, WVector2 _location)
		{
			object = _object;
			location = _location;
		}

		// The object
		ObjectType* object;

		// The object location
		WVector2 location;
	};

	// The quad tree node
	struct QuadtreeNode
	{
		// The node location and size
		WVector2 location;
		WVector2 size;

		// If this node is a lead
		bool leaf;

		// The child nodes
		QuadtreeNode* childs[4];

		// The array of objects (empty if this is not a leaf)
		TArray<QuadtreeObjectTuple> objectsInside;
	};

public:
	TQuadtree()
	{
		// Create the root node
		m_RootNode = new QuadtreeNode;

		// Build the quadtree
		BuildTree(m_RootNode, WVector2(0, 0), WVector2(width, height));
	}

	TQuadtree(const TQuadtree&){}
	~TQuadtree(){}

	// Insert an object (return false if the object is out of range or if it already exist)
	bool Insert(ObjectType* _object, WVector2 _location = WVector2(0, 0), bool _useLocation = false)
	{
		// Check if the object is in range (the GetLocation() function ensure the object is an Actor)
		if (!InsideRange((_useLocation ? _location : _object->GetLocation())))
		{
			// Out of range
			return false;
		}

		// Get the leaf node (the GetLocation() function ensure the object is an Actor)
		QuadtreeNode* leafNode = LeafNode(m_RootNode, (_useLocation ? _location : _object->GetLocation()));

		// Check if the object exist
		if (ObjectExist(leafNode, _object))
		{
			// The object already exist
			return false;
		}

		// Insert the object
		leafNode->objectsInside.Add(QuadtreeObjectTuple(_object, (_useLocation ? _location : _object->GetLocation())));

		return true;
	}

	// Remove an object (return false if the object is out of range or if it does not exist)
	bool Remove(ObjectType* _object)
	{
		// Check if the object is in range (the GetLocation() function ensure the object is an Actor)
		if (!InsideRange(_object->GetLocation()))
		{
			// Out of range
			return false;
		}

		// Get the leaf node (the GetLocation() function ensure the object is an Actor)
		QuadtreeNode* leafNode = LeafNode(m_RootNode, _object->GetLocation());

		// Check if the object exist
		if (!ObjectExist(leafNode, _object, true))
		{
			// The object does not exist
			return false;
		}

		return true;
	}

	// Update an object (return false if the object goes out of range)
	bool Update(ObjectType* _object, WVector2 _location)
	{
		// Check if the object is in range
		if (!InsideRange(_location))
		{
			// Out of range
			return false;
		}

		// Get the leaf node
		QuadtreeNode* leafNode = LeafNode(m_RootNode, _location);

		// Get the old leaf node (the GetLocation() function ensure the object is an Actor)
		QuadtreeNode* oldLeafNode = LeafNode(m_RootNode, _object->GetLocation());

		// Check if the leafs are the same
		if (leafNode == oldLeafNode)
		{
			// The object is inside the same leaf
			return true;
		}

		// Remove the object
		Remove(_object);

		// Re-insert it (at the new location)
		Insert(_object, _location, true);

		return true;
	}

	//////////
	// PICK //
	//////////

	// Pick all objects inside range
	ObjectType** PickInRange(WVector2 _center, float _range, unsigned int& _pickCounter)
	{
		// Set the pick counter
		_pickCounter = 0;

		// Pick all objects in range
		PickAllObjectsInRange(m_RootNode, _pickCounter, _center, _range);

		return m_PickArray;
	}

	// Pick all objects inside range from the given class
	template <typename ClassType>
	ObjectType** PickInRangeFromClass(WVector2 _center, float _range, unsigned int& _pickCounter)
	{
		// Set the pick counter
		_pickCounter = 0;

		// Pick all objects in range
		PickAllObjectsInRangeFromClass<ClassType>(m_RootNode, _pickCounter, _center, _range);

		return m_PickArray;
	}

private:

	// Recursively build the tree
	void BuildTree(QuadtreeNode* _node, WVector2 _location, WVector2 _size, unsigned int _depth = 0)
	{ 
		// Set the location and the size
		_node->location = _location;
		_node->size = _size;

		// Check if we should keep building the tree
		if (_depth >= depth)
		{
			// This node is a leaf
			_node->leaf = true;

			// Null each child
			for (int i = 0; i < 4; i++)
			{
				// Null this child
				_node->childs[i] = nullptr;
			}
		}
		else
		{
			// This node isnt a leaf
			_node->leaf = false;

			// Create the 4 childs
			for (int i = 0; i < 4; i++)
			{
				// Create this child
				_node->childs[i] = new QuadtreeNode;
			}

			// For each child
			for (int i = 0; i < 4; i++)
			{
				// Call the function for this child
				BuildTree(_node->childs[i], WVector2(_location.x + _size.x * (i % 2) / 2.0, _location.y + _size.x * (i / 2) / 2.0), WVector2(_size.x / 2.0, _size.y / 2.0), _depth + 1);
			}
		}
	}

	// Verify if the given location is inside the tree range
	bool InsideRange(WVector2 _location)
	{
		return (_location.x < width || _location.y < height);
	}

	// Find a leaf node
	QuadtreeNode* LeafNode(QuadtreeNode* _node, WVector2 _location)
	{
		// Check if this node is a leaf
		if (!_node->leaf)
		{
			// Continue calling the function
			return LeafNode(_node->childs[NodeQuadrant(_node, _location)], _location);
		}

		return _node;
	}

	// Verify if the given object exist inside the given node
	bool ObjectExist(QuadtreeNode* _node, ObjectType* _object, bool _remove = false)
	{
		// For each object
		for (int i = 0; i < _node->objectsInside.Size(); i++)
		{
			// Compare the object
			if (_node->objectsInside[i].object == _object)
			{
				// Check if we should remove the object
				if (_remove)
				{
					_node->objectsInside.Remove(i);
				}

				return true;
			}
		}

		return false;
	}

	// Return the node quadrant that we should keep the search
	int NodeQuadrant(QuadtreeNode* _node, WVector2 _location)
	{
		if (_location.x >= _node->location.x + _node->size.x / 2.0)
		{
			// Quadrants 1 or 3
			if (_location.y >= _node->location.y + _node->size.y / 2.0)
			{
				// Quadrant 3
				return 3;
			}
			else
			{
				// Quadrant 1
				return 1;
			}
		}
		else
		{
			// Quadrants 0 or 2
			if (_location.y >= _node->location.y + _node->size.y / 2.0)
			{
				// Quadrant 2
				return 2;
			}
			else
			{
				// Quadrant 0
				return 0;
			}
		}
	}

	//////////
	// PICK //
	//////////

	// Pick all objects inside the circle range
	void PickAllObjectsInRange(QuadtreeNode* _node, unsigned int& _pickCounter, WVector2 _center, float _range)
	{
		// Check if this node is inside the range
		if (!RectangleIntersectsSphere(_node->location, _node->size, _center, _range))
		{
			return;
		}

		// Check if this node is a leaf
		if (!_node->leaf)
		{
			// Call the function for each child
			for (int i = 0; i < 4; i++)
			{
				// Call the function for this child
				PickAllObjectsInRange(_node->childs[i], _pickCounter, _center, _range);
			}

			return;
		}

		// For each object inside this leaf
		for (int i = 0; i < _node->objectsInside.Size(); i++)
		{
			// Get the distance from the object to the circle center
			float distance = Distance(_node->objectsInside[i].object->GetLocation(), _center);

			// Check we are inside the circle
			if (distance < _range)
			{
				// Pick this object
				m_PickArray[_pickCounter] = _node->objectsInside[i].object;

				// Increment the counter
				_pickCounter++;
			}
		}
	}

	// Pick all objects inside the circle range from the given class
	template <typename ClassType>
	void PickAllObjectsInRangeFromClass(QuadtreeNode* _node, unsigned int& _pickCounter, WVector2 _center, float _range)
	{
		// Check if this node is inside the range
		if (!RectangleIntersectsSphere(_node->location, _node->size, _center, _range))
		{
			return;
		}

		// Check if this node is a leaf
		if (!_node->leaf)
		{
			// Call the function for each child
			for (int i = 0; i < 4; i++)
			{
				// Call the function for this child
				PickAllObjectsInRangeFromClass<ClassType>(_node->childs[i], _pickCounter, _center, _range);
			}

			return;
		}

		// For each object inside this leaf
		for (int i = 0; i < _node->objectsInside.Size(); i++)
		{
			// Get the distance from the object to the circle center
			float distance = Distance(_node->objectsInside[i].object->GetLocation(), _center);

			// Check we are inside the circle
			if (distance < _range)
			{
				// Try to do a dynamic cast
				ClassType* object = dynamic_cast<ClassType*>(_node->objectsInside[i].object);

				// Check if the object is valid
				if (object != nullptr)
				{
					// Pick this object
					m_PickArray[_pickCounter] = _node->objectsInside[i].object;

					// Increment the counter
					_pickCounter++;
				}
			}
		}
	}

private:

	// The root node
	QuadtreeNode* m_RootNode;
	
	// The pick array
	ObjectType* m_PickArray[MaximumPickLenght];
};

#endif
