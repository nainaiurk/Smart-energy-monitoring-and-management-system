#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define AUTH_TOKEN "your auth token"
const char* resource = "your iftt server url";
const char* server = "maker.ifttt.com";
char ssid[] = "your wifi name";
char pass[] = "wifi pass";
#define voltage1 voltage_pin
#define current1 current_pin
#define relay1 relay_pin
#define ir ir_pin
#define buzzer buzzer_pin

bool led_set[2];
long timer_start_set[2] = {0xFFFF, 0xFFFF};
long timer_stop_set[2] = {0xFFFF, 0xFFFF};
unsigned char weekday_set[2];

long rtc_sec;
unsigned char day_of_week;

bool led_status[2];
bool update_blynk_status[2];
bool led_timer_on_set[2];


float amps;
bool prevVal;
bool currentVal;

uint32_t lastSampleTime = 0;
uint32_t lastPulseTime = 0;
int pulses = 0;
int volt, rpm;
double curnt;
uint32_t m;

void setup() {
  pinMode(voltage1, INPUT);
  pinMode(current1, INPUT);
  pinMode(relay1, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ir, INPUT);
  Blynk.begin(AUTH_TOKEN, ssid, pass);
  timer.setInterval(10000L, checkTime);
  Serial.begin(115200);
}

void loop() {
  Blynk.run();
  volt = voltage_measure();
  techometer();
  curnt = read_Amps();
  if (millis() - m > 1000) {
    Blynk.virtualWrite(V16, volt);
    Blynk.virtualWrite(V17, curnt);
    Blynk.virtualWrite(V6, rpm);
    Blynk.virtualWrite(V5, curnt * volt);
    // Serial.println(analogRead(34));
    // makeIFTTTRequest(volt, curnt, rpm);
  }
}

BLYNK_WRITE(V0) {
  int v0Pin = param.asInt();
  digitalWrite(relay1, v0Pin);
}
BLYNK_WRITE(V10) {
  int v10 = param.asInt();
  digitalWrite(buzzer, v10);
}