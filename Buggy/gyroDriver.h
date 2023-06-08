#pragma once

#define xAxis 0
#define yAxis 1
#define zAxis 2

#define gyroAxisAddr 0x43

#define KalibirierungsIteration 500
#define BitToDegree 0.0152592f
#define BitToDegreeNegative 0.0152587f

class Gyro {
private:
	short x_offset;
	short y_offset;
	short z_offset;
	float relativeAngle[3];
	bool isMeasuring;

public: 
	float readGyroAxis(int axis);
	void initializeGyro();
	short read16bitRegister(int adress);
	void startMeasurement();
	void updateMeasurement();
	void endMeasurement();
	float getRelativeAngle(int axis);
};

