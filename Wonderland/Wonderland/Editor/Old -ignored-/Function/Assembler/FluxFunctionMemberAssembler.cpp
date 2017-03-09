﻿////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionMemberAssembler.cpp
////////////////////////////////////////////////////////////////////////////////
#include "FluxFunctionMemberAssembler.h"

FluxFunctionMemberAssembler::FluxFunctionMemberAssembler()
{
    // Set the initial data
	// ...
}

FluxFunctionMemberAssembler::~FluxFunctionMemberAssembler()
{
}

bool FluxFunctionMemberAssembler::BuildProcess()
{
	/*
	
	// Get the input/output variables
	Array<FluxPlugObject*>& inputVariables = *_link->GetInputPlugs();
	Array<FluxPlugObject*>& outputVariables = *_link->GetOutputPlugs();

	
	// Primeira coisa, usaremos os valores de entrada para a função exatamente como indicados MAS
	// os valores de saída não serão colocados como uma struct no retorno e sim também passados como
	// parâmetros (mas por referência), então devemos aqui declarar as variáveis que serão passadas
	// por referencia!
	
	
	// Para cada variavel de saida
	for (int i = 0; i < outputVariables.Size(); i++)
	{
		// Check if it's a variable
		if (!outputVariables[i]->IsFromType(FluxPlugObject::PlugType::Variable))
		{
			continue;
		}

		// Devemos declarar o tipo de variável e logo em seguida o nome da variável (sem inicialização)
		*_compileString += outputVariables[i]->GetVariableData()->GetType().GetName() + " " + outputVariables[i]->GetPlugName() + ";\n";
	}

	
	// Temos todas as variáveis de saida declaradas, agora podemos iniciar a chamada para a função, lembrando
	// que não precisamos guardar o valor de retorno, a função criada deverá ser do tipo void!

	// Aqui adicionamos o nome da funcao atual + entrada das variáveis
	*_compileString += m_FunctionName + "(";

	
	// Prosseguiremos para a declaração dos parâmetros, aqui usaremos primeiramente os valores de entrada e depois
	// os de saída que serão passados por referencia.
	// Usaremos um indicador booleano para assegurar que temos pelo menos um parâmetro escrito e caso tenhamos que
	// escrever outro(s), devemos separa-los por virgula
	bool haveParameter = false;

	// Para cada variavel de entrada
	for (int i = 0; i < inputVariables.Size(); i++)
	{
		// Check if it's a variable
		if (!inputVariables[i]->IsFromType(FluxPlugObject::PlugType::Variable))
		{
			// Ignorar "exec"
			continue;
		}

		// Verifica se precisamos de virgula
		if (haveParameter)
		{
			*_compileString += ", ";
		}

		// Escreve o nome da vari�vel
		*_compileString += inputVariables[i]->GetVariableData()->GetName();

		// Indica que já existem parametros (controlador de virgula)
		haveParameter = true;;
	}

	
	// Agora iremos escrever escrever os parametros de saida, aqui passaremos eles por referencia
	// Nota que mantemos nosso veficiador de virgula como está!

	// Para cada variavel de saida
	for (int i = 0; i < outputVariables.Size(); i++)
	{
		// Check if it's a variable
		if (!outputVariables[i]->IsFromType(FluxPlugObject::PlugType::Variable))
		{
			// Ignorar "exec"
			continue;
		}

		// Verifica se precisamos de virgula
		if (haveParameter)
		{
			*_compileString += ", ";
		}

		// Escreve o nome da vari�vel
		*_compileString += "&" + outputVariables[i]->GetPlugName();

		// Indica que já existem parametros (controlador de virgula)
		haveParameter = true;
	}

	// Aqui finalizamos a chamada!
	*_compileString += ");\n";

	// Verificamos se existe algum "exec" na saida e chamamos ele para continuar a compilar 
	for (int i = 0; i < outputVariables.Size(); i++)
	{
		// Check if is different from the exec
		if (outputVariables[i]->IsFromType(FluxPlugObject::PlugType::ExecLink))
		{
			// Chamamos a execu��o do pr�ximo link ligado � esta vari�vel do tipo "exec"
			return outputVariables[i]->GetExecLink()->CompileLink(_compileString, outputVariables[i]->GetExecLink(), i);
		}
	}

	return true;
	
	*/

	return true;
}