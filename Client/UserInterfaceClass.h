////////////////////////////////////////////////////////////////////////////////
// Filename: userinterfaceclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _USERINTERFACECLASS_H_
#define _USERINTERFACECLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "D3DClass.h"
#include "InputClass.h"
#include "TextureShaderClass.h"
#include "BitmapClass.h"
#include "TextClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: UserInterfaceClass
////////////////////////////////////////////////////////////////////////////////
class UserInterfaceClass
{
public:
	UserInterfaceClass();
	UserInterfaceClass(const UserInterfaceClass& other);
	~UserInterfaceClass();

	bool Initialize(D3DClass* Direct3D, HWND hwnd, int screenWidth, int screenHeight);
	void Shutdown();
	bool Frame(D3DClass* Direct3D, InputClass* Input, int fps, int cpu, int latency);
	bool Render(D3DClass* Direct3D, TextureShaderClass* TextureShader, DirectX::XMMATRIX worldMatrix, DirectX::XMMATRIX baseViewMatrix, DirectX::XMMATRIX orthoMatrix);

	bool UpdateDrawCount(ID3D11DeviceContext* deviceContext, int drawCount);
	void CheckForChatMessage(char* message, bool& newMessage);
	bool AddChatMessageFromServer(char* message, int id);

private:
	bool SetupTextStrings(D3DClass* Direct3D);
	bool SetVideoCardInfo(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* videoCardName, int videoCardMemory);
	bool SetFps(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	bool UpdateFps(ID3D11DeviceContext* deviceContext, int fps);
	bool SetCpu(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	bool UpdateCpu(ID3D11DeviceContext* deviceContext, int cpu);
	bool SetLatency(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	bool UpdateLatency(ID3D11DeviceContext* deviceContext, int latency);
	bool SetDrawCount(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	bool SetChatTextStrings(ID3D11Device* device, ID3D11DeviceContext* deviceContext);
	void KeyPressUpdate(int key, ID3D11DeviceContext* deviceContext);
	bool UpdateChatBar(ID3D11DeviceContext* deviceContext);
	bool AddChatMessage(ID3D11DeviceContext* deviceContext);
	void AddChatMessageForServer();

private:
	D3DClass* m_direct3d = 0;

	BitmapClass* m_ChatWindow;
	int m_chatWindowX, m_chatWindowY;
	TextClass* m_Text;
	int m_talkBarPosition;
	char m_chatBarString[50];
	char m_chatString1[50];
	char m_chatString2[50];
	char m_chatString3[50];
	char m_chatString4[50];
	char m_chatString5[50];
	char m_chatString6[50];
	char m_chatString7[50];
	bool m_newMessage;
	char m_serverMessage[50];
};

#endif