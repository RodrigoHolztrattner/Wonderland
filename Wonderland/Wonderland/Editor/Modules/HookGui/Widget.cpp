////////////////////////////////////////////////////////////////////////////////
// Filename: FluxWidget.cpp
////////////////////////////////////////////////////////////////////////////////
#include "Widget.h"

HookGui::Widget::Widget()
{
	// Set the initial data
    m_Delegate = this;
    m_Parent = nullptr;
    m_BoundedWidgetController = nullptr;
    // m_Tag = -1; // Request new tag
    m_IsHidden = false;
    m_ClipToBound = true;
    m_CanInteract = true;
    m_AutoresizeChilds = true;
}

HookGui::Widget::~Widget()
{
}

bool HookGui::Widget::Initialize()
{
    return true;
}

void HookGui::Widget::AddSubwidget(Widget* _widget)
{
    // Get the insert position
    int insertPosition = m_Childs.size();
    
    // Insert the subwidget
    InsertSubwidget(_widget, insertPosition);
}

void HookGui::Widget::InsertSubwidget(Widget* _widget, int _atIndex)
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

bool HookGui::Widget::ExchangeSubwidget(int _fromIndex, int _toIndex)
{
    // -> Delegate
//    m_Delegate->WidgetWillAddSubwidget(_widget, _toIndex);
    
    // -> Delegate
//    m_Delegate->WidgetDidAddSubwidget();
    
    return true;
}

void HookGui::Widget::RemoveSubwidget(Widget* _widget)
{
    // Get the remove position
    int removePosition = m_Childs.size();
    
    // -> Delegate
    m_Delegate->WidgetWillRemoveSubwidget(_widget, removePosition);
    
    // -> Delegate
    m_Delegate->WidgetDidRemoveSubwidget(_widget, removePosition);
}

void HookGui::Widget::RemoveSubwidgetFromIndex(int _fromIndex)
{

}

void HookGui::Widget::AddToSuperwidget(Widget* _widget)
{
    // Add to the parent child list
    AddSubwidget(_widget);
    
    // Set the parent
    m_Parent = _widget;
}

void HookGui::Widget::RemoveFromSuperwidget()
{
    // Remove from the parent
    m_Parent->RemoveSubwidget(this);
    
    // Set a null parent
    m_Parent = nullptr;
}

void HookGui::Widget::SetFrame(HookGui::Frame _newFrame)
{
    // -> Delegate
    m_Delegate->OnChangeLayout(_newFrame);
    
    // Set the new frame
    m_FrameHolder.ChangeFrame(_newFrame);
}

HookGui::Frame HookGui::Widget::GetFrame()
{
    return m_FrameHolder.GetFrame();
}

bool HookGui::Widget::IsDescendant(Widget* _widget)
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

bool HookGui::Widget::IsFocused()
{
    return false;
}

void HookGui::Widget::SetDelegate(WidgetDelegate* _delegate)
{
    m_Delegate = _delegate;
}

HookGui::Widget* HookGui::Widget::FindPointTarget(HookGui::Point _point)
{
    // First check if the point is inside this widget
    if(!m_FrameHolder.PointIsInside(_point.x, _point.y))
    {
        return nullptr;
    }
    
    // Set the current widget
    HookGui::Widget* currentWidget = this;
    
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
bool HookGui::Widget::ContainPoint(HookGui::Point _point)
{
    return m_FrameHolder.PointIsInside(_point.x, _point.y);
}
