#ifndef __PT_CONTROLLER__
#define __PT_CONTROLLER__

#include <pad.h>
#include <scebase.h>
#include <user_service.h>

class PtController
{
private:
	const float DEAD_BAND = 0.3;
	SceUserServiceUserId  m_userId; //id of the user the controller is assigned to
	int32_t m_handle;				//the controller handle, used for all subsequent data collection
	ScePadData m_padState;			//holds the state of the controller when polled 
	bool m_initialised;		//flag to show when initialised

	bool isCrossPressed;
	bool isSquarePressed;
	bool isCirclePressed;
	bool isTrianglePressed;
	bool isUpPressed;
	bool isDownPressed;
	bool isLeftPressed; 
	bool isRightPressed;
	bool isL1Pressed;
	bool isL2Pressed;
	bool isL3Pressed;
	bool isR1Pressed;
	bool isR2Pressed;
	bool isR3Pressed;
	bool isOptionsPressed;

	bool crossToggle;
	bool squareToggle;
	bool circleToggle;
	bool triangleToggle;
	bool upToggle;
	bool downToggle;
	bool leftToggle;
	bool rightToggle;
	bool l1Toggle;
	bool l2Toggle;
	bool l3Toggle;
	bool r1Toggle;
	bool r2Toggle;
	bool r3Toggle;
	bool optionsToggle;

	uint8_t rightStickOffset;
	uint8_t leftStickOffset;

	float leftAngleX;
	float leftAngleY;
	float rightAngleX;
	float rightAngleY;

public: 
	int initialise();
	int update();
	bool crossPressed();
	bool trianglePressed();
	bool circlePressed();
	bool squarePressed();
	bool upPressed();
	bool leftPressed();
	bool downPressed();
	bool rightPressed();
	bool l1Pressed();
	bool l2Pressed();
	bool l3Pressed();
	bool r1Pressed();
	bool r2Pressed();
	bool r3Pressed();
	bool optionsPressed();

	bool rightTrigger();
	bool leftTrigger();
	bool upTrigger();
	bool downTrigger();
	bool triangleTrigger();
	bool squareTrigger();
	bool circleTrigger();
	bool crossTrigger();
	bool l1Trigger();
	bool l2Trigger();
	bool l3Trigger();
	bool r1Trigger();
	bool r2Trigger();
	bool r3Trigger();
	bool optionsTrigger();

	bool toggleRight();
	bool toggleLeft();
	bool toggleUp();
	bool toggleDown();
	bool toggleTriangle();
	bool toggleSquare();
	bool toggleCircle();
	bool toggleCross();
	bool toggleL1();
	bool toggleL2();
	bool toggleL3();
	bool toggleR1();
	bool toggleR2();
	bool toggleR3();
	bool toggleOptions();

	bool getTriangleToggle();
	bool getCircleToggle();
	bool getSquareToggle();
	bool getCrossToggle();

	float leftStickX();
	float leftStickY();
	float rightStickX();
	float rightStickY();
};

//typedef struct ScePadData {
//	uint32_t buttons;
// ScePadAnalogStick leftStick;
//	ScePadAnalogStick rightStick;
//	ScePadAnalogButtons analogButtons;
//	SceFQuaternion orientation;
//	SceFVector3 acceleration;
//	SceFVector3 angularVelocity;
//	ScePadTouchData touchData;
//	bool connected;
//	uint64_t timestamp;
//	ScePadExtensionUnitData extensionUnitData;
//	uint8_t connectedCount;
//	uint8_t reserve[2];
//	uint8_t deviceUniqueDataLen;
//	uint8_t deviceUniqueData[SCE_PAD_MAX_DEVICE_UNIQUE_DATA_SIZE];
//} ScePadData;

//typedef enum ScePadButtonDataOffset {
//	SCE_PAD_BUTTON_L3 = 0x00000002,
//	SCE_PAD_BUTTON_R3 = 0x00000004,
//	SCE_PAD_BUTTON_OPTIONS = 0x00000008,
//	SCE_PAD_BUTTON_UP = 0x00000010,
//	SCE_PAD_BUTTON_RIGHT = 0x00000020,
//	SCE_PAD_BUTTON_DOWN = 0x00000040,
//	SCE_PAD_BUTTON_LEFT = 0x00000080,
//	SCE_PAD_BUTTON_L2 = 0x00000100,
//	SCE_PAD_BUTTON_R2 = 0x00000200,
//	SCE_PAD_BUTTON_L1 = 0x00000400,
//	SCE_PAD_BUTTON_R1 = 0x00000800,
//	SCE_PAD_BUTTON_TRIANGLE = 0x00001000,
//	SCE_PAD_BUTTON_CIRCLE = 0x00002000,
//	SCE_PAD_BUTTON_CROSS = 0x00004000,
//	SCE_PAD_BUTTON_SQUARE = 0x00008000,
//	SCE_PAD_BUTTON_TOUCH_PAD = 0x00100000,
//	SCE_PAD_BUTTON_INTERCEPTED = 0x80000000,
//} ScePadButtonDataOffset;

#endif