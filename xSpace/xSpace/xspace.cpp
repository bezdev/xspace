#include "xspace.h"

#define ASSERT(exp)

using namespace Windows::ApplicationModel::Activation;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::UI::Core;
using namespace Windows::Foundation;

[Platform::MTAThread]
int main(Platform::Array<Platform::String^>^)
{
	auto direct3DApplicationSource = ref new Direct3DApplicationSource();
	CoreApplication::Run(direct3DApplicationSource);

	return 0;
}

IFrameworkView^ Direct3DApplicationSource::CreateView()
{
    return ref new xspace();
}

xspace::xspace() :
	m_visible(true)
{
}

// First method called when IFrameworkView is created.
void xspace::Initialize(CoreApplicationView^ applicationView)
{
	// Register event handlers for app lifecycle.
	applicationView->Activated +=
        ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^>(
		[](Windows::ApplicationModel::Core::CoreApplicationView^ applicationView, Windows::ApplicationModel::Activation::IActivatedEventArgs^ args)
		{
			// Run() won't start until the CoreWindow is activated.
			CoreWindow::GetForCurrentThread()->Activate();
		});

	// initialize render object
}

// Set current window for the view.
void xspace::SetWindow(CoreWindow^ window)
{
	static bool setWindow = true;
	ASSERT(setWindow);

	// Register event handlers with the CoreWindow object.
	window->SizeChanged += 
        ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(
		[this](Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args)
		{
			// Notify the rendering controller to set up new swap chains (and so on).
		});
	window->VisibilityChanged +=
		ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^>(
		[this](CoreWindow^ sender, VisibilityChangedEventArgs^ args)
		{
			m_visible = sender->Visible;
		});

	// Add an event handler when the charms bar is activated.
	CoreWindow::GetForCurrentThread()->Activated += 
		ref new TypedEventHandler<CoreWindow^, WindowActivatedEventArgs^>(
		[this] (CoreWindow^ sender, Windows::UI::Core::WindowActivatedEventArgs^ args)
		{
			switch (args->WindowActivationState)
			{
			case Windows::UI::Core::CoreWindowActivationState::Deactivated:
				break;
			case CoreWindowActivationState::CodeActivated:
				break;
			case CoreWindowActivationState::PointerActivated:
				break;
			}
		});

	// Add event handlers to recognize input.
	window->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^>(
		[this](CoreWindow^ sender, KeyEventArgs^ args)
		{
			switch (args->VirtualKey)
			{
			case Windows::System::VirtualKey::Escape:
				break;
			default:
				break;
			}
		});
	window->PointerPressed += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^>(
		[this](CoreWindow^ sender, PointerEventArgs^ args)
		{
		});
	
	/*
	Future App Bar development.

	auto edgeGestures = Windows::UI::Input::EdgeGesture::GetForCurrentView();
	edgeGestures->Completed += ref new TypedEventHandler<Windows::UI::Input::EdgeGesture^, Windows::UI::Input::EdgeGestureEventArgs^>(
		[this](Windows::UI::Input::EdgeGesture^ gesture, Windows::UI::Input::EdgeGestureEventArgs^ args)
		{
			m_renderer.SwitchToSCBP();
			Windows::ApplicationModel::Core::CoreApplication::MainView->CoreWindow->Dispatcher->RunAsync(Windows::UI::Core::CoreDispatcherPriority::Normal,
			ref new DispatchedHandler(
			[this]()
			{
				Windows::UI::Xaml::Window::Current->Activate();
			}));
		});
	*/

	setWindow = false;
}

// Load any external resources before Run is called.
void xspace::Load(Platform::String^ entryPoint)
{
}

// This method is called after the window becomes active.
void xspace::Run()
{
	while (true)
	{
		if (m_visible)
		{
			// Process window events.
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);	
		
			// Update the timer.

			// Update Physics.

			// Render targets.
		}
		else
		{
			CoreWindow::GetForCurrentThread()->Dispatcher->ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);	
		}
	}
}

// Uninitialize the view.
// TODO: remove initialize event handlers.
// TODO: remove setwindow event handlers.
void xspace::Uninitialize()
{
}