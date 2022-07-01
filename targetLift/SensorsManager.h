#ifndef SensorsManager_h
#define SensorsManager_h

#include "TargetsSwitchesState.h"

class SensorsManager {
  private:
  TargetsSwitchesState _targetsSwitchesState;
  int _laserSensorLevel;
  int _laserSignalLevel();
public:
  SensorsManager();
  void configurePins();
  void renewLaserSensorLevel();
  bool isBatteryNotConnected();
  double batteryVoltage();
  bool isAllTargetsDown();
  bool isSomeoneTargetDown();
  bool isDownSwitchPressed();
  bool isTargetsStatesChanges();
  TargetsSwitchesState targetsSwitchesState();
};
#endif
