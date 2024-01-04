/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include <stdio.h>
#include <string.h>

// rgb functions
void rgb_block(int led_start, int led_end, uint8_t red, uint8_t green, uint8_t blue) {

    for (uint8_t i = led_start; i < led_end+1; i++) {
        rgb_matrix_set_color(i, red, green, blue);
    }
}
void rgb_home_row(char side){

    // GUI color: Red, index: 17 and 38
    // not used must adaped to crkbd layout
    // left
    if (side == 'l'){
        rgb_matrix_set_color(17, RGB_RED);
    // right
    } else if (side == 'r') {
        rgb_matrix_set_color(38, RGB_RED);
    }
    else {
        rgb_matrix_set_color(17, RGB_RED);
        rgb_matrix_set_color(38, RGB_RED);
    }
    // ALT color: Orange, index: 14 and 35
    if (side == 'l'){
        rgb_matrix_set_color(14, RGB_ORANGE);
    // right
    } else if (side == 'r') {
        rgb_matrix_set_color(35, RGB_ORANGE);
    }
    else {
        rgb_matrix_set_color(14, RGB_ORANGE);
        rgb_matrix_set_color(35, RGB_ORANGE);
    }
    // SHIFT color: Yellow, index: 11 and 32
    if (side == 'l'){
        rgb_matrix_set_color(11, RGB_YELLOW);
    // right
    } else if (side == 'r') {
        rgb_matrix_set_color(32, RGB_YELLOW);
    }
    else {
        rgb_matrix_set_color(11, RGB_YELLOW);
        rgb_matrix_set_color(32, RGB_YELLOW);
    }
    // CTRL color: White, index: 07 and 28
    if (side == 'l'){
        rgb_matrix_set_color(07, RGB_WHITE);
    // right
    } else if (side == 'r') {
        rgb_matrix_set_color(28, RGB_WHITE);
    }
    else {
        rgb_matrix_set_color(07, RGB_WHITE);
        rgb_matrix_set_color(28, RGB_WHITE);
    }
}
void rgb_indicator(char side, uint8_t red, uint8_t green, uint8_t blue){

    // colors outer column and inner column
    // left
    if (side == 'l'){
        rgb_block(0, 5, red, green, blue);
    // right
    } else if (side == 'r') {
        rgb_block(27, 32, red, green, blue);
    }
    // both sides
    else {
        rgb_block(0, 5, red, green, blue);
        rgb_block(27, 32, red, green, blue);
    }
}

// definitions
//
// define layers
//

enum crkbd_layers {
    _QWERTY,
    _NAV,
    _NUM,
    _FUN,
    _SYM,
    _MOS,
    _MED,
    _ADJUST,
};

// left hand home row mods

#define GUI_A LGUI_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define ALT_R LALT_T(KC_R)
#define CTL_S MT(MOD_LCTL, KC_S)
#define CTL_F LCTL_T(KC_F)
#define SHT_T MT(MOD_LSFT, KC_T)
#define SHT_D LSFT_T(KC_D)
#define ADJUST MO(_ADJUST)
#define QWERTY MO(_QWERTY)
#define NAV_SPC LT(_NAV, KC_SPC)
#define MED_ESC LT(_MED, KC_ESC)
#define MOS_TAB LT(_MOS, KC_TAB)

// right hand home row mods

#define SHT_N MT(MOD_RSFT, KC_N)
#define SHT_K RSFT_T(KC_K)
#define CTL_E MT(MOD_LCTL, KC_E)
#define ALT_I MT(MOD_LALT, KC_I)
#define CTL_J LCTL_T(KC_J)
#define ALT_L LALT_T(KC_L)
#define ALT_M RALT_T(KC_M)
#define GUI_O MT(MOD_LGUI, KC_O)
#define GUI_SC LGUI_T(KC_SCLN)
#define SYM_ENT LT(_SYM, KC_ENTER)
#define FUN_DEL LT(_FUN, KC_DEL)
#define NUM_BS LT(_NUM, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       ADJUST,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_RALT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,   GUI_A,   ALT_S,   SHT_D,   CTL_F,    KC_G,                         KC_H,   CTL_J,   SHT_K,   ALT_L, GUI_SC,  KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,   ALT_M, KC_COMM,  KC_DOT, KC_SLSH, FUN_DEL,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          MED_ESC, NAV_SPC, MOS_TAB,    SYM_ENT,  NUM_BS, FUN_DEL
                                      //`--------------------------'  `--------------------------'

  ),

    [_NUM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_GRV,     KC_1,    KC_2,    KC_3, KC_BSLS,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                           KC_DOT,    KC_0, KC_MINS,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_COLN, KC_DLR,  KC_PERC, KC_CIRC, KC_PPLS,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LPRN, KC_RPRN, KC_UNDS,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_FUN] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,  KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SCRL,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,  KC_F10,   KC_F1,   KC_F2,   KC_F3,  KC_BRK,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_APP, _______, _______,     _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      _______, KC_UNDO,  KC_CUT, KC_COPY, KC_PSTE, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,   GUI_A,   ALT_S,   SHT_D,   CTL_F,    KC_G,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_CAPS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_DEL,   KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,                       KC_INS, KC_PGDN, KC_PGUP, KC_HOME,  KC_END, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                        MED_ESC,  NAV_SPC,  MOS_TAB,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_MOS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                      _______, KC_UNDO,  KC_CUT, KC_COPY, KC_PSTE, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,   GUI_A,   ALT_S,   SHT_D,   CTL_F,    KC_G,                      KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_CAPS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_DEL,   KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,                      KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R,  KC_END, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          MED_ESC, NAV_SPC, MOS_TAB,    KC_BTN2, KC_BTN1, KC_BTN3
                                      //`--------------------------'  `--------------------------'
  ),

    [_MED] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_R,    KC_M,    KC_H,    KC_S,    KC_V, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_TAB,   GUI_A,   ALT_S,   SHT_D,   CTL_F,    KC_G,                      KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT,    KC_E, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
       KC_DEL,   KC_Z,     KC_X,    KC_C,    KC_V,    KC_B,                         KC_O,    KC_0,    KC_1,    KC_2,    KC_3, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          MED_ESC, NAV_SPC, MOS_TAB,    KC_MSTP, KC_MPLY, KC_MUTE
                                      //`--------------------------'  `--------------------------'
  ),

    [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      _______, AU_TOGG, HF_TOGG, RGB_HUI, RGB_MOD, XXXXXXX,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      QK_BOOT, DB_TOGG,  QWERTY, RGB_SAI, RGB_VAI, XXXXXXX,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      XXXXXXX, XXXXXXX, XXXXXXX, RGB_SAD, RGB_VAD, XXXXXXX,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};


