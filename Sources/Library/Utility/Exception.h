#pragma once

#include <string>
#include <Windows.h>

namespace utility
{
	struct Exeption
	{
	public:
		std::exception	exception;		//!< std::exeption
		std::string		className;		//!< 例外が起こったクラス名
		std::string		methodName;		//!< 例外が起こった関数名
		std::string		overview;		//!< 例外の概要

		//const char*		fileName;		//!< 例外が起こったファイル名
		//int				line;			//!< 例外が起こった行

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
