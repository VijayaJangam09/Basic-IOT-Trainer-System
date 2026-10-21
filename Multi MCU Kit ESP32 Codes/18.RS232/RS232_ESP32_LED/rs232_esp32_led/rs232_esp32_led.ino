#include <SoftwareSerial.h>
#include <string.h>
#include <stdio.h>
uint8_t recv_char;
char recv_str[20];
int i=0;

SoftwareSerial mySerial(16, 17); // RX of rs232 to ESP32 16, TX of rs232 to ESP32 17
#define LED 2
void setup()
{
  
  Serial.begin( 2400 );                   //Set the baund rate as 2400 for arduino serial 
  Serial.println("USB Serial is ready");
  mySerial.begin( 2400 );                 // set the baund rate for the SoftwareSerial port
  pinMode(LED, OUTPUT); 
  digitalWrite(LED,LOW);   
}

void loop()
{ 
  if ( mySerial.available() )
  {
    recv_char =  mySerial.read();
    if(recv_char == '\r'){
      recv_str[i] = '\0';
      if(!strcmp(recv_str, "ON")){
        digitalWrite(LED,HIGH);
        Serial.println("high");
      }
      if(!strcmp(recv_str, "OFF")){
        digitalWrite(LED,LOW);
        Serial.println("low");
      }
      Serial.println(recv_str);       // Write the serial from MAX3232 to Arduino serial 
      i=0;
      memset(recv_str, 0, sizeof(recv_str));
    }
    else{
		  if(recv_char == '\r' || recv_char == '\n'){
		} 
      else{
		    recv_str[i++] = recv_char;
		    }
    }
   
  }

  if ( Serial.available() )
  {
   recv_char =  Serial.read();
    if(recv_char == '\r'){
      recv_str[i] = '\0';
      mySerial.println(recv_str);       // Write the serial from MAX3232 to Arduino serial 
      i=0;
      memset(recv_str, 0, sizeof(recv_str));
    }
    else{
		  if(recv_char == '\r' || recv_char == '\n'){
		} 
      else{
		    recv_str[i++] = recv_char;
		    }
    }
     
  }
}