/*!-----------------------------------------------------------------------
@file	NonCopyable.h
@brief	NonCopyable�N���X�w�b�_
@date	2016/12/01 �쐬
------------------------------------------------------------------------*/
#pragma once

namespace utility
{
	/*!-----------------------------------------------------------------------
	@class		NonCopyable
	@brief		�R�s�[�s��Mix-in�N���X
	@template	�p����N���X���w��
	@date		2016/12/01 �쐬
	------------------------------------------------------------------------*/
	template <class T>
	class NonCopyable
	{
	protected:
		NonCopyable() {}
		~NonCopyable() {} //!< protected �Ȕ񉼑z�f�X�g���N�^

	private:
		NonCopyable(const NonCopyable &);
		T & operator = (const T &);

	};		// end of class NonCopyable
}	// end of namespace utility