#define xAxis 0
#define yAxis 1
#define zAxis 2

#define gyroAxisAddr 0x43

class Gyro {
public: 
	int16_t readGyroAxis(int axis);
	void initializeGyro();
	int16_t read16bitRegister(int adress);
	//Buffer readAxis();
};

struct Buffer {
	int16_t xAchse;
	int16_t yAchse;
	int16_t zAchse;
};