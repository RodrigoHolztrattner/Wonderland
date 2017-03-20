////////////////////////////////////////////////////////////////////////////////
// Filename: PacketLoader.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\NamespaceDefinitions.h"

#include "HoardResource.h"
#include "HoardResourceCache.h"
#include "HoardResourceLoader.h"
#include "HoardResourceManager.h"
#include "HoardResourceRequest.h"
#include "HoardResourceVault.h"

#include "Supply\HoardSupplyIndex.h"
#include "Supply\HoardSupplyIndexLoader.h"
#include "Supply\HoardSupplyManager.h"
#include "Supply\HoardSupplyObject.h"
#include "Supply\HoardSupplyRequest.h"
#include "Supply\HoardSupplyVault.h"

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

//////////////////
// DEPENDENCIES //
//////////////////

// Peon lib initialized inside a singleton variable
// Packet lib initialized inside a singleton variable

//////////////
// TYPEDEFS //
//////////////

// Hoard Resource Module
NamespaceBegin(Hoard)

	typedef HoardResource					Resource;
	typedef HoardResourceManager			ResourceManager;
	typedef HoardResourceRequest			ResourceRequest;

	// Hoard Resource Supply Module
	NamespaceBegin(Supply)

		typedef HoardSupplyIndex				Index;
		typedef HoardSupplyObject				Object;
		// typedef HoardSupplyIndexLoader		IndexLoader;
		// typedef HoardSupplyManager			Manager;

		template<typename ObjectType, typename IndexType>
		using Manager = HoardSupplyManager<ObjectType, IndexType>;

		template<typename ObjectType>
		using IndexLoader = HoardSupplyIndexLoader<ObjectType>;

	// Hoard Resource Supply Module
	NamespaceEnd(Supply)

// Hoard Resource Module
NamespaceEnd(Hoard)