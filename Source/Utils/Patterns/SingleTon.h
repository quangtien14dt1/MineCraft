#pragma once

#include "NonMovable.h"
#include "NonCopyable.h"

class SingleTon : public NonCopyable, public NonMovable {};