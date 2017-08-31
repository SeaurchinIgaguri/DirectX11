#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace utility
{

	/*!-----------------------------------------------------------------------
	@brief	std::wstringからstd::stringに変換
	@param[in]		src		ソース
	@param[out]		dest	出力先
	@return 出力されたstd::string
	@date	2015/09/09 更新
	------------------------------------------------------------------------*/
	inline std::string WStringToString(const std::wstring &src, std::string &dest)
	{
		int returnValue;

		char *mbs = new char[src.length() * MB_CUR_MAX + 1];	// ソース元の文字列の長さ分char配列をnew

		wcstombs_s(												// wchar_tからchar型に変換
			(size_t*)&returnValue,
			mbs,
			(size_t)src.length() * MB_CUR_MAX + 1,
			src.c_str(),
			_TRUNCATE);

		dest = mbs;												// 出力先にコピー

		delete[] mbs;

		return dest;
	}

	inline std::string WStringToString(const std::wstring &src)
	{
		int returnValue;

		char *pMBS = new char[src.length() * MB_CUR_MAX + 1];	// ソース元の文字列の長さ分char配列をnew

		wcstombs_s(												// wchar_tからchar型に変換
			(size_t*)&returnValue,
			pMBS,
			(size_t)src.length() * MB_CUR_MAX + 1,
			src.c_str(),
			_TRUNCATE);

		std::string dest = pMBS;

		delete[] pMBS;

		return dest;
	}

	inline std::wstring ReadWStringUTF16(std::ifstream& _ifs)
	{
		int size = 0;

		_ifs.read((char*)&size, sizeof(int));

		std::vector<char> buffer;

		if (size <= 0)
		{
			return std::wstring(L"");
		}

		buffer.resize(size);

		_ifs.read((char*)buffer.data(), size);

		// UTF16
		return std::wstring((wchar_t*)buffer.data(), size / 2);

		// UTF8
		//std::wstring result;
		//converter.Utf8ToUtf16(buffer.data(), size, &result);
		//return result;
	}



}	// end of namespace utility