#include "PMXLoader.h"

#include "../../../../Utility/WString.h"

namespace resource
{
	namespace mesh
	{
		namespace pmxloader
		{
			PMX* Load(const std::string& _pmxFilePath)
			{
				using namespace utility;

				PMX* pPMX = new PMX;

				std::ifstream ifStreamPMX(_pmxFilePath, std::ios::binary);

				if (ifStreamPMX.fail())
				{
					throw std::exception("failed open pmx file");
				}

				// load header
				ifStreamPMX.read((char*)&pPMX->header, sizeof(pmxformat::Header));

				// load modelinfo
				pPMX->modelInfo = LoadModelInfo(ifStreamPMX);

				pPMX->vertices = LoadVertices(ifStreamPMX, pPMX->header);

				return pPMX;
			}



			resource::mesh::pmxformat::ModelInfo LoadModelInfo(std::ifstream& _ifStreamPMX)
			{
				using namespace utility;

				resource::mesh::pmxformat::ModelInfo modelInfo;

				modelInfo.modelName			= ReadWStringUTF16(_ifStreamPMX);
				modelInfo.modelNameEnglish	= ReadWStringUTF16(_ifStreamPMX);
				modelInfo.comment			= ReadWStringUTF16(_ifStreamPMX);
				modelInfo.commentEnglish	= ReadWStringUTF16(_ifStreamPMX);

				return modelInfo;
			}

			std::vector<resource::mesh::pmxformat::VertexData> LoadVertices(std::ifstream& _ifStreamPMX, const resource::mesh::pmxformat::Header& _header)
			{
				using namespace resource::mesh;

				int verticesSize;

				_ifStreamPMX.read((char*)&verticesSize, sizeof(int));

				std::vector<resource::mesh::pmxformat::VertexData> vertices(verticesSize);

				for (int i = 0; i < verticesSize; ++i)
				{
					_ifStreamPMX.read((char*)&vertices[i].position, sizeof(pmxformat::float3));
					_ifStreamPMX.read((char*)&vertices[i].normal, sizeof(pmxformat::float3));
					_ifStreamPMX.read((char*)&vertices[i].uv, sizeof(pmxformat::float2));

					auto numAddUV = _header.data[pmxformat::ByteDataDatail::ADD_UV_NUM];

					if (numAddUV > 0)
					{
						vertices[i].pAddUV.reset(new pmxformat::float4);

						for (int j = 0; j < numAddUV; ++j)
						{
							_ifStreamPMX.read((char*)&vertices[i].pAddUV, sizeof(pmxformat::float4));
						}
					}

					_ifStreamPMX.read((char*)&vertices[i].skiningType, sizeof(vertices[i].skiningType));

					switch (static_cast<pmxformat::SkiningType>(vertices[i].skiningType))
					{
					case pmxformat::SkiningType::BDEF1:
						vertices[i].pSkining.reset(new pmxformat::BDEF1);
						break;

					case pmxformat::SkiningType::BDEF2:
						vertices[i].pSkining.reset(new pmxformat::BDEF2);
						break;

					case pmxformat::SkiningType::BDEF4:
						vertices[i].pSkining.reset(new pmxformat::BDEF4);
						break;

					case pmxformat::SkiningType::SDEF:
						vertices[i].pSkining.reset(new pmxformat::SDEF);
						break;

					default:
						break;
					}

					if (vertices[i].pSkining)
						vertices[i].pSkining->Read(_ifStreamPMX, _header.data[pmxformat::BONE_INDEX_SIZE]);

					_ifStreamPMX.read((char*)&vertices[i].edgeMagnification, sizeof(vertices[i].edgeMagnification));
				}

				return vertices;
			}

			std::vector<int> LoadIndices(std::ifstream& _ifStreamPMX, const resource::mesh::pmxformat::Header& _header)
			{
				using namespace resource::mesh;

				int indicesSize = 0;

				_ifStreamPMX.read((char*)indicesSize, sizeof(int));

				std::vector<int> indices(indicesSize);

				_ifStreamPMX.read((char*)&indices[0], _header.data[pmxformat::ByteDataDatail::VERTEX_INDEX_SIZE] * indicesSize);

				return indices;
			}

			std::vector<std::string> LoadTextureNames(std::ifstream& _ifStreamPMX)
			{
				using namespace utility;

				int textureNamesSize = 0;

				_ifStreamPMX.read((char*)textureNamesSize, sizeof(int));

				std::vector<std::string> textureNames(textureNamesSize);

				for (auto& textureName : textureNames)
				{
					textureName = WStringToString(ReadWStringUTF16(_ifStreamPMX));
				}

				return textureNames;
			}

			std::vector<resource::mesh::pmxformat::Material> LoadMaterials(std::ifstream& _ifStreamPMX, const resource::mesh::pmxformat::Header& _header)
			{
				using namespace utility;
				using namespace resource::mesh::pmxformat;

				int materialsSize = 0;

				_ifStreamPMX.read((char*)materialsSize, sizeof(int));

				std::vector<Material> materials(materialsSize);

				for (auto& material : materials)
				{
					material.name			= ReadWStringUTF16(_ifStreamPMX);
					material.nameEnglish	= ReadWStringUTF16(_ifStreamPMX);

					_ifStreamPMX.read((char*)&material.diffuse,				sizeof(float4));
					_ifStreamPMX.read((char*)&material.specular,			sizeof(float3));
					_ifStreamPMX.read((char*)&material.specularPower,		sizeof(float));
					_ifStreamPMX.read((char*)&material.ambient,				sizeof(float3));
					_ifStreamPMX.read((char*)&material.drawFlg,				sizeof(char));
					_ifStreamPMX.read((char*)&material.edgeColor,			sizeof(float4));
					_ifStreamPMX.read((char*)&material.edgeSize,			sizeof(float));
					_ifStreamPMX.read((char*)&material.textureIndex,		_header.data[TEXTURE_INDEX_SIZE]);
					_ifStreamPMX.read((char*)&material.sphereTextureIndex,	_header.data[TEXTURE_INDEX_SIZE]);
					_ifStreamPMX.read((char*)&material.sphereMode,			sizeof(char));
					_ifStreamPMX.read((char*)&material.shareToonFlg,		sizeof(char));

					material.shareToonFlg == true ?  
						_ifStreamPMX.read((char*)&material.toonTextureIndex, _header.data[TEXTURE_INDEX_SIZE]) :
						_ifStreamPMX.read((char*)&material.shareToonTextureIndex, sizeof(char));

					material.memo = ReadWStringUTF16(_ifStreamPMX);
					
					_ifStreamPMX.read((char*)&material.faceCount, sizeof(int));
				}

				return materials;
			}
		}
	}
}
