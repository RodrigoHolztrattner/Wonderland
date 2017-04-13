////////////////////////////////////////////////////////////////////////////////
// Filename: FluxWidget.cpp
////////////////////////////////////////////////////////////////////////////////
#include "HGWidget.h"
#include <glm/gtx/transform.hpp>

HookGui::HGWidget::HGWidget() : HGFrameComponent(this)
{
	// Set the initial data
    m_Delegate = this;
    m_Parent = nullptr;
    m_BoundedWidgetController = nullptr;
    // m_Tag = -1; // Request new tag
    m_IsHidden = false;
    m_ClipToBound = true;
    m_CanInteract = true;
	m_CanReceiveInput = true;
    m_AutoresizeChilds = true;
	m_CanBeRendered = true;

	static uint32_t id = 0;
	m_Handle = id;
	id++;
}

HookGui::HGWidget::~HGWidget()
{
}

bool HookGui::HGWidget::Initialize()
{
    return true;
}

void HookGui::HGWidget::Update(float _timeElapsed)
{
	// Update the image
	m_Image.Update(_timeElapsed);
}

void HookGui::HGWidget::AddSubwidget(HGWidget* _widget)
{
    // Get the insert position
    int insertPosition = m_Childs.size();
    
    // Insert the subwidget
    InsertSubwidget(_widget, insertPosition);
}

void HookGui::HGWidget::InsertSubwidget(HGWidget* _widget, int _atIndex)
{
    // Correct the index if it is out of bounds
    if(_atIndex > m_Childs.size())
    {
        _atIndex = m_Childs.size();
    }
    else if(_atIndex < 0)
    {
        _atIndex = 0;
    }
    
    // -> Delegate
    m_Delegate->WidgetWillAddSubwidget(_widget, _atIndex);
    
    // Insert the widget
    m_Childs.insert(m_Childs.begin() + _atIndex, _widget);
    
    // -> Delegate
    m_Delegate->WidgetDidAddSubwidget(_widget, _atIndex);
}

bool HookGui::HGWidget::ExchangeSubwidget(int _fromIndex, int _toIndex)
{
    // -> Delegate
//    m_Delegate->WidgetWillAddSubwidget(_widget, _toIndex);
    
    // -> Delegate
//    m_Delegate->WidgetDidAddSubwidget();
    
    return true;
}

void HookGui::HGWidget::RemoveSubwidget(HGWidget* _widget)
{
    // Get the remove position
    int removePosition = m_Childs.size();
    
    // -> Delegate
    m_Delegate->WidgetWillRemoveSubwidget(_widget, removePosition);
    
    // -> Delegate
    m_Delegate->WidgetDidRemoveSubwidget(_widget, removePosition);
}

void HookGui::HGWidget::RemoveSubwidgetFromIndex(int _fromIndex)
{

}

void HookGui::HGWidget::AddToSuperwidget(HGWidget* _widget)
{
    // Add to the parent child list
    AddSubwidget(_widget);
    
    // Set the parent
    m_Parent = _widget;
}

void HookGui::HGWidget::RemoveFromSuperwidget()
{
    // Remove from the parent
    m_Parent->RemoveSubwidget(this);
    
    // Set a null parent
    m_Parent = nullptr;
}

bool HookGui::HGWidget::EvaluateInput(HookGui::HGInputCommand _inputCommand)
{
	std::cout << "Widget received input!" << std::endl;

	return false;
}

HookGui::HGImage* HookGui::HGWidget::GetImage()
{
	return &m_Image;
}

bool HookGui::HGWidget::IsDescendant(HGWidget* _widget)
{
    // Compare the widgets
    if(_widget == this)
    {
        return true;
    }
    
    // For each child
    for(auto child : m_Childs)
    {
        // Check if is descendant
        if(IsDescendant(child))
        {
            return true;
        }
    }
    
    return false;
}

bool HookGui::HGWidget::IsValid()
{
	// Check if the image is valid
	if (!m_Image.IsValid())
	{
		return false;
	}

	return true;
}

bool HookGui::HGWidget::IsFocused()
{
    return false;
}

void HookGui::HGWidget::SetDelegate(HGWidgetDelegate* _delegate)
{
    m_Delegate = _delegate;
}

HookGui::HGWidget* HookGui::HGWidget::FindPointTarget(HookGui::Point _point)
{
    // First check if the point is inside this widget
    if(!m_CurrentFrame.PointIsInside(_point.x, _point.y))
    {
        return nullptr;
    }
    
    // Set the current widget
    HookGui::HGWidget* currentWidget = this;
    
    // Go until we break
    while(true)
    {
        // Set target found to false
        bool targetFound = false;
        
        // For each child
        for(auto child : currentWidget->m_Childs)
        {
            // Check if this child contains the point
            if(ContainPoint(_point))
            {
                // Set the new current widget
                currentWidget = child;
                
                // Set target found
                targetFound = true;
                
                break;
            }
        }
        
        // Check if we found a target this round
        if(targetFound)
        {
            // Ok we need to check the current view childs
            continue;
        }
        else
        {
            // We can return the current widget without problems
            break;
        }
    }
    
    return currentWidget;
}

// Check if the given point is inside our frame
bool HookGui::HGWidget::ContainPoint(HookGui::Point _point)
{
    return m_CurrentFrame.PointIsInside(_point.x, _point.y);
}

glm::mat4 HookGui::HGWidget::GetTransformMatrix()
{
	// Get our frame
	HGFrame frame = m_CurrentFrame;

	// Set the position, scale and rotation
	glm::vec3 position = glm::vec3(frame.x, frame.y, 0);
	glm::vec3 scale = glm::vec3(frame.width, frame.height, 1);
	glm::vec3 rotation = glm::vec3(0, 0, 0);

	// Create the transform matrix
	glm::mat4 transformMatrix = glm::mat4();

	// Scale the transform matrix
	transformMatrix = glm::scale(transformMatrix, scale);

	// Rotate the transform matrix
	transformMatrix = glm::rotate(transformMatrix, rotation.x, glm::vec3(1, 0, 0));
	transformMatrix = glm::rotate(transformMatrix, rotation.y, glm::vec3(1, 1, 0));
	transformMatrix = glm::rotate(transformMatrix, rotation.z, glm::vec3(1, 0, 1));

	// Translate the transform matrix
	transformMatrix = glm::translate(transformMatrix, position);

	return transformMatrix;
}

const std::vector<HookGui::HGWidget*>& HookGui::HGWidget::GetChildArray()
{
	return m_Childs;
}