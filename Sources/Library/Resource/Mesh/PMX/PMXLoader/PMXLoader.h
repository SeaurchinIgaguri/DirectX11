#pragma once

#include "../PMXFormat.h"

// 前方宣言
//class PMXFormat;

namespace resource
{
	namespace mesh
	{
		class PMX
		{
		public:

			//std::string	meshFilePath_;	//!< ファイルパス
			pmxformat::Header					header;			//!< ヘッダ情報
			pmxformat::ModelInfo				modelInfo;		//!< モデル情報
			int									vertexCount;	//!< 頂点数
			std::vector<pmxformat::VertexData>	vertices;		//!< 頂点配列
			//int								indexCount;		//!< インデックス数
			std::vector<int>					indices;		//!< インデックス配列
			//int								textureCount;	//!< テクスチャ数
			std::vector<std::string>			textureNames;	//!< テクスチャ配列
			//int								materialCount;	//!< マテリアル数
			std::vector<pmxformat::Material>	materials;		//!< マテリアル配列
			int									boneCount;		//!< ボーン数
			std::vector<pmxformat::Bone>		bones;			//!< ボーン排列
		};

		namespace pmxloader 
		{

			PMX* Load(const std::string& pmxFilePath);

			resource::mesh::pmxformat::ModelInfo LoadModelInfo(std::ifstream & _ifStreamPMX);

			std::vector<resource::mesh::pmxformat::VertexData> LoadVertices(std::ifstream & _ifStreamPMX, const resource::mesh::pmxformat::Header & _header);

			std::vector<int> LoadIndices(std::ifstream & _ifStreamPMX, const resource::mesh::pmxformat::Header & _header);

			std::vector<std::string> LoadTextureNames(std::ifstream & _ifStreamPMX);

			std::vector<resource::mesh::pmxformat::Material> LoadMaterials(std::ifstream & _ifStreamPMX, const resource::mesh::pmxformat::Header & _header);

		}		// end of namespace pmxloader
	}
}