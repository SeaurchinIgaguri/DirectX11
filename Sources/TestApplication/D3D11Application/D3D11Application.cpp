#include "D3D11Application.h"

namespace d3d11application
{
	D3D11Application::D3D11Application(
		const::HINSTANCE &				_hInstance,
		int								_nCmdShow,
		application::ApplicationSetting _applicationSetting)
		: application::win32::ApplicationWin32(_hInstance, _nCmdShow, _applicationSetting)
		, d3d11WindowSetting("D3D11Window", 800, 600)
		, d3d11Window_(*this, _nCmdShow, d3d11WindowSetting)
	{
		pGraphicDevice_		= std::make_unique<graphics::d3d11::GraphicDeviceD3D11>();
		pGraphicContext_	= std::make_unique<graphics::d3d11::GraphicContextD3D11>(pGraphicDevice_->GetDeviceContextShared());

		pSwapChain_			= utility::make_com_unique(
			pGraphicDevice_->CreateIDXGISwapChain(d3d11Window_.GetWindowHandle(), true, true));

		pRenderTargetView_	= utility::make_com_unique(
			pGraphicDevice_->CreateID3D11RenderTargetView(*pSwapChain_));

		pTestShader_ = std::make_unique<TestShaderD3D11>(*pGraphicDevice_);

		pGraphicContext_->SetViewport(
			static_cast<float>(d3d11WindowSetting.width),
			static_cast<float>(d3d11WindowSetting.height),
			0.0f,
			1.0f);


		TestVertex testVertices[3] = {
			0.0f, 0.5f, 1.0f,
			0.5f, -0.5f, 1.0f,
			-0.5f, -0.5f, 1.0f,
		};

		pTestVertexBuffer = 
			std::make_unique<graphics::d3d11::BufferD3D11>(
				pGraphicDevice_->GetDevice(),
				pGraphicDevice_->GetDeviceContextWeak(),
				testVertices, 
				sizeof(testVertices), 
				D3D11_USAGE_DEFAULT, 
				D3D11_BIND_VERTEX_BUFFER);
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
		auto pID3D11DeviceContext = pGraphicContext_->GetID3D11DeviceContext();

		float clearColor[] = { 0.0f, 0.0f, 1.0f, 0.0f };

		pGraphicContext_->SetRenderTarget(1, pRenderTargetView_.get(), nullptr);

		pID3D11DeviceContext->ClearRenderTargetView(pRenderTargetView_.get(), clearColor);

		ID3D11Buffer* pBuffers[] = { pTestVertexBuffer->GetBuffer() };
		unsigned int strides[] = { sizeof(TestVertex) };
		unsigned int offsets[] = { 0 };

		pID3D11DeviceContext->IASetVertexBuffers(0, 1, pBuffers, strides, offsets);
		pID3D11DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		pTestShader_->Begin(*pGraphicContext_);

		pID3D11DeviceContext->Draw(3, 0);

		pSwapChain_->Present(0, 0);
	}
}