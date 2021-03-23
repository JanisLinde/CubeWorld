////////////////////////////////////////////////////////////////////////////////
// Filename: textclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _TEXTCLASS_H_
#define _TEXTCLASS_H_


/////////////
// GLOBALS //
/////////////
const int NUM_SENTENCES = 20;

#include <DirectXMath.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "FontClass.h"
#include "FontShaderClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: TextClass
////////////////////////////////////////////////////////////////////////////////
class TextClass
{
private:
	struct SentenceType
	{
		ID3D11Buffer *vertexBuffer, *indexBuffer;
		int vertexCount, indexCount, maxLength;
		float red, green, blue;
		bool active;
	};

	struct VertexType
	{
		DirectX::XMFLOAT3 position;
		DirectX::XMFLOAT2 texture;
	};

public:
	TextClass();
	TextClass(const TextClass& otrher);
	~TextClass();

	bool Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, HWND hwnd, int screenWidth, int screenHeight);
	void Shutdown();
	void Render(ID3D11DeviceContext* deviceContext, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX orthoMatrix);

	bool CreateSentence(ID3D11Device* device, ID3D11DeviceContext* deviceContext, int id, int maxLength, char* sentence, int posX, int posY, float red, float green, float blue);
	bool UpdateSentence(ID3D11DeviceContext* deviceContext, int sentenceId, char* text, int positionX, int positionY, float red, float green, float blue);

private:
	bool InitializeSentence(int sentenceId, int maxLength, ID3D11Device* device);
	void ReleaseSentence(int sentenceId);
	void RenderSentence(ID3D11DeviceContext* deviceContext, int sentenceId, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX viewMatrix, DirectX::XMMATRIX orthoMatrix);

private:
	FontClass* m_Font;
	FontShaderClass* m_FontShader;
	int m_screenWidth, m_screenHeight;
	SentenceType* m_sentenceArray;
};

#endif