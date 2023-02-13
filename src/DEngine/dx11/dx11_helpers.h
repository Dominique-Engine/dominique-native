/**
 * @file dx11_helpers.h
 * @author Copied from DearImGui (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2021-11-21
 *
 *
 */
// TODO understand, refactor and improve everything here
#pragma once

#include <d3d11.h>
#include <dxgi.h>

#pragma comment(lib, "dxgi")

struct DEDirectX11Context {
  // TODO this are COM interfaces(light COM), check if its better to put them in
  // global scope as in DearImGui code
  ID3D11Device* pd3dDevice = nullptr;
  ID3D11DeviceContext* pd3dDeviceContext = nullptr;
  IDXGISwapChain* pSwapChain = nullptr;
  ID3D11RenderTargetView* mainRenderTargetView = nullptr;
  D3D11_TEXTURE2D_DESC backBufferDesc;
  ID3D11Texture2D* pDepthStencil;
  ID3D11DepthStencilView* pDepthStencilView;
};

namespace dengine {

// Helper functions TODO: separate implementation from definition if needed
void CreateRenderTarget(DEDirectX11Context& dxContext);
void CreateDepthStencilBuffer(DEDirectX11Context& dxContext);

bool CreateDeviceD3D(HWND hWnd, DEDirectX11Context& dxContext,
                     const bool debug = false);

void CleanupRenderTarget(DEDirectX11Context& dxContext);

void CleanupDeviceD3D(DEDirectX11Context& dxContext);
}  // namespace dengine

int GetDefaultAdapterDesc(DXGI_ADAPTER_DESC& desc);
