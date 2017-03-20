////////////////////////////////////////////////////////////////////////////////
// Filename: VWShaderParameterHolder.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "..\..\NamespaceDefinitions.h"
#include "..\..\HashedString.h"

#include <map>
#include <string>
#include <glm/glm.hpp>

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

// Just another graphic wrapper
NamespaceBegin(VulkanWrapper)

////////////////
// FORWARDING //
////////////////

class VWContext;
class VWTexture;
class VWBuffer;

////////////////////////////////////////////////////////////////////////////////
// Class name: VWShaderParameterHolder
////////////////////////////////////////////////////////////////////////////////
class VWShaderParameterHolder
{ //TODO: Usar ponteiros para os dados que devem existir no proprio objeto e não armazenar como estamos fazendo
public:

	struct MaterialParameterAux
	{
		MaterialParameterAux() {}
		~MaterialParameterAux() {}

		std::string sParameterName;

		union
		{
			float scalar;
			glm::vec2 vector2;
			glm::vec3 vector3;
			glm::vec4 vector4;
			glm::mat2 matrix2;
			glm::mat3 matrix3;
			VWTexture* texture;
			VWBuffer* buffer;
		};
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	VWShaderParameterHolder();
	~VWShaderParameterHolder();

//////////////////
// MAIN METHODS //
protected: ///////

	// Set parameter value
	void SetScalarParameter(const char* _parameterName, float _scalarValue);
	void SetVector2Parameter(const char* _parameterName, glm::vec2& _vector);
	void SetVector3Parameter(const char* _parameterName, glm::vec3& _vector);
	void SetVector4Parameter(const char* _parameterName, glm::vec4& _vector);
	void SetMatrix2Parameter(const char* _parameterName, glm::mat2& _matrix);
	void SetMatrix3Parameter(const char* _parameterName, glm::mat3& _matrix);
	void SetTextureParameter(const char* _parameterName, VWTexture* _texture);
	void SetBufferParameter(const char* _parameterName, VWBuffer* _buffer);

public:

	// Get parameter value
	float GetScalarParameter(const char* _parameterName);
	glm::vec2 GetVector2Parameter(const char* _parameterName);
	glm::vec3 GetVector3Parameter(const char* _parameterName);
	glm::vec4 GetVector4Parameter(const char* _parameterName);
	glm::mat2 GetMatrix2Parameter(const char* _parameterName);
	glm::mat3 GetMatrix3Parameter(const char* _parameterName);
	VWTexture* GetTextureParameter(const char* _parameterName);
	VWBuffer* GetBufferParameter(const char* _parameterName);

private:

	// Find a material parameter inside our map using the parameter name
	MaterialParameterAux* FindMaterialParameter(const char* _parameterName);

///////////////
// VARIABLES //
private: //////

	// Our parameter map
	std::map<int64_t, MaterialParameterAux> m_ParameterMap;
};

// Just another graphic wrapper
NamespaceEnd(VulkanWrapper)