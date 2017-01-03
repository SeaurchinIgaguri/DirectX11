#pragma once

#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")

#include <vector>
#include "../../../Utility/COMPointer.h"
#include "../../../Utility/Exception.h"
#include "../../ShaderBinaryCode.h"

namespace graphics
{
	namespace d3d11
	{
		class GraphicDeviceD3D11
		{
		private:
			std::shared_ptr<ID3D11Device>			pDevice_;			//!< D3D11デバイス
			std::shared_ptr<ID3D11DeviceContext>	pDeviceContext_;	//!< D3D11デバイスコンテキスト
			std::shared_ptr<ID3D11DeviceContext>	pDeferredContext_;	//!< D3D11ディファードコンテキスト
			std::shared_ptr<IDXGIDevice1>			pDXGIDevice_;		//!< DXGIデバイス
			std::shared_ptr<IDXGIAdapter>			pDXGIAdapter_;		//!< DXGIアダプター
			std::shared_ptr<IDXGIFactory>			pDXGIFactory_;		//!< DXGIファクトリー

			D3D_DRIVER_TYPE		driverType_;		//!< D3Dドライバータイプ
			D3D_FEATURE_LEVEL	featureLevel_;		//!< D3Dフィーチャーレベル
			DXGI_SAMPLE_DESC	dxgiSampleDesc_;	//!< DXGIサンプルデスク

		public:
			GraphicDeviceD3D11();

			//~GraphicDeviceD3D11();

			//void SetViewport(float _width, float _height, float _minDepth, float _maxDepth);

			IDXGISwapChain* CreateDXGISwapChain(
				HWND _hWnd,
				bool _isWindowMode);

			ID3D11RenderTargetView* CreateD3D11RenderTargetView(IDXGISwapChain& _swapChain);

			ID3D11VertexShader* CreateD3D11VertexShader(const std::string& _csoName);

			ID3D11VertexShader* CreateD3D11VertexShader(const ShaderBinaryCode& shaderBinaryCode);

			ID3D11PixelShader* CreateD3D11PixelShader(const std::string& _csoName);

			ID3D11Device* GetDevice() const;

			std::weak_ptr<ID3D11Device> GetDeviceWeak() const;

			std::shared_ptr<ID3D11Device> GetDeviceShared() const;

			ID3D11DeviceContext* GetDeviceContext() const;

			std::weak_ptr<ID3D11DeviceContext> GetDeviceContextWeak() const;

			std::shared_ptr<ID3D11DeviceContext> GetDeviceContextShared() const;

			ID3D11DeviceContext* GetDeferredContext() const;

			std::weak_ptr<ID3D11DeviceContext> GetDeferredContextWeak() const;

			std::shared_ptr<ID3D11DeviceContext> GetDeferredContextShared() const;

			IDXGIDevice1* GetDXGIDevice() const;

			IDXGIAdapter* GetDXGIAdapter() const;

		};	// GraphicDeviceD3D11
	}	// d3d11
}	// graphics