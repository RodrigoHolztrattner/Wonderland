////////////////////////////////////////////////////////////////////////////////
// Filename: ECS_Component.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

/////////////
// LINKING //
/////////////

//////////////
// INCLUDES //
//////////////
#include "ECS_System.h"
#include <string>
#include <vector>
#include "..\..\Support\Container\Map\ConstantMap.h"

/////////////
// DEFINES //
/////////////

/**
 *	Contrato:
 *
 *	=> Cada componente � respons�vel por si, a partir do momento que ele adquire todas as suas dependencias ele deve ser capaz de exercer a sua fun��o sem
 *	precisar de qualquer interferencia da entidade pai.
 *	=> Qualquer fun��o de callback de algum componente deve ser opcional para o funcionamento do mesmo, n�o deve necessariamente ser implementada para que
 *	o mesmo possa existir.
 *	=> Um componente n�o existe se n�o ligado � uma entidade (ou indiretamente ligado � ela).
 *	=> Quando uma entidade deixa de existir, todos os seus componentes seguem a mesma regra.
 *	=> Um componente pode ter acesso a qualquer objeto externo, assim como recursos e controladores sem precisar fazer chamadas para a entidade pai, em suma,
 *	um componente n�o deve depender em nada de uma entidade com exce��o da procura por dependeicias, no restante ele apenas deve receber informa��es e a��es.
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
#define AddComponentUniqueID(classtype)										\
private:																	\
static int GetClassComponentPrivateID()										\
{																			\
	return reinterpret_cast<int>(typeid(classtype).name());					\
}																			\
public:																		\
static const unsigned int ClassComponentID()								\
{																			\
	return reinterpret_cast<size_t>(GetClassComponentPrivateID);			\
}

/*
/**
 *	Generate an unique ID for the class
 */
/*
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
*/

/**
 *	Register the dependencies for this component
 */
#define RegisterClassDependencies(...)										\
private: ConstantMap<__VA_ARGS__> dependencies;								\
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
	return (dependencies.storageCount) || m_Invalidated;					\
}																			\
																			\
protected: virtual void Invalidate()										\
{																			\
	dependencies.Reset();													\
	m_Invalidated = true;													\
}	

/**
*	Register the optional dependencies for this component
*/
#define RegisterOptionalClassDependencies(...)								\
private: ConstantMap<__VA_ARGS__> optionalDependencies;						\
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
																			\
protected: virtual void Validate()											\
{																			\
	optionalDependencies.Reset();											\
	m_Invalidated = true;													\
}	

// We know the ECS_Entity class
class ECS_Entity;

////////////////////////////////////////////////////////////////////////////////
// Class name: ECS_Component
////////////////////////////////////////////////////////////////////////////////
class ECS_Component
{
private:

	// Add a unique ID to this component class
	// AddComponentUniqueID();

	// The ECS_Entity class is a friend
	friend ECS_Entity;

public:
	ECS_Component(unsigned int _componentID);
	ECS_Component(const ECS_Component&);
	~ECS_Component();

	// Return an entity component by class
	ECS_Component* GetEntityComponentById(unsigned int _id);
	template <typename ComponentClass> ComponentClass* GetEntityComponent()
	{
		return m_EntityOwner->FindComponent<ComponentClass>();
	}

	/////////////
	// VIRTUAL //
	/////////////

	// The update method
	virtual void Update(unsigned int _updateId, float _timeElapsed){}

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
	ECS_Entity* GetEntityOwner()
	{
		return m_EntityOwner;
	}

	// Return if this component is dirty
	virtual bool IsDirty()
	{
		return m_Invalidated;
	}

// protected:

	// Validate this component
	virtual void Validate()
	{
		m_Invalidated = false;
	}

	// Invalidate this component
	virtual void Invalidate()
	{
		m_Invalidated = true;
	}

	// Register the entity owner
	void RegisterEntityOwner(ECS_Entity* _entity)
	{
		m_EntityOwner = _entity;
	}

private:

	// The component ID type
	unsigned int m_ComponentID;

	// The entity owner
	ECS_Entity* m_EntityOwner;

	/*
	// The external component dependencies
	std::vector<ECS_Component*> m_ExternalDependencies;

	// The external linked dependencies
	std::vector<ECS_Component*> m_ExternalLinkedDependencies;
	*/

protected:

	// If this component was invalidated
	bool m_Invalidated;

};