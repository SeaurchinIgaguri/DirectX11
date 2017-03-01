#include "PMXLoader.h"
#include "../../../../Utility/WString.h"

namespace resource
{
	namespace mesh
	{
		void PMXLoader::Open(const std::string& _filePath)
		{
			std::ifstream	ifs(_filePath, std::ios::binary);

			if (ifs.fail())
			{
				throw std::runtime_error("failed open pmx file");
			}

			isOpend_ = true;
		}

		namespace pmxloader
		{
			namespace
			{
				std::streamoff StreamOffsetModelInfo()
				{
					return sizeof(PMX::Header);
				}

				std::streamoff StreamOffsetVertices(const PMX::ModelInfo& modelInfo)
				{
					auto streamOffsetModelInfo = StreamOffsetModelInfo();

					return streamOffsetModelInfo + modelInfo.GetLength();
				}

				std::streamoff StreamOffsetIndices(const PMX::ModelInfo& modelInfo, const int vertexCount)
				{
					auto streamOffsetVertices = StreamOffsetVertices(modelInfo);

					//std::size_t vertexSize = sizeof(PMX::float3) + sizeof(PMX::float3) + sizeof(PMX::float2)
				}
			}

			PMX::Header LoadHeader(std::ifstream pmxStream)
			{
				PMX::Header pmxHeader;

				/*if (pmxStream.fail())
				{
					throw std::runtime_error("not opend pmxStream");
				}*/

				pmxStream.seekg(0, std::ios_base::beg);

				pmxStream.read((char*)&pmxHeader, sizeof(pmxHeader));

				return pmxHeader;
			}

			PMX::ModelInfo LoadModelInfo(std::ifstream pmxStream)
			{
				using namespace utility;

				PMX::ModelInfo pmxModelInfo;

				std::streamoff streamOffModelInfo = sizeof(PMX::Header);

				pmxStream.seekg(streamOffModelInfo, std::ios_base::beg);

				pmxModelInfo.modelName			= ReadWStringUTF16(pmxStream);
				pmxModelInfo.modelNameEnglish	= ReadWStringUTF16(pmxStream);
				pmxModelInfo.comment			= ReadWStringUTF16(pmxStream);
				pmxModelInfo.commentEnglish		= ReadWStringUTF16(pmxStream);

				return pmxModelInfo;
			}

			std::vector<PMX::VertexData> LoadVertices(std::ifstream pmxStream, const PMX::Header& pmxHeader)
			{
				std::vector<PMX::VertexData> vertices;

				//auto streamOffszetVertices = StreamOffsetVertices(modelInfo);

				int vertexCount = 0;

				

				return vertices;
			}


		}
	}
}
