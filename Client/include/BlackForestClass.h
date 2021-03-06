////////////////////////////////////////////////////////////////////////////////
// Filename: blackforestclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _BLACKFORESTCLASS_H_
#define _BLACKFORESTCLASS_H_


///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "D3DClass.h"
#include "InputClass.h"
#include "CameraClass.h"
#include "PositionClass.h"
#include "LightClass.h"
#include "SkydomeClass.h"
#include "SkydomeShaderClass.h"
#include "TerrainClass.h"
#include "TerrainShaderClass.h"
#include "TextureShaderClass.h"
#include "ModelClass.h"
#include "EntityListClass.h"
#include "FrustumClass.h"
#include "QuadTreeClass.h"
#include "UserInterfaceClass.h"


////////////////////////////////////////////////////////////////////////////////
// Class name: BlackForestClass
////////////////////////////////////////////////////////////////////////////////
class BlackForestClass
{
public:
	BlackForestClass();
	BlackForestClass(const BlackForestClass&);
	~BlackForestClass();

	bool Initialize(D3DClass*, HWND, int, int, float, float);
	void Shutdown();
	bool Frame(D3DClass*, InputClass*, float, UserInterfaceClass*);

	void AddEntity(unsigned short, char, float, float, float, float, float, float);
	void RemoveEntity(unsigned short);
	bool GetStateChange(char&);
	void UpdateEntityState(unsigned short, char);
	bool PositionUpdate(float&, float&, float&, float&, float&, float&);
	void UpdateEntityPosition(unsigned short, float, float, float, float, float, float);
	void UpdateEntityRotate(unsigned short, bool);

private:
	void HandleMovementInput(InputClass*, float);
	bool Render(D3DClass*, UserInterfaceClass*);

private:
	CameraClass* m_Camera;
	PositionClass* m_Position;
	LightClass* m_Light;
	SkyDomeClass* m_SkyDome;
	SkyDomeShaderClass* m_SkyDomeShader;
	TerrainClass* m_Terrain;
	TerrainShaderClass* m_TerrainShader;
	TextureShaderClass* m_TextureShader;
	ModelClass *m_CubeModel1, *m_CubeModel2;
	EntityListClass* m_EntityList;
	FrustumClass* m_Frustum;
	float m_screenDepth;
	QuadTreeClass* m_QuadTree;
	
	bool m_stateChange;
	char m_newState;
	unsigned long m_updateTime;
	bool m_positionUpdateReady;
};

#endif