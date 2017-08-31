/*!-----------------------------------------------------------------------
@file	ファイル名
@brief	ファイル説明
@date	作成/更新した日付
------------------------------------------------------------------------*/
#pragma once

/*------------------------------------------------------------------------
//インクルード
------------------------------------------------------------------------*/
#include "../../Library/Application/Win32/WindowWin32/WindowWin32.h"

namespace d3d11application
{
	/*!-----------------------------------------------------------------------
	@class	クラス名
	@brief	クラス説明
	@date	作成/更新した日付
	------------------------------------------------------------------------*/
	class D3D11Window
		: public application::win32::WindowWin32
	{
		/*------------------------------------------------------------------------
		//メンバ変数
		------------------------------------------------------------------------*/
	private:

		/*------------------------------------------------------------------------
		//publicメンバ関数
		------------------------------------------------------------------------*/
	public:
		D3D11Window(
			application::win32::ApplicationWin32&	_applicationWin32,
			int										_nCmdShow,
			application::WindowSetting				_windowSetting) 
			: application::win32::WindowWin32(_applicationWin32, _nCmdShow, _windowSetting)
		{

		}

		/*!-----------------------------------------------------------------------
		@fn			関数名
		@brief		関数説明
		@param[in]	引数名			引数の説明
		@param[out]	引数(出力)名	引数(出力)の説明
		@return		戻り値の説明
		@exeption	例外の説明
		@date		作成/更新した日付
		------------------------------------------------------------------------*/
		LRESULT WindowProcedur(
			HWND	_hWnd,
			UINT	_message,
			WPARAM	_wParam,
			LPARAM	_lParam) override
		{
			switch (_message)
			{
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
				
			default:
				break;
			}

			return DefWindowProc(_hWnd, _message, _wParam, _lParam);
		}

		/*------------------------------------------------------------------------
		//privateメンバ関数
		------------------------------------------------------------------------*/
	private:

	};	//D3D11Window
}	// d3d11application