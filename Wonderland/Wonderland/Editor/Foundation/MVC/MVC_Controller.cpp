///////////////////////////////////////////////////////////////////////////////
// Filename: MVC_Controller.cpp
///////////////////////////////////////////////////////////////////////////////
#include "MVC_Controller.h"
#include "MVC_Model.h"
#include "MVC_View.h"

MVC_Controller::MVC_Controller()
{
	// Set the initial data
	m_ModelReference = nullptr;
}

MVC_Controller::MVC_Controller(const MVC_Controller& other)
{
}

MVC_Controller::~MVC_Controller()
{
}

void MVC_Controller::SetModelReference(MVC_Model* _modelReference)
{
	m_ModelReference = _modelReference;
}

void MVC_Controller::AddSubscriber(MVC_View* _subscriber)
{
	m_Subscribers.Add(_subscriber);
}

void MVC_Controller::AlertSubscribers()
{
	// For each subscriber
	for (int i = 0; i < m_Subscribers.Size(); i++)
	{
		// Alert this subscriber
		m_Subscribers[i]->ModelChangedAlert();
	}
}