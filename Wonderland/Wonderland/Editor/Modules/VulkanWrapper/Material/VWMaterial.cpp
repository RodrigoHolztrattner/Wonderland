////////////////////////////////////////////////////////////////////////////////
// Filename: FluxMyWrapper.cpp
////////////////////////////////////////////////////////////////////////////////
#include "VWMaterial.h"
#include "..\Core\VWGraphicAdapter.h"
#include "..\Core\VWSwapChain.h"
#include "..\Core\VWGraphicInstance.h"
#include "..\Context\VWContext.h"
#include "VWObject.h"

VulkanWrapper::VWMaterial::VWMaterial()
{
	// Set the initial data
	m_Initialized = false;
}

VulkanWrapper::VWMaterial::~VWMaterial()
{
}

/*
	- Um material vai ter a função de um shader agora, usaremos a seguinte ideia:

		Temos vários objetos que serão renderizados com um certo material, cada objeto tem texturas de entrada e estes são agrupados por estas texturas e enviados
		para o material que funcionará como um shader e fará a renderização.

		Temos um descriptorSet para cada CONJUNTO de texturas usados por esses objetos, o set layout é o molde do material apenas.

		Quando carregamos um objeto a gente pega a listagem de texturas (e usando um hashcode) verificamos se esta mesma listagem já existe e já foi criado um
		descriptorSet, caso positivo, pegamos a referencia, caso contrário, criamos um!

	- Temos que ter uma forma de linkar no object uma textura ou valores para serem passados para um uniform buffer, creio que criar funções pre-definidas seja
	a melhor forma

	- Precisamos verificar se usamos parametros externos, em caso afirmativo nós não podemos renderizar (a principio) usando instancing porque dependemos de pegar
	os valores individualmente de cada objeto (até da pra instanciar sim) mas caso não tenhamos essa dependência, então temos texturas pre-definidas e valores de
	uniform buffer que são constantes para todos os objetos, facilitando assim a renderização por instanciamento.
*/

bool VulkanWrapper::VWMaterial::Initialize(VWContext* _graphicContext)
{
	// Add our layout descriptors
	AddDescriptorSetLayoutBinding(0,	VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,			"ubo",		1,	VK_SHADER_STAGE_VERTEX_BIT);
	AddDescriptorSetLayoutBinding(1,	VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,	"texture",	1,	VK_SHADER_STAGE_FRAGMENT_BIT);

	// Create the descriptor pool
	CreateDescriptorPool(_graphicContext, 100);

	// Create the set layout
	CreateDescriptorSetLayout(_graphicContext);

	return true;
}

void VulkanWrapper::VWMaterial::CreateDescriptorPool(VWContext* _graphicContext, uint32_t _maxSets)
{
	std::vector<VkDescriptorPoolSize> poolSizes;
	for (auto layoutBinding : m_DescriptorSetLayoutBindings)
	{
		VkDescriptorPoolSize poolSize = {};
		poolSize.type = layoutBinding.sDescriptorBindingInfo.descriptorType;
		poolSize.descriptorCount = layoutBinding.sDescriptorBindingInfo.descriptorCount;

		poolSizes.push_back(poolSize);
	}

	VkDescriptorPoolCreateInfo poolInfo = {};
	poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	poolInfo.poolSizeCount = poolSizes.size();
	poolInfo.pPoolSizes = poolSizes.data();
	poolInfo.maxSets = _maxSets;
	
	if (vkCreateDescriptorPool(_graphicContext->GetGraphicInstance()->GetDevice(), &poolInfo, nullptr, &m_DescriptorPool) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to create descriptor pool!");
	}
}


void VulkanWrapper::VWMaterial::AddDescriptorSetLayoutBinding(uint32_t _binding, VkDescriptorType _type, std::string _bindingName, uint32_t _count, VkShaderStageFlags _flags, const VkSampler* _immutableSamplers)
{
	DescriptorLayoutBindingAux bindingAux = {};

	bindingAux.sDescriptorBindingInfo = {};
	bindingAux.sDescriptorBindingInfo.binding = _binding;
	bindingAux.sDescriptorBindingInfo.descriptorType = _type;
	bindingAux.sDescriptorBindingInfo.descriptorCount = _count;
	bindingAux.sDescriptorBindingInfo.stageFlags = _flags;
	bindingAux.sDescriptorBindingInfo.pImmutableSamplers = _immutableSamplers;

	bindingAux.sBindingName = _bindingName;

	m_DescriptorSetLayoutBindings.push_back(bindingAux);
}

