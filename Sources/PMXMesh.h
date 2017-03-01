#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <WinBase.h>
#include "Library\Utility\WString.h"

class PMXMesh
{
	// PMX�̃f�[�^�\��
#pragma pack(push, 1)		// �A���C�����g��OFF
	struct float2
	{
		float x, y;
	};

	struct float3
	{
		float x, y, z;
	};

	struct float4
	{
		float x, y, z, w;
	};

	// �w�b�_�[
	struct Header
	{
		unsigned char	magic[4];		//!< "PMX " | ASCII�� 0x50,0x4d,0x58,0x20  �������󔒂ɒ��� (PMX1.0��"Pmx "�ɂȂ��Ă���̂ŊԈႦ�Ȃ��悤��)
		float			version;		//!< PMX�o�[�W����
		unsigned char	dataByteSize;	//!< �㑱����f�[�^��̃o�C�g�T�C�Y
		unsigned char	data[8];		//!< �o�C�g��

	};

	//�@�o�C�g��ڍ�
	enum ByteDataDatail : unsigned int
	{
		ENCODE					= 0,	//	[0] - �G���R�[�h����		| 0:UTF16 1 : UTF8
		ADD_UV_NUM				= 1,	//	[1] - �ǉ�UV��				| 0�`4 �ڍׂ͒��_�Q��
		VERTEX_INDEX_SIZE		= 2,	//	[2] - ���_Index�T�C�Y		| 1, 2, 4 �̂����ꂩ
		TEXTURE_INDEX_SIZE		= 3,	//	[3] - �e�N�X�`��Index�T�C�Y | 1, 2, 4 �̂����ꂩ
		MATERIAL_INDEX_SIZE		= 4,	//	[4] - �ގ�Index�T�C�Y		| 1, 2, 4 �̂����ꂩ
		BONE_INDEX_SIZE			= 5,	//	[5] - �{�[��Index�T�C�Y		| 1, 2, 4 �̂����ꂩ
		MORPH_INDEX_SIZE		= 6,	//	[6] - ���[�tIndex�T�C�Y		| 1, 2, 4 �̂����ꂩ
		RIGIDBODY_INDEX_SIZE	= 7,	//	[7] - ����Index�T�C�Y		| 1, 2, 4 �̂����ꂩ
	};

	// ���f�����
	struct ModelInfo
	{
		std::wstring modelName;		//!< ���f����
		std::wstring modelNameEnglish;	//!< ���f���p�ꖼ
		std::wstring comment;			//!< �R�����g
		std::wstring commentEnglish;	//!< �R�����g�p
	};

	// �E�F�C�g��񂱂�����
	enum SkiningType
	{
		SKININGTYPE_BDEF1,
		SKININGTYPE_BDEF2,
		SKININGTYPE_BDEF4,
		SKININGTYPE_SDEF,
	};

	// �{�[���̂� �C���f�b�N�X�̃o�C�g���͉ς������ڂ炵��int�Œ�
	class IVertexSkining
	{
	public:
		virtual void Read(std::ifstream& _ifs, unsigned char _boneIndexSize) = 0;
	};

	class BDEF1 : public IVertexSkining
	{
	public:
		int index = 0;

		void Read(std::ifstream& _ifs, unsigned char _boneIndexSize)
		{
			_ifs.read((char*)&index, _boneIndexSize);
		}
	};

	// �{�[��2�ƁA�{�[��1�̃E�F�C�g�l(PMD����)
	class BDEF2 : public IVertexSkining
	{
	public:
		int		index1;		//!< �{�[��1
		int		index2;		//!< �{�[��2
		float	bone1Weight;	//!< �{�[��1�E�F�C�g�l

		void Read(std::ifstream& _ifs, unsigned char _boneIndexSize)
		{
			_ifs.read((char*)&index1, _boneIndexSize);
			_ifs.read((char*)&index2, _boneIndexSize);
			_ifs.read((char*)&bone1Weight, sizeof(float));
		}
	};

