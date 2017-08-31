#pragma once

#include "../PMXFormat.h"

// �O���錾
//class PMXFormat;

namespace resource
{
	namespace mesh
	{
		class PMX
		{
		public:

			//std::string	meshFilePath_;	//!< �t�@�C���p�X
			pmxformat::Header					header;			//!< �w�b�_���
			pmxformat::ModelInfo				modelInfo;		//!< ���f�����
			int									vertexCount;	//!< ���_��
			std::vector<pmxformat::VertexData>	vertices;		//!< ���_�z��
			//int								indexCount;		//!< �C���f�b�N�X��
			std::vector<int>					indices;		//!< �C���f�b�N�X�z��
			//int								textureCount;	//!< �e�N�X�`����
			std::vector<std::string>			textureNames;	//!< �e�N�X�`���z��
			//int								materialCount;	//!< �}�e���A����
			std::vector<pmxformat::Material>	materials;		//!< �}�e���A���z��
			int									boneCount;		//!< �{�[����
			std::vector<pmxformat::Bone>		bones;			//!< �{�[���r��
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