struct PS_INPUT
{
	float4 position : POSITION;
	float3 color : COLOR;
	float3 color1 : COLOR1;
};

cbuffer constant : register(b0)
{
	row_major float4x4 m_world;
	row_major float4x4 m_view;
	row_major float4x4 m_projection;

	unsigned int m_time;
};

float4 main(PS_INPUT i) : SV_TARGET
{
	return float4(lerp(i.color, i.color1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f), 1.0f);
}