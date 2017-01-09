#include "D3D11Application.h"

namespace d3d11application
{
	D3D11Application::D3D11Application(
		const::HINSTANCE &				_hInstance,
		int								_nCmdShow,
		application::ApplicationSetting _applicationSetting)
		: d3d11WindowSetting("D3D11Window", 800, 600)
		, application::win32::ApplicationWin32(_hInstance, _nCmdShow, _applicationSetting)
		, d3d11Window_(*this, d3d11WindowSetting)
		, graphicContext_(graphicDevice_.GetDeviceContextShared())
		, testShader_(graphicDevice_)
		//, testVertices_(graphicDevice_.GetDevice(), graphicDevice_.GetDeviceContextWeak(),)
	{
		::ShowWindow(d3d11Window_.GetWindowHandle(), _nCmdShow);

		graphicContext_.SetViewport(
			static_cast<float>(d3d11WindowSetting.width), 
			static_cast<float>(d3d11WindowSetting.height), 
			0.0f, 
			1.0f);

		pSwapChain_			= utility::make_com_unique(
			graphicDevice_.CreateIDXGISwapChain(d3d11Window_.GetWindowHandle(), true));

		pRenderTargetView_	= utility::make_com_unique(
			graphicDevice_.CreateID3D11RenderTargetView(*pSwapChain_));

		DXGI_FORMAT depthStencilFormat = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;

		pDepthStencilTexture_ = utility::make_com_unique(
			graphicDevice_.CreateID3D11Texture2D(
				static_cast<float>(d3d11WindowSetting.width),
				static_cast<float>(d3d11WindowSetting.height), 
				depthStencilFormat,
				1,
				0,
				//(D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE),
				D3D11_BIND_DEPTH_STENCIL,
				1));

		pDepthStencilView_ = utility::make_com_unique(
			graphicDevice_.CreateID3D11DepthStencilView(
				depthStencilFormat,
				D3D11_DSV_DIMENSION_TEXTURE2DMS,
				pDepthStencilTexture_.get()));

		graphicContext_.SetRenderTarget(1 ,pRenderTargetView_.get(), pDepthStencilView_.get());	
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
		auto pD3D11DeviceContext = graphicContext_.GetID3D11DeviceContext();

		float clearColor[] = { 0.0f, 0.0f, 1.0f, 0.0f };

		pD3D11DeviceContext->ClearRenderTargetView(pRenderTargetView_.get(), clearColor);
		pD3D11DeviceContext->ClearDepthStencilView(pDepthStencilView_.get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

		pSwapChain_->Present(0, 0);
	}
}