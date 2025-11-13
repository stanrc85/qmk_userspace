/* Copyright 2021 Harrison Chan (Xelus)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_all(
    KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  _______, KC_BSPC,
    KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_PGDN, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
             KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(3),
             KC_LCTL,          KC_LALT, KC_SPC, KC_LGUI,                           KC_SPC,          KC_RALT,          KC_RCTL
  ),

  [1] = LAYOUT_all(
    KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  _______, KC_BSPC,
    KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_PGDN, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
             KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(3),
             KC_LCTL,          KC_LALT, KC_SPC,  MO(2),                       KC_SPC,           KC_RALT,          KC_RCTL
  ),

  [2] = LAYOUT_all(
    _______, KC_TILD,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, KC_DEL,
    _______, _______,  _______, _______, _______, _______, KC_VOLU,          KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PSCR, _______, _______, KC_INS,
    _______, KC_CAPS,  _______, _______, KC_LCTL, KC_LSFT, KC_VOLD,          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______,
             _______,  _______,  _______, _______, _______, _______,          _______, _______, KC_WBAK, KC_WFWD, _______, _______, _______, _______,
             _______,           _______, _______, _______,                            _______,          _______,          _______
  ),

  [3] = LAYOUT_all(
    BL_TOGG,  RGB_TOG, RGB_MOD, RGB_VAD, RGB_VAI, RGB_SAI, RGB_HUD,  RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______,
    _______,   _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
    _______,   _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,          _______,
              _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______, _______,
              _______,          _______, _______, _______,                             _______,          _______,          TG(1)
  )
};

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    // caps lock red
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(27, 255, 0, 0); //caps lock led
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(27, 0, 0, 0); //caps lock led
    }   

    // num lock cyan
    if (host_keyboard_led_state().num_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(26, 0, 128, 128);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(26, 0, 0, 0);
    }

    // scroll lock cyan
    if (host_keyboard_led_state().scroll_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(25, 0, 128, 128);
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(25, 0, 0, 0);
    }

    // layer state
    switch (get_highest_layer(layer_state)) {
        case 0:
            RGB_MATRIX_INDICATOR_SET_COLOR(24, 0, 0, 0);
            break;
        case 1:
            RGB_MATRIX_INDICATOR_SET_COLOR(24, 0, 255, 0);
            break;
        case 2:
            RGB_MATRIX_INDICATOR_SET_COLOR(24, 0, 128, 255);
            break;
        case 3:
            RGB_MATRIX_INDICATOR_SET_COLOR(24, 255, 255, 255);
            break;
        default:
            // white
            RGB_MATRIX_INDICATOR_SET_COLOR(24, 128, 128, 128);
            break;
    }
    return false;
}
#endif

