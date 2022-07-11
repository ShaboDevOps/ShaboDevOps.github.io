#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <Arduino_JSON.h>
#include <WiFiClient.h>
int input_reading1=A0;
int output1=5;
int output2=4;
int output3=0;
int output4=2;
int output5=14;
int output6=12;
int output7=13;
int output8=15;
char input;
double reading;
double currentLMT =0.0;
double stopVolt = 0.0;
double increment = 0.0;
bool isNew;

void setup() {
pinMode(input_reading1,INPUT);
pinMode(output1,OUTPUT);
pinMode(output2,OUTPUT);
pinMode(output3,OUTPUT);
pinMode(output4,OUTPUT);
pinMode(output5,OUTPUT);
pinMode(output6,OUTPUT);
pinMode(output7,OUTPUT);
pinMode(output8,OUTPUT);
Serial.begin(115200); 
WiFi.begin("hawa","hawa1717");
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  calc();
}
void calc(){
  double volts[8] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
  double currents[8] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};
digitalWrite(output1,HIGH);
reading=analogRead(input_reading1);
float data=((reading/1024)*5);
Serial.print("Voltage 1: ");
Serial.print(data);
Serial.print("V\t");
Serial.print("Current : ");
Serial.print(calcCurrent(data));
Serial.println("A");
volts[0] = data;
currents[0] = calcCurrent(data);
delay(3000);


digitalWrite(output2,HIGH);
reading=analogRead(input_reading1);
float data1=((reading/1024)*5);
Serial.print("Voltage 2: ");
Serial.print(data1);
Serial.print("V\t");
Serial.print("Current : ");
Serial.print(calcCurrent(data1));
Serial.println("A");
digitalWrite(output2,LOW);
volts[1] = data1;
currents[1] = calcCurrent(data1);
delay(3000);


digitalWrite(output3,HIGH);
reading=analogRead(input_reading1);
float data2=((reading/1024)*5);
Serial.print("Voltage 3: ");
Serial.print(data2);
Serial.print("V\t");
Serial.print("Current : ");
Serial.print(calcCurrent(data2));
Serial.println("A");
digitalWrite(output3,LOW);
volts[2] = data2;
currents[2] = calcCurrent(data2);
delay(3000);

digitalWrite(output4,HIGH);
reading=analogRead(input_reading1);
float data3=((reading/1024)*5);
Serial.print("Voltage 4: ");
Serial.print(data3);
Serial.print("V\t");
Serial.print("Current : ");
Serial.print(calcCurrent(data3));
Serial.println("A");
digitalWrite(output4,LOW);
volts[3] = data3;
currents[3] = calcCurrent(data3);
delay(3000);


digitalWrite(output5,HIGH);
reading=analogRead(input_reading1);
float data4=((reading/1024)*5);
Serial.print("Voltage 5: ");
Serial.print(data4);
Serial.print("V\t");
Serial.print("Current : ");
Serial.print(calcCurrent(data4));
Serial.println("A");
digitalWrite(output5,LOW);
volts[4] = data4;
currents[4] = calcCurrent(data4);
delay(3000);


digitalWrite(output6,HIGH);
reading=analogRead(input_reading1);
float data5=((reading/1024)*5);
Serial.print("Voltage 6: ");
Serial.print(data5);
Serial.print("V\t");
Serial.print("Current : ");
Serial.print(calcCurrent(data5));
Serial.println("A");
digitalWrite(output6,LOW);
volts[5] = data5;
currents[5] = calcCurrent(data5);
delay(3000);


digitalWrite(output7,HIGH);
reading=analogRead(input_reading1);
float data6=((reading/1024)*5);
Serial.print("Voltage 7: ");
Serial.print(data6);
Serial.print("V\t");
Serial.print("Current : ");
Serial.print(calcCurrent(data6));
Serial.println("A");
digitalWrite(output7,LOW);
volts[6] = data6;
currents[6] = calcCurrent(data6);
delay(3000);


digitalWrite(output8,HIGH);
reading=analogRead(input_reading1);
float data7=((reading/1024)*5);
Serial.print("Voltage 8: ");
Serial.print(data7);
Serial.print("V\t");
Serial.print("Current : ");
Serial.print(calcCurrent(data7));
Serial.println("A");
digitalWrite(output8,LOW);
volts[7] = data7;
currents[7] = calcCurrent(data7); 
 postResult(volts, currents);
}


void postResult(double volts[8],double currents[8]){
 
  String payload ="[{\"volt\":\""+String(volts[0])+"\",\"current\":\""+String(currents[0])+"\"},{\"volt\":\""+String(volts[1])+"\",\"current\":\""+String(currents[1])+"\"},{\"volt\":\""+String(volts[2])+"\",\"current\":\""+String(currents[2])+"\"},{\"volt\":\""+String(volts[3])+"\",\"current\":\""+String(currents[3])+"\"},{\"volt\":\""+String(volts[4])+"\",\"current\":\""+String(currents[4])+"\"},{\"volt\":\""+String(volts[5])+"\",\"current\":\""+String(currents[5])+"\"},{\"volt\":\""+String(volts[6])+"\",\"current\":\""+String(currents[6])+"\"},{\"volt\":\""+String(volts[7])+"\",\"current\":\""+String(currents[7])+"\"}]";
  String url = "http://50.116.49.8:8885/output/add";
  if(WiFi.status()== WL_CONNECTED){
      WiFiClient client;
      HTTPClient http;
      
      // Your Domain name with URL path or IP address with path
      http.begin(client, url);
      
      // Specify content-type header
      http.addHeader("Content-Type", "application/json");
      
      // Send HTTP POST request
      int httpResponseCode = http.POST(payload);
      Serial.print("\tPosting Data : ");
      Serial.println(httpResponseCode);
      http.end(); 
  }
}

double calcCurrent(double volt){ 
  return pow(2.718,(volt/0.0259));
}
