
#include "Display.h"

Display::Display()
{
    display->setBrightness(0x0a);
}

void Display::update()
{
    if (!needsUpdate)
        return;
    needsUpdate = false;
    display->setSegments(digits, 4, 0);
}

void Display::setDigits(byte d0, byte d1, byte d2, byte d3)
{
    digits[0] = d0;
    digits[1] = d1;
    digits[2] = d2;
    digits[3] = d3;
    needsUpdate = true;
}

void Display::clear()
{
    setDigits(0, 0, 0, 0);
}

void Display::write(const char *text)
{
    clear();
    int lenght = min(4, (int)strlen(text));
    for (int i = 0; i < lenght; i++)
    {
        digits[i] = digitFor(text[i]);
    }
    needsUpdate = true;
}

void Display::write(char *text)
{
    clear();
    int lenght = min(4, (int)strlen(text));
    for (int i = 0; i < lenght; i++)
    {
        digits[i] = digitFor(text[i]);
    }
    needsUpdate = true;
}

void Display::writeValue(int value)
{
    clear();
    
    uint8_t val1000 = value / 1000;
    if (val1000 > 0)
    {
        digits[0] = digitFor(val1000);
    }

    uint8_t val100 = (value - (val1000 * 1000)) / 100;
    if (val1000 > 0 || val100 > 0)
    {
        digits[1] = digitFor(val100);
    }

    uint8_t val10 = (value - (val1000 * 1000) - (val100 * 100)) / 10;
    if (val1000 > 0 || val100 > 0 || val10 > 0)
    {
        digits[2] = digitFor(val10);
    }

    uint8_t val1 = value - (val1000 * 1000) - (val100 * 100) - (val10 * 10);
    digits[3] = digitFor(val1);

    needsUpdate = true;
}

void Display::writeTitleValue(const char title, uint8_t value)
{
    clear();
    digits[0] = digitFor(title);

    uint8_t val100 = value / 100;
    if (val100 > 0)
    {
        digits[1] = digitFor(val100);
    }

    uint8_t val10 = (value - (val100 * 100)) / 10;
    if (val10 > 0)
    {
        digits[2] = digitFor(val10);
    }

    uint8_t val1 = value - (val100 * 100) - (val10 * 10);
    digits[3] = digitFor(val1);

    needsUpdate = true;
}

void Display::writeTitle2Value(const char title, const char title2, uint8_t value)
{
    clear();
    digits[0] = digitFor(title);
    digits[1] = digitFor(title2);

    uint8_t val10 = value / 10;
    if (val10 > 0)
    {
        digits[2] = digitFor(val10);
    }

    uint8_t val1 = value - (val10 * 10);
    digits[3] = digitFor(val1);

    needsUpdate = true;
}

//
//      A
//     ---
//  F |   | B
//     -G-
//  E |   | C
//     ---
//      D
byte Display::digitFor(char character)
{
    switch (character)
    {
    //                XGFEDCBA
    case 0:
        return 0b00111111; // 0
    case 1:
        return 0b00000110; // 1
    case 2:
        return 0b01011011; // 2
    case 3:
        return 0b01001111; // 3
    case 4:
        return 0b01100110; // 4
    case 5:
        return 0b01101101; // 5
    case 6:
        return 0b01111101; // 6
    case 7:
        return 0b00000111; // 7
    case 8:
        return 0b01111111; // 8
    case 9:
        return 0b01101111; // 9
    case '0':
        return 0b00111111; // 0
    case '1':
        return 0b00000110; // 1
    case '2':
        return 0b01011011; // 2
    case '3':
        return 0b01001111; // 3
    case '4':
        return 0b01100110; // 4
    case '5':
        return 0b01101101; // 5
    case '6':
        return 0b01111101; // 6
    case '7':
        return 0b00000111; // 7
    case '8':
        return 0b01111111; // 8
    case '9':
        return 0b01101111; // 9
    case 'a':
        return 0b01110111; // A
    case 'b':
        return 0b01111100; // B
    case 'c':
        return 0b00111001; // C
    case 'd':
        return 0b01011110; // D
    case 'e':
        return 0b01111001; // E
    case 'f':
        return 0b01110001; // F
    case 'g':
        return 0b00111101; // G
    case 'h':
        return 0b01110110; // H
    case 'k':
        return 0b01110110; // K
    case 'i':
        return 0b00000110; // I
    case 'j':
        return 0b00001110; // J
    case 'l':
        return 0b00111000; // L
    case 'm':
        return 0b00110111; // M
    case 'n':
        return 0b01010100; // N
    case 'o':
        return 0b00111111; // O
    case 'p':
        return 0b01110011; // P
    case 'q':
        return 0b01011100; // Q
    case 'r':
        return 0b01010000; // R
    case 's':
        return 0b01101101; // S
    case 't':
        return 0b01111000; // T
    case 'u':
        return 0b00111110; // U
    case 'v':
        return 0b00011100; // V
    case 'w':
        return 0b00011100; // W
    case 'x':
        return 0b01110110; // X
    case 'y':
        return 0b01100110; // Y
    case 'z':
        return 0b01011011; // Z
    case '.':
        return 0b10000000; // .
    case '=':
        return 0b01001001; // =
    case '#':
        return 0b01110110; // H
    }
    return 0b00000000;
}