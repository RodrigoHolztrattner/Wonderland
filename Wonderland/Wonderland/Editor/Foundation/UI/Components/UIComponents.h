////////////////////////////////////////////////////////////////////////////////
// Filename: UIComponents.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

///////////
// FRAME //
///////////

// Base frame components and utils
#include "Frame\UIFrameComponent.h"
#include "Frame\UIRelativeFrameComponent.h"
#include "Frame\UIFrameToken.h"

// Anchor frame modifier
#include "Frame\Anchor\UIAnchorComponent.h"

// Text fit frame modifier
#include "Frame\Fit\UITextFitComponent.h"

/////////////
// COMMAND //
/////////////

// Base command types and utils
#include "Command\UICommandComponent.h"
#include "Command\UIMovableCommandComponent.h"
#include "Command\UICommandComponentCallback.h"

////////////////
// RENDERABLE //
////////////////

// Base renderable
#include "Renderable\UIRenderableComponent.h"
#include "Renderable\UIRenderableShader.h"

// Border renderable
#include "Renderable\Border\UIBorderComponent.h"
#include "Renderable\Border\UIBorderShader.h"

// Base color renderable
#include "Renderable\Color\UIColorComponent.h"
#include "Renderable\Color\UIColorShader.h"

// Base line renderable
#include "Renderable\Line\UILineComponent.h"
#include "Renderable\Line\UILineShader.h"

// Base text renderable, font type/data and utils
#include "Renderable\Text\UITextComponent.h"
#include "Renderable\Text\UIString.h"
#include "Renderable\Text\UIFont.h"
#include "Renderable\Text\UIFontShader.h"

// Base texture renderable
#include "Renderable\Texture\UITextureComponent.h"
#include "Renderable\Texture\UITextureShader.h"

///////////
// STATE //
///////////

// Base state component
#include "State\UIStateComponent.h"

//////////
// TREE //
//////////

// Base tree component
#include "Tree\UITreeComponent.h"