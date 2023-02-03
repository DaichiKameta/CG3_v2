#pragma once
#include <d3d12.h>
#include "DirectXMath.h"
#include <wrl.h>

#include "Material.h"
/// <summary>
/// ���C�g
/// </summary>
class Light
{
private:// �G�C���A�X
	// Microsoft::WRL���ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:// �T�u�N���X
	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData {
		XMVECTOR lightv;		// ���C�g�ւ̕�����\���x�N�g��
		XMFLOAT3 lightcolor;	// ���C�g�̐F
	};

public:// �����o�֐�
	/// <summary>
	/// ������
	/// </summary>
	void Initialize();

	/// <summary>
	/// �萔�o�b�t�@�]��
	/// </summary>
	void TransferConstBuffer();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="lightdir"></param>
	void SetLightDir(const XMVECTOR& lightdir);

	/// <summary>
	/// 
	/// </summary>
	/// <param name="lightcolor"></param>
	void SetLightColor(const XMFLOAT3& lightcolor);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="cmdList"></param>
	/// <param name="rootParameterIndex"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

	static Light* Create();

private:// �ÓI�����o�ϐ��̎���
	// �f�o�C�X
	static ID3D12Device* device;

public:// �ÓI�����o�֐�
	static void StaticInitialize(ID3D12Device* device)
	{
		// �ď������`�F�b�N
		assert(!Light::device);
		// nullptr�`�F�b�N
		assert(device);
		// �ÓI�����o�ϐ��̃Z�b�g
		Light::device = device;
	}

private:// �����o�ϐ�
	// �萔�o�b�t�@
	ComPtr<ID3D12Resource>constBuff;
	// ���C�g���������i�P�ʃx�N�g���j
	XMVECTOR lightdir = { 1,0,0,0 };
	// ���C�g�F
	XMFLOAT3 lightcolor = { 1,1,1 };
	// �_�[�e�B�t���O
	bool dirty = false;
};

