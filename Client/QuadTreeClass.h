////////////////////////////////////////////////////////////////////////////////
// Filename: quadtreeclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _QUADTREECLASS_H_
#define _QUADTREECLASS_H_


/////////////
// GLOBALS //
/////////////
const int MAX_TRIANGLES = 10000;


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "TerrainClass.h"
#include "FrustumClass.h"
#include "TerrainShaderClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: QuadTreeClass
////////////////////////////////////////////////////////////////////////////////
class QuadTreeClass
{
private:
	struct VertexType
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT4 color;
	};

	struct VectorType
	{
		float x, y, z;
	};

	struct NodeType
	{
        float positionX, positionZ, width;
		int triangleCount;
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		VectorType* vertexArray;
        NodeType* nodes[4];
	};

public:
	QuadTreeClass();
	QuadTreeClass(const QuadTreeClass&);
	~QuadTreeClass();

	bool Initialize(TerrainClass* Terrain, ID3D11Device* device);
	void Shutdown();
	void Render(FrustumClass* frustum, ID3D11DeviceContext* deviceContext, TerrainShaderClass* shader);

	int GetDrawCount();
	bool GetHeightAtPosition(float, float, float&);

private:
	void CalculateMeshDimensions(int vertexCount, float& centerX, float& centerZ, float& meshWidth);
	void CreateTreeNode(NodeType* node, float positionX, float positionZ, float width, ID3D11Device* device);
	int CountTriangles(float positionX, float positionZ, float width);
	bool IsTriangleContained(int index, float positionX, float positionZ, float width);
	void ReleaseNode(NodeType* node);
	void RenderNode(NodeType* node, FrustumClass* frustum, ID3D11DeviceContext* deviceContext, TerrainShaderClass* shader);

	void FindNode(NodeType*, float, float, float&);
	bool CheckHeightOfTriangle(float, float, float&, float[3], float[3], float[3]);

private:
	int m_triangleCount;
	VertexType* m_vertexList;
	NodeType* m_parentNode;
	int m_drawCount;
};

#endif