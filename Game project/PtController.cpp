#include "PtController.h"

int PtController::initialise()
{
	int l_error = SCE_OK;

	l_error = sceUserServiceInitialize(NULL);
	if (l_error != SCE_OK) 
	{ 
		printf("Unable to initialise user service (from ptController::initialise())\n");  
		return SCE_ERROR_ERROR_FLAG; 
	}

	//initialise pad library
	l_error = scePadInit();
	if (l_error != SCE_OK)
	{ 
		printf("Unable to initialise controller library\n"); 
		return SCE_ERROR_ERROR_FLAG; 
	}

	//get id for logged in user
	l_error = sceUserServiceGetInitialUser(&m_userId);
	if (l_error != SCE_OK) 
	{ 
		printf("Unable to get initial user id (ptController::initialise())\n");  
		return SCE_ERROR_ERROR_FLAG; 
	}

	m_handle = scePadOpen(m_userId, SCE_PAD_PORT_TYPE_STANDARD, 0, NULL);
	if (m_handle < 0) 
	{ 
		printf("Unable to get controller handle\n");  
		return SCE_ERROR_ERROR_FLAG; 
	}

	//get first lot of data
	l_error = scePadReadState(m_handle, &m_padState);
	if (l_error != SCE_OK) 
	{ 
		printf("Unable to read intial data for controller\n");  
		return SCE_ERROR_ERROR_FLAG; 
	}

	m_initialised = true;

	isCrossPressed = false;
	isSquarePressed = false;
	isCirclePressed = false;
	isTrianglePressed = false;
	isUpPressed = false;
	isDownPressed = false;
	isLeftPressed = false;
	isRightPressed = false;
	isL1Pressed = false;
	isL2Pressed = false;
	isL3Pressed = false;
	isR1Pressed = false;
	isR2Pressed = false;
	isR3Pressed = false;
	isOptionsPressed = false;

	crossToggle = false;
	squareToggle = false;
	circleToggle = false;
	triangleToggle = true;
	upToggle = false;
	downToggle = false;
	leftToggle = false;
	rightToggle = false;
	l1Toggle = false;
	l2Toggle = false;
	l3Toggle = false;
	r1Toggle = false;
	r2Toggle = false;
	r3Toggle = false;
	optionsToggle = false;

	rightStickOffset = 0;
	leftStickOffset = 0;

	leftAngleX = 0;
	rightAngleX = 0;
	leftAngleY = 0;
	rightAngleY = 0;

	return l_error;
}

int PtController::update()
{
	int l_error = SCE_ERROR_ERROR_FLAG;
	if (m_initialised)
	{
		l_error = scePadReadState(m_handle, &m_padState);
	}
	else
	{
		printf("Warning: attempting to read controller data for an un-initialised controller\n");
	}	
	return l_error;
}

bool PtController::crossPressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_CROSS;
}

bool PtController::trianglePressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_TRIANGLE;
}

bool PtController::circlePressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_CIRCLE;
}

bool PtController::squarePressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_SQUARE;
}

bool PtController::upPressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_UP;
}

bool PtController::leftPressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_LEFT;
}

bool PtController::downPressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_DOWN;
}

bool PtController::rightPressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_RIGHT;
}

bool PtController::l1Pressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_L1;
}

bool PtController::l2Pressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_L2;
}

bool PtController::l3Pressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_L3;
}

bool PtController::r1Pressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_R1;
}

bool PtController::r2Pressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_R2;
}

bool PtController::r3Pressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_R3;
}

bool PtController::optionsPressed()
{
	return m_padState.buttons & SCE_PAD_BUTTON_OPTIONS;
}

bool PtController::rightTrigger()
{
	if (!isRightPressed && rightPressed())
	{
		isRightPressed = true;
		return true;
	}
	else if (isRightPressed && rightPressed())
	{
		return false;
	}
	else
	{
		isRightPressed = false;
		return false;
	}
}

bool PtController::leftTrigger()
{
	if (!isLeftPressed && leftPressed())
	{
		isLeftPressed = true;
		return true;
	}
	else if (isLeftPressed && leftPressed())
	{
		return false;
	}
	else
	{
		isLeftPressed = false;
		return false;
	}
}

bool PtController::upTrigger()
{
	if (!isUpPressed && upPressed())
	{
		isUpPressed = true;
		return true;
	}
	else if (isUpPressed && upPressed())
	{
		return false;
	}
	else
	{
		isUpPressed = false;
		return false;
	}
}

bool PtController::downTrigger()
{
	if (!isDownPressed && downPressed())
	{
		isDownPressed = true;
		return true;
	}
	else if (isDownPressed && downPressed())
	{
		return false;
	}
	else
	{
		isDownPressed = false;
		return false;
	}
}

bool PtController::triangleTrigger()
{
	if (!isTrianglePressed && trianglePressed())
	{
		isTrianglePressed = true;
		return true;
	}
	else if (isTrianglePressed && trianglePressed())
	{
		return false;
	}
	else
	{
		isTrianglePressed = false;
		return false;
	}
}

bool PtController::squareTrigger()
{
	if (!isSquarePressed && squarePressed())
	{
		isSquarePressed = true;
		return true;
	}
	else if (isSquarePressed && squarePressed())
	{
		return false;
	}
	else
	{
		isSquarePressed = false;
		return false;
	}
}

bool PtController::crossTrigger()
{
	if (!isCrossPressed && crossPressed())
	{
		isCrossPressed = true;
		return true;
	}
	else if (isCrossPressed && crossPressed())
	{
		return false;
	}
	else
	{
		isCrossPressed = false;
		return false;
	}
}

