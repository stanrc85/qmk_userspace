/* Copyright 2020 Team Mechlovin
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

enum my_keycodes {
  BL_TOG = QK_KB_0,
  BL_EFFECT,
  BL_ISPD,
  BL_DSPD,
  BL_IHUE,
  BL_DHUE,
  BL_ISAT,
  BL_DSAT,
  BL_IVAL,
  BL_DVAL
};

layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(C15, layer_state_cmp(state, 2) || layer_state_cmp(state, 1));
    writePin(B9, layer_state_cmp(state, 3) || layer_state_cmp(state, 1));
    return state;
}

bool led_update_user(led_t led_state) {
    writePin(B2, led_state.caps_lock);
    return false;
}

bool suspended = false;
void housekeeping_task_user(void) {
    if (last_matrix_activity_elapsed() > RGBLIGHT_TIMEOUT)
    {
        rgblight_suspend();
        suspended = true;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_alice(
    KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
    KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_PGDN, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
             KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(3),
             KC_LCTL,          KC_LALT, KC_SPC, KC_LGUI,                           KC_SPC,          KC_RALT,          KC_RCTL
  ),

  [1] = LAYOUT_alice(
    KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
    KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_PGDN, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
             KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(3),
             KC_LCTL,          KC_LALT, KC_SPC,  MO(2),                       KC_SPC,           KC_RALT,          KC_RCTL
  ),

  [2] = LAYOUT_alice(
    _______, KC_TILD,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
    _______, _______,  _______, _______, _______, _______, KC_VOLU,          KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PSCR, _______, _______, KC_INS,
    _______, KC_CAPS,  _______, _______, KC_LCTL, KC_LSFT, KC_VOLD,          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______,
             _______,  _______,  _______, _______, _______, _______,          _______, _______, KC_WBAK, KC_WFWD, _______, _______, _______, _______,
             _______,           _______, _______, _______,                            _______,          _______,          _______
  ),

  [3] = LAYOUT_alice(
    BL_TOGG,  RGB_TOG, RGB_MOD, RGB_VAD, RGB_VAI, RGB_SAI, RGB_HUD,  RGB_HUI, _______, _______, _______, _______, _______, _______,          _______,
    _______,   _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
    _______,   _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,          _______,
              _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______, _______,
              _______,          _______, _______, _______,                             _______,          _______,          TG(1)
  )
};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLD);
        } else {
            tap_code(KC_VOLU);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_LEFT);
        } else {
            tap_code(KC_RGHT);
        }
    } else if (index == 2) {
        if (clockwise) {
            tap_code(KC_UP);
        } else {
            tap_code(KC_DOWN);
        }
    }
    return true;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
#ifdef RGB_MATRIX_ENABLE
            case BL_TOG: // toggle rgb matrix
                rgb_matrix_toggle();
                return false;
            case BL_EFFECT:
                rgb_matrix_step();
                return false;
            case BL_ISPD:
                rgb_matrix_increase_speed();
                return false;
            case BL_DSPD:
                rgb_matrix_decrease_speed();
                return false;
            case BL_IHUE:
                rgb_matrix_increase_hue();
                return false;
            case BL_DHUE:
                rgb_matrix_decrease_hue();
                return false;
            case BL_ISAT:
                rgb_matrix_increase_sat();
                return false;
            case BL_DSAT:
                rgb_matrix_decrease_sat();
                return false;
            case BL_IVAL:
                rgb_matrix_increase_val();
                return false;
            case BL_DVAL:
                rgb_matrix_decrease_val();
                return false;
#endif
            default:
                break;
        }
    }
    return true;
}
