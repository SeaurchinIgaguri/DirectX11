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
				ENCODE = 0,	//	[0] - エンコード方式		| 0:UTF16 1 : UTF8
				ADD_UV_NUM = 1,	//	[1] - 追加UV数				| 0～4 詳細は頂点参照
				VERTEX_INDEX_SIZE = 2,	//	[2] - 頂点Indexサイズ		| 1, 2, 4 のいずれか
				TEXTURE_INDEX_SIZE = 3,	//	[3] - テクスチャIndexサイズ | 1, 2, 4 のいずれか
				MATERIAL_INDEX_SIZE = 4,	//	[4] - 材質Indexサイズ		| 1, 2, 4 のいずれか
				BONE_INDEX_SIZE = 5,	//	[5] - ボーンIndexサイズ		| 1, 2, 4 のいずれか
				MORPH_INDEX_SIZE = 6,	//	[6] - モーフIndexサイズ		| 1, 2, 4 のいずれか
				RIGIDBODY_INDEX_SIZE = 7,	//	[7] - 剛体Indexサイズ		| 1, 2, 4 のいずれか
			};

			// モデル情報
			struct ModelInfo
			{
				std::wstring modelName;		//!< モデル名
				std::wstring modelNameEnglish;	//!< モデル英語名
				std::wstring comment;			//!< コメント
				std::wstring commentEnglish;	//!< コメント英

				std::size_t GetLength() const
				{
					return modelName.length() + modelNameEnglish.length() + comment.length() + commentEnglish.length();
				}
			};

			// ウェイト情報ここから
			enum class SkiningType
			{
				BDEF1,
				BDEF2,
				BDEF4,
				SDEF,
			};

			// ボーンのみ インデックスのバイト数は可変だがずぼらしてint固定
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

			// ボーン2つと、ボーン1のウェイト値(PMD方式)
			struct BDEF2 : public IVertexSkining
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

			// BDEF2に加え、SDEF用のfloat3(Vector3)が3つ。実際の計算ではさらに補正値の算出が必要(一応そのままBDEF2としても使用可能)
			struct SDEF : public IVertexSkining
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
				std::unique_ptr<float4>			pAddUV;				//!< 追加UV(x,y,z,w)  PMXヘッダの追加UV数による n:追加UV数 0～4
				unsigned char	skiningType;		//!< ウェイト変形方式 0:BDEF1 1:BDEF2 2:BDEF4 3:SDEF		
				std::unique_ptr<IVertexSkining>	pSkining;			//!< ウェイト情報 ※変形方式により継続データが異なる／参照Indexは - 1:非参照の場合があるので注意
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
		};
	}
}	// end of namespace resource