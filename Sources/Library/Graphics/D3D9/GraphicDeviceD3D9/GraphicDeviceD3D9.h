//#pragma once
//
//#include <d3dx9.h>
//#pragma comment	(lib, "d3d9.lib")		// 描画処理に必要
//#pragma comment (lib, "d3dx9.lib")		// [d3d9.lib]の拡張ライブラリ
//#pragma comment (lib, "dxguid.lib")		// DirectXコンポーネント使用に必要
//
//#include "../../../Utility/Detachable.h"
//#include "../../../Utility/COMPointer.h"
//
//namespace graphics
//{
//	namespace d3d9
//	{
//
//		
//		class GraphicDeviceD3D9 : public utility::Detachable
//		{
//		public:
//			//GraphicDeviceD3D9(HWND hWnd, bool isWindowMode, unsigned int backBufferWidth, unsigned int backBufferHeight);
//
//			~GraphicDeviceD3D9();
//
//			IDirect3D9* GetIDirect3D() const;
//
//			IDirect3DDevice9* GetIDirect3D9Device() const;
//
//		private:
//			std::shared_ptr<IDirect3D9>			pIDirect3D9_;
//			std::shared_ptr<IDirect3DDevice9>	pIDirect3DDevice9_;
//
//			D3DPRESENT_PARAMETERS d3dpp_;
//		};
//
//
//
//	}	// end of namespace d3d9
//
//}	// end of namespace graphics