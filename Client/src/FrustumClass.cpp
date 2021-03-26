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
	plane.x = m._14 + m._13;
	plane.y = m._24 + m._23;
	plane.z = m._34 + m._33;
	plane.w = m._44 + m._43;
	m_planes[0] = DirectX::XMPlaneNormalize(DirectX::XMLoadFloat4(&plane));

	// Calculate far plane of frustum.
	plane.x = m._14 - m._13;
	plane.y = m._24 - m._23;
	plane.z = m._34 - m._33;
	plane.w = m._44 - m._43;
	m_planes[1] = DirectX::XMPlaneNormalize(DirectX::XMLoadFloat4(&plane));

	// Calculate left plane of frustum.
	plane.x = m._14 + m._11;
	plane.y = m._24 + m._21;
	plane.z = m._34 + m._31;
	plane.w = m._44 + m._41;
	m_planes[2] = DirectX::XMPlaneNormalize(DirectX::XMLoadFloat4(&plane));

	// Calculate right plane of frustum.
	plane.x = m._14 - m._11;
	plane.y = m._24 - m._21;
	plane.z = m._34 - m._31;
	plane.w = m._44 - m._41;
	m_planes[3] = DirectX::XMPlaneNormalize(DirectX::XMLoadFloat4(&plane));

	// Calculate top plane of frustum.
	plane.x = m._14 - m._12;
	plane.y = m._24 - m._22;
	plane.z = m._34 - m._32;
	plane.w = m._44 - m._42;
	m_planes[4] = DirectX::XMPlaneNormalize(DirectX::XMLoadFloat4(&plane));

	// Calculate bottom plane of frustum.
	plane.x = m._14 + m._12;
	plane.y = m._24 + m._22;
	plane.z = m._34 + m._32;
	plane.w = m._44 + m._42;
	m_planes[5] = DirectX::XMPlaneNormalize(DirectX::XMLoadFloat4(&plane));

	return;
}

bool FrustumClass::CheckPoint(float x, float y, float z)
{
	/*
	int i;

	// Check if the point is inside all six planes of the view frustum.
	for(i=0; i<6; i++) 
	{
		DirectX::XMPlaneDotCoord(m_planes[i], DirectX::XMVECTOR(x, y, z)) < 0.0f)
		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(x, y, z)) < 0.0f)
		{
			return false;
		}
	}

	return true;
	*/

	return true;
}

bool FrustumClass::CheckCube(float xCenter, float yCenter, float zCenter, float radius)
{
	/*
	int i;


	// Check if any one point of the cube is in the view frustum.
	for(i=0; i<6; i++) 
	{
		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter - radius), (zCenter - radius))) >= 0.0f)
		{
			continue;
		}
		
		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter - radius), (zCenter - radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter + radius), (zCenter - radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter + radius), (zCenter - radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter - radius), (zCenter + radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter - radius), (zCenter + radius))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - radius), (yCenter + radius), (zCenter + radius))) >= 0.0f)
		{
			continue;
		}
		
		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + radius), (yCenter + radius), (zCenter + radius))) >= 0.0f)
		{
			continue;
		}

		return false;
	}

	return true;
	*/

	return true;
}

bool FrustumClass::CheckSphere(float xCenter, float yCenter, float zCenter, float radius)
{
	/*
	int i;


	// Check if the radius of the sphere is inside the view frustum.
	for(i=0; i<6; i++) 
	{
		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3(xCenter, yCenter, zCenter)) < -radius)
		{
			return false;
		}
	}

	*/
	return true;
}

bool FrustumClass::CheckRectangle(float xCenter, float yCenter, float zCenter, float xSize, float ySize, float zSize)
{
	/*
	int i;


	// Check if any of the 6 planes of the rectangle are inside the view frustum.
	for(i=0; i<6; i++)
	{
		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter - ySize), (zCenter - zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter - ySize), (zCenter - zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter + ySize), (zCenter - zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter - ySize), (zCenter + zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter + ySize), (zCenter - zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter - ySize), (zCenter + zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter - xSize), (yCenter + ySize), (zCenter + zSize))) >= 0.0f)
		{
			continue;
		}

		if(D3DXPlaneDotCoord(&m_planes[i], &D3DXVECTOR3((xCenter + xSize), (yCenter + ySize), (zCenter + zSize))) >= 0.0f)
		{
			continue;
		}

		return false;
	}

	*/
	return true;
}