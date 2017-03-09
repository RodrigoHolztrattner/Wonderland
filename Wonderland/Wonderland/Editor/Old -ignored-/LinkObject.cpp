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
			- Estamos criando a partir de uma refer�ncia, isso implica que se o tipo da vari�vel for exec, N�O estamos fazendo link,
			caso seja uma vari�vel normal estamos ajustando o nome do objeto vari�vel interno.
			- Em ambos os casos o nome do PlugObjet � ajustado de acordo com o especificado na FUN��O!
			- No caso de uma vari�vel normal, DEVEMOS ajustar o nome quando o link for realizado! (sen�o teriamos como entrada um nome
			que n�o necessariamente est� em uso pois ele foi estipulado pela fun��o, no caso como geramos nomes diferentes para as saidas
			este nome da fun��o n�o existe e/ou n�o est� em uso, precisamos referenciar o nome real de saida da fun��o atrav�s da
			linkagem com outro link OU usar uma vari�vel real externa.

			OBS: N�o preciso ajustar caso seja um exec pois n�o faz sentido saber o link anterior de execu��o.
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
			- Estamos criando a partir de uma refer�ncia... Caso seja uma vari�vel normal, estamos ajustando o seu nome com um nome
			v�lido atrav�s do gerador.
			- Caso seja um exec n�s devemos ajust�-lo somente quando ele for linkado com outro objeto de link, ou seja, quando a fun��o
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
	// Disabilitado pois n�o faz sentido eu linkar uma vari�vel de sa�da, assim estariamos fixando em apenas um uso
	// o que n�o corresponde ao esperado.
	// Unico caso que isso � poss�vel � no exec, mas dai tratamos de outra forma... (ver o if em SetInputReference())

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