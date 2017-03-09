////////////////////////////////////////////////////////////////////////////////
// Filename: ResourceDefinitions.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <cstdint>
#include "Common\String\FHashedString.h"

///////////////
// NAMESPACE //
///////////////
namespace ResourceDefinitions
{
	/////////////
	// DEFINES //
	/////////////

	// The resource name size
	static const int ResourceNameSize = 32;

	// The resource header
	struct ResourceHeader
	{
		// Internal Info //

		// The resource hash Id
		FHashId hashId;

		// The resource complete name
		char resourceName[ResourceDefinitions::ResourceNameSize];

		// File Info //

		// The file ID where this resource is located
		int32_t fileId;

		// The file position where we can find the data
		int64_t filePosition;

		// The data original size
		int32_t dataOriginalSize;

		// The data compressed size
		int32_t dataCompressedSize;
	};

	// Create resource functor typedef
	// typedef Resource*(*CreateResourceFunctor)();

	////////////
	// GLOBAL //
	////////////
}
