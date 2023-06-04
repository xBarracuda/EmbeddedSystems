#define xAxis 0
#define yAxis 1
#define zAxis 2

#define gyroAxisAddr 0x43

class Gyro {
private:
	short x_offset;
	short y_offset;
	short z_offset;
public: 
	short readGyroAxis(int axis);
	void initializeGyro();
	short read16bitRegister(int adress);
	//Buffer readAxis();
};

//struct Buffer {
//	int16_t xAchse;
//	int16_t yAchse;
//	int16_t zAchse;
//};