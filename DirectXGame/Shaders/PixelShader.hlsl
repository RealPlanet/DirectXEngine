struct PS_INPUT
{
	float4 position : POSITION;
	float3 color : COLOR;
};

float4 main(PS_INPUT i) : SV_TARGET
{
	return float4(i.color, 1.0f);
}