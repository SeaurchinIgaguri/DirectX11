#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <WinBase.h>
#include "Library\Utility\WString.h"

class PMXMesh
{
	// PMXのデータ構造
#pragma pack(push, 1)		// アライメントをOFF
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

	// ヘッダー
	struct Header
	{
		unsigned char	magic[4];		//!< "PMX " | ASCIIで 0x50,0x4d,0x58,0x20  ※末尾空白に注意 (PMX1.0は"Pmx "になっているので間違えないように)
		float			version;		//!< PMXバージョン
		unsigned char	dataByteSize;	//!< 後続するデータ列のバイトサイズ
		unsigned char	data[8];		//!< バイト列

	};

	//　バイト列詳細
	enum ByteDataDatail : unsigned int
	{
		ENCODE					= 0,	//	[0] - エンコード方式		| 0:UTF16 1 : UTF8
		ADD_UV_NUM				= 1,	//	[1] - 追加UV数				| 0～4 詳細は頂点参照
		VERTEX_INDEX_SIZE		= 2,	//	[2] - 頂点Indexサイズ		| 1, 2, 4 のいずれか
		TEXTURE_INDEX_SIZE		= 3,	//	[3] - テクスチャIndexサイズ | 1, 2, 4 のいずれか
		MATERIAL_INDEX_SIZE		= 4,	//	[4] - 材質Indexサイズ		| 1, 2, 4 のいずれか
		BONE_INDEX_SIZE			= 5,	//	[5] - ボーンIndexサイズ		| 1, 2, 4 のいずれか
		MORPH_INDEX_SIZE		= 6,	//	[6] - モーフIndexサイズ		| 1, 2, 4 のいずれか
		RIGIDBODY_INDEX_SIZE	= 7,	//	[7] - 剛体Indexサイズ		| 1, 2, 4 のいずれか
	};

	// モデル情報
	struct ModelInfo
	{
		std::wstring modelName;		//!< モデル名
		std::wstring modelNameEnglish;	//!< モデル英語名
		std::wstring comment;			//!< コメント
		std::wstring commentEnglish;	//!< コメント英
	};

	// ウェイト情報ここから
	enum SkiningType
	{
		SKININGTYPE_BDEF1,
		SKININGTYPE_BDEF2,
		SKININGTYPE_BDEF4,
		SKININGTYPE_SDEF,
	};

	// ボーンのみ インデックスのバイト数は可変だがずぼらしてint固定
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

	// ボーン2つと、ボーン1のウェイト値(PMD方式)
	class BDEF2 : public IVertexSkining
	{
	public:
		int		index1;		//!< ボーン1
		int		index2;		//!< ボーン2
		float	bone1Weight;	//!< ボーン1ウェイト値

		void Read(std::ifstream& _ifs, unsigned char _boneIndexSize)
		{
			_ifs.read((char*)&index1, _boneIndexSize);
			_ifs.read((char*)&index2, _boneIndexSize);
			_ifs.read((char*)&bone1Weight, sizeof(float));
		}
	};

	// ボーン4つと、それぞれのウェイト値。ウェイト合計が1.0である保障はしない
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

	// BDEF2に加え、SDEF用のfloat3(Vector3)が3つ。実際の計算ではさらに補正値の算出が必要(一応そのままBDEF2としても使用可能)
	class SDEF : public IVertexSkining
	{
	public:
		int		index1;		//!< ボーン1
		int		index2;		//!< ボーン2
		float	bone1Weight;	//!< ボーン1ウェイト値
		float3	sdef_C;			//!< SDEF-C値(x,y,z)
		float3	sdef_R0;		//!< SDEF-R0値(x,y,z)
		float3	sdef_R1;		//!< SDEF-R1値(x,y,z) ※修正値を要計算

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
	// ウェイト情報ここまで

