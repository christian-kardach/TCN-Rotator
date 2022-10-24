#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPUpdateServer.h>
#include <ArduinoLog.h>

#include "arduino_secrets.h"
#include "device/RotatorHandler.h"

int status = WL_IDLE_STATUS;
///////enter your sensitive data in the Secret tab/arduino_secrets.h
char hostname[] = _HOSTNAME;
char ssid[] = _SSID;     // your network SSID (name)
char pass[] = _PASSWORD; // your network password (use for WPA, or use as key for WEP)
int keyIndex = 0;        // your network key Index number (needed only for WEP)

unsigned int localPort = 32227;  // The Alpaca Discovery test port
unsigned int alpacaPort = 11111; // The (fake) port that the Alpaca API would be available on

char packetBuffer[255]; // buffer to hold incoming packet

ESP8266WebServer *server = new ESP8266WebServer(alpacaPort);

ESP8266HTTPUpdateServer updater;
WiFiUDP Udp;

RotatorHandler *device = new RotatorHandler(server);

void CheckForDiscovery()
{
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize)
  {
    Log.traceln("Received packet of size: %d" CR, packetSize);
    IPAddress remoteIp = Udp.remoteIP();
    Log.traceln("From %s , on port %d" CR, remoteIp.toString().c_str(), Udp.remotePort());

    // read the packet into packetBufffer
    int len = Udp.read(packetBuffer, 255);
    if (len > 0)
    {
      // Ensure that it is null terminated
      packetBuffer[len] = 0;
    }
    Log.traceln("Contents: %s" CR, packetBuffer);

    // No undersized packets allowed
    if (len < 16)
    {
      return;
    }

    if (strncmp("alpacadiscovery1", packetBuffer, 16) != 0)
    {
      return;
    }

    char response[36] = {0};
    sprintf(response, "{\"AlpacaPort\": %d}", alpacaPort);

    uint8_t buffer[36] = "{\"AlpacaPort\": 11111}";

    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(buffer, 36);
    Udp.endPacket();
  }
}

void printWifiStatus()
{
  // print the SSID of the network you're attached to:
  Log.traceln(F("SSID: %s" CR), WiFi.SSID());

  // print your board's IP address:
  IPAddress ip = WiFi.localIP();
  Log.traceln(F("IP Address: %s" CR), ip.toString().c_str());

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Log.traceln("signal strength (RSSI): %l dBm" CR, rssi);
}

void handleMgmtVersions() { device->handlerMgmtVersions(); }
void handleMgmtDescription() { device->handlerMgmtDescription(); }
void handleMgmtConfiguredDevices() { device->handlerMgmtConfiguredDevices(); }

void handleConnected() { device->handlerConnected(); }
void handleDescriptionGet() { device->handlerDescriptionGet(); }
void handleDriverInfoGet() { device->handlerDriverInfoGet(); }
void handleDriverVersionGet() { device->handlerDriverVersionGet(); }
void handleInterfaceVersionGet() { device->handlerInterfaceVersionGet(); }
void handleNameGet() { device->handlerNameGet(); }
void handleSupportedActionsGet() { device->handlerSupportedActionsGet(); }

void handleAction() { device->handleAction(); }
void handleCommandBlind() { device->handleCommandBlind(); }
void handleCommandBool() { device->handleCommandBool(); }
void handleCommandString() { device->handleCommandString(); }

// GET
void handleDriver0CanReverse() { device->handlerDriver0CanReverse(); }
void handleDriver0IsMoving() { device->handlerDriver0IsMoving(); }
void handleDriver0MechanicalPosition() { device->handlerDriver0MechanicalPosition(); }
void handleDriver0Position() { device->handlerDriver0Position(); }
void handleDriver0Reverse() { device->handlerDriver0Reverse(); }
void handleDriver0StepSize() { device->handlerDriver0StepSize(); }
void handleDriver0TargetPosition() { device->handlerDriver0TargetPosition(); }


