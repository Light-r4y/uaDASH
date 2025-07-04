// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.5.3
// LVGL version: 8.3.11
// Project name: engine_settings

#include "ui.h"

lv_obj_t * ui_engineConfigScreen = NULL;
lv_obj_t * ui_LabelEngineConf = NULL;
lv_obj_t * ui_LabelDisplacement = NULL;
lv_obj_t * ui_LabelTrigger = NULL;
lv_obj_t * ui_LabelCam = NULL;
lv_obj_t * ui_CheckboxDisp48 = NULL;
lv_obj_t * ui_CheckboxDisp53 = NULL;
lv_obj_t * ui_CheckboxDisp57 = NULL;
lv_obj_t * ui_CheckboxDisp60 = NULL;
lv_obj_t * ui_CheckboxDisp62 = NULL;
lv_obj_t * ui_CheckboxDisp70 = NULL;
lv_obj_t * ui_CheckboxTrig24 = NULL;
lv_obj_t * ui_CheckboxTrig58 = NULL;
lv_obj_t * ui_CheckboxCamshape1 = NULL;
lv_obj_t * ui_CheckboxCamshape2 = NULL;
lv_obj_t * ui_CheckboxCamshape4 = NULL;
lv_obj_t * ui_engConfSaveButton = NULL;
lv_obj_t * ui_LabelSave = NULL;
lv_obj_t * ui_engConfBackButton = NULL;
lv_obj_t * ui_LabelBack = NULL;
// event funtions
void ui_event_CheckboxDisp48(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        setDisp48L(e);
    }
}

void ui_event_CheckboxDisp53(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        setDisp53L(e);
    }
}

void ui_event_CheckboxDisp57(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        setDisp57L(e);
    }
}

void ui_event_CheckboxDisp60(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        setDisp60L(e);
    }
}

void ui_event_CheckboxDisp62(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        setDisp62L(e);
    }
}

void ui_event_CheckboxDisp70(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        setDisp70L(e);
    }
}

void ui_event_CheckboxTrig24(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        setTrig24(e);
    }
}

void ui_event_CheckboxTrig58(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        setTrig58(e);
    }
}

void ui_event_CheckboxCamshape1(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        setCamS1(e);
    }
}

void ui_event_CheckboxCamshape2(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        setCamS2(e);
    }
}

void ui_event_CheckboxCamshape4(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        setCamS4(e);
    }
}

void ui_event_engConfSaveButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        engSetSave(e);
    }
}

void ui_event_engConfBackButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);

    if(event_code == LV_EVENT_CLICKED) {
        _ui_screen_change(&ui_benchScreen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, &ui_benchScreen_screen_init);
        _ui_screen_delete(&ui_engineConfigScreen);
        clearEngConfiguration(e);
    }
}

// build funtions

