#include <Keyboard.h>
#include "cpu_map.h"

class pad
{
private:
    volatile byte *padRPort;
    byte padBit;
    byte padPin;
    byte debounceTime;
    unsigned long nextReadTime;
    bool _hasChanged;
    char pressedKey;
    char releasedKey;

    void init()
    {
        pinMode(padPin, INPUT_PULLUP);
    }

public:
    bool state; // Indica se o pad está pressionado ou não (true = pressionado, false = não pressionado)

    /**
     * @brief Construtor da classe pad
     *
     * @param _pressedKey (char): Caractere que será enviado ao computador quando o pad for pressionado
     * @param _releasedKey (char): Caractere que será enviado ao computador quando o pad for solto
     * @param _padRPort Ponteiro (volatile byte): para o registrador de leitura do pad
     * @param _padBit (byte): Bit do registrador de leitura do pad
     * @param _padPin (byte): Número do pino do pad
     * @param _debounceTime (byte): Tempo de debounce do pad
     *
     * @example
     * pad('a', 0x00, &PIND, 1, 2, 15);
     */
    pad(char _pressedKey, char _releasedKey, volatile byte *_padRPort, byte _padBit, byte _padPin, byte _debounceTime)
    {
        this->pressedKey = _pressedKey;
        this->releasedKey = _releasedKey;
        this->padRPort = _padRPort;
        this->padBit = _padBit;
        this->padPin = _padPin;
        this->debounceTime = _debounceTime;

        this->init();
    }

    /**
     * @brief Lê e atualiza o estado do pad
     *
     * @return (bool): True se o pad estiver pressionado, false se não estiver
     */
    bool read()
    {
        if (millis() > nextReadTime && !tstBit(*padRPort, padBit) != state)
        {
            state = !state;
            _hasChanged = true;
            nextReadTime = millis() + debounceTime;
        }

        return state;
    }

    /**
     * @brief Verifica se o estado do pad mudou
     *
     * @return (bool): True se o estado do pad mudou, false se não mudou
     */
    bool hasChanged()
    {
        read();
        if (_hasChanged)
        {
            _hasChanged = false;
            return true;
        }
        return false;
    }

    /**
     * @brief Verifica se o pad está pressionado
     *
     * @return (bool): True se o pad estiver pressionado, false se não estiver
     */
    bool isPressed()
    {
        return read();
    }

    /**
     * @brief Verifica se o pad está solto
     *
     * @return (bool): True se o pad estiver solto, false se não estiver
     */
    bool isReleased()
    {
        return !read();
    }

    /**
     * @brief Verifica se o pad foi pressionado (borda de subida)
     *
     * @return (bool): True se o pad foi pressionado, false se não foi
     */
    bool risingEdge()
    {
        return hasChanged() && isPressed();
    }

    /**
     * @brief Verifica se o pad foi solto (borda de descida)
     *
     * @return (bool): True se o pad foi solto, false se não foi
     */
    bool fallingEdge()
    {
        return hasChanged() && isReleased();
    }

    /**
     * Processa o estado do pad, pressionando e soltando as teclas necessárias
     */
    void proccess()
    {
        if (risingEdge())
        {
            Keyboard.release(releasedKey);
            Keyboard.press(pressedKey);
            DebugLog(pressedKey);
        }
        else if (fallingEdge())
        {
            Keyboard.release(pressedKey);
            Keyboard.press(releasedKey);
            DebugLog(releasedKey);
        }
    }
};
