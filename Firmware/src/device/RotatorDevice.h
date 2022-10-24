#pragma once

#include <Arduino.h>
#include <ArduinoLog.h>
#include "configuration.hpp"

class RotatorDevice
{


    public:
        RotatorDevice();

        bool connected = false;
        String uniqueID = "";

        bool    getCanReverse();
        bool    getIsMoving();
        double  getMechanicalPosition();
        double  getPosition();
        bool    getReverseState();
        double  getStepSize();
        double  getTargetPosition();

        void putReverseState(bool reverse);
        void putHalt();
        void putMove(double position);
        void putMoveAbsolute(double position);
        void putMoveMechanical(double position);
        void putSync(double position);

    private:
        int _brightness;
        bool _canReverse = true;
        bool _isMoving = false;
        double _mechanicalPosition = 0.0; // Degrees
        double _position = 0.0; // Degrees
        bool _reverseState = false;
        double _stepSize = 0.0;
        double _targetPosition = 0.0;
        double _targetMechanicalPosition = 0.0;

        bool _halt = false;

        //void writeRelayData(int relay, int boolValue, double doubleValue);
        //byte relayData = B00000000;
};
