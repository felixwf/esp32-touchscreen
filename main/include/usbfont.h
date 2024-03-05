#ifndef USBFONT_H
#define USBFONT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

/* 外部声明usbfont字体，这使得usbfont字体可以被项目中的其他C文件访问 */
extern const lv_font_t usbfont;

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* USBFONT_H */
