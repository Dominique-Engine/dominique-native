#include "coreDX11.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_syswm.h>
#include <d3d11.h>
#include <dengine/spdlog_helper.h>

#include "dx11_helpers.h"
#include "d3dcompiler.h"
#include "shaders.h"

DEDirectX11Context _dxContext;

int dengine::core::InitDX11(DE &engine) {
  auto logger = getMultiSinkLogger();

  // initialize SDL
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    logger.error("Couldn't initialize SDL: {}", SDL_GetError());
    return 1;  // sdl could not initialize
  }
  // clean up SDL
  atexit(SDL_Quit);

  // Also request a depth buffer
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

  // if succeeded create our window
  engine.windowHandler = SDL_CreateWindow(
      engine.config.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
      engine.config.width, engine.config.height,
      SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);

  if (engine.windowHandler == NULL) {
    logger.error("Couldn't set video mode: {}", SDL_GetError());
    return 1;
  }

  // if the window creation succeeded create our renderer
  SDL_SysWMinfo wmInfo;
  SDL_VERSION(&wmInfo.version);
  SDL_GetWindowWMInfo(engine.windowHandler, &wmInfo);
  HWND hwnd = (HWND)wmInfo.info.win.window;

  // Initialize Direct3D
  if (!CreateDeviceD3D(hwnd, _dxContext, false)) {
    logger.error("Failed to initialize DirectX");
    CleanupDeviceD3D(_dxContext);
    return 1;
  }

  DXGI_ADAPTER_DESC tempDescription;
  GetDefaultAdapterDesc(tempDescription);

  // Turn this into some useful information
  logger.info("DirectX11 loaded");
  std::wstring_view ws(tempDescription.Description);
  std::string s(ws.begin(), ws.end());
  logger.info("Vendor:   {}, Renderer: {}, Version:  {}",
              tempDescription.VendorId, s,
              _dxContext.pd3dDevice->GetFeatureLevel());

  return 0;
}

void dengine::core::RenderDX11(DE &engine, const RenderDataDX11 &data) {
  // _dxContext.pd3dDeviceContext->UpdateSubresource(m_pConstantBuffer.Get(), 0,
  // nullptr,
  //                            &m_constantBufferData, 0, 0);

  _dxContext.pd3dDeviceContext->ClearRenderTargetView(
      _dxContext.mainRenderTargetView, engine.config.clearColor);

  _dxContext.pd3dDeviceContext->ClearDepthStencilView(
      _dxContext.pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
      1.0f, 0);

  _dxContext.pd3dDeviceContext->OMSetRenderTargets(
      1, &_dxContext.mainRenderTargetView, _dxContext.pDepthStencilView);

  // Set up the IA stage by setting the input topology and layout.
  UINT stride = sizeof(VertexPositionColor);
  UINT offset = 0;
  _dxContext.pd3dDeviceContext->IASetVertexBuffers(0, 1, &data.vertexBuffer,
                                                   &stride, &offset);

  _dxContext.pd3dDeviceContext->IASetIndexBuffer(data.indexBuffer,
                                                 DXGI_FORMAT_R16_UINT, 0);
  // context->IASetInputLayout(m_pInputLayout.Get());

  // Set up the vertex shader stage.
  _dxContext.pd3dDeviceContext->VSSetShader(data.shader.p_vertexShader, nullptr,
                                            0);

  // _dxContext.pd3dDeviceContext->VSSetConstantBuffers(0, 1,
  // m_pConstantBuffer.GetAddressOf());

  // Set up the pixel shader stage.
  _dxContext.pd3dDeviceContext->PSSetShader(data.shader.p_pixelShader, nullptr,
                                            0);

  // Calling Draw tells Direct3D to start sending commands to the graphics
  // device.
  _dxContext.pd3dDeviceContext->DrawIndexed(data.indexCount, 0, 0);

  _dxContext.pSwapChain->Present(1, 0);  // Present with vsync
}

int dengine::core::CleanDX11(DE &engine) {
  auto logger = getMultiSinkLogger();

  logger.info("Cleaning engine");

  CleanupDeviceD3D(_dxContext);
  SDL_DestroyWindow(engine.windowHandler);
  SDL_Quit();

  return 0;
}

