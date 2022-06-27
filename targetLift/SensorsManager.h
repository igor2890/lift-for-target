#ifndef SensorsManager_h
#define SensorsManager_h

class SensorsManager {
public:
    SensorsManager();
    void configurePins();
    void storeLaserSensorLevel();
    bool isBatteryNotConnected();
    double batteryVoltage();
    bool isAllTargetsDown();
private:
  int _laserSensorLevel;
  int _laserSignalLevel();
};
#endif