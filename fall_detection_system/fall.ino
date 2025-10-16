#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>


const char* ssid = "Arpit";// Enter your WIFI SSID
const char* password = "Arpit1921"; // Enter your WIFI Password


#define BOTtoken "7180574089:AAEErDsbF5GIH3zFSbQHpogF68cVWCpsWts" // Enter the bottoken you got from botfather
#define CHAT_ID "1325621328" // Enter your chatID you got from chatid bot


X509List cert(TELEGRAM_CERTIFICATE_ROOT);
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

Adafruit_MPU6050 mpu;

int const buzzPin=D5;
int const led=D7;

void setup() {
  Serial.begin(115200);
Serial.begin(115200);
  configTime(0, 0, "pool.ntp.org");      
  client.setTrustAnchors(&cert);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int a = 0;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
    a++;
  }
  while (!Serial)
    delay(10); // wait for native usb

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);

  Serial.println("");
  delay(100);

  pinMode(buzzPin,OUTPUT);
  pinMode(led,OUTPUT);

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  bot.sendMessage(CHAT_ID, "Wifi Connected!", "");
  bot.sendMessage(CHAT_ID, "System has Started!!", "");
 
}

void loop() {
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  Serial.print("Accel X: "); Serial.print(a.acceleration.x); Serial.print(", ");
  Serial.print("Accel Y: "); Serial.print(a.acceleration.y); Serial.print(", ");
  Serial.print("Accel Z: "); Serial.print(a.acceleration.z); Serial.print(" m/s^2");
  Serial.println("  ");

  // Simple fall detection algorithm based on acceleration threshold
  float fall_threshold = 1.5; // Adjust the threshold based on your requirements
  if (a.acceleration.z > fall_threshold) {
    Serial.println("Fall detected!");
    bot.sendMessage(CHAT_ID, "ALERT! FALL DETECTED!!", "");
    digitalWrite(buzzPin,HIGH);
    digitalWrite(led,HIGH);
    delay(1500);
    digitalWrite(buzzPin,LOW);
    digitalWrite(led,LOW);
  }
  

  
delay(500);
}