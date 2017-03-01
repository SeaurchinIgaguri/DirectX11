//#include "GraphicDeviceD3D9.h"
//
//namespace graphics
//{
//	namespace d3d9
//	{
//
//		//GraphicDeviceD3D9::GraphicDeviceD3D9(HWND _hWnd, bool _isWindowMode, unsigned int _backBufferWidth, unsigned int _backBufferHeight)
//		//{
//		//	//D3DPRESENT_PARAMETERS d3dpp_;
//		//	D3DDISPLAYMODE d3ddm;
//
//		//	// Direct3Dオブジェクトの生成
//		//	auto pDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION);
//
//		//	if (pDirect3D9 == NULL)
//		//	{
//		//		throw std;
//		//	}
//
//		//	// 現在のディスプレイモードを取得
//		//	if (FAILED(pDirect3D_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
//		//	{
//		//		return E_FAIL;
//		//	}
//
//		//	// デバイスのプレゼンテーションパラメータの設定
//		//	ZeroMemory(&d3dpp_, sizeof(d3dpp_));								// ワークをゼロクリア
//		//	d3dpp_.BackBufferCount = 1;							// バックバッファの数
//		//	d3dpp_.BackBufferWidth = _backBufferWidth;				// ゲーム画面サイズ(幅)
//		//	d3dpp_.BackBufferHeight = _backBufferHeight;			// ゲーム画面サイズ(高さ)
//		//	d3dpp_.BackBufferFormat = D3DFMT_UNKNOWN;				// バックバッファのフォーマットは現在設定されているものを使う
//		//	d3dpp_.SwapEffect = D3DSWAPEFFECT_DISCARD;		// 映像信号に同期してフリップする
//		//	d3dpp_.Windowed = bWindow;						// ウィンドウモード
//		//	d3dpp_.EnableAutoDepthStencil = TRUE;							// デプスバッファ（Ｚバッファ）とステンシルバッファを作成
//		//	d3dpp_.AutoDepthStencilFormat = D3DFMT_D16;					// デプスバッファとして16bitを使う
//
//		//	if (bWindow)
//		//	{// ウィンドウモード
//		//		d3dpp_.BackBufferFormat = D3DFMT_UNKNOWN;					// バックバッファ
//		//		d3dpp_.FullScreen_RefreshRateInHz = 0;								// リフレッシュレート
//		//		d3dpp_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// インターバル
//		//	}
//		//	else
//		//	{// フルスクリーンモード
//		//		d3dpp_.BackBufferFormat = D3DFMT_R5G6B5;					// バックバッファ
//		//		d3dpp_.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// リフレッシュレート
//		//		d3dpp_.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// インターバル
//		//	}
//
//		//	// デバイスオブジェクトの生成
//		//	// [デバイス作成制御]<描画>と<頂点処理>をハードウェアで行なう
//		//	if (FAILED(pDirect3D_->CreateDevice(D3DADAPTER_DEFAULT,						// ディスプレイアダプタ
//		//		D3DDEVTYPE_HAL,															// ディスプレイタイプ
//		//		hWnd,																	// フォーカスするウインドウへのハンドル
//		//		D3DCREATE_HARDWARE_VERTEXPROCESSING,									// デバイス作成制御の組み合わせ
//		//		&d3dpp_,																	// デバイスのプレゼンテーションパラメータ
//		//		&pDirect3DDevice_)))													// デバイスインターフェースへのポインタ
//		//	{
//		//		// 上記の設定が失敗したら
//		//		// [デバイス作成制御]<描画>をハードウェアで行い、<頂点処理>はCPUで行なう
//		//		if (FAILED(pDirect3D_->CreateDevice(D3DADAPTER_DEFAULT,
//		//			D3DDEVTYPE_HAL,
//		//			hWnd,
//		//			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
//		//			&d3dpp_,
//		//			&pDirect3DDevice_)))
//		//		{
//		//			// 上記の設定が失敗したら
//		//			// [デバイス作成制御]<描画>と<頂点処理>をCPUで行なう
//		//			if (FAILED(pDirect3D_->CreateDevice(D3DADAPTER_DEFAULT,
//		//				D3DDEVTYPE_REF,
//		//				hWnd,
//		//				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
//		//				&d3dpp_,
//		//				&pDirect3DDevice_)))
//		//			{
//		//				// 初期化失敗
//		//				return E_FAIL;
//		//			}
//		//		}
//		//	}
//		//}
//
//
//		GraphicDeviceD3D9::~GraphicDeviceD3D9()
//		{
//		}
//
//
//	}	// end of namespace d3d9
//
//}	// end of namespace graphics
//