/// Overview LED numbers
//                                                       Front
//       Left                                                                           Right
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
//      24   ,     23 ,     18 ,     17 ,    10  ,     9  ,                         36  ,    37  ,   44   ,   45   ,   50   ,   51   ,
//  |--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//      25   ,     22 ,     19 ,     16 ,    11  ,     8  ,                         35  ,    38  ,   43   ,   46   ,   49   ,   52   ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//      26   ,     21 ,     20 ,     15 ,    12  ,     7  ,                         34  ,    39  ,   42   ,   47   ,   48   ,   53   ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//                                    ,   14  ,     13   ,    6    ,      33    ,    40 ,   41
                                      //`--------------------------'  `--------------------------'



//                                                    Back
// Left                                                                            Right
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
//           ,  2     ,        ,        ,    1   ,    0   ,                         27  ,   28   ,        ,        ,   29   ,        ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//           ,   3    ,        ,        ,   4    ,    5   ,                         32  ,   31   ,        ,        ,   30   ,        ,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
//           ,        ,        ,        ,        ,        ,                             ,        ,        ,        ,        ,        ,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
//                                       ,                ,        ,           ,            ,
                                      //`--------------------------'  `--------------------------'

#if RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
      rgb_indicator('b', RGB_RED);
      /* for (uint8_t i = 4; i < 7; i++) { */
      /*     rgb_matrix_set_color(i, RGB_RED); */
      /* } */
      /* // not possible to change color of the secondary split half in case of caps look */
      /***************************************/
      /* for (uint8_t i = 25; i < 27; i++) { */
      /*   rgb_matrix_set_color(i, RGB_RED); */
      /* }                                   */
      /* rgb_matrix_set_color(25, RGB_RED);  */
      /* rgb_matrix_set_color(26, RGB_RED);  */
      /* rgb_matrix_set_color(27, RGB_RED);  */
      /***************************************/
      /* RGB_MATRIX_INDICATOR_SET_COLOR(25, 255, 255, 255); // assuming caps lock is at led #5 */
    }
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case _ADJUST:
            // qwerty
            rgb_matrix_set_color(19, RGB_TURQUOISE);
            // qmk boot
            rgb_matrix_set_color(25, RGB_RED);

            rgb_matrix_set_color(17, RGB_AZURE);
            rgb_block(15,16, RGB_GREEN);
            rgb_matrix_set_color(10, RGB_CYAN);
            rgb_block(11,12, RGB_BLUE);
            rgb_indicator('l', RGB_ORANGE);
            break;
        case _NUM:
            rgb_indicator('l', RGB_AZURE);
            break;
        case _FUN:
            rgb_indicator('l', RGB_BLUE);
            break;
        case _SYM:
            rgb_indicator('l', RGB_CORAL);
            break;
        case _NAV:
            rgb_indicator('r', RGB_GREEN);
            break;
        case _MOS:
            rgb_indicator('r', RGB_YELLOW);
            break;
        case _MED:
            rgb_indicator('r', RGB_PINK);
            break;
        default:
            break;
        }
    return false;
}

#endif


// oled
#ifdef OLED_ENABLE

bool render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Q W E R T Y\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("N U M\n"), false);
            break;
        case _FUN:
            oled_write_P(PSTR("F U N\n"), false);
            break;
        case _SYM:
            oled_write_P(PSTR("S Y M\n"), false);
            break;
        case _NAV:
            oled_write_P(PSTR("N A V\n"), false);
            break;
        case _MOS:
            oled_write_P(PSTR("M O S\n"), false);
            break;
        case _MED:
            oled_write_P(PSTR("M E D\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("A D J\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
       oled_render_logo();  // Renders a static logo

    }
    return false;
}

#endif
