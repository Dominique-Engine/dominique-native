#pragma once

const char *vertexShaderSourceDX11 = R"(

  cbuffer ConstantBufferData
  {
    float4x4 matrixWorld;
    float4x4 matrixView;
    float4x4 matrixProjection;
  }
  
  StructuredBuffer<float3> particles;
  
  struct v2g
  {
    float4 position : SV_POSITION;
    float4 particleId : TEXCOORD0;
  };
  
  v2g main( uint vertexId : SV_VertexID )
  {
    v2g o;
  
    float4 objPos = float4(particles[vertexId].xyz, 1.0);
    float4 worldPos = mul(matrixWorld, objPos);
    float4x4 matVP = mul(matrixProjection, matrixView);
  
    o.position = mul(matVP, worldPos);
    o.particleId = float4(vertexId, vertexId, vertexId, vertexId);
  
    return o;
  }

)";

const char *pixelShaderSourceDX11 = R"(

  struct g2f
  {
    float4 position : SV_POSITION;
    float4 color : TEXCOORD0;
    float2 uv : TEXCOORD1;
  };
  
  float4 main(g2f i) : SV_TARGET
  {
    return i.color;
}

)";