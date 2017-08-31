/*!-----------------------------------------------------------------------
@file	ApplicationWin32.cpp
@brief	ApplicationWin32クラス実装部
@date	2017/08/17 作成
------------------------------------------------------------------------*/

/*------------------------------------------------------------------------
//インクルード
------------------------------------------------------------------------*/
#include "ApplicationWin32.h"
#include "../WindowWin32/WindowWin32.h"

namespace application
{
	namespace win32
	{
		/*------------------------------------------------------------------------
		//変数宣言
		------------------------------------------------------------------------*/
		std::unordered_map<HWND, WindowWin32*> ApplicationWin32::windowWin32s_;

		/*------------------------------------------------------------------------
		//関数定義
		------------------------------------------------------------------------*/
		ApplicationWin32::ApplicationWin32(
			const HINSTANCE&	_hInstance,
			int					_nCmdShow,
			ApplicationSetting	_applicationSetting)
			: hInstance_(_hInstance),
			applicationSetting_(_applicationSetting)
		{
			WNDCLASSEX	wndClassEx;
			const char*	applicaionName = applicationSetting_.applicationName.c_str();

			wndClassEx.cbSize			= sizeof(WNDCLASSEX);
			wndClassEx.style			= CS_CLASSDC;
			wndClassEx.lpfnWndProc		= GlobalWindowProcedur;
			wndClassEx.cbClsExtra		= 0;
			wndClassEx.cbWndExtra		= 0;
			wndClassEx.hInstance		= hInstance_;
			wndClassEx.hIcon			= NULL;
			wndClassEx.hCursor			= LoadCursor(NULL, IDC_ARROW);
			wndClassEx.hbrBackground	= (HBRUSH)(COLOR_WINDOW + 1);
			wndClassEx.lpszMenuName		= NULL;
			wndClassEx.lpszClassName	= applicaionName;
			wndClassEx.hIconSm			= NULL;

			// ウィンドウクラスの登録
			try
			{
				WORD result = RegisterClassEx(&wndClassEx);

				if (result == 0)
				{
					DWORD lastError = GetLastError();

					throw ApplicationWin32Exeption(
						"ApplicationWin32",
						"ApplicationWin32",
						"RegisterClassEx failed",
						lastError);
				}
			}
			catch (ApplicationWin32Exeption exeption)
			{
				throw exeption;
			}
		}

		void ApplicationWin32::BeginMessageLoop()
		{
			MSG message;

			while (GetMessage(&message, NULL, 0, 0))
			{
				TranslateMessage(&message);
				DispatchMessage(&message);

				MessageLoopCallback();
			}
		}

		void ApplicationWin32::BeginPeekMessageLoop()
		{
			MSG		message;
			bool	isLoop = true;

			while (isLoop)
			{
				// メッセージループ
				if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE) != 0)
				{
					if (message.message == WM_QUIT)
					{// PostQuitMessage()が呼ばれたらループ終了
						break;
					}

					// メッセージの翻訳と送出
					TranslateMessage(&message);
					DispatchMessage(&message);
				}
				else
				{
					isLoop = PeekMessageLoopCallback();
				}
			}
		}

		LRESULT CALLBACK ApplicationWin32::GlobalWindowProcedur(
			HWND	_hWnd,
			UINT	_message,
			WPARAM	_wParam,
			LPARAM	_lParam)
		{
			LRESULT	lResult = 0L;

			auto pWindowWin32 = reinterpret_cast<WindowWin32*>(::GetWindowLongPtr(_hWnd, GWL_USERDATA));

			if(pWindowWin32 == nullptr)
			{
				if (_message == WM_CREATE || _message == WM_NCCREATE)
				{
					pWindowWin32 = reinterpret_cast<WindowWin32*>(((LPCREATESTRUCT)_lParam)->lpCreateParams);

					_ASSERT(pWindowWin32 != nullptr);

					SetWindowLong(_hWnd, GWL_USERDATA, reinterpret_cast<LONG>(pWindowWin32));

					lResult = pWindowWin32->WindowProcedur(_hWnd, _message, _wParam, _lParam);
				}
				else
				{
					//_ASSERT(0);
				}
			}
			else
			{
				lResult = pWindowWin32->WindowProcedur(_hWnd, _message, _wParam, _lParam);

				if(_message == WM_CLOSE)
					SetWindowLong(_hWnd, GWL_USERDATA, 0);
			}

			return lResult;
		}
	}	// win32
}	// application