// Wonderland.cpp : Defines the entry point for the console application.
//

#include <pthread.h>
// #include "SystemClass.h"

#include <fstream>
#include <iterator>
#include <algorithm>
#include <map>
/*

	=> The engine will be divided by modules:

		- Thread library
			- System specific
			- Job stealing system
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
#include "Common\Entity Component\IComponent.h"
#include "Common\Math\WMath.h"
#include "Common\Entity Component\ISystem.h"


/*
	=> Por testes � melhor que a gente use v�rios threads para ler arquivos
	=> O ideal � que cada thread tenha sempre um FILE para cada arquivo que ele possa ler
	=> Threads usando FILEs compartilhados s�o lentos
	=> Cria��o de FILEs � desprez�vel

	=> Usar mesmo sistema do job system
	=> Pensar em uma implementa��o gen�rica para o job system
*/

#include "..\..\Editor\Foundation\UI\ViewController\ViewController.h"

#include "..\..\Editor\Foundation\ECS\ECS_Component.h"
#include "..\..\Editor\Foundation\ECS\ECS_Entity.h"
#include "..\..\Editor\Foundation\ECS\ECS_System.h"

// #include "..\..\Editor\Foundation\UI\UIView.h"

int main()
{
	ViewController viewController;
	viewController.Initialize();

	viewController.GetUpdateThread()->join();

	////////////////////////
	////////////////////////
	////////////////////////
	/*
	using namespace WonderlandTS;
	using namespace System;

	//
	JobSystem* jobSystem = new JobSystem;
	SystemClass* system = new SystemClass;

	// Initialize the job system
	if (!jobSystem->Initialize(4, 65536))
	{
		return false;
	}

	// Start the main job
	jobSystem->CreateJobArea(*system, &SystemClass::MainFrame, nullptr);

	// Delete the job area
	jobSystem->DeleteJobArea();
	*/

    return 0;
}

