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

	=> Systems s�o criados logo na inicializa��o da engine, logo, n�o precisam de algum tipo especial de controlador e podem usar o new/delete.
	=> Componentes s�o os objetos que podem ser criados dinamicamente e persistem durante frames, eles devem ser criados em forma de array (e n�o vetor de ponteiros)
	e devem suportar v�rios threads. Devemos usar um modelo especial de aloca��o para eles:

		- Toda cria��o de componente deve inicialmente feita usando-se a mem�ria tempor�ria e depois esta sendo copiada para a �rea permanente.

		=> Particle Emitter solicita nova particula
		=> Entidade e Position Component criados
		=> Adiciono o Position Component na sua array de controle
		=> Problema pois outra thread pode estar atualizando a array de controle ou mesmo adicionando outro elemento
		=> Solu��es: Mutex (N�O), atualiza��o n�o � problema e podemos dar um jeito do adicionamento ser thread-safe
		=> Novo problema: Dele��o de componentes

			=> Um componente s� pode ser deletado se OU a entidade a qual ele pertence for deletada OU o componente em si n�o � utilizado como dependencia de algum
			outro componente OU o componente � ou possui alguma dependencia, mas esta dependencia tamb�m o possui como dependencia (assim, deletando todo o conjunto
			de dependencia) (mutualmente dependentes, embora isso n�o deveria existir). Seguindo essa regra nunca precisaremos informar outros componentes da dele��o 
			de algum irm�o.
			=> Um componente marcado para dele��o dever� ter sua estrutura de linked-list editada e a dele��o propria ser� realizada na fase final do update frame

			=> Talvez o component vector deva saber do escopo do objeto base componente e permitir iterar automaticamente fazendo update e verificando o deletion status.

*/

// #include "Common\Entity Component\ComponentVector.h"

/*
	=> Por testes � melhor que a gente use v�rios threads para ler arquivos
	=> O ideal � que cada thread tenha sempre um FILE para cada arquivo que ele possa ler
	=> Threads usando FILEs compartilhados s�o lentos
	=> Cria��o de FILEs � desprez�vel

	=> Usar mesmo sistema do job system
	=> Pensar em uma implementa��o gen�rica para o job system
*/

//aqui:
/*
	- Criar um command pool "per-thread" com cada uma das caracteristicas poss�veis
	- Criar um tipo de command buffer inteligente que pode variar do tipo que tem pre alocado um para cada imagem (est�tico), ou desaloca e � remontado quase que a cada frame (semi-est�tico)
	ou � remontado sempre a cada frame (din�mico).

	- Diferente do OpenGL e DirectX onde tinhamos um objeto (unidade) e ela continha o seu vertex/index buffer, texture reference, etc e na hora de renderizar puxavamos todos esses dados no shader e
	renderizavamos usando instanced, aqui devemos criar uma especie de "layout" de renderiza��o.
	- Esse layout ir� ser como um buffer de vertices mas al�m disso possuir� dados referentes � binding de texturas e uniform buffers, logo, diferentemente de como faziamos generalizando os objetos
	dos shaders e depois enviando para renderiza��o separadamente, aqui precisamos criar esse link logo de inicio.

	- Preciso ver como fa�o para usar esse template do Descriptor Set para v�rios objetos, at� certo ponto eu sei criar s� o template mas aparentemente na hora que eu fa�o um VkDescriptorSet eu
	"linko" os dados, sendo que para cada objeto eu deveria atualiz�-los, devo ter v�rios destes e criar um render pass para cada objeto?

	- Se eu quero renderizar apenas um tipo de objeto alterando posi��es e tal � f�cil, s� usar instancing e atualizar o uniform buffer (usar uma array e renderizar por batches), agora caso eu queira
	usar um "shader" para v�rios objetos eu preciso atualizar o vertex buffer, texture, etc. At� para instancing eu talvez precisasse atualizar o buffer de textura (na real posso enviar v�rias tex por
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

		- Handle precisa ter um id de vers�o
	*/

	/*
		
		=> Dynamic Function:

		- Head		-> Defini��es de uma fun��o (qual o nome, se pertence � uma classe, quais entradas... etc)
		- Body		-> Como esta definido o seu corpo, quais fun��es (boxes) s�o utilizados, quais foram as liga��es efetuadas, vari�veis utilizadas... etc
		- Linker	-> Realiza��o da compila��o da DynamicFunction em realtime.
	*/

	/*
		- Vamos ter uma nova classe que vai ser tipo um box, ele vai contar o ponto inicial, final e vai possuir blocos que v�o se ligar entre si, esses blocos fazem refer�ncia
		� um box conectado.
		- Come�ando no bloco inicial, vamos ir para o proximo, aqui podemos ter por exemplo uma fun��o membro, nosso objetivo ser� pegar os dados da fun��o membro, fazer a chamada
		com ela utilizando as vari�veis linkadas (nota que n�o foi incluido a gera��o dos nomes das vari�veis).
		- Ap�s isso vamos para a proxima fun��o, que pode ser um loop por exemplo, o loop deve criar uma vari�vel que vai ser o contador e usar os par�metros de entrada para realizar
		as chamadas seguintes.

		- Da pra perceber que o ideal � fechar cada bloco, por exemplo no primeiro, podemos passar as vari�veis linkadas aos sockets de entrada para o "fechador" da fun��o membro
		utilizada e ela fica respons�vel por usar essas entradas e gerar a chamada, podendo at� mesmo retornar e assim seguimos para a proxima box ou continuar por conta propria.
		- No segundo exemplo nos iriamos para um loop, ele vai ter os valores de entrada (index inicial, final, etc) e provavelmente deveriamos continuar a execu��o por conta
		propria.

		- Temos que pensar em como vamos fazer os ifs, os sequences, sets, gets, for eachs, prints, etc... S�o todas fun��es standard, intrinsic.
		- Talvez devemos separar tipo, fun��es membro, fun��es normais, loop for, if, set, get e assim vai... S� que as fun��es (tanto membro quando normais) existiriam de v�rias
		formas precisando serem registradas enquanto os outros seriam classes especializadas que n�o precisariam serem registradas, afinal j� teriamos uma de cada tipo.
		- O ideal seria que tivermos uma forma de criar essas fun��es intrinsics, talvez seja poss�vel faze-las na parte de fun��es normais ou quem sabe fazer um criador para elas.
	*/

	/*
		- Uma box pode ter inputs e outputs, n�o importa qual o tipo de box.
		- Uma input/output pode ser de v�rios tipos.

		- Uma box pode ser uma fun��o, uma caixa de debug, um start ou end dentro de uma fun��o, etc.
		- Uma input/output pode ser uma vari�vel, um valor absoluto, uma constante, etc.
		- Uma input/output pode ter um valor tempor�rio para teste na engine.
		- Uma input/output pode ser uma array, nesse caso ele n�o pode possuir um valor absoluto e sim deve ser uma vari�vel.

		- Uma box SEMPRE deve ter (se tiver) apenas UMA entrada.
		- Uma box pode ter v�rias sa�das desde que mantenha em mente que as sa�das ser�o executadas em sequ�ncia (depende da interpreta��o da box)

		
	
	
	
	
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

