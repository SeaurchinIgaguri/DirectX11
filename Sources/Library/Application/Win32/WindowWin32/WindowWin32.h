/*!-----------------------------------------------------------------------
@file	WindowWin32.h
@brief	WindowWin32宣言部
@date	2017/08/16 作成
------------------------------------------------------------------------*/
#pragma once

/*------------------------------------------------------------------------
//インクルード
------------------------------------------------------------------------*/
#include "../ApplicationWin32/ApplicationWin32.h"
#include "../../../Utility/NonCopyable.h"

namespace application
{
	/*!-----------------------------------------------------------------------
	@struct	WindowSetting
	@brief	ウィンドウの設定データ
	@date	2017/08/16 作成
	------------------------------------------------------------------------*/
	struct WindowSetting
	{
		std::string	windowName;		//!< ウィンドウ名
		int			width;			//!< ウィンドウ横幅
		int			height;			//!< ウィンドウ縦幅

		WindowSetting() {}

		WindowSetting(
			std::string _windowName,
			int			_width,
			int			_height)
		{
			windowName	= _windowName;
			width		= _width;
			height		= _height;
		}
	};

	namespace win32 
	{
		class ApplicationWin32;

		/*!-----------------------------------------------------------------------
		@class	WindowWin32
		@brief	ウィンドウの作成/更新
		@date	2017/08/16 作成
		------------------------------------------------------------------------*/
		class WindowWin32 
			: private utility::NonCopyable<WindowWin32>
		{
		protected:
			ApplicationWin32&		applicationWin32_;		//!< 親アプリケーション
			WindowSetting			windowSetting_;			//!< ウィンドウ設定
			HWND					hWnd_;					//!< ウィンドウハンドル

		public:

			/*!-----------------------------------------------------------------------
			@fn			WindowWin32
			@brief		コンストラクタ
			@param[in]	_applicationWin32		親アプリケーション
			@param[in]	_windowSetting			ウィンドウの設定
			@return		無し
			@exeption	CreateWindowExを失敗したときApplicationWin32Exeptionを投げる
			@date		2017/08/16 作成
			------------------------------------------------------------------------*/
			WindowWin32(
				ApplicationWin32&	_applicationWin32,
				WindowSetting		_windowSetting);

			/*!-----------------------------------------------------------------------
			@fn			WindowWin32
			@brief		コンストラクタ
			@param[in]	_applicationWin32		親アプリケーション
			@param[in]	_nCmdShow				ウィンドウ表示状態
			@param[in]	_windowSetting			ウィンドウの設定
			@return		無し
			@exeption	CreateWindowExを失敗したときApplicationWin32Exeptionを投げる
			@date		2017/08/16 作成
			------------------------------------------------------------------------*/
			WindowWin32(
				ApplicationWin32&	_applicationWin32,
				int					_nCmdShow,
				WindowSetting		_windowSetting);

			/*!-----------------------------------------------------------------------
			@fn			~WindowWin32
			@brief		デストラクタ
			@return		無し
			@exeption	無し
			@date		2017/08/16 作成
			------------------------------------------------------------------------*/
			virtual ~WindowWin32();

			/*!-----------------------------------------------------------------------
			@fn			WindowProcedur
			@brief		ウィンドウ別ウィンドウプロシージャ
						オーバーライドして使用
			@date		2017/08/16 作成
			------------------------------------------------------------------------*/
			virtual LRESULT WindowProcedur(
				HWND	_hWnd,
				UINT	_message,
				WPARAM	_wParam,
				LPARAM	_lParam)
			{
				return DefWindowProc(_hWnd, _message, _wParam, _lParam);
			}

			/*!-----------------------------------------------------------------------
			@fn			GetWindowHandle
			@brief		ウィンドウハンドルを取得
			@return		ウィンドウハンドル
			@exeption	無し
			@date		2017/08/16 作成
			------------------------------------------------------------------------*/
			HWND GetWindowHandle() const
			{
				return hWnd_;
			}

			UINT GetClientWidth()
			{
				RECT clientRect;
				GetClientRect(hWnd_, &clientRect);

				return clientRect.right - clientRect.left;
			}

			UINT GetClientHeight()
			{
				RECT clientRect;
				GetClientRect(hWnd_, &clientRect);

				return  clientRect.bottom - clientRect.top;
			}

		private:
			void _CreateWindow(
				ApplicationWin32&	_applicationWin32,
				WindowSetting		_windowSetting);
		};		// WindowWin32

	}	// win32
}	// apllication
