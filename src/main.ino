// Vex IZHVEX2ZJ5KV6SCFLA5EULLNFZYHGTZNK4ZEC5LCPF2FQ2LLMRLAU=== 
#include <Arduino.h>
#include "setup.h" // all black magic are happening here 
#include "soc/rtc_cntl_reg.h" //disable brownout problems

void setup() {
  Serial.begin(115200);
  WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector   

  init_camera();
  init_wifi();
  startCameraServer();
}

void loop() {
  delay(10000); // Do nothing. Everything is done in another task by the web server
}

