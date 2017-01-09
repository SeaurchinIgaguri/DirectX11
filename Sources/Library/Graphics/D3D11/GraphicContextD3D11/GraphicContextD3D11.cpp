#include "GraphicContextD3D11.h"
#include "../ShaderD3D11/ShaderD3D11.h"

namespace graphics
{
	namespace d3d11
	{
		GraphicContextD3D11::GraphicContextD3D11(std::shared_ptr<ID3D11DeviceContext>	_pDeviceContext)
			: pDeviceContext_(_pDeviceContext)
		{
			
		}

		void GraphicContextD3D11::SetRenderTarget(unsigned int _numViews,ID3D11RenderTargetView* _pID3D11RenderTargetView, ID3D11DepthStencilView* _pID3D11DepthStencilView)
		{
			pDeviceContext_->OMSetRenderTargets(_numViews, &_pID3D11RenderTargetView, _pID3D11DepthStencilView);
		}

		//void GraphicContextD3D11::SetShader(ShaderD3D11& _shader)
		//{
		//	//_shader.Begin(*this);
		//}

		void GraphicContextD3D11::SetShader(ID3D11VertexShader* _pVertexShader)
		{
			pDeviceContext_->VSSetShader(_pVertexShader, nullptr, 0);
		}

		void GraphicContextD3D11::SetShader(ID3D11PixelShader* _pPixelShader)
		{
			pDeviceContext_->PSSetShader(_pPixelShader, nullptr, 0);
		}

		void GraphicContextD3D11::SetViewport(float _width, float _height, float _minDepth, float _maxDepth)
		{
			D3D11_VIEWPORT vp;

			vp.Width	= _width;
			vp.Height	= _height;
			vp.MinDepth = _minDepth;
			vp.MaxDepth = _maxDepth;
			vp.TopLeftX = 0;
			vp.TopLeftY = 0;

			pDeviceContext_->RSSetViewports(1, &vp);
		}

		void GraphicContextD3D11::SetInputLayout(ID3D11InputLayout * pInputLayout)
		{
			pDeviceContext_->IASetInputLayout(pInputLayout);
		}

		ID3D11DeviceContext * GraphicContextD3D11::GetID3D11DeviceContext()
		{
			return pDeviceContext_.get();
		}

	}	// d3d11
}	// graphics