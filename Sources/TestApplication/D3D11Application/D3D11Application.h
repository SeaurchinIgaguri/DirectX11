/*!-----------------------------------------------------------------------
@file	ファイル名
@brief	ファイル説明
@date	作成/更新した日付
------------------------------------------------------------------------*/
#pragma once

/*------------------------------------------------------------------------
//インクルード
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
	@class	クラス名
	@brief	クラス説明
	@date	作成/更新した日付
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
		//メンバ変数
		------------------------------------------------------------------------*/
	private:
		application::WindowSetting d3d11WindowSetting;

		D3D11Window d3d11Window_;

		std::unique_ptr<graphics::d3d11::GraphicDeviceD3D11> 	pGraphicDevice_;
		std::unique_ptr<graphics::d3d11::GraphicContextD3D11>	pGraphicContext_;

		utility::com_unique_ptr<IDXGISwapChain>				pSwapChain_;
		utility::com_unique_ptr<ID3D11RenderTargetView>		pRenderTargetView_;

		std::unique_ptr<TestShaderD3D11>				pTestShader_;
		std::unique_ptr<graphics::d3d11::BufferD3D11>	pTestVertexBuffer;

		/*------------------------------------------------------------------------
		//publicメンバ関数
		------------------------------------------------------------------------*/
	public:		
		/*!-----------------------------------------------------------------------
		@fn			D3D11Application
		@brief		コンストラクタ
		@param[in]	引数名			引数の説明
		@param[out]	引数(出力)名	引数(出力)の説明
		@return		戻り値の説明
		@exeption	例外の説明
		@date		作成/更新した日付
		------------------------------------------------------------------------*/
		D3D11Application(
			const ::HINSTANCE&				_hInstance,
			int								_nCmdShow,
			application::ApplicationSetting	_applicationSetting);

		bool PeekMessageLoopCallback() override;

		/*------------------------------------------------------------------------
		//privateメンバ関数
		------------------------------------------------------------------------*/
	private:
		void Update();
		void Render();

	};		// D3D11Application
}		// d3d11application