////////////////////////////////////////////////////////////////////////////////
// Filename: ReferenceCounter.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIDef.h"
#include <memory>
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

// HookGui workspace
NamespaceBegin(HookGui)

////////////////////////////////////////////////////////////////////////////////
// Class name: Reference
////////////////////////////////////////////////////////////////////////////////
template <typename HoldClass>
class Reference
{
//////////////////
// MAIN METHODS //
public: //////////

    // Constructor / destructor
    Reference()
    {
       // Hold a reference
        m_Object->HoldReference();
    }
    ~Reference()
    {
        // Release the reference
        m_Object->ReleaseReference();
    }

///////////////
// VARIABLES //
private: //////
    
    // The holder object
    HoldClass* m_Object;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: ReferenceCounter
////////////////////////////////////////////////////////////////////////////////
class ReferenceCounter
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	ReferenceCounter();
	~ReferenceCounter();

//////////////////
// MAIN METHODS //
public: //////////
    
    // The virtual destroy call
    virtual void DestroyWarning() = 0;
    
    // The caller wants to hold a reference
    void HoldReference();
    
    // The caller wants to release our reference
    void ReleaseReference();
    
    // Return the current number of references
    unsigned int GetTotalReferences();
    
///////////////
// VARIABLES //
private: //////
    
    // The number of references
    unsigned int m_TotalReferences;
    
};

// HookGui workspace
NamespaceEnd(HookGui)
