1#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

#define DHTPIN 6 
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE); 

#include <LiquidCrystal_AIP31068_I2C.h>
LiquidCrystal_AIP31068_I2C lcd(0x3E,16,2);

#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

 #include <VirtualWire.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>
SoftwareSerial serial_connection(3, 4);    
TinyGPS gps; 

float latitude;
float longitude;
int counter = 0;
const int HR=A1;
const int SPO2=A2;

const int ESP=5;
String LoRaMessage;

char c;
   float flat, flon;
    unsigned long age;

int ES;

void setup() {
Serial.begin(9600);
delay(2000);
c = Serial.read();
    Serial.println(c); 
    delay(2000);
serial_connection.begin(9600);
mlx.begin();
lcd.init();
lcd.clear();
lcd.print(" LORA TRANSMITTER");
lcd.setCursor(0, 1);
lcd.print(" STARTING");

while (!Serial);
Serial.println("LoRa Sender");
lcd.clear();
lcd.print(" LORA TRANSMITTER");
lcd.setCursor(0, 1);
lcd.print("LORA ONLINE....");

if (!LoRa.begin(433E6)) {
Serial.println("Starting LoRa failed!");
lcd.clear();
lcd.print(" LORA TRANSMITTER");
lcd.setCursor(0, 1);
lcd.print(" LoRa failed! ");
while (1);
}
LoRa.setTxPower(20);

dht.begin();
pinMode(HR,INPUT);  
pinMode(SPO2,INPUT_PULLUP); 
pinMode(ESP,INPUT_PULLUP);
delay(1000);
}


void loop() {

 

  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;
 
  // For one second we parse GPS data and report some key values
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (serial_connection.available())
    {
      char c =serial_connection.read();
      Serial.print(c);
      if (gps.encode(c)) 
        newData = true;  
    }
  }
 
  if (newData)      //If newData is true
  {
 
    gps.f_get_position(&flat, &flon, &age);  
    delay(200); 
    
   Serial.print("Latitude = ");
   Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
  
    
    delay(1000);
    Serial.print(" Longitude = ");
     Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    
    delay(1000);
    
   
 
  }

int humidity= dht.readHumidity();
int temperature = dht.readTemperature();
Serial.println("temperature");
Serial.println(temperature);
Serial.println("humidity");
Serial.println(humidity);
lcd.clear();
lcd.print("TEMPERATURE= ");
lcd.print(temperature);
lcd.print("*C");
lcd.setCursor(0, 1);
lcd.print("HUMIDITY= ");
lcd.print(humidity);
lcd.print("%");
delay(500);
 int  HEART_RATE=analogRead(HR);
 HEART_RATE= map(HEART_RATE, 0,1023, 0, 200);
 Serial.println("HEART_RATE"); 
 Serial.println(HEART_RATE); 
int SP2=analogRead(SPO2);
 SP2= map(SP2,0,1023, 0, 100); 
 Serial.println("SP02- "); 
  Serial.println(SP2);

lcd.clear();
lcd.print("HEART RATE= ");
lcd.print(HEART_RATE);
lcd.setCursor(0, 1);
lcd.print("SPO2=");
lcd.print(SP2);
delay(500);

delay(500);
Serial.println("READING TEMP");
Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()); Serial.println("*C");
int t=mlx.readObjectTempC();
lcd.clear();
lcd.print("YOUR TEMP - ");
// Or setting the cursor in the desired position.
lcd.print(mlx.readObjectTempC());
lcd.print("*C");
lcd.setCursor(0, 1);
delay(1000); 
 int e=digitalRead(ESP);
if(e==LOW)
{ES=1;
lcd.setCursor(0, 1);
lcd.print("EMRERGENCY ON");
}
else
{ES=0;
lcd.setCursor(0, 1);
lcd.print("EMRERGENCY OFF");}
delay(1000);
lcd.clear();
lcd.print("LAT-");
lcd.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
lcd.setCursor(0, 1);
lcd.print("LON-");
lcd.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
delay(1000); 


lcd.clear();
lcd.print("SENDING DATA....");
lcd.setCursor(0, 1);
lcd.print(counter);
// send packet



LoRaMessage = String(counter) + "/" + String(temperature) + "&" + String(humidity)+
"@" + String(HEART_RATE) + "#" + String(SP2)+ "%" + String(t)+ "^" + String(flat, 6)+ "]" + String(flon, 6)+ "|" + String(ES);

LoRa.beginPacket();
LoRa.print(LoRaMessage);
  

counter++;
LoRa.endPacket();
counter++;
delay(3000);

}