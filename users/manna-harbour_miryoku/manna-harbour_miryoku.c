// Copyright 2019 Manna Harbour
// https://github.com/manna-harbour/miryoku

// This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 2 of the License, or (at your option) any later version. This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details. You should have received a copy of the GNU General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.

#include QMK_KEYBOARD_H

#include "manna-harbour_miryoku.h"

enum layers { MIRYOKU_LAYER_NAMES };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE]   = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_BASE),
  [NAV]    = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_NAV),
  [MOUSE]  = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_MOUSE),
  [MEDIA]  = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_MEDIA),
  [NUM]    = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_NUM),
  [SYM]    = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_SYM),
  [FUN]    = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_FUN),
  [BUTTON] = U_MACRO_VA_ARGS(LAYOUT_miryoku, MIRYOKU_LAYER_BUTTON)
};

#ifdef OLED_ENABLE

void render_status(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case BASE   : oled_write_P(PSTR("BASE  \n"), false); break;
        case NAV    : oled_write_P(PSTR("NAV   \n"), false); break;
        case MOUSE  : oled_write_P(PSTR("MOUSE \n"), false); break;
        case MEDIA  : oled_write_P(PSTR("MEDIA \n"), false); break;
        case NUM    : oled_write_P(PSTR("NUM   \n"), false); break;
        case SYM    : oled_write_P(PSTR("SYM   \n"), false); break;
        case FUN    : oled_write_P(PSTR("FUN   \n"), false); break;
        case BUTTON : oled_write_P(PSTR("BUTTON\n"), false); break;
    }
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(is_caps_word_on() ? PSTR("CAPS_WORD ") : PSTR("          "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
}

static void render_logo(void) {
    oled_write_P(PSTR("\nFREDERICK ADAN"),false);
    oled_write_P(PSTR("\nAKA DADDY POGI"),false);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        //oled_rotation = (swap_hands?OLED_ROTATION_180:OLED_ROTATION_0);
        render_status();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        //oled_rotation = (swap_hands?OLED_ROTATION_0:OLED_ROTATION_180);
        render_logo();  // Renders a static logo
        oled_scroll_left();  // Turns on scrolling
    }

    return false;
}

#endif

#if defined (MIRYOKU_KLUDGE_THUMBCOMBOS)
const uint16_t PROGMEM thumbcombos_base_right[] = {LT(SYM, KC_ENT), LT(NUM, KC_BSPC), COMBO_END};
const uint16_t PROGMEM thumbcombos_base_left[] = {LT(NAV, KC_SPC), LT(MOUSE, KC_TAB), COMBO_END};
const uint16_t PROGMEM thumbcombos_nav[] = {KC_ENT, KC_BSPC, COMBO_END};
const uint16_t PROGMEM thumbcombos_mouse[] = {KC_BTN1, KC_BTN3, COMBO_END};
const uint16_t PROGMEM thumbcombos_media[] = {KC_MSTP, KC_MPLY, COMBO_END};
const uint16_t PROGMEM thumbcombos_num[] = {KC_0, KC_MINS, COMBO_END};
  #if defined (MIRYOKU_LAYERS_FLIP)
const uint16_t PROGMEM thumbcombos_sym[] = {KC_UNDS, KC_LPRN, COMBO_END};
  #else
const uint16_t PROGMEM thumbcombos_sym[] = {KC_RPRN, KC_UNDS, COMBO_END};
  #endif
const uint16_t PROGMEM thumbcombos_fun[] = {KC_SPC, KC_TAB, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {
  COMBO(thumbcombos_base_right, LT(FUN, KC_DEL)),
  COMBO(thumbcombos_base_left, LT(MEDIA, KC_ESC)),
  COMBO(thumbcombos_nav, KC_DEL),
  COMBO(thumbcombos_mouse, KC_BTN2),
  COMBO(thumbcombos_media, KC_MUTE),
  COMBO(thumbcombos_num, KC_DOT),
  #if defined (MIRYOKU_LAYERS_FLIP)
  COMBO(thumbcombos_sym, KC_RPRN),
  #else
  COMBO(thumbcombos_sym, KC_LPRN),
  #endif
  COMBO(thumbcombos_fun, KC_APP)
};
#endif
