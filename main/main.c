
#include "taskdisplay.h"
#include "esp_err.h"
#include "esp_log.h"
#include "esp_check.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "string.h"
#include "task_lcd_touch.h"


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

// 定义用于存储任务状态信息的字符数组的大小
#define TASKS_STATUS_BUFFER_SIZE 2048

// 任务状态打印函数
void printTasksStatus(void *parameters) {
    // 分配内存用于存储任务状态信息
    char *taskStatusBuffer = malloc(TASKS_STATUS_BUFFER_SIZE);
    if (taskStatusBuffer == NULL) {
        ESP_LOGE("TASKS", "Failed to allocate memory for task status buffer.");
        vTaskDelete(NULL); // 删除当前任务
    }

    for (;;) {
        // 清零内存区域
        memset(taskStatusBuffer, 0, TASKS_STATUS_BUFFER_SIZE);
        // 打印列名称
        ESP_LOGI("TASKS", "Name\t\tState\tPrio\tStack\tNum");
        // 获取并填充所有任务的状态信息
        vTaskList(taskStatusBuffer);
        // 打印任务状态信息
        ESP_LOGI("TASKS", "Task Status:\n%s", taskStatusBuffer);

        // 等待一段时间，这里设置为每5秒打印一次
        vTaskDelay(pdMS_TO_TICKS(5000));
    }

    // 任务结束后释放内存
    free(taskStatusBuffer);
}

void taskstatus_start(void) {
    // 创建任务
    xTaskCreate(printTasksStatus, "printTasksStatus", 2048, NULL, 5, NULL);
}

void task_lcd_touch_start(void) {
    xTaskCreate(vTaskLcdTouch, "vTaskLcdTouch", 4096, NULL, 5, NULL);
}

void app_main(void)
{
    ESP_ERROR_CHECK(esp_check());
    
    // taskdisplay_start();
    task_lcd_touch_start();
    ESP_LOGI("main", "Task task_lcd_touch_start started");
    taskstatus_start();
    ESP_LOGI("main", "Task status started");


    ESP_LOGI("main", "All tasks started");
}
