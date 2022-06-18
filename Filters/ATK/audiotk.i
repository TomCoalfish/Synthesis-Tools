%module audiotk
%{
#include "ATK/Adaptive/LMSFilter.h"
#include <cassert>
%}

%inline %{

    struct LMSFilter
    {
        ATK::LMSFilter * filter;

        LMSFilter(size_t size) {
            filter = new ATK::LMSFilter(size);
            assert(filter != NULL);
        }
        ~LMSFilter() {
            if(filter) delete filter;
        }
    };
%}