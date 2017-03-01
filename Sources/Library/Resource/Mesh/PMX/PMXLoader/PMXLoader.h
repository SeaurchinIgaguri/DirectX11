#pragma once

#include "../PMX.h"

namespace resource
{
	namespace mesh
	{
		class PMXLoader
		{
		public:
			void Open(const std::string& filePath);
			void Close();

			void LoadHeader();
			void LoadModelData();
			void LoadVertices();
			void LoadIndices();
			void LoadTexturePaths();
			void LoadMaterials();
			void LoadBone();
			void LoadMofe();

			PMX& GetPMXData();
			void GetVertices();
			void GetIndices();
			void GetTexturePaths();
			void GetMaterials();

		private:
			bool isOpend_;
			bool isLoadedHeader_;
			bool isLoadedModelData_;
			bool isLoadedVertices_;
			bool isLoadedIndices_;
			bool isLoadedTexturePaths_;
			bool isLoadedMaterials_;
			bool isLoadedBone_;
			bool isLoadedMofe_;

			PMX pmxData_;
		};

		class PMXConverter
		{
			
		};

		namespace pmxloader 
		{

			PMX::Header	LoadHeader(std::ifstream pmxStream);
			
			PMX::ModelInfo LoadModelInfo(std::ifstream pmxStream);

			std::vector<PMX::VertexData> LoadVertices(std::ifstream pmxStream, const PMX::Header& pmxHeader);

			std::vector<int> LoadIndices(std::ifstream pmxStream, const PMX::Header& pmxHeader);

			std::vector<std::string> LoadTexturePaths(std::ifstream pmxStream, const PMX::Header& pmxHeader);

			std::vector<PMX::Material> LoadMaterial(std::ifstream& pmxStream, const PMX::Header& pmxHeader);

		}		// end of namespace pmxloader
	}
}