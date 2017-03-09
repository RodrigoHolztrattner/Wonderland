////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionMaker.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxFunctionMaker.h"
#include "FluxFunctionValidator.h"
#include "FluxFunctionRegister.h"
#include <iostream>

FluxFunctionMaker::FluxFunctionMaker()
{
    // Set the initial data
	// ...
}

FluxFunctionMaker::~FluxFunctionMaker()
{
}

bool FluxFunctionMaker::MakeFunction(FluxFunction* _function)
{
	// Consideramos que a função já está validada //

	// Declara a string que usaremos
	std::string outputString;

	// Pega o id do componente de função inicial
	unsigned int currentFunctionComponentId = _function->GetInitialFunctionComponentId();

	bool result = ProcessFunctionLink(_function, currentFunctionComponentId, outputString, 0);

	std::cout << outputString;

	return result;
}

bool FluxFunctionMaker::ProcessFunctionLink(FluxFunction* _fromFunction, unsigned int _functionId, std::string& _outputString, unsigned int _ident)
{
	// Pega o componente de função proprio e verifica se ele é válido
	FluxFunctionBody::FunctionComponent* functionComponent = _fromFunction->FindFunctionComponent(_functionId);
	if (functionComponent == nullptr)
	{
		return false;
	}

	// Verificar aqui se a função é do tipo texto??????????????????????????????????

	// Cria um novo assembly box para essa função (como estamos seguindo linearmente, essa assembly box NÃO deve existir)
	AssemblyBox* assemblyBox = CreateAssemblyBox(_fromFunction, functionComponent);
	if (assemblyBox == nullptr)
	{
		// Ops
		return false;
	}

	///////////////////////////////////////
	// DECLARAÇÃO DAS VARIÁVEIS DE SAÍDA //
	///////////////////////////////////////
	/*
		- Aqui vamos fazer a declaração (tipo + nome) de todas as variáveis de saída que serão utilizadas pela chamada da função.
		- Essas variáveis (teóricamente) serão preenchidas com o resultado da função e ficam disponíveis para serem utilizadas em outras chamadas.
	*/

	// Para cada variável de entrada
	for (int i = 0; i < assemblyBox->outputVariables.size(); i++)
	{
		// Verifica se não é exec
		if (assemblyBox->outputVariables[i].variableIsExec)
		{
			// Ignore
			continue;
		}

		// Declara essa variável
		WriteToString(assemblyBox->outputVariables[i].variableType + " " + assemblyBox->outputVariables[i].variableGeneratedName + ";\n", _outputString, _ident);
	}

	////////////////////////////////////
	// CHAMADA DA FUNÇÃO E PARÂMETROS //
	////////////////////////////////////
	/*
		- Aqui fazemos a escrita da chamada da função e colocamos os parâmetros de entrada na chamada da mesma.
		- Devemos cuidar o caso de precisar usar uma virgula na hora de separar os parâmetros.
	*/

	// Faz a chamada para essa função
	WriteToString(functionComponent->functionData.functionName + "(", _outputString, _ident);

	// Para cada link de entrada
	bool useComma = false;
	for (int i = 0; i < functionComponent->functionInputs.size(); i++)
	{
		// Pega o link
		FluxFunctionBody::FunctionLink inputLink = functionComponent->functionInputs[i];

		// Adiciona uma virgula se precisar
		if (useComma)
		{
			// Adiciona uma virgula
			WriteToString(" ", _outputString, _ident, false);
		}

		// Verifica qual é o tipo de link //

		// Execução
		if (inputLink.linkType == FluxFunctionBody::FunctionLinkType::Execution)
		{
			// Ignorar execuções
			continue;
		}
		// Função
		else if (inputLink.linkType == FluxFunctionBody::FunctionLinkType::Function)
		{
			// Procura qual função estamos tentando localizar
			AssemblyBox* targetAssemblyBox = FindAssemblyBox(inputLink.fromComponentFunctionId);
			if (targetAssemblyBox == nullptr)
			{
				// Estamos usando um valor de saída de uma função que ainda não esta aqui no nosso banco de dados,
				// como estamos seguindo um fluxo, quer sizer que essa variável possui lixo e está sendo usada
				// indevidamente, ou seja, problema!
				return false;
			}

			// Procura a variável que estamos querendo
			AssemblyBoxOutputVariable* targetVariable = FindOutputVariable(targetAssemblyBox, inputLink.fromParameterId);
			if (targetVariable == nullptr)
			{
				// Não achamos a variável que queriamos, aqui temos um erro!
				return false;
			}

			// Ok, temos nossa variável e o nome dela, podemos adicioná-la como parâmetro //
			WriteToString(targetVariable->variableGeneratedName, _outputString, _ident, false);
		}
		// Variável
		else
		{
			// Ok, vamos usar o nome original da variável!
			WriteToString(inputLink.fromVariable.variableName, _outputString, _ident, false);
		}

		// Devemos usar virgula na proxima vez
		useComma = true;
	}

	// Para cada variável de saída
	for (int i = 0; i < assemblyBox->outputVariables.size(); i++)
	{
		// Verifica se não é exec
		if (assemblyBox->outputVariables[i].variableIsExec)
		{
			// Ignore
			continue;
		}

		// Adiciona uma virgula se precisar
		if (useComma)
		{
			// Adiciona uma virgula
			WriteToString(", ", _outputString, _ident, false);
		}

		// Insere essa variável
		WriteToString("&" + assemblyBox->outputVariables[i].variableGeneratedName, _outputString, _ident, false);

		// Devemos usar virgula na proxima vez
		useComma = true;
	}

	// Finaliza a chamada para essa função
	WriteToString(");\n", _outputString, _ident, false);

	///////////////////////////////////////////
	// FINALIZAÇÃO E CONTINUAÇÃO DA EXECUÇÃO //
	///////////////////////////////////////////
	/*
		- Finalizamos a chamada para a função e agora vamos verificar se devemos continuar o path de execução.
	*/

	// Agora para cada saida de fluxo
	bool result;
	for (int i = 0; i < functionComponent->functionOutputs.size(); i++)
	{
		// Adiciona os preparativos (colchetes)
		WriteToString("{\n", _outputString, _ident);

		// Chama essa função novamente
		result = ProcessFunctionLink(_fromFunction, functionComponent->functionOutputs[i].toComponentFunctionId, _outputString, _ident + 4);
		if (!result)
		{
			return false;
		}

		// Finaliza os preparativos (colchetes)
		WriteToString("}\n", _outputString, _ident);
	}

	return true;
}



void FluxFunctionMaker::WriteToString(std::string _whatToWrite, std::string& _toString, unsigned int _ident, bool _souldIdent)
{
	// Ident
	if (_souldIdent)
	{
		for (int i = 0; i < _ident; i++)
		{
			_toString += " ";
		}
	}

	_toString += _whatToWrite;
}

/*
	To-do:

		DONE - Terminar a crianção da função CreateAssemblyBox() (logo acima)
		DONE - Fazer o teste com essa função aqui (populando uma função dummy)
		- Fazer a entrada de uma função e a saida
		- Ajustar o json e excluir outros arquivos não necessários
		- Fazer a criação do header no assembler

*/