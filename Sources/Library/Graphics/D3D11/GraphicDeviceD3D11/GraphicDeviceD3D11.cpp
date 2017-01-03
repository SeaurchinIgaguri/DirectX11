#include "GraphicDeviceD3D11.h"

#include <array>
#include "../../ShaderCompiler/ShaderCompilerHLSL/ShaderCompilerHLSL.h"

namespace graphics
{
	namespace d3d11
	{
		GraphicDeviceD3D11::GraphicDeviceD3D11()
		{
			HRESULT hr					= S_OK;
			UINT	createDeviceFlags	= 0;

	#if defined(DEBUG) || defined(_DEBUG)

			createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;

	#endif

			// �h���C�o�[�^�C�v
			constexpr std::array<D3D_DRIVER_TYPE, 3> driverTypes = {
				D3D_DRIVER_TYPE_HARDWARE,
				D3D_DRIVER_TYPE_WARP,
				D3D_DRIVER_TYPE_REFERENCE,
			};

			// �@�\���x��
			constexpr std::array<D3D_FEATURE_LEVEL, 7> featureLevels = {
				D3D_FEATURE_LEVEL_11_1,
				D3D_FEATURE_LEVEL_11_0,
				D3D_FEATURE_LEVEL_10_1,
				D3D_FEATURE_LEVEL_10_0,
				D3D_FEATURE_LEVEL_9_3,
				D3D_FEATURE_LEVEL_9_2,
				D3D_FEATURE_LEVEL_9_1,
			};

			ID3D11Device*			pDevice;
			ID3D11DeviceContext*	pDeviceContext;

			// �f�o�C�X���쐬����
			for (const auto& driverType : driverTypes)
			{
				hr = D3D11CreateDevice(
					nullptr,
					driverType,
					nullptr,
					createDeviceFlags,
					featureLevels.data(),
					static_cast<UINT>(featureLevels.size()),
					D3D11_SDK_VERSION,
					&pDevice,
					&featureLevel_,
					&pDeviceContext);

				driverType_ = driverType;

				if (SUCCEEDED(hr)) 
				{
					pDevice_		= std::shared_ptr<ID3D11Device>(pDevice, utility::ComDeleter());
					pDeviceContext_ = std::shared_ptr<ID3D11DeviceContext>(pDeviceContext, utility::ComDeleter());

					break;
				}
			}

			try
			{
				if (FAILED(hr))
				{
					throw utility::Exeption("GraphicDviceD3D11", "GraphicDviceD3D11", "D3D11Device cant created");
				}
			}
			catch(utility::Exeption exeption)
			{
				throw exeption;
			}

			// �f�B�t�@�[�h�R���e�L�X�g�쐬
			ID3D11DeviceContext* pDeferredContext;

			hr = pDevice_->CreateDeferredContext(0, &pDeferredContext);

			try
			{
				if (FAILED(hr))
				{
					throw utility::Exeption("GraphicDviceD3D11", "GraphicDviceD3D11", "failed pDevice_->CreateDeferredContext");
				}
			}
			catch (utility::Exeption exeption)
			{
				throw exeption;
			}

			pDeferredContext_ = std::shared_ptr<ID3D11DeviceContext>(pDeferredContext, utility::ComDeleter());

			//DXGI������
			IDXGIDevice1* pDXGIDevice	= NULL;
			IDXGIAdapter* pDXGIAdapter	= NULL;
			IDXGIFactory* pDXGIFactory	= NULL;

			pDevice_->QueryInterface(__uuidof(IDXGIDevice1), (void**)&pDXGIDevice);
			pDXGIDevice->GetAdapter(&pDXGIAdapter);
			pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&pDXGIFactory);

			pDXGIDevice_	= std::shared_ptr<IDXGIDevice1>(pDXGIDevice,  utility::ComDeleter());
			pDXGIAdapter_	= std::shared_ptr<IDXGIAdapter>(pDXGIAdapter, utility::ComDeleter());
			pDXGIFactory_	= std::shared_ptr<IDXGIFactory>(pDXGIFactory, utility::ComDeleter());

			// �����Ŏg�p�ł���MSAA���`�F�b�N
			for (int i = 1; i <= D3D11_MAX_MULTISAMPLE_SAMPLE_COUNT; i <<= 1)
			{
				UINT Quality;

				if (SUCCEEDED(pDevice_->CheckMultisampleQualityLevels(DXGI_FORMAT_D24_UNORM_S8_UINT, i, &Quality)))
				{
					if (0 < Quality)
					{
						dxgiSampleDesc_.Count	= i;
						dxgiSampleDesc_.Quality	= Quality - 1;
					}
				}
			}
		}	// GraphicDeviceD3D11

		IDXGISwapChain* GraphicDeviceD3D11::CreateDXGISwapChain(
			HWND _hWnd,
			bool _isWindowMode)
		{
			HRESULT hr						= S_OK;
			IDXGISwapChain* pDXGISwapChain	= nullptr;

			// �E�B���h�E�T�C�Y���擾
			RECT rc;

			GetClientRect(_hWnd, &rc);
			UINT width	= rc.right	- rc.left;
			UINT height = rc.bottom - rc.top;

			// �X���b�v�`�F�C���̐ݒ�
			DXGI_SWAP_CHAIN_DESC sd;
			ZeroMemory(&sd, sizeof(sd));
			sd.BufferCount							= 1;
			sd.BufferDesc.Width						= width;
			sd.BufferDesc.Height					= height;
			sd.BufferDesc.Format					= DXGI_FORMAT_R8G8B8A8_UNORM;
			sd.BufferDesc.RefreshRate.Numerator		= 60;
			sd.BufferDesc.RefreshRate.Denominator	= 1;
			sd.BufferUsage							= DXGI_USAGE_RENDER_TARGET_OUTPUT;
			sd.OutputWindow							= _hWnd;
			sd.SampleDesc.Count						= 1;
			sd.SampleDesc.Quality					= 0;
			sd.SampleDesc							= dxgiSampleDesc_;
			sd.Windowed								= _isWindowMode;

			try
			{
				hr = pDXGIFactory_->CreateSwapChain(
					pDevice_.get(),
					&sd,
					&pDXGISwapChain);

				if (FAILED(hr))
				{
					throw utility::Exeption("GraphicDeviceD3D11", "CreateDXGISwapChain", "failed CreateSwapChain");
				}
			}
			catch (utility::Exeption exeption)
			{
				throw exeption;
			}

			return pDXGISwapChain;
		}

