%module chorus
%{
#include "chorus.h"
#include "Sample/SampleVector.h"
%}

%include "Sample/SampleVector.h"
%template(SampleVectorFloat) Sample::SampleVector<float>;
%include "chorus.h"