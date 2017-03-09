////////////////////////////////////////////////////////////////////////////////
// Filename: ISystem.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _ISystem_H_
#define _ISystem_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "ComponentVector.h"

/////////////
// DEFINES //
/////////////

/**
 *	Contrato:
 *
 *	=> Cada sistema usa o Curiously Recurring Template Pattern (CRTP) e é responsável pelo gerenciamento de cada componente do seu tipo.
 *	=> O sistema deve ser responsável por criar, realizar updates e destruir qualquer componente marcado, o mesmo deve também guardar em listas as referencias de
 *	componentes já destruidos que serão utilizados para poupar memória.
 *
 */

////////////////////////////////////////////////////////////////////////////////
// Class name: ISystem
////////////////////////////////////////////////////////////////////////////////
template<typename ComponentClass>
class ISystem
{
private:

	// The IComponent is a friend
	friend IComponent;

public:
	ISystem(){}
	ISystem(const ISystem&){}
	~ISystem(){}

	// Create a new component of this type
	static IndirectionPointer<IComponent>* Create()
	{
		if (m_ComponentVector == nullptr)
		{
			m_ComponentVector = new ComponentVector<ComponentClass>;
			m_ComponentVector->SetSizes(16, 4);
		}

		return m_ComponentVector->GetNewComponent();
	}

	// Update the component list
	static void UpdateComponents(float _timeElapsed)
	{
		m_ComponentVector->UpdatePack(0, _timeElapsed); // Need to set all the jobs here!
	}

private:

	// The component vector
	static ComponentVector<ComponentClass>* m_ComponentVector;
};

template<typename ComponentClass>
ComponentVector<ComponentClass>* ISystem<ComponentClass>::m_ComponentVector = nullptr;

#endif
