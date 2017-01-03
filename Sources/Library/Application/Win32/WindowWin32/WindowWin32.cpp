/*!-----------------------------------------------------------------------
@file	WindowWin32.cpp
@brief	WindowWin32実装部
@date	2017/08/16 作成
------------------------------------------------------------------------*/

/*------------------------------------------------------------------------
//インクルード
------------------------------------------------------------------------*/
#include "WindowWin32.h"

/*------------------------------------------------------------------------
//関数定義
------------------------------------------------------------------------*/
namespace application
{
	namespace win32
	{
		WindowWin32::WindowWin32(
			ApplicationWin32&	_applicationWin32,
			WindowSetting		_windowSetting)
			: applicationWin32_(_applicationWin32),
			windowSetting_(_windowSetting)
		{
			_CreateWindow(_applicationWin32, _windowSetting);
		}

		WindowWin32::WindowWin32(
			ApplicationWin32&	_applicationWin32,
			int					_nCmdShow,
			WindowSetting		_windowSetting)
			: applicationWin32_(_applicationWin32),
			windowSetting_(_windowSetting)
		{
			_CreateWindow(_applicationWin32, _windowSetting);

			ShowWindow(hWnd_, _nCmdShow);
		}

		WindowWin32::~WindowWin32()
		{

		}

		void WindowWin32::_CreateWindow(
			ApplicationWin32&	_applicationWin32,
			WindowSetting		_windowSetting)
		{
			HINSTANCE		hInstance		= applicationWin32_.GetInstanceHandle();
			const char*		apllicationName = applicationWin32_.GetApplicationSetting().applicationName.c_str();
			const char*		windowName		= windowSetting_.windowName.c_str();

			try
			{
				hWnd_ = CreateWindowEx(
					0,
					apllicationName,
					windowName,
					WS_OVERLAPPEDWINDOW,
					CW_USEDEFAULT,
					CW_USEDEFAULT,
					windowSetting_.width,	//	+ GetSystemMetrics(SM_CXDLGFRAME) * 2,
					windowSetting_.height,	//	+ GetSystemMetrics(SM_CXDLGFRAME) * 2 + GetSystemMetrics(SM_CYCAPTION),
					NULL,
					NULL,
					hInstance,
					(void*)this);

				if (hWnd_ == NULL)
				{
					DWORD lastError = GetLastError();

					throw ApplicationWin32Exeption(
						"WindowWin32",
						"WindowWin32",
						"CreateWindowEX failed",
						lastError);
				}
			}
			catch (ApplicationWin32Exeption exeption)
			{
				throw exeption;
			}
		}
	}	// namespace win32
}	// namespace application