	// �{�[��4�ƁA���ꂼ��̃E�F�C�g�l�B�E�F�C�g���v��1.0�ł���ۏ�͂��Ȃ�
	class BDEF4 : public IVertexSkining
	{
	public:
		int		index1;
		int		index2;
		int		index3;
		int		index4;
		float	bone1Weight;
		float	bone2Weight;
		float	bone3Weight;
		float	bone4Weight;

		void Read(std::ifstream& _ifs, unsigned char _boneIndexSize)
		{
			_ifs.read((char*)&index1, _boneIndexSize);
			_ifs.read((char*)&index2, _boneIndexSize);
			_ifs.read((char*)&index3, _boneIndexSize);
			_ifs.read((char*)&index4, _boneIndexSize);
			_ifs.read((char*)&bone1Weight, sizeof(bone1Weight));
			_ifs.read((char*)&bone2Weight, sizeof(bone2Weight));
			_ifs.read((char*)&bone3Weight, sizeof(bone3Weight));
			_ifs.read((char*)&bone4Weight, sizeof(bone4Weight));
		}
	};

	// BDEF2�ɉ����ASDEF�p��float3(Vector3)��3�B���ۂ̌v�Z�ł͂���ɕ␳�l�̎Z�o���K�v(�ꉞ���̂܂�BDEF2�Ƃ��Ă��g�p�\)
	class SDEF : public IVertexSkining
	{
	public:
		int		index1;		//!< �{�[��1
		int		index2;		//!< �{�[��2
		float	bone1Weight;	//!< �{�[��1�E�F�C�g�l
		float3	sdef_C;			//!< SDEF-C�l(x,y,z)
		float3	sdef_R0;		//!< SDEF-R0�l(x,y,z)
		float3	sdef_R1;		//!< SDEF-R1�l(x,y,z) ���C���l��v�v�Z

		void Read(std::ifstream& _ifs, unsigned char _boneIndexSize)
		{
			_ifs.read((char*)&index1, _boneIndexSize);
			_ifs.read((char*)&index2, _boneIndexSize);
			_ifs.read((char*)&bone1Weight, sizeof(bone1Weight));
			_ifs.read((char*)&sdef_C, sizeof(sdef_C));
			_ifs.read((char*)&sdef_R0, sizeof(sdef_R0));
			_ifs.read((char*)&sdef_R1, sizeof(sdef_R1));
		}
	};
	// �E�F�C�g��񂱂��܂�

	// ���_�f�[�^
	struct VertexData
	{
		float3			position;			//!< �ʒu(x,y,z);
		float3			normal;				//!< �@��(x,y,z);
		float2			uv;					//!< UV(u,v);
		float4*			pAddUV;				//!< �ǉ�UV(x,y,z,w)  PMX�w�b�_�̒ǉ�UV���ɂ�� n:�ǉ�UV�� 0�`4
		unsigned char	skiningType;		//!< �E�F�C�g�ό`���� 0:BDEF1 1:BDEF2 2:BDEF4 3:SDEF		
		IVertexSkining*	pSkining;			//!< �E�F�C�g��� ���ό`�����ɂ��p���f�[�^���قȂ�^�Q��Index�� - 1:��Q�Ƃ̏ꍇ������̂Œ���
		float			edgeMagnification;	//!< �G�b�W�{��
	};

