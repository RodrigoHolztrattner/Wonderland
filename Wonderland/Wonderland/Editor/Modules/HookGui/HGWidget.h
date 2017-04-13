////////////////////////////////////////////////////////////////////////////////
// Filename: HGWidget.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

//////////////
// INCLUDES //
//////////////
#include "UIDef.h"
#include "HGImage.h"
#include "ReferenceCounter.h"
#include <vector>
#include <string>

#include "Widget\HGFrameComponent.h"
#include "HGInputDispatcher.h"

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
    - Itens obrigatórios do HGWidget (e separação dos mesmos em classes com suas funcionalidades)
    - Contagem de referência e forma de referenciar uma instancia com verificação
    - Definições das funções básicas (em andamento...)
 
 
 
 
 
 */

/*
	=> Pontos para pensar/criar:

		- Não é melhor usar um modelo de shader mais genérico? Afinal assim estamos limitado à um "Renderable" que pode ser criado de qualquer forma
		externamente, acho que devemos dar mais suporte ao shader/material, lembrando também que um objeto pode usar mais de um shader/material, ter
		multiplos passos, etc...
		- Criar um renderable aqui?
		- Devemos pensar em como multiplos passos seriam implementados, os shaders precisam de uma ordem para serem executados, etc etc (talvez não pensar nisso agora)

		- Widgets devem poder serem criados diretamente sem usar um manager.
		- Podemos adotar que são single thread.
		- Devemos criar um objeto UIImage que será uma textura.
		- Cada widget suporta ter uma UIImage, senão usará uma default criada pelo sistema.
		- Cada widget possui um Renderable, o model deverá ser ajustado automaticamente e a textura depende da UIImage.
*/

////////////////
// FORWARDING //
////////////////

class HGWidgetDelegate;
class HGWidget;
class HGWidgetController;

////////////////////////////////////////////////////////////////////////////////
// Class name: WidgetDelegate
////////////////////////////////////////////////////////////////////////////////
class HGWidgetDelegate
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
    virtual void WidgetWillAddSubwidget(HGWidget* _widget, int _atIndex){}
    virtual void WidgetDidAddSubwidget(HGWidget* _widget, int _atIndex){}
    virtual void WidgetWillRemoveSubwidget(HGWidget* _widget, int _atIndex){}
    virtual void WidgetDidRemoveSubwidget(HGWidget* _widget, int _atIndex){}
    
    // Change the current controller
    virtual void WidgetWillMoveToController(HookGui::HGWidgetController* _widgetController){}
    virtual void WidgetDidMoveToController(HookGui::HGWidgetController* _widgetController){}
    
    // Change controller virtual calls
    virtual void WidgetWillChangeController(){}
    virtual void WidgetDidChangeController(){}
    
    // On "..." events
    virtual void OnFocus(){}
    virtual void OnChangeLayout(HookGui::HGFrame _newFrame){};
    virtual void OnCommandEvent(){};
};

////////////////////////////////////////////////////////////////////////////////
// Class name: HGWidget
////////////////////////////////////////////////////////////////////////////////
class HGWidget : public ReferenceCounter, public HGWidgetDelegate, public HGFrameComponent
{
public:

//////////////////
// CONSTRUCTORS //
public: //////////

	// Constructor / destructor
	HGWidget();
	~HGWidget();
 
////////////////////
// INITIALIZATION //
public: ////////////
    
    // Initialize the widget
    virtual bool Initialize();

	// Update this widget
	virtual void Update(float _timeElapsed);

	// Return the identifier
	uint32_t GetIdentifier() { return m_Handle; }
    
///////////////
// SUBWIDGET //
public: ///////
    
    // Subwidget management
    void AddSubwidget(HGWidget* _widget);
    void InsertSubwidget(HGWidget* _widget, int _atIndex);
    bool ExchangeSubwidget(int _fromIndex, int _toIndex);
    void RemoveSubwidget(HGWidget* _widget);
    void RemoveSubwidgetFromIndex(int _fromIndex);
    
/////////////////
// SUPERWIDGET //
public: /////////
    
    // Add/remove this widget to a super widget (parent)
    void AddToSuperwidget(HGWidget* _widget);
    void RemoveFromSuperwidget();
    
///////////
// FRAME //
public: ///

///////////
// INPUT //
public: ///

	// Process input
	virtual bool EvaluateInput(HGInputCommand _inputCommand);

///////////
// IMAGE //
public: ///

	// Return the image
	HGImage* GetImage();
    
///////////
// UTILS //
public: ///

	// If this widget is valid to be used
	bool IsValid();
    
    // Check if the current widget is descendant of the given widget
    bool IsDescendant(HGWidget* _widget);
    
    // Return is the current widget is on focus
    virtual bool IsFocused();
    
    // Set the delegate
    void SetDelegate(HGWidgetDelegate* _delegate);

    // Find the widget (child widget) that contains the given point
    HGWidget* FindPointTarget(HookGui::Point _point);
    
    // Check if the given point is inside our frame
    bool ContainPoint(HookGui::Point _point);

	// Return the widget transform matrix
	glm::mat4 GetTransformMatrix();

	// Return the child array reference
	const std::vector<HookGui::HGWidget*>& GetChildArray();

	// Set/return our controller variables
	void IsHidden(bool _status) { m_IsHidden = _status; }
	bool IsHidden() { return m_IsHidden; }
	void CanInteract(bool _status) { m_CanInteract = _status; }
	bool CanInteract() { return m_CanInteract; }
	void CanReceiveInput(bool _status) { m_CanReceiveInput = _status; }
	bool CanReceiveInput() { return m_CanReceiveInput; }
	void CanBeRendered(bool _status) { m_CanBeRendered = _status; }
	bool CanBeRendered() { return m_CanBeRendered; }
	
private:
    
    // The destroy call
    virtual void DestroyWarning(){};
    
///////////////
// VARIABLES //
private: //////
    
    // The handle
    uint32_t m_Handle;

    // The parent
    HGWidget* m_Parent;

    // The widget delegate (self at initialization)
	HGWidgetDelegate* m_Delegate;

    // The childs
    std::vector<HGWidget*> m_Childs;
    
    // The bounded widget controller (UIWindow)
    HookGui::HGWidgetController* m_BoundedWidgetController;

	// The widget image
	HookGui::HGImage m_Image;
    
    // Controllers
    bool m_IsHidden;
    bool m_ClipToBound;
    bool m_CanInteract;
	bool m_CanReceiveInput;
    bool m_AutoresizeChilds;
	bool m_CanBeRendered;
};

// HookGui workspace
NamespaceEnd(HookGui)
