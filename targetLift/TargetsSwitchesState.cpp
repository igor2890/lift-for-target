#include "TargetsSwitchesState.h"

bool TargetsSwitchesState::isAllUp() {
  if (this->target_1 == PRESSED ||
    this->target_2 == PRESSED ||
    this->target_3 == PRESSED ||
    this->target_4 == PRESSED ||
    this->target_5 == PRESSED) {
      return false;
  }
  return true;
}

bool operator==(const TargetsSwitchesState& lhs, const TargetsSwitchesState& rhs)
{
  return (lhs.target_1 == rhs.target_1 &&
    lhs.target_2 == rhs.target_2 &&
    lhs.target_3 == rhs.target_3 &&
    lhs.target_4 == rhs.target_4 &&
    lhs.target_5 == rhs.target_5);
};
