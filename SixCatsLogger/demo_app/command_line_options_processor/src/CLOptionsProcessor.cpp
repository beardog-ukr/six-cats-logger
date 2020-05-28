#include "CLOptionsProcessor.h"

#include <iostream>
#include <sstream> //ostringstream
using namespace std;

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

bool isShortKey(char const * const inStr) {
  string s = inStr;
  if (s.empty()) {
    return false;
  }

  if (s.length()!=2) {
    return false;
  }

  if (s[0]!= '-') {
    return false;
  }

  return true;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

bool isLongKey(char const * const inStr) {
  string s = inStr;
  if (s.empty()) {
    return false;
  }

  if (s.length()<3) {
    return false;
  }

  if ((s[0]!= '-')&&(s[1]!= '-')) {
    return false;
  }

  return true;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

CLOptionsProcessor::CLOptionsProcessor() {
  //nothing to do
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

CLOptionsProcessor::~CLOptionsProcessor() {
  //nothing to do
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

void CLOptionsProcessor::addExpectedOption(const char shortKey, const std::string& longKey,
                                           const bool requiresParameter) {
  ExpectedOption newOption;
  newOption.shortKey = shortKey;
  newOption.longKey = longKey;
  newOption.requiresParameter = requiresParameter;

  expectedOptions.push_back(newOption);
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

std::string CLOptionsProcessor::getOptionValue(const char shortKey) const {
  for (ProcessedOption po : processedOptions) {
    if (po.shortKey == shortKey) {
      return po.value;
    }
  }

  // default
  return "";
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

std::string CLOptionsProcessor::getRemainingLine() const {
  return remainingLine;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

bool CLOptionsProcessor::hasOption(const char shortKey) const {
  for(const ProcessedOption po: processedOptions) {
    if (shortKey == po.shortKey) {
      return true;
    }
  }

  //if nothing found
  return false;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

bool CLOptionsProcessor::process(int argc, char *argv[]) {
  enum ProcessingStateCode {
    PSC_WaitingForOption,
    PSC_WaitingForParameter
  };

  string value;
  ProcessingStateCode stateCode = PSC_WaitingForOption;
  ProcessedOption processedOption;

  list<string> remainingPieces;

  for (int i = 0; i< argc; i++) {
    bool needToAdd = false;

    if (stateCode == PSC_WaitingForOption) {

      if (isShortKey(argv[i])) {

        const char currentShortKey = argv[i][1];

        cout << "Found short Option: " << currentShortKey << endl;

        bool found = false;
        for(const ExpectedOption eo :expectedOptions) {
          if (eo.shortKey == currentShortKey) {
            found = true;
            processedOption.shortKey = currentShortKey;
            processedOption.longKey = eo.longKey;

            if (eo.requiresParameter) {
              stateCode = PSC_WaitingForParameter;
            }
            else {
              processedOptions.push_back(processedOption);
              processedOption = {.shortKey = '0', .longKey = "", .value = ""};
              //TODO: replace previous line with a kind of "reset" method
            }
          }
          // else {
          //   cout << "Does not match: " << currentShortKey << " vs " << eo.shortKey <<  endl;
          // }
        }

        if (!found) {
          cout << "Error: unexpected short Option: " << currentShortKey;
          return false;
        }
      }
      else if (isLongKey(argv[i])) {
        const string fullLongKey = argv[i];
        const string currentLongKey = fullLongKey.substr(2, fullLongKey.length() -2);

        cout << "Found long Option: " << currentLongKey << endl;

        bool found = false;
        for(const ExpectedOption eo :expectedOptions) {
          if (eo.longKey == currentLongKey) {
            found = true;
            processedOption.shortKey = eo.shortKey;
            processedOption.longKey = currentLongKey;

            if (eo.requiresParameter) {
              stateCode = PSC_WaitingForParameter;
            }
            else {
              processedOptions.push_back(processedOption);
              processedOption = {.shortKey = '0', .longKey = "", .value = ""};
              //TODO: replace previous line with a kind of "reset" method
            }
          }
          // else {
          //   cout << "Does not match: " << currentShortKey << " vs " << eo.shortKey <<  endl;
          // }
        }

        if (!found) {
          cout << "Error: unknown long option: " << currentLongKey;
          return false;
        }
      }
      //TODO: check for java stype options that a neither short nor long, like "-opt"
      else {
        remainingPieces.push_back(argv[i]);
      }


      ///
    }
    else if (stateCode ==PSC_WaitingForParameter) {
      if (isShortKey(argv[i]) || isLongKey(argv[i])) {
        cout << "Error: expected parameter, received option " << argv[i] << endl;
        return false;
      }

      processedOption.value = argv[i];
      processedOptions.push_back(processedOption);
      processedOption = {.shortKey = '0', .longKey = "", .value = ""};

      stateCode = PSC_WaitingForOption;
    }
  }

  if (stateCode == PSC_WaitingForParameter) {
    cout << "Error: expected parameter, received nothing" << endl;
    return false;
  }

  if (remainingPieces.size() >=2) {
    ostringstream ss;
    ss << remainingPieces.front();
    remainingPieces.pop_front();
    for (const string rp: remainingPieces) {
      ss << " ";
      ss << rp;
    }
    remainingLine = ss.str();
  }
  else {
    if (remainingPieces.size() == 1) {
      remainingLine = remainingPieces.front();
    }
    else {
      remainingLine = "";
    }
  }

  return true;
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
