/*
 MQTT example with Serial Monitor
  - file: "serial_mqtt_loop.ino" v1.0 (ready for GitHub publishing)
  - connects to an MQTT server, either providing username
    and password (MQTT v3.1) or w/o them (version <= MQTT v3.0)
  - publishes user-specified messgae to user-selected topic, then
     subscribes to the topic above; upon success, prints the topic
     message to the Serial port Monitor
  
  - developed by German Kutsy, Litmus Automation LLC. (2014)
*/
#include <Bridge.h>
#include <YunClient.h>
#include <PubSubClient.h>

YunClient yun;

void callback(char* topic, byte* payload, unsigned int length) {
  // handle message arrived
}

byte server[] = { 10, 0, 0, 15 };     // user input reqd
uint16_t port = 1883;                 // user input reqd

char* username = "rAnDoM_chars";      // user input reqd
char* password= "kgrem142";           // user input reqd
char* clientId = "ClientSerial_39243";// user input reqd
char* projectId = "LoopPersonalId";   // user input reqd
char* deviceName = "yun";             // user input reqd
char* jsonKV = "{'programming':true,'litmusAuto':'great'}";  // user input reqd
boolean cleanSession = true;

// no username, no password (version <= MQTT v3.0)
PubSubClient litmus(server,port,callback,yun,clientId,projectId,deviceName,jsonKV,cleanSession);
// username/password used (MQTT v3.1)
//PubSubClient litmus(server,port,callback,yun,username,password,clientId,projectId,deviceName,jsonKV,cleanSession);

void setup() {
  Bridge.begin();
  Serial.begin(9600);
  litmus.loop();
  litmus.connect();  
}

void loop() {
  litmus.publish("openSerial",jsonKV);
  boolean success = litmus.subscribe("openSerial");
  
  if (success)  // ensure USB connectivity to Yun and TTY port is selected
    Serial.println(jsonKV);
}
