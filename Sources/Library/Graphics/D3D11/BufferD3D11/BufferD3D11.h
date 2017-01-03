#pragma once

#include <d3d11.h>

#include "../../../Utility/COMPointer.h"

namespace graphics
{
	namespace d3d11
	{
		class BufferD3D11
		{
			BufferD3D11(
				ID3D11Device*						pDevice,
				std::weak_ptr<ID3D11DeviceContext>	pDeviceContext,
				std::size_t							size,
				D3D11_USAGE							bufferUsage,
				D3D11_BIND_FLAG						bindFlag);

			BufferD3D11(
				ID3D11Device*						pDevice,
				std::weak_ptr<ID3D11DeviceContext>	pDeviceContext,
				const void*							sourceData,
				std::size_t							size,
				D3D11_USAGE							bufferUsage,
				D3D11_BIND_FLAG						bindFlag);

			//@Todo ‚ ‚Æ‚Å‚Â‚­‚é
			/*void GetData(
				std::size_t offset,
				void*		dest,
				std::size_t	size);

			void SetData();*/

			ID3D11Buffer* GetBuffer() const
			{
				return pBuffer_.get();
			}

		private:
			ID3D11Buffer* CreateBuffer(
				ID3D11Device*						pDevice,
				const void*							sourceData,
				std::size_t							size,
				D3D11_USAGE							bufferUsage,
				D3D11_BIND_FLAG						bindFlag);

		private:
			utility::com_unique_ptr<ID3D11Buffer>	pBuffer_;
			std::weak_ptr<ID3D11DeviceContext>		pDeviceContext_;

		};

	}	// namespace graphics
}	// namespace graphics