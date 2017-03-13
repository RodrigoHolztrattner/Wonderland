////////////////////////////////////////////////////////////////////////////////
// Filename: Socket.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////

//TODO: Remover dos modulos pois esta lib não faz parte dos modulos reais da "engine", posso colocá-la numa parte para modulos externos mas aqui não!

// Namespace
#include "..\NamespaceDefinitions.h"

// Handle
#include "Handle\Handle.h"

// Type
#include "Type\Type.h"
#include "Type\TypeCreator.h"
#include "Type\TypeRegister.h"

// Socket
#include "Socket\Socket.h"
#include "Socket\SocketExecution.h"
#include "Socket\SocketType.h"

// Box / Function
#include "Box\Box.h"
#include "Box\BoxCreator.h"
#include "Box\BoxRegister.h"
#include "Box\Function\DynamicFunction\DynamicFunction.h"
#include "Box\Function\DynamicFunction\DynamicFunctionCreator.h"
#include "Box\Function\DynamicFunction\DynamicFunctionRegister.h"
#include "Box\Function\DynamicMemberFunction\DynamicMemberFunction.h"
#include "Box\Function\DynamicMemberFunction\DynamicMemberFunctionCreator.h"
#include "Box\Function\DynamicMemberFunction\DynamicMemberFunctionRegister.h"

// Class
#include "Class\Class.h"
#include "Class\ClassCreator.h"
#include "Class\ClassRegister.h"

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// Flux workspace
NamespaceBegin(Flux)

// Flux workspace
NamespaceEnd(Flux)
