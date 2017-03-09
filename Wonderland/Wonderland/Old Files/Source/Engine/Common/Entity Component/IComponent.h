////////////////////////////////////////////////////////////////////////////////
// Filename: IComponent.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _IComponent_H_
#define _IComponent_H_

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "ISystem.h"
#include <string>
#include "..\..\..\..\Editor\Support\Container\Map\ConstantMap.h"
#include "ComponentVector.h"

/////////////
// DEFINES //
/////////////

/**
 *	Contrato:
 *
 *	=> Cada componente é responsável por si, a partir do momento que ele adquire todas as suas dependencias ele deve ser capaz de exercer a sua função sem
 *	precisar de qualquer interferencia da entidade pai.
 *	=> Qualquer função de callback de algum componente deve ser opcional para o funcionamento do mesmo, não deve necessariamente ser implementada para que
 *	o mesmo possa existir.
 *	=> Um componente não existe se não ligado à uma entidade (ou indiretamente ligado à ela).
 *	=> Quando uma entidade deixa de existir, todos os seus componentes seguem a mesma regra.
 *	=> Um componente pode ter acesso a qualquer objeto externo, assim como recursos e controladores sem precisar fazer chamadas para a entidade pai, em suma,
 *	um componente não deve depender em nada de uma entidade com exceção da procura por dependeicias, no restante ele apenas deve receber informações e ações.
 */

/**
 *	Exemplos de componentes:
 *
 *	=> Transform.
 *	=> Displacement.
 *	=> Collision.
 *	=> Model.
 *	=> Mesh.					?
 *	=> Sprite					?
 *	=> Input.
 *	=> AI.
 *	=> Particle Emitter.
 *	=> Controllers.
 *
 *
 */

////////////
// MACROS //
////////////

/**
 *	Generate an unique ID for the class
 */
#define AddComponentUniqueID()												\
private:																	\
static int GetClassComponentPrivateID()										\
{																			\
	return __LINE__;														\
}																			\
public:																		\
static const unsigned int ClassComponentID()								\
{																			\
	return reinterpret_cast<size_t>(GetClassComponentPrivateID);			\
}

/**
 *	Register the dependencies for this component
 */
#define RegisterClassDependencies(...)										\
private: ConstantMap<__VA_ARGS__> dependencies;							\
public: template <typename ClassType>										\
ClassType* GetDependency()													\
{																			\
	ClassType* dummy = 0;													\
	return dependencies[dummy];												\
}																			\
																			\
public: template <typename ClassType>										\
ClassType* RegisterDependency(ClassType* _object)							\
{																			\
	ClassType* dummy = 0;													\
	dependencies.storageCount--;											\
	return *(dependencies << dummy) = _object;								\
}																			\
																			\
public: bool IsDirty()														\
{																			\
	return (dependencies.storageCount);										\
}

/**
*	Register the optional dependencies for this component
*/
#define RegisterOptionalClassDependencies(...)								\
private: ConstantMap<__VA_ARGS__> optionalDependencies;					\
public: template <typename ClassType>										\
ClassType* GetOptionalDependency()											\
{																			\
	ClassType* dummy = 0;													\
	return optionalDependencies[dummy];										\
}																			\
																			\
public: template <typename ClassType>										\
ClassType* RegisterOptionalDependency(ClassType* _object)					\
{																			\
	ClassType* dummy = 0;													\
	return *(optionalDependencies << dummy) = _object;						\
}																			\

// We know the IEntity class
class IEntity;

////////////////////////////////////////////////////////////////////////////////
// Class name: IComponent
////////////////////////////////////////////////////////////////////////////////
// template <typename ComponentExtensionType>
class IComponent
{
public:

	// Add a unique ID to this component class
	AddComponentUniqueID();

	// The IEntity class is a friend
	friend IEntity;

	// The ISystem class is a friend
	friend ISystem<IComponent>;

	// The ComponentVector class is a friend
	friend ComponentVector<IComponent>;

	// The IndirectionPointer class is a friend
	friend IndirectionPointer<IComponent>;

public:
	IComponent(unsigned int _componentID)
	{
		// Set the initial data
		m_ComponentID = _componentID;
		m_ShouldDelete = false;
		m_SelfPointer = new IndirectionPointer<IComponent>;
		m_SelfPointer->Set(this);
	}
	IComponent(const IComponent&) {}
	~IComponent() {}

protected:

	/////////////
	// VIRTUAL //
	/////////////

	// The update method
	virtual void Update(float _timeElapsed){}

	// The clear method
	virtual void Clear(){}

	//////////////
	// INTERNAL //
	//////////////

	// Return the component ID
	unsigned int GetComponentID()
	{
		return m_ComponentID;
	}

	// Return the entity owner
	IEntity* GetEntityOwner()
	{
		return m_EntityOwner;
	}

	// Return if this component is dirty
	virtual bool IsDirty()
	{
		return true;
	}

	// Return if this component should be deleted
	bool ShouldDelete()
	{
		return m_ShouldDelete;
	}

protected:

	// Register the entity owner
	void RegisterEntityOwner(IEntity* _entity)
	{
		m_EntityOwner = _entity;
	}

	// Deletion call
	void DeletionCall()
	{
		m_ShouldDelete = true;
	}

public:

	void SetIndirectionPointer(IndirectionPointer<IComponent>* _reference)
	{
		m_SelfPointer = _reference;
		m_SelfPointer->Set(this);
	}

	// Return the internal reference
	IndirectionPointer<IComponent>* GetIndirectionPointer()
	{
		return m_SelfPointer;
	}

private:

	// The indirection pointer (called self pointer, a constant reference to the right piece of memory where this component exists)
	IndirectionPointer<IComponent>* m_SelfPointer;

	// The component ID type
	unsigned int m_ComponentID;

	// The entity owner
	IEntity* m_EntityOwner;

	// If this component should be deleted
	bool m_ShouldDelete;

private:

};

#endif
