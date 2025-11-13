/*
Copyright 2020 Stanrc85 <stanrc@gmail.com>

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
#include "stanrc85.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_alice(
    KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
    KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_PGDN, KC_CTLE, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
             KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN2_60),
             KC_LCTL,          KC_LALT, LT_BPCF, KC_LGUI,                           LT_SPCF,          KC_RALT,          KC_RCTL
  ),

  [_DEFAULT] = LAYOUT_alice(
    KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
    KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_PGDN, KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
             KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN2_60),
             KC_LCTL,          KC_LALT, KC_SPC,  MO(_FN1_60),                       KC_SPC,           KC_RALT,          KC_RCTL
  ),

  [_FN1_60] = LAYOUT_alice(
    _______, KC_TILD,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,           KC_DEL,
    _______, _______,  _______, CA_QUOT, _______, CA_SCLN, KC_VOLU,          KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PSCR, _______, _______, KC_INS,
    _______, KC_CAPS,  _______, _______, KC_LCTL, KC_LSFT, KC_VOLD,          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______,
             _______,  KC_RDP,  _______, _______, _______, _______,          _______, _______, KC_WBAK, KC_WFWD, _______, _______, _______, _______,
             _______,           _______, _______, _______,                            _______,          _______,          _______
  ),

  [_FN2_60] = LAYOUT_alice(
    BL_TOGG,  _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,          _______,
    _______,   _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
    _______,   _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,          KC_MAKE,
              _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______, _______,
              _______,          _______, _______, _______,                             _______,          _______,          TG(_DEFAULT)
  )
};

//RGB Timeout

static uint32_t key_timer; // timer to track the last keyboard activity
static void refresh_rgb(void); // refreshes the activity timer and RGB, invoke whenever activity happens
static void check_rgb_timeout(void); // checks if enough time has passed for RGB to timeout
bool is_rgb_timeout = false; // store if RGB has timed out or not in a boolean


void refresh_rgb() {
  key_timer = timer_read32(); // store time of last refresh
  if (is_rgb_timeout) { // only do something if rgb has timed out
    print("Activity detected, turning on RGB\n");
    is_rgb_timeout = false;
    rgblight_wakeup();
  }
}

void check_rgb_timeout() {
  if (!is_rgb_timeout && timer_elapsed32(key_timer) > RGBLIGHT_TIMEOUT) {
    rgblight_suspend();
    print("Idle timeout reached, turning off RGB\n");
    is_rgb_timeout = true;
  }
}


void housekeeping_task_user(void) {
  #ifdef RGBLIGHT_TIMEOUT
  check_rgb_timeout();
  #endif
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef RGBLIGHT_TIMEOUT
  if (record->event.pressed) refresh_rgb();
  #endif
}


void post_encoder_update_user(uint8_t index, bool clockwise) {
  #ifdef RGBLIGHT_TIMEOUT
  refresh_rgb();
  #endif
}


//Layer Indicators
layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(INDICATOR_PIN_2, layer_state_cmp(state, 3) || layer_state_cmp(state, 1));
    writePin(INDICATOR_PIN_1, layer_state_cmp(state, 2) || layer_state_cmp(state, 1));
    return state;
}

bool led_update_user(led_t led_state) {
    writePin(INDICATOR_PIN_0, led_state.caps_lock);
    return false;
}

//Startup fanfare

static uint8_t top = 0;
static uint8_t middle = 0;
static uint8_t bottom = 0;

static bool is_enabled = true;
static bool is_rgblight_startup = true;
static uint16_t rgblight_startup_loop_timer;

void matrix_scan_user(void) {
    // Boot up "fanfare"
    if (is_rgblight_startup && is_keyboard_master()) {
        if (timer_elapsed(rgblight_startup_loop_timer) > 10) {
            static uint8_t counter;
            counter++;
            if (counter == 1) {
                top = 1;
                writePin(INDICATOR_PIN_0, top);
                wait_ms(300);
                top = 0;
                writePin(INDICATOR_PIN_0, top);
            }
            if (counter == 2) {
                middle = 1;
                writePin(INDICATOR_PIN_1, middle);
                wait_ms(300);
                middle = 0;
                writePin(INDICATOR_PIN_1, middle);
            }
            if (counter == 3) {
                bottom = 1;
                writePin(INDICATOR_PIN_2, bottom);
                wait_ms(300);
                bottom = 0;
                writePin(INDICATOR_PIN_2, bottom);
            }
            if (counter == 4) {
                is_enabled = is_rgblight_startup = false;
            }
        }
    }
}
