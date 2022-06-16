#include "TStk.hpp"

namespace stk {    
    template<typename T> T Stk<T>::srate_ = SRATE;
    template<typename T> std::string Stk<T>::rawwavepath_ = RAWWAVE_PATH;
    template<typename T> bool Stk<T> :: showWarnings_ = true;
    template<typename T> bool Stk<T> :: printErrors_ = true;
    template<typename T> std::vector<Stk<T> *> Stk<T> :: alertList_;
    template<typename T> std::ostringstream Stk<T> :: oStream_;
};