void VulkanWrapper::VWMaterial::CreateDescriptorSetLayout(VWContext* _graphicContext, VkDescriptorSetLayoutCreateFlags _flags)
{
	std::vector<VkDescriptorSetLayoutBinding> layoutBindings;
	for (auto layoutBinding : m_DescriptorSetLayoutBindings)
	{
		layoutBindings.push_back(layoutBinding.sDescriptorBindingInfo);
	}

	VkDescriptorSetLayoutCreateInfo layoutInfo = {};
	layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	layoutInfo.bindingCount = layoutBindings.size();
	layoutInfo.pBindings = layoutBindings.data();
	layoutInfo.flags = _flags;
	
	if (vkCreateDescriptorSetLayout(_graphicContext->GetGraphicInstance()->GetDevice(), &layoutInfo, nullptr, &m_DescriptorSetLayout) != VK_SUCCESS) {
		throw std::runtime_error("failed to create descriptor set layout!");
	}
}

VkDescriptorSet VulkanWrapper::VWMaterial::GenerateDescriptorSet(VWContext* _context)
{
	VkDescriptorSet descriptorSet = {};
	VkDescriptorSetAllocateInfo allocInfo = {};
	allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	allocInfo.descriptorPool = m_DescriptorPool;
	allocInfo.descriptorSetCount = 1;
	allocInfo.pSetLayouts = &m_DescriptorSetLayout;

	if (vkAllocateDescriptorSets(_context->GetGraphicInstance()->GetDevice(), &allocInfo, &descriptorSet) != VK_SUCCESS)
	{
		throw std::runtime_error("failed to allocate descriptor set!");
	}

	return descriptorSet;
}


void VulkanWrapper::VWMaterial::FindBindingsForDescriptorSet(VWContext* _graphicContext, VkDescriptorSet _descriptorSet, VWObject* _object)
{
	std::vector<VkWriteDescriptorSet> descriptorWrites = {};
	for (auto layoutBinding : m_DescriptorSetLayoutBindings)
	{
		VkWriteDescriptorSet descriptorWrite = {};

		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = _descriptorSet;
		descriptorWrite.dstBinding = layoutBinding.sDescriptorBindingInfo.binding;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrite.descriptorCount = 1;

		// Uniform buffer
		if (layoutBinding.sDescriptorBindingInfo.descriptorType == VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER)
		{
			VkDescriptorBufferInfo bufferInfo = {};
			//bufferInfo.buffer = m_UniformBuffer.GetRawBuffer();
			bufferInfo.offset = 0;
			//bufferInfo.range = sizeof(UniformBufferObject);

			descriptorWrite.pBufferInfo = &bufferInfo;
		}
		// Combined image sampler
		else if (layoutBinding.sDescriptorBindingInfo.descriptorType == VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER)
		{
			VkDescriptorImageInfo imageInfo = {};
			imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
			//imageInfo.imageView = _renderable->GetImage()->GetImageView();
			//imageInfo.sampler = _renderable->GetImage()->GetSampler();

			descriptorWrite.pImageInfo = &imageInfo;
		}

		descriptorWrites.push_back(descriptorWrite);
	}

	vkUpdateDescriptorSets(_graphicContext->GetGraphicInstance()->GetDevice(), descriptorWrites.size(), descriptorWrites.data(), 0, nullptr);
}

/*
- Suponto que cada shader tenha um set layout, vamos então pensar que cada "material" tem um descriptor set
- Podemos enviar mais de 1 descriptor set dentro do command buffer, logo, podemos ter um dedicado totalmente para
o material (já que precisamos usar o descriptor pool que limita o tipo de envio para a pipeline)

-> Precisamos separar em 2 descriptor sets (uniform buffer e textura) para ver se é ok enviar + de 1 set
*/



void VulkanWrapper::VWMaterial::Release()
{

}

bool VulkanWrapper::VWMaterial::IsRead()
{
	return m_Initialized;
}