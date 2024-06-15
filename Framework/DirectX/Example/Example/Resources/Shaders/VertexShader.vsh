// ���
float4x4 g_stWorldMatrix;
float4x4 g_stViewMatrix;
float4x4 g_stProjectionMatrix;

/** VS Input */
struct STInput
{
	float3 m_stPosition : POSITION;
	float2 m_stUV : TEXCOORD0;
};

/** VS Output */
struct STOutput
{
	float4 m_stPosition : POSITION;
	float2 m_stUV : TEXCOORD0;
};

/** VS Main */
STOutput VSMain(STInput a_stInput)
{
	STOutput stOutput;
	float4 stWorldPosition = mul(float4(a_stInput.m_stPosition, 1.0f), g_stWorldMatrix);

	stOutput.m_stPosition = mul(stWorldPosition, g_stViewMatrix);
	stOutput.m_stPosition = mul(stOutput.m_stPosition, g_stProjectionMatrix);

	stOutput.m_stUV = a_stInput.m_stUV;
	return stOutput;
}
