#include "BufferD3D11.h"

#include "../../../Utility/Exception.h"

namespace graphics
{
	namespace d3d11
	{
		BufferD3D11::BufferD3D11(
			ID3D11Device*						_pDevice,
			std::weak_ptr<ID3D11DeviceContext>	_pDeviceContext,
			std::size_t							_size,
			D3D11_USAGE							_bufferUsage,
			D3D11_BIND_FLAG						_bindFlag)
			: pDeviceContext_(_pDeviceContext)
		{
			pBuffer_.reset(CreateBuffer(_pDevice, nullptr, _size, _bufferUsage, _bindFlag));
		}

		BufferD3D11::BufferD3D11(
			ID3D11Device*						_pDevice,
			std::weak_ptr<ID3D11DeviceContext>	_pDeviceContext,
			const void*							_sourceData,
			std::size_t							_size,
			D3D11_USAGE							_bufferUsage,
			D3D11_BIND_FLAG						_bindFlag)
			: pDeviceContext_(_pDeviceContext)
		{
			pBuffer_.reset(CreateBuffer(_pDevice, _sourceData, _size, _bufferUsage, _bindFlag));
		}

		ID3D11Buffer* BufferD3D11::CreateBuffer(
			ID3D11Device*						_pDevice,
			const void*							_sourceData,
			std::size_t							_size,
			D3D11_USAGE							_bufferUsage,
			D3D11_BIND_FLAG						_bindFlag)
		{
			D3D11_BUFFER_DESC bufferDesc;

			bufferDesc.ByteWidth			= static_cast<::UINT>(_size);
			bufferDesc.BindFlags			= _bindFlag;
			bufferDesc.MiscFlags			= 0;
			bufferDesc.StructureByteStride	= 0;
			bufferDesc.Usage				= _bufferUsage;
			
			_bufferUsage == D3D11_USAGE_DYNAMIC
				? bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE
				: bufferDesc.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA subresourceData;

			subresourceData.pSysMem				= _sourceData;
			subresourceData.SysMemPitch			= 0;
			subresourceData.SysMemSlicePitch	= 0;

			auto pInitialData = (_sourceData != nullptr) ? &subresourceData : nullptr;

			ID3D11Buffer* pBuffer = nullptr;

			HRESULT hr = _pDevice->CreateBuffer(&bufferDesc, pInitialData, &pBuffer);

			if (FAILED(hr))
			{
				throw std::runtime_error("Failed to ID3D11Device::CreateBuffer");
			}

			return pBuffer;
		}
	}	// namespace d3d11
}	// namespace graphics