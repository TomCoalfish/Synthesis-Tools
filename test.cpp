#include "Stk.hpp"
#include "StkADSR.hpp"
#include "StkAsymp.hpp"
#include "StkBandedWG.hpp"
#include "StkBeeThree.hpp"
#include "StkBlit.hpp"
#include "StkBlitSaw.hpp"
#include "StkBlitSquare.hpp"
#include "std_samples.hpp"
#include "std_dsp.hpp"
#include "SndFile.hpp"
#include "Resampler.hpp"

using namespace stk;

using namespace SoundAlchemy;

int main()
{
    Stk<float>::setRawwavePath("stk/rawwaves");
    ADSR<float> ADSR;
    Asymp<float> Asymp;
    BandedWG<float> bwg;
    BeeThree<float> b3;
    Stk<float>::setSampleRate(44100);
    StkFrames<float> f(1024,2);
    f.fill(0,1);
    f.fill(1,2);
    f.print();
    std::cout << f.frames() << std::endl;
    std::cout << f.channels() << std::endl;
    StkFrames<float> l(1024,1);
    f.getChannel(0,l,0);
    l.print();
    std::vector<float> right = f.GetVectorChannel(1);
    l = right;
    l.print();
    f.setChannel(0,l,0);
    f.print();
}
