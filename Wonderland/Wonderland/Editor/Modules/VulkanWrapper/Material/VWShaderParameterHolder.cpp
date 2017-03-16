////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWShaderParameterHolder.h"
#include "..\Resource\Texture\VWTexture.h"
#include "..\VWBuffer.h"

VulkanWrapper::VWShaderParameterHolder::VWShaderParameterHolder()
{
	// Set the initial data
	m_TextureIdentificator = 0;
}

VulkanWrapper::VWShaderParameterHolder::~VWShaderParameterHolder()
{
}

void VulkanWrapper::VWShaderParameterHolder::SetScalarParameter(const char* _parameterName, float _scalarValue)
{
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.scalar = _scalarValue;
}
void VulkanWrapper::VWShaderParameterHolder::SetVector2Parameter(const char* _parameterName, glm::vec2& _vector)
{
	
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.vector2 = _vector;
}
void VulkanWrapper::VWShaderParameterHolder::SetVector3Parameter(const char* _parameterName, glm::vec3& _vector)
{
	
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.vector3 = _vector;
}
void VulkanWrapper::VWShaderParameterHolder::SetVector4Parameter(const char* _parameterName, glm::vec4& _vector)
{
	
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.vector4 = _vector;
}
void VulkanWrapper::VWShaderParameterHolder::SetMatrix2Parameter(const char* _parameterName, glm::mat2& _matrix)
{
	
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.matrix2 = _matrix;
}
void VulkanWrapper::VWShaderParameterHolder::SetMatrix3Parameter(const char* _parameterName, glm::mat3& _matrix)
{
	
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.matrix3 = _matrix;
}

void VulkanWrapper::VWShaderParameterHolder::SetTextureParameter(const char* _parameterName, VulkanWrapper::VWTexture* _texture)
{
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.texture = _texture;

	// Update the texture identificator
	// m_TextureIdentificator += (_texture->GetId() + 1) * (_texture->GetId() + 2) * _texture->GetId();
}

void VulkanWrapper::VWShaderParameterHolder::SetBufferParameter(const char* _parameterName, VulkanWrapper::VWBuffer* _buffer)
{
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.buffer = _buffer;
}

float VulkanWrapper::VWShaderParameterHolder::GetScalarParameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return 0.0f;
	}

	return parameter->scalar;
}

glm::vec2 VulkanWrapper::VWShaderParameterHolder::GetVector2Parameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return glm::vec2();
	}

	return parameter->vector2;
}

glm::vec3 VulkanWrapper::VWShaderParameterHolder::GetVector3Parameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return glm::vec3();
	}

	return parameter->vector3;
}

glm::vec4 VulkanWrapper::VWShaderParameterHolder::GetVector4Parameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return glm::vec4();
	}

	return parameter->vector4;
}

glm::mat2 VulkanWrapper::VWShaderParameterHolder::GetMatrix2Parameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return glm::mat2();
	}

	return parameter->matrix2;
}
glm::mat3 VulkanWrapper::VWShaderParameterHolder::GetMatrix3Parameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return glm::mat3();
	}

	return parameter->matrix3;
}

VulkanWrapper::VWTexture* VulkanWrapper::VWShaderParameterHolder::GetTextureParameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return nullptr;
	}

	return parameter->texture;
}

VulkanWrapper::VWBuffer* VulkanWrapper::VWShaderParameterHolder::GetBufferParameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return nullptr;
	}

	return parameter->buffer;
}

VulkanWrapper::VWShaderParameterHolder::MaterialParameterAux* VulkanWrapper::VWShaderParameterHolder::FindMaterialParameter(const char* _parameterName)
{
	
	if (m_ParameterMap.find(SimpleHash(_parameterName)) != m_ParameterMap.end())
	{
		return &m_ParameterMap[SimpleHash(_parameterName)];
	}
	
	return nullptr;
}