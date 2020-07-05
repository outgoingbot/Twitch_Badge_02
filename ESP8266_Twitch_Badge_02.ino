//add Hex Flash Support for Firmware Updates. i.e firmware distrobution method without compilation
//customizable keywords and parameters?
//bitmap loading?
//low power mode options and power requirements (battery capacity) ?


#include "Creds.h"

#define FONT_3X5 0
#define FONT_8X8 1
#define DEBUGPRINTSPEED 10
#define PRINTSPEED 50
#define MAXPRINTLENGTH 200
#define MAXRGBCOLOR 64

//commmands from twitch
const String keyword_1 = "setled(";
const String keyword_2 = "print(";
const String keyword_3 = "flash(";
const String keyword_4 = "vote(";
const String keyword_5 = "vReset(";

//------------GLOBAL VARS-----------------
uint32_t Forecolor = 0x000800;
uint8_t Brange = MAXRGBCOLOR/4; //set the brightness for each chanel in getrand();
uint8_t green; //used in getrand
uint8_t red;   //used in getrand
uint8_t blue;  //used in getrand

unsigned int voteTally[3]={0,0,0}; //{candidate_1, candidate_2, Total votes}

secret o; 


void setup() { 
  setupHardware();    
  o.startwifi();
  
  printStringWithShiftL("  CONNECTED !!!   ", DEBUGPRINTSPEED,0,FONT_8X8); //see chartable for valid characters. all caps a few symbols, etc
  char ipCharArray[20];
  IPAddress ip = WiFi.localIP();
  sprintf(ipCharArray, "%d.%d.%d.%d   ", ip[0], ip[1], ip[2], ip[3]);
  printStringWithShiftL(ipCharArray, DEBUGPRINTSPEED,0,FONT_8X8); //Print he local IP on the LED matrix

 //LedTest(2); //quick led hardware test
  
  webSocket.begin("irc-ws.chat.twitch.tv", 80, "/"); // server address, port, and URL path
  webSocket.onEvent(webSocketEvent); // event handler
  webSocket.setReconnectInterval(5000); // try ever 5000 again if connection has failed
}


void loop() 
{
  webSocket.loop();
}




void webSocketEvent(WStype_t type, uint8_t * payload, size_t length){
  String OAUTH = o.gettwitch_oauth_token();
  String NICK = o.gettwitch_nick();
  String CHANNEL = o.gettwitch_channel();
  switch(type) {
    case WStype_CONNECTED: // If the websocket connection is succesful, try to join the IRC server
      Serial.printf("[WSc] Connected to: %s\n", payload);
      webSocket.sendTXT("PASS " + String(OAUTH) + "\r\n");
      webSocket.sendTXT("NICK " + String(NICK) + "\r\n");
      webSocket.sendTXT("JOIN " + String(CHANNEL) + "\r\n");
      break;
  
    case WStype_TEXT:{ // If we get a response, print it to Serial
      Serial.printf("\nPAYLOAD %s\n", payload); //DEBUG
      String payload_str = String((char*) payload);
      int quote_start = payload_str.indexOf(":$");
      if(quote_start > 0) {
        int quote_end = payload_str.length();
        String cmd_str = payload_str.substring(quote_start+2, quote_end);
        Serial.printf("\nCMD %s\n", cmd_str.c_str()); //DEBUG
        parseMessage(cmd_str);
      }
      break;
	}
	
    case WStype_DISCONNECTED: // Handle disconnecting from the websocket
      Serial.printf("[WSc] Disconnected!\n");
      webSocket.sendTXT("PART " + String(o.gettwitch_channel()) + "\r\n");
      break;
  }
}


