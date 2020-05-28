#include "BasicC6MacroDemo.h"
#include "SixCatsLogger.h"

#include <iostream> // cout
using namespace std;

const string outputPrefix = ">> ";

#define NUMBER_SIX 6

// Function used for demonstration
string getPartThree() {
  return "s, a number ";
}

// Another function used for demonstration
string getPartThreeSpecial() {
  cout << "This should be never printed" << endl;
  return "s, a number ";
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

BasicC6MacroDemo::BasicC6MacroDemo(const int inLogLevel) {
  const SixCatsLogger::LogLevel logLevelValues[6] = {
    SixCatsLogger::Critical, SixCatsLogger::Warning,
    SixCatsLogger::Info, SixCatsLogger::Debug,
    SixCatsLogger::Trace, SixCatsLogger::Flood
  };

  SixCatsLogger::LogLevel ll = SixCatsLogger::Debug;
  if ((inLogLevel>=0)&&(inLogLevel<=6)) {
    ll = logLevelValues[inLogLevel];
  }
  c6 = make_shared<SixCatsLogger>(ll);
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

BasicC6MacroDemo::~BasicC6MacroDemo() {
  // nothing to be done here
  // but it's required for shared_ptr usage
}

void BasicC6MacroDemo::showNoEvaluationFeature() {
  SixCatsLogger* c6custom = new SixCatsLogger(SixCatsLogger::Info);

  string partOne = "I'll have two number ";
  int partTwo = 9;

  cout << outputPrefix
       << "Special test: nothing will appear between this line and next one" << endl;

  //Note: getPartThreeSpecial() prints something to cout, but it will not be called
  // so nothing will be printed until "next line"

  C6_D3(c6custom, partOne, partTwo, getPartThreeSpecial());

  cout << outputPrefix << "Special test: this is \"next\" line" << endl;

  delete c6custom;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void BasicC6MacroDemo::showInfoMacro() {

  string partOne = "I'll have two number ";
  int partTwo = 9;

  cout << outputPrefix << "Now it will use C6_Ix macro:" << endl;
  C6_I1(c6, partOne);
  C6_I2(c6, partOne, partTwo);
  C6_I3(c6, partOne, partTwo, getPartThree());
  C6_I4(c6, partOne, partTwo, getPartThree(), 3*3);
  C6_I5(c6, partOne, partTwo, getPartThree(), 3*3, " large, a number");
  C6_I6(c6, partOne, partTwo, getPartThree(), 3*3, " large, a number ", NUMBER_SIX);
  cout << outputPrefix << ">> Done with C6_Ix" << endl;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void BasicC6MacroDemo::showWarningMacro() {

  string partOne = "I'll have two number ";
  int partTwo = 9;

  cout << outputPrefix << "Now it will use C6_Wx macro:" << endl;
  C6_W1(c6, partOne);
  C6_W2(c6, partOne, partTwo);
  C6_W3(c6, partOne, partTwo, getPartThree());
  C6_W4(c6, partOne, partTwo, getPartThree(), 3*3);
  C6_W5(c6, partOne, partTwo, getPartThree(), 3*3, " large, a number");
  C6_W6(c6, partOne, partTwo, getPartThree(), 3*3, " large, a number ", NUMBER_SIX);
  cout << outputPrefix << ">> Done with C6_Wx" << endl;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void BasicC6MacroDemo::showDebugMacro() {

  string partOne = "I'll have two number ";
  int partTwo = 9;

  cout << outputPrefix << "Now it will use C6_Dx macro:" << endl;
  C6_D1(c6, partOne);
  C6_D2(c6, partOne, partTwo);
  C6_D3(c6, partOne, partTwo, getPartThree());
  C6_D4(c6, partOne, partTwo, getPartThree(), 3*3);
  C6_D5(c6, partOne, partTwo, getPartThree(), 3*3, " large, a number");
  C6_D6(c6, partOne, partTwo, getPartThree(), 3*3, " large, a number ", NUMBER_SIX);
  cout << outputPrefix << ">> Done with C6_Dx" << endl;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void BasicC6MacroDemo::showTraceMacro() {

  string partOne = "I'll have two number ";
  int partTwo = 9;

  cout << outputPrefix << "Now it will use C6_Tx macro:" << endl;
  C6_T1(c6, partOne);
  C6_T2(c6, partOne, partTwo);
  C6_T3(c6, partOne, partTwo, getPartThree());
  C6_T4(c6, partOne, partTwo, getPartThree(), 3*3);
  C6_T5(c6, partOne, partTwo, getPartThree(), 3*3, " large, a number");
  C6_T6(c6, partOne, partTwo, getPartThree(), 3*3, " large, a number ", NUMBER_SIX);
  cout << outputPrefix << ">> Done with C6_Tx" << endl;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void BasicC6MacroDemo::showFloodMacro() {

  string partOne = "I'll have two number ";
  int partTwo = 9;

  cout << outputPrefix << "Now it will use C6_Fx macro:" << endl;
  C6_F1(c6, partOne);
  C6_F2(c6, partOne, partTwo);
  C6_F3(c6, partOne, partTwo, getPartThree());
  C6_F4(c6, partOne, partTwo, getPartThree(), 3*3);
  C6_F5(c6, partOne, partTwo, getPartThree(), 3*3, " large, a number");
  C6_F6(c6, partOne, partTwo, getPartThree(), 3*3, " large, a number ", NUMBER_SIX);
  cout << outputPrefix << ">> Done with C6_Fx" << endl;
}

