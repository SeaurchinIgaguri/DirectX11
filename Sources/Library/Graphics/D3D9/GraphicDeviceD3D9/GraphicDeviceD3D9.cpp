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
//		//	// Direct3D�I�u�W�F�N�g�̐���
//		//	auto pDirect3D9 = Direct3DCreate9(D3D_SDK_VERSION);
//
//		//	if (pDirect3D9 == NULL)
//		//	{
//		//		throw std;
//		//	}
//
//		//	// ���݂̃f�B�X�v���C���[�h���擾
//		//	if (FAILED(pDirect3D_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
//		//	{
//		//		return E_FAIL;
//		//	}
//
//		//	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^�̐ݒ�
//		//	ZeroMemory(&d3dpp_, sizeof(d3dpp_));								// ���[�N���[���N���A
//		//	d3dpp_.BackBufferCount = 1;							// �o�b�N�o�b�t�@�̐�
//		//	d3dpp_.BackBufferWidth = _backBufferWidth;				// �Q�[����ʃT�C�Y(��)
//		//	d3dpp_.BackBufferHeight = _backBufferHeight;			// �Q�[����ʃT�C�Y(����)
//		//	d3dpp_.BackBufferFormat = D3DFMT_UNKNOWN;				// �o�b�N�o�b�t�@�̃t�H�[�}�b�g�͌��ݐݒ肳��Ă�����̂��g��
//		//	d3dpp_.SwapEffect = D3DSWAPEFFECT_DISCARD;		// �f���M���ɓ������ăt���b�v����
//		//	d3dpp_.Windowed = bWindow;						// �E�B���h�E���[�h
//		//	d3dpp_.EnableAutoDepthStencil = TRUE;							// �f�v�X�o�b�t�@�i�y�o�b�t�@�j�ƃX�e���V���o�b�t�@���쐬
//		//	d3dpp_.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
//
//		//	if (bWindow)
//		//	{// �E�B���h�E���[�h
//		//		d3dpp_.BackBufferFormat = D3DFMT_UNKNOWN;					// �o�b�N�o�b�t�@
//		//		d3dpp_.FullScreen_RefreshRateInHz = 0;								// ���t���b�V�����[�g
//		//		d3dpp_.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;	// �C���^�[�o��
//		//	}
//		//	else
//		//	{// �t���X�N���[�����[�h
//		//		d3dpp_.BackBufferFormat = D3DFMT_R5G6B5;					// �o�b�N�o�b�t�@
//		//		d3dpp_.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			// ���t���b�V�����[�g
//		//		d3dpp_.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		// �C���^�[�o��
//		//	}
//
//		//	// �f�o�C�X�I�u�W�F�N�g�̐���
//		//	// [�f�o�C�X�쐬����]<�`��>��<���_����>���n�[�h�E�F�A�ōs�Ȃ�
//		//	if (FAILED(pDirect3D_->CreateDevice(D3DADAPTER_DEFAULT,						// �f�B�X�v���C�A�_�v�^
//		//		D3DDEVTYPE_HAL,															// �f�B�X�v���C�^�C�v
//		//		hWnd,																	// �t�H�[�J�X����E�C���h�E�ւ̃n���h��
//		//		D3DCREATE_HARDWARE_VERTEXPROCESSING,									// �f�o�C�X�쐬����̑g�ݍ��킹
//		//		&d3dpp_,																	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^
//		//		&pDirect3DDevice_)))													// �f�o�C�X�C���^�[�t�F�[�X�ւ̃|�C���^
//		//	{
//		//		// ��L�̐ݒ肪���s������
//		//		// [�f�o�C�X�쐬����]<�`��>���n�[�h�E�F�A�ōs���A<���_����>��CPU�ōs�Ȃ�
//		//		if (FAILED(pDirect3D_->CreateDevice(D3DADAPTER_DEFAULT,
//		//			D3DDEVTYPE_HAL,
//		//			hWnd,
//		//			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
//		//			&d3dpp_,
//		//			&pDirect3DDevice_)))
//		//		{
//		//			// ��L�̐ݒ肪���s������
//		//			// [�f�o�C�X�쐬����]<�`��>��<���_����>��CPU�ōs�Ȃ�
//		//			if (FAILED(pDirect3D_->CreateDevice(D3DADAPTER_DEFAULT,
//		//				D3DDEVTYPE_REF,
//		//				hWnd,
//		//				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
//		//				&d3dpp_,
//		//				&pDirect3DDevice_)))
//		//			{
//		//				// ���������s
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
