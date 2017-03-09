// Wonderland.cpp : Defines the entry point for the console application.
//

#define GLFW_INCLUDE_VULKAN

#include <pthread.h>
// #include "SystemClass.h"

#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
 
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

/*

	=> The engine will be divided by modules:

		- Thread library
			- System specific
			- __InternalPeonJob stealing system
			- Multitasking for all modules
		- File explorer (IO file system)
			- With cached/temporary/predicted data
		- Core (main engine functionality)
			- Entity-component system
			- Data driven (oriented)
		- Physics engine
		- Sound engine
		- Resource deployer
		- Shader composer (collection of shaders)
			- Super-shader support
		- Shard library (network system)
			- Void connection support
*/

/*

	=> Systems são criados logo na inicialização da engine, logo, não precisam de algum tipo especial de controlador e podem usar o new/delete.
	=> Componentes são os objetos que podem ser criados dinamicamente e persistem durante frames, eles devem ser criados em forma de array (e não vetor de ponteiros)
	e devem suportar vários threads. Devemos usar um modelo especial de alocação para eles:

		- Toda criação de componente deve inicialmente feita usando-se a memória temporária e depois esta sendo copiada para a área permanente.

		=> Particle Emitter solicita nova particula
		=> Entidade e Position Component criados
		=> Adiciono o Position Component na sua array de controle
		=> Problema pois outra thread pode estar atualizando a array de controle ou mesmo adicionando outro elemento
		=> Soluções: Mutex (NÃO), atualização não é problema e podemos dar um jeito do adicionamento ser thread-safe
		=> Novo problema: Deleção de componentes

			=> Um componente só pode ser deletado se OU a entidade a qual ele pertence for deletada OU o componente em si não é utilizado como dependencia de algum
			outro componente OU o componente é ou possui alguma dependencia, mas esta dependencia também o possui como dependencia (assim, deletando todo o conjunto
			de dependencia) (mutualmente dependentes, embora isso não deveria existir). Seguindo essa regra nunca precisaremos informar outros componentes da deleção 
			de algum irmão.
			=> Um componente marcado para deleção deverá ter sua estrutura de linked-list editada e a deleção propria será realizada na fase final do update frame

			=> Talvez o component vector deva saber do escopo do objeto base componente e permitir iterar automaticamente fazendo update e verificando o deletion status.

*/

// #include "Common\Entity Component\ComponentVector.h"

/*
	=> Por testes é melhor que a gente use vários threads para ler arquivos
	=> O ideal é que cada thread tenha sempre um FILE para cada arquivo que ele possa ler
	=> Threads usando FILEs compartilhados são lentos
	=> Criação de FILEs é desprezível

	=> Usar mesmo sistema do job system
	=> Pensar em uma implementação genérica para o job system
*/

//aqui:
/*
	- Criar um command pool "per-thread" com cada uma das caracteristicas possíveis
	- Criar um tipo de command buffer inteligente que pode variar do tipo que tem pre alocado um para cada imagem (estático), ou desaloca e é remontado quase que a cada frame (semi-estático)
	ou é remontado sempre a cada frame (dinâmico).

	- Diferente do OpenGL e DirectX onde tinhamos um objeto (unidade) e ela continha o seu vertex/index buffer, texture reference, etc e na hora de renderizar puxavamos todos esses dados no shader e
	renderizavamos usando instanced, aqui devemos criar uma especie de "layout" de renderização.
	- Esse layout irá ser como um buffer de vertices mas além disso possuirá dados referentes à binding de texturas e uniform buffers, logo, diferentemente de como faziamos generalizando os objetos
	dos shaders e depois enviando para renderização separadamente, aqui precisamos criar esse link logo de inicio.

	- Preciso ver como faço para usar esse template do Descriptor Set para vários objetos, até certo ponto eu sei criar só o template mas aparentemente na hora que eu faço um VkDescriptorSet eu
	"linko" os dados, sendo que para cada objeto eu deveria atualizá-los, devo ter vários destes e criar um render pass para cada objeto?

	- Se eu quero renderizar apenas um tipo de objeto alterando posições e tal é fácil, só usar instancing e atualizar o uniform buffer (usar uma array e renderizar por batches), agora caso eu queira
	usar um "shader" para vários objetos eu preciso atualizar o vertex buffer, texture, etc. Até para instancing eu talvez precisasse atualizar o buffer de textura (na real posso enviar várias tex por
	vez e usar um index para pegar elas).
*/

#include "..\..\Editor\System\MainViewController.h"

#include "..\..\Editor\Foundation\ECS\ECS_Component.h"
#include "..\..\Editor\Foundation\ECS\ECS_Entity.h"
#include "..\..\Editor\Foundation\ECS\ECS_System.h"

// #include "..\..\Editor\Foundation\UI\UIView.h"

#include "..\..\Editor\Modules\Flux\Flux.h"

#include "..\..\Editor\Application.h"

//
//
//

#include "..\..\Editor\Modules\Peon\Peon.h"

#include <functional>
#include <iostream>
#include <vector>

