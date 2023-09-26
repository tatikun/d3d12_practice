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
    DirectX::XMMATRIX World; // ���[���h�s��ł�
    DirectX::XMMATRIX View;  // �r���[�s��ł�
    DirectX::XMMATRIX Proj;  // �ˉe�s��ł�
};

//
// ConstantBufferView structure
// 
template<typename T>
struct ConstantBufferView
{
    D3D12_CONSTANT_BUFFER_VIEW_DESC Desc;       // �萔�o�b�t�@�̍\���ݒ�ł�
    D3D12_CPU_DESCRIPTOR_HANDLE     HandleCPU;  // CPU�f�B�X�N���v�^�n���h���ł�
    D3D12_GPU_DESCRIPTOR_HANDLE     HandleGPU;  // GPU�f�B�X�N���v�^�n���h���ł�
    T*                              pBuffer;    // �o�b�t�@�擪�ւ̃|�C���^�ł�
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
    static const uint32_t FrameCount = 2; // �t���[���o�b�t�@���ł�.

    HINSTANCE m_hInst;     // �C���X�^���X�n���h���ł�.
    HWND      m_hWnd;      // �E�B���h�E�n���h���ł�.
    uint32_t  m_Width;     // �E�B���h�E�̉����ł�.
    uint32_t  m_Height;    // �E�B���h�E�̏c���ł�.

    ComPtr<ID3D12Device>                   m_pDevice;                     // �f�o�C�X�ł�.
    ComPtr<ID3D12CommandQueue>             m_pQueue;					  // �R�}���h�L���[�ł�.
    ComPtr<IDXGISwapChain3>                m_pSwapChain;				  // �X���b�v�`�F�C���ł�.
    ComPtr<ID3D12Resource>                 m_pColorBuffer[FrameCount];	  // �J���[�o�b�t�@�ł�.
    ComPtr<ID3D12CommandAllocator>         m_pCmdAllocator[FrameCount];   // �R�}���h�A���P�[�^�ł�.
    ComPtr<ID3D12GraphicsCommandList>      m_pCmdList;					  // �R�}���h���X�g�ł�.
    ComPtr<ID3D12DescriptorHeap>           m_pHeapRTV;					  // �f�B�X�N���v�^�q�[�v�ł�.(�����_�[�^�[�Q�b�g�r���[)
    ComPtr<ID3D12Fence>                    m_pFence;					  // �t�F���X�ł�.
    ComPtr<ID3D12DescriptorHeap>           m_pHeapCBV;                    // �f�B�X�N���v�^�q�[�v�ł�
    ComPtr<ID3D12Resource>                 m_pVB;                          // ���_�o�b�t�@�ł�
    ComPtr<ID3D12Resource>                 m_pCB[FrameCount];             // �萔�o�b�t�@�ł�
    ComPtr<ID3D12RootSignature>            m_RootSignature;               // ���[�g�V�O�l�`���ł�
    ComPtr<ID3D12PipelineState>            m_pPSO;                        // �p�C�v���C���X�e�[�g�ł�

    HANDLE								   m_FenceEvent;				  // �t�F���X�C�x���g�ł�.
    uint64_t							   m_FenceCounter[FrameCount];	  // �t�F���X�J�E���^�[�ł�.
    uint32_t							   m_FrameIndex;				  // �t���[���ԍ��ł�.
    D3D12_CPU_DESCRIPTOR_HANDLE			   m_HandleRTV[FrameCount];	  // CPU�f�B�X�N���v�^�ł�.(�����_�[�^�[�Q�b�g�r���[)
    D3D12_VERTEX_BUFFER_VIEW               m_VBV;                     // ���_�o�b�t�@�r���[�ł�
    D3D12_VIEWPORT                         m_Viewport;                // �r���[�|�[�g�ł�
    D3D12_RECT                             m_Scissor;                 // �V�U�[��`�ł�
    ConstantBufferView<Transform>          m_CBV[FrameCount];         // �萔�o�b�t�@�r���[�ł�
    float                                  m_RotateAngle;             // ��]�p�ł�

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