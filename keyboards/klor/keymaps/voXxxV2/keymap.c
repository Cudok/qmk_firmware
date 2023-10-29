/*

                                        █         █    █            ▄▄▄▀▀▀▀▀▀▄▄▄        █▀▀▀▀▀▀▀▀▀▀█
                                        █        █     █          ▄▀            ▀▄      █          █
                                        █       █      █        ▄▀                ▀▄    █          █
                                        █      █       █        █                  █    █          █
                                        █     █        █       █                    █   █          █
                                        █    █         █       █                    █   █▄▄▄▄▄▄▄▄▄▄█
                                        █   █ █        █       █                    █   █      █
                                        █  █   █       █        █                  █    █       █
                                        █ █     █      █        ▀▄                ▄▀    █        █
                                        ██       █     █          ▀▄            ▄▀      █         █
                                        █         █    █▄▄▄▄▄▄▄▄    ▀▀▀▄▄▄▄▄▄▀▀▀        █          █

                                        ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
                                        adapted by voxXx

*/
#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include "klor.h"
#ifdef HAPTIC_ENABLE
#include "drivers/haptic/DRV2605L.h"
#endif //HAPTIC ENABLE


void rgb_block(int led_start, int led_end, uint8_t red, uint8_t green, uint8_t blue) {

    for (uint8_t i = led_start; i < led_end+1; i++) {
        rgb_matrix_set_color(i, red, green, blue);
    }
}
void rgb_home_row(char side){

    // GUI color: Red, index: 17 and 38
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

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ D E F I N I T I O N S                                                                                                                      │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   l a y e r s                                 │
// └───────────────────────────────────────────────────────────┘ 

enum klor_layers {
    /* _M_XYZ = Mac Os, _W_XYZ = Win/Linux */
    _QWERTY,
    _NAV,
    _ADJUST,
};


// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   m a c r o n a m e s                         │
// └───────────────────────────────────────────────────────────┘

// LEFT HAND HOME ROW MODS ├───────────────────────────────────┐

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
//#define Medi_Esc LT(Medi, KC_ESC)
//#define Mos_Tab LT(Mouse, KC_TAB)

// RIGHT HAND HOME ROW MODS ├───────────────────────────────────┐

#define SHT_N MT(MOD_RSFT, KC_N)
#define SHT_K RSFT_T(KC_K)
#define CTL_E MT(MOD_LCTL, KC_E)
#define CTL_J RCTL_T(KC_J)
#define ALT_I MT(MOD_LALT, KC_I)
#define ALT_L LALT_T(KC_L)
#define ALT_M RALT_T(KC_M)
#define GUI_O MT(MOD_LGUI, KC_O)
#define GUI_sc LGUI_T(KC_SCLN)
//#define Sym_Ent LT(Nav, KC_ENTER)
//#define Fun_Del LT(Fun, KC_DEL)
//#define Num_Bs LT(Num, KC_DEL)
// ┌───────────────────────────────────────────────────────────┐
// │ d e f i n e   s o u n d s                                 │
// └───────────────────────────────────────────────────────────┘

#ifdef AUDIO_ENABLE
  #define WINXP_SOUND W__NOTE(_DS6), Q__NOTE(_DS5), H__NOTE(_AS5), H__NOTE(_GS5), H__NOTE(_DS5), H__NOTE(_DS6), H__NOTE(_AS5)
  #define MAC_SOUND S__NOTE(_CS5), B__NOTE(_C5)
 
  float winxp_song[][2] = SONG(WINXP_SOUND);
  float mac_song[][2] = SONG(MAC_SOUND);
#endif // AUDIO_ENABLE

// ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
// │ K E Y M A P S                                                                                                                              │
// └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
// ▝▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▘

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌───────────────────────────────────────────────────────────┐
   │ q w e r t y                                               │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐   __________________________________   ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │    Q    │    W    │    E    │    R    │    T    │  /                                  \  │    Y    │    U    │    I    │    O    │    P    │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ /                                    \ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │   Tab   │ GUI(A)  │ Alt(S)  │Shift(D) │ Ctl(F)  │    G    |/      ────────           ────────     \│    H    │ Ctl(J)  │Shift(K) │ AltR(L) │ GUI(;)  │    "    │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤      │Mute/Vol│         │PLY/Scrol│    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │Shift/Cap│    Z    │    X    │    C    │    V    │    B    │       ────────           ────────      │    N    │    M    │    ,    │    .    │    /    │  AltR   │
   └─────────┴─────────┴─────────┴─────────┼─────────┼─────────┼─────────┬─────────┐┌─────────┬─────────┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                           │Medi(Esc)│Nav(Spc) │Mos(TAB) │         ││         │Sym(ENT) │Num(BSpc)│Fun(Del) │
                                           └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */

   [_QWERTY] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                                              KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,
    KC_TAB,   GUI_A,    ALT_S,    SHT_D,    CTL_F,    KC_G,                                              KC_H,     CTL_J,    SHT_K,    ALT_L,    GUI_sc,    KC_QUOT,
    KC_DEL,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_MUTE,                       KC_MPLY,  KC_N,     ALT_M,    KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
                                            KC_ESC,   NAV_SPC,  KC_TAB,   ADJUST,    KC_LGUI,  KC_ENTER, KC_BSPC,  KC_DEL
 ),

 /*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸

   ┌───────────────────────────────────────────────────────────┐
   │ n a v i g a t i o n                                       │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐   __________________________________   ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │    Q    │    W    │    E    │    R    │    T    │  /                                  \  │  redo   │  undo   │   cut   │  copy   │  paste  │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ /                                    \ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │   Tab   │ GUI(A)  │ Alt(S)  │Shift(D) │ Ctl(F)  │    G    |/      ────────           ────────     \│  left   │  down   │    up   │  right  │  Caps   │    "    │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤      │Mute/Vol│         │PLY/Scrol│    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │Shift/Cap│    Z    │    X    │    C    │    V    │    B    │       ────────           ────────      │  insert │page down│ page up │  home   │  end    │  AltR   │
   └─────────┴─────────┴─────────┴─────────┼─────────┼─────────┼─────────┬─────────┐┌─────────┬─────────┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                           │Medi(Esc)│Nav(Spc) │Mos(TAB) │         ││         │Sym(ENT) │Num(BSpc)│Fun(Del) │
                                           └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */

   [_NAV] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
              KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                                              KC_Y,     KC_UNDO,  KC_CUT,   KC_COPY,  KC_PSTE,
    KC_TAB,   GUI_A,    ALT_S,    SHT_D,    CTL_F,    KC_G,                                              KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT, KC_CAPS,  KC_QUOT,
    KC_DEL,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_MUTE,                       KC_MPLY,  KC_INS,   KC_PGDN,  KC_PGUP,  KC_HOME,  KC_END,   KC_RSFT,
                                            KC_ESC,   KC_SPC,   KC_TAB,   ADJUST,    KC_LGUI,  KC_ENTER, KC_BSPC,  KC_DEL
 ),

