float4x4 g_stWorldMatrix;
float4x4 g_stViewMatrix;
float4x4 g_stProjectionMatrix;

texture g_pDiffuseTexture;
texture g_pNormalTexture;

float g_fParallax;
float4 g_stViewPosition;
float4 g_stLightDirection;

/** VS Input */
struct STInput
{
	float3 m_stPosition: POSITION0;
	float3 m_stNormal: NORMAL0;
	float3 m_stTangent: TANGENT0;
	float3 m_stBinormal: BINORMAL0;
	float2 m_stUV: TEXCOORD0;
};

/** VS Output */
struct STOutput
{
	float4 m_stPosition: POSITION0;
	float3 m_stNormal: TEXCOORD0;
	float3 m_stTangent: TEXCOORD1;
	float3 m_stBinormal: TEXCOORD2;
	float2 m_stUV: TEXCOORD3;
	float3 m_stViewDirection: TEXCOORD4;
	float3 m_stLightDirection: TEXCOORD5;
};

/** VS Main */
STOutput VSMain(STInput a_stInput)
{
	STOutput stOutput = (STOutput)0;
	float4 stWorldPosition = mul(float4(a_stInput.m_stPosition, 1.0f), g_stWorldMatrix);

	stOutput.m_stPosition = mul(stWorldPosition, g_stViewMatrix);
	stOutput.m_stPosition = mul(stOutput.m_stPosition, g_stProjectionMatrix);

	float3 stNormal = mul(a_stInput.m_stNormal, (float3x3)g_stWorldMatrix);
	stOutput.m_stNormal = normalize(stNormal);

	float3 stTangent = mul(a_stInput.m_stTangent, (float3x3)g_stWorldMatrix);
	stOutput.m_stTangent = normalize(stTangent);

	float3 stBinormal = mul(a_stInput.m_stBinormal, (float3x3)g_stWorldMatrix);
	stOutput.m_stBinormal = normalize(stBinormal);

	float3 stViewDirection = stWorldPosition.xyz - g_stViewPosition.xyz;
	stOutput.m_stViewDirection = normalize(stViewDirection);

	float3 stLightDirection = g_stLightDirection.xyz;
	stOutput.m_stLightDirection = normalize(stLightDirection);

	stOutput.m_stUV = a_stInput.m_stUV;
	return stOutput;
}

sampler2D g_pDiffuseSampler = sampler_state
{
	Texture = g_pDiffuseTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

sampler2D g_pNormalSampler = sampler_state
{
	Texture = g_pNormalTexture;

	MinFilter = LINEAR;
	MagFilter = LINEAR;
	MipFilter = LINEAR;
};

/** PS Main */
float4 PSMain(STOutput a_stInput): COLOR0
{
	float3 stNormal = normalize(a_stInput.m_stNormal);
	float3 stTangent = normalize(a_stInput.m_stTangent);
	float3 stBinormal = normalize(a_stInput.m_stBinormal);

	float3 stViewDirection = normalize(a_stInput.m_stViewDirection);
	float3 stLightDirection = normalize(a_stInput.m_stLightDirection);

	float3x3 stInverseMatrix = float3x3(stTangent,
		stBinormal,
		stNormal);

	stInverseMatrix = transpose(stInverseMatrix);
	
	float fHeight = tex2D(g_pNormalSampler, a_stInput.m_stUV).w;
	float2 stOffsetUV = a_stInput.m_stUV + ((fHeight * g_fParallax) * -stViewDirection.xy);

	float3 stTangentNormal = tex2D(g_pNormalSampler, stOffsetUV).xyz;
	stTangentNormal = normalize((stTangentNormal * 2.0f) - 1.0f);
	stTangentNormal = mul(stTangentNormal, stInverseMatrix);
	
	float fDiffuse = saturate(dot(-stLightDirection, stTangentNormal));
	
	float fSpecular = saturate(dot(reflect(stLightDirection, stTangentNormal), -stViewDirection));
	fSpecular = pow(fSpecular, 20.0f);

	float4 stDiffuseColor = tex2D(g_pDiffuseSampler, stOffsetUV);

	float4 stFinalColor = stDiffuseColor;
	stFinalColor.rgb = stFinalColor.rgb * fDiffuse;
	stFinalColor.rgb = stFinalColor.rgb + (stDiffuseColor.rgb * fSpecular);

	return stFinalColor;
}

technique MyTechnique
{
	pass P0
	{
		VertexShader = compile vs_3_0 VSMain();
		PixelShader = compile ps_3_0 PSMain();
	}
}
