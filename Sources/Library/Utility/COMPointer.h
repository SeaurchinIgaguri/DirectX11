/*!-----------------------------------------------------------------------
@file	COMPointer.h
@brief	COMオブジェクト用のスマートポインターを定義
@date	2015/08/19 作成
------------------------------------------------------------------------*/
#pragma once

/*------------------------------------------------------------------------
//インクルード
------------------------------------------------------------------------*/
#include <Unknwn.h>
#include <memory>
#include <wrl.h>

namespace utility
{
	/*!-----------------------------------------------------------------------
	@brief	COMオブジェクトを解放する関数オブジェクト
	std::shared_ptrなどのスマートポインタのコンストラクタの引数に指定して使用
	@date	2015/08/19 作成
	------------------------------------------------------------------------*/
	typedef struct ComDeleter
	{
		void operator () (IUnknown* p)
		{
			p->Release();
		}
	}comdeleter;

	template <class T>
	using com_unique_ptr = std::unique_ptr<T, ComDeleter>;

	//template <class T>
	//using com_shared_ptr = Microsoft::WRL::ComPtr<T>;

	template <class T>
	com_unique_ptr<T> make_com_unique(T* pCOM)
	{
		return com_unique_ptr<T>(pCOM);
	}

	/*template <class T>
	class com_shared_ptr
	{
	public:
		com_shared_ptr()
		{
			ptr = nullptr;
		}

		com_shared_ptr(T* _ptr)
		{
			Set(_ptr);
		}

		~com_shared_ptr()
		{
			Release();
		}

		void operator= (const com_shared_ptr& _other)
		{
			ptr->AddRef();

			ptr = _other.ptr;
		}

		T* operator->()
		{
			return ptr;
		}

		void Set(T* _ptr)
		{
			if (_ptr)
			{
				Release();
			}

			ptr = _ptr;
			ptr->AddRef();
		}

		void Release()
		{
			if (ptr)
			{
				ptr->Release();
				ptr = nullptr;
			}
		}

	private:
		T* ptr;
	};*/
}	// utility