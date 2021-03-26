///////////////////////////////////////////////////////////////////////////////
// Filename: networkclass.h
///////////////////////////////////////////////////////////////////////////////
#ifndef _NETWORKCLASS_H_
#define _NETWORKCLASS_H_


/////////////
// GLOBALS //
/////////////
const int MAX_MESSAGE_SIZE = 512;
const int MAX_QUEUE_SIZE = 200;

const int DEFAULT_PORT = 7000;

/////////////
// LINKING //
/////////////
#pragma comment(lib, "ws2_32.lib")


//////////////
// INCLUDES //
//////////////
#include <winsock2.h>


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "NetworkMessages.h"
#include "UserInterfaceClass.h"
#include "BlackForestClass.h"


///////////////////////////////////////////////////////////////////////////////
// Class name: NetworkClass
///////////////////////////////////////////////////////////////////////////////
class NetworkClass
{
private:
	struct QueueType
	{
		bool active;
		struct sockaddr_in address;
		int size;
		char message[MAX_MESSAGE_SIZE];
	};

public:
	NetworkClass();
	NetworkClass(const NetworkClass& other);
	~NetworkClass();

	bool Initialize();
	bool Initialize(char* ipAddress, unsigned short serverPort);
	void Shutdown();
	void Frame();

	void SetZonePointer(BlackForestClass* ptr);
	void SetUIPointer(UserInterfaceClass* ptr);
	int GetLatency();
	void SetThreadActive();
	void SetThreadInactive();
	bool Online();
	SOCKET GetClientSocket();

	void ReadNetworkMessage(char* recvBuffer, int bytesRead, struct sockaddr_in serverAddress);

	bool SendStateChange(char state);
	bool SendPositionUpdate(float positionX, float positionY, float positionZ, float rotationX, float rotationY, float rotationZ);

private:
	bool InitializeWinSock();
	void ShutdownWinsock();

	bool ConnectToServer(char* ipAddress, unsigned short portNumber);
	void HandlePingMessage();
	void ProcessLatency();
	void SendPing();
	void SendDisconnectMessage();

	void AddMessageToQueue(char* message, int messageSize, struct sockaddr_in serverAddress);
	void ProcessMessageQueue();
	void HandleChatMessage(int queuePosition);
	void HandleEntityInfoMessage(int queuePosition);
	void HandleNewUserLoginMessage(int queuePosition);
	void HandleUserDisconnectMessage(int queuePosition);
	void HandleStateChangeMessage(int queuePosition);
	void HandlePositionMessage(int queuePosition);
	void HandleAIRotateMessage(int queuePosition);

	bool SendChatMessage(char* inputMsg);
	bool RequestEntityList();

private:
	BlackForestClass* m_ZonePtr;
	UserInterfaceClass* m_UserInterfacePtr;
	int m_latency;
	SOCKET m_clientSocket;
	int m_addressLength;
	struct sockaddr_in m_serverAddress;
	unsigned short m_idNumber, m_sessionId;
	bool m_online, m_threadActive;
	unsigned long m_pingTime;
	QueueType* m_networkMessageQueue;
	int m_nextQueueLocation, m_nextMessageForProcessing;
	char m_chatMessage[64];
	char m_uiMessage[50];
};


/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
void NetworkReadFunction(void* ptr);


#endif