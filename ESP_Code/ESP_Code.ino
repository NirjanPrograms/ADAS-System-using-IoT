#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <ESP8266WiFi.h>
#include "Arduino.h"
#include <EMailSender.h>

TinyGPSPlus gps;
SoftwareSerial SerialGPS(4, 5); 

const char* ssid = "Galaxy M21"; // provide hotspot name
const char* password = "11110000"; // provide hotspot password

float Latitude , Longitude;
int year , month , date, hour , minute , second;
String DateString, TimeString, LatitudeString, LongitudeString;
int flag=0;
String lati="0", lon="0";

WiFiServer server(80);

IPAddress ip = WiFi.localIP();

EMailSender emailSend("abc@gmail.com","fwsi czhc zbfi rykx");//"<YOUR SENDER EMAIL ADDRESS>", "<YOUR-SENDER-PASSWORD>xicz yzoe fwjs iycp"

void setup()
{
  Serial.begin(9600);
  SerialGPS.begin(9600);
  Serial.println();
  Serial.print("Connecting");
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
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
      gps_Connection();
      if(flag==0){
        lati = LatitudeString;
        lon = LongitudeString;
        Email_Sent();
        flag=1;
        delay(3000);
      }
      if(lati!= LatitudeString || lon!= LongitudeString){
        flag=0;
      }
    }
  }
  gps_Connection();
}

void gps_Connection()
{
//  Serial.println(WiFi.localIP());
  while (SerialGPS.available() > 0)
    if (gps.encode(SerialGPS.read()))
    {
      if (gps.location.isValid())
      {
        Latitude = gps.location.lat();
        LatitudeString = String(Latitude , 6);
        Longitude = gps.location.lng();
        LongitudeString = String(Longitude , 6);
      }

      if (gps.date.isValid())
      {
        DateString = "";
        date = gps.date.day();
        month = gps.date.month();
        year = gps.date.year();

        if (date < 10)
        DateString = '0';
        DateString += String(date);

        DateString += " / ";

        if (month < 10)
        DateString += '0';
        DateString += String(month);
        DateString += " / ";

        if (year < 10)
        DateString += '0';
        DateString += String(year);
      }

      if (gps.time.isValid())
      {
        TimeString = "";
        hour = gps.time.hour()+ 5; //adjust UTC
        minute = gps.time.minute();
        second = gps.time.second();
    
        if (hour < 10)
        TimeString = '0';
        TimeString += String(hour);
        TimeString += " : ";

        if (minute < 10)
        TimeString += '0';
        TimeString += String(minute);
        TimeString += " : ";

        if (second < 10)
        TimeString += '0';
        TimeString += String(second);
      }

    }
  WiFiClient client = server.available();
  if (!client)
  {
    return;
  }

  //Response
  String s = "<!DOCTYPE html><html><head><title>NEO-6M GPS Readings</title>";
s += "<style>table, th, td {border: 3px solid rgb(0, 137, 164); font-size: 18px; font-family: sans-serif;}";
s += "body {background-color: rgb(255, 228, 181); font-family: sans-serif;}";
s += "table {box-shadow: 0px 0px 10px 5px rgb(95, 158, 160);}";
s += "tr {background-color: #7FFFD4;}</style></head>";
s += "<body><h1 style='text-align: center; font-size: 300%;'>Implementation of ADAS System Using IoT</h1>";
s += "<h2 style='font-size: 200%; text-align: center; text-decoration: underline; font-family: sans-serif;'>NEO-6M GPS Readings</h2>";
s += "<p style='font-size: 150%; text-align: center;'><b>Location Details</b></p>";
s += "<table style='margin: auto; width: 50%;'><tr><th>Latitude</th><td style='text-align: center;'>";
s += LatitudeString;
s += "</td></tr><tr><th>Longitude</th><td style='text-align: center;'>";
s += LongitudeString;
s += "</td></tr><tr><th>Date</th><td style='text-align: center;'>";
s += DateString;
s += "</td></tr><tr><th>Time</th><td style='text-align: center;'>";
s += TimeString;
s += "</td></tr></table>";
//s += "</td></tr></table><p style='text-align: center;'><a style='color: rgb(206, 48, 48); font-size: 125%;' href='http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=" + LatitudeString + "+" + LongitudeString +"' target='_top'>Click here</a> to open the location in Google Maps.</p>"; 
  
  if (gps.location.isValid())
  {
    s += "<p align=center><a style=""color:RED;font-size:125%;"" href=""http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
    s += LatitudeString;
    s += "+";
    s += LongitudeString;
    s += """ target=""_top"">Click here</a> to open the location in Google Maps.</p>";
  }
  s += "<div style='text-align: center;'><h2 style='text-decoration: underline;'>Project Members</h2>";
  s += "<ul style='list-style-type: none; font-family: sans-serif; font-size: 20px; padding: 0;'>";
  s += "<li>Partha Pratim Goswami</li><li>Shantanu Dey</li><li>Niladri De</li><li>Nilabha Biswas</li><li>Nirjan Pal</li></ul></div></body></html>";
  
  s += "</body> </html> \n";

  client.print(s);
  delay(100);

}

String get_Link(String lati, String lon){
  String s = "Location:\n";
  s += "\n Latitude: ";
  s += lati;
  s += "\n Longitude: ";
  s += lon; 
  s += "\n Click the link below to see the accident location:";
  s += "\n http://maps.google.com/maps?&z=15&mrt=yp&t=k&q=";
  s += lati;
  s += "+";
  s += lon;
  return s;
}

void Email_Sent(){
  EMailSender::EMailMessage message;
    message.subject = "Immediate Attention Required! Car Accident Notification and Location Details";
    message.message = get_Link(LatitudeString, LongitudeString);

    EMailSender::Response resp = emailSend.send("xyz@gmail.com", message);//<RECIEVERS EMAIL ADDRESS>

    Serial.println("Sending status: ");
    Serial.println(resp.status);
    Serial.println(resp.code);
    Serial.println(resp.desc);
}
