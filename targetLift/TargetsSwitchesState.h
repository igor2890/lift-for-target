#ifndef TargetsSwitchesState_h
#define TargetsSwitchesState_h

enum Pressed : bool {
  PRESSED = true,
  NOTPRESSED = false
};

struct TargetsSwitchesState {
      Pressed target_1;
      Pressed target_2;
      Pressed target_3;
      Pressed target_4;
      Pressed target_5;

      bool isAllUp();
};

bool operator==(const TargetsSwitchesState& lhs, const TargetsSwitchesState& rhs);

#endif
