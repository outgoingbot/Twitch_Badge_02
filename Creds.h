#define DEBUG 1 //skip EEPROM Read credentials. use hard coded
//#include "Hardware.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WebSocketsClient.h>
#include <ArduinoJson.h>

StaticJsonDocument<200> doc; // Allocate the JSON document
WebSocketsClient webSocket;// Declare websocket client class variable

#include <EEPROM.h>

class secret 
{

private:
// Initialize network parameters
String ssid="";
String password="";
// Parameters for Twitch channel
String twitch_oauth_token= "oauth:";
String twitch_nick="esp8266led";
String twitch_channel="#esp8266led";

//EEPROM
int addr = 0;
struct {
	char strSSID[50] = "";
	char strPASSWORD[50] = "";
	char strCHANNEL[50] = "";
	char strNICK[50] = "";
	char strTOKEN[100] = "";
	char flagFIRSTBOOT = 1;
} EEPROMdata;


public:
  secret() {} //constructor


  void setssid( const String &SECRET_SSID){
	  ssid = SECRET_SSID;
  }
  
  String getssid() const{
	  return ssid;
  }

  void setpassword( const String &SECRET_PASS){
	  password = SECRET_PASS;
  }
  
  String getpassword() const{
	  return password;
  }
  
  void settwitch_oauth_token( const String &TWITCH_OAUTH_TOKEN ){
	  twitch_oauth_token = TWITCH_OAUTH_TOKEN;
  }
  
  String gettwitch_oauth_token() const{
	  return twitch_oauth_token;
  }

  void settwitch_nick( const String &TWITCH_NICK ){
	  twitch_nick = TWITCH_NICK;
  }
  
  String gettwitch_nick() const {
	  return twitch_nick;
  }
  
  void settwitch_channel( const String &TWITCH_CHANNEL ){
	  twitch_channel = TWITCH_CHANNEL;
  }
  
  String gettwitch_channel() const {
	  return twitch_channel;
  }

void startwifi() {
	int credsTimout = 20;
	int credTime = 0;
	EEPROM.begin(512);
	Serial.begin(115200);
	digitalWrite(LED_BUILTIN,1);
	Serial.println("Chat Badge XxMLG-420xX ");
	Serial.println();
	Serial.println("Press Enter to change Credentials");
	while (!Serial.available()){
		static int i = credsTimout;
		Serial.printf("%d..",i--);
		delay(500);
		if(!i) break;
	}
	
  if(Serial.read()=='\n' || EEPROMdata.flagFIRSTBOOT){
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
	
	//write to EEPROM here//
	//EEPROMdata.strSSID = ssid.c_str();
	//EEPROMdata.flagFIRSTBOOT = 0; //clear the FirstBoot flag
	//EEPROM.put(addr,EEPROMdata); //write to the struct
	//EEPROM.commit();		  //flash self-write 512 byte block
  }
  
  //read EEPROM here//
  //if(!DEBUG) EEPROM.get(addr,EEPROMdata);	//read from 512 block to struct
  
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
