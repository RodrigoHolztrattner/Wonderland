////////////////////////////////////////////////////////////////////////////////
// Filename: UIFont.cpp
////////////////////////////////////////////////////////////////////////////////
#include "UIFont.h"

// This Function Gets The First Power Of 2 >= The
// Int That We Pass It.
inline int next_p2(int a)
{
	int rval = 1;
	// rval<<=1 Is A Prettier Way Of Writing rval*=2;
	while (rval<a) rval <<= 1;
	return rval;

}

UIFont::UIFont()
{
}

UIFont::~UIFont()
{
}

bool UIFont::Initialize(char* _fontName, unsigned int _h)
{
	// Initialize the FT_Library
	static bool FT_LibraryInitialized = false;
	static FT_Library ftlib;
	if (!FT_LibraryInitialized)
	{
		//
		if (FT_Init_FreeType(&ftlib))
		{
			throw std::runtime_error("FT_Init_FreeType failed");
		}

		// Set that we initialized
		FT_LibraryInitialized = true;
	}
	
	// Create the new face object
	if (FT_New_Face(ftlib, _fontName, 0, &m_FaceObject))
	{
		throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");
	}

	// Set the char size
	FT_Set_Char_Size(m_FaceObject, _h << 6, _h << 6, 96, 96);

	// Set the font size variable
	m_FontSize = _h;

	// Make all glyphs
	if (!MakeAllGlyphs())
	{
		return false;
	}

	// We Don't Need The Face Information Now That The Display
	// (m_FaceObject);

	// Ditto For The Font Library
	// FT_Done_FreeType(ftlib);

	return true;
}

bool UIFont::MakeAllGlyphs()
{
	// Compute the size for our bitmap texture
	FT_GlyphSlot g = m_FaceObject->glyph;
	int w = 0;
	int h = 0;

	// For each glyph
	for (int i = 0; i < 128; i++) 
	{
		if (FT_Load_Char(m_FaceObject, i, FT_LOAD_RENDER))
		{
			fprintf(stderr, "Loading character %c failed!\n", i);
			continue;
		}

		w += g->bitmap.width;
		h = std::max(h, (int)g->bitmap.rows);
	}

	/* you might as well save this value as it is needed later on */
	int atlas_width = w;

	// Create the font texture
	m_FontTexture.SetInternalGenerationData(GL_ALPHA, GL_ALPHA, GL_UNSIGNED_BYTE, 0);
	m_FontTexture.SetParameter(GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	m_FontTexture.SetParameter(GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	m_FontTexture.SetParameter(GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	m_FontTexture.SetParameter(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	m_FontTexture.PreCreateTexture();
	m_FontTexture.ApplyTextureParameters([]() -> void
	{
		// Set the pixel storage
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	});
	m_FontTexture.CreateTextureFromMemory(w, h, 0);
	m_FontTexture.ApplyTextureParameters(false);

	// Set the glyph texture data
	int x = 0;

	for (int i = 0; i < 128; i++) 
	{
		// Check if we are ok
		if (FT_Load_Char(m_FaceObject, i, FT_LOAD_RENDER))
			continue;

		// Set the sub image bitmap
		m_FontTexture.SetSubImage(x, 0, g->bitmap.width, g->bitmap.rows, g->bitmap.buffer);

		// Increment the current x position
		x += g->bitmap.width;

		// m_Glyphs[i].ax = g->advance.x >> 6;
		// m_Glyphs[i].ay = g->advance.y >> 6;
		m_Glyphs[i].advance.x = g->advance.x >> 6;
		m_Glyphs[i].advance.y = g->advance.y >> 6;

		// [i].bw = g->bitmap.width;
		// m_Glyphs[i].bh = g->bitmap.rows;
		m_Glyphs[i].size.x = g->bitmap.width;
		m_Glyphs[i].size.y = g->bitmap.rows;

		// m_Glyphs[i].bl = g->bitmap_left;
		// m_Glyphs[i].bt = g->bitmap_top;
		m_Glyphs[i].position.x = g->bitmap_left;
		m_Glyphs[i].position.y = g->bitmap_top;

		// m_Glyphs[i].tx = (float)x / w;
		m_Glyphs[i].offset = (float)x / w;

		// Set the texture coordinates
		m_Glyphs[i].texCoordinates.x = (float)x / w - (m_Glyphs[i].size.x / (float)w);
		m_Glyphs[i].texCoordinates.y = 0;
		m_Glyphs[i].texCoordinates.z = g->bitmap.width / (float)w;
		m_Glyphs[i].texCoordinates.w = g->bitmap.rows / (float)h;
	}

	// End the texture creation
	m_FontTexture.EndCreation();

	// Set the glyph vertices
	m_GlyphFrame.AddVertex(Vector3(0, 1, 0), Vector2(0, 0));
	m_GlyphFrame.AddVertex(Vector3(1, 1, 0), Vector2(1, 0));
	m_GlyphFrame.AddVertex(Vector3(0, 0, 0), Vector2(0, 1));
	m_GlyphFrame.AddVertex(Vector3(1, 0, 0), Vector2(1, 1));

	// Add the glyph indexes
	m_GlyphFrame.AddIndex(0);
	m_GlyphFrame.AddIndex(1);
	m_GlyphFrame.AddIndex(2);
	m_GlyphFrame.AddIndex(2);
	m_GlyphFrame.AddIndex(1);
	m_GlyphFrame.AddIndex(3);

	// Make the glyph frame object
	bool result = m_GlyphFrame.MakeFrame();
	GLenum error = glGetError();
	if (!result || error)
	{
		throw std::runtime_error("Criação do frame da fonte deu erro!");

		return false;
	}

	return true;
}