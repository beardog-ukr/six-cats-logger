#include "BigSmoke.h"

#include "SixCatsLoggerMacro.h"
#include "SixCatsLogger.h"
#include <string>
#include <sstream>

#include <limits> // max int limit
//using namespace std; //not used here just for demo purposes; c6 works fine without this

static const char lastWords[] = "When I'm gone, everyone gonna remember my name... Big Smoke!";

BigSmoke::BigSmoke() {
  weight = std::numeric_limits<int>::max();
}

BigSmoke::~BigSmoke() {
  //nothing to do here
  //but say last words
  C6_W1(c6, lastWords);
}

std::string BigSmoke::getFailedTrainMessage() {
  return "All you had to do was follow the damn train CJ!";
}