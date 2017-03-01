#pragma once

#include <array>
#include "../../Library/Graphics/D3D11/ShaderD3D11/ShaderD3D11.h"
#include "../../Library/Graphics/D3D11/GraphicDeviceD3D11/GraphicDeviceD3D11.h"
#include "../../Library/Graphics/D3D11/GraphicContextD3D11/GraphicContextD3D11.h"
#include "../../Library/Graphics/ShaderCompiler/ShaderCompilerHLSL/ShaderCompilerHLSL.h"

namespace d3d11application
{
	class TestShaderD3D11 : public graphics::d3d11::ShaderD3D11
	{
	public:
		TestShaderD3D11(graphics::d3d11::GraphicDeviceD3D11& _graphicDevice)
		{
			auto pShaderBinaryCode = graphics::shadercompiler::LoadFromCSO("Resources/Shader/VertexShader.cso");

			pVertexShader_	= utility::make_com_unique(_graphicDevice.CreateID3D11VertexShader(*pShaderBinaryCode.get()));
			pPixelShader_	= utility::make_com_unique(_graphicDevice.CreateID3D11PixelShader("Resources/Shader/PixelShader.cso"));

			constexpr std::array<D3D11_INPUT_ELEMENT_DESC, 1> inputElements = {
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			};

			pInputLayout_ = 
				utility::make_com_unique<ID3D11InputLayout>(
					_graphicDevice.CreateID3D11InputLayout<1>(
						inputElements, *pShaderBinaryCode));
		}

		void Begin(graphics::d3d11::GraphicContextD3D11& _graphicContext)
		{
			_graphicContext.ClearShaders();

			_graphicContext.SetShader(pVertexShader_.get());
			_graphicContext.SetShader(pPixelShader_.get());

			_graphicContext.SetInputLayout(pInputLayout_.get());
		}

	private:
		utility::com_unique_ptr<ID3D11VertexShader>		pVertexShader_;
		utility::com_unique_ptr<ID3D11PixelShader>		pPixelShader_;
		utility::com_unique_ptr<ID3D11InputLayout>		pInputLayout_;

	};
}