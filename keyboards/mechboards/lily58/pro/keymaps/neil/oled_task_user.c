#include "quantum.h"
#include "oled_driver.h"

bool oled_task_user(void) {
    oled_write_ln(PSTR("TEST"), false);
    return false;
}
