#include <SPI.h>
#include <LoRa.h>
#include <LiquidCrystal_AIP31068_I2C.h>
LiquidCrystal_AIP31068_I2C lcd(0x3E,16,2);
String loRaMessage;
String temperature;
String humidity;
String HEART_RATE;
String SPO2;
String BODY_TEMP;
String LATTITUDE;
String LONGITUDE;
String EMERGENCY;
String readingID;

const int BUZZER=7;

#include <SoftwareSerial.h>
SoftwareSerial ser(4,5);              // RX, TX

String apiKey = "RRFR7C51UME4VRU4";    // Edit this API key according to your Account490PPI8R8MV4R0A2
String Host_Name = "SOLNETWORK";         // Edit Host_Name
String Password = "password"; 


void setup() {
Serial.begin(115200);
pinMode(BUZZER,OUTPUT);
//digitalWrite(BUZZER,HIGH);
lcd.init();
lcd.clear();
lcd.print(" LORA RECEIVER");
lcd.setCursor(0, 1);
lcd.print(" STARTING");
while (!Serial);
Serial.println("LoRa Receiver");
if (!LoRa.begin(433E6)) {
Serial.println("Starting LoRa failed!");
lcd.init();
lcd.clear();
lcd.print(" LORA RECEIVER");
lcd.setCursor(0, 1);
lcd.print(" LoRa failed!.....");
while (1);
}
lcd.clear();
lcd.print(" LORA ONLINE");
lcd.setCursor(0, 1);
lcd.print("CONNECTING WiFi..");
ser.begin(115200);                     // 
ser.println("AT+RST");               // Resetting ESP8266
delay(1000);
ser.println("AT+CWMODE=1");               // AS WIFI CLIENT
delay(1000);
                     
char inv ='"';

String cmd = "AT+CWJAP";

       cmd+= "=";

       cmd+= inv;

       cmd+= Host_Name;

       cmd+= inv;

       cmd+= ",";

       cmd+= inv;

       cmd+= Password;

       cmd+= inv;

ser.println(cmd);                    // Connecting ESP8266 to your WiFi Router
lcd.clear();
lcd.print("   WAITING FOR ");
lcd.setCursor(0, 1);
lcd.print("   LORA DATA..");
}


void loop() {

    int packetSize = LoRa.parsePacket();
  if (packetSize)
  {
    Serial.print("Lora packet received: ");
    while (LoRa.available())    // Read packet
  {
    String LoRaData = LoRa.readString();
    Serial.println(packetSize); 
    
   
    int pos1 = LoRaData.indexOf('/');   
    int pos2 = LoRaData.indexOf('&');
    int pos3 = LoRaData.indexOf('@');  
    int pos4 = LoRaData.indexOf('#');
    int pos5 = LoRaData.indexOf('%');
    int pos6 = LoRaData.indexOf('^');
    int pos7 = LoRaData.indexOf(']');
    int pos8 = LoRaData.indexOf('|');
    
    readingID = LoRaData.substring(0, pos1);                   // Get readingID
    temperature = LoRaData.substring(pos1 +1, pos2);           // Get temperature
    humidity = LoRaData.substring(pos2+1, pos3);
   HEART_RATE = LoRaData.substring(pos3+1,pos4); 
    SPO2=LoRaData.substring(pos4+1,pos5); 
    BODY_TEMP=LoRaData.substring(pos5+1,pos6);
    LATTITUDE= LoRaData.substring(pos6+1,pos7); 
 LONGITUDE=LoRaData.substring(pos7+1, pos8  ); 
EMERGENCY=LoRaData.substring(pos8+1,   LoRaData.length());

int x = EMERGENCY.toInt();  
if(x>0)
{ lcd.clear();
lcd.print("EMERGENCY ");
lcd.setCursor(0, 1);
lcd.print("REQUESTED");
digitalWrite(BUZZER,HIGH);
}
else
{digitalWrite(BUZZER,LOW);
}
  
   Serial.print("temperature- ");
   Serial.println(temperature);
   Serial.print("humidity- ");
   Serial.println(humidity);
   lcd.clear();
lcd.print("TEMPERATURE-");
lcd.print(temperature);
lcd.setCursor(0, 1);
lcd.print("HUMIDITY-");
lcd.print(humidity);

delay(2000);

   Serial.print("HEART RATE -"); 
   Serial.println(HEART_RATE); 
    Serial.print("SPO2"); 
  Serial.println(SPO2); 
     lcd.clear();
lcd.print("BODY_TEMP-");
lcd.print(BODY_TEMP);
lcd.setCursor(0, 1);
lcd.print("ES STATUS -");
lcd.print(EMERGENCY);

delay(2000);

 Serial.print(" LAT-"); 
Serial.println(LATTITUDE); 
Serial.print("LONGITUDE-"); 
Serial.println(LONGITUDE); 
lcd.clear();
lcd.print("LAT-");
lcd.print(LATTITUDE);
lcd.setCursor(0, 1);
lcd.print("LON-");
lcd.print(LONGITUDE);
delay(2000);

Serial.print("http://maps.google.com/maps?q=loc:");
Serial.println(LATTITUDE);
Serial.println(",");
Serial.println(LONGITUDE);

String state1=String(HEART_RATE);  
String state2=String(SPO2);
String state3=String(BODY_TEMP); 
String state4=String(temperature); 
String state5=String(humidity); 
String state6=String(LATTITUDE);  
String state7=String(LONGITUDE); // Converting them to string 
 String state8=String(EMERGENCY);



delay(1000);


 lcd.clear();
lcd.print("UPDATING..SERVER");
lcd.setCursor(0, 1);
lcd.print("PLEASE WAIT.....");


  String cmd = "AT+CIPSTART=\"TCP\",\"";          // Establishing TCP connection

  cmd += "184.106.153.149";                       // api.thingspeak.com

  cmd += "\",80";                                 // port 80

  ser.println(cmd);

  //Serial.println(cmd);


 if(ser.find("Error")){

    Serial.println("AT+CIPSTART error");

    return;

  }

String getStr = "GET /update?api_key=";         // prepare GET string

  getStr += apiKey;

getStr +="&field1=";
getStr += String(state1);                       // wl Data

getStr +="&field2=";
getStr += String(state2);

getStr +="&field3=";
getStr += String(state3);

getStr +="&field4=";
getStr += String(state4);

getStr +="&field5=";
getStr += String(state5);

getStr +="&field6=";
getStr += String(state6);

getStr +="&field7=";
getStr += String(state7);

getStr +="&field8=";
getStr += String(state8);


  getStr += "\r\n\r\n";

  cmd = "AT+CIPSEND=";

  cmd += String(getStr.length());                // Total Length of data

  ser.println(cmd);

  Serial.println(cmd);

 ser.print(getStr);

    Serial.print(getStr);
    


 delay(10000);

 

  
 lcd.clear();
lcd.print("   WAITING FOR ");
lcd.setCursor(0, 1);
lcd.print("   LORA DATA..");

 
}
}}