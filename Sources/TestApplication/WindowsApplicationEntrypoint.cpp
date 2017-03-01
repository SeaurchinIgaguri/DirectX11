#include <Windows.h>
//#include "../Application/Win32/ApplicationWin32/ApplicationWin32.h"
#include "D3D11Application/D3D11Application.h"

#define _DEBUGMODE

#ifdef _DEBUGMODE

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)

#endif		// end of #if _DEBUG

/*!-----------------------------------------------------------------------
@brief	Windows�A�v���P�[�V�����G���g���|�C���g
@date	2015/8/19
------------------------------------------------------------------------*/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	
#ifdef _DEBUGMODE

	// ���������[�N���o	
	::_CrtSetBreakAlloc(5440);										// (�R�[�hn�s��)�̃R�[�h�����s���ꂽ���u���[�N�|�C���g�𔭐�������
	::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

#endif		// end of #if _DEBUG

	application::ApplicationSetting applicaionSetting;

	applicaionSetting.applicationName = "D3D11Application";

	d3d11application::D3D11Application d3d11Application(hInstance, nCmdShow, applicaionSetting);

	d3d11Application.BeginPeekMessageLoop();
}