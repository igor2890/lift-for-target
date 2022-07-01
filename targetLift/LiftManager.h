#ifndef LiftManager_h
#define LiftManager_h

#include "SensorsManager.h"

class LiftManager {
  private:
    SensorsManager * _sensorManager;
    int _stepsOneWay;
    void _setDirectionUp();
    void _setDirectionDown();
    void _makeStep();
public:
    LiftManager(SensorsManager * sensorManager, int stepsOneWay);
    void configurePins();
    void calibrationLift();
    void moveTargetsUp();
    void moveLiftUp(int);
    void moveLiftDown();
};
#endif
