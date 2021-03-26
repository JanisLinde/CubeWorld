////////////////////////////////////////////////////////////////////////////////
// Filename: terrainclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TERRAINCLASS_H_
#define _TERRAINCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>
#include <stdio.h>


////////////////////////////////////////////////////////////////////////////////
// Class name: TerrainClass
////////////////////////////////////////////////////////////////////////////////
class TerrainClass
{
private:
	struct HeightMapType 
	{ 
		float x, y, z;
		float nx, ny, nz;
		float r, g, b;
	};

	struct VectorType 
	{ 
		float x, y, z;
	};

	struct VertexType
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT4 color;
	};
	
public:
	TerrainClass();
	TerrainClass(const TerrainClass& other);
	~TerrainClass();

	bool Initialize(const char* heightMapFilename, const char* colorMapFilename, float maxHeight);
	void Shutdown();

	int GetVertexCount();
	void CopyVertexArray(void* vertexList);

private:
	bool LoadHeightMap(const char* filename);
	bool LoadColorMap(const char* filename);
	void ReduceHeightMap(float value);
	bool CalculateNormals();
	bool InitializeVertexArray();

	void ReleaseHeightMap();
	void ReleaseVertexArray();

private:
	int m_terrainWidth, m_terrainHeight, m_vertexCount;
	HeightMapType* m_heightMap;
	VertexType* m_vertexArray;
};

#endif