void parseMessage(String cmd_str){
		
	//setled(i,g,r,b)  e.g. $setled(4,255,255,255)
  if(cmd_str.indexOf(keyword_1)>=0 && cmd_str.indexOf(")")>0) {
	int cmd_start = keyword_1.length();
	int cmd_end = cmd_str.indexOf(")");
	String buffer_str = cmd_str.substring(cmd_start,cmd_end);
	//Serial.print(buffer_str.c_str());
	unsigned int i, r, g, b;
    sscanf(buffer_str.c_str(), "%d,%d,%d,%d%*s", &i, &g, &r, &b);
	Serial.printf("i=%d  g=%d  g=%d  g=%d\n",i, g, r, b);
    if(!(i<0 || i>NUMPIXELS-1 || g<0 || g> MAXRGBCOLOR || r<0 || r> MAXRGBCOLOR || b<0 || b> MAXRGBCOLOR)){ //check that vars are in "bounds"
	  	  setPixelColor(i,Color(g,r,b));
	  	  FastLED.show();
	}else{
	Serial.printf("%s ERROR !!!",keyword_1.c_str());
	}
  }
  
	//print e.g. $print(HELLO)
    if(cmd_str.indexOf(keyword_2)>=0 && cmd_str.indexOf(")")>0) {
	    int cmd_start = keyword_2.length();
	    int cmd_end = cmd_str.indexOf(")");
	    if(cmd_end > 0 && cmd_end < MAXPRINTLENGTH){
			String buffer_str = cmd_str.substring(cmd_start,cmd_end);
			//Serial.print(buffer_str.c_str());
			printStringWithShiftL("    ", PRINTSPEED,0,FONT_8X8);
			printStringWithShiftL(buffer_str.c_str(),PRINTSPEED,0,FONT_8X8);
			printStringWithShiftL("    ", PRINTSPEED,0,FONT_8X8);
		}else{
		Serial.printf("%s ERROR !!!",keyword_2.c_str());
		}
    }
  
	//flash e.g: $flash(3)
  if(cmd_str.indexOf(keyword_3)>=0 && cmd_str.indexOf(")")>0) {
	  int cmd_start = keyword_3.length();
	  int cmd_end = cmd_str.indexOf(")");
	  String buffer_str = cmd_str.substring(cmd_start,cmd_end);
	  //Serial.print(buffer_str.c_str());
	  unsigned int i;
	  sscanf(buffer_str.c_str(), "%d%*s", &i);
	  Serial.printf("i=%d\n",i);
	  if(!(i<0 || i>NUMPIXELS-1)){ //check that vars are in "bounds"
		  for(int k=0; k<i; k++){
			getrand();
			ColorWipe(Forecolor,1);
			FastLED.show();
		  }
		  ColorWipe(0,5);
	  }else{
	  Serial.printf("%s ERROR !!!",keyword_3.c_str());
	  }
  }
  
  
  	//vote e.g: $vote(0) or $vote(1)
  	if(cmd_str.indexOf(keyword_4)>=0 && cmd_str.indexOf(")")>0) {
	  	unsigned int cmd_start = keyword_4.length();
	  	unsigned int cmd_end = cmd_str.indexOf(")");
	  	String buffer_str = cmd_str.substring(cmd_start,cmd_end);
	  	//Serial.print(buffer_str.c_str());
	  	unsigned int i;
	  	float votePercent[2]={0,0};
		uint8_t voteColorMax = MAXRGBCOLOR; //Max brightness for each voting color (red,blue)
		uint8_t voteColor[2];
		sscanf(buffer_str.c_str(), "%d%*s", &i);
	  	Serial.printf("i=%d\n",i);
	  	if(!(i<0 || i>1)){ //check that vars are in "bounds"
			voteTally[2]++; //increase the total vote count
			if(!i) voteTally[0]++; //increase the candidate vote number
			if(i) voteTally[1]++;
			votePercent[0] = (float)voteTally[0]/(float)voteTally[2]; //votes for 1 / total votes
			votePercent[1] = (float)voteTally[1]/(float)voteTally[2]; //vote for 2 / total votes
			for(int i=0; i<2; i++) {
				voteColor[i] = (uint8_t) (votePercent[i]*voteColorMax);
				//Serial.printf("  VC Percent%d: %f  ", i, votePercent[i]); //DEBUG
				//Serial.printf("  VC%d: %d  ", i, (unsigned int) voteColor[i]); //DEBUG
			}
			  	RGBFillScreen(Color(0, voteColor[0],voteColor[1]));
			  	FastLED.show();
		  	}else{
		  	Serial.printf("%s ERROR !!!",keyword_4.c_str());
	  	}
  	}
	  
	//vReset e.g: $vReset
	if(cmd_str.indexOf(keyword_5)>=0) {
		for(int i=0; i<3; i++) voteTally[i] = 0; //reset the vote tally and the vote count
		Serial.printf("vote reset\n"); //DEBUG
		getrand();
		ColorWipe(Forecolor,10);
		ColorWipe(0,10);
	}
}



void PollButtons(){ //read the Buttons status
	if(!digitalRead(BTN1_PIN)){
		//cli();//stop interrupts
		lmd.clear();
		while (digitalRead(BTN1_PIN) == LOW) delay(10);
		// do stuff
		Serial.printf("Button 1\n");
		printStringWithShiftL("1", 10,0,FONT_8X8);
	}

	if(!digitalRead(BTN2_PIN)){
		lmd.clear();
		while (digitalRead(BTN2_PIN) == LOW) delay(10);
		//do stuff
		Serial.printf("Button 2\n");
		printStringWithShiftL("2", 10,0,FONT_8X8);
	}
	
}


