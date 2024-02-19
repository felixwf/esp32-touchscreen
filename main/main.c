
#include "taskdisplay.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#define ESP_CHECK(x) \
    if (x != ESP_OK)  \
    {                 \
        return;       \
    }

void taskdisplay_start(void)
{
    xTaskCreate(vTaskDisplay, "vTaskDisplay", 4096, NULL, 5, NULL);
}

esp_err_t esp_check_stack(void)
{
    uint32_t stack = uxTaskGetStackHighWaterMark(NULL);
    if (stack < 100)
    {
        ESP_LOGE("esp_check_stack", "Stack is low");
        return ESP_FAIL;
    }
    return ESP_OK;
}

esp_err_t esp_check_heap(void)
{
    uint32_t heap = esp_get_free_heap_size();
    if (heap < 100)
    {
        ESP_LOGE("esp_check_heap", "Heap is low");
        return ESP_FAIL;
    }
    return ESP_OK;
}
esp_err_t esp_check(void)
{
    esp_err_t ret = ESP_OK;
    ret = esp_check_stack();
    if (ret != ESP_OK)
    {
        ESP_LOGE("esp_check", "Stack check failed");
        return ret;
    }
    ret = esp_check_heap();
    if (ret != ESP_OK)
    {
        ESP_LOGE("esp_check", "Heap check failed");
        return ret;
    }
    return ret;
}


void app_main(void)
{
    ESP_CHECK(esp_check());
    ESP_LOGI("main", "Starting task display");
    taskdisplay_start();
    ESP_LOGI("main", "Task display started");
    while (1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}
