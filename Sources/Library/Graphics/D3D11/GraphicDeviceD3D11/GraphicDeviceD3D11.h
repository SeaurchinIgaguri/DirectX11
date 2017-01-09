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
			std::shared_ptr<IDXGIDevice1>			pDXGIDevice_;		//!< DXGIデバイス
			std::shared_ptr<IDXGIAdapter>			pDXGIAdapter_;		//!< DXGIアダプター
			std::shared_ptr<IDXGIFactory>			pDXGIFactory_;		//!< DXGIファクトリー

			//utility::com_unique_ptr<ID3D11Texture2D>				pDefaultDepthStencil;
			//utility::com_unique_ptr<ID3D11DepthStencilView>			pDefaultDepthStencilView;

			D3D_DRIVER_TYPE		driverType_;		//!< D3Dドライバータイプ
			D3D_FEATURE_LEVEL	featureLevel_;		//!< D3Dフィーチャーレベル
			DXGI_SAMPLE_DESC	dxgiSampleDesc_;	//!< DXGIサンプル

		public:
			GraphicDeviceD3D11();

			//~GraphicDeviceD3D11();

			IDXGISwapChain* CreateIDXGISwapChain(
				HWND _hWnd,
				bool _isWindowMode);

			ID3D11RenderTargetView* CreateID3D11RenderTargetView(IDXGISwapChain& _swapChain);

			ID3D11Texture2D * CreateID3D11Texture2D(
				UINT							width,
				UINT							height, 
				DXGI_FORMAT						dxgiFormat, 
				UINT							count, 
				UINT							quality, 
				UINT							bindFlags, 
				UINT							mipmapLevels,
				D3D11_USAGE						usage			= D3D11_USAGE_DEFAULT,
				UINT							cpuAccessFlags	= 0, 
				UINT							miscFlags		= 0,
				const D3D11_SUBRESOURCE_DATA*	pInitialData	= nullptr);

			ID3D11DepthStencilView * CreateID3D11DepthStencilView(DXGI_FORMAT _dxgiFormat, D3D11_DSV_DIMENSION _d3d11DSVdimension, ID3D11Resource * _pResource);

			ID3D11VertexShader* CreateID3D11VertexShader(const std::string& _csoName);

			ID3D11VertexShader* CreateID3D11VertexShader(const ShaderBinaryCode& shaderBinaryCode);

			ID3D11PixelShader* CreateID3D11PixelShader(const std::string& _csoName);

			ID3D11Device* GetDevice() const;

			std::weak_ptr<ID3D11Device> GetDeviceWeak() const;

			std::shared_ptr<ID3D11Device> GetDeviceShared() const;

			ID3D11DeviceContext* GetDeviceContext() const;

			std::weak_ptr<ID3D11DeviceContext> GetDeviceContextWeak() const;

			std::shared_ptr<ID3D11DeviceContext> GetDeviceContextShared() const;

			IDXGIDevice1* GetDXGIDevice() const;

			IDXGIAdapter* GetDXGIAdapter() const;

		};	// GraphicDeviceD3D11
	}	// d3d11
}	// graphics