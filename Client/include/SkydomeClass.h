////////////////////////////////////////////////////////////////////////////////
// Filename: skydomeclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _SKYDOMECLASS_H_
#define _SKYDOMECLASS_H_


//////////////
// INCLUDES //
//////////////
#include <d3d11.h>
#include <DirectXMath.h>
#include <fstream>
using namespace std;


////////////////////////////////////////////////////////////////////////////////
// Class name: SkyDomeClass
////////////////////////////////////////////////////////////////////////////////
class SkyDomeClass
{
private:
	struct ModelType
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

	struct VertexType
	{
		DirectX::XMFLOAT3 position;
	};

public:
	SkyDomeClass();
	SkyDomeClass(const SkyDomeClass& other);
	~SkyDomeClass();

	bool Initialize(ID3D11Device* device);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext);

	int GetIndexCount();
	DirectX::XMFLOAT4 GetApexColor();
	DirectX::XMFLOAT4 GetCenterColor();

private:
	bool LoadSkyDomeModel(const char*);
	void ReleaseSkyDomeModel();

	bool InitializeBuffers(ID3D11Device* device);
	void ReleaseBuffers();
	void RenderBuffers(ID3D11DeviceContext* deviceContext);

private:
	ModelType* m_model;
	int m_vertexCount, m_indexCount;
	ID3D11Buffer *m_vertexBuffer, *m_indexBuffer;
	DirectX::XMFLOAT4 m_apexColor, m_centerColor;
};

#endif