struct VS_INPUT
{
	float4 position : POSITION;
	float4 position1 : POSITION1;
	float3 color : COLOR;
	float3 color1 : COLOR1;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float3 color : COLOR;
	float3 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
	unsigned int m_time;
};

VS_OUTPUT main( VS_INPUT i )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	o.position = lerp(i.position, i.position1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f );
	o.color = i.color;
	o.color1 = i.color1;
	return o;
}