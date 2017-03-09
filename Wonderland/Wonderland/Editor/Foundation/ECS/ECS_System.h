////////////////////////////////////////////////////////////////////////////////
// Filename: ECS_System.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "..\..\Support\Container\List\GlobalList.h"
#include "..\..\Support\Container\Array\Array.h"
#include <typeinfo>

/////////////
// DEFINES //
/////////////

/**
 *	Contrato:
 *
 *	=> Cada sistema usa o Curiously Recurring Template Pattern (CRTP) e � respons�vel pelo gerenciamento de cada componente do seu tipo.
 *	=> O sistema deve ser respons�vel por criar, realizar updates e destruir qualquer componente marcado, o mesmo deve tamb�m guardar em listas as referencias de
 *	componentes j� destruidos que ser�o utilizados para poupar mem�ria.
 *
 */

// The system node type
template<typename ComponentClass>
struct ECS_SystemNode
{
	// The component itself
	ComponentClass* component;

	// The next node
	ECS_SystemNode* next;
};

////////////////////////////////////////////////////////////////////////////////
// Class name: ECS_SystemManager
////////////////////////////////////////////////////////////////////////////////
class ECS_SystemManager
{
protected:

	ECS_SystemManager() 
	{
		// Insert this system into the global array
		ECS_SystemManager* temp = this;
		GetGlobalArray()->Add(temp);
	}
	ECS_SystemManager(const ECS_SystemManager&) {}
	~ECS_SystemManager() {}

public:

	static void UpdateAllSystems(unsigned int _updateId, float _timeElapsed)
	{
		// For each system stores
		for (int i = 0; i < GetGlobalArray()->Size(); i++)
		{
			// Call the update function
			(*GetGlobalArray())[i]->UpdateComponents(_updateId, _timeElapsed);
		}
	}

protected:

	virtual void UpdateComponents(unsigned int _updateId, float _timeElapsed) = 0;

	// Return the global array
	static Array<ECS_SystemManager*>* GetGlobalArray()
	{
		static Array<ECS_SystemManager*>* systemArray = nullptr;
		if (systemArray == nullptr)
		{
			systemArray = new Array<ECS_SystemManager*>();
		}

		return systemArray;
	}

private:

	
};

////////////////////////////////////////////////////////////////////////////////
// Class name: ECS_System
////////////////////////////////////////////////////////////////////////////////
template<typename ComponentClass>
class ECS_System : public ECS_SystemManager
{
private:

public:
	ECS_System(){}
	ECS_System(const ECS_System&){}
	~ECS_System(){}

	// Return a instance for this system
	static ECS_System<ComponentClass>* GetInstance()
	{
		// Check if the system was created
		static ECS_System<ComponentClass>* system = nullptr;
		if (system == nullptr)
		{
			system = new ECS_System<ComponentClass>();
		}

		return system;
	}

	// Create a new component of this type
	static ComponentClass* Create()
	{
		// Ensure we created a instance of this system
		GetInstance();

		// Get the new component
		ComponentClass* newComponent = m_ComponentList->Create();

		// Validate the new component
		newComponent->Validate();

		std::cout << "+> Component from class <" << typeid(ComponentClass).name() << "> created!" << std::endl;

		return newComponent;
	}

	/*
	// Update the component list
	static void UpdateComponents(unsigned int _updateId, float _timeElapsed)
	{
		// For each component
		for(ComponentClass* component = m_ComponentList->InitializeIterator(); (component = m_ComponentList->GetNextObject()) != nullptr; m_ComponentList->IncrementIterator())
		{
			// Check if this component is dirty
			if (component->IsDirty())
			{
				// Register a null entity owner for this component
				component->RegisterEntityOwner(nullptr);

				// Remove this component from the list
				m_ComponentList->RemoveCurrentNode();

				// Delete the current component
				// delete component;

				std::cout << "-> Component from class <" << typeid(ComponentClass).name() << "> deleted!" << std::endl;

				continue;
			}

			// Update this component
			component->Update(_updateId, _timeElapsed);			
		}
	}
	*/

protected:

	// Update the component list
	void UpdateComponents(unsigned int _updateId, float _timeElapsed)
	{
		// For each component
		for (ComponentClass* component = m_ComponentList->InitializeIterator(); (component = m_ComponentList->GetNextObject()) != nullptr; m_ComponentList->IncrementIterator())
		{
			// Check if this component is dirty
			if (component->IsDirty())
			{
				// Register a null entity owner for this component
				component->RegisterEntityOwner(nullptr);

				// Remove this component from the list
				m_ComponentList->RemoveCurrentNode();

				// Delete the current component
				// delete component;

				std::cout << "-> Component from class <" << typeid(ComponentClass).name() << "> deleted!" << std::endl;

				continue;
			}

			// Update this component
			component->Update(_updateId, _timeElapsed);
		}
	}

///////////
// DEBUG //
public: ///

	// Return the number of components for this system
	static unsigned int GetComponentCount()
	{
		return m_ComponentList.Size();
	}

private:

	// The component list
	static GlobalList<ComponentClass>* m_ComponentList;
};

template<typename ComponentClass>
GlobalList<ComponentClass>* ECS_System<ComponentClass>::m_ComponentList = nullptr;