// hid_mouse.h
//

void HID_MOUSE_Init();

void HID_MOUSE_ProcessData();

void HID_MouseMenuProcess(void);

void HID_MOUSE_ButtonPressed(uint8_t button_idx);
void HID_MOUSE_ButtonReleased(uint8_t button_idx);