void setPixelColor(int i, uint32_t c){ //input a 32-bit color. write the g,r,b to led[i] color buffer
	leds[i].g = ((c >> 16) & 0xFF); //Green
	leds[i].r = ((c >> 8) & 0xFF); //Red
	leds[i].b = ((c >> 0) & 0xFF); //Blue
}


uint32_t Color(uint8_t g, uint8_t r, uint8_t b) {
	return ((uint32_t)g << 16) | ((uint32_t)r <<  8) | b;
}


void RGBFillScreen(uint32_t c){
	for(int i=0; i<NUMPIXELS; i++){
		setPixelColor(i,c);
	}
	FastLED.show();
}

void ClearMatrix(){
	for (int x=0; x<numCols; x++){
		for (int y=0; y<numRows; y++){
			lmd.setPixel(x,y,0);
		}
	}
	lmd.display();
}


void rotateScreen(float angPercent, int dir){ //rotates all pixels theta rads counter clockwise
	//dir: 1 for CCW, -1 for CW
	storeScreen();
	int angleIndex = 0;
	for(float i=0; i<=2*angPercent; i+=.05){
		PollButtons();
		for(int x=0; x<16; x++){
			for(int y=0; y<16; y++){
				int myXT = (int) (myOffset+(((x-myOffset)*cos(M_PI*i))-(dir)*((y-myOffset)*sin(M_PI*i))));
				int myYT = (int) (myOffset+(((x-myOffset)*(dir)*sin(M_PI*i))+((y-myOffset)*cos(M_PI*i))));
				SetLEDxy(myXT,myYT,buffTemp[x][y]);
			}
		}
		lmd.display();
	}
	if(ceilf(angPercent) == angPercent) printStored(); //if angle to rotate is integer value then fix rotation error by printing the tempbuff
}

void storeScreen(){ //copy every mono led state to a buffer called bitmap
	for(int x=0; x<16; x++){
		for(int y=0; y<16; y++){
			buffTemp[x][y] = GetLEDxy(x,y);
		}
	}
}

void printStored(){ //print the buffer called bitmap
	for(int x=0; x<16; x++){
		for(int y=0; y<16; y++){
			SetLEDxy(x,y,buffTemp[x][y]);
		}
	}
	lmd.display();
}


void SetLEDxy(int x, int y, bool c){ //just pass in cartesian (x,y) pairs
	if(x<8){
		lmd.setPixel(Y2[y], X1[x], c);
		}else{
		lmd.setPixel(Y3[y], X1[x], c);
	}
}

bool GetLEDxy(int x, int y){ //just pass in cartesian (x,y) pairs
	if(x<8){
		return lmd.getPixel(Y2[y], X1[x]);
		}else{
		return lmd.getPixel(Y3[y], X1[x]);
	}
}



void drawBitmap(char* image){ //draws a bitmap from a hex array defined at top
	byte Tempbuff = 0;
	int mySide = 1;
	int myYY = 0;
	for(int x=0; x<32; x++){
		Tempbuff = pgm_read_byte(&(image[x]));
		uint8_t b = 0b10000000;
		if(x%2==0){
			mySide = 0;
			if(x) myYY++;
			}else{
			mySide = 8;
		}
		for (int k = 0; k < 8; k++) {
			if (!(Tempbuff&b)) SetLEDxy(mySide+k,numRows-1-myYY,1);
			b = b >> 1;
		}
	}
	lmd.display();
}


void FillScreen(bool c){
	for(int x=0; x<16; x++){
		for(int y=0; y<16; y++){
			SetLEDxy(x,y,c);
		}
	}
}

/*
//Extract characters for Static Text
void printString(char* s, int x, int y){
	while (*s != 0) {
		printChar(*s, x, y);
		s++;
		x+=4;
	}
}
*/

/*
// Put extracted character on Display   <-------------------NEED to change to support two fonts
void printChar(char c, int x, int y){
	byte mybuff;
	if (c < 32) return; //error check for ascii values less than ASCII  < ' ' (space) = 32 >
	c -= 32;      //align the char ascii with the CharTable
	for (int j = 0; j < 3; j++) {
		mybuff = pgm_read_byte(&(CH[3*c+j]));
		uint8_t b = 0b00000001;
		for (int k = y; k < y+5; k++) {
			if (mybuff&b) SetLEDxy(j+x,k,1);
			b = b << 1;
		}

	}
}

*/

//Extract characters for Scrolling text -PHASE THESE OUT? same as above but with shiftL()
void printStringWithShiftL(const char* s, int shift_speed, int textpos, int font) {
	while (*s != 0) {
		printCharWithShiftL(*s, shift_speed, textpos, font);
		s++;
	}
}

