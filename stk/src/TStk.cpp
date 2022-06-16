#include "TStk.hpp"

namespace stk {
    StkFloat Stk :: srate_ = (StkFloat) SRATE;
    std::string Stk :: rawwavepath_ = RAWWAVE_PATH;
    bool Stk :: showWarnings_ = true;
    bool Stk :: printErrors_ = true;
    std::vector<Stk *> Stk :: alertList_;
    std::ostringstream Stk :: oStream_;
};