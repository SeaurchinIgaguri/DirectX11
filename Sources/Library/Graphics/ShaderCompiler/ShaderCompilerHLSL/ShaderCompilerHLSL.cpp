#include "ShaderCompilerHLSL.h"

namespace graphics
{
	namespace shadercompiler
	{
		std::unique_ptr<ShaderBinaryCode> LoadFromCSO(const std::string& _csoPath)
		{
			auto pShaderBinaryCode = std::make_unique<ShaderBinaryCode>();

			//バイナリファイルを読み込む
			FILE* fp;

			try
			{
				fopen_s(&fp , _csoPath.c_str(), "rb");

				if (fp == NULL)
				{
					throw utility::Exeption("ShaderCompilerD3D11.h", "LoadCSO", "can not open cso");
				}
			}
			catch (utility::Exeption exeption)
			{
				throw exeption;
			}

			fseek(fp, 0, SEEK_END);

			pShaderBinaryCode->size = ftell(fp);
			pShaderBinaryCode->code.reset(new unsigned char[pShaderBinaryCode->size]);

			fseek(fp, 0, SEEK_SET);

			fread(pShaderBinaryCode->code.get(), pShaderBinaryCode->size, 1, fp);

			fclose(fp);

			return pShaderBinaryCode;
		}

	}	// shadercompiler

}	// graphics