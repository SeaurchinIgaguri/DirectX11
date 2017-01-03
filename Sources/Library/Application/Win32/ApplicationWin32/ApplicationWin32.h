/*!-----------------------------------------------------------------------
@file	ApplicationWin32.h
@brief	Win32�A�v���P�[�V�������b�p�[�N���X
@date	2017/08/16 �쐬
------------------------------------------------------------------------*/
#pragma once

/*------------------------------------------------------------------------
//�C���N���[�h
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
	@brief	�A�v���P�[�V�����̐ݒ�f�[�^
	@date	2017/08/16 �쐬
	------------------------------------------------------------------------*/
	struct ApplicationSetting
	{
		std::string applicationName;	//!<�A�v���P�[�V������
	};

	namespace win32
	{
		/*!-----------------------------------------------------------------------
		@struct	ApplicationWin32Exeption
		@brief	ApplicationWin32��O�f�[�^
		@date	2017/08/16 �쐬
		------------------------------------------------------------------------*/
		struct ApplicationWin32Exeption 
			: public utility::Exeption
		{
			DWORD errorCode;		//!< �G���[�R�[�h

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
		@brief	WindowsAPI���b�p�[�N���X
		@date	2017/08/16 �쐬
		------------------------------------------------------------------------*/
		class ApplicationWin32 : private utility::NonCopyable<WindowWin32>
		{

		/*------------------------------------------------------------------------
		//�����o�ϐ�
		------------------------------------------------------------------------*/	
		protected:
			::HINSTANCE			hInstance_;							//!< �C���X�^���X�n���h��
			ApplicationSetting	applicationSetting_;				//!< �A�v���P�[�V�����ݒ�		@�ʂɎQ�Ƃ���Ȃ��Ă���������

			static std::unordered_map<HWND, WindowWin32*> windowWin32s_;	//!< �q�E�B���h�E�ւ̎Q�ƃ��X�g

		/*------------------------------------------------------------------------
		//public�����o�֐�
		------------------------------------------------------------------------*/
		public:
		
			/*!-----------------------------------------------------------------------
			@fn			ApplicationWin32
			@brief		�R���X�g���N�^
			@param[in]	_hInstance			�C���X�^���X�n���h��
			@param[in]	_nCmdShow			�E�B���h�E�̕\�����
			@param[in]	_applicationSetting	�A�v���P�[�V�����̐ݒ�
			@return		����
			@exeption	ApplicationWin32Exeption �E�B���h�E�N���X�̓o�^�Ɏ��s��������throw
			@date		2017/08/16 �쐬
			------------------------------------------------------------------------*/
			ApplicationWin32(
				const ::HINSTANCE&	_hInstance,
				int					_nCmdShow,
				ApplicationSetting	_applicationSetting);
			
			/*!-----------------------------------------------------------------------
			@fn			MessageLoop
			@brief		���b�Z�[�W���[�v���s��
			@return		����
			@exeption	ApplicationWin32Exeption �E�B���h�E�N���X�̓o�^�Ɏ��s��������throw
			@date		2017/08/16 �쐬
			@todo		Callback�֐��������Ŏw��ł���悤�ɂ���
			------------------------------------------------------------------------*/
			void BeginMessageLoop();
			

			/*!-----------------------------------------------------------------------
			@fn			MessageLoopCallback
			@brief		���b�Z�[�W���[�v���̃R�[���o�b�N
						�I�[�o�[���C�h���Ďg�p����
			@return		����
			@exeption	����
			@date		2017/08/16 �쐬
			------------------------------------------------------------------------*/
			virtual void MessageLoopCallback()
			{
				
			}

			/*!-----------------------------------------------------------------------
			@fn			PeekMessageLoop
			@brief		PeekMessage�ɂă��b�Z�[�W���[�v���s��
						�Q�[���Ȃǃ��A���^�C���ŏ������s���ꍇ�͂�������g�p
			@return		����
			@exeption	����
			@date		2017/08/16 �쐬
			@todo		Callback�֐��������Ŏw��ł���悤�ɂ���
			------------------------------------------------------------------------*/
			void BeginPeekMessageLoop();

			/*!-----------------------------------------------------------------------
			@fn			PeekMessageLoopCallback
			@brief		���b�Z�[�W���[�v���̃R�[���o�b�N
						�I�[�o�[���C�h���Ďg�p����
			@return		PeekMessage�̃��[�v�𑱂��邩
						true	: ���[�v���s
						false	: ���[�v���f
			@exeption	����
			@date		2017/08/16 �쐬
			------------------------------------------------------------------------*/
			virtual bool PeekMessageLoopCallback()
			{
				return true;
			}

			/*!-----------------------------------------------------------------------
			@fn			GetInstanceHandle
			@brief		�C���X�^���X�n���h�����擾
			@return		�C���X�^���X�n���h��
			@exeption	����
			@date		2017/08/16 �쐬
			------------------------------------------------------------------------*/
			const HINSTANCE& GetInstanceHandle() const
			{
				return hInstance_;
			}

			/*!-----------------------------------------------------------------------
			@fn			GetInstanceHandle
			@brief		�A�v���P�[�V�����̐ݒ���擾
			@return		�A�v���P�[�V�����̐ݒ�
			@exeption	����
			@date		2017/08/16 �쐬
			------------------------------------------------------------------------*/
			const ApplicationSetting& GetApplicationSetting() const
			{
				return applicationSetting_;
			}

			/*!-----------------------------------------------------------------------
			@fn			GlobalWindowProcedur
			@brief		�E�B���h�E�v���V�[�W��
						��������eWindow�̃E�B���h�E�v���V�[�W�����Ăяo��
			@exeption	����
			@date		2017/08/16 �쐬
			------------------------------------------------------------------------*/
			static LRESULT CALLBACK GlobalWindowProcedur(
				HWND	_hWnd,
				UINT	_message,
				WPARAM	_wParam,
				LPARAM	_lParam);
		};

	}		// win32
}		// application
