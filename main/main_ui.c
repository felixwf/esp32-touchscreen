
#include "lvgl.h"

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

void main_lvgl_demo_ui(lv_disp_t *disp)
{
    lv_obj_t * scr = lv_disp_get_scr_act(NULL);

    // Create a label for the main power readout
    lv_obj_t * power_label = lv_label_create(scr);
    lv_label_set_text(power_label, "24w");
    lv_obj_set_style_text_font(power_label, &lv_font_montserrat_48, 0);
    lv_obj_set_style_text_color(power_label, lv_color_make(0, 255, 0), 0);
    lv_obj_align(power_label, LV_ALIGN_CENTER, 0, -50);

    // Create a chart for power history
    lv_obj_t * power_chart = lv_chart_create(scr);
    lv_obj_set_size(power_chart, 200, 100);
    lv_obj_align_to(power_chart, power_label, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_chart_set_type(power_chart, LV_CHART_TYPE_LINE);
    lv_chart_series_t * ser = lv_chart_add_series(power_chart, lv_palette_main(LV_PALETTE_GREEN), LV_CHART_AXIS_PRIMARY_Y);

    // Add points to the series
    // lv_chart_set_next(power_chart, ser, 10);
    // lv_chart_set_next(power_chart, ser, 25);
    // lv_chart_set_next(power_chart, ser, 45);
    // lv_chart_set_next(power_chart, ser, 30);
    // lv_chart_set_point_count(power_chart, ser, 10);
    // lv_chart_set_point_count(power_chart, ser, 25);
    // lv_chart_set_point_count(power_chart, ser, 45);
    // lv_chart_set_point_count(power_chart, ser, 30);

    // Create styles for the bar background and indicator
    static lv_style_t style_bar_bg;
    lv_style_init(&style_bar_bg);
    lv_style_set_bg_color(&style_bar_bg, lv_color_make(0, 0, 0));
    lv_style_set_bg_opa(&style_bar_bg, LV_OPA_COVER);
    lv_style_set_border_color(&style_bar_bg, lv_color_make(255, 255, 255));
    lv_style_set_border_width(&style_bar_bg, 1);
    lv_style_set_radius(&style_bar_bg, 5);

    static lv_style_t style_bar_indic;
    lv_style_init(&style_bar_indic);
    lv_style_set_bg_color(&style_bar_indic, lv_palette_main(LV_PALETTE_GREEN));
    lv_style_set_bg_opa(&style_bar_indic, LV_OPA_COVER);
    lv_style_set_radius(&style_bar_indic, 5);

    // Create bars for power readings
    for (int i = 0; i < 4; i++) {
        lv_obj_t * power_bar = lv_bar_create(scr);
        lv_obj_set_size(power_bar, 200, 20);
        lv_obj_add_style(power_bar, &style_bar_bg, 0);
        lv_obj_add_style(power_bar, &style_bar_indic, LV_PART_INDICATOR);
        lv_bar_set_range(power_bar, 0, 100);
        lv_bar_set_value(power_bar, 25, LV_ANIM_OFF);
        lv_obj_align(power_bar, LV_ALIGN_CENTER, 0, (i * 30) + 100);
    }
}