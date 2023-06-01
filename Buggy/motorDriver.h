#define LED_Base   0b00000110
#define LED8_ON_L  LED_Base + 8*4 
#define LED8_ON_H  LED8_Base + 1
#define LED8_OFF_L LED8_Base + 2
#define LED8_OFF_H LED8_Base + 3

#define LED9_Base  LED_Base + 9*4 
#define LED9_ON_L  LED9_Base
#define LED9_ON_H  LED9_Base + 1
#define LED9_OFF_L LED9_Base + 2
#define LED9_OFF_H LED9_Base + 3

#define LED10_Base  LED_Base + 10*4 
#define LED10_ON_L  LED10_Base
#define LED10_ON_H  LED10_Base + 1
#define LED10_OFF_L LED10_Base + 2
#define LED10_OFF_H LED10_Base + 3

#define LED11_Base  LED_Base + 11*4 
#define LED11_ON_L  LED11_Base
#define LED11_ON_H  LED11_Base + 1
#define LED11_OFF_L LED11_Base + 2
#define LED11_OFF_H LED11_Base + 3

#define LED12_Base  LED_Base + 12*4
#define LED12_ON_L  LED12_Base
#define LED12_ON_H  LED12_Base +1
#define LED12_OFF_L LED12_Base +2
#define LED12_OFF_H LED12_Base +3

#define LED13_Base  LED_Base + 13*4
#define LED13_ON_L  LED13_Base
#define LED13_ON_H  LED13_Base +1
#define LED13_OFF_L LED13_Base +2
#define LED13_OFF_H LED13_Base +3

#define LED_ENABLE 4095
#define LED_DISABLE 0

#define LED_ENABLE_L 0xff
#define LED_ENABLE_H 0x0f

#define LED_DISABLE_L 0x00
#define LED_DISABLE_H 0x00

#define FORWARD 0
#define BACKWARD 1
#define BREAK 2
#define RELEASE 3

void setLEDPin(int number, int valueOn, int valueOff);

class Motor{
    private:
    int pwmPin = 0;
    int in1Pin = 0;
    int in2Pin = 0;

    public:
    Motor(int motorIndex);
    void setSpeed(float speed);
    void setCommand(int command);
};