#pragma once

#include <fstream>
#include <string>
#include <vector>

namespace utility
{

	/*!-----------------------------------------------------------------------
	@brief	std::wstring����std::string�ɕϊ�
	@param[in]		src		�\�[�X
	@param[out]		dest	�o�͐�
	@return �o�͂��ꂽstd::string
	@date	2015/09/09 �X�V
	------------------------------------------------------------------------*/
	inline std::string WStringToString(const std::wstring &src, std::string &dest)
	{
		int returnValue;

		char *mbs = new char[src.length() * MB_CUR_MAX + 1];	// �\�[�X���̕�����̒�����char�z���new

		wcstombs_s(												// wchar_t����char�^�ɕϊ�
			(size_t*)&returnValue,
			mbs,
			(size_t)src.length() * MB_CUR_MAX + 1,
			src.c_str(),
			_TRUNCATE);

		dest = mbs;												// �o�͐�ɃR�s�[

		delete[] mbs;

		return dest;
	}

	inline std::string WStringToString(const std::wstring &src)
	{
		int returnValue;

		char *pMBS = new char[src.length() * MB_CUR_MAX + 1];	// �\�[�X���̕�����̒�����char�z���new

		wcstombs_s(												// wchar_t����char�^�ɕϊ�
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