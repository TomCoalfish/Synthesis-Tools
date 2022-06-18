# Lua Physical Modelling Synthesis
Synthesis Toolkit with Lua/JIT   
 
# Books
* https://ccrma.stanford.edu/~jos/pasp/
* https://www.academia.edu/27559334/Wave_Digital_Filter_Modeling_of_Circuits_with_Operational_Amplifiers
* https://ccrma.stanford.edu/~jos//WaveDigitalFilters/WaveDigitalFilters_2up.pdf
* https://dafx09.como.polimi.it/proceedings/papers/paper_16.pdf
* https://dafx2020.mdw.ac.at/proceedings/papers/DAFx2020_paper_35.pdf
* http://dafx17.eca.ed.ac.uk/papers/DAFx17_paper_89.pdf

# Base Classes
* Effect
* FM
* Function
* Generator
* Instrmnt

# Classes
* ADSR
* Asymp (envelope)
* BandedWG (Banded Wave Guide)
* BeeThree (FM Instrument)
* BiQuad
* Blit
* BlitSaw
* BlitSquare
* BlowBotl
* BlowHole
* BowTable
* Bowed
* Brass
* Chorus
* Clarinet
* Cubic
* Delay
* DelayA
* DelayL
* Drummer
* Echo
* FileLoop (WaveTable)
* FileRead
* FileWrite
* FileWvIn
* FileWvOut
* Filter
* Fir
* Flute
* FormSwep
* FreeVerb
* Granulate
* Guitar
* HevyMetl
* Iir
* INetWvIn
* INetWvOut
* JCRev (Reverb)
* JetTable
* LentPitSHift
* Mandolin
* Mesh2D
* Messager
* MidiFileIn
* Modal
* ModalBar
* Modulate
* Moog
* Mutex
* NRev (Reverb)
* Noise
* OnePole
* OneZero
* PRCRev (Reverb)
* PercFlut
* Phonemes
* PitShift
* Plucked
* PoleZero
* Recorder
* ReedTable
* Resonate
* Rhodey
* RtAudio
* RtMidi
* RtWvIn
* RtWvOut
* SKINI
* Sampler
* Saxofony
* Shakers
* Simple
* SineWave
* Sitar
* SOcket
* Sphere
* StifKarp
* TapDelay
* TcpClient
* TcpServer
* Thread
* TubeBell
* Twang
* TwoPole
* TwoZero
* UdpSOcket
* Vector3D
* VoicForm
* Voicer
* Whislte
* Wurley
* WvIn
* WvOut

# Comb Filter Example
```c++
// filterNoise.cpp - filtered white noise example 
// Tested with STK 4.4.2

#include "Noise.h"  // Synthesis Tool Kit (STK) class
#include "Iir.h"    // STK class
#include "FileWvOut.h"  // STK class
#include <cmath>   // for pow()
#include <vector>

using namespace stk;

int main()
{
  Noise *theNoise = new Noise(); // Noise source

  /* Set up the filter */
  StkFloat bCoefficients[5] = {1,0,0,pow(0.5,3)}; 
  std::vector<StkFloat> b(bCoefficients, bCoefficients+5);
  StkFloat aCoefficients[7] = {1,0,0,0,0,pow(0.9,5)};
  std::vector<StkFloat> a(aCoefficients, aCoefficients+7);
  Iir *filter = new Iir;
  filter->setNumerator(b);
  filter->setDenominator(a);

  FileWvOut output("main");  /* write to main.wav */

  /* Generate one second of white noise */
  StkFloat amp = 0.1; // noise amplitude
  for (long i=0;i<SRATE;i++)   {
    output.tick(amp*theNoise->tick());
  }

  /* Generate filtered noise for comparison */
  for (long i=0;i<SRATE;i++)   {
    output.tick(filter->tick(amp*theNoise->tick()));
  }
}
```
