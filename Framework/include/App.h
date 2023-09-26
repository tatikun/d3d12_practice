//
//
//
//
//
#pragma once

//
// Includes
//
#include <Windows.h>
#include <cstdint>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <wrl/client.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>

//
// Linker
// 
#pragma comment (lib, "d3d12.lib")
#pragma comment (lib, "dxgi.lib")
#pragma comment (lib, "d3dcompiler.lib" )

//
// Type definitions.
// 
template<typename T> 
using ComPtr = Microsoft::WRL::ComPtr<T>;


//
// Transform structure
// 
struct alignas(256) Transform
{
    DirectX::XMMATRIX World; // ワールド行列です
    DirectX::XMMATRIX View;  // ビュー行列です
    DirectX::XMMATRIX Proj;  // 射影行列です
};

//
// ConstantBufferView structure
// 
template<typename T>
struct ConstantBufferView
{
    D3D12_CONSTANT_BUFFER_VIEW_DESC Desc;       // 定数バッファの構成設定です
    D3D12_CPU_DESCRIPTOR_HANDLE     HandleCPU;  // CPUディスクリプタハンドルです
    D3D12_GPU_DESCRIPTOR_HANDLE     HandleGPU;  // GPUディスクリプタハンドルです
    T*                              pBuffer;    // バッファ先頭へのポインタです
};


// 
// App class
//
class App
{
    //
    // list of friend classes and methods.
    //
    /* NOTHING */

public:
    //
    // public variables.
    //
    /* NOTHING */

    //
    // public methods
    //
    App(uint32_t width, uint32_t height);
    ~App();
    void Run();

private:
    //
    // private variables.
    //
    static const uint32_t FrameCount = 2; // フレームバッファ数です.

    HINSTANCE m_hInst;     // インスタンスハンドルです.
    HWND      m_hWnd;      // ウィンドウハンドルです.
    uint32_t  m_Width;     // ウィンドウの横幅です.
    uint32_t  m_Height;    // ウィンドウの縦幅です.

    ComPtr<ID3D12Device>                   m_pDevice;                     // デバイスです.
    ComPtr<ID3D12CommandQueue>             m_pQueue;					  // コマンドキューです.
    ComPtr<IDXGISwapChain3>                m_pSwapChain;				  // スワップチェインです.
    ComPtr<ID3D12Resource>                 m_pColorBuffer[FrameCount];	  // カラーバッファです.
    ComPtr<ID3D12CommandAllocator>         m_pCmdAllocator[FrameCount];   // コマンドアロケータです.
    ComPtr<ID3D12GraphicsCommandList>      m_pCmdList;					  // コマンドリストです.
    ComPtr<ID3D12DescriptorHeap>           m_pHeapRTV;					  // ディスクリプタヒープです.(レンダーターゲットビュー)
    ComPtr<ID3D12Fence>                    m_pFence;					  // フェンスです.
    ComPtr<ID3D12DescriptorHeap>           m_pHeapCBV;                    // ディスクリプタヒープです
    ComPtr<ID3D12Resource>                 m_pVB;                          // 頂点バッファです
    ComPtr<ID3D12Resource>                 m_pCB[FrameCount];             // 定数バッファです
    ComPtr<ID3D12RootSignature>            m_RootSignature;               // ルートシグネチャです
    ComPtr<ID3D12PipelineState>            m_pPSO;                        // パイプラインステートです

    HANDLE								   m_FenceEvent;				  // フェンスイベントです.
    uint64_t							   m_FenceCounter[FrameCount];	  // フェンスカウンターです.
    uint32_t							   m_FrameIndex;				  // フレーム番号です.
    D3D12_CPU_DESCRIPTOR_HANDLE			   m_HandleRTV[FrameCount];	  // CPUディスクリプタです.(レンダーターゲットビュー)
    D3D12_VERTEX_BUFFER_VIEW               m_VBV;                     // 頂点バッファビューです
    D3D12_VIEWPORT                         m_Viewport;                // ビューポートです
    D3D12_RECT                             m_Scissor;                 // シザー矩形です
    ConstantBufferView<Transform>          m_CBV[FrameCount];         // 定数バッファビューです
    float                                  m_RotateAngle;             // 回転角です

    //
    // private methods.
    //
    bool InitApp();
    void TermApp();
    bool InitWnd();
    void TermWnd();
    void MainLoop();
    bool InitD3D();
    void TermD3D();
    void Render();
    void WaitGpu();
    void Present(uint32_t interval);
    bool OnInit();
    void OnTerm();

    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

};