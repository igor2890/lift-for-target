#ifndef MotorManager_h
#define MotorManager_h

enum Direction : bool {
  Up = true,
  Down = false
};

class MotorManager {
public:
    MotorManager();
    void configurePins();
    void moveMechan(Direction direction, int steps);
private:
    void _dirMoveDown();
    void _dirMoveUp();
    void _makeStep();
};
#endif