	// 頂点データ
	struct VertexData
	{
		float3			position;			//!< 位置(x,y,z);
		float3			normal;				//!< 法線(x,y,z);
		float2			uv;					//!< UV(u,v);
		float4*			pAddUV;				//!< 追加UV(x,y,z,w)  PMXヘッダの追加UV数による n:追加UV数 0～4
		unsigned char	skiningType;		//!< ウェイト変形方式 0:BDEF1 1:BDEF2 2:BDEF4 3:SDEF		
		IVertexSkining*	pSkining;			//!< ウェイト情報 ※変形方式により継続データが異なる／参照Indexは - 1:非参照の場合があるので注意
		float			edgeMagnification;	//!< エッジ倍率
	};

	struct Material
	{
		std::wstring	name;					//!< 材質名
		std::wstring	nameEnglish;			//!< 材質名英
		float4			diffuse;				//!< Diffuse (R,G,B,A)
		float3			specular;				//!< Specular (R,G,B)
		float			specularPower;			//!< Specular係数
		float3			ambient;				//!< Ambient (R,G,B)
		unsigned char	drawFlg;				//!< 描画フラグ(8bit) - 各bit 0:OFF 1:ON 0x01:両面描画, 0x02 : 地面影, 0x04 : セルフシャドウマップへの描画, 0x08 : セルフシャドウの描画, 0x10 : エッジ描画
		float4			edgeColor;				//!< エッジ色 (R,G,B,A)
		float			edgeSize;				//!< エッジサイズ
		int				textureIndex = 0;		//!< 通常テクスチャ, テクスチャテーブルの参照Index
		int				sphereTextureIndex;		//!< スフィアテクスチャ, テクスチャテーブルの参照Index  ※テクスチャ拡張子の制限なし
		unsigned char	sphereMode;				//!< スフィアモード 0:無効 1:乗算(sph) 2:加算(spa) 3:サブテクスチャ(追加UV1のx,yをUV参照して通常テクスチャ描画を行う)
		unsigned char	shareToonFlg;			//!< 共有Toonフラグ 0:継続値は個別Toon 1:継続値は共有Toon
		int				toonTextureIndex;		//!< Toonテクスチャ, テクスチャテーブルの参照Index
		char			shareToonTextureIndex;	//!< 共有Toonテクスチャ[0～9] -> それぞれ toon01.bmp～toon10.bmp に対応
		std::wstring	memo;					//!< メモ : 自由欄／スクリプト記述／エフェクトへのパラメータ配置など
		int				faceCount;				//!<  材質に対応する面(頂点)数 (必ず3の倍数になる)
	};

	struct Bone
	{
		std::wstring	name;						//!< ボーン名
		std::wstring	nameEnglish;				//!< ボーン名英
		float3			position;					//!< 位置
		int				parentIndex;				//!< 親ボーンインデックス
		int				transformHierarchy;			//!< 変形階層

		// ボーンフラグ
		bool			connectionPoint;			//!< 接続先(PMD子ボーン指定)表示方法 -> 0:座標オフセットで指定 1:ボーンで指定
		bool			isRotation;					//!< 回転可能
		bool			isTranslation;				//!< 移動可能
		bool			isShow;						//!< 表示
		bool			isControl;					//!< 操作可能
		bool			isIK;						//!< IK
		bool			localGrant;					//!< ローカル付与 | 付与対象 0:ユーザー変形値／IKリンク／多重付与 1:親のローカル変形量
		bool			isRotationGrant;			//!< 回転付与
		bool			isTranslationGrant;			//!< 移動付与
		bool			isAxisFix;					//!< 軸固定
		bool			isLocalAxis;				//!< ローカル軸
		bool			transformAfterPhysics;		//!< 物理後変形
		bool			externalParentTransform;	//!< 外部親変形

		// connectionPoint == 0 接続先:0 の場合
		float3			coordinateOffset;			//!< 座標オフセット, ボーン位置からの相対分

		// connectionPoint == 1 接続先:1 の場合
		int				connectionBoneIndex;		//!< 接続先ボーンのボーンIndex

		// isLocalRotationGrant == 1 or isLocalRotationGrant = 1 回転付与:1 または 移動付与:1 の場合
		int				grantParentBoneIndex;		//!< 付与親ボーンのボーンIndex
		float			grantRate;					//!< 付与率