	struct Material
	{
		std::wstring	name;					//!< �ގ���
		std::wstring	nameEnglish;			//!< �ގ����p
		float4			diffuse;				//!< Diffuse (R,G,B,A)
		float3			specular;				//!< Specular (R,G,B)
		float			specularPower;			//!< Specular�W��
		float3			ambient;				//!< Ambient (R,G,B)
		unsigned char	drawFlg;				//!< �`��t���O(8bit) - �ebit 0:OFF 1:ON 0x01:���ʕ`��, 0x02 : �n�ʉe, 0x04 : �Z���t�V���h�E�}�b�v�ւ̕`��, 0x08 : �Z���t�V���h�E�̕`��, 0x10 : �G�b�W�`��
		float4			edgeColor;				//!< �G�b�W�F (R,G,B,A)
		float			edgeSize;				//!< �G�b�W�T�C�Y
		int				textureIndex = 0;		//!< �ʏ�e�N�X�`��, �e�N�X�`���e�[�u���̎Q��Index
		int				sphereTextureIndex;		//!< �X�t�B�A�e�N�X�`��, �e�N�X�`���e�[�u���̎Q��Index  ���e�N�X�`���g���q�̐����Ȃ�
		unsigned char	sphereMode;				//!< �X�t�B�A���[�h 0:���� 1:��Z(sph) 2:���Z(spa) 3:�T�u�e�N�X�`��(�ǉ�UV1��x,y��UV�Q�Ƃ��Ēʏ�e�N�X�`���`����s��)
		unsigned char	shareToonFlg;			//!< ���LToon�t���O 0:�p���l�͌�Toon 1:�p���l�͋��LToon
		int				toonTextureIndex;		//!< Toon�e�N�X�`��, �e�N�X�`���e�[�u���̎Q��Index
		char			shareToonTextureIndex;	//!< ���LToon�e�N�X�`��[0�`9] -> ���ꂼ�� toon01.bmp�`toon10.bmp �ɑΉ�
		std::wstring	memo;					//!< ���� : ���R���^�X�N���v�g�L�q�^�G�t�F�N�g�ւ̃p�����[�^�z�u�Ȃ�
		int				faceCount;				//!<  �ގ��ɑΉ������(���_)�� (�K��3�̔{���ɂȂ�)
	};

	struct Bone
	{
		std::wstring	name;						//!< �{�[����
		std::wstring	nameEnglish;				//!< �{�[�����p
		float3			position;					//!< �ʒu
		int				parentIndex;				//!< �e�{�[���C���f�b�N�X
		int				transformHierarchy;			//!< �ό`�K�w

		// �{�[���t���O
		bool			connectionPoint;			//!< �ڑ���(PMD�q�{�[���w��)�\�����@ -> 0:���W�I�t�Z�b�g�Ŏw�� 1:�{�[���Ŏw��
		bool			isRotation;					//!< ��]�\
		bool			isTranslation;				//!< �ړ��\
		bool			isShow;						//!< �\��
		bool			isControl;					//!< ����\
		bool			isIK;						//!< IK
		bool			localGrant;					//!< ���[�J���t�^ | �t�^�Ώ� 0:���[�U�[�ό`�l�^IK�����N�^���d�t�^ 1:�e�̃��[�J���ό`��
		bool			isRotationGrant;			//!< ��]�t�^
		bool			isTranslationGrant;			//!< �ړ��t�^
		bool			isAxisFix;					//!< ���Œ�
		bool			isLocalAxis;				//!< ���[�J����
		bool			transformAfterPhysics;		//!< ������ό`
		bool			externalParentTransform;	//!< �O���e�ό`

		// connectionPoint == 0 �ڑ���:0 �̏ꍇ
		float3			coordinateOffset;			//!< ���W�I�t�Z�b�g, �{�[���ʒu����̑��Ε�

		// connectionPoint == 1 �ڑ���:1 �̏ꍇ
		int				connectionBoneIndex;		//!< �ڑ���{�[���̃{�[��Index

		// isLocalRotationGrant == 1 or isLocalRotationGrant = 1 ��]�t�^:1 �܂��� �ړ��t�^:1 �̏ꍇ
		int				grantParentBoneIndex;		//!< �t�^�e�{�[���̃{�[��Index
		float			grantRate;					//!< �t�^��

		// isAxisFit == 1 ���Œ�:1 �̏ꍇ
		float3			axisDirection;				//!< ���̕����x�N�g��

		// isLocalAxis == 1 ���[�J����:1 �̏ꍇ
		float3			xAxisDirection;				//!< X���̕����x�N�g��
		float3			zAxisDirection;				//!< Z���̕����x�N�g��

