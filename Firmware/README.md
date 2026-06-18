# Duck Keyboard Firmware

This firmware implements a 4x13 keyboard matrix on the ESP32 Feather HUZZAH32 and exposes a BLE HID keyboard device.

## Pin mapping

- Rows: GPIO21, GPIO14, GPIO32, GPIO13
- Columns: GPIO26, GPIO25, GPIO34, GPIO39, GPIO36, GPIO4, GPIO5, GPIO18, GPIO19, GPIO16, GPIO17, GPIO22, GPIO23

## Build instructions

1. Install the ESP32 Arduino core for the Arduino IDE or Visual Studio Code PlatformIO.
2. Install the `ESP32 BLE Keyboard` library.
3. Open `Firmware/DuckKeyboard.ino`.
4. Select the `Adafruit ESP32 Feather` board or equivalent ESP32 board.
5. Upload the sketch.

## Keymap

The default keymap is arranged as a 4x13 layout:

- Row 0: ESC, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, -, =
- Row 1: TAB, Q, W, E, R, T, Y, U, I, O, P, [, ]
- Row 2: CAPS LOCK, A, S, D, F, G, H, J, K, L, ;, ', ENTER
- Row 3: LEFT SHIFT, Z, X, C, V, B, N, M, ,, ., /, SPACE, BACKSPACE

## Notes

- If you want a custom layout, edit the `keymap` table in `DuckKeyboard.ino`.
- The keyboard uses internal pull-ups on the column pins and drives one row low at a time.
- Audio/quack effects are not implemented in this initial firmware.
