////////////////////////////////////////////////////////////////////////////////
// Filename: HashedString.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include <cstdint>

/////////////
// DEFINES //
/////////////

/*

	=> Pre-processor constant hashed strings only are created if those flags..:

		- C/C++ > Optimization > Full Optimization
		- C/C++ > Code Generation > Enable String Pooling

	are set to true... So, if you wanna use this, remember to change the project properties.

*/

uint32_t constexpr SimpleHash(char const *input)
{
	return *input ?
		static_cast<uint32_t>(*input) + 33 * SimpleHash(input + 1) :
		5381;
}

// The hash id
typedef int64_t FHashId;

////////////////////////////////////////////////////////////////////////////////
// Class name: HashedString
////////////////////////////////////////////////////////////////////////////////
class HashedString
{
public:

	// Used to return the hash component
	class Hasher
	{
		friend HashedString;

	public:
		FHashId operator()(const HashedString & _hashedString) const
		{
			return _hashedString.m_Hash;
		}
	};

	// Compare 2 hashed strings
	class Equal
	{
		friend HashedString;

	public:
		bool operator() (HashedString const& t1, HashedString const& t2) const
		{
			return (t1.m_Hash == t2.m_Hash);
		}
	};

private:
	
	// Just a constant wrapper
	struct ConstCharWrapper
	{
		inline ConstCharWrapper(const char* str);
		const char* str;
	};



public:

	// A wrapper so we can generate any number of functions using the pre-processor (const strings)
	inline explicit HashedString(const char* _string)
	{
	
	}

	// Return the original string
	const char* String()
	{
		return m_String;
	}

	// Return the hash
	FHashId Hash()
	{
		return m_Hash;
	}

public:

	// The hash object (pre-calculated if we use the full optimization flag)
	FHashId m_Hash;

	// The original string
	const char* m_String;
};