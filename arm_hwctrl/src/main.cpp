#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "ESP32_Servo.h"
#include "esp_log.h"

#define BLINK_LED GPIO_NUM_23
#define SERVO_PIN GPIO_NUM_5

static const char *INIT = "initializing";

// blink task
void tBlink(void * pvParameters){
    pinMode(BLINK_LED, OUTPUT);
    while(1){
        gpio_set_level(BLINK_LED, 1);
        vTaskDelay(1000/portTICK_PERIOD_MS);
        gpio_set_level(BLINK_LED, 0);
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

// servo task
void tServo(void * pvParametersid)
{
    Servo servo;
    servo.attach(SERVO_PIN, 500,2400);
    servo.write(0);

    int angle = 0;
    int step = 5;

    while (1) {
        servo.write(angle);
        vTaskDelay(pdMS_TO_TICKS(500));
        if ((angle + step) > 60 || (angle + step) < -60) {
            step *= -1;
        }
        angle += step;
    }
}

void setup() {
  static uint8_t blink_param;
  static uint8_t servo_param;
  TaskHandle_t blink_handle = NULL;
  TaskHandle_t servo_handle = NULL;

  ESP_LOGI(INIT, "starting blink task ...");
  BaseType_t blink_status = xTaskCreate(&tBlink, "blink task", 2048, &blink_param, 5, &blink_handle);
  if(blink_status != pdPASS){vTaskDelete(blink_handle);}
  ESP_LOGI(INIT, "starting servo task ...");
  BaseType_t servo_status = xTaskCreate(&tServo, "servo task", 3062, &servo_param, 4, &servo_handle);
  if(servo_status != pdPASS){vTaskDelete(servo_handle);}      

  ESP_LOGI(INIT, "**end of initialization**");
}

void loop() {
  // main
}
