////////////////////////////////////////////////////////////////////////////////
// Filename: Widget.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIDef.h"
#include "Frame.h"
#include "ReferenceCounter.h"
#include <vector>
#include <string>

///////////////
// NAMESPACE //
///////////////

/////////////
// DEFINES //
/////////////

////////////
// GLOBAL //
////////////

///////////////
// NAMESPACE //
///////////////

// HookGui workspace
NamespaceBegin(HookGui)

/*
 
    - Sistema de autolayout
    - Formas de renderizacao (main, border, rounded border, etc...) (render components?)
    - Formas de callback, delegate, etc...
    - Itens obrigatórios do Widget (e separação dos mesmos em classes com suas funcionalidades)
    - Contagem de referência e forma de referenciar uma instancia com verificação
    - Definições das funções básicas (em andamento...)
 
 
 
 
 
 */

////////////////
// FORWARDING //
////////////////

class WidgetDelegate;
class Widget;
class WidgetController;

////////////////////////////////////////////////////////////////////////////////
// Class name: WidgetDelegate
////////////////////////////////////////////////////////////////////////////////
class WidgetDelegate
{
/////////////////////
// VIRTUAL METHODS //
public: /////////////
    
    // Load & appear virtual calls
    virtual void WidgetWillLoad(){};
    virtual void WidgetDidLoad(){};
    virtual void WidgetWillAppear(){};
    virtual void WidgetDidAppear(){};
    
    // Subview add & remove virtual calls
    virtual void WidgetWillAddSubwidget(Widget* _widget, int _atIndex){}
    virtual void WidgetDidAddSubwidget(Widget* _widget, int _atIndex){}
    virtual void WidgetWillRemoveSubwidget(Widget* _widget, int _atIndex){}
    virtual void WidgetDidRemoveSubwidget(Widget* _widget, int _atIndex){}
    
    // Change the current controller
    virtual void WidgetWillMoveToController(HookGui::WidgetController* _widgetController){}
    virtual void WidgetDidMoveToController(HookGui::WidgetController* _widgetController){}
    
    // Change controller virtual calls
    virtual void WidgetWillChangeController(){}
    virtual void WidgetDidChangeController(){}
    
    // On "..." events
    virtual void OnFocus(){}
    virtual void OnChangeLayout(HookGui::Frame _newFrame){};
    virtual void OnCommandEvent(){};
};

////////////////////////////////////////////////////////////////////////////////
// Class name: Widget
////////////////////////////////////////////////////////////////////////////////
class Widget : public ReferenceCounter, public WidgetDelegate
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	Widget();
	~Widget();
 
////////////////////
// INITIALIZATION //
public: ////////////
    
    // Initialize the widget
    virtual bool Initialize();
    
///////////////
// SUBWIDGET //
public: ///////
    
    // Subwidget management
    void AddSubwidget(Widget* _widget);
    void InsertSubwidget(Widget* _widget, int _atIndex);
    bool ExchangeSubwidget(int _fromIndex, int _toIndex);
    void RemoveSubwidget(Widget* _widget);
    void RemoveSubwidgetFromIndex(int _fromIndex);
    
/////////////////
// SUPERWIDGET //
public: /////////
    
    // Add/remove this widget to a super widget (parent)
    void AddToSuperwidget(Widget* _widget);
    void RemoveFromSuperwidget();
    
///////////
// FRAME //
public: ///
    
    // Set the frame
    void SetFrame(HookGui::Frame _newFrame);
    
    // Return the frame
    HookGui::Frame GetFrame();
    
///////////
// UTILS //
public: ///
    
    // Check if the current widget is descendant of the given widget
    bool IsDescendant(Widget* _widget);
    
    // Return is the current widget is on focus
    bool IsFocused();
    
    // Set the delegate
    void SetDelegate(WidgetDelegate* _delegate);

    // Find the widget (child widget) that contains the given point
    Widget* FindPointTarget(HookGui::Point _point);
    
    // Check if the given point is inside our frame
    bool ContainPoint(HookGui::Point _point);
    
private:
    
    // The destroy call
    virtual void DestroyWarning(){};
    
///////////////
// VARIABLES //
private: //////
    
    // The handle
    HookGui::Handle m_Handle;

    // The parent
    Widget* m_Parent;

    // The widget delegate (self at initialization)
    WidgetDelegate* m_Delegate;

    // The childs
    std::vector<Widget*> m_Childs;
    
    // The bounded widget controller (UIWindow)
    HookGui::WidgetController* m_BoundedWidgetController;
    
    // The frame holder
    HookGui::FrameHolder m_FrameHolder;
    
    // Controllers
    bool m_IsHidden;
    bool m_ClipToBound;
    bool m_CanInteract;
    bool m_AutoresizeChilds;
};

// HookGui workspace
NamespaceEnd(HookGui)
