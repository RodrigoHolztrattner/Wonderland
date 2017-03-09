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
	// Consideramos que a fun��o j� est� validada //

	// Declara a string que usaremos
	std::string outputString;

	// Pega o id do componente de fun��o inicial
	unsigned int currentFunctionComponentId = _function->GetInitialFunctionComponentId();

	bool result = ProcessFunctionLink(_function, currentFunctionComponentId, outputString, 0);

	std::cout << outputString;

	return result;
}

bool FluxFunctionMaker::ProcessFunctionLink(FluxFunction* _fromFunction, unsigned int _functionId, std::string& _outputString, unsigned int _ident)
{
	// Pega o componente de fun��o proprio e verifica se ele � v�lido
	FluxFunctionBody::FunctionComponent* functionComponent = _fromFunction->FindFunctionComponent(_functionId);
	if (functionComponent == nullptr)
	{
		return false;
	}

	// Verificar aqui se a fun��o � do tipo texto??????????????????????????????????

	// Cria um novo assembly box para essa fun��o (como estamos seguindo linearmente, essa assembly box N�O deve existir)
	AssemblyBox* assemblyBox = CreateAssemblyBox(_fromFunction, functionComponent);
	if (assemblyBox == nullptr)
	{
		// Ops
		return false;
	}

	///////////////////////////////////////
	// DECLARA��O DAS VARI�VEIS DE SA�DA //
	///////////////////////////////////////
	/*
		- Aqui vamos fazer a declara��o (tipo + nome) de todas as vari�veis de sa�da que ser�o utilizadas pela chamada da fun��o.
		- Essas vari�veis (te�ricamente) ser�o preenchidas com o resultado da fun��o e ficam dispon�veis para serem utilizadas em outras chamadas.
	*/

	// Para cada vari�vel de entrada
	for (int i = 0; i < assemblyBox->outputVariables.size(); i++)
	{
		// Verifica se n�o � exec
		if (assemblyBox->outputVariables[i].variableIsExec)
		{
			// Ignore
			continue;
		}

		// Declara essa vari�vel
		WriteToString(assemblyBox->outputVariables[i].variableType + " " + assemblyBox->outputVariables[i].variableGeneratedName + ";\n", _outputString, _ident);
	}

	////////////////////////////////////
	// CHAMADA DA FUN��O E PAR�METROS //
	////////////////////////////////////
	/*
		- Aqui fazemos a escrita da chamada da fun��o e colocamos os par�metros de entrada na chamada da mesma.
		- Devemos cuidar o caso de precisar usar uma virgula na hora de separar os par�metros.
	*/

	// Faz a chamada para essa fun��o
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

		// Verifica qual � o tipo de link //

		// Execu��o
		if (inputLink.linkType == FluxFunctionBody::FunctionLinkType::Execution)
		{
			// Ignorar execu��es
			continue;
		}
		// Fun��o
		else if (inputLink.linkType == FluxFunctionBody::FunctionLinkType::Function)
		{
			// Procura qual fun��o estamos tentando localizar
			AssemblyBox* targetAssemblyBox = FindAssemblyBox(inputLink.fromComponentFunctionId);
			if (targetAssemblyBox == nullptr)
			{
				// Estamos usando um valor de sa�da de uma fun��o que ainda n�o esta aqui no nosso banco de dados,
				// como estamos seguindo um fluxo, quer sizer que essa vari�vel possui lixo e est� sendo usada
				// indevidamente, ou seja, problema!
				return false;
			}

			// Procura a vari�vel que estamos querendo
			AssemblyBoxOutputVariable* targetVariable = FindOutputVariable(targetAssemblyBox, inputLink.fromParameterId);
			if (targetVariable == nullptr)
			{
				// N�o achamos a vari�vel que queriamos, aqui temos um erro!
				return false;
			}

			// Ok, temos nossa vari�vel e o nome dela, podemos adicion�-la como par�metro //
			WriteToString(targetVariable->variableGeneratedName, _outputString, _ident, false);
		}
		// Vari�vel
		else
		{
			// Ok, vamos usar o nome original da vari�vel!
			WriteToString(inputLink.fromVariable.variableName, _outputString, _ident, false);
		}

		// Devemos usar virgula na proxima vez
		useComma = true;
	}

	// Para cada vari�vel de sa�da
	for (int i = 0; i < assemblyBox->outputVariables.size(); i++)
	{
		// Verifica se n�o � exec
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

		// Insere essa vari�vel
		WriteToString("&" + assemblyBox->outputVariables[i].variableGeneratedName, _outputString, _ident, false);

		// Devemos usar virgula na proxima vez
		useComma = true;
	}

	// Finaliza a chamada para essa fun��o
	WriteToString(");\n", _outputString, _ident, false);

	///////////////////////////////////////////
	// FINALIZA��O E CONTINUA��O DA EXECU��O //
	///////////////////////////////////////////
	/*
		- Finalizamos a chamada para a fun��o e agora vamos verificar se devemos continuar o path de execu��o.
	*/

	// Agora para cada saida de fluxo
	bool result;
	for (int i = 0; i < functionComponent->functionOutputs.size(); i++)
	{
		// Adiciona os preparativos (colchetes)
		WriteToString("{\n", _outputString, _ident);

		// Chama essa fun��o novamente
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

		DONE - Terminar a crian��o da fun��o CreateAssemblyBox() (logo acima)
		DONE - Fazer o teste com essa fun��o aqui (populando uma fun��o dummy)
		- Fazer a entrada de uma fun��o e a saida
		- Ajustar o json e excluir outros arquivos n�o necess�rios
		- Fazer a cria��o do header no assembler

*/