// Put extracted character on Display
//choose a font 0 for 3x5 font and 1 for 8x8 font
void printCharWithShiftL(char c, int shift_speed, int textpos, int font) {
	if (c < 32) return; //error check for ascii values less than ASCII  < ' ' (space) = 32 >
	c -= 32; //align the char ascii with the CharTable
	if(font == 0){
		byte mybuff;
		for (int j = 0; j < 3; j++) {
			mybuff = pgm_read_byte(&(CH_3x5[3*c+j]));
			uint8_t b = 0b00000001;
			for (int k = textpos; k < textpos+5; k++) {
				if (mybuff&b) SetLEDxy(numCols-1,k,1);
				b = b << 1;
			}
			lmd.display();
			ShiftLEDLeft(); //shift every column one column left (one space between letters)
			BlankColumn(numCols-1);
			delay(shift_speed);
		}
		}else{
		byte mybuff[8];
		for (int i = 0; i < 8; i++) mybuff[i] = pgm_read_byte(&(CH_8x8[8*c+i])); //copy all 8 bytes from font
		uint8_t b = 0b10000000;												//Mask Location starts at 1
		for (int i = 0; i < 8; i++){											//loop through all 8 bit positions
			for (int k = 0; k < 8; k++) if (mybuff[k]&b) SetLEDxy(numCols-1,k,1);//loop through each byte
			b = b >> 1;
			lmd.display(); //display a column
			ShiftLEDLeft(); //shift every column one column left (one space between letters)
			BlankColumn(numCols-1);
			delay(shift_speed);
		}
	}
	ShiftLEDLeft(); // one space after letter
}

//shift mono leds Left function
void ShiftLEDLeft () {   //Shift columns right 1 palce
	for ( int x = 1; x <= numCols-1; x++) { //read one behind left
		for (int y = 0; y <= numRows-1; y++) { //read each Led value
			SetLEDxy(x-1,y,GetLEDxy(x,y));
		}
	}
	lmd.display();
}

//shift mono leds Left function
void ShiftLEDDown () {   //Shift columns right 1 palce
	for (int y = numRows-2; y >= 0; y--) { //read one behind left
		for (int x = 0; x <= numCols-1; x++) { //read each Led value
			SetLEDxy(x,y+1,GetLEDxy(x,y));
		}
	}
	lmd.display();
}

void BlankColumn(int c) {    //wipes the coulmn 0 to clear out jjunk, to get ready for shifting
	for (int w = 0; w <= numRows-1; w++) {
		SetLEDxy(c,w,0);
	}
}

void BlankRow(int c) {    //wipes the coulmn 0 to clear out jjunk, to get ready for shifting
	for (int w = 0; w <= numCols-1; w++) {
		SetLEDxy(w,c,0);
	}
}


void ColorWipe(uint32_t c, int s){
	for(int i=0;i<NUMPIXELS;i++){
		setPixelColor(i, c); // Moderately bright green color.
		FastLED.show(); // This sends the updated pixel color to the hardware.
		delay(s); // Delay for a period of time (in milliseconds).
	}
}

void getrand() { // trying to make it //the goal is to get a random forecolor that is not white, then find the opposite of
	switch (random(0, 3)) {
		case 0:
		green = (random(0, Brange + 1) * 2);
		red = (random(0, Brange + 1) * 2);
		blue = 0;
		if (green == 0 || red == 0) { //prevents all black values
			blue = 1;
		};
		break;

		case 1:
		green = (random(0, Brange + 1) * 2);
		blue = (random(0, Brange + 1) * 2);
		red = 0; //32
		if (green == 0 || blue == 0) {
			red = 1;
		};
		break;

		case 2:
		red = (random(0, Brange + 1) * 2);
		blue = (random(0, Brange + 1) * 2);
		green = 0; //32
		if (red == 0 || blue == 0) {
			green = 1;
		};
		break;
	}
	Forecolor =  Color(green,red,blue);
}

void LedTest(int s){
	for(int x=0; x<numCols-1; x++){
		for(int y=0; y<numRows-1; y++){
			SetLEDxy(y,x,1);
			lmd.display();
			delay(s);
			SetLEDxy(y,x,0);
			lmd.display();
			delay(s);
		}
	}
	
	ColorWipe(0x0A0000,s);
	delay(300);
	ColorWipe(0x000A00,s);
	delay(300);
	ColorWipe(0x00000A,s);
	delay(300);
	ColorWipe(0,10);
	
	for(int x=numCols-1; x>=0; x--){
		for(int y=numRows-1; y>=0; y--){
			SetLEDxy(y,x,0);
			lmd.display();
			delay(s);
		}
	}
}
