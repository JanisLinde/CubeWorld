////////////////////////////////////////////////////////////////////////////////
// Filename: positionclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _POSITIONCLASS_H_
#define _POSITIONCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <math.h>


/////////////
// DEFINES //
/////////////
const char STATE_TURNING_LEFT = 0;
const char STATE_NOT_TURNING_LEFT = 1;
const char STATE_TURNING_RIGHT = 2;
const char STATE_NOT_TURNING_RIGHT = 3;
const char STATE_MOVING_FORWARD = 4;
const char STATE_NOT_MOVING_FORWARD = 5;
const char STATE_MOVING_BACKWARD = 6;
const char STATE_NOT_MOVING_BACKWARD = 7;


////////////////////////////////////////////////////////////////////////////////
// Class name: PositionClass
////////////////////////////////////////////////////////////////////////////////
class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass& other);
	~PositionClass();

	void SetPosition(float x, float y, float z);
	void SetRotation(float x, float y, float z);

	void GetPosition(float& x, float& y, float& z);
	void GetRotation(float& x, float& y, float& z);

	void SetFrameTime(float time);

	void MoveForward(bool keydown);
	void MoveBackward(bool keydown);
	void TurnLeft(bool keydown);
	void TurnRight(bool keydown);
	void LookUpward(bool keydown);
	void LookDownward(bool keydown);

	bool TurnLeftStateChange(char& newState);
	bool TurnRightStateChange(char& newState);
	bool MoveForwardStateChange(char& newState);
	bool MoveBackwardStateChange(char& newState);

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;

	float m_frameTime;
	float m_lookUpSpeed, m_lookDownSpeed;

	bool m_turnLeftStateChange, m_turningLeft;
	bool m_turnRightStateChange, m_turningRight;
	bool m_moveForwardStateChange, m_movingForward;
	bool m_moveBackwardStateChange, m_movingBackward;
};

#endif