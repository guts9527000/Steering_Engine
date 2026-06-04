#include "global.h"

Mode mode = Manual;
static  uint8_t manual_first = 1;
static uint8_t scan_first = 1;
static uint8_t middle_first = 1;

void Mode_Set(void) {
	switch (double_click) {
	    case 0:
			mode = Manual;
			break;
		case 1:
			mode = Middle;
			break;
		case 2:
			mode = Scan;
			break;
			default:
			break;
	}
}

static void Mode_Manual(void) {
	Led_Mode(Manual);
	scan_first = 1;
	middle_first = 1;
	if (manual_first) {
		tim = 0;
		encoder_btn_pressed = 0;
		flicker_bit = 0;
		manual_first = 0;
	}
    if (encoder_btn_pressed) {
        encoder_btn_pressed = 0;
        flicker_bit++;
        if (flicker_bit > 3) {
            flicker_bit = 0;
        }
    }
    if (encoder_count >= 0) {
        Servo_SetAngle(encoder_count);
        Display_3Digit(encoder_count);
    }
}

static void Mode_Middle(void) {
	Led_Mode(Middle);
	manual_first = 1;
	scan_first = 1;
	if (middle_first) {
		tim = 0;
		middle_first = 0;
		flicker_bit = 0;
	}
	Servo_SetAngle(encoder_count);
	Display_3Digit(encoder_count);
}

static void Mode_Scan(void) {
	Led_Mode(Scan);
	manual_first = 1;
	middle_first = 1;
	if (scan_first) {
		tim = 0;
		scan_first = 0;
		flicker_bit = 0;
	}
	Servo_SetAngle(encoder_count);
	Display_3Digit(servo_speed);
}

static ModeHandlerMap Mode_Table[] = {
    {Manual, Mode_Manual},
    {Middle, Mode_Middle},
	{Scan, Mode_Scan}
};

static uint8_t Mode_Count = sizeof(Mode_Table) / sizeof(ModeHandlerMap);

void Mode_Process(void) {
	Mode_Set();
	for (uint8_t i = 0; i < Mode_Count; i++) {
	    if (mode == Mode_Table[i].mode) {
	        Mode_Table[i].handler();
			return;
	    }
	}
}