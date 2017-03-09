////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionHeader.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include <vector>

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

/*
	- Aqui descreveremos um objeto função que pode representar uma certa quantidade de objetos criados pelo sistema e/ou
	por usuários.
	- Temos a seguinte estrutura de atributos:

		* Nome da função
		* ID / handle
		* Tipo (membro de classe, função stand-alone ou definida pelo sistema)
		* Qual classe faz parte	* Caso seja membro de uma classe
		* Tipo de retorno que é SEMPRE void
		* Parâmetros de entrada (garantidos que terão os nomes definidos)
		* Parâmetros de saída	(mudarão muito provavelmente de nome)
		* O tipo de criação do corpo da função (obrigatório set Text em caso de ser SystemDefine)
		* Indica o corpo da função caso ela seja do tipo texto

		=> Exemplos:

			a) 
				int AdicionaInt(int _a, int _b)
				{
					return _a + _b;
				}
		
				~Name 				= "AdicionaInt"
				~ID					= 28
				~Type				= StandAlone
				~ClassOwner			= None
				~ReturnType			= void
				~InputParameters	= {int _a, int _b}
				~OutputParameters	= {exec, int}
				~BodyCreation		= Chain
				~TextBody			= ""

			b) 
				if(bool _expression)
				{

				}
				else
				{
					
				}

				~Name				= "if"
				~ID					= 2
				~Type				= SystemDefine
				~ClassOwner			= None
				~ReturnType			= 
				~InputParameters	= {bool _expression}
				~OutputParameters	= {exec, exec}
				~BodyCreation		= Text
				~TextBody			= "if(" + InputParameter(0) + ")\n" + "{\n" + OutputParametes(0) + "\n}\nelse\n{\n}" + OutputParameters(1) + "\n}\n"

			c)
				for(int _var=0; _var<_expression; _var++)
				{

				}

				~Name				= "for"
				~ID					= 3
				~Type				= SystemDefine
				~ClassOwner			= None
				~ReturnType			= 
				~InputParameters	= {int _var, bool _expression}
				~OutputParameters	= {exec, exec}
				~BodyCreation		= Text
				~TextBody			= "for(int " + InputParameter(0) + "=0; " + InputParameter(0) " < " InputParameter(1) + "; " + InputParameter(0) + "++)\n{\n" + OutputParameters(0) + "\n}\n" + OutputParameters(1)

		=> Explicação:

			- Quando uma função é criada através de uma Chain, nós devemos criar as variáveis de saída e fazer a chamada para a 
			função, apenas isso (sempre o considerando se ela faz parte de uma classe ou não)
			- Quando uma função é definida pelo sistema, ela deve ter o seu corpo de texto copiado quando necessário e interpretado
			para a compilação.
			- Se a função é do tipo texto, não precisamos carregar o corpo dela e devemos apenas interpretar o seu "TextBody"
			quando a mesma for solicitada
*/

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxFunctionHeader
////////////////////////////////////////////////////////////////////////////////
class FluxFunctionHeader
{
/////////////
// DEFINES //
public: /////

	// We know the FluxFunctionBody class
	class FluxFunctionBody;
	friend FluxFunctionBody;

	// The function types
	enum class FunctionType
	{
		Member	= 0,
		Alone	= 1,
		System	= 2
	};

	// The function body creation type
	enum class FunctionBodyType
	{
		Chain	= 0,
		Text	= 1
	};

	// The function parameter type
	struct FunctionParameter
	{
		// O nome do parâmetro (será mostrado ao usuário na flux box MAS não será utilizado para parâmetros de saída pois
		// estes possuem nome dinâmico)
		std::string parameterName;

		// O tipo do parâmetro (em string)
		std::string parameterType;

		// O id do parâmetros
		unsigned int parameterId;
	};

	// The function definition
	struct FunctionHeader
	{
		// O nome da função
		std::string functionName;
		
		// O id da função
		unsigned int functionId;

		// Versão (é usado para verificar se está atualizada)
		unsigned int functionVersion;

		// O tipo de função (membro, alone ou system)
		FunctionType functionType;

		// O tipo de criação do corpo
		FunctionBodyType functionBodyType;

		// The current parameter id
		unsigned int currentParameterId;

		// A qual classe ela faz parte (nome da classe e apenas usada se ela é membro)
		std::string classOwner;

		// A quantidade de parâmetros de entrada e saida
		// unsigned int totalInputParameters;
		// unsigned int totalOutputParameters;

		// O corpo da função no tipo texto (apenas usável caso o tipo de corpo seja texto)
		// Usamos texto normal para descrever a função e quando desejamos fazer referência à uma variável, utilizamos
		// um @ seguido de um caractere "I" ou "O" para simbolizar se é input ou output seguido do index da variável
		// seguido por ultimo de outro @, ex: "if ( @I0@ ) \n { \n @O0@ \n } \n else \n { \n @O1@ \n } \n"
		std::string functionTextBody;

		// Os parâmetros de entrada
		std::vector<FunctionParameter> inputParameters;

		// Os parâmetros de saída
		std::vector<FunctionParameter> outputParameters;
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FluxFunctionHeader();
	~FluxFunctionHeader();

//////////////////
// MAIN METHODS //
protected: ///////

	// Create a new function header
	bool CreateNewHeader(std::string _functionName, FunctionType _functionType, FunctionBodyType _functionBodyType);

public:

	// Increment the current version
	void IncrementVersion();

	// Get <m_FunctionDefinition>
	std::string GetFunctionName();
	unsigned int GetFunctionId();
	unsigned int GetCurrentVersion();
	FunctionType GetFunctionType();
	FunctionBodyType GetFunctionBodyType();
	std::string GetFunctionClassOwner();
	unsigned int GetInputSize();
	unsigned int GetOutputSize();

	// Return a input/output parameter data
	FunctionParameter GetInputParameter(unsigned int _index);
	FunctionParameter GetOutputParameter(unsigned int _index);

////////////
// PARAMS //
////////////

	// Add an input/output param
	void AddInputParam(std::string _paramName, std::string _paramType);
	void AddOutputParam(std::string _paramName, std::string _paramType);

////////////////////
// INPUT / OUTPUT //
protected: /////////

	// Save the function header
	bool SaveFunctionHeader(std::string _fileName);

	// Load the function header
	bool LoadFunctionHeader(std::string _fileName);

///////////////
// VARIABLES //
protected: ////

	// The function definition
	FunctionHeader m_FunctionDefinition;
};