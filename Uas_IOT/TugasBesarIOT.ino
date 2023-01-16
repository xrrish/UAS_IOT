#include "DHTesp.h"
#include <FirebaseESP32.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "ThingSpeak.h"

const char apiKey[] = "EW0ZI7MNZLWDVUZF"; //String apiKey = "EB8O249TM782T9TV";
long myChannelNumber = 1999833;

#define FIREBASE_HOST "https://harisiot-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "mQazhMUWq4Ozr1guRuUUZZZeqn3sXezG2r9EAJ3C"
#define WIFI_SSID "Wokwi-GUEST"
#define WIFI_PASSWORD ""
#define relay 26
const int DHTPIN = 27;

WiFiClient client;
DHTesp dhtSensor;
FirebaseData firebaseData;

String path = "/Node1";

void setup() {
  Serial.begin(115200);
  ThingSpeak.begin(client);
  dhtSensor.setup(DHTPIN, DHTesp::DHT22);
  initWifi();

}

void loop() {
delay(500);
  TempAndHumidity  data = dhtSensor.getTempAndHumidity();
  Serial.println("Temp: " + String(data.temperature, 2) + "°C");
  Serial.println("Humidity: " + String(data.humidity, 1) + "%");
  Serial.println("---");
  String t = String(data.temperature, 2);
  String h = String(data.humidity, 1);

Firebase.setString(firebaseData, path + "/value_tmp",  String(data.temperature));
Firebase.setString(firebaseData, path + "/value_hmn",  String(data.humidity));

if ("api.thingspeak.com")   //   "184.106.153.149" or api.thingspeak.com
    {                        
      // Serial.println("Temperature: " + (String) data.temperature, 2);
      // Serial.println("Humidity: " + (String) data.humidity, 1);
      
      ThingSpeak.writeField(myChannelNumber, 1,  String(data.humidity), apiKey);
      ThingSpeak.writeField(myChannelNumber, 2,  String(data.temperature), apiKey);
    }

}

void initWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

  
