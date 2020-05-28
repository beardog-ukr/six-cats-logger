#pragma once

#define C6_W1(c6, p1) {                           \
    if (c6->warningEnabled()) {                   \
      ostringstream c6_ss;                        \
      c6_ss << p1;                                \
      c6->w(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_W2(c6, p1, p2) {                       \
    if (c6->warningEnabled()) {                   \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2;                          \
      c6->w(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_W3(c6, p1, p2, p3) {                   \
    if (c6->warningEnabled()) {                   \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3;                    \
      c6->w(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_W4(c6, p1, p2, p3, p4) {               \
    if (c6->warningEnabled()) {                   \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4;              \
      c6->w(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_W5(c6, p1, p2, p3, p4, p5) {           \
    if (c6->warningEnabled()) {                   \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4 << p5;        \
      c6->w(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_W6(c6, p1, p2, p3, p4, p5, p6) {       \
    if (c6->warningEnabled()) {                   \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4 << p5 << p6;  \
      c6->w(__c6_MN__, c6_ss.str());              \
    }                                             \
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

#define C6_I1(c6, p1) {                           \
    if (c6->infoEnabled()) {                      \
      ostringstream c6_ss;                        \
      c6_ss << p1;                                \
      c6->i(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_I2(c6, p1, p2) {                       \
    if (c6->infoEnabled()) {                      \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2;                          \
      c6->i(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_I3(c6, p1, p2, p3) {                   \
    if (c6->infoEnabled()) {                      \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3;                    \
      c6->i(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_I4(c6, p1, p2, p3, p4) {               \
    if (c6->infoEnabled()) {                      \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4;              \
      c6->i(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_I5(c6, p1, p2, p3, p4, p5) {           \
    if (c6->infoEnabled()) {                      \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4 << p5;        \
      c6->i(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_I6(c6, p1, p2, p3, p4, p5, p6) {       \
    if (c6->infoEnabled()) {                      \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4 << p5 << p6;  \
      c6->i(__c6_MN__, c6_ss.str());              \
    }                                             \
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

#define C6_D1(c6, p1) {                           \
    if (c6->debugEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1;                                \
      c6->d(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_D2(c6, p1, p2) {                       \
    if (c6->debugEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2;                          \
      c6->d(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_D3(c6, p1, p2, p3) {                   \
    if (c6->debugEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3;                    \
      c6->d(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_D4(c6, p1, p2, p3, p4) {               \
    if (c6->debugEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4;              \
      c6->d(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_D5(c6, p1, p2, p3, p4, p5) {           \
    if (c6->debugEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4 << p5;        \
      c6->d(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_D6(c6, p1, p2, p3, p4, p5, p6) {       \
    if (c6->debugEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4 << p5 << p6;  \
      c6->d(__c6_MN__, c6_ss.str());              \
    }                                             \
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

#define C6_T1(c6, p1) {                           \
    if (c6->traceEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1;                                \
      c6->t(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_T2(c6, p1, p2) {                       \
    if (c6->traceEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2;                          \
      c6->t(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_T3(c6, p1, p2, p3) {                   \
    if (c6->traceEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3;                    \
      c6->t(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_T4(c6, p1, p2, p3, p4) {               \
    if (c6->traceEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4;              \
      c6->t(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_T5(c6, p1, p2, p3, p4, p5) {           \
    if (c6->traceEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4 << p5;        \
      c6->t(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_T6(c6, p1, p2, p3, p4, p5, p6) {       \
    if (c6->traceEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4 << p5 << p6;  \
      c6->t(__c6_MN__, c6_ss.str());              \
    }                                             \
}

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

#define C6_F1(c6, p1) {                           \
    if (c6->floodEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1;                                \
      c6->f(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_F2(c6, p1, p2) {                       \
    if (c6->floodEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2;                          \
      c6->f(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_F3(c6, p1, p2, p3) {                   \
    if (c6->floodEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3;                    \
      c6->f(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_F4(c6, p1, p2, p3, p4) {               \
    if (c6->floodEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4;              \
      c6->f(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_F5(c6, p1, p2, p3, p4, p5) {           \
    if (c6->floodEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4 << p5;        \
      c6->f(__c6_MN__, c6_ss.str());              \
    }                                             \
}

#define C6_F6(c6, p1, p2, p3, p4, p5, p6) {       \
    if (c6->floodEnabled()) {                     \
      ostringstream c6_ss;                        \
      c6_ss << p1 << p2 << p3 << p4 << p5 << p6;  \
      c6->f(__c6_MN__, c6_ss.str());              \
    }                                             \
}
