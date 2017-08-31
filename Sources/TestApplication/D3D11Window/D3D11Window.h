/*!-----------------------------------------------------------------------
@file	�t�@�C����
@brief	�t�@�C������
@date	�쐬/�X�V�������t
------------------------------------------------------------------------*/
#pragma once

/*------------------------------------------------------------------------
//�C���N���[�h
------------------------------------------------------------------------*/
#include "../../Library/Application/Win32/WindowWin32/WindowWin32.h"

namespace d3d11application
{
	/*!-----------------------------------------------------------------------
	@class	�N���X��
	@brief	�N���X����
	@date	�쐬/�X�V�������t
	------------------------------------------------------------------------*/
	class D3D11Window
		: public application::win32::WindowWin32
	{
		/*------------------------------------------------------------------------
		//�����o�ϐ�
		------------------------------------------------------------------------*/
	private:

		/*------------------------------------------------------------------------
		//public�����o�֐�
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
		@fn			�֐���
		@brief		�֐�����
		@param[in]	������			�����̐���
		@param[out]	����(�o��)��	����(�o��)�̐���
		@return		�߂�l�̐���
		@exeption	��O�̐���
		@date		�쐬/�X�V�������t
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
		//private�����o�֐�
		------------------------------------------------------------------------*/
	private:

	};	//D3D11Window
}	// d3d11application