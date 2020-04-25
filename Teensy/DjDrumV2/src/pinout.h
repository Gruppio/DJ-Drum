#ifndef PINOUT_H
#define PINOUT_H

// PADS
#define PIN_PAD18 A9
#define PIN_PAD17 A12
#define PIN_PAD16 A6
#define PIN_PAD15 A8
#define PIN_PAD14 A7
#define PIN_PAD13 A4
#define PIN_PAD12 A2
#define PIN_PAD11 A5
#define PIN_PAD10 A3
#define PIN_PAD9 A0
#define PIN_PAD8 A21
#define PIN_PAD7 A1
#define PIN_PAD6 A22
#define PIN_PAD5 A19
#define PIN_PAD4 A17
#define PIN_PAD3 A20
#define PIN_PAD2 A18
#define PIN_PAD1 A16

#define PIN_PAD19 A14
#define PIN_PAD20 A13
#define PIN_PAD21 A15

#define NUM_PADS 1

// uint8_t pinPads[] = {
//     PIN_PAD1,
//     PIN_PAD2,
//     PIN_PAD3,
//     PIN_PAD4,
//     PIN_PAD5,
//     PIN_PAD6,
//     PIN_PAD7,
//     PIN_PAD8,
//     PIN_PAD9,
//     PIN_PAD10,
//     PIN_PAD11,
//     PIN_PAD12,
//     PIN_PAD13,
//     PIN_PAD14,
//     PIN_PAD15,
//     PIN_PAD16,
//     PIN_PAD17,
//     PIN_PAD18
// };

uint8_t pinPads[] = {
    PIN_PAD18
};



// CONTROL BUTTONS
#define PIN_BUTTON1 D7
#define PIN_BUTTON2 D6
#define PIN_BUTTON3 D5
#define PIN_BUTTON4 D10
#define PIN_BUTTON5 D9
#define PIN_BUTTON6 D8

// FOOT SWITCHES
#define PIN_FOOTSWITCH1 D24
#define PIN_FOOTSWITCH2 D25
#define PIN_FOOTSWITCH3 D26
#define PIN_FOOTSWITCH4 D12
#define PIN_FOOTSWITCH5 D28
#define PIN_FOOTSWITCH6 D27
#define PIN_FOOTSWITCH7 D30
#define PIN_FOOTSWITCH8 D29

// RGB
#define PIN_RGB1 A15
#define PIN_RGB2 A15

// I2C
#define PIN_SDA D4
#define PIN_SCL D3

// UART
#define PIN_RX D0
#define PIN_TX D1

#endif