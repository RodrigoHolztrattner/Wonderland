///////////////////////////////////////////////////////////////////////////////
// Filename: MVC_Model.cpp
///////////////////////////////////////////////////////////////////////////////
#include "MVC_Model.h"

MVC_Model::MVC_Model()
{
	// Set our controller reference
	MVC_Controller::SetModelReference(this);

	// Set the initial data
	// ...
}

MVC_Model::MVC_Model(const MVC_Model& other)
{
}

MVC_Model::~MVC_Model()
{
}

void MVC_Model::CommitChanges()
{
	// Alert all subscribers
	MVC_Controller::AlertSubscribers();
}