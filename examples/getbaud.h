#pragma once

#include <termios.h>

//! Exception
struct bad_speed {};

//! Convert requested int based speed to corresponding speed_t enum value.
//! The retuened enum value will be the closed value not bigger than the
//! requested value.
//! If no matching enum value could be found a bad_speed exception is thrown.
speed_t getBaud(int speed);
