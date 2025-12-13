#include <WiFi.h>
#include "esp_camera.h"

#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"
#define FLASH_LED_PIN 4

WiFiServer server(3333);

const int FWD_A = 12;
const int FWD_B = 15;
const int BCK_A = 13;
const int BCK_B = 14;


const char* ssid = "Everlong - The Foo Fighters";
const char* password = "12345678";

void setup() {
  pinMode(FWD_A, OUTPUT);
  pinMode(FWD_B, OUTPUT);
  pinMode(BCK_A, OUTPUT);
  pinMode(BCK_B, OUTPUT);

  pinMode(FLASH_LED_PIN, OUTPUT);

  Serial.begin(115200);
  delay(1000);

  startCamera();
  startAccessPoint();
  startServer();
}

void loop() {
  waitForClient();
}

void startAccessPoint(){
  Serial.println("booting ap...");
  WiFi.softAP(ssid, password);
  Serial.print("ap IP = ");
  Serial.println(WiFi.softAPIP());
}

void startServer(){
  server.begin();
  Serial.println("tcp started");
}

void waitForClient() {
  WiFiClient client = server.available();
  if (!client) return;

  Serial.println("controller connected [!]");

  while (client.connected()) {

    while (client.available()) {
      String cmd = client.readStringUntil('\n');
      cmd.trim();

      Serial.print("Received command: ");
      Serial.println(cmd);

      if (cmd == "sframe") sendFrame(client);
      if (cmd == "fwd") moveFWD();
      if (cmd == "bck") moveBCK();
      if (cmd == "right") turnRIGHT();
      if (cmd == "left") turnLEFT();
      if (cmd == "f_on") digitalWrite(FLASH_LED_PIN, HIGH);
      if (cmd == "f_off") digitalWrite(FLASH_LED_PIN, LOW);
      if (cmd == "stop") STOP();
      else Serial.println("CMD not recognized [!][!][!]");
    }

    delay(10);   // prevent watchdog reset
  }

  client.stop();
  Serial.println("controller disconnected [!][!]");
}

void STOP(){
  digitalWrite(FWD_A, LOW);
  digitalWrite(FWD_B, LOW);
  digitalWrite(BCK_A, LOW);
  digitalWrite(BCK_B, LOW);
}

void moveFWD(){
  digitalWrite(FWD_A, HIGH);
  digitalWrite(FWD_B, HIGH);
  digitalWrite(BCK_A, LOW);
  digitalWrite(BCK_B, LOW);
  delay(100);
  STOP();
}

void moveBCK(){
  digitalWrite(FWD_A, LOW);
  digitalWrite(FWD_B, LOW);
  digitalWrite(BCK_A, HIGH);
  digitalWrite(BCK_B, HIGH);
  delay(100);
  STOP();
}

void turnRIGHT(){
  digitalWrite(FWD_A, HIGH);
  digitalWrite(FWD_B, LOW);
  digitalWrite(BCK_A, LOW);
  digitalWrite(BCK_B, HIGH);
  delay(100); 
  STOP();

}

void turnLEFT(){
  digitalWrite(FWD_A, LOW);
  digitalWrite(FWD_B, HIGH);
  digitalWrite(BCK_A, HIGH);
  digitalWrite(BCK_B, LOW);
  delay(100); 
  STOP();
}

void sendFrame(WiFiClient &client) {
  camera_fb_t * fb = esp_camera_fb_get();
  if (!fb) {
    Serial.println("Camera capture failed");
    return;
  }

  // Send image size (4 bytes)
  uint32_t len = fb->len;
  client.write((uint8_t*)&len, sizeof(len));

  // Send JPEG raw bytes
  client.write(fb->buf, fb->len);

  esp_camera_fb_return(fb);

  Serial.println("Frame sent.");
}


void startCamera() {
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;

  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // resolution and quality
  config.frame_size = FRAMESIZE_VGA;
  config.jpeg_quality = 12;
  config.fb_count = 1;

  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed: %s\n", esp_err_to_name(err));
  }
}
