////////////////////////////////////////////////////////////////////////////////
// Filename: HoardResourceBase.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <atomic>
#include <vector>
#include <functional>

#include "..\NamespaceDefinitions.h"

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// Hoard Resource Module
NamespaceBegin(Hoard)

////////////////
// FORWARDING //
////////////////

class HoardResourceManager;

////////////////
// STRUCTURES //
////////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: HoardResourceBase
////////////////////////////////////////////////////////////////////////////////
class HoardResourceBase
{
private:

	// The HoardResourceManager is a friend
	friend HoardResourceManager;

public:

	// The resource status
	enum class ResourceStatus
	{
		Unknow,			// Error
		Created,		// When we first create this object
		Loading,		// If we are loading this resource
		Loaded,			// When we loaded this resource
		Initializing,	// When we are initializing this resource
		Initialized,	// When we initialized this resource
		Deleted			// The resource is pending deletion
	};

//////////////////
// CONSTRUCTORS //
protected: ///////

	// Constructor / destructor
	HoardResourceBase();
	~HoardResourceBase();

//////////////////
// MAIN METHODS //
public: //////////

	// Set the current status
	void SetStatus(ResourceStatus _status) { m_Status = _status; }

	// Get the current status
	ResourceStatus GetStatus() { return m_Status; }

protected:

	// Insert a wake callback
	void InsertWakeCallback(std::function<void()> _wakeMethod);

	// Process all wake callbacks
	void ProcessWakeCallbacks();

///////////////
// VARIABLES //
private: //////

	// The resource status
	ResourceStatus m_Status;

	// The wake callbacks
	std::vector<std::function<void()>> m_WakeCallbacks;

protected:

	// Useb by the resource manager to threat those resources like a list
	HoardResourceBase* next;
};

// Hoard Resource Module
NamespaceEnd(Hoard)