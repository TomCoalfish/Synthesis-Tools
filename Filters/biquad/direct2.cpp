// b0, b1, b2, a1, a2 calculated via r.b-j's cookbook
// formulae.
// m1, m2 are the memory locations
// dn is the de-denormal coeff (=1.0e-20f)

void processBiquad(const float* in, float* out, unsigned length)
{
    for(unsigned i = 0; i < length; ++i)
    {
        register float w = in[i] - a1*m1 - a2*m2 + dn;
        out[i] = b1*m1 + b2*m2 + b0*w;
        m2 = m1; m1 = w;
    }
    dn = -dn;
}

void processBiquadStereo(const float* inL,
   const float* inR,
   float* outL,
   float* outR,
   unsigned length)
{
    for(unsigned i = 0; i < length; ++i)
    {
        register float wL = inL[i] - a1*m1L - a2*m2L + dn;
        register float wR = inR[i] - a1*m1R - a2*m2R + dn;
        outL[i] = b1*m1L + b2*m2L + b0*wL;
        m2L = m1L; m1L = wL;
        outR[i] = b1*m1R + b2*m2R + b0*wR;
        m2R = m1R; m1R = wR;
    }
    dn = -dn;
}