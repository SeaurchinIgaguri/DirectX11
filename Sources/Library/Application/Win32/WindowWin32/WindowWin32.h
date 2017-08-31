/*!-----------------------------------------------------------------------
@file	WindowWin32.h
@brief	WindowWin32�錾��
@date	2017/08/16 �쐬
------------------------------------------------------------------------*/
#pragma once

/*------------------------------------------------------------------------
//�C���N���[�h
------------------------------------------------------------------------*/
#include "../ApplicationWin32/ApplicationWin32.h"
#include "../../../Utility/NonCopyable.h"

namespace application
{
	/*!-----------------------------------------------------------------------
	@struct	WindowSetting
	@brief	�E�B���h�E�̐ݒ�f�[�^
	@date	2017/08/16 �쐬
	------------------------------------------------------------------------*/
	struct WindowSetting
	{
		std::string	windowName;		//!< �E�B���h�E��
		int			width;			//!< �E�B���h�E����
		int			height;			//!< �E�B���h�E�c��

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
		@brief	�E�B���h�E�̍쐬/�X�V
		@date	2017/08/16 �쐬
		------------------------------------------------------------------------*/
		class WindowWin32 
			: private utility::NonCopyable<WindowWin32>
		{
		protected:
			ApplicationWin32&		applicationWin32_;		//!< �e�A�v���P�[�V����
			WindowSetting			windowSetting_;			//!< �E�B���h�E�ݒ�
			HWND					hWnd_;					//!< �E�B���h�E�n���h��

		public:

			/*!-----------------------------------------------------------------------
			@fn			WindowWin32
			@brief		�R���X�g���N�^
			@param[in]	_applicationWin32		�e�A�v���P�[�V����
			@param[in]	_windowSetting			�E�B���h�E�̐ݒ�
			@return		����
			@exeption	CreateWindowEx�����s�����Ƃ�ApplicationWin32Exeption�𓊂���
			@date		2017/08/16 �쐬
			------------------------------------------------------------------------*/
			WindowWin32(
				ApplicationWin32&	_applicationWin32,
				WindowSetting		_windowSetting);

			/*!-----------------------------------------------------------------------
			@fn			WindowWin32
			@brief		�R���X�g���N�^
			@param[in]	_applicationWin32		�e�A�v���P�[�V����
			@param[in]	_nCmdShow				�E�B���h�E�\�����
			@param[in]	_windowSetting			�E�B���h�E�̐ݒ�
			@return		����
			@exeption	CreateWindowEx�����s�����Ƃ�ApplicationWin32Exeption�𓊂���
			@date		2017/08/16 �쐬
			------------------------------------------------------------------------*/
			WindowWin32(
				ApplicationWin32&	_applicationWin32,
				int					_nCmdShow,
				WindowSetting		_windowSetting);

			/*!-----------------------------------------------------------------------
			@fn			~WindowWin32
			@brief		�f�X�g���N�^
			@return		����
			@exeption	����
			@date		2017/08/16 �쐬
			------------------------------------------------------------------------*/
			virtual ~WindowWin32();

			/*!-----------------------------------------------------------------------
			@fn			WindowProcedur
			@brief		�E�B���h�E�ʃE�B���h�E�v���V�[�W��
						�I�[�o�[���C�h���Ďg�p
			@date		2017/08/16 �쐬
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
			@brief		�E�B���h�E�n���h�����擾
			@return		�E�B���h�E�n���h��
			@exeption	����
			@date		2017/08/16 �쐬
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
