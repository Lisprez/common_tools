#pragma once

#include "_dlog.h"
#include "_ModernCPP.h"


#define NoneCopyable(className)                      \
    className(const className&) = delete;            \
    className(const className&&) = delete;           \
    className& operator=(const className&) = delete; \
    className& operator=(const className&&) = delete