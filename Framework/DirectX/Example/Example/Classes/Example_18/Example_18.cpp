#include "Example_18.h"
#include "../Global/Function/GlobalFunction.h"
#include "../Global/Utility/Object/CCamera.h"
#include "../Global/Utility/Manager/CDeviceManager.h"
#include "../Global/Utility/Manager/CResourceManager.h"

Example_18::Example_18(HINSTANCE a_hInstance, int a_nOptions, const SIZE& a_rstWindowSize)
	:
	CDirect3DApplication(a_hInstance, a_nOptions, a_rstWindowSize)
{
	// Do Nothing
}

Example_18::~Example_18(void)
{
	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pIndexBuffer);

	SAFE_RELEASE(m_pVertexBuffer);
	SAFE_RELEASE(m_pPixelShader);

	SAFE_RELEASE(m_pVertexVariable);
	SAFE_RELEASE(m_pPixelVariable);
}

void Example_18::initApplication(void)
{
	CDirect3DApplication::initApplication();

	m_pVertexBuffer = this->createVertexBuffer();
	m_pIndexBuffer = this->createIndexBuffer();
	m_pVertexShader = this->createVertexShader(&m_pVertexVariable);
	m_pPixelShader = this->createPixelShader(&m_pPixelVariable);

	m_pTexture = GET_TEXTURE("Resources/Textures/HelloWorld.png");
}

void Example_18::update(void)
{
	CDirect3DApplication::update();
}

