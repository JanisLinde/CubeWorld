////////////////////////////////////////////////////////////////////////////////
// Filename: frustumclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "../include/FrustumClass.h"

FrustumClass::FrustumClass()
{
}

FrustumClass::FrustumClass(const FrustumClass& other)
{
}

FrustumClass::~FrustumClass()
{
}

void FrustumClass::ConstructFrustum(float screenDepth, DirectX::XMMATRIX projectionMatrix, DirectX::XMMATRIX viewMatrix)
{
	float zMinimum, r;
	DirectX::XMMATRIX matrix;

	DirectX::XMFLOAT4X4 proj, view, m;

	DirectX::XMStoreFloat4x4(&proj, projectionMatrix);
	DirectX::XMStoreFloat4x4(&view, viewMatrix);
	DirectX::XMStoreFloat4x4(&m, DirectX::XMMatrixIdentity());

	
	// Calculate the minimum Z distance in the frustum.
	zMinimum = -proj._43 / proj._33;
	r = screenDepth / (screenDepth - zMinimum);
	proj._33 = r;
	proj._43 = -r * zMinimum;

	projectionMatrix = DirectX::XMLoadFloat4x4(&proj);

	// Create the frustum matrix from the view matrix and updated projection matrix.
	DirectX::XMStoreFloat4x4(&m, DirectX::XMMatrixMultiply(viewMatrix, projectionMatrix));

	DirectX::XMFLOAT4 plane;

	// Calculate near plane of frustum.
	m_planes[0].x = m._14 + m._13;
	m_planes[0].y = m._24 + m._23;
	m_planes[0].z = m._34 + m._33;
	m_planes[0].w = m._44 + m._43;

	// Calculate far plane of frustum.
	m_planes[1].x = m._14 - m._13;
	m_planes[1].y = m._24 - m._23;
	m_planes[1].z = m._34 - m._33;
	m_planes[1].w = m._44 - m._43;

	// Calculate left plane of frustum.
	m_planes[2].x = m._14 + m._11;
	m_planes[2].y = m._24 + m._21;
	m_planes[2].z = m._34 + m._31;
	m_planes[2].w = m._44 + m._41;

	// Calculate right plane of frustum.
	m_planes[3].x = m._14 - m._11;
	m_planes[3].y = m._24 - m._21;
	m_planes[3].z = m._34 - m._31;
	m_planes[3].w = m._44 - m._41;
	
	// Calculate top plane of frustum.
	m_planes[4].x = m._14 - m._12;
	m_planes[4].y = m._24 - m._22;
	m_planes[4].z = m._34 - m._32;
	m_planes[4].w = m._44 - m._42;

	// Calculate bottom plane of frustum.
	m_planes[5].x = m._14 + m._12;
	m_planes[5].y = m._24 + m._22;
	m_planes[5].z = m._34 + m._32;
	m_planes[5].w = m._44 + m._42;

	return;
}

bool FrustumClass::CheckPoint(float x, float y, float z)
{
	// Chck if the point is inside all six planes of the view frustum
	for (int i = 0; i < 6; i++)
	{
		if (DistancePointToPlane(m_planes[i], x, y, z) < 0.0f)
		{
			return false;
		}
	}

	return true;
}

bool FrustumClass::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	for (int i = 0; i < 6; i++)
	{
		if (DistancePointToPlane(m_planes[i], xCenter - radius, yCenter - radius, zCenter - radius) >= 0.0f)
			continue;

		if (DistancePointToPlane(m_planes[i], xCenter + radius, yCenter - radius, zCenter - radius) >= 0.0f)
			continue;

		if (DistancePointToPlane(m_planes[i], xCenter - radius, yCenter + radius, zCenter - radius) >= 0.0f)
			continue;

		if (DistancePointToPlane(m_planes[i], xCenter + radius, yCenter + radius, zCenter - radius) >= 0.0f)
			continue;

		if (DistancePointToPlane(m_planes[i], xCenter - radius, yCenter - radius, zCenter + radius) >= 0.0f)
			continue;

		if (DistancePointToPlane(m_planes[i], xCenter + radius, yCenter - radius, zCenter + radius) >= 0.0f)
			continue;

		if (DistancePointToPlane(m_planes[i], xCenter - radius, yCenter + radius, zCenter + radius) >= 0.0f)
			continue;

		if (DistancePointToPlane(m_planes[i], xCenter + radius, yCenter + radius, zCenter + radius) >= 0.0f)
			continue;

		return false;
	}

	return true;
}

bool FrustumClass::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	for (int i = 0; i < 6; i++)
	{
		if (DistancePointToPlane(m_planes[i], xCenter, yCenter, zCenter) < -radius)
		{
			return false;
		}
	}

	return true;
}

bool FrustumClass::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	for (int i = 0; i < 6; i++)
	{
		if (DistancePointToPlane(m_planes[i], xCenter - xSize, yCenter - ySize, zCenter - zSize) >= 0.0f)
			continue;

		if (DistancePointToPlane(m_planes[i], xCenter + xSize, yCenter - ySize, zCenter - zSize) >= 0.0f)
			continue;

		if (DistancePointToPlane(m_planes[i], xCenter - xSize, yCenter + ySize, zCenter - zSize) >= 0.0f)
			continue;

		if (DistancePointToPlane(m_planes[i], xCenter + xSize, yCenter + ySize, zCenter - zSize) >= 0.0f)
			continue;

		if (DistancePointToPlane(m_planes[i], xCenter - xSize, yCenter - ySize, zCenter + zSize) >= 0.0f)
			continue;

		if (DistancePointToPlane(m_planes[i], xCenter + xSize, yCenter - ySize, zCenter + zSize) >= 0.0f)
			continue;

		if (DistancePointToPlane(m_planes[i], xCenter - xSize, yCenter + ySize, zCenter + zSize) >= 0.0f)
			continue;

		if (DistancePointToPlane(m_planes[i], xCenter + xSize, yCenter + ySize, zCenter + zSize) >= 0.0f)
			continue;

		return false;
	}
	
	return true;
}

float FrustumClass::DistancePointToPlane(DirectX::XMFLOAT4 plane, float px, float py, float pz)
{
	return plane.x * px + plane.y * py + plane.z * pz + plane.w;
}
