/*!-----------------------------------------------------------------------
@file	�t�@�C����
@brief	�t�@�C������
@date	�쐬/�X�V�������t
------------------------------------------------------------------------*/
#pragma once

/*------------------------------------------------------------------------
//�C���N���[�h
------------------------------------------------------------------------*/
#include "../../Library/Application/Win32/ApplicationWin32/ApplicationWin32.h"
#include "../D3D11Window/D3D11Window.h"
#include "../../Library/Graphics/D3D11/GraphicDeviceD3D11/GraphicDeviceD3D11.h"
#include "../../Library/Graphics/D3D11/GraphicContextD3D11/GraphicContextD3D11.h"
#include "../TestShader/TestShaderD3D11.h"
#include "../../Library/Graphics/D3D11/BufferD3D11/BufferD3D11.h"

namespace d3d11application
{
	/*!-----------------------------------------------------------------------
	@class	�N���X��
	@brief	�N���X����
	@date	�쐬/�X�V�������t
	------------------------------------------------------------------------*/
	class D3D11Application
		: public application::win32::ApplicationWin32
	{
	private:

		struct TestVertex 
		{
			float x, y, z;
		};

		/*------------------------------------------------------------------------
		//�����o�ϐ�
		------------------------------------------------------------------------*/
	private:
		application::WindowSetting d3d11WindowSetting;

		D3D11Window d3d11Window_;

		graphics::d3d11::GraphicDeviceD3D11		graphicDevice_;
		graphics::d3d11::GraphicContextD3D11	graphicContext_;

		utility::com_unique_ptr<IDXGISwapChain>				pSwapChain_;
		utility::com_unique_ptr<ID3D11RenderTargetView>		pRenderTargetView_;

		TestShaderD3D11									testShader_;
		std::unique_ptr<graphics::d3d11::BufferD3D11>	pTestVertexBuffer;

		/*------------------------------------------------------------------------
		//public�����o�֐�
		------------------------------------------------------------------------*/
	public:		
		/*!-----------------------------------------------------------------------
		@fn			D3D11Application
		@brief		�R���X�g���N�^
		@param[in]	������			�����̐���
		@param[out]	����(�o��)��	����(�o��)�̐���
		@return		�߂�l�̐���
		@exeption	��O�̐���
		@date		�쐬/�X�V�������t
		------------------------------------------------------------------------*/
		D3D11Application(
			const ::HINSTANCE&				_hInstance,
			int								_nCmdShow,
			application::ApplicationSetting	_applicationSetting);

		bool PeekMessageLoopCallback() override;

		/*------------------------------------------------------------------------
		//private�����o�֐�
		------------------------------------------------------------------------*/
	private:
		void Update();
		void Render();

	};		// D3D11Application
}		// d3d11application


/*------------------------------------------------------------------------
���̑��g������
@tparam		�e���v���[�g�^��	�e���v���[�g�̐���
@todo		���Ȃ���΂����Ȃ����̐���
------------------------------------------------------------------------*/