#pragma once

#define C6_D1(p1) {    \
    auto v1 = p1;      \
    c6->c( __c6_MN__, [v1]() -> std::string { \
      ostringstream ss;  \
      ss << v1;          \
      return ss.str();   \
    });   \
}

