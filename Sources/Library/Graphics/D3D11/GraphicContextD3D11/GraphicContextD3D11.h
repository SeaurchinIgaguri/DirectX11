/*!-----------------------------------------------------------------------
@file	GraphicContextD3D11.h
@brief	GraphicContextD3D11クラス宣言部
@date	2016/08/20 作成
------------------------------------------------------------------------*/
#pragma once

/*------------------------------------------------------------------------
//インクルード
------------------------------------------------------------------------*/
#include "../GraphicDeviceD3D11/GraphicDeviceD3D11.h"
#include "../ShaderD3D11/ShaderD3D11.h"

namespace graphics
{
	namespace d3d11
	{
		/*!-----------------------------------------------------------------------
		@class	GraphicContextD3D11
		@brief	描画/設定処理を行う
		@date	2016/08/20 作成
		------------------------------------------------------------------------*/
		class GraphicContextD3D11
		{
			/*------------------------------------------------------------------------
			//publicメンバ関数
			------------------------------------------------------------------------*/
		public:

			/*!-----------------------------------------------------------------------
			@brief		コンストラクタ
			@param[in]	pDeviceContext			ID3D11DeviceContextのshared_ptr
			@date		2016/08/20 作成
			------------------------------------------------------------------------*/
			GraphicContextD3D11(
				std::shared_ptr<ID3D11DeviceContext> pDeviceContext);

			/*!-----------------------------------------------------------------------
			@brief		レンダーターゲットを設定
			@param[in]	pRenderTarget			設定するレンダーターゲットへのポインタ
			@date		2016/08/20 作成
			------------------------------------------------------------------------*/
			void SetRenderTarget(unsigned int _numViews, ID3D11RenderTargetView * _pID3D11RenderTargetView, ID3D11DepthStencilView * _pID3D11DepthStencilView);

			//void SetShader(ShaderD3D11& shader);

			void ClearShaders();

			/*!-----------------------------------------------------------------------
			@brief		頂点シェーダーを設定
			@param[in]	pVertexShader			設定する頂点シェーダへのポインタ
			@date		2016/08/20 作成
			------------------------------------------------------------------------*/
			void SetShader(ID3D11VertexShader* pVertexShader);

			/*!-----------------------------------------------------------------------
			@brief		ピクセルシェーダーを設定
			@param[in]	pVertexShader			設定する頂点シェーダへのポインタ
			@date		2016/08/20 作成
			------------------------------------------------------------------------*/
			void SetShader(ID3D11PixelShader* pPixelShader);

			/*!-----------------------------------------------------------------------
			@brief		ビューポートを設定
			@param[in]	width		横幅	
			@param[in]	height		縦幅
			@param[in]	minDepth	最低深度
			@param[in]	maxDepth	最高深度
			@date		2016/08/20 作成
			------------------------------------------------------------------------*/
			void SetViewport(float width, float height, float minDepth, float maxDepth);

			/*!-----------------------------------------------------------------------
			@brief		インプットレイアウトを設定
			@param[in]	pInputLayout			設定するインプットレイアウトへのポインタ
			------------------------------------------------------------------------*/
			void SetInputLayout(ID3D11InputLayout* pInputLayout);

			ID3D11DeviceContext* GetID3D11DeviceContext();

			/*------------------------------------------------------------------------
			//メンバ変数
			------------------------------------------------------------------------*/
		private:
			std::shared_ptr<ID3D11DeviceContext>	pDeviceContext_;	//!< D3D11デバイスコンテキスト

		};	// end of class GraphicContextD3D11


	}	// end of namespace d3d11
}	// end of namespace graphic