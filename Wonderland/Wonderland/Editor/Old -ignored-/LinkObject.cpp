////////////////////////////////////////////////////////////////////////////////
// Filename: LinkObject.cpp
////////////////////////////////////////////////////////////////////////////////
#include "LinkObject.h"
#include "FluxObject.h"

LinkObject::LinkObject(FluxObject* _fluxObject, VariableNameProvider* _fromVariableNameProvider)
{
	// Set the linked flux id and reference
	m_LinkedFluxObject = _fluxObject;

	// Clear all the input and output variables
	m_InputPlugs.Zero();
	m_OutputPlugs.Zero();

	// Set the input plugs
	for (int i = 0; i < _fluxObject->GetNumberInputPlugs(); i++)
	{
		// Create the object
		FluxPlugObject* temp = FluxPlugObject::CreateFromReference(_fluxObject->GetInputPlug(i));
		
		/*
			- Estamos criando a partir de uma referência, isso implica que se o tipo da variável for exec, NÃO estamos fazendo link,
			caso seja uma variável normal estamos ajustando o nome do objeto variável interno.
			- Em ambos os casos o nome do PlugObjet é ajustado de acordo com o especificado na FUNÇÃO!
			- No caso de uma variável normal, DEVEMOS ajustar o nome quando o link for realizado! (senão teriamos como entrada um nome
			que não necessariamente está em uso pois ele foi estipulado pela função, no caso como geramos nomes diferentes para as saidas
			este nome da função não existe e/ou não está em uso, precisamos referenciar o nome real de saida da função através da
			linkagem com outro link OU usar uma variável real externa.

			OBS: Não preciso ajustar caso seja um exec pois não faz sentido saber o link anterior de execução.
		*/
		
		// Add a the object
		m_InputPlugs.Add(temp);
	}

	// Set the output plugs
	for (int i = 0; i < _fluxObject->GetNumberOutputPlugs(); i++)
	{
		// Add the object
		FluxPlugObject* temp = FluxPlugObject::CreateFromReference(_fluxObject->GetOutputPlug(i), true, _fromVariableNameProvider->GetValidVariableName());
		
		/*
			- Estamos criando a partir de uma referência... Caso seja uma variável normal, estamos ajustando o seu nome com um nome
			válido através do gerador.
			- Caso seja um exec nós devemos ajustá-lo somente quando ele for linkado com outro objeto de link, ou seja, quando a função
			de adicionar input for chamado em um link que utiliza este objeto como chamador.
		*/

		// Add the plug to the array
		m_OutputPlugs.Add(temp);
	}
}

LinkObject::~LinkObject()
{
}

bool LinkObject::CompileLink(std::string* _compileString, LinkObject* _link, unsigned int _fromLinkInput)
{
	// Call the compile function for our linked object
	return m_LinkedFluxObject->CompileLink(_compileString, _link, _fromLinkInput);
}

bool LinkObject::ConnectPlugs(FluxPlugObject* _fromObject, LinkObject* _targetLink, unsigned int _usingIndex)
{
	// Check if it is a variable type
	if (_fromObject->IsFromType(FluxPlugObject::PlugType::Variable))
	{
		// Set the input plug reference
		return _targetLink->SetInputPlugReference(_usingIndex, _fromObject, _fromObject->GetVariableData()->GetName());
	}

	// Set the input plug reference
	return _targetLink->SetInputPlugReference(_usingIndex, _fromObject);
}

bool LinkObject::SetInputPlugReference(unsigned int _location, FluxPlugObject* _reference, std::string _variableName)
{
	// Check if we are inbounds
	if (_location < 0 || _location >= m_InputPlugs.Size())
	{
		return false;
	}

	// Check if the types are ok
	if (!_reference->IsFromType(m_InputPlugs[_location]->GetPlugType()))
	{
		return false;
	}

	// Check if we need to update the exec link
	if (_reference->IsFromType(FluxPlugObject::PlugType::ExecLink))
	{
		// Set the target exec link
		_reference->SetExecLinkData(this);
	}

	// Set the reference
	m_InputPlugs[_location] = _reference;

	return true;
}

bool LinkObject::SetOutputPlugReference(unsigned int _location, LinkObject* _fromLink, FluxPlugObject* _reference)
{
	// Disabilitado pois não faz sentido eu linkar uma variável de saída, assim estariamos fixando em apenas um uso
	// o que não corresponde ao esperado.
	// Unico caso que isso é possível é no exec, mas dai tratamos de outra forma... (ver o if em SetInputReference())

	/*
	// Check if we are inbounds
	if (_location < 0 || _location >= m_OutputPlugs.Size())
	{
		return false;
	}

	// Set the reference
	m_OutputPlugs[_location] = _reference;
	*/

	return true;
}

Array<FluxPlugObject*>* LinkObject::GetOutputPlugs()
{
	return &m_OutputPlugs;
}

Array<FluxPlugObject*>* LinkObject::GetInputPlugs()
{
	return &m_InputPlugs;
}

FluxPlugObject* LinkObject::GetInputPlugByIndex(unsigned int _index)
{
	return m_InputPlugs[_index];
}

FluxPlugObject* LinkObject::GetOutputPlugByIndex(unsigned int _index)
{
	return m_OutputPlugs[_index];
}