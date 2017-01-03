/*!-----------------------------------------------------------------------
@file	ApplicationWin32.h
@brief	Win32アプリケーションラッパークラス
@date	2017/08/16 作成
------------------------------------------------------------------------*/
#pragma once

/*------------------------------------------------------------------------
//インクルード
------------------------------------------------------------------------*/
#include <Windows.h>
#include <memory>
#include <unordered_map>
#include <string>
//#include <cassert>

#include "../../../Utility/Exception.h"
#include "../../../Utility/NonCopyable.h"

class WindowWin32;

namespace application
{
	/*!-----------------------------------------------------------------------
	@struct	ApplicationSetting
	@brief	アプリケーションの設定データ
	@date	2017/08/16 作成
	------------------------------------------------------------------------*/
	struct ApplicationSetting
	{
		std::string applicationName;	//!<アプリケーション名
	};

	namespace win32
	{
		/*!-----------------------------------------------------------------------
		@struct	ApplicationWin32Exeption
		@brief	ApplicationWin32例外データ
		@date	2017/08/16 作成
		------------------------------------------------------------------------*/
		struct ApplicationWin32Exeption 
			: public utility::Exeption
		{
			DWORD errorCode;		//!< エラーコード

			ApplicationWin32Exeption()
			{
				errorCode = NULL;
			}

			ApplicationWin32Exeption(
				std::string _className,
				std::string _methodName,
				std::string _overview,
				DWORD		_errorCode)
				: Exeption(_className, _methodName, _overview)
			{
				errorCode = _errorCode;
			}
		};

		class WindowWin32;

		/*!-----------------------------s------------------------------------------
		@class	ApllicationWin32
		@brief	WindowsAPIラッパークラス
		@date	2017/08/16 作成
		------------------------------------------------------------------------*/
		class ApplicationWin32 : private utility::NonCopyable<WindowWin32>
		{

		/*------------------------------------------------------------------------
		//メンバ変数
		------------------------------------------------------------------------*/	
		protected:
			::HINSTANCE			hInstance_;							//!< インスタンスハンドル
			ApplicationSetting	applicationSetting_;				//!< アプリケーション設定		@別に参照じゃなくてもいいかも

			static std::unordered_map<HWND, WindowWin32*> windowWin32s_;	//!< 子ウィンドウへの参照リスト

		/*------------------------------------------------------------------------
		//publicメンバ関数
		------------------------------------------------------------------------*/
		public:
		
			/*!-----------------------------------------------------------------------
			@fn			ApplicationWin32
			@brief		コンストラクタ
			@param[in]	_hInstance			インスタンスハンドル
			@param[in]	_nCmdShow			ウィンドウの表示状態
			@param[in]	_applicationSetting	アプリケーションの設定
			@return		無し
			@exeption	ApplicationWin32Exeption ウィンドウクラスの登録に失敗した時にthrow
			@date		2017/08/16 作成
			------------------------------------------------------------------------*/
			ApplicationWin32(
				const ::HINSTANCE&	_hInstance,
				int					_nCmdShow,
				ApplicationSetting	_applicationSetting);
			
			/*!-----------------------------------------------------------------------
			@fn			MessageLoop
			@brief		メッセージループを行う
			@return		無し
			@exeption	ApplicationWin32Exeption ウィンドウクラスの登録に失敗した時にthrow
			@date		2017/08/16 作成
			@todo		Callback関数を引数で指定できるようにする
			------------------------------------------------------------------------*/
			void BeginMessageLoop();
			

			/*!-----------------------------------------------------------------------
			@fn			MessageLoopCallback
			@brief		メッセージループ中のコールバック
						オーバーライドして使用する
			@return		無し
			@exeption	無し
			@date		2017/08/16 作成
			------------------------------------------------------------------------*/
			virtual void MessageLoopCallback()
			{
				
			}

			/*!-----------------------------------------------------------------------
			@fn			PeekMessageLoop
			@brief		PeekMessageにてメッセージループを行う
						ゲームなどリアルタイムで処理を行う場合はこちらを使用
			@return		無し
			@exeption	無し
			@date		2017/08/16 作成
			@todo		Callback関数を引数で指定できるようにする
			------------------------------------------------------------------------*/
			void BeginPeekMessageLoop();

			/*!-----------------------------------------------------------------------
			@fn			PeekMessageLoopCallback
			@brief		メッセージループ中のコールバック
						オーバーライドして使用する
			@return		PeekMessageのループを続けるか
						true	: ループ続行
						false	: ループ中断
			@exeption	無し
			@date		2017/08/16 作成
			------------------------------------------------------------------------*/
			virtual bool PeekMessageLoopCallback()
			{
				return true;
			}

			/*!-----------------------------------------------------------------------
			@fn			GetInstanceHandle
			@brief		インスタンスハンドルを取得
			@return		インスタンスハンドル
			@exeption	無し
			@date		2017/08/16 作成
			------------------------------------------------------------------------*/
			const HINSTANCE& GetInstanceHandle() const
			{
				return hInstance_;
			}

			/*!-----------------------------------------------------------------------
			@fn			GetInstanceHandle
			@brief		アプリケーションの設定を取得
			@return		アプリケーションの設定
			@exeption	無し
			@date		2017/08/16 作成
			------------------------------------------------------------------------*/
			const ApplicationSetting& GetApplicationSetting() const
			{
				return applicationSetting_;
			}

			/*!-----------------------------------------------------------------------
			@fn			GlobalWindowProcedur
			@brief		ウィンドウプロシージャ
						ここから各Windowのウィンドウプロシージャを呼び出す
			@exeption	無し
			@date		2017/08/16 作成
			------------------------------------------------------------------------*/
			static LRESULT CALLBACK GlobalWindowProcedur(
				HWND	_hWnd,
				UINT	_message,
				WPARAM	_wParam,
				LPARAM	_lParam);
		};

	}		// win32
}		// application
