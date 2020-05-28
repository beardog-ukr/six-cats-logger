#pragma once

#include <memory>
class SixCatsLogger;

class BasicC6MacroDemo final {
public:
  BasicC6MacroDemo(const int logLevel);
  ~BasicC6MacroDemo();

  void showInfoMacro();
  void showDebugMacro();
  void showWarningMacro();
  void showTraceMacro();
  void showFloodMacro();

protected:
  std::shared_ptr<SixCatsLogger> c6;
};