void ui_engineConfigScreen_screen_init(void)
{
    ui_engineConfigScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_engineConfigScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_engineConfigScreen, lv_color_hex(0x313131), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_engineConfigScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelEngineConf = lv_label_create(ui_engineConfigScreen);
    lv_obj_set_width(ui_LabelEngineConf, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelEngineConf, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelEngineConf, 0);
    lv_obj_set_y(ui_LabelEngineConf, -219);
    lv_obj_set_align(ui_LabelEngineConf, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelEngineConf, "ENGINE CONFIGURATION");
    lv_obj_set_style_text_color(ui_LabelEngineConf, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelEngineConf, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelEngineConf, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelDisplacement = lv_label_create(ui_engineConfigScreen);
    lv_obj_set_width(ui_LabelDisplacement, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelDisplacement, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelDisplacement, 100);
    lv_obj_set_y(ui_LabelDisplacement, 79);
    lv_label_set_text(ui_LabelDisplacement, "Displacement");
    lv_obj_set_style_text_color(ui_LabelDisplacement, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelDisplacement, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelDisplacement, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelTrigger = lv_label_create(ui_engineConfigScreen);
    lv_obj_set_width(ui_LabelTrigger, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelTrigger, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelTrigger, 350);
    lv_obj_set_y(ui_LabelTrigger, 79);
    lv_label_set_text(ui_LabelTrigger, "Trigger");
    lv_obj_set_style_text_color(ui_LabelTrigger, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelTrigger, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelTrigger, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelCam = lv_label_create(ui_engineConfigScreen);
    lv_obj_set_width(ui_LabelCam, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelCam, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_LabelCam, 600);
    lv_obj_set_y(ui_LabelCam, 79);
    lv_label_set_text(ui_LabelCam, "Camshape");
    lv_obj_set_style_text_color(ui_LabelCam, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelCam, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelCam, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CheckboxDisp48 = lv_checkbox_create(ui_engineConfigScreen);
    lv_checkbox_set_text(ui_CheckboxDisp48, "4.8 l");
    lv_obj_set_width(ui_CheckboxDisp48, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CheckboxDisp48, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CheckboxDisp48, 110);
    lv_obj_set_y(ui_CheckboxDisp48, 125);
    lv_obj_add_flag(ui_CheckboxDisp48, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CheckboxDisp48,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);     /// Flags
    lv_obj_set_style_text_color(ui_CheckboxDisp48, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CheckboxDisp48, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CheckboxDisp48, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_CheckboxDisp48, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_CheckboxDisp48, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CheckboxDisp48, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CheckboxDisp48, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CheckboxDisp48, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_CheckboxDisp48, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_CheckboxDisp48, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_CheckboxDisp48, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_CheckboxDisp53 = lv_checkbox_create(ui_engineConfigScreen);
    lv_checkbox_set_text(ui_CheckboxDisp53, "5.3 l");
    lv_obj_set_width(ui_CheckboxDisp53, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CheckboxDisp53, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CheckboxDisp53, 110);
    lv_obj_set_y(ui_CheckboxDisp53, 170);
    lv_obj_add_flag(ui_CheckboxDisp53, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CheckboxDisp53,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);     /// Flags
    lv_obj_set_style_text_color(ui_CheckboxDisp53, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CheckboxDisp53, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CheckboxDisp53, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_CheckboxDisp53, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_CheckboxDisp53, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CheckboxDisp53, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CheckboxDisp53, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CheckboxDisp53, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_CheckboxDisp53, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_CheckboxDisp53, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_CheckboxDisp53, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_CheckboxDisp57 = lv_checkbox_create(ui_engineConfigScreen);
    lv_checkbox_set_text(ui_CheckboxDisp57, "5.7 l");
    lv_obj_set_width(ui_CheckboxDisp57, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CheckboxDisp57, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CheckboxDisp57, 110);
    lv_obj_set_y(ui_CheckboxDisp57, 215);
    lv_obj_add_flag(ui_CheckboxDisp57, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CheckboxDisp57,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);     /// Flags
    lv_obj_set_style_text_color(ui_CheckboxDisp57, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CheckboxDisp57, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CheckboxDisp57, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_CheckboxDisp57, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_CheckboxDisp57, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CheckboxDisp57, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CheckboxDisp57, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CheckboxDisp57, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_CheckboxDisp57, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_CheckboxDisp57, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_CheckboxDisp57, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_CheckboxDisp60 = lv_checkbox_create(ui_engineConfigScreen);
    lv_checkbox_set_text(ui_CheckboxDisp60, "6.0 l");
    lv_obj_set_width(ui_CheckboxDisp60, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CheckboxDisp60, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CheckboxDisp60, 110);
    lv_obj_set_y(ui_CheckboxDisp60, 260);
    lv_obj_add_flag(ui_CheckboxDisp60, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CheckboxDisp60,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);     /// Flags
    lv_obj_set_style_text_color(ui_CheckboxDisp60, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CheckboxDisp60, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CheckboxDisp60, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_CheckboxDisp60, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_CheckboxDisp60, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CheckboxDisp60, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CheckboxDisp60, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CheckboxDisp60, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_CheckboxDisp60, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_CheckboxDisp60, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_CheckboxDisp60, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_CheckboxDisp62 = lv_checkbox_create(ui_engineConfigScreen);
    lv_checkbox_set_text(ui_CheckboxDisp62, "6.2 l");
    lv_obj_set_width(ui_CheckboxDisp62, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CheckboxDisp62, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CheckboxDisp62, 110);
    lv_obj_set_y(ui_CheckboxDisp62, 305);
    lv_obj_add_flag(ui_CheckboxDisp62, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CheckboxDisp62,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);     /// Flags
    lv_obj_set_style_text_color(ui_CheckboxDisp62, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CheckboxDisp62, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CheckboxDisp62, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_CheckboxDisp62, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_CheckboxDisp62, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CheckboxDisp62, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CheckboxDisp62, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CheckboxDisp62, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_CheckboxDisp62, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_CheckboxDisp62, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_CheckboxDisp62, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_CheckboxDisp70 = lv_checkbox_create(ui_engineConfigScreen);
    lv_checkbox_set_text(ui_CheckboxDisp70, "7.0 l");
    lv_obj_set_width(ui_CheckboxDisp70, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CheckboxDisp70, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CheckboxDisp70, 110);
    lv_obj_set_y(ui_CheckboxDisp70, 350);
    lv_obj_add_flag(ui_CheckboxDisp70, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CheckboxDisp70,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);     /// Flags
    lv_obj_set_style_text_color(ui_CheckboxDisp70, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CheckboxDisp70, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CheckboxDisp70, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_CheckboxDisp70, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_CheckboxDisp70, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CheckboxDisp70, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CheckboxDisp70, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CheckboxDisp70, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_CheckboxDisp70, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_CheckboxDisp70, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_CheckboxDisp70, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_CheckboxTrig24 = lv_checkbox_create(ui_engineConfigScreen);
    lv_checkbox_set_text(ui_CheckboxTrig24, "24");
    lv_obj_set_width(ui_CheckboxTrig24, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CheckboxTrig24, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CheckboxTrig24, 365);
    lv_obj_set_y(ui_CheckboxTrig24, 125);
    lv_obj_add_flag(ui_CheckboxTrig24, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CheckboxTrig24,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);     /// Flags
    lv_obj_set_style_text_color(ui_CheckboxTrig24, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CheckboxTrig24, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CheckboxTrig24, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_CheckboxTrig24, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_CheckboxTrig24, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CheckboxTrig24, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CheckboxTrig24, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CheckboxTrig24, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_CheckboxTrig24, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_CheckboxTrig24, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_CheckboxTrig24, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_CheckboxTrig58 = lv_checkbox_create(ui_engineConfigScreen);
    lv_checkbox_set_text(ui_CheckboxTrig58, "58");
    lv_obj_set_width(ui_CheckboxTrig58, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CheckboxTrig58, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CheckboxTrig58, 365);
    lv_obj_set_y(ui_CheckboxTrig58, 170);
    lv_obj_add_flag(ui_CheckboxTrig58, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CheckboxTrig58,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);     /// Flags
    lv_obj_set_style_text_color(ui_CheckboxTrig58, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CheckboxTrig58, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CheckboxTrig58, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_CheckboxTrig58, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_CheckboxTrig58, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CheckboxTrig58, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CheckboxTrig58, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CheckboxTrig58, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_CheckboxTrig58, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_CheckboxTrig58, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_CheckboxTrig58, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_CheckboxCamshape1 = lv_checkbox_create(ui_engineConfigScreen);
    lv_checkbox_set_text(ui_CheckboxCamshape1, "1");
    lv_obj_set_width(ui_CheckboxCamshape1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CheckboxCamshape1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CheckboxCamshape1, 610);
    lv_obj_set_y(ui_CheckboxCamshape1, 125);
    lv_obj_add_flag(ui_CheckboxCamshape1, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CheckboxCamshape1,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);     /// Flags
    lv_obj_set_style_text_color(ui_CheckboxCamshape1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CheckboxCamshape1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CheckboxCamshape1, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_CheckboxCamshape1, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_CheckboxCamshape1, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CheckboxCamshape1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CheckboxCamshape1, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CheckboxCamshape1, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_CheckboxCamshape1, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_CheckboxCamshape1, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_CheckboxCamshape1, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_CheckboxCamshape2 = lv_checkbox_create(ui_engineConfigScreen);
    lv_checkbox_set_text(ui_CheckboxCamshape2, "2");
    lv_obj_set_width(ui_CheckboxCamshape2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CheckboxCamshape2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CheckboxCamshape2, 610);
    lv_obj_set_y(ui_CheckboxCamshape2, 170);
    lv_obj_add_flag(ui_CheckboxCamshape2, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CheckboxCamshape2,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);     /// Flags
    lv_obj_set_style_text_color(ui_CheckboxCamshape2, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CheckboxCamshape2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CheckboxCamshape2, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_CheckboxCamshape2, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_CheckboxCamshape2, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CheckboxCamshape2, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CheckboxCamshape2, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CheckboxCamshape2, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_CheckboxCamshape2, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_CheckboxCamshape2, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_CheckboxCamshape2, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_CheckboxCamshape4 = lv_checkbox_create(ui_engineConfigScreen);
    lv_checkbox_set_text(ui_CheckboxCamshape4, "4");
    lv_obj_set_width(ui_CheckboxCamshape4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_CheckboxCamshape4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_CheckboxCamshape4, 610);
    lv_obj_set_y(ui_CheckboxCamshape4, 215);
    lv_obj_add_flag(ui_CheckboxCamshape4, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CheckboxCamshape4,
                      LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE);     /// Flags
    lv_obj_set_style_text_color(ui_CheckboxCamshape4, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_CheckboxCamshape4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_CheckboxCamshape4, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_radius(ui_CheckboxCamshape4, 0, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_CheckboxCamshape4, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_CheckboxCamshape4, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_CheckboxCamshape4, lv_color_hex(0xFFFFFF), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_CheckboxCamshape4, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_CheckboxCamshape4, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui_CheckboxCamshape4, lv_color_hex(0x313131), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_CheckboxCamshape4, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_engConfSaveButton = lv_btn_create(ui_engineConfigScreen);
    lv_obj_set_width(ui_engConfSaveButton, 120);
    lv_obj_set_height(ui_engConfSaveButton, 50);
    lv_obj_set_x(ui_engConfSaveButton, -33);
    lv_obj_set_y(ui_engConfSaveButton, -26);
    lv_obj_set_align(ui_engConfSaveButton, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_engConfSaveButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_engConfSaveButton,
                      LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                      LV_OBJ_FLAG_SCROLLABLE);     /// Flags
    lv_obj_set_style_bg_color(ui_engConfSaveButton, lv_color_hex(0x32A41B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_engConfSaveButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelSave = lv_label_create(ui_engConfSaveButton);
    lv_obj_set_width(ui_LabelSave, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelSave, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelSave, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelSave, "SAVE");
    lv_obj_set_style_text_color(ui_LabelSave, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelSave, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelSave, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_engConfBackButton = lv_btn_create(ui_engineConfigScreen);
    lv_obj_set_width(ui_engConfBackButton, 120);
    lv_obj_set_height(ui_engConfBackButton, 40);
    lv_obj_set_x(ui_engConfBackButton, -180);
    lv_obj_set_y(ui_engConfBackButton, -30);
    lv_obj_set_align(ui_engConfBackButton, LV_ALIGN_BOTTOM_RIGHT);
    lv_obj_add_flag(ui_engConfBackButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_engConfBackButton,
                      LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE |
                      LV_OBJ_FLAG_SCROLLABLE);     /// Flags
    lv_obj_set_style_bg_color(ui_engConfBackButton, lv_color_hex(0xE0FF00), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_engConfBackButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_LabelBack = lv_label_create(ui_engConfBackButton);
    lv_obj_set_width(ui_LabelBack, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_LabelBack, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_LabelBack, LV_ALIGN_CENTER);
    lv_label_set_text(ui_LabelBack, "back");
    lv_obj_set_style_text_color(ui_LabelBack, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_LabelBack, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_LabelBack, &ui_font_FontLabel, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_add_event_cb(ui_CheckboxDisp48, ui_event_CheckboxDisp48, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CheckboxDisp53, ui_event_CheckboxDisp53, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CheckboxDisp57, ui_event_CheckboxDisp57, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CheckboxDisp60, ui_event_CheckboxDisp60, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CheckboxDisp62, ui_event_CheckboxDisp62, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CheckboxDisp70, ui_event_CheckboxDisp70, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CheckboxTrig24, ui_event_CheckboxTrig24, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CheckboxTrig58, ui_event_CheckboxTrig58, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CheckboxCamshape1, ui_event_CheckboxCamshape1, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CheckboxCamshape2, ui_event_CheckboxCamshape2, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CheckboxCamshape4, ui_event_CheckboxCamshape4, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_engConfSaveButton, ui_event_engConfSaveButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_engConfBackButton, ui_event_engConfBackButton, LV_EVENT_ALL, NULL);

}

void ui_engineConfigScreen_screen_destroy(void)
{
    if(ui_engineConfigScreen) lv_obj_del(ui_engineConfigScreen);

    // NULL screen variables
    ui_engineConfigScreen = NULL;
    ui_LabelEngineConf = NULL;
    ui_LabelDisplacement = NULL;
    ui_LabelTrigger = NULL;
    ui_LabelCam = NULL;
    ui_CheckboxDisp48 = NULL;
    ui_CheckboxDisp53 = NULL;
    ui_CheckboxDisp57 = NULL;
    ui_CheckboxDisp60 = NULL;
    ui_CheckboxDisp62 = NULL;
    ui_CheckboxDisp70 = NULL;
    ui_CheckboxTrig24 = NULL;
    ui_CheckboxTrig58 = NULL;
    ui_CheckboxCamshape1 = NULL;
    ui_CheckboxCamshape2 = NULL;
    ui_CheckboxCamshape4 = NULL;
    ui_engConfSaveButton = NULL;
    ui_LabelSave = NULL;
    ui_engConfBackButton = NULL;
    ui_LabelBack = NULL;

}
