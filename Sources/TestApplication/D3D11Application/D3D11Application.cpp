#include "D3D11Application.h"

namespace d3d11application
{
	D3D11Application::D3D11Application(
		const::HINSTANCE &				_hInstance,
		int								_nCmdShow,
		application::ApplicationSetting _applicationSetting)
		: application::win32::ApplicationWin32(_hInstance, _nCmdShow, _applicationSetting)
		, d3d11window_(*this, application::WindowSetting("D3D11Window", 800, 600))
		, graphicContext_(graphicDevice_.GetDeviceContextShared())
		, testShader_(graphicDevice_)
	{
		::ShowWindow(d3d11window_.GetWindowHandle(), _nCmdShow);

		graphicContext_.SetViewport(800.0f, 600.0f, 0.0f, 1.0f);

		IDXGISwapChain*			pSwapChain		= graphicDevice_.CreateDXGISwapChain(d3d11window_.GetWindowHandle(), true);
		ID3D11RenderTargetView*	pRenderTarget	= graphicDevice_.CreateD3D11RenderTargetView(*pSwapChain);

		pSwapChain_.reset(pSwapChain);
		pRenderTarget_.reset(pRenderTarget);

		graphicContext_.SetRenderTarget(pRenderTarget_.get());	
	}

	bool D3D11Application::PeekMessageLoopCallback()
	{
		if (GetAsyncKeyState(VK_ESCAPE))
		{
			PostQuitMessage(0);
		}

		Update();
		Render();

		return true;
	}

	void D3D11Application::Update()
	{
		
	}

	void D3D11Application::Render()
	{

	}
}