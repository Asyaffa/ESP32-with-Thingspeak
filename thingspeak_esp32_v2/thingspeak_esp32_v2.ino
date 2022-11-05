#include <WiFi.h>
#include "ThingSpeak.h"
#include "DHT.h"

const char* ssid =      "**********";
const char* password =  "**********";

WiFiClient  client;

unsigned long myChannelNumber_2 = *;
unsigned long myChannelNumber_3 = *;
//Channel Number on My Channels List

const char * myWriteAPIKey_2 = "****************";
const char * myWriteAPIKey_3 = "****************";

unsigned long lastTimeTemperature = 0;
unsigned long timerDelayTemperature = 15000;

unsigned long lastTimeHumidity = 0;
unsigned long timerDelayHumidity = 20000;

unsigned long lastTimeDouble = 0;
unsigned long timerDelayDouble = 20000;

#define DHTPIN 32
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void initWiFi()
{
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void setup()
{
  Serial.begin(115200);

  dht.begin();

  initWiFi();

  ThingSpeak.begin(client);
}

void loop()
{
  /*
  if ((millis() - lastTimeHumidity) > timerDelayHumidity)
  {

    float h = dht.readHumidity();
    Serial.print("Humidity: ");
    Serial.print(h);

    ThingSpeak.writeField (myChannelNumber_2, 1, h, myWriteAPIKey_2);

    lastTimeHumidity = millis();
  }

  if ((millis() - lastTimeTemperature) > timerDelayTemperature)
  {

    float c = dht.readTemperature();
    Serial.print("\tTemperature: ");
    Serial.println(c);

    ThingSpeak.writeField(myChannelNumber_2, 2, c, myWriteAPIKey_2);

    lastTimeTemperature = millis();
  }
  */
  
  if ((millis() - lastTimeDouble) > timerDelayDouble)
  {
    float h = dht.readHumidity();
    Serial.print("Humidity: ");
    Serial.print(h);
    
    float c = dht.readTemperature();
    Serial.print("\tTemperature: ");
    Serial.println(c);

    ThingSpeak.setField(1, h);
    ThingSpeak.setField(2, c);

    ThingSpeak.writeFields(myChannelNumber_3, myWriteAPIKey_3);

    lastTimeDouble = millis();
  }
 
}
