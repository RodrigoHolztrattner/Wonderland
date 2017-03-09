////////////////////////////////////////////////////////////////////////////////
// Filename: UIFont.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
// #include "..\View\View.h"
#include "..\..\..\..\Shader\ShaderFrame.h"
#include "..\..\..\..\Texture\Texture2D.h"

// FreeType Headers
#include <ft2build.h>
#include <freetype.h>
#include <ftglyph.h>
#include <ftoutln.h>
#include <fttrigon.h>

#include <vector>
#include <string>
#include <algorithm>

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// STRUCT //
////////////

////////////
// GLOBAL //
////////////

////////////////////////////////////////////////////////////////////////////////
// Class name: UIFont
////////////////////////////////////////////////////////////////////////////////
class UIFont
{
public:

	// The total number of glyphs
	static const unsigned int TotalGlyphs = 128;

	// The glyph type
	struct GlyphType
	{
		// The position and the size
		Vector2 position;
		Vector2 size;

		// The advance
		Vector2 advance;

		// The x offset
		float offset;

		// The texture coordinate
		Vector4 texCoordinates;
	};

public:
	UIFont();
	~UIFont();

	// Initialize this font
	bool Initialize(char* _fontName, unsigned int _h);

	// Return the glyph data
	GlyphType* GetGlyphData(char _ch)
	{
		return &m_Glyphs[_ch];
	}

	// Return the glyph frame
	ShaderFrame* GetGlyphFrame(char _ch)
	{
		return &m_GlyphFrame;
	}

	// Return the font texture
	Texture2D* GetTexture()
	{
		return &m_FontTexture;
	}

	// Return the font size
	unsigned int GetFontSize()
	{
		return m_FontSize;
	}

private:

	// Make all glyphs from the given face
	bool MakeAllGlyphs();

private:

	// The glyphs
	GlyphType m_Glyphs[TotalGlyphs];

	// Our face object
	FT_Face m_FaceObject;

	// The font texture
	Texture2D m_FontTexture;

	// The glyph frame
	ShaderFrame m_GlyphFrame;

	// The font size
	unsigned int m_FontSize;
};
