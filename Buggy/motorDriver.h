#define LED_Base   0b00000110

#define LED_ENABLE 4095
#define LED_DISABLE 0

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