////////////////////////////////////////////////////////////////////////////////
// Filename: FluxFunctionBody.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <string>
#include <vector>
#include "FluxFunctionHeader.h"
#include "..\Variable\FluxVariable.h"
#include "..\..\..\Support\Container\Array\Array.h"

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
	- Essa parte só existe no caso da nossa função não ser do tipo texto.
	- Aqui teremos as funções que utilizamos para definir a nossa (usando nomes, ids, etc)
	- Temos também a descrição de todas as ligações, as ligações devem ser confirmadas em tempo de carregamento

		* Não temos salvo os tipos das ligações para confirmar se elas são válidas, elas são confirmadas apenas no
		carregamento.
		* Uma conexão pode ser feita com um socket de outra função, pode vir de uma variável (tanto de classe quanto
		local, ambos os casos ela é indexada e localizada por nome)
		* Caso façamos uma alteração em outra função que é usada no corpo desta, se usamos esta função que foi alterada
		então existe uma dependência desta com aquela, então já que existe essa dependência, nós verificaremos na hora
		de compilar esta função e um chamado de verificação será feito, caso tenhamos alvo inválido o programa não
		será compilado e avisaremos o usuário que tem algum erro aqui dentro.

	- Devemos fazer um interpretador que cria a partir deste arquivo um objeto para ser compilado.
*/

////////////////////////////////////////////////////////////////////////////////
// Class name: FluxFunctionBody
////////////////////////////////////////////////////////////////////////////////
class FluxFunctionBody
{
/////////////
// DEFINES //
public: /////

	// FluxFunctionHeader is a friend class
	friend FluxFunctionHeader;

	// The function link type
	enum class FunctionLinkType
	{
		Function	= 0,
		Variable	= 1,
		Execution	= 2
	};

	// The variable origin type
	enum class VariableOriginType
	{
		Member		= 0,
		Local		= 1
	};

	// The variable component type
	struct VariableComponent
	{
		// O nome da variável
		std::string variableName;

		// O tipo de variável
		std::string variableType;

		// A origem da variável
		VariableOriginType variableOrigin;
	};

	// The function data
	struct FunctionData
	{
		// O nome da função
		std::string functionName;

		// O id da função
		unsigned int functionId;

		// A versão da função
		unsigned int functionVersion;
	};

	// A link type
	struct FunctionLink
	{
		// O tipo de link
		FunctionLinkType linkType;

		// Para qual entrada na função que é dona deste objeto o link esta designado
		unsigned int toParameterId;

		// Considerando que seja de uma outra função //

		// De qual função
		unsigned int fromComponentFunctionId; // Referente à uma função já armazenada aqui no body

		// De qual parâmetro na função de onde vem
		unsigned int fromParameterId; // Buscamos dados da variável no header

		// Considerando que seja de uma variável //

		// A variável de onde vem o link
		VariableComponent fromVariable;

		// Considerando que seja execução para uma outra função //

		// Para qual função
		unsigned int toComponentFunctionId;
	};

	// The function component type
	struct FunctionComponent
	{
		// O id de criação
		unsigned int creationId;

		// Informações de data da função para conseguir localizá-la, verificar se está atualizada, etc...
		FunctionData functionData;

		// Todas as entradas desta função (sem incluir componentes de execução)
		std::vector<FunctionLink> functionInputs;

		// Todas as saidas desta função do tipo execução (apenas desse tipo)
		std::vector<FunctionLink> functionOutputs;
	};

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	FluxFunctionBody(FluxFunctionHeader* _header);
	~FluxFunctionBody();

//////////////////
// MAIN METHODS //
protected: ///////

	// Create a new function body
	bool CreateNewBody();

public:

	// Cria um novo componete de função <retorna o ID de criação>
	unsigned int CreateNewFunctionComponent(FluxFunctionHeader* _functionHeader);

	// Cria um novo link
	bool CreateNewLink(unsigned int _fromFunctionComponentId, unsigned int _toFunctionComponentId, unsigned int _fromParameterId, unsigned int _toParameterId);
	bool CreateNewLink(FluxVariable* _fromVariable, unsigned int _toFunctionComponentId, unsigned int _toParameterId);

	// retornar ID da ligação? verificar aqui se a ligação é válida?
	// como fazer para remover uma ligação? devemos remover aqui simplesmente adicionando?
	// Devemos deixar para remover quando o sistema detectar que deve remover?
	// se removermos automaticamente, como avisar o sistema? não é melhor que o sistema nos avise?

	// Localiza um componente de função usando um creation id
	FunctionComponent* FindFunctionComponent(unsigned int _creationId);

	// Retorna o id do componente de função inicial e final
	unsigned int GetInitialFunctionComponentId() { return 0; }
	unsigned int GetFinalFunctionComponentId() { return 1; }

////////////////////
// INPUT / OUTPUT //
protected: /////////

	// Save the function body
	bool SaveFunctionBody(std::string _fileName);

	// Load the function body
	bool LoadFunctionBody(std::string _fileName);

///////////////
// VARIABLES //
protected: ////

	// A array com todas as funções componentes
	std::vector<FunctionComponent> m_ComponentFunctions;

	// A array com todos os links de saída
	std::vector<FunctionLink> m_OutputComponentLinks;

private:

	// Our header reference
	FluxFunctionHeader* m_HeaderReference;

	// Variável que controla o ID que estamos usando para criar componentes de função (lido do arquivo ou zero na criação)
	unsigned int m_CreationId;
};