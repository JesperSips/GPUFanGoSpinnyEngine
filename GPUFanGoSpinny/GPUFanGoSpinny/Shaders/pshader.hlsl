//***************************************************************************************
// modified version of color.hlsl by Frank Luna (C) 2015 All Rights Reserved.
//
// Transforms and colors geometry.
//***************************************************************************************


struct PixelIn
{
    float3 PosL : POSITION;
    float4 Color : COLOR;
};


float4 main(PixelIn IN) : SV_Target
{
    return IN.Color;
}