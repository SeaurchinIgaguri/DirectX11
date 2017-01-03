/*!-----------------------------------------------------------------------
@file	GraphicContextD3D11.h
@brief	GraphicContextD3D11�N���X�錾��
@date	2016/08/20 �쐬
------------------------------------------------------------------------*/
#pragma once

/*------------------------------------------------------------------------
//�C���N���[�h
------------------------------------------------------------------------*/
#include "../GraphicDeviceD3D11/GraphicDeviceD3D11.h"
#include "../ShaderD3D11/ShaderD3D11.h"

namespace graphics
{
	namespace d3d11
	{
		/*!-----------------------------------------------------------------------
		@class	GraphicContextD3D11
		@brief	�`��/�ݒ菈�����s��
		@date	2016/08/20 �쐬
		------------------------------------------------------------------------*/
		class GraphicContextD3D11
		{
			/*------------------------------------------------------------------------
			//public�����o�֐�
			------------------------------------------------------------------------*/
		public:

			/*!-----------------------------------------------------------------------
			@brief		�R���X�g���N�^
			@param[in]	pDeviceContext			ID3D11DeviceContext��shared_ptr
			@date		2016/08/20 �쐬
			------------------------------------------------------------------------*/
			GraphicContextD3D11(
				std::shared_ptr<ID3D11DeviceContext> pDeviceContext);

			/*!-----------------------------------------------------------------------
			@brief		�����_�[�^�[�Q�b�g��ݒ�
			@param[in]	pRenderTarget			�ݒ肷�郌���_�[�^�[�Q�b�g�ւ̃|�C���^
			@date		2016/08/20 �쐬
			------------------------------------------------------------------------*/
			void SetRenderTarget(ID3D11RenderTargetView* pRenderTarget);

			//void SetShader(ShaderD3D11& shader);

			/*!-----------------------------------------------------------------------
			@brief		���_�V�F�[�_�[��ݒ�
			@param[in]	pVertexShader			�ݒ肷�钸�_�V�F�[�_�ւ̃|�C���^
			@date		2016/08/20 �쐬
			------------------------------------------------------------------------*/
			void SetShader(ID3D11VertexShader* pVertexShader);

			/*!-----------------------------------------------------------------------
			@brief		�s�N�Z���V�F�[�_�[��ݒ�
			@param[in]	pVertexShader			�ݒ肷�钸�_�V�F�[�_�ւ̃|�C���^
			@date		2016/08/20 �쐬
			------------------------------------------------------------------------*/
			void SetShader(ID3D11PixelShader* pPixelShader);

			/*!-----------------------------------------------------------------------
			@brief		�r���[�|�[�g��ݒ�
			@param[in]	width		����	
			@param[in]	height		�c��
			@param[in]	minDepth	�Œ�[�x
			@param[in]	maxDepth	�ō��[�x
			@date		2016/08/20 �쐬
			------------------------------------------------------------------------*/
			void SetViewport(float width, float height, float minDepth, float maxDepth);

			/*------------------------------------------------------------------------
			//�����o�ϐ�
			------------------------------------------------------------------------*/
		private:
			std::shared_ptr<ID3D11DeviceContext>	pDeviceContext_;	//!< D3D11�f�o�C�X�R���e�L�X�g

		};	// end of class GraphicContextD3D11


	}	// end of namespace d3d11
}	// end of namespace graphic