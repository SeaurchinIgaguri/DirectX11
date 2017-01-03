#pragma once

#include <memory>

namespace graphics
{
	struct ShaderBinaryCode
	{
		std::unique_ptr<unsigned char[]>	code;
		std::size_t							size;
	};

}	// graphics