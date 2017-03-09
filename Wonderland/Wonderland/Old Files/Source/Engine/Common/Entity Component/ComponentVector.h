////////////////////////////////////////////////////////////////////////////////
// Filename: ComponentVector.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include <stdlib.h>     /* srand, rand */
#include <iostream>
#include "..\Containers\Pointer\IndirectionPointer.h"

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
class Component
{
	// The ComponentVector class is a friend
	friend ComponentVector;

public:

	Component()
	{
		m_Active = true;
		m_SelfPointer = new IndirectionPointer<Component>;
		m_SelfPointer->Set(this);
	}


	// Return the status
	bool ShouldDelete()
	{
		return m_Active;
	}

	//

	void Update(int _time)
	{
		if(_time == 3)
		{
			m_Active = false;
		}
	}





protected:

	void SetIndirectionPointer(IndirectionPointer<Component>* _reference)
	{
		m_SelfPointer = _reference;
		m_SelfPointer->Set(this);
	}

	// Return the internal reference
	IndirectionPointer<Component>* GetIndirectionPointer()
	{
		return m_SelfPointer;
	}

private:

	IndirectionPointer<Component>* m_SelfPointer;
	bool m_Active;
};
*/

/*

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	- Preciso de uma array que tenha memória alinhada, ou seja, não posso trabalhar com pointers em uma array pois os objetos precisam existir no mesmo local.
	- Em algum momento preciso mover esses objetos, então qualquer referencia de fora utilizando ponteiros seria quebrada, preciso atualizar esses ponteiros.
	- Como são muitos ponteiros e vários objetos, seria pesado guardar uma referencia para cada um deles, então preciso distribuir um tipo de ponteiro para todos
	os objetos que referenciam o componente em questão e atualizar apenas esse "tipo" de ponteiro.
	- Opções:

		- Distribuir um constantPointer como eu havia feito, ele pode ficar dentro do objeto sem problemas.

			- Preciso deletar um objeto, salvo os 2 ponteiros de referencia.
			- Removo o objeto deletado copiando um novo para o local de memória desse.
			- Atualizo os ponteiros de referencia para ambos os objetos nos seus novos locais de memória.
			- Ativo os ponteiros para apontarem para o objeto real.

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	- Quando uma entity é criada, criamos um IndirectionPointer para cada Component que irá existir.
	- Existe uma fase durante o frame update que iremos criar efetivamente cada componente, mas essa fase não é a mesma onde as entidades são criadas.
	- Existe um local onde se encontram vários componentes vagos (livres para serem utilizados)

*/

// We know the IComponent class
class IComponent;

////////////////////////////////////////////////////////////////////////////////
// Class name: ComponentVector
////////////////////////////////////////////////////////////////////////////////
template <typename ComponentType>
class ComponentVector
{
	// The IComponent class is a friend
	friend IComponent;

	// The component pack type
	struct ComponentPack
	{
		ComponentType* components;
		int numberActiveComponents;
	};

public:
	ComponentVector() {}
	ComponentVector(const ComponentVector&) {}
	~ComponentVector() {}

	// Get a new component
	IndirectionPointer<IComponent>* GetNewComponent()
	{
		// Need to find a better solution to this //

		// For each pack
		for (int i = 0; i < m_NumberPacks; i++)
		{
			// Get the pack
			ComponentPack* componentPack = &m_ComponentPacks[i];

			// Check if there is a empty slot for the new component
			if (componentPack->numberActiveComponents < m_PackSize)
			{
				// Get the free component
				ComponentType* component = &componentPack->components[componentPack->numberActiveComponents];

				// Increment the number of active components
				componentPack->numberActiveComponents++;

				// Return the component indirection pointer
				return component->GetIndirectionPointer();
			}
		}

		// No free components //
		return nullptr;
	}

	// Set the vector size
	void SetSizes(int _pageSize, int _packSize)
	{
		// Set the page size, pack size and the number of packs
		m_PageSize = _pageSize;
		m_PackSize = _packSize;
		m_NumberPacks = m_PageSize / m_PackSize;
		
		// Create all the component pages
		m_ComponentPacks = new ComponentPack[m_NumberPacks];

		for (int i = 0; i < m_PageSize / m_PackSize; i++)
		{
			// Get the component pack
			ComponentPack* pack = &m_ComponentPacks[i];

			// Initialize all components
			pack->components = new ComponentType[m_PackSize];
			pack->numberActiveComponents = 0;
		}
	}

	// Return a component by index
	IndirectionPointer<IComponent>* GetComponentByIndex(int _index)
	{
		// Set the page number and get the component page
		int pageNumber = _index / m_PackSize;
		ComponentPack* componentPack = &m_ComponentPacks[pageNumber];

		// Get the component
		ComponentType* component = &componentPack->components[_index % m_PackSize];

		// Return the indirection pointer
		return component->GetIndirectionPointer();
	}

	// Return the number of packs
	int GetNumberPacks()
	{
		return m_NumberPacks;
	}

	// Update a pack of components
	void UpdatePack(int _packIndex, float _time)
	{
		// Get the component pack
		ComponentPack* pack = &m_ComponentPacks[_packIndex];

		// Each thread here
		for (int j = 0; j < pack->numberActiveComponents; j++)
		{
			// Get a ptr to the current components
			ComponentType* component = &pack->components[j];

			// Update this component
			component->Update(_time);

			// Check the status
			if (component->ShouldDelete())
			{
				// Get a ptr to the last valid component
				ComponentType* lastValidComponent = &pack->components[pack->numberActiveComponents - 1];

				// Get the internal reference
				IndirectionPointer<IComponent>* deletedInternalReference = component->GetIndirectionPointer();
				IndirectionPointer<IComponent>* aliveInternalReference = lastValidComponent->GetIndirectionPointer();

				// Copy the valid component data (ignore the deleted one)
				memcpy(component, lastValidComponent, sizeof(ComponentType));
				// memset(lastValidComponent, 0, sizeof(ComponentType)); // Optional

				// Set the internal references
				component->SetIndirectionPointer(aliveInternalReference);
				lastValidComponent->SetIndirectionPointer(deletedInternalReference);

				// Subtract one from the active components counter
				pack->numberActiveComponents--;
			}
		}
	}

	// Allock a new page for this component vector
	// ...
	
private:

	ComponentPack* m_ComponentPacks;
	int m_PackSize;
	int m_PageSize;
	int m_NumberPacks;
	int m_NumberPages; // Não utilizado por enquanto
};