		// isAxisFit == 1 軸固定:1 の場合
		float3			axisDirection;				//!< 軸の方向ベクトル

		// isLocalAxis == 1 ローカル軸:1 の場合
		float3			xAxisDirection;				//!< X軸の方向ベクトル
		float3			zAxisDirection;				//!< Z軸の方向ベクトル

		// transformAfterPhysics == 1 外部親変形:1 の場合
		int				keyValue;					//!< Key値

		// isIK == 1 IK:1 の場合 IKデータを格納
		struct IK
		{
			int				boneIndex;				//!< IKターゲットボーンのボーンIndex
			int				loop;					//!< IKループ回数 (PMD及びMMD環境では255回が最大になるようです)
			float			loopAngleLimit;			//!< IKループ計算時の1回あたりの制限角度 -> ラジアン角 | PMDのIK値とは4倍異なるので注意
			int				linkCount;				//!< IKリンク数 : 後続の要素数

			struct Link
			{
				int				boneIndex;			//!< リンクボーンのボーンIndex
				unsigned char	angleLimit;			//!< 角度制限

				// angleLimit == 1 角度制限:1の場合
				float3			min;				//!< 下限 (x,y,z) -> ラジアン角
				float3			max;				//!< 上限 (x,y,z) -> ラジアン角
			};

			std::vector<Link> links;
		};

		IK ik;		//!< IKデータ
	};

#pragma pack(pop)


	//メンバ変数
public:
	std::string	meshFilePath_;	//!< ファイルパス
	Header			header_;		//!< ヘッダ情報
	ModelInfo		modelInfo_;		//!< モデル情報
	int				vertexCount_;	//!< 頂点数
	VertexData*		pVertices_;		//!< 頂点配列
	int				indexCount_;	//!< インデックス数
	int*			pIndices_;		//!< インデックス配列
	int				textureCount_;	//!< テクスチャ数
	std::vector<std::string>	textureNames_;	//!< テクスチャ配列
	int				materialCount_;	//!< マテリアル数
	Material*		pMaterial_;		//!< マテリアル配列
	int				boneCount_;		//!< ボーン数
	std::vector<Bone> bones_;		//!< ボーン排列


	//メンバ関数
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

		// ファイル読み込み
		std::ifstream	ifs(meshFilePath_, std::ios::binary);
		if (ifs.fail())
		{
			// エラー！
			return;
		}

		// ヘッダを読む
		ifs.read((char*)&header_, sizeof(header_));

		// モデル情報を読む
		modelInfo_.modelName.swap(ReadWString(ifs));
		modelInfo_.modelNameEnglish.swap(ReadWString(ifs));
		modelInfo_.comment.swap(ReadWString(ifs));
		modelInfo_.commentEnglish.swap(ReadWString(ifs));

		// 頂点数を読む
		ifs.read((char*)&vertexCount_, sizeof(int));

		// 頂点情報*頂点数を読む
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

		// インデックス数を読む
		ifs.read((char*)&indexCount_, sizeof(int));
		pIndices_ = new int[indexCount_];
		ZeroMemory(pIndices_, sizeof(int) * indexCount_);

		// インデックス*インデックス数を読む
		for (int i = 0; i < indexCount_; i++)
		{
			ifs.read((char*)&pIndices_[i], header_.data[ByteDataDatail::VERTEX_INDEX_SIZE]);
		}
		//indexCount_ /= 3;		// インデックス数を合わせる(3の倍数のため)

		// テクスチャ数を読む
		ifs.read((char*)&textureCount_, sizeof(int));

		// テクスチャパス*テクスチャ数を読む
		textureNames_.resize(textureCount_);
		for (int i = 0; i < textureCount_; i++)
		{
			utility::WStringToString(ReadWString(ifs), textureNames_[i]);
		}

		// 材質数を読む
		ifs.read((char*)&materialCount_, sizeof(int));

		// 材質*材質数を読む
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

		// ボーン数を読む
		ifs.read((char*)&boneCount_, sizeof(int));

		// ボーン*ボーン数を読む
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

	//	// テクスチャパスを実行環境からの相対パスへ変更
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