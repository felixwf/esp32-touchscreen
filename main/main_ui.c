
#include "lvgl.h"
#include <stdlib.h> // For rand() and srand()
#include <time.h>   // For time() - optional, see note below
#include "usbfont.h"

static lv_obj_t *meter;
// static lv_obj_t * btn;
static lv_disp_rot_t rotation = LV_DISP_ROT_NONE;

// static lv_obj_t *bg;


static void set_value(void *indic, int32_t v)
{
    lv_meter_set_indicator_end_value(meter, indic, v);
}

static void btn_cb(lv_event_t * e)
{
    lv_disp_t *disp = lv_event_get_user_data(e);
    rotation++;
    if (rotation > LV_DISP_ROT_270) {
        rotation = LV_DISP_ROT_NONE;
    }
    lv_disp_set_rotation(disp, rotation);
}

static void update_chart_with_random_data(lv_obj_t *chart, lv_chart_series_t *ser) 
{
    srand(time(NULL)); // Initialize random seed - only do this once, see note below

    // Assuming a fixed number of points you want to display
    for (int i = 0; i < 10; i++) {
        int random_value = rand() % 100; // Generate a random value
        // If lv_chart_set_next is available, use it
        lv_chart_set_next_value(chart, ser, random_value);
    }
}

void main_lvgl_demo_ui(lv_disp_t *disp)
{
    // lv_obj_t * scr = lv_disp_get_scr_act(NULL);
    lv_obj_t * bg = lv_disp_get_scr_act(NULL);
    lv_obj_center(bg);
    lv_obj_set_size(bg, 244, 244);

    // style of the background
    static lv_style_t style_bg;
    lv_style_init(&style_bg);
    // black background
    lv_style_set_bg_color(&style_bg, lv_color_make(0, 0, 0));
    lv_style_set_bg_opa(&style_bg, LV_OPA_COVER);
    // not scrollable
    lv_obj_set_scrollbar_mode(bg, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(bg, &style_bg, 0);



    // Create a label for the main power readout
    lv_obj_t * power_label = lv_label_create(bg);
    lv_label_set_text(power_label, "24w");
    lv_obj_set_style_text_font(power_label, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_color(power_label, lv_color_make(0, 255, 0), 0);
    lv_obj_align(power_label, LV_ALIGN_TOP_MID, 0, 4);

    // Create a chart for power history
    lv_obj_t * power_chart = lv_chart_create(bg);
    lv_obj_set_size(power_chart, 150, 50);
    lv_obj_align_to(power_chart, power_label, LV_ALIGN_TOP_MID, 0, 50);
    lv_chart_set_type(power_chart, LV_CHART_TYPE_LINE);
    lv_chart_series_t * ser = lv_chart_add_series(power_chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);
    static lv_style_t style_chart;
    lv_style_init(&style_chart);
    lv_style_set_bg_opa(&style_chart, LV_OPA_TRANSP);
    lv_style_set_border_opa(&style_chart, LV_OPA_TRANSP);
    lv_style_set_pad_all(&style_chart, 0);
    lv_obj_add_style(power_chart, &style_chart, 0);
    
    // Adjust the style for the lines if needed
    static lv_style_t style_grid;
    lv_style_init(&style_grid);
    // Set the grid line color and width
    // lv_style_set_line_color(&style_grid, lv_palette_main(LV_PALETTE_GREY)); // Correct function call without state
    lv_style_set_line_opa(&style_grid, LV_OPA_TRANSP); // Correct function call without state
    // lv_style_set_line_width(&style_grid, 1); // Correct function call without state
    lv_obj_add_style(power_chart, &style_grid, 0);


    // // Manually draw the bottom x-axis grid line
    // lv_obj_t * bottom_line = lv_line_create(power_chart); // Parent is 'bg' to ensure correct positioning
    // static lv_point_t bottom_line_points[] = {{0, 50}, {150, 50}}; // Adjust these coordinates based on the chart's size and position
    // lv_line_set_points(bottom_line, bottom_line_points, 2);
    // static lv_style_t style_bottom_line;
    // lv_style_init(&style_bottom_line);
    // lv_style_set_line_color(&style_bottom_line, lv_palette_main(LV_PALETTE_GREEN)); // Set color to match grid
    // lv_style_set_line_width(&style_bottom_line, 1); // Set line width

    //  lv_obj_t * right_line = lv_line_create(power_chart); // Parent is 'bg' to ensure correct positioning
    // static lv_point_t right_line_points[] = {{150, 0}, {150, 50}}; // Adjust these coordinates based on the chart's size and position
    // lv_line_set_points(right_line, right_line_points, 2);
    // static lv_style_t style_right_line;
    // lv_style_init(&style_right_line);
    // lv_style_set_line_color(&style_right_line, lv_palette_main(LV_PALETTE_GREEN)); // Set color to match grid
    // lv_style_set_line_width(&style_right_line, 1); // Set line width
   
    // lv_obj_add_style(bottom_line, &style_bottom_line, 0);
    // lv_obj_add_style(right_line, &style_right_line, 0);

    // // Ensure the line is positioned correctly relative to the chart
    // lv_obj_align_to(bottom_line, power_chart, LV_ALIGN_BOTTOM_MID, 0, 0);
    // add icon

    // Create an image and set the source to your image data
    // lv_obj_t * img = lv_img_create(bg); // Create an image object in the background object
    // lv_img_set_src(img, &icon_c_array); // Set the image source
    // lv_obj_align(img, NULL, LV_ALIGN_CENTER, 0, 0); // Position the image. Adjust as needed.

    // lv_obj_t * usbc = lv_label_create(bg)

    // 创建一个标签来显示第一个图标
    lv_obj_t *icon1 = lv_label_create(bg);
    lv_label_set_text(icon1, LV_SYMBOL_DUMMY "\xEE\x98\x9C"); // 使用图标的Unicode
    lv_obj_set_style_text_font(icon1, &usbfont, 0); // 设置为usbfont字体
    lv_obj_align(icon1, LV_ALIGN_CENTER, -50, 0); // 调整位置
    lv_obj_set_style_text_color(icon1, lv_color_make(30, 0xA7, 0xAF), 0);

    // 创建另一个标签来显示第二个图标
    lv_obj_t *icon2 = lv_label_create(bg);
    lv_label_set_text(icon2, LV_SYMBOL_DUMMY "\xEE\xA1\xBC"); // 使用图标的Unicode
    lv_obj_set_style_text_font(icon2, &usbfont, 0); // 设置为usbfont字体
    lv_obj_align(icon2, LV_ALIGN_CENTER, 50, 0); // 调整位置
    lv_obj_set_style_text_color(icon2, lv_color_make(30, 0xA7, 0xAF), 0);

    update_chart_with_random_data(power_chart, ser);

}