#include <ESP8266WiFi.h>
#include "Arduino.h"
#include <EMailSender.h>

const char* ssid = "Galaxy M21"; // provide hotspot name
const char* password = "11110000"; // provide hotspot password

WiFiServer server(80);
IPAddress ip = WiFi.localIP();
EMailSender emailSend("abc@gmail.com","fwsi czhc zbfi rykx");//"<YOUR SENDER EMAIL ADDRESS>", "<YOUR-SENDER-PASSWORD>fwsi czhc zbfi rykx"

void setup()
{
  Serial.begin(9600);
  Serial.print("Connecting");
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  if (Serial.available()>0) {
    char receivedData[50]; 
    size_t length = Serial.readBytesUntil('\n', receivedData, sizeof(receivedData)); 
    length--;
    receivedData[length] = '\0'; 
    
    Serial.print("Received: "); 
    Serial.println(receivedData); 

    if (strcmp(receivedData, "Vibration detected!") == 0) {
      Serial.print("Arduino sent: ");
      Serial.println(receivedData);
      Email_Sent();
    }
  }
}

void Email_Sent(){
  EMailSender::EMailMessage message;
    message.subject = "Write the Subject";
    message.message = "Write the message";
    EMailSender::Response resp = emailSend.send("xyz@gmail.com", message);//<RECIEVERS EMAIL ADDRESS>

    Serial.println("Sending status: ");
    Serial.println(resp.status);
    Serial.println(resp.code);
    Serial.println(resp.desc);
}
