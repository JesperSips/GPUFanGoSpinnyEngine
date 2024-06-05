//***************************************************************************************
// modified version of color.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************

cbuffer cbPerObject : register(b0)
{
    float4x4 gWorldViewProj;
};

struct VertexIn
{
    float3 PosL : POSITION;
    float3 Color : COLOR;
};

struct VertexOut
{
    float4 PosH : SV_POSITION;
    float4 Color : COLOR;
};

VertexOut main(VertexIn IN)
{
    VertexOut OUT;

    OUT.PosH = mul(float4(IN.PosL, 1.0f), gWorldViewProj);

    OUT.Color = float4(IN.Color, 1.0f);
    
    return OUT;
}