int main()
{
	// Our application initialization params
	Application::InitializationParams initParams = {};
	initParams.sApplicationName = "Chronicles of a Fallen Soul";
	initParams.sEngineName = "Wonderland";
	initParams.sApplicationVersion = VK_MAKE_VERSION(0, 0, 1);
	initParams.sEngineVersion = VK_MAKE_VERSION(0, 0, 1);
	initParams.sTotalNumberPeonThreads = 4;
	initParams.sThreadRingBufferSize = 65000;

	// Create and initialize the main application
	Application mainApplication = {};
	if (!mainApplication.Initialize(initParams))
	{
		return false;
	}

	// Run the main loop
	mainApplication.MainLoop();

	//

	bool result;

	//

	// Get all creator a register instances we need
	Flux::ClassCreator* classCreatorInstance = Flux::ClassCreator::GetInstance();
	Flux::ClassRegister* classRegisterInstance = Flux::ClassRegister::GetInstance();
	Flux::TypeCreator* typeCreatorInstance = Flux::TypeCreator::GetInstance();
	Flux::TypeRegister* typeRegisterInstance = Flux::TypeRegister::GetInstance();
	Flux::DynamicMemberFunctionCreator* memberFunctionCreatorInstance = Flux::DynamicMemberFunctionCreator::GetInstance();

	// Basic type registration //
	Flux::Type* intType = typeCreatorInstance->CreateType("int");
	Flux::Type* floatType = typeCreatorInstance->CreateType("float");
	Flux::Type* charType = typeCreatorInstance->CreateType("char");
	Flux::Type* stringType = typeCreatorInstance->CreateType("string");
	Flux::Type* booleanType = typeCreatorInstance->CreateType("bool");
	Flux::Type* vectorType = typeCreatorInstance->CreateType("vector");

	// Class creation //

	// Create a new class
	Flux::Class* newClass = classCreatorInstance->CreateClass("Car");
	if (newClass == nullptr)
	{
		return false;
	}

	// Create a variable from the created class
	Flux::MemberVariable speedVariable;
	result = speedVariable.Build(floatType, "m_Speed");
	if (!result)
	{
		return false;
	}

	// Add the member variable
	result = newClass->AddMemberVariable(speedVariable);
	if(!result)
	{
		return false;
	}

	// Create a variable from the created class
	Flux::MemberVariable distanceVariable;
	result = distanceVariable.Build(intType, "m_CurrentDistance");
	if (!result)
	{
		return false;
	}

	// Add the member variable
	result = newClass->AddMemberVariable(speedVariable);
	if (!result)
	{
		return false;
	}

	// Create a variable from the created class
	Flux::MemberVariable costVariable;
	result = costVariable.Build(floatType, "m_CostPerDistance");
	if (!result)
	{
		return false;
	}

	// Add the member variable
	result = newClass->AddMemberVariable(speedVariable);
	if (!result)
	{
		return false;
	}

	// Function creation //

	// Create the nem member function
	Flux::DynamicMemberFunction* newFunction = memberFunctionCreatorInstance->CreateDynamicMemberFunction("CalculateTime", *newClass);
	if (newFunction == nullptr)
	{
		return false;
	}

	/*

		- Handle precisa ter um id de versão
	*/

	/*
		
		=> Dynamic Function:

		- Head		-> Definições de uma função (qual o nome, se pertence à uma classe, quais entradas... etc)
		- Body		-> Como esta definido o seu corpo, quais funções (boxes) são utilizados, quais foram as ligações efetuadas, variáveis utilizadas... etc
		- Linker	-> Realização da compilação da DynamicFunction em realtime.
	*/

	/*
		- Vamos ter uma nova classe que vai ser tipo um box, ele vai contar o ponto inicial, final e vai possuir blocos que vão se ligar entre si, esses blocos fazem referência
		à um box conectado.
		- Começando no bloco inicial, vamos ir para o proximo, aqui podemos ter por exemplo uma função membro, nosso objetivo será pegar os dados da função membro, fazer a chamada
		com ela utilizando as variáveis linkadas (nota que não foi incluido a geração dos nomes das variáveis).
		- Após isso vamos para a proxima função, que pode ser um loop por exemplo, o loop deve criar uma variável que vai ser o contador e usar os parâmetros de entrada para realizar
		as chamadas seguintes.

		- Da pra perceber que o ideal é fechar cada bloco, por exemplo no primeiro, podemos passar as variáveis linkadas aos sockets de entrada para o "fechador" da função membro
		utilizada e ela fica responsável por usar essas entradas e gerar a chamada, podendo até mesmo retornar e assim seguimos para a proxima box ou continuar por conta propria.
		- No segundo exemplo nos iriamos para um loop, ele vai ter os valores de entrada (index inicial, final, etc) e provavelmente deveriamos continuar a execução por conta
		propria.

		- Temos que pensar em como vamos fazer os ifs, os sequences, sets, gets, for eachs, prints, etc... São todas funções standard, intrinsic.
		- Talvez devemos separar tipo, funções membro, funções normais, loop for, if, set, get e assim vai... Só que as funções (tanto membro quando normais) existiriam de várias
		formas precisando serem registradas enquanto os outros seriam classes especializadas que não precisariam serem registradas, afinal já teriamos uma de cada tipo.
		- O ideal seria que tivermos uma forma de criar essas funções intrinsics, talvez seja possível faze-las na parte de funções normais ou quem sabe fazer um criador para elas.
	*/

	/*
		- Uma box pode ter inputs e outputs, não importa qual o tipo de box.
		- Uma input/output pode ser de vários tipos.

		- Uma box pode ser uma função, uma caixa de debug, um start ou end dentro de uma função, etc.
		- Uma input/output pode ser uma variável, um valor absoluto, uma constante, etc.
		- Uma input/output pode ter um valor temporário para teste na engine.
		- Uma input/output pode ser uma array, nesse caso ele não pode possuir um valor absoluto e sim deve ser uma variável.

		- Uma box SEMPRE deve ter (se tiver) apenas UMA entrada.
		- Uma box pode ter várias saídas desde que mantenha em mente que as saídas serão executadas em sequência (depende da interpretação da box)

		
	
	
	
	
	*/

	////////////////
	// INITIALIZE //
	////////////////
	MainViewController viewController;
	viewController.Initialize();

	////////////////////////
	////////////////////////
	////////////////////////

    return 0;
}

