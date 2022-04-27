#include "Particle.hlsli"
Texture2D tex : register(t0);
Texture2D tex2 : register(t1);
SamplerState samLinear : register(s0);

float4 main(PS_INPUT input) : SV_TARGET
{
	//‰æ‘œ•\Ž¦
	float4 t1 = tex.Sample(samLinear, input.Tex) ;
	float4 t2 = tex2.Sample(samLinear, input.Tex) ;
	float alpha = t2.r - sin(diffuse.w);
	t1 = lerp(float4(1, 1, 1, 1), t1, step(alpha, 0));
	t1 = lerp(float4(0, 0, 0, 0), t1, step(alpha, 0.1f));
	t1.rgb += diffuse.rgb;
	return t1;
}