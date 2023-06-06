//#include "Buggy.h"
//#include "gyroDriver.h"
//#include <chrono>
//
//void Buggy::turn(float angle, float speed){
//    float angleTurned = 0;
//    int angleRate = 0;
//    
//    //Rechts drehen
//    if(angle > 0){
//        motorLinks.setCommand(FORWARD);
//        motorLinks.setSpeed(speed);
//        while(angleTurned < angle){
//            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
//            angleRate = gyroskop.readGyroAxis(zAxis);
//            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
//            angleTurned += std::chrono::duration_cast<std::chrono::nanoseconds> (end - begin).count()/1e-9f * angleRate;
//        }
//    }
//    //links drehen
//    else{
//    
//    }
//}