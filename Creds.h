#define DEBUG 1 //skip credentials. use hard coded
#include "Hardware.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>



StaticJsonDocument<200> doc; // Allocate the JSON document
WebSocketsClient webSocket;// Declare websocket client class variable

class secret 
{


// Initialize network parameters
String ssid="";
String password="";
// Parameters for Twitch channel
String twitch_oauth_token= "oauth:";
String twitch_nick="esp8266led";
String twitch_channel="#esp8266led";


public:
  secret() {}
  secret(const String &SECRET_SSID, const String &SECRET_PASS, const String &TWITCH_OAUTH_TOKEN, const String &TWITCH_NICK, const String &TWITCH_CHANNEL)
  {
    ssid = SECRET_SSID;
    password = SECRET_PASS;
    twitch_oauth_token = TWITCH_OAUTH_TOKEN;
    twitch_nick = TWITCH_NICK;
    twitch_channel = TWITCH_CHANNEL;
	
  }


void setssid( const String &SECRET_SSID)
  {
    ssid = SECRET_SSID;
  }  
String getssid() const 
  {
    return ssid;
  }

void setpassword( const String &SECRET_PASS) 
  {
    password = SECRET_PASS;
  } 
String getpassword() const 
  {
    return password;
  }

void settwitch_oauth_token( const String &TWITCH_OAUTH_TOKEN ) 
  {
    twitch_oauth_token = TWITCH_OAUTH_TOKEN; 
  }
String gettwitch_oauth_token() const 
  {
    return twitch_oauth_token;
  }

void settwitch_nick( const String &TWITCH_NICK ) 
  {
    twitch_nick = TWITCH_NICK;
  }
String gettwitch_nick() const {
    return twitch_nick;
  }
  

void settwitch_channel( const String &TWITCH_CHANNEL ) 
  {
    twitch_channel = TWITCH_CHANNEL;
  }
String gettwitch_channel() const {
   return twitch_channel;
  }

void startwifi() {
  Serial.begin(115200);
  digitalWrite(LED_BUILTIN,1);
  Serial.println("Shalom ");
  Serial.println();
  if(!DEBUG){
    Serial.println("Please Enter your SSID ");  // requesting ssid from user
    while (Serial.available() == 0) { }       // looping untill serial input in entered
    ssid = Serial.readString();

    Serial.println("Please Enter your Password ");  // requesting password from user
    while (Serial.available() == 0) { }       // looping untill serial input in entered
    password= Serial.readString();
    Serial.println();
	
	Serial.println("Please Enter your Twitch Oauth Token ");  // requesting twitch_oauth_token from user
	while (Serial.available() == 0) { }       // looping untill serial input in entered
	settwitch_oauth_token( Serial.readString() );
	Serial.println();

	Serial.println("Please Enter your Twitch Nick ");  // requesting twitch_nick from user
	while (Serial.available() == 0) { }       // looping untill serial input in entered
	settwitch_nick( Serial.readString() );
	Serial.println();
	  
	Serial.println("Please Enter your Twitch Channel ");  // requesting twitch_channel from user
	while (Serial.available() == 0) { }       // looping untill serial input in entered
	settwitch_channel( Serial.readString() );
	Serial.println();
  }
  
  // Connect to WiFi
  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){    
    digitalWrite(LED_BUILTIN,1);
    Serial.print(".");
    delay(250);
    digitalWrite(LED_BUILTIN,0);
    delay(250);    
  }
    
  digitalWrite(LED_BUILTIN,0);  //<--- to get to here the wifi needs to connect to a SSID
  //Serial.println();
  Serial.print("\nIP Address: "); 
  Serial.println(WiFi.localIP());
  //Serial.println();
  Serial.print("\nIP Address: "); 
  Serial.println(WiFi.localIP());
}
};
