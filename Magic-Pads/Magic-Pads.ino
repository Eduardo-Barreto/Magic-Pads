// PRECISA DE TESTES!
#define DEBUG_LOG 1

#if DEBUG_LOG == 1
#define DebugInit(x) Serial.begin(x)
#define DebugLog(x) Serial.print(String(x))
#define DebugLogln(x) Serial.println(String(x))
#else
#define DebugInit(x)
#define DebugLog(x)
#define DebugLogln(x)
#endif

#include "cpu_map.h"
#include "pad.h"

// teclas em https://github.com/arduino-libraries/Keyboard/blob/master/src/Keyboard.h

pad pads[] = {
    // Pressed Key, Released Key, Port, Bit, Pin, Debounce Time
    {'t', 0x00, &pad_1_rPort, pad_1_bit, pad_1_pin, 15},
    {'y', 0x00, &pad_2_rPort, pad_2_bit, pad_2_pin, 15},
    {'u', 0x00, &pad_3_rPort, pad_3_bit, pad_3_pin, 15},
    {'i', 0x00, &pad_4_rPort, pad_4_bit, pad_4_pin, 15},
    {'o', 0x00, &pad_5_rPort, pad_5_bit, pad_5_pin, 15}};

void setup()
{
    pinMode(enable_pin, INPUT_PULLUP);
    DebugInit(9600);
    delay(500);

    DebugLogln("Aguardando enable...");
    while (tstBit(enable_rPort, enable_bit))
    {
    }
    DebugLogln("Pronto!");
}

void loop()
{
    for (pad p : pads)
    {
        p.proccess();
        DebugLog("\t");
    }
    DebugLogln();
}
