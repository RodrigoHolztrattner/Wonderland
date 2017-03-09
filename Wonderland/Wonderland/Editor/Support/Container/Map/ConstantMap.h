////////////////////////////////////////////////////////////////////////////////
// Filename: ConstantMap.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////

/////////////
// DEFINES //
/////////////

struct none { };

template<class T0 = none, typename... Args>
struct ConstantMap;

template <>
struct ConstantMap<none>
{
	void operator[](const int &) {};
	void operator<<(const int &) {};
};

template
<
	class T0, typename... Args
>
struct ConstantMap : public ConstantMap<Args...>
{
	typedef ConstantMap<Args...> base_type;

	// Register the operators
	using base_type::operator[];
	using base_type::operator<<;

	// Initial value is null
	typename T0* storage = nullptr;

	// The number of arguments
	typename int storageCount = sizeof...(Args)+1;

	// The original number of arguments
	typename int storageCountOriginal = sizeof...(Args)+1;

	// Get operator
	typename T0* operator[](T0 *c) // TROQUEI DE & POR *
	{
		return storage;
	}

	// Set operator
	typename T0** operator << (T0 *c)
	{
		return &storage;
	}

	// Reset
	typename void Reset()
	{
		storageCount = storageCountOriginal;
	}
};