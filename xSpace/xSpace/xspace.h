#pragma once

[Windows::Foundation::Metadata::WebHostHiddenAttribute]
ref class xspace sealed : public Windows::ApplicationModel::Core::IFrameworkView
{
public:
	xspace();
	
	// IFrameworkView methods.
	virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView^ applicationView);
	virtual void SetWindow(Windows::UI::Core::CoreWindow^ window);
	virtual void Load(Platform::String^ entryPoint);
	virtual void Run();
	virtual void Uninitialize();

private:
	bool m_visible;
};

[Windows::Foundation::Metadata::WebHostHiddenAttribute]
ref class Direct3DApplicationSource sealed : Windows::ApplicationModel::Core::IFrameworkViewSource
{
public:
	virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView();
};