		// transformAfterPhysics == 1 �O���e�ό`:1 �̏ꍇ
		int				keyValue;					//!< Key�l

		// isIK == 1 IK:1 �̏ꍇ IK�f�[�^���i�[
		struct IK
		{
			int				boneIndex;				//!< IK�^�[�Q�b�g�{�[���̃{�[��Index
			int				loop;					//!< IK���[�v�� (PMD�y��MMD���ł�255�񂪍ő�ɂȂ�悤�ł�)
			float			loopAngleLimit;			//!< IK���[�v�v�Z����1�񂠂���̐����p�x -> ���W�A���p | PMD��IK�l�Ƃ�4�{�قȂ�̂Œ���
			int				linkCount;				//!< IK�����N�� : �㑱�̗v�f��

			struct Link
			{
				int				boneIndex;			//!< �����N�{�[���̃{�[��Index
				unsigned char	angleLimit;			//!< �p�x����

				// angleLimit == 1 �p�x����:1�̏ꍇ
				float3			min;				//!< ���� (x,y,z) -> ���W�A���p
				float3			max;				//!< ��� (x,y,z) -> ���W�A���p
			};

			std::vector<Link> links;
		};

		IK ik;		//!< IK�f�[�^
	};

#pragma pack(pop)


	//�����o�ϐ�
public:
	std::string	meshFilePath_;	//!< �t�@�C���p�X
	Header			header_;		//!< �w�b�_���
	ModelInfo		modelInfo_;		//!< ���f�����
	int				vertexCount_;	//!< ���_��
	VertexData*		pVertices_;		//!< ���_�z��
	int				indexCount_;	//!< �C���f�b�N�X��
	int*			pIndices_;		//!< �C���f�b�N�X�z��
	int				textureCount_;	//!< �e�N�X�`����
	std::vector<std::string>	textureNames_;	//!< �e�N�X�`���z��
	int				materialCount_;	//!< �}�e���A����
	Material*		pMaterial_;		//!< �}�e���A���z��
	int				boneCount_;		//!< �{�[����
	std::vector<Bone> bones_;		//!< �{�[���r��


	//�����o�֐�
public:
	explicit PMXMesh()
	{

	}

	PMXMesh(PMXMesh&&) = delete;
	PMXMesh(PMXMesh&) = delete;

	explicit PMXMesh(const std::string& _meshFilePath)
	{
		Load(_meshFilePath);
	}

	void LoadHeader()
	{

	}

	void LoadModelInfomation()
	{

	}

