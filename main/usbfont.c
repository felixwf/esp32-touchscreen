/*******************************************************************************
 * Size: 48 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/
#define LV_LVGL_H_INCLUDE_SIMPLE
#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef USBFONT
#define USBFONT 1
#endif

#if USBFONT

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E61C "" */
    0xf, 0xff, 0xff, 0xff, 0xfc, 0x7, 0x0, 0x0,
    0x0, 0x0, 0x61, 0x80, 0x0, 0x0, 0x0, 0x6,
    0x20, 0xc8, 0x0, 0x0, 0x0, 0x6c, 0x7f, 0xff,
    0xff, 0xff, 0x5, 0xf, 0xff, 0xff, 0xff, 0xf0,
    0xa1, 0xff, 0xff, 0xff, 0xfe, 0x16, 0x3f, 0xff,
    0xff, 0xff, 0xc2, 0x41, 0xef, 0xde, 0xfd, 0xe0,
    0xcc, 0x0, 0x0, 0x0, 0x0, 0x30, 0xc0, 0x0,
    0x0, 0x0, 0xc, 0x7, 0xff, 0xff, 0xff, 0xfe,
    0x0,

    /* U+E87C "" */
    0x3f, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xfe,
    0xff, 0xff, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x7,
    0xe0, 0x0, 0x0, 0x7, 0xe0, 0x0, 0x0, 0x7,
    0xe0, 0x0, 0x0, 0x7, 0xe0, 0x0, 0x0, 0x7,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0x7f, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xfc
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 768, .box_w = 43, .box_h = 12, .ofs_x = 3, .ofs_y = 12},
    {.bitmap_index = 65, .adv_w = 768, .box_w = 32, .box_h = 16, .ofs_x = 8, .ofs_y = 10}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x260
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 58908, .range_length = 609, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 2, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LVGL_VERSION_MAJOR == 8
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
#endif

#if LVGL_VERSION_MAJOR >= 8
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LVGL_VERSION_MAJOR == 8
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LVGL_VERSION_MAJOR >= 8
const lv_font_t usbfont = {
#else
lv_font_t usbfont = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font*/
    .base_line = -10,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc,          /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
    .fallback = NULL,
    .user_data = NULL
};



#endif /*#if USBFONT*/