		ID3D11RenderTargetView* GraphicDeviceD3D11::CreateD3D11RenderTargetView(
			IDXGISwapChain& _swapChain)
		{
			HRESULT hr = S_OK;

			// �o�b�N�o�b�t�@�擾
			ID3D11Texture2D* pBackBuffer = nullptr;

			try
			{
				hr = _swapChain.GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&pBackBuffer);

				if (FAILED(hr))
				{
					throw utility::Exeption("GraphicDeviceD3D11", "CreateD3D11RenderTargetView", "Failed IDXGISwapChain.GetBuffer");
				}
			}
			catch (utility::Exeption exeption)
			{
				throw exeption;
			}
			
			// �����_�[�^�[�Q�b�g�r���[�𐶐�
			ID3D11RenderTargetView* pRenderTargetView = nullptr;

			try
			{
				hr = pDevice_->CreateRenderTargetView(pBackBuffer, NULL, &pRenderTargetView);

				pBackBuffer->Release();
				pBackBuffer = NULL;

				if (FAILED(hr))
				{
					throw utility::Exeption("GraphicDeviceD3D11", "CreateD3D11RenderTargetView", "Failed ID3D11Device.CreateRenderTargetView");
				}
			}
			catch (utility::Exeption exeption)
			{
				throw exeption;
			}
			
			return pRenderTargetView;
		}

		ID3D11VertexShader* GraphicDeviceD3D11::CreateD3D11VertexShader(const std::string& _csoPath)
		{
			auto				pShaderBinaryCode	= graphics::shadercompiler::LoadFromCSO(_csoPath);
			ID3D11VertexShader* pVertexShader		= nullptr;
			
			try
			{
				HRESULT hr = pDevice_->CreateVertexShader(
					pShaderBinaryCode->code.get(), 
					pShaderBinaryCode->size, 
					NULL, 
					&pVertexShader);

				if (FAILED(hr))
				{
					throw utility::Exeption("GraphicDeviceD3D11", "CreateD3D11VertexShader", "Failed ID3D11Device.CreateVertexShader");
				}
			}
			catch (utility::Exeption exeption)
			{
				throw exeption;
			}

			return pVertexShader;
		}

		ID3D11VertexShader* GraphicDeviceD3D11::CreateD3D11VertexShader(const ShaderBinaryCode& _shaderBinaryCode)
		{
			ID3D11VertexShader* pVertexShader = nullptr;

			try
			{
				HRESULT hr = pDevice_->CreateVertexShader(
					_shaderBinaryCode.code.get(),
					_shaderBinaryCode.size,
					NULL,
					&pVertexShader);

				if (FAILED(hr))
				{
					throw utility::Exeption("GraphicDeviceD3D11", "CreateD3D11VertexShader", "can not ID3D11Device.CreateVertexShader");
				}
			}
			catch (utility::Exeption exeption)
			{
				throw exeption;
			}

			return pVertexShader;
		}

		ID3D11PixelShader* GraphicDeviceD3D11::CreateD3D11PixelShader(const std::string& _csoPath)
		{
			auto				pShaderBinaryCode = graphics::shadercompiler::LoadFromCSO(_csoPath);
			ID3D11PixelShader*	pPixelShader = nullptr;

			try
			{
				HRESULT hr = pDevice_->CreatePixelShader(
					pShaderBinaryCode->code.get(),
					pShaderBinaryCode->size,
					NULL,
					&pPixelShader);

				if (FAILED(hr))
				{
					throw utility::Exeption("GraphicDeviceD3D11", "CreateD3D11VertexShader", "can not ID3D11Device.CreateVertexShader");
				}
			}
			catch (utility::Exeption exeption)
			{
				throw exeption;
			}

			return pPixelShader;
		}

		inline ID3D11Device * GraphicDeviceD3D11::GetDevice() const
		{
			return pDevice_.get();
		}

		inline std::weak_ptr<ID3D11Device> GraphicDeviceD3D11::GetDeviceWeak() const
		{
			return pDevice_;
		}

		inline std::shared_ptr<ID3D11Device> GraphicDeviceD3D11::GetDeviceShared() const
		{
			return pDevice_;
		}

		inline ID3D11DeviceContext * GraphicDeviceD3D11::GetDeviceContext() const
		{
			return pDeviceContext_.get();
		}

		inline std::weak_ptr<ID3D11DeviceContext> GraphicDeviceD3D11::GetDeviceContextWeak() const
		{
			return pDeviceContext_;
		}

		inline std::shared_ptr<ID3D11DeviceContext> GraphicDeviceD3D11::GetDeviceContextShared() const
		{
			return pDeviceContext_;
		}

		inline IDXGIDevice1 * GraphicDeviceD3D11::GetDXGIDevice() const
		{
			return pDXGIDevice_.get();
		}

		inline IDXGIAdapter * GraphicDeviceD3D11::GetDXGIAdapter() const
		{
			return pDXGIAdapter_.get();
		}

	}	// d3d11
}	// graphics