void Example_18::draw(void)
{
	CDirect3DApplication::draw();
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, false);

	// ����� �����Ѵ�
	// {
	D3DXMATRIXA16 stWorldMatrix;
	D3DXMatrixIdentity(&stWorldMatrix);

	auto stViewMatrix = GET_CAMERA()->getViewMatrix();
	auto stProjectionMatrix = GET_CAMERA()->getProjectionMatrix();

	m_pVertexVariable->SetMatrix(GET_DEVICE(), "g_stWorldMatrix", &stWorldMatrix);
	m_pVertexVariable->SetMatrix(GET_DEVICE(), "g_stViewMatrix", &stViewMatrix);
	m_pVertexVariable->SetMatrix(GET_DEVICE(), "g_stProjectionMatrix", &stProjectionMatrix);
	// }

	// �ؽ�ó�� �����Ѵ�
	// {
	D3DXCONSTANT_DESC stVariableDesc;
	m_pPixelVariable->GetConstantDesc("g_pSampler", &stVariableDesc, NULL);

	GET_DEVICE()->SetTexture(stVariableDesc.RegisterIndex, m_pTexture);

	GET_DEVICE()->SetSamplerState(stVariableDesc.RegisterIndex, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	GET_DEVICE()->SetSamplerState(stVariableDesc.RegisterIndex, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	GET_DEVICE()->SetSamplerState(stVariableDesc.RegisterIndex, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
	// }

	GET_DEVICE()->SetStreamSource(0, m_pVertexBuffer, 0, sizeof(STVertex));
	GET_DEVICE()->SetIndices(m_pIndexBuffer);
	GET_DEVICE()->SetFVF(STVertex::FVF);
	GET_DEVICE()->SetVertexShader(m_pVertexShader);
	GET_DEVICE()->SetPixelShader(m_pPixelShader);

	GET_DEVICE()->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);

	GET_DEVICE()->SetVertexShader(NULL);
	GET_DEVICE()->SetPixelShader(NULL);
	GET_DEVICE()->SetTexture(stVariableDesc.RegisterIndex, NULL);
	GET_DEVICE()->SetRenderState(D3DRS_LIGHTING, true);
}

LPDIRECT3DVERTEXBUFFER9 Example_18::createVertexBuffer(void)
{
	auto pVertexBuffer = CreateVertexBuffer(sizeof(STVertex) * 4,
		D3DUSAGE_WRITEONLY,
		STVertex::FVF,
		D3DPOOL_MANAGED);

	/** VS Input */�� �����Ѵ�
	// {
	STVertex* pstVertices = nullptr;

	if(SUCCEEDED(pVertexBuffer->Lock(0, 0, (void**)&pstVertices, 0)))
	{
		pstVertices[0].m_stPosition = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
		pstVertices[0].m_stUV = D3DXVECTOR2(0.0f, 0.0f);

		pstVertices[1].m_stPosition = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
		pstVertices[1].m_stUV = D3DXVECTOR2(1.0f, 0.0f);

		pstVertices[2].m_stPosition = D3DXVECTOR3(1.0f, -1.0f, 0.0f);
		pstVertices[2].m_stUV = D3DXVECTOR2(1.0f, 1.0f);

		pstVertices[3].m_stPosition = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
		pstVertices[3].m_stUV = D3DXVECTOR2(0.0f, 1.0f);

		pVertexBuffer->Unlock();
	}
	// }

	return pVertexBuffer;
}

LPDIRECT3DINDEXBUFFER9 Example_18::createIndexBuffer(void)
{
	auto pIndexBuffer = CreateIndexBuffer(sizeof(WORD) * 6,
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED);

	// �ε��� ������ �����Ѵ�
	// {
	WORD* pnIndices = nullptr;

	if(SUCCEEDED(pIndexBuffer->Lock(0, 0, (void**)&pnIndices, 0)))
	{
		pnIndices[0] = 0;	pnIndices[1] = 1;	pnIndices[2] = 2;
		pnIndices[3] = 0;	pnIndices[4] = 2;	pnIndices[5] = 3;

		pIndexBuffer->Unlock();
	}
	// }

	return pIndexBuffer;
}

LPDIRECT3DVERTEXSHADER9 Example_18::createVertexShader(LPD3DXCONSTANTTABLE* a_pOutVariableTable)
{
	LPD3DXBUFFER pShaderCode = nullptr;
	LPD3DXBUFFER pErrorBuffer = nullptr;
	LPD3DXCONSTANTTABLE pVariableTable = nullptr;

	// ���̴� �ڵ带 �������Ѵ�
	D3DXCompileShaderFromFile(_T("Resources/Shaders/VertexShader.vsh"),
		NULL,
		NULL,
		"VSMain",
		"vs_3_0",
		D3DXSHADER_DEBUG,
		&pShaderCode,
		&pErrorBuffer,
		&pVariableTable);

	if(pErrorBuffer != nullptr)
	{
		char* pszErrorMessage = (char*)(pErrorBuffer->GetBufferPointer());
		printf("Example_18.createVertexShader: %s\n", pszErrorMessage);

		SAFE_RELEASE(pErrorBuffer);
	}

	LPDIRECT3DVERTEXSHADER9 pVertexShader = nullptr;

	/** VS Main */�� �����Ѵ�
	GET_DEVICE()->CreateVertexShader((DWORD*)(pShaderCode->GetBufferPointer()),
		&pVertexShader);

	*a_pOutVariableTable = pVariableTable;
	return pVertexShader;
}

LPDIRECT3DPIXELSHADER9 Example_18::createPixelShader(LPD3DXCONSTANTTABLE* a_pOutVariableTable)
{
	LPD3DXBUFFER pShaderCode = nullptr;
	LPD3DXBUFFER pErrorBuffer = nullptr;
	LPD3DXCONSTANTTABLE pVariableTable = nullptr;

	// ���̴� �ڵ带 �������Ѵ�
	D3DXCompileShaderFromFile(_T("Resources/Shaders/PixelShader.psh"),
		NULL,
		NULL,
		"PSMain",
		"ps_3_0",
		D3DXSHADER_DEBUG,
		&pShaderCode,
		&pErrorBuffer,
		&pVariableTable);

	if(pErrorBuffer != nullptr)
	{
		char* pszErrorMessage = (char*)(pErrorBuffer->GetBufferPointer());
		printf("Example_18.createPixelShader: %s\n", pszErrorMessage);

		SAFE_RELEASE(pErrorBuffer);
	}

	LPDIRECT3DPIXELSHADER9 pPixelShader = nullptr;

	/** PS Main */�� �����Ѵ�
	GET_DEVICE()->CreatePixelShader((DWORD*)(pShaderCode->GetBufferPointer()),
		&pPixelShader);

	*a_pOutVariableTable = pVariableTable;
	return pPixelShader;
}
