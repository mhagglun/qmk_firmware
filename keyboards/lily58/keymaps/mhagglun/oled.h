#pragma once

#ifdef OLED_ENABLE
#include "quantum.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation);
bool oled_task_user(void);

const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);
#endif // OLED_ENABLE
