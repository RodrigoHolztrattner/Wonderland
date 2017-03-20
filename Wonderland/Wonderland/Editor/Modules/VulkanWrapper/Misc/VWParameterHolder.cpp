////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWParameterHolder.h"
#include "..\Resource\Texture\VWTexture.h"
#include "..\Resource\VWBuffer.h"

VulkanWrapper::VWParameterHolder::VWParameterHolder()
{
	// Set the initial data
	// ...
}

VulkanWrapper::VWParameterHolder::~VWParameterHolder()
{
}

void VulkanWrapper::VWParameterHolder::SetScalarParameter(const char* _parameterName, float _scalarValue)
{
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.scalar = _scalarValue;
}
void VulkanWrapper::VWParameterHolder::SetVector2Parameter(const char* _parameterName, glm::vec2& _vector)
{
	
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.vector2 = _vector;
}
void VulkanWrapper::VWParameterHolder::SetVector3Parameter(const char* _parameterName, glm::vec3& _vector)
{
	
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.vector3 = _vector;
}
void VulkanWrapper::VWParameterHolder::SetVector4Parameter(const char* _parameterName, glm::vec4& _vector)
{
	
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.vector4 = _vector;
}
void VulkanWrapper::VWParameterHolder::SetMatrix2Parameter(const char* _parameterName, glm::mat2& _matrix)
{
	
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.matrix2 = _matrix;
}
void VulkanWrapper::VWParameterHolder::SetMatrix3Parameter(const char* _parameterName, glm::mat3& _matrix)
{
	
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.matrix3 = _matrix;
}

void VulkanWrapper::VWParameterHolder::SetTextureParameter(const char* _parameterName, VulkanWrapper::VWTexture* _texture)
{
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.texture = _texture;
}

void VulkanWrapper::VWParameterHolder::SetBufferParameter(const char* _parameterName, VulkanWrapper::VWBuffer* _buffer)
{
	MaterialParameterAux& newParameter = m_ParameterMap[SimpleHash(_parameterName)];
	newParameter.sParameterName = _parameterName;
	newParameter.buffer = _buffer;
}

float VulkanWrapper::VWParameterHolder::GetScalarParameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return 0.0f;
	}

	return parameter->scalar;
}

glm::vec2 VulkanWrapper::VWParameterHolder::GetVector2Parameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return glm::vec2();
	}

	return parameter->vector2;
}

glm::vec3 VulkanWrapper::VWParameterHolder::GetVector3Parameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return glm::vec3();
	}

	return parameter->vector3;
}

glm::vec4 VulkanWrapper::VWParameterHolder::GetVector4Parameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return glm::vec4();
	}

	return parameter->vector4;
}

glm::mat2 VulkanWrapper::VWParameterHolder::GetMatrix2Parameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return glm::mat2();
	}

	return parameter->matrix2;
}
glm::mat3 VulkanWrapper::VWParameterHolder::GetMatrix3Parameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return glm::mat3();
	}

	return parameter->matrix3;
}

VulkanWrapper::VWTexture* VulkanWrapper::VWParameterHolder::GetTextureParameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return nullptr;
	}

	return parameter->texture;
}

VulkanWrapper::VWBuffer* VulkanWrapper::VWParameterHolder::GetBufferParameter(const char* _parameterName)
{
	MaterialParameterAux* parameter = FindMaterialParameter(_parameterName);
	if (parameter == nullptr)
	{
		return nullptr;
	}

	return parameter->buffer;
}

VulkanWrapper::VWParameterHolder::MaterialParameterAux* VulkanWrapper::VWParameterHolder::FindMaterialParameter(const char* _parameterName)
{
	
	if (m_ParameterMap.find(SimpleHash(_parameterName)) != m_ParameterMap.end())
	{
		return &m_ParameterMap[SimpleHash(_parameterName)];
	}
	
	return nullptr;
}