#pragma once
#include <d3d12.h>
#include "DirectXMath.h"
#include <wrl.h>

#include "Material.h"
/// <summary>
/// ライト
/// </summary>
class Light
{
private:// エイリアス
	// Microsoft::WRLを省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;

public:// サブクラス
	// 定数バッファ用データ構造体
	struct ConstBufferData {
		XMVECTOR lightv;		// ライトへの方向を表すベクトル
		XMFLOAT3 lightcolor;	// ライトの色
	};

public:// メンバ関数
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 定数バッファ転送
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
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="cmdList"></param>
	/// <param name="rootParameterIndex"></param>
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);

	static Light* Create();

private:// 静的メンバ変数の実態
	// デバイス
	static ID3D12Device* device;

public:// 静的メンバ関数
	static void StaticInitialize(ID3D12Device* device)
	{
		// 再初期化チェック
		assert(!Light::device);
		// nullptrチェック
		assert(device);
		// 静的メンバ変数のセット
		Light::device = device;
	}

private:// メンバ変数
	// 定数バッファ
	ComPtr<ID3D12Resource>constBuff;
	// ライト光線方向（単位ベクトル）
	XMVECTOR lightdir = { 1,0,0,0 };
	// ライト色
	XMFLOAT3 lightcolor = { 1,1,1 };
	// ダーティフラグ
	bool dirty = false;
};