/*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸


   ┌───────────────────────────────────────────────────────────┐
   │ a d j u s t                                               │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐   __________________________________   ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │  AUDIO  │ HAPTIC  │ RGB HUE │ RGB MOD │         │  /                                  \  │    Y    │    U    │    I    │    O    │    P    │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ /                                    \ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │  RESET  │  DEBUG  │ QWERTY  │ RGB SAT │         │         |/      ────────           ────────     \│    H    │ Ctl(J)  │Shift(K) │ AltR(L) │ GUI(;)  │    "    │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤      │Mute/Vol│         │PLY/Scrol│    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │  MAKE   │ OS SWAP │ COLEMAK │ RGB VAL │         │         │       ────────           ────────      │    N    │    M    │    ,    │    .    │    /    │  AltR   │
   └─────────┴─────────┴─────────┴─────────┼─────────┼─────────┼─────────┬─────────┐┌─────────┬─────────┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                           │Medi(Esc)│Nav(Spc) │Mos(TAB) │         ││         │Sym(ENT) │Num(BSpc)│Fun(Del) │
                                           └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */
   [_ADJUST] = LAYOUT_polydactyl(
 //╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷╷         ╷         ╷         ╷         ╷         ╷         ╷         ╷
              AU_TOGG,  HF_TOGG,  RGB_HUI,  RGB_MOD,  XXXXXXX,                                           _______,  _______,  _______,  _______,  _______,
    QK_BOOT,  DB_TOGG,  QWERTY,   RGB_SAI,  RGB_VAI,  XXXXXXX,                                           _______,  _______,  _______,  _______,  _______,   _______,
    XXXXXXX,  XXXXXXX,  XXXXXXX,  RGB_SAD,  RGB_VAD,  XXXXXXX,  KC_MUTE,                       KC_MPLY,  _______,  _______,  _______,  _______,  _______,   _______,
//    MAKE_H,   OS_SWAP,  COLEMAK,  RGB_VAI,  XXXXXXX,  XXXXXXX,  KC_MUTE,                       KC_MPLY,  _______,  _______,  _______,  _______,  _______,   _______,
                                            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______)

};


