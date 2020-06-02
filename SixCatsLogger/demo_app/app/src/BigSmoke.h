#pragma once

#include <string>
#include "SixCatsLoggerLoggable.h"

class BigSmoke : virtual public SixCatsLoggerLoggable {
public:
  BigSmoke();
  virtual ~BigSmoke();

  std::string getFailedTrainMessage();

protected:
  int weight;

};