/* Copyright 2024 Cipulot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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
#include "keyboards/cipulot/ec_alice/ec_switch_matrix.h"

// Tap dance: double-tap Left Shift to toggle Caps Lock
enum {
  TD_LSFT_CAPS,
  TD_ALT_SPC_LGUI,
};

void dance_lshift_caps_finished(tap_dance_state_t *state, void *user_data);
void dance_lshift_caps_reset(tap_dance_state_t *state, void *user_data);

void dance_alt_spc_finished(tap_dance_state_t *state, void *user_data);
void dance_alt_spc_reset(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
  [TD_LSFT_CAPS] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_lshift_caps_finished, dance_lshift_caps_reset),
  [TD_ALT_SPC_LGUI] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_alt_spc_finished, dance_alt_spc_reset),
};

static bool lsft_registered = false;
static bool lgui_registered = false;

void dance_lshift_caps_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    // Single tap: behave as regular Shift when held, or a tap when quickly pressed
    if (state->pressed) {
      register_code(KC_LSFT);
      lsft_registered = true;
    } else {
      tap_code(KC_LSFT);
    }
  } else if (state->count == 2) {
    // Double tap: toggle Caps Lock
    tap_code(KC_CAPS);
  }
}

void dance_lshift_caps_reset(tap_dance_state_t *state, void *user_data) {
  if (lsft_registered) {
    unregister_code(KC_LSFT);
    lsft_registered = false;
  }
}

void dance_alt_spc_finished(tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->pressed) {
      register_code(KC_LGUI);
      lgui_registered = true;
    } else {
      register_code(KC_LALT);
      tap_code(KC_SPC);
      unregister_code(KC_LALT);
    }
  } else {
    // For multiple taps, treat like a single tap (send Alt+Space)
    register_code(KC_LALT);
    tap_code(KC_SPC);
    unregister_code(KC_LALT);
  }
}

void dance_alt_spc_reset(tap_dance_state_t *state, void *user_data) {
  if (lgui_registered) {
    unregister_code(KC_LGUI);
    lgui_registered = false;
  }
}

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

enum my_layers {
  _NUMPAD = 0,  //Macropad numpad
  _NAVKEY,      //Macropad nav keys
  _MEDIA,       //Macropad media controls
  _RGB,         //Macropad RGB controls
  _FN1PAD,      //Macropad reset and make commands
  _QWERTY = 0,  //Qwerty with custom shortcuts and functions
  _DEFAULT,     //Default ANSI for gaming, enable with FN2+RCtl
  _FN1_60,      //Function keys, arrows, custom shortcuts, volume control
  _FN2_60       //RGB Underglow controls and RESET
};

//Aliases for longer keycodes
#define KC_CAD	LALT(LCTL(KC_DEL))
#define KC_LOCK	LGUI(KC_L)
#define CA_QUOT LCA(KC_QUOT)
#define CA_SCLN LCA(KC_SCLN)
#define KC_CTLE LCTL_T(KC_ESC)
#define LT_SPCF LT(_FN1_60, KC_SPC)
#define LT_BPCF LT(_FN1_60, KC_BSPC)
#define CA_COPY LCTL(KC_C)
#define CA_PSTE LCTL(KC_V)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_alice(
    KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,           KC_BSPC,
    KC_PGUP, KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    KC_PGDN, KC_CTLE, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
             TD(TD_LSFT_CAPS), KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_B,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, MO(_FN2_60),
             KC_LCTL,          KC_LALT, LT_SPCF, TD(TD_ALT_SPC_LGUI),  LT_SPCF,          KC_RALT,          KC_RCTL
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
    _______, _______,  _______, _______, _______, _______, KC_VOLU,          KC_PGUP, KC_BSPC, KC_UP,   KC_DEL,  KC_PSCR, _______, _______, KC_INS,
    _______, KC_CAPS,  _______, _______, _______, _______, KC_VOLD,          KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______,
             _______,  _______,  _______, _______, _______, _______,          _______, _______, _______, LCA(KC_COMM), LCA(KC_DOT), _______, _______, _______,
             _______,           _______, _______, _______,                            _______,          _______,          _______
  ),

  [_FN2_60] = LAYOUT_alice(
    RM_TOGG,  _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, _______,          _______,
    RM_NEXT,  _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______, QK_BOOT,
    RM_PREV, _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______,          _______,
              _______, _______, _______, _______, _______, _______,           _______, _______, _______, _______, _______, _______, _______, _______,
              _______,          _______, _______, _______,                             _______,          _______,          TG(_DEFAULT)
  )
};
