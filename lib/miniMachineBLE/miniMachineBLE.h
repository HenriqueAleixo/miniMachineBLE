#pragma once
#include <Arduino.h>
#include <functional>

typedef std::function<void(const String &dir)> DirCallback;

void miniMachineBLE_begin(const char *deviceName, DirCallback cb);