#pragma once

#include "../Define/KGlobalDefine.h"

//! Float -> DWORD ������ ��ȯ�Ѵ�
DWORD FloatToDWORD(float a_fValue);

//! ��ü ��� ���� -> ��� �������� ��ȯ�Ѵ�
STBoundingBox ObjectBoxToBox(const STObjectBoundingBox& a_rstObjectBoundingBox);

//! ���� ���� ������ �����Ѵ�
int ClampIntValue(int a_nValue, int a_nMin, int a_nMax);

//! �Ǽ� ���� ������ �����Ѵ�
float ClampFloatValue(float a_fValue, float a_fMin, float a_fMax);

//! ���� ���� ���� �����Ѵ�
int CreateIntRandomValue(int a_nMin, int a_nMax);

//! �Ǽ� ���� ���� �����Ѵ�
float CreateFloatRandomValue(float a_fMin, float a_fMax);

//! ������ �����Ѵ�
STRay CreateRay(const POINT& a_rstPoint);

//! ��� ������ �����Ѵ�
STBoundingBox CreateBoundingBox(LPD3DXMESH a_pMesh);

//! ��� ���� �����Ѵ�
STBoundingSphere CreateBoundingSphere(LPD3DXMESH a_pMesh);

//! ���� ���۸� �����Ѵ�
LPDIRECT3DVERTEXBUFFER9 CreateVertexBuffer(int a_nSize, DWORD a_nUsage, DWORD a_nFVF, D3DPOOL a_ePool);

//! �ε��� ���۸� �����Ѵ�
LPDIRECT3DINDEXBUFFER9 CreateIndexBuffer(int a_nSize, DWORD a_nUsage, D3DFORMAT a_eFormat, D3DPOOL a_ePool);

//! ��� ������ ���� ���θ� �˻��Ѵ�
bool IsIntersectBox(const STBoundingBox& a_rstLhs, const STBoundingBox& a_rstRhs);

//! ��ü ��� ������ ���� ���θ� �˻��Ѵ�
bool IsIntersectObjectBox(const STObjectBoundingBox& a_rstLhs, const STObjectBoundingBox& a_rstRhs);

//! ��� ���� ���� ���θ� �˻��Ѵ�
bool IsIntersectSphere(const STBoundingSphere& a_rstLhs, const STBoundingSphere& a_rstRhs);

//! ������ ��� ������ ���� ���θ� �˻��Ѵ�
bool IsIntersectRayBox(const STBoundingBox& a_rstBoundingBox, const STRay& a_rstRay);

//! ������ ���� ���� ���θ� �˻��Ѵ�
bool IsIntersectRaySphere(const STBoundingSphere& a_rstBoundingSphere, const STRay& a_rstRay);

//! �簢���� ���� ���� ���� ���θ� �˻��Ѵ�
bool IsContainPoint(const RECT& a_rstRect, const POINT& a_rstPoint);

//! ����Ʈ ������ �����Ѵ�
void RunEffectLoop(LPD3DXEFFECT a_pEffect, const std::string& a_rTechniqueName, const std::function<void(int)>& a_rCallback);

//! ��ü�� �����Ѵ�
template <typename T, typename... ARGS>
T* CreateObject(ARGS&&... args);

//! �ν��Ͻ��� �����Ѵ�
template <typename T, typename... ARGS>
T* CreateInstance(ARGS&&... args);

#include "GlobalFunction.inl"
