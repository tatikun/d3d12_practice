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

//
// Linker
// 
#pragma comment (lib, "d3d12.lib")
#pragma comment (lib, "dxgi.lib")


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

	ID3D12Device*                   m_pDevice;                    // デバイスです.
	ID3D12CommandQueue*             m_pQueue;					  // コマンドキューです.
	IDXGISwapChain3*                m_pSwapChain;				  // スワップチェインです.
	ID3D12Resource*                 m_pColorBuffer[FrameCount];	  // カラーバッファです.
	ID3D12CommandAllocator*         m_pCmdAllocator[FrameCount];  // コマンドアロケータです.
	ID3D12GraphicsCommandList*      m_pCmdList;					  // コマンドリストです.
	ID3D12DescriptorHeap*           m_pHeapRTV;					  // ディスクリプタヒープです.(レンダーターゲットビュー)
	ID3D12Fence*                    m_pFence;					  // フェンスです.
	HANDLE                          m_FenceEvent;				  // フェンスイベントです.
	uint64_t                        m_FenceCounter[FrameCount];	  // フェンスカウンターです.
	uint32_t                        m_FrameIndex;				  // フレーム番号です.
	D3D12_CPU_DESCRIPTOR_HANDLE     m_HandleRTV[FrameCount];	  // CPUディスクリプタです.(レンダーターゲットビュー)

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

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);

};