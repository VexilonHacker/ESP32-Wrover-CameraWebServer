#ifndef SETUP_H
#define SETUP_H


esp_err_t init_camera();
void init_wifi();
void startCameraServer();   // NOTE: startCameraServer function is from src/app_httpd.cpp

#endif


