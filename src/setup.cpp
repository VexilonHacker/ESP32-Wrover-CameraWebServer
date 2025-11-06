#include "config.h"
#include "esp_camera.h"
#include <WiFi.h>
#include <Arduino.h>
#include <ESPmDNS.h>

esp_err_t init_camera() {
    camera_config_t config;
    // Pins CAM Setup
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
    config.pin_sccb_sda = SIOD_GPIO_NUM;
    config.pin_sccb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;

    // CAM configs
    config.xclk_freq_hz = 40000000;
    config.pixel_format = PIXFORMAT_JPEG;  // for streaming
    //config.pixel_format = PIXFORMAT_RGB565; // for face detection / recognition
    config.grab_mode = CAMERA_GRAB_WHEN_EMPTY;
    config.jpeg_quality = 12;
    config.fb_count = 1;

    if (psramFound()) {
        Serial.println("LET GOOOOOOOO PSRAM WAS FOUND = Enabling high-performance mode");
        config.frame_size = FRAMESIZE_SVGA; 
        config.jpeg_quality = 10;           
        config.fb_count = 2;                
        config.fb_location = CAMERA_FB_IN_PSRAM;

    } else {
        Serial.println("NO PSRAM NO BI..... = Using low-memory settings ;]");
        config.frame_size = FRAMESIZE_VGA;
        config.jpeg_quality = 12;
        config.fb_count = 1;
        config.fb_location = CAMERA_FB_IN_DRAM;
    }


    esp_err_t err = esp_camera_init(&config);
    if (err != ESP_OK) {
        Serial.printf("camera init FAIL: 0x%x", err);
        return err;
    }

    sensor_t * s = esp_camera_sensor_get();
    s->set_framesize(s, FRAMESIZE_VGA);
    s->set_vflip(s, 1); // Enable vflip
    
    Serial.println("camera init OK");
    return ESP_OK;
};

void init_wifi() {
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.printf("Connecting to WiFi %s\n", WIFI_SSID);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWiFi connected ;]");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    String msg = "Check \"http://" + WiFi.localIP().toString() + "\" To use ESP32-Wrover CAM";
    Serial.println(msg);

    if (MDNS.begin(MDNS_NAME)) { 
        String name = MDNS_NAME;
        name.toLowerCase();
        Serial.printf("or check \"http://%s.local\" To use ESP32-Wrover cam\n", name);
    } else {
        Serial.println("* Error setting up MDNS responder");
    }

}


