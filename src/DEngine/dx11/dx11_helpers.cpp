#include "dx11_helpers.h"

#pragma comment(lib, "dxgi")

// Helper functions TODO: separate implementation from definition if needed
void dengine::CreateRenderTarget(DEDirectX11Context& dxContext) {
  ID3D11Texture2D* pBackBuffer;
  dxContext.pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
  dxContext.pd3dDevice->CreateRenderTargetView(pBackBuffer, NULL,
                                               &dxContext.mainRenderTargetView);
  pBackBuffer->Release();
}

bool dengine::CreateDeviceD3D(HWND hWnd, DEDirectX11Context& dxContext,
                              const bool debug) {
  // Setup swap chain
  DXGI_SWAP_CHAIN_DESC sd;
  ZeroMemory(&sd, sizeof(sd));
  sd.BufferCount = 2;
  sd.BufferDesc.Width = 0;
  sd.BufferDesc.Height = 0;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferDesc.RefreshRate.Numerator = 60;
  sd.BufferDesc.RefreshRate.Denominator = 1;
  sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
  sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.OutputWindow = hWnd;
  sd.SampleDesc.Count = 1;    // for antialiasing
  sd.SampleDesc.Quality = 0;  // for antialiasing
  sd.Windowed = TRUE;
  sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

  UINT createDeviceFlags = 0;
  if (debug)
    createDeviceFlags |=
        D3D11_CREATE_DEVICE_DEBUG;  // TODO not working in debug mode
  D3D_FEATURE_LEVEL featureLevel;
  const D3D_FEATURE_LEVEL featureLevelArray[2] = {
      D3D_FEATURE_LEVEL_11_0,
      D3D_FEATURE_LEVEL_10_0,
  };
  if (D3D11CreateDeviceAndSwapChain(
          NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags,
          featureLevelArray, 2, D3D11_SDK_VERSION, &sd, &dxContext.pSwapChain,
          &dxContext.pd3dDevice, &featureLevel,
          &dxContext.pd3dDeviceContext) != S_OK) {
    return false;
  }

  CreateRenderTarget(dxContext);
  return true;
}

void dengine::CleanupRenderTarget(DEDirectX11Context& dxContext) {
  if (dxContext.mainRenderTargetView) {
    dxContext.mainRenderTargetView->Release();
    dxContext.mainRenderTargetView = NULL;
  }
}

void dengine::CleanupDeviceD3D(DEDirectX11Context& dxContext) {
  CleanupRenderTarget(dxContext);
  if (dxContext.pSwapChain) {
    dxContext.pSwapChain->Release();
    dxContext.pSwapChain = NULL;
  }
  if (dxContext.pd3dDeviceContext) {
    dxContext.pd3dDeviceContext->Release();
    dxContext.pd3dDeviceContext = NULL;
  }
  if (dxContext.pd3dDevice) {
    dxContext.pd3dDevice->Release();
    dxContext.pd3dDevice = NULL;
  }
}

int GetDefaultAdapterDesc(DXGI_ADAPTER_DESC& desc) {
  IDXGIFactory* factory = nullptr;

  if (SUCCEEDED(CreateDXGIFactory(IID_PPV_ARGS(&factory)))) {
    IDXGIAdapter* adapter = nullptr;

    if (SUCCEEDED(factory->EnumAdapters(0, &adapter))) {
      adapter->GetDesc(&desc);
      adapter->Release();
    }

    factory->Release();
  }

  return 0;
}
