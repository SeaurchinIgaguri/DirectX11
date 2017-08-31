#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <memory>

namespace resource
{
	namespace mesh
	{


		namespace pmxformat
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
				ENCODE = 0,	//	[0] - �G���R�[�h����		| 0:UTF16 1 : UTF8
				ADD_UV_NUM = 1,	//	[1] - �ǉ�UV��				| 0�`4 �ڍׂ͒��_�Q��
				VERTEX_INDEX_SIZE = 2,	//	[2] - ���_Index�T�C�Y		| 1, 2, 4 �̂����ꂩ
				TEXTURE_INDEX_SIZE = 3,	//	[3] - �e�N�X�`��Index�T�C�Y | 1, 2, 4 �̂����ꂩ
				MATERIAL_INDEX_SIZE = 4,	//	[4] - �ގ�Index�T�C�Y		| 1, 2, 4 �̂����ꂩ
				BONE_INDEX_SIZE = 5,	//	[5] - �{�[��Index�T�C�Y		| 1, 2, 4 �̂����ꂩ
				MORPH_INDEX_SIZE = 6,	//	[6] - ���[�tIndex�T�C�Y		| 1, 2, 4 �̂����ꂩ
				RIGIDBODY_INDEX_SIZE = 7,	//	[7] - ����Index�T�C�Y		| 1, 2, 4 �̂����ꂩ
			};

			// ���f�����
			struct ModelInfo
			{
				std::wstring modelName;		//!< ���f����
				std::wstring modelNameEnglish;	//!< ���f���p�ꖼ
				std::wstring comment;			//!< �R�����g
				std::wstring commentEnglish;	//!< �R�����g�p

				std::size_t GetLength() const
				{
					return modelName.length() + modelNameEnglish.length() + comment.length() + commentEnglish.length();
				}
			};

			// �E�F�C�g��񂱂�����
			enum class SkiningType
			{
				BDEF1,
				BDEF2,
				BDEF4,
				SDEF,
			};

			// �{�[���̂� �C���f�b�N�X�̃o�C�g���͉ς������ڂ炵��int�Œ�
			struct IVertexSkining
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
			struct BDEF2 : public IVertexSkining
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
			struct BDEF4 : public IVertexSkining
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
			struct SDEF : public IVertexSkining
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
				std::unique_ptr<float4>			pAddUV;				//!< �ǉ�UV(x,y,z,w)  PMX�w�b�_�̒ǉ�UV���ɂ�� n:�ǉ�UV�� 0�`4
				unsigned char	skiningType;		//!< �E�F�C�g�ό`���� 0:BDEF1 1:BDEF2 2:BDEF4 3:SDEF		
				std::unique_ptr<IVertexSkining>	pSkining;			//!< �E�F�C�g��� ���ό`�����ɂ��p���f�[�^���قȂ�^�Q��Index�� - 1:��Q�Ƃ̏ꍇ������̂Œ���
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
		};
	}
}	// end of namespace resource