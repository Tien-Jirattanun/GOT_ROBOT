
// Blynk setup
#define BLYNK_TEMPLATE_ID "TMPL6cJ0nOn2C"
#define BLYNK_TEMPLATE_NAME "car"
#define BLYNK_AUTH_TOKEN "Vz44YVYykTti6sow4bl5lDKSHB_Anmv8"

// Lib include
#include <Arduino.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <DHT_U.h>
#include <TridentTD_LineNotify.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Line setting
// #define LINE_TOKEN "lTGllJhxINoZlRWzoNr8nKKLf5F6kRaCWM6ZfIu6RbE"

// Motor pins
#define IN_ONE   16
#define IN_TWO   5
#define IN_THREE 4
#define IN_FOUR  0

#define DHT_PIN 12
#define DHTTYPE DHT11

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Tien_iphone";
char pass[] = "0970530641";

DHT dht(DHT_PIN, DHTTYPE);
BlynkTimer timer;

float humid = 0.0;
float temp = 0.0;

void dhtData()
{
    humid = dht.readHumidity();
    temp = dht.readTemperature();

    Blynk.virtualWrite(V5, temp);
    Blynk.virtualWrite(V6, humid);
}

BLYNK_WRITE(V1)
{ // move forward
    digitalWrite(IN_ONE, param.asInt());
    digitalWrite(IN_THREE, param.asInt());
}

BLYNK_WRITE(V2)
{ // move backward
    digitalWrite(IN_TWO, param.asInt());
    digitalWrite(IN_FOUR, param.asInt());
}

BLYNK_WRITE(V3)
{ // turn left
    digitalWrite(IN_THREE, param.asInt());
}

BLYNK_WRITE(V4)
{ // turn right
    digitalWrite(IN_ONE, param.asInt());
}

void setup()
{

    // DHT begin
    dht.begin();

    // Line
    // Serial.println(LINE.getVersion());

    // WiFi.begin(ssid, pass);
    // Serial.printf("WiFi connecting to %s\n", pass);
    // while (WiFi.status() != WL_CONNECTED)
    // {
    //     Serial.print(".");
    //     delay(400);
    // }
    // Serial.printf("\nWiFi connected\nIP : ");
    // Serial.println(WiFi.localIP());

    // // กำหนด Line Token
    // LINE.setToken(LINE_TOKEN);

    // // ตัวอย่างส่งข้อความ
    // LINE.notify("ครูก็อทสุดหล่อ");

    // Pin Mode
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(IN_ONE, OUTPUT);
    pinMode(IN_TWO, OUTPUT);
    pinMode(IN_THREE, OUTPUT);
    pinMode(IN_FOUR, OUTPUT);

    // Setting LED to HIGH
    digitalWrite(LED_BUILTIN, HIGH);

    // Serial begin
    Serial.begin(9600);

    // start Blynk
    Blynk.begin(auth, ssid, pass);
    timer.setInterval(1000L, dhtData);
}

void loop()
{
    Blynk.run();
    timer.run();
}