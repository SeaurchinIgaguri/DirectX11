#pragma once

#include <memory>
#include <string>
#include "../../ShaderBinaryCode.h"
#include "../../../Utility/Exception.h"

namespace graphics
{
	namespace shadercompiler
	{
		std::unique_ptr<ShaderBinaryCode> LoadFromCSO(const std::string& _csoName);

	}	// shadercompiler
}	// graphics