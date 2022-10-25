#include "device/RotatorDevice.h"

RotatorDevice::RotatorDevice()
{
    pinMode(CW_PIN, INPUT_PULLUP); 
    pinMode(CCW_PIN, INPUT_PULLUP);

    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);

    //pinMode(EN_PIN, OUTPUT);
    
    digitalWrite(STEP_PIN, LOW);
    digitalWrite(DIR_PIN, LOW);
    //digitalWrite(EN_PIN, LOW);

    _stepper = new AccelStepper(AccelStepper::FULL4WIRE, STEP_PIN, DIR_PIN, CW_PIN, CCW_PIN, true);
    _stepper->setMaxSpeed(800);// 5000 works good,  use 500000 for confrom test1000 geared rotator10000 for geared stepper   200 for non-geared large stepper(500 max)  also may depend on what else is on loop()
    _stepper->setAcceleration(1000);//1000 for geared rotator  10000 for geared stepper    1000 for non-geared large stepper
    _stepper->setCurrentPosition(0);
    //_stepper->setCurrentPosition(readFocuserPos());
  
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
    Log.traceln("RotatorDevice::getIsMoving()");
    return _isMoving;
}

/*
Returns the rotator's mechanical current position.
Returns the raw mechanical position of the rotator in degrees.
*/
double RotatorDevice::getMechanicalPosition()
{
    Log.traceln("RotatorDevice::getMechanicalPosition()");
    // In Degrees
    return _mechanicalPosition;
}

/*
Returns the rotator's current position.
Current instantaneous Rotator position, in degrees.
*/
double RotatorDevice::getPosition()
{
    Log.traceln("RotatorDevice::getPosition()");
    // In Degrees
    double val = 0.0;
    return val; //(double)_stepper->currentPosition();
}

/**
 * @brief Returns the rotator’s Reverse state.
 * 
 * @return true 
 * @return false 
 */
bool RotatorDevice::getReverseState()
{
    Log.traceln("RotatorDevice::getReverseState()");
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
    Log.traceln("RotatorDevice::getTargetPosition()");
    return _targetPosition;
}

// PUT
/*
Sets the rotator’s Reverse state.

*/
void RotatorDevice::putReverseState(bool reverse)
{
    Log.traceln("RotatorDevice::putReverseState(bool reverse)");
    _reverseState = reverse;
}

/*
Immediatley stops rotator motion.
Immediately stop any Rotator motion due to a previous Move or MoveAbsolute method call.
*/
void RotatorDevice::putHalt()
{
    Log.traceln("RotatorDevice::putHalt()");
    _stepper->stop();
    _halt = true;
}

/*
Moves the rotator to a new relative position.
Causes the rotator to move Position degrees relative to the current Position value.
*/
void RotatorDevice::putMove(double position)
{
    Log.traceln("RotatorDevice::putMove(double position)");
    _targetPosition = position;
    
}

/*
Moves the rotator to a new absolute position.
Causes the rotator to move the absolute position of Position degrees.
*/
void RotatorDevice::putMoveAbsolute(double position)
{
    Log.traceln("RotatorDevice::putMoveAbsolute(double position)");
    _targetPosition = position;
}

/*
Moves the rotator to a new raw mechanical position.
Causes the rotator to move the mechanical position of Position degrees.
*/
void RotatorDevice::putMoveMechanical(double position)
{
    Log.traceln("RotatorDevice::putMoveMechanical(double position)");
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

void RotatorDevice::update()
{
    if(_stepper == nullptr)
    {
        return;
    }

    if (_isFindingHome == true){
        _stepper->moveTo(_targetPosition);
      return;
    }

      
    if(_targetPosition != _stepper->currentPosition())
    {
        if(_targetPosition < 0 || _targetPosition > maxSteps)
        {
            Serial.println("out of range");
            return;
        }
    else
    {
       _stepper->moveTo(_targetPosition);
    }
  }

}