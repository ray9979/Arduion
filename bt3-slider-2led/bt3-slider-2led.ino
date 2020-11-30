
#include "BluetoothSerial.h"

#define R_Pin 32
#define G_Pin 17
#define B_Pin 21

const int RedChannel = 0;
const int GreenChannel = 1;
const int BlueChannel = 2;

BluetoothSerial SerialBT;
String mystring,val,Color;
String QRcode[4] = {"a","b","c","d"};
int Rval,Gval,Bval = 0;
int LEDtable[3][3] = {{123,211,56},{67,133,211},{167,91,189},{167,91,189}};

void setup() {
	SerialBT.begin("ESP32");
	Serial.begin(9600);
	//mystring = "R125";
	ledcSetup(RedChannel,5000,8);
	ledcSetup(GreenChannel,5000,8);
	ledcSetup(BlueChannel,5000,8);
	ledcAttachPin(R_Pin,RedChannel);
	ledcAttachPin(G_Pin,GreenChannel);
	ledcAttachPin(B_Pin,BlueChannel);
}
 
void loop() {

	while (SerialBT.available())         // Read while there is data in the buffer
	{
		mystring = SerialBT.readString();
    if(mystring.substring(0,1) != "C"){
		  Serial.println(mystring);
      //Serial.println(mystring.substring(0,1));
		  Color = mystring.substring(0,1);
     
      int Rn,Gn,Bn = 0;
      for(int i = 0;i <= mystring.length();i++){
        if(mystring.substring(i,i+1) == "G")
        Rn = i - 1;
        if(mystring.substring(i,i+1) == "B"){
          Gn = i - Rn - 2;
          Bn =  mystring.length() - i - 1;
        }
      }
      Rval = mystring.substring(1,Rn+1).toInt();
      Gval = mystring.substring(Rn+2,Rn+Gn+3).toInt();
      Bval = mystring.substring(Rn+Gn+3).toInt();
      showLED(Rval,Gval,Bval);
   }
   else{
      show(mystring.substring(1,2));
   }
   }
   Serial.print(Rval);
   Serial.print("\t");
   Serial.print(Gval);
   Serial.print("\t");
   Serial.print(Bval);
   Serial.println("\t");
}


void showLED(int R,int G, int B)
{
		ledcWrite(RedChannel,R);
		ledcWrite(GreenChannel,G);
		ledcWrite(BlueChannel,B);

}
void show(String type){
	for(int i = 0; i < 4;i++){
		if (type == QRcode[i]){
			ledcWrite(RedChannel,LEDtable[i][0]);
			ledcWrite(GreenChannel,LEDtable[i][1]);
			ledcWrite(BlueChannel,LEDtable[i][2]);
		}
	
	}
	
}