bool PtController::circleTrigger()
{
	if (!isCirclePressed && circlePressed())
	{
		isCirclePressed = true;
		return true;
	}
	else if (isCirclePressed && circlePressed())
	{
		return false;
	}
	else
	{
		isCirclePressed = false;
		return false;
	}
}

bool PtController::l1Trigger()
{
	if (!isL1Pressed && l1Pressed())
	{
		isL1Pressed = true;
		return true;
	}
	else if (isL1Pressed && l1Pressed())
	{
		return false;
	}
	else
	{
		isL1Pressed = false;
		return false;
	}
}

bool PtController::l2Trigger()
{
	if (!isL2Pressed && l2Pressed())
	{
		isL2Pressed = true;
		return true;
	}
	else if (isL2Pressed && l2Pressed())
	{
		return false;
	}
	else
	{
		isL2Pressed = false;
		return false;
	}
}

bool PtController::l3Trigger()
{
	if (!isL3Pressed && l3Pressed())
	{
		isL3Pressed = true;
		return true;
	}
	else if (isL3Pressed && l3Pressed())
	{
		return false;
	}
	else
	{
		isL3Pressed = false;
		return false;
	}
}

bool PtController::r1Trigger()
{
	if (!isR1Pressed && r1Pressed())
	{
		isR1Pressed = true;
		return true;
	}
	else if (isR1Pressed && r1Pressed())
	{
		return false;
	}
	else
	{
		isR1Pressed = false;
		return false;
	}
}

bool PtController::r2Trigger()
{
	if (!isR2Pressed && r2Pressed())
	{
		isR2Pressed = true;
		return true;
	}
	else if (isR2Pressed && r2Pressed())
	{
		return false;
	}
	else
	{
		isR2Pressed = false;
		return false;
	}
}

bool PtController::r3Trigger()
{
	if (!isR3Pressed && r3Pressed())
	{
		isR3Pressed = true;
		return true;
	}
	else if (isR3Pressed && r3Pressed())
	{
		return false;
	}
	else
	{
		isR3Pressed = false;
		return false;
	}
}

bool PtController::optionsTrigger()
{
	if (!isOptionsPressed && optionsPressed())
	{
		isOptionsPressed = true;
		return true;
	}
	else if (isOptionsPressed && optionsPressed())
	{
		return false;
	}
	else
	{
		isOptionsPressed = false;
		return false;
	}
}

bool PtController::toggleTriangle()
{
	if (triangleToggle)
	{
		triangleToggle = false;
		return true;
	}
	else
	{
		triangleToggle = true;
		return false;
	}
	//return triangleToggle = !triangleToggle;
}

bool PtController::toggleSquare()
{
	return squareToggle = !squareToggle;
}

bool PtController::toggleCircle()
{
	return circleToggle = !circleToggle;
}

bool PtController::toggleCross() 
{
	return crossToggle = !crossToggle;
}

bool PtController::toggleUp()
{
	return upToggle = !upToggle;
}

bool PtController::toggleDown()
{
	return downToggle = !downToggle;
}

bool PtController::toggleLeft()
{
	return leftToggle = !leftToggle;
}

bool PtController::toggleRight()
{
	return rightToggle = !rightToggle;
}

bool PtController::toggleL1()
{
	return l1Toggle = !l1Toggle;
}

bool PtController::toggleL2()
{
	return l2Toggle = !l2Toggle;
}

bool PtController::toggleL3()
{
	return l3Toggle = !l3Toggle;
}

bool PtController::toggleR1()
{
	return r1Toggle = !r1Toggle;
}

bool PtController::toggleR2()
{
	return r2Toggle = !r2Toggle;
}

bool PtController::toggleR3()
{
	return r3Toggle = !r3Toggle;
}

bool PtController::toggleOptions()
{
	return optionsToggle = !optionsToggle;
}

bool PtController::getTriangleToggle()
{
	return triangleToggle;
}

bool PtController::getCircleToggle()
{
	return circleToggle;
}

bool PtController::getSquareToggle()
{
	return squareToggle;
}

bool PtController::getCrossToggle()
{
	return crossToggle;
}

float PtController::leftStickX()
{
	float value = -1;
	float stickOffset = m_padState.leftStick.x;
	stickOffset = stickOffset / 128;
	value = value + stickOffset;

	if (value < DEAD_BAND && value > 0 - DEAD_BAND)
	{
		value = 0;
	}

	return value;
}

float PtController::leftStickY()
{
	float value = -1;
	float stickOffset = m_padState.leftStick.y;
	stickOffset = stickOffset / 128;
	value = value + stickOffset;

	if (value < DEAD_BAND && value > 0 - DEAD_BAND)
	{
		value = 0;
	}

	return value;
}

float PtController::rightStickX()
{
	float value = -1;
	float stickOffset = m_padState.rightStick.x;
	stickOffset = stickOffset / 128;
	value = value + stickOffset;

	if (value < DEAD_BAND && value > 0 - DEAD_BAND)
	{
		value = 0;
	}

	return value;
}

float PtController::rightStickY()
{
	float value = -1;
	float stickOffset = m_padState.rightStick.y;
	stickOffset = stickOffset / 128;
	value = value + stickOffset;

	if (value < DEAD_BAND && value > 0 - DEAD_BAND)
	{
		value = 0;
	}

	return value;
}