std::function<void(dengine::DE &)> dengine::core::SetupRendererDX11(
    DE &engine) {
  RenderDataDX11 data;
  // TESTING

  // load and compile the two shaders
  // ID3D10Blob *VS, *PS;
  // D3DCompileFromFile(L"BasicHLSL11_VS.hlsl", 0, 0, "VShader", "vs_4_0", 0, 0,
  //                    &VS, 0);
  // D3DCompileFromFile(L"BasicHLSL11_PS.hlsl", 0, 0, "PShader", "ps_4_0", 0, 0,
  //                    &PS, 0);

  // encapsulate both shaders into shader objects
  // _dxContext.pd3dDevice->CreateVertexShader(VS->GetBufferPointer(),
  //                                           VS->GetBufferSize(), NULL,
  //                                           &data.shader.p_vertexShader);

  _dxContext.pd3dDevice->CreateVertexShader(vertexShaderSourceDX11,
                                            strlen(vertexShaderSourceDX11),
                                            NULL, &data.shader.p_vertexShader);
  // _dxContext.pd3dDevice->CreatePixelShader(PS->GetBufferPointer(),
  //                                          PS->GetBufferSize(), NULL,
  //                                          &data.shader.p_pixelShader);
  _dxContext.pd3dDevice->CreatePixelShader(pixelShaderSourceDX11,
                                           strlen(pixelShaderSourceDX11), NULL,
                                           &data.shader.p_pixelShader);

  // set the shader objects
  _dxContext.pd3dDeviceContext->VSSetShader(data.shader.p_vertexShader, 0, 0);
  _dxContext.pd3dDeviceContext->PSSetShader(data.shader.p_pixelShader, 0, 0);

  CreateCube(data);

  auto renderer = [=](dengine::DE &engine) {
    return dengine::core::RenderDX11(engine, data);
  };
  return renderer;
}

int dengine::core::CreateCube(dengine::core::RenderDataDX11 &data) {
  HRESULT hr = S_OK;

  // Create cube geometry.
  VertexPositionColor CubeVertices[] = {
      {
          DirectX::XMFLOAT3(-0.5f, -0.5f, -0.5f),
          DirectX::XMFLOAT3(0, 0, 0),
      },
      {
          DirectX::XMFLOAT3(-0.5f, -0.5f, 0.5f),
          DirectX::XMFLOAT3(0, 0, 1),
      },
      {
          DirectX::XMFLOAT3(-0.5f, 0.5f, -0.5f),
          DirectX::XMFLOAT3(0, 1, 0),
      },
      {
          DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f),
          DirectX::XMFLOAT3(0, 1, 1),
      },

      {
          DirectX::XMFLOAT3(0.5f, -0.5f, -0.5f),
          DirectX::XMFLOAT3(1, 0, 0),
      },
      {
          DirectX::XMFLOAT3(0.5f, -0.5f, 0.5f),
          DirectX::XMFLOAT3(1, 0, 1),
      },
      {
          DirectX::XMFLOAT3(0.5f, 0.5f, -0.5f),
          DirectX::XMFLOAT3(1, 1, 0),
      },
      {
          DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f),
          DirectX::XMFLOAT3(1, 1, 1),
      },
  };

  float vertices[] = {
      -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f,
  };

  // Create vertex buffer:

  CD3D11_BUFFER_DESC vDesc(sizeof(CubeVertices), D3D11_BIND_VERTEX_BUFFER);

  D3D11_SUBRESOURCE_DATA vData;
  ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
  vData.pSysMem = CubeVertices;
  vData.SysMemPitch = 0;
  vData.SysMemSlicePitch = 0;

  hr = _dxContext.pd3dDevice->CreateBuffer(&vDesc, &vData, &data.vertexBuffer);

  // Create index buffer:
  unsigned short CubeIndices[] = {
      0, 2, 1,  // -x
      1, 2, 3,

      4, 5, 6,  // +x
      5, 7, 6,

      0, 1, 5,  // -y
      0, 5, 4,

      2, 6, 7,  // +y
      2, 7, 3,

      0, 4, 6,  // -z
      0, 6, 2,

      1, 3, 7,  // +z
      1, 7, 5,
  };

  data.indexCount = ARRAYSIZE(CubeIndices);

  CD3D11_BUFFER_DESC iDesc(sizeof(CubeIndices), D3D11_BIND_INDEX_BUFFER);

  D3D11_SUBRESOURCE_DATA iData;
  ZeroMemory(&iData, sizeof(D3D11_SUBRESOURCE_DATA));
  iData.pSysMem = CubeIndices;
  iData.SysMemPitch = 0;
  iData.SysMemSlicePitch = 0;

  hr = _dxContext.pd3dDevice->CreateBuffer(&iDesc, &iData, &data.indexBuffer);

  return hr;
}