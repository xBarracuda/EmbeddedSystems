#define xAxis 0
#define yAxis 1
#define zAxis 2

#define gyroAxisAddr 0x43

class Gyro {
public: 
	int readGyroAxis(int axis);
};