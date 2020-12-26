struct VS_INPUT
{
	float4 position : POSITION;
	float3 color : COLOR;
};

struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float3 color : COLOR;
};

VS_OUTPUT main( VS_INPUT i )
{
	VS_OUTPUT o = (VS_OUTPUT)0;
	o.position = i.position;
	o.color = i.color;

	return o;
}