#include QMK_KEYBOARD_H

#include "oled.h"

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
};

/* Custom keycodes shared across keymaps. */
enum custom_keycodes {
  ALT_TAB = SAFE_RANGE,
};

static int8_t alt_tab_layer = -1;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY (BASE)
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  =   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | BSP  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                 | LAlt | LCtrl | lower| /Space  /       \ Enter\  | raise | RAlt  | CMD  |
 *                 |      |       |      |/       /         \      \ |       |       |      |
 *                 `---------------------''------'           '------''----------------------'
 */
  [_QWERTY] = LAYOUT(
    KC_EQL,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,
    KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,                         KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_BSPC,
    KC_ESC,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,                         KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_WBAK,  KC_WFWD,  KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,
                              KC_LALT,  KC_LCTL,  MO(_LOWER),   KC_SPC,   KC_ENT,   MO(_RAISE),   KC_RALT,  KC_RGUI
  ),

  /* LOWER LAYER */
  [_LOWER] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
    ALT_TAB,  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,                      KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______,
    _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_PIPE,  KC_UNDS,  KC_PLUS,  KC_LBRC,  KC_RBRC,  KC_TILD,
    _______,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    _______,     _______,  KC_BSLS,  KC_MINS,  KC_EQL,   KC_LCBR,  KC_RCBR,  KC_GRV,
                                  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
  ),

  /* RAISE LAYER*/
  [_RAISE] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
    KC_CAPS,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,                         KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_DEL,
    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,                        KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,  KC_F11,   _______,
    _______,  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   _______,  _______,  KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   KC_F12,   KC_INS,
                                  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
  ),

  /* ADJUST LAYER*/
  [_ADJUST] = LAYOUT(
    _______,  _______,  _______,  _______,  _______,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  KC_MPLY,  KC_VOLU,  KC_MSTP,  _______,                      EE_CLR,  QK_BOOT,  _______,  _______,  _______,  _______,
    _______,  _______,  KC_MPRV,  KC_VOLD,  KC_MNXT,  _______,                      _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  KC_MUTE,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
                                  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
  ),
};


__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) { return state; }
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

layer_state_t layer_state_set_user(layer_state_t state) {
    state = layer_state_set_keymap(state);
    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
    if (alt_tab_layer >= 0 && !layer_state_cmp(state, alt_tab_layer)) {
        unregister_code(KC_LALT);
        alt_tab_layer = -1;
    }
    return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_keymap(keycode, record)) {
        return false;
    }
    switch (keycode) {
        /* Alt+Tab that holds Alt until current layer is released: */
        case ALT_TAB:
            if (record->event.pressed) {
                if (alt_tab_layer < 0) {
                    alt_tab_layer = layer_switch_get_layer(record->event.key);
                    register_code(KC_LALT);
                }
                register_code(KC_TAB);
            } else {
                unregister_code(KC_TAB);
            }
            return false;
        default:
            return true;
    }
}