	void Load(const std::string& _meshFilePath)
	{
		using namespace utility;

		meshFilePath_ = _meshFilePath;

		// �t�@�C���ǂݍ���
		std::ifstream	ifs(meshFilePath_, std::ios::binary);
		if (ifs.fail())
		{
			// �G���[�I
			return;
		}

		// �w�b�_��ǂ�
		ifs.read((char*)&header_, sizeof(header_));

		// ���f������ǂ�
		modelInfo_.modelName.swap(ReadWString(ifs));
		modelInfo_.modelNameEnglish.swap(ReadWString(ifs));
		modelInfo_.comment.swap(ReadWString(ifs));
		modelInfo_.commentEnglish.swap(ReadWString(ifs));

		// ���_����ǂ�
		ifs.read((char*)&vertexCount_, sizeof(int));

		// ���_���*���_����ǂ�
		pVertices_ = new VertexData[vertexCount_];
		for (int i = 0; i < vertexCount_; i++)
		{
			ifs.read((char*)&pVertices_[i].position, sizeof(pVertices_[i].position));
			ifs.read((char*)&pVertices_[i].normal, sizeof(pVertices_[i].normal));
			ifs.read((char*)&pVertices_[i].uv, sizeof(pVertices_[i].uv));

			if (header_.data[ByteDataDatail::ADD_UV_NUM] > 0)
				pVertices_[i].pAddUV = new float4;

			for (int j = 0; j < header_.data[ByteDataDatail::ADD_UV_NUM]; j++)
			{
				ifs.read((char*)&pVertices_[j].pAddUV, sizeof(float) * 4);
			}

			ifs.read((char*)&pVertices_[i].skiningType, sizeof(pVertices_[i].skiningType));
			switch (pVertices_[i].skiningType)
			{
			case SKININGTYPE_BDEF1:
				pVertices_[i].pSkining = new BDEF1;
				break;

			case SKININGTYPE_BDEF2:
				pVertices_[i].pSkining = new BDEF2;
				break;

			case SKININGTYPE_BDEF4:
				pVertices_[i].pSkining = new BDEF4;
				break;

			case SKININGTYPE_SDEF:
				pVertices_[i].pSkining = new SDEF;
				break;

			default:
				break;
			}
			pVertices_[i].pSkining->Read(ifs, header_.data[BONE_INDEX_SIZE]);

			ifs.read((char*)&pVertices_[i].edgeMagnification, sizeof(pVertices_[i].edgeMagnification));
		}

		// �C���f�b�N�X����ǂ�
		ifs.read((char*)&indexCount_, sizeof(int));
		pIndices_ = new int[indexCount_];
		ZeroMemory(pIndices_, sizeof(int) * indexCount_);

		// �C���f�b�N�X*�C���f�b�N�X����ǂ�
		for (int i = 0; i < indexCount_; i++)
		{
			ifs.read((char*)&pIndices_[i], header_.data[ByteDataDatail::VERTEX_INDEX_SIZE]);
		}
		//indexCount_ /= 3;		// �C���f�b�N�X�������킹��(3�̔{���̂���)

		// �e�N�X�`������ǂ�
		ifs.read((char*)&textureCount_, sizeof(int));

		// �e�N�X�`���p�X*�e�N�X�`������ǂ�
		textureNames_.resize(textureCount_);
		for (int i = 0; i < textureCount_; i++)
		{
			utility::WStringToString(ReadWString(ifs), textureNames_[i]);
		}

		// �ގ�����ǂ�
		ifs.read((char*)&materialCount_, sizeof(int));

		// �ގ�*�ގ�����ǂ�
		pMaterial_ = new Material[materialCount_];
		for (int i = 0; i < materialCount_; i++)
		{
			pMaterial_[i].name.swap(ReadWString(ifs));
			pMaterial_[i].nameEnglish.swap(ReadWString(ifs));
			ifs.read((char*)&pMaterial_[i].diffuse, sizeof(float4));
			ifs.read((char*)&pMaterial_[i].specular, sizeof(float3));
			ifs.read((char*)&pMaterial_[i].specularPower, sizeof(float));
			ifs.read((char*)&pMaterial_[i].ambient, sizeof(float3));
			ifs.read((char*)&pMaterial_[i].drawFlg, sizeof(char));
			ifs.read((char*)&pMaterial_[i].edgeColor, sizeof(float4));
			ifs.read((char*)&pMaterial_[i].edgeSize, sizeof(float));
			ifs.read((char*)&pMaterial_[i].textureIndex, header_.data[TEXTURE_INDEX_SIZE]);
			ifs.read((char*)&pMaterial_[i].sphereTextureIndex, header_.data[TEXTURE_INDEX_SIZE]);
			ifs.read((char*)&pMaterial_[i].sphereMode, sizeof(char));
			ifs.read((char*)&pMaterial_[i].shareToonFlg, sizeof(char));

			if (pMaterial_[i].shareToonFlg)
				ifs.read((char*)&pMaterial_[i].toonTextureIndex, header_.data[TEXTURE_INDEX_SIZE]);
			else
				ifs.read((char*)&pMaterial_[i].shareToonTextureIndex, sizeof(char));

			pMaterial_[i].memo.swap(ReadWString(ifs));
			ifs.read((char*)&pMaterial_[i].faceCount, sizeof(int));
			pMaterial_[i].faceCount /= 3;
		}

		// �{�[������ǂ�
		ifs.read((char*)&boneCount_, sizeof(int));

		// �{�[��*�{�[������ǂ�
		/*bones_.resize(boneCount_);
		for(int i = 0; i < boneCount_; i++)
		{
		bones_[i].name.swap(ReadWString(ifs));
		bones_[i].nameEnglish.swap(ReadWString(ifs));

		ifs.read((char*)&bones_[i].position, sizeof(float3));
		ifs.read((char*)&bones_[i].parentIndex, sizeof(header_.data[BONE_INDEX_SIZE]));
		ifs.read((char*)&bones_[i].transformHierarchy, sizeof(int));

		WORD boneFlg = 0;
		ifs.read((char*)&boneFlg, sizeof(WORD));

		bones_[i].connectionPoint			= boneFlg & 0x0001;
		bones_[i].isRotation				= boneFlg & 0x0002 >> 1;
		bones_[i].isTranslation				= boneFlg & 0x0004 >> 2;
		bones_[i].isShow					= boneFlg & 0x0008 >> 3;
		bones_[i].isControl					= boneFlg & 0x0010 >> 4;
		bones_[i].isIK						= boneFlg & 0x0020 >> 5;
		bones_[i].localGrant				= boneFlg & 0x0080 >> 7;
		bones_[i].isRotationGrant			= boneFlg & 0x0100 >> 8;
		bones_[i].isTranslationGrant		= boneFlg & 0x0200 >> 9;
		bones_[i].isAxisFix					= boneFlg & 0x0400 >> 10;
		bones_[i].isLocalAxis				= boneFlg & 0x0800 >> 11;
		bones_[i].transformAfterPhysics		= boneFlg & 0x1000 >> 12;
		bones_[i].externalParentTransform	= boneFlg & 0x2000 >> 13;

		if(bones_[i].connectionPoint == 0)
		ifs.read((char*)&bones_[i].coordinateOffset, sizeof(float3));
		else
		ifs.read((char*)&bones_[i].connectionBoneIndex, sizeof(header_.data[BONE_INDEX_SIZE]));

		if(bones_[i].isRotationGrant || bones_[i].isTranslationGrant)
		{
		ifs.read((char*)&bones_[i].grantParentBoneIndex, sizeof(header_.data[BONE_INDEX_SIZE]));
		ifs.read((char*)&bones_[i].grantRate, sizeof(float));
		}

		if(bones_[i].isAxisFix)
		ifs.read((char*)&bones_[i].axisDirection, sizeof(float3));

		if(bones_[i].isLocalAxis)
		{
		ifs.read((char*)&bones_[i].xAxisDirection, sizeof(float3));
		ifs.read((char*)&bones_[i].zAxisDirection, sizeof(float3));
		}

		if(bones_[i].externalParentTransform)
		ifs.read((char*)&bones_[i].keyValue, sizeof(int));

		if(bones_[i].isIK)
		{
		ifs.read((char*)&bones_[i].ik.boneIndex, sizeof(header_.data[BONE_INDEX_SIZE]));
		ifs.read((char*)&bones_[i].ik.loop, sizeof(int));
		ifs.read((char*)&bones_[i].ik.loopAngleLimit, sizeof(float));
		ifs.read((char*)&bones_[i].ik.linkCount, sizeof(int));

		bones_[i].ik.links.resize(bones_[i].ik.linkCount);

		auto end = bones_[i].ik.links.end();
		for(auto link = bones_[i].ik.links.begin(); link != end; ++link)
		{
		ifs.read((char*)&link->boneIndex, sizeof(header_.data[BONE_INDEX_SIZE]));
		ifs.read((char*)&link->angleLimit, sizeof(char));

		if(link->angleLimit)
		{
		ifs.read((char*)&link->min, sizeof(float3));
		ifs.read((char*)&link->max, sizeof(float3));
		}
		}
		}
		}*/
	}

