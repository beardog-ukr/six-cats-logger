#pragma once

#include <string>
#include <list>

class CLOptionsProcessor {
public:
  CLOptionsProcessor();
  ~CLOptionsProcessor();

  void addExpectedOption(const char shortOption, const std::string& longOption,
                         const bool requiresParameter);
  //TODO: parameter can be three states: mandatory, possible or "no param"
  //TODO: allow multiple options with one line? (allow, not allow, "allow but only one is returned")

  /// returns option as string (empty if there was no such option)
  std::string getOptionValue(const char shortOption) const;

  bool hasOption(const char shortOption) const;

  bool process(int argc, char *argv[]);

  std::string getRemainingLine() const;

protected:
  struct ExpectedOption {
    char shortKey;
    std::string longKey;
    bool requiresParameter;
  };
  std::list<ExpectedOption> expectedOptions;

  struct ProcessedOption {
    char shortKey;
    std::string longKey;
    std::string value;
  };
  std::list<ProcessedOption> processedOptions;

  std::string remainingLine;
};

