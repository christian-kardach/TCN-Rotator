#include "device/RotatorHandler.h"

/*
Successful transaction 0x0 (0) N/A
Property or method not implemented 0x400 (1024) 0x80040400
Invalid value 0x401 (1025) 0x80040401
Value not set 0x402 (1026) 0x80040402
Not connected 0x407 (1031) 0x80040407
Invalid while parked 0x408 (1032) 0x80040408
Invalid while slaved 0x409 (1033) 0x80040409
Invalid operation 0x40B (1035) 0x8004040B
Action not implemented 0x40C (1036) 0x8004040C
*/

RotatorHandler::RotatorHandler(ESP8266WebServer *server)
{
    _server = server;
    rotatorDevice = new RotatorDevice();
    serverTransactionID = 0;
}

void RotatorHandler::debugServerQuery()
{
    for (int i = 0; i < _server->args(); i++) {
        Log.traceln("%d" CR, i);
        Log.traceln("%s" CR, _server->argName(i));
        Log.traceln("%s" CR, _server->arg(i));
        Log.traceln("--------------------------");
    }
}

void RotatorHandler::incrementServerTransID()
{
    serverTransactionID++;
}

void RotatorHandler::returnEmpty(String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void RotatorHandler::returnBoolValue(bool val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void RotatorHandler::returnStringValue(String val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void RotatorHandler::returnIntValue(int val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void RotatorHandler::returnFloatValue(float val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void RotatorHandler::returnJsonArrayValue(JsonArray val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}

void RotatorHandler::returnDoubleValue(double val, String errMsg, int errNr)
{
    incrementServerTransID();
    DynamicJsonDocument doc(1024);

    doc["Value"] = val;
    doc["ErrorMessage"] = errMsg;
    doc["ErrorNumber"] = errNr;
    doc["ClientTransactionID"] = transID;
    doc["ServerTransactionID"] = serverTransactionID;

    String output;
    serializeJson(doc, output);
    Log.traceln(F("Returning: %s" CR), output.c_str());

    _server->send(200, "text/json", output);
}
/*
 * ALPACA DEVICE MANAGEMENT
 */

void RotatorHandler::handlerMgmtVersions()
{
    Log.traceln("handlerMgmtVersions called...");
    incrementServerTransID();

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        DynamicJsonDocument doc(1024);

        const size_t CAPACITY = JSON_ARRAY_SIZE(1);
        StaticJsonDocument<CAPACITY> devices;
        JsonArray array = devices.to<JsonArray>();
        array.add(1);
        // returnJsonArrayValue(array);
        
        doc["Value"] = array;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());
        // return output;
        _server->send(200, "text/json", output);
        // sendDeviceSetup( returnCode, message, err );
        
    }
}

void RotatorHandler::handlerMgmtDescription()
{
    Log.traceln("handlerMgmtDescription called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        incrementServerTransID();
        DynamicJsonDocument val(1024);

        val["ServerName"] = SERVER_NAME; //"TCN Mount Switch";
        val["Manufacturer"] = MANUFACTURER; // "Christian Kardach";
        val["ManufacturerVersion"] = MANUFACTURER_VERSION; //"1.0";
        val["Location"] = LOCATION; //"SE";

        const size_t CAPACITY = JSON_ARRAY_SIZE(5);
        StaticJsonDocument<CAPACITY> devices;
        JsonArray array = devices.to<JsonArray>();
        array.add(val);

        //returnJsonArrayValue(array);
        
        DynamicJsonDocument doc(1024);
        doc["Value"] = val;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());
        _server->send(200, "text/json", output);
        
    }
}

void RotatorHandler::handlerMgmtConfiguredDevices()
{
    Log.traceln("handlerMgmtConfiguredDevices called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        incrementServerTransID();
        DynamicJsonDocument val(1024);
        DynamicJsonDocument doc(1024);

        const size_t CAPACITY = JSON_ARRAY_SIZE(5);
        StaticJsonDocument<CAPACITY> devices;

        val["DeviceName"] = DEVICE_NAME; //"TCN Mount Switch";
        val["DeviceType"] = DEVICE_TYPE; //"Switch";
        val["DeviceNumber"] = DEVICE_NR; //0;
        val["UniqueID"] = UNIQUE_CLIENT_ID;
        JsonArray array = devices.to<JsonArray>();
        array.add(val);

        // returnJsonArrayValue(array);
        
        doc["Value"] = array;
        doc["ErrorMessage"] = "";
        doc["ErrorNumber"] = 0;
        doc["ClientTransactionID"] = transID;
        doc["ServerTransactionID"] = serverTransactionID;

        String output;
        serializeJson(doc, output);
        Log.traceln(F("Returning: %s" CR), output.c_str());

        _server->send(200, "text/json", output);
        
    }
}

void RotatorHandler::handlerConnected()
{
    Log.traceln("handlerConnected called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    if (_server->method() == HTTP_GET)
    {
        Log.traceln("handlerConnected GET called");

        String deviceType = _server->arg("device_type");
        //uint32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

        returnBoolValue(coverCalibratorDevice->connected, "", 0);
    }

    if (_server->method() == HTTP_PUT)
    {
        Log.traceln("handlerConnected POST called");

        // String _connected = _server->arg("Connected");
        coverCalibratorDevice->connected = (bool)_server->arg("Connected");
        // Log.traceln("%t", CR, coverCalibratorDevice->connected);

        returnEmpty("", 0);
    }
}

/***********************************
 * ASCOM STANDARD
 **********************************/
void RotatorHandler::handlerDescriptionGet()
{
    Log.traceln("handlerDescriptionGet called");
    returnStringValue(DESCRIPTION, "", 0);
}

void RotatorHandler::handlerDriverInfoGet()
{
    Log.traceln("handlerDriverInfoGet called");
    returnStringValue(DRIVER_INFO, "", 0);
}

void RotatorHandler::handlerDriverVersionGet()
{
    Log.traceln("handlerDriverVersionGet called");
    returnStringValue(DRIVER_VERSION, "", 0);
}

void RotatorHandler::handlerInterfaceVersionGet()
{
    Log.traceln("handlerInterfaceVersionGet called");
    returnIntValue(1, "", 0);
}

void RotatorHandler::handlerNameGet()
{
    Log.traceln("handlerNameGet called");
    returnStringValue(DEVICE_NAME, "", 0);
}

void RotatorHandler::handlerSupportedActionsGet()
{
    Log.traceln("handlerSupportedActionsGet called");

    DynamicJsonDocument val(1024);
    const size_t CAPACITY = JSON_ARRAY_SIZE(13);
    StaticJsonDocument<CAPACITY> devices;
    JsonArray array = devices.to<JsonArray>();
    
    array.add("action");
    array.add("commandblind");
    array.add("commandbool");
    array.add("commandstring");

    returnJsonArrayValue(array, "", 0);
    
}

void RotatorHandler::handleAction()
{
    Log.traceln("handleAction called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    //u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String action = _server->arg("Action");
    String parameters = _server->arg("Parameters");

    returnStringValue("ok", "", 0);
}

void RotatorHandler::handleCommandBlind()
{
    Log.traceln("handleCommandBlind called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command);
    Log.traceln("%s" CR, raw);

    returnEmpty("", 0);
}

void RotatorHandler::handleCommandBool()
{
    Log.traceln("handleCommandBool called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command);
    Log.traceln("%s" CR, raw);

    returnBoolValue(true, "", 0);
}

void RotatorHandler::handleCommandString()
{
    Log.traceln("handleCommandBool called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();

    String deviceType = _server->arg("device_type");
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();

    String command = _server->arg("Command");
    String raw = _server->arg("Raw");

    Log.traceln("%s" CR, command.c_str());
    Log.traceln("%s" CR, raw.c_str());

    returnStringValue("ok", "", 0);
}

/***********************************
 * ASCOM Alpaca Rotator
 **********************************/
// GET
/*
True if the Rotator supports the Reverse method.
*/
void RotatorHandler::handlerDriver0CanReverse()
{
    Log.traceln("handlerDriver0TargetPosition called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnBoolValue(coverCalibratorDevice->getCanReverse(), "", 0);
}

/*
True if the rotator is currently moving to a new position. False if the focuser is stationary.
*/
void RotatorHandler::handlerDriver0IsMoving()
{
    Log.traceln("handlerDriver0IsMoving called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnBoolValue(rotatorDevice->getIsMoving(), "", 0);
}

/*
Returns the raw mechanical position of the rotator in degrees.
*/
void RotatorHandler::handlerDriver0MechanicalPosition()
{
    Log.traceln("handlerDriver0MechanicalPosition called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnDoubleValue(rotatorDevice->getMechanicalPosition(), "", 0);
}

/*
Current instantaneous Rotator position, in degrees.
*/
void RotatorHandler::handlerDriver0Position()
{
    Log.traceln("handlerDriver0Position called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnDoubleValue(rotatorDevice->getPosition(), "", 0);
}

/*
Returns the rotator’s Reverse state.
*/
void RotatorHandler::handlerDriver0Reverse()
{
    Log.traceln("handlerDriver0Reverse called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnBoolValue(rotatorDevice->getReverseState(), "", 0);
}

/*
The minimum StepSize, in degrees.
*/
void RotatorHandler::handlerDriver0StepSize()
{
    Log.traceln("handlerDriver0StepSize called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnDoubleValue(rotatorDevice->getStepSize(), "", 0);
}

/*
The destination position angle for Move() and MoveAbsolute().
*/
void RotatorHandler::handlerDriver0TargetPosition()
{
    Log.traceln("handlerDriver0TargetPosition called");
    
    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    returnDoubleValue(rotatorDevice->getTargetPosition(), "", 0);
}

// PUT
/*
Sets the rotator’s Reverse state.
*/
void RotatorHandler::handlerDriver0Reverse()
{
    Log.traceln("handlerDriver0Reverse called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    int rev = _server->arg("Reverse").toInt();

    if (_server->method() == HTTP_PUT)
    {
        
        rotatorDevice->putReverseState(1);
        returnEmpty("", 0);
    }
}

/*
Immediately stop any Rotator motion due to a previous Move or MoveAbsolute method call.
*/
void RotatorHandler::handlerDriver0Halt()
{
    Log.traceln("handlerDriver0Halt called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_PUT)
    {
        
        rotatorDevice->putHalt();
        returnEmpty("", 0);
    }
}

/*
Causes the rotator to move Position degrees relative to the current Position value.
*/
void RotatorHandler::handlerDriver0Move()
{
    Log.traceln("handlerDriver0Move called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    double position = _server->arg("Position ").toDouble();

    if (_server->method() == HTTP_PUT)
    {
        
        rotatorDevice->putMove(position);
        returnEmpty("", 0);
    }
}

/*
Causes the rotator to move the absolute position of Position degrees.
*/
void RotatorHandler::handlerDriver0MoveAbsolute()
{
    Log.traceln("handlerDriver0MoveAbsolute called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_PUT)
    {
        double position = _server->arg("Position ").toDouble();
        rotatorDevice->putMoveAbsolute(position);
        returnEmpty("", 0);
    }
}

/*
Causes the rotator to move the mechanical position of Position degrees.
*/
void RotatorHandler::handlerDriver0MoveMechanical()
{
    Log.traceln("handlerDriver0MoveAbsolute called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_PUT)
    {
        double position = _server->arg("Position ").toDouble();
        rotatorDevice->putMoveMechanical(position);
        returnEmpty("", 0);
    }
}

/*
Syncs the rotator to the specified position angle without moving it.
*/
void RotatorHandler::handlerDriver0Sync()
{
    Log.traceln("handlerDriver0MoveAbsolute called");

    clientID = (uint32_t)_server->arg("ClientID").toInt();
    transID = (uint32_t)_server->arg("ClientTransactionID").toInt();
    // u_int32_t deviceNumber = (uint32_t)_server->arg("device_number").toInt();
    u_int32_t id = (uint32_t)_server->arg("ID").toInt();

    if (_server->method() == HTTP_PUT)
    {
        double position = _server->arg("Position ").toDouble();
        rotatorDevice->putSync(position);
        returnEmpty("", 0);
    }
}