	//DirectX9Mesh*  ConvertToDirectX9Mesh(const std::shared_ptr<DirectX9Renderer>& _pRenderer)
	//{
	//	DirectX9Mesh::Vertex* vertices = new DirectX9Mesh::Vertex[vertexCount_];
	//	//std::vector<DirectX9Mesh::Vertex> vertices(vertexCount_);

	//	for(int i = 0; i < vertexCount_; i++)
	//	{
	//		vertices[i].position.x = pVertices_[i].position.x;
	//		vertices[i].position.y = pVertices_[i].position.y;
	//		vertices[i].position.z = pVertices_[i].position.z;
	//		//vertices[i].position.w = 1.0f;

	//		vertices[i].normal.x = pVertices_[i].normal.x;
	//		vertices[i].normal.y = pVertices_[i].normal.y;
	//		vertices[i].normal.z = pVertices_[i].normal.z;

	//		vertices[i].uv.x = pVertices_[i].uv.x;
	//		vertices[i].uv.y = pVertices_[i].uv.y;
	//	}
	//	
	//	std::vector<DirectX9Mesh::Subset> subsets(materialCount_);

	//	unsigned int indexOffset = 0;
	//	for(int i = 0; i < materialCount_; i ++)
	//	{
	//		subsets[i].material.diffuse.r = pMaterial_[i].diffuse.x;
	//		subsets[i].material.diffuse.g = pMaterial_[i].diffuse.y;
	//		subsets[i].material.diffuse.b = pMaterial_[i].diffuse.z;
	//		subsets[i].material.diffuse.a = pMaterial_[i].diffuse.w;

