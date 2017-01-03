/*!-----------------------------------------------------------------------
@file	NonCopyable.h
@brief	NonCopyableクラスヘッダ
@date	2016/12/01 作成
------------------------------------------------------------------------*/
#pragma once

namespace utility
{
	/*!-----------------------------------------------------------------------
	@class		NonCopyable
	@brief		コピー不可Mix-inクラス
	@template	継承先クラスを指定
	@date		2016/12/01 作成
	------------------------------------------------------------------------*/
	template <class T>
	class NonCopyable
	{
	protected:
		NonCopyable() {}
		~NonCopyable() {} //!< protected な非仮想デストラクタ

	private:
		NonCopyable(const NonCopyable &);
		T & operator = (const T &);

	};		// end of class NonCopyable
}	// end of namespace utility