#include "device/RotatorDevice.h"

RotatorDevice::RotatorDevice()
{
    //pinMode(LIGHT_PIN_1, OUTPUT);
    //pinMode(LIGHT_PIN_2, OUTPUT);
}

/*
Indicates whether the Rotator supports the Reverse method.
True if the Rotator supports the Reverse method.
*/
bool RotatorDevice::getCanReverse()
{
    return _canReverse;
}

/*
Indicates whether the rotator is currently moving.
True if the rotator is currently moving to a new position. False if the focuser is stationary.
*/
bool RotatorDevice::getIsMoving()
{
    return _isMoving;
}

/*
Returns the rotator's mechanical current position.
Returns the raw mechanical position of the rotator in degrees.
*/
double RotatorDevice::getMechanicalPosition()
{
    // In Degrees
    return _mechanicalPosition;
}

/*
Returns the rotator's current position.
Current instantaneous Rotator position, in degrees.
*/
double RotatorDevice::getPosition()
{
    // In Degrees
    return _position;
}

/**
 * @brief Returns the rotator’s Reverse state.
 * 
 * @return true 
 * @return false 
 */
bool RotatorDevice::getReverseState()
{
    return _reverseState;
}

/*
Returns the minimum StepSize
The minimum StepSize, in degrees.
*/
double RotatorDevice::getStepSize()
{
    return _stepSize;
}

/*
Returns the destination position angle.
The destination position angle for Move() and MoveAbsolute().
*/
double RotatorDevice::getTargetPosition()
{
    return _targetPosition;
}

// PUT
/*
Sets the rotator’s Reverse state.

*/
void RotatorDevice::putReverseState(bool reverse)
{
    _reverseState = reverse;
}

/*
Immediatley stops rotator motion.
Immediately stop any Rotator motion due to a previous Move or MoveAbsolute method call.
*/
void RotatorDevice::putHalt()
{
    _halt = true;
}

/*
Moves the rotator to a new relative position.
Causes the rotator to move Position degrees relative to the current Position value.
*/
void RotatorDevice::putMove(double position)
{
    _targetPosition = position;
}

/*
Moves the rotator to a new absolute position.
Causes the rotator to move the absolute position of Position degrees.
*/
void RotatorDevice::putMoveAbsolute(double position)
{
    _targetPosition = position;
}

/*
Moves the rotator to a new raw mechanical position.
Causes the rotator to move the mechanical position of Position degrees.
*/
void RotatorDevice::putMoveMechanical(double position)
{
    _targetMechanicalPosition = position;
}

/*
Syncs the rotator to the specified position angle without moving it.
Causes the rotator to sync to the position of Position degrees.
*/
void RotatorDevice::putSync(double position)
{
    _targetMechanicalPosition = position;
}


/*
int RotatorDevice::getBrightness()
{
    return _brightness;
}
void RotatorDevice::setCalibratonOn(int brightness)
{
    analogWrite(LIGHT_PIN_1, brightness);
    analogWrite(LIGHT_PIN_2, brightness);
    _brightness = brightness;
    calibrationState = 3;
}

void RotatorDevice::setCalibratonOff()
{
    analogWrite(LIGHT_PIN_1, 0);
    analogWrite(LIGHT_PIN_2, 0);
    _brightness = 0;
    calibrationState = 1;
}

void RotatorDevice::setCoverState(int state)
{
    coverState = state;
}
*/