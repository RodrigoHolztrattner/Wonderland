////////////////////////////////////////////////////////////////////////////////
// Filename: HookGui.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "HGWidget.h"
#include "HGWidgetManager.h"
#include "HGInputDispatcher.h"
#include "HGInputController.h"
#include "HGAnchor.h"
#include "HGImage.h"
#include "Widget\HGFrame.h"
#include "Widget\HGFrameComponent.h"
#include "Shaders\HGWidgetShader.h"

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

/////////////
// DEFINES //
/////////////

// Core
typedef HGWidget						Widget;
typedef HGWidgetManager					WidgetManager;
typedef HGInputDispatcher				InputDispatcher;
typedef HGInputController				InputController;
typedef HGAnchor						Anchor;
typedef HGImage							Image;
typedef HGFrame							Frame;
typedef HGFrameComponent				FrameComponent;
typedef HGWidgetShader					WidgetShader;

// HookGui workspace
NamespaceEnd(HookGui)
