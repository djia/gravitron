
struct Material {
	float4 amb; 
	float4 dif; 
	float4 spe;  
	float  sPow; 
};

struct Light {
	float4 amb; 
	float4 dif; 
	float4 spe;
	float3 vec;  
};

SamplerState sLinear
{
	Filter = MIN_MAG_MIP_LINEAR;
	AddressU = Wrap;
	AddressV = Wrap;
};

cbuffer cbPerSubset {
	Material g_Mat;
};

cbuffer cbPerObj {
	matrix g_WVP;
	matrix g_World;
	float g_TexTile;
};

cbuffer cbPerFrame {
	float3 g_CamPos;
	Light g_Light;
};

Texture2D g_Tex;
Texture2D g_TexHeightMap;


struct VS_INPUT
{
	float3 pos	: POSITION;	
	float3 nor	: NORMAL;	
	float2 tex	: TEXCOORD;	
};

struct PS_INPUT
{
	float4 wvpPos	: SV_POSITION;
	float3 wNor	: NORMAL;
	float3 wPos	: TEXCOORD0;
	float2 wTex	: TEXCOORD1;
};

PS_INPUT VS(VS_INPUT input)
{
	PS_INPUT output	= (PS_INPUT)0;
	output.wvpPos	= mul(float4(input.pos, 1.f), g_WVP);
	output.wNor	= mul(float4(input.nor, 0.f), g_World).xyz;
	output.wPos	= mul(float4(input.pos, 1.f), g_World).xyz;
	output.wTex	= g_TexTile*input.tex;

	return output;
}

float4 ShadePixel(float3 wNor, float3 wVVec, float2 wTex)
{
	float4 color = g_Tex.Sample(sLinear, wTex);
	clip(color.a - .01f);

	float3 nor = normalize(wNor).xyz;
	float3 vVec = normalize(wVVec).xyz;
	
	//ambient
	float4 amb = (g_Mat.amb*g_Light.amb);
	
	//diffuse
	float perDif = max(0, dot(-g_Light.vec, nor));
	float4 dif = perDif*(g_Mat.dif*g_Light.dif);
	
	//specular
	float3 rVec = reflect(-g_Light.vec, nor);
	float perSpe = pow(abs(max(0, dot(vVec, rVec))), g_Mat.sPow);
	float4 spe = perSpe*(g_Mat.spe*g_Light.spe);

	return color*(amb+dif) + spe;
}

float4 PS(PS_INPUT input) : SV_Target
{
	return ShadePixel(input.wNor, input.wPos - g_CamPos, input.wTex);
}

float4 PSClipAbove(PS_INPUT input) : SV_Target
{
	clip(input.wPos.y > 0 ? -1 : 1);
	//float h = g_TexHeightMap.Sample(sLinear, input.wTex);//lod parameters
	//clip(input.wPos.y > h ? -1 : 1);
	return ShadePixel(input.wNor, input.wPos - g_CamPos, input.wTex);
}

float4 PSRefraction(PS_INPUT input) : SV_Target
{


}

RasterizerState CullCCW{
	CullMode = Back;
};


RasterizerState CullCW {
	CullMode = Front;
};

technique10 Render
{
    pass P0
    {
        SetVertexShader(CompileShader(vs_4_0, VS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, PS()));
	SetRasterizerState(CullCCW);
    }
    pass P1
    {
        SetVertexShader(CompileShader(vs_4_0, VS()));
        SetGeometryShader(NULL);
        SetPixelShader(CompileShader(ps_4_0, PSClipAbove()));
	SetRasterizerState(CullCW);
    }
}
