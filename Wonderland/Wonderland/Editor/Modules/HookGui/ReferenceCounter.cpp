////////////////////////////////////////////////////////////////////////////////
// Filename: FluxReferenceCounter.cpp
////////////////////////////////////////////////////////////////////////////////
#include "ReferenceCounter.h"

HookGui::ReferenceCounter::ReferenceCounter()
{
	// Set the initial data
    m_TotalReferences = 0;
}

HookGui::ReferenceCounter::~ReferenceCounter()
{
}

void HookGui::ReferenceCounter::HoldReference()
{
    // Increment the total references
    m_TotalReferences++;
}

void HookGui::ReferenceCounter::ReleaseReference()
{
    // Decrement the total references
    m_TotalReferences--;
    
    // Check if we have any reference
    if(m_TotalReferences <= 0)
    {
        // Destroy warning signal
        DestroyWarning();
    }
    
    // Delete this
    // delete this;
}

unsigned int HookGui::ReferenceCounter::GetTotalReferences()
{
    return m_TotalReferences;
}