// rgb matix
/*
   ╺━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╸


   ┌───────────────────────────────────────────────────────────┐
   │ led index                                                 │
   └───────────────────────────────────────────────────────────┘
             ┌─────────┬─────────┬─────────┬─────────┬─────────┐   __________________________________   ┌─────────┬─────────┬─────────┬─────────┬─────────┐
             │    18   │    13   │    12   │    06   │    05   │  /                                  \  │    26   │    27   │   33    │   34    │   39    │
   ┌─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤ /                                    \ ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┐
   │    19   │    17   │    14   │    11   │    07   │    04   |/      ────────           ────────     \│    25   │    28   │   32    │   35    │   38    │   40    │
   ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤      │Mute/Vol│         │PLY/Scrol│    ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┤
   │    20   │    16   │    15   │    10   │    08   │    03   │       ────────           ────────      │    24   │    29   │   31    │   36    │   37    │   41    │
   └─────────┴─────────┴─────────┴─────────┼─────────┼─────────┼─────────┬─────────┐┌─────────┬─────────┼─────────┼─────────┼─────────┼─────────┴─────────┴─────────┘
                                           │    09   │    02   │    01   │    00   ││    21   │    22   │    23   │    30   │
                                           └─────────┴─────────┴─────────┴─────────┘└─────────┴─────────┴─────────┴─────────┘ */

#if RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
      for (uint8_t i = 4; i < 7; i++) {
          rgb_matrix_set_color(i, RGB_RED);
      }
      // not possible to change color of the secondary split half in case of caps look
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
            rgb_matrix_set_color(19, RGB_TURQUOISE);
            rgb_matrix_set_color(12, RGB_AZURE);
            rgb_block(10,11, RGB_GREEN);
            rgb_matrix_set_color(6, RGB_CYAN);
            rgb_block(7,8, RGB_BLUE);
            rgb_home_row('r');
            break;
        case _NAV:
            // arrows color: green
            rgb_matrix_set_color(25, RGB_GREEN);
            rgb_matrix_set_color(28, RGB_GREEN);
            rgb_matrix_set_color(32, RGB_GREEN);
            rgb_matrix_set_color(35, RGB_GREEN);
            // caps lock: Azure
            rgb_matrix_set_color(39, RGB_RED);
            // redo and undo: Blue
            rgb_block(26,27, RGB_BLUE);
            // cut, copy and paste: Azure
            rgb_matrix_set_color(39, RGB_AZURE);
            rgb_block(33,34, RGB_AZURE);
            // insert: Orange
            rgb_matrix_set_color(24, RGB_ORANGE);
            // page down and up: Pink
            rgb_matrix_set_color(29, RGB_PINK);
            rgb_matrix_set_color(31, RGB_PINK);
            // home and end: Purple
            rgb_block(36,37, RGB_PURPLE);
            rgb_home_row('l');
            break;
        default:
            rgb_home_row('b');
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
        case _NAV:
            oled_write_P(PSTR("N A V\n"), false);
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

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}


bool oled_task_user(void) {
    if (is_keyboard_master()) {
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_logo();  // Renders a static logo
        oled_scroll_left();  // Turns on scrolling
    }
    return false;
}

#endif

// encoder setup
#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) {
        // Volume control
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        // Page up/Page down
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}
#endif

/*



                                                       ▐█    ▟▛ ▐█     ▄▆▀▀▀▀▀▀▆▄  ▐█▀▀▀▀▀█▌
                                                       ▐█   ▟▛  ▐█    ▟▛        ▜▙ ▐█     █▌
                                                       ▐█  ▟▛   ▐█   ▐█          █▋▐█     █▌
                                                       ▐█ ▟█▙   ▐█   ▐█          █▋▐█▀▀▜█▀▀▘
                                                       ▐█▟▛ ▜▙  ▐█    ▜▙        ▟▛ ▐█   ▜▙
                                                       ▐█▛   ▜▙ ▐█▄▄▄▄ ▀▜▆▄▄▄▄▆▛▀  ▐█    ▜▙

                                                                 ▄██████████████▄
                                                                 ████████████████
                                                            ▄██████▀  ▀████▀  ▀██████▄
                                                            ███████▄  ▄████▄  ▄███████
                                                            ███████████▀▀▀▀███████████
                                                            ▀█████████▀ ▄▄ ▀█████████▀
                                                                 ████▀ ▄██▄ ▀████
                                                                 ████▄▄████▄▄████

*/