	//		subsets[i].material.ambient.r = pMaterial_[i].ambient.x;
	//		subsets[i].material.ambient.g = pMaterial_[i].ambient.y;
	//		subsets[i].material.ambient.b = pMaterial_[i].ambient.z;
	//		subsets[i].material.ambient.a = 1.0f;

	//		subsets[i].material.specular.r = pMaterial_[i].specular.x;
	//		subsets[i].material.specular.g = pMaterial_[i].specular.y;
	//		subsets[i].material.specular.b = pMaterial_[i].specular.z;
	//		subsets[i].material.specular.a = 1.0f;
	//		subsets[i].material.specularPower = pMaterial_[i].specularPower;

	//		subsets[i].material.emissive.r = 0;
	//		subsets[i].material.emissive.g = 0;
	//		subsets[i].material.emissive.b = 0;
	//		subsets[i].material.emissive.a = 1.0f;

	//		subsets[i].material.textureIndex = pMaterial_[i].textureIndex;
	//		if(pMaterial_[i].textureIndex >= 255)
	//			subsets[i].material.textureIndex = 0;

	//		subsets[i].indexCount = pMaterial_[i].faceCount * 3;
	//		subsets[i].indexOffset = indexOffset;
	//		indexOffset += pMaterial_[i].faceCount * 3;
	//	}

	//	//std::vector<DirectX9Texture> textures(textureCount_);
	//	//for(int i = 0; i < textureCount_; i++)
	//	//{
	//	//	textures[i].LoadFromFile(_pRenderer, pTexturePath_[i]);
	//	//}

	//	// �e�N�X�`���p�X�����s������̑��΃p�X�֕ύX
	//	std::string filePath = meshFilePath_.substr(0, meshFilePath_.find_last_of("/") + 1);

	//	std::vector<std::string> textureFilePaths(textureCount_);

	//	for(int i = 0; i < textureCount_; i++)
	//	{
	//		textureFilePaths[i] = filePath + textureNames_[i];
	//	}

	//	return new DirectX9Mesh(
	//		_pRenderer, 
	//		vertices, 
	//		pIndices_, 
	//		textureFilePaths,
	//		std::move(subsets), 
	//		vertexCount_, 
	//		indexCount_, 
	//		textureCount_,
	//		materialCount_);
	//	//return NULL;

	//	delete[] vertices;
	//}


};