// PUT
void handleDriver0Reverse() { device->handlerDriver0Reverse(); }
void handleDriver0Halt() { device->handlerDriver0Halt(); }
void handleDriver0Move() { device->handlerDriver0Move(); }
void handleDriver0MoveAbsolute() { device->handlerDriver0MoveAbsolute(); }
void handleDriver0MoveMechanical() { device->handlerDriver0MoveMechanical(); }
void handleDriver0Sync() { device->handlerDriver0Sync(); }



/******************************************
 * SETUP
 ******************************************/
void setup()
{
  Serial.begin(9600);

  // Initialize with log level and log output.
  Log.begin(LOG_LEVEL_TRACE, &Serial);

  Log.infoln("Connecting to WIFI...");

  // Some ESP8266 modules broadcast their own network, this turns that off
  WiFi.mode(WIFI_STA);
  WiFi.hostname(hostname);

  // attempt to connect to the Wifi network defined in arduino_secrets.h
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Log.traceln(".");
  }

  Log.infoln("Connected to wifi");
  printWifiStatus();

  // Management API
  server->on("/management/apiversions", HTTP_GET, handleMgmtVersions);
  server->on("/management/v1/description", HTTP_GET, handleMgmtDescription);
  server->on("/management/v1/configureddevices", HTTP_GET, handleMgmtConfiguredDevices);

  server->on("/api/v1/rotator/0/connected", HTTP_ANY, handleConnected);
  server->on("/api/v1/rotator/0/description", HTTP_GET, handleDescriptionGet);
  server->on("/api/v1/rotator/0/driverinfo", HTTP_GET, handleDriverInfoGet);
  server->on("/api/v1/rotator/0/driverversion", HTTP_GET, handleDriverVersionGet);
  server->on("/api/v1/rotator/0/interfaceversion", HTTP_GET, handleInterfaceVersionGet);
  server->on("/api/v1/rotator/0/name", HTTP_GET, handleNameGet);
  server->on("/api/v1/rotator/0/supportedactions", HTTP_GET, handleSupportedActionsGet);

  server->on("/api/v1/rotator/0/action", HTTP_PUT, handleAction);
  server->on("/api/v1/rotator/0/commandblind", HTTP_PUT, handleCommandBlind);
  server->on("/api/v1/rotator/0/commandbool", HTTP_PUT, handleCommandBool);
  server->on("/api/v1/rotator/0/commandstring", HTTP_PUT, handleCommandString);

  // Calibrator-specific functions
  server->on("/api/v1/rotator/0/canreverse", HTTP_GET, handleDriver0CanReverse);
  server->on("/api/v1/rotator/0/ismoving", HTTP_GET, handleDriver0IsMoving);
  server->on("/api/v1/rotator/0/mechanicalposition", HTTP_GET, handleDriver0MechanicalPosition);
  server->on("/api/v1/rotator/0/position", HTTP_GET, handleDriver0Position);
  server->on("/api/v1/rotator/0/reverse", HTTP_GET, handleDriver0Reverse);
  server->on("/api/v1/rotator/0/stepsize", HTTP_GET, handleDriver0StepSize);
  server->on("/api/v1/rotator/0/targetposition", HTTP_GET, handleDriver0TargetPosition);

  server->on("/api/v1/rotator/0/reverse", HTTP_PUT, handleDriver0Reverse);
  server->on("/api/v1/rotator/0/halt", HTTP_PUT, handleDriver0Halt);
  server->on("/api/v1/rotator/0/move", HTTP_PUT, handleDriver0Move);
  server->on("/api/v1/rotator/0/moveabsolute", HTTP_PUT, handleDriver0MoveAbsolute);
  server->on("/api/v1/rotator/0/movemechanical", HTTP_PUT, handleDriver0MoveMechanical);
  server->on("/api/v1/rotator/0/sync", HTTP_PUT, handleDriver0Sync);

  /*
  //Custom
  server.on("/status",                              HTTP_GET, handlerStatus);
  server.on("/restart",                             HTTP_ANY, handlerRestart);
  */

  updater.setup(server);
  server->begin();
  Log.infoln("Alpaca server handlers setup & started...");
  Log.infoln("Listening for Alpaca discovery requests...");

  Udp.begin(localPort);
}

void loop()
{
  server->handleClient();
  CheckForDiscovery();
}