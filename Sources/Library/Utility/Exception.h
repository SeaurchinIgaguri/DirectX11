#pragma once

#include <string>
#include <Windows.h>

namespace utility
{
	struct Exeption
	{
	public:
		std::exception	exception;		//!< std::exeption
		std::string		className;		//!< ��O���N�������N���X��
		std::string		methodName;		//!< ��O���N�������֐���
		std::string		overview;		//!< ��O�̊T�v

		//const char*		fileName;		//!< ��O���N�������t�@�C����
		//int				line;			//!< ��O���N�������s

		Exeption()
		{
		}

		Exeption(const std::exception& _exeption)
		{
			exception = _exeption;
		}

		Exeption(
			std::string _className, 
			std::string _methodName,
			std::string _overview)
		{
			className	= _className;
			methodName	= _methodName;
			overview	= _overview;
		}

		Exeption(
			std::exception _exeption,
			std::string _className,
			std::string _methodName,
			std::string _overview)
		{
			exception = _exeption;
			className = _className;
			methodName = _methodName;
			overview = _overview;
		}
	};

	inline int ShowExeption(const Exeption& exeption)
	{
		std::string text = exeption.overview;
		std::string caption = exeption.className + "::" + exeption.methodName;

		return ::MessageBox(
			NULL,
			text.c_str(),
			caption.c_str(),
			MB_ABORTRETRYIGNORE);
	}
}		// system
