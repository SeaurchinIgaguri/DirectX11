#pragma once

#include <string>

namespace graphics
{
	enum class GraphicSystem
	{
		D3D9,
		D3D11,
	};

	enum class BufferType
	{
		Vertex,
		Index,
		Constant,
	};

	class ITexture;
	class IBuffer;
	class IShader;

	class IGraphicDevice
	{
		virtual ITexture* CreateTexture(std::string _textureFilePath)	= 0;

		virtual IBuffer* CreateBuffer(BufferType _bufferType)			= 0;

		virtual IShader* CreateShader(std::string _shaderFilePath)		= 0;
	};
}	// graphics