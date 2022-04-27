#include "Particle.hlsli"
Texture2D tex : register(t0);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//‰æ‘œ•\Ž¦
	float4 t1 = tex.Sample(samLinear, input.Tex) ;

	float2 uv = input.Tex;
	float d = distance(float2(0.5f , 0.5f),uv);
	t1.rgb += diffuse.rgb;
	return step(diffuse.w,d)*t1;
}