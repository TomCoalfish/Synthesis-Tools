%module pitchshifterpp
%{
#include "fftwpvadapter.hpp"
#include "phasevocoder.hpp"
#include "used_math.hpp"
%}

%include "fftwpvadapter.hpp"
//%include "phasevocoder.hpp"
%include "used_math.hpp"

namespace pv {

template <typename scalar_t>
struct Complex {
    scalar_t real, imag;
};

template <typename scalar_t>
struct ComplexPolar {
    scalar_t magnitude, phase;
};

/**
 * @brief simple circular iterator for plain arrays, no checks
 */
template<typename T>
class circular_iterator {
public:
    circular_iterator(T *begin, uint32_t size);
    T& operator[](uint32_t idx) const;
    circular_iterator& operator+=(uint32_t idx);
    circular_iterator& operator-=(uint32_t idx);
    circular_iterator& operator--(int);
    circular_iterator& operator++(int);
    circular_iterator operator+(uint32_t num) const;
    circular_iterator operator-(uint32_t num) const;
    bool is_full() const;
};



/**
 * @brief PhaseVocoder optimized for speed and low memory consumption,
 * currently implemented with 1.5 * window_size latency
 * @tparam window_size window size of FFT, is a template parameter  as
 * all needed memory is allocated at compile time;
 * @tparam max_syn_size this is equivalent to @ref window_size *
 *  maximum scaling factor which is planned to be used
 * @tparam fft_adapter_t non-virtual adapter and implicit interface type
 * for the used FFT
 * @tparam scalar_t scalar type
 */
template <uint32_t window_size, uint32_t max_syn_size,
          typename fft_adapter_t, typename scalar_t = double>
class PhaseVocoder
{
public:
    PhaseVocoder(fft_adapter_t &fft_adapter, uint32_t overlap_factor);
    void correct_phase(scalar_t syn_hop_size);
    /**
     * @brief process
     * @param input_buffer
     * @param output_buffer can be the same as output
     * @param input_size maximum size of samples which is copied to
     * @ref output_buffer, if it is bigger than @ref window_size then
     * @ref window_size number of samples are copied; this
     * parameter exist only to be able to process blocks smaller than
     * @ref window_size, e.g to process a whole wav file which don't
     * necessarily has a number of samples which are a multiple of
     * the @ref window_size
     * @param scaling_factor pitch scaling factor
     */
    void process(scalar_t *input_buffer, scalar_t *output_buffer,
                 uint32_t input_size, scalar_t scaling_factor);

    /**
     * @brief init_window window for the window function
     */
    void init_window();

    uint32_t const m_overlap_factor;
    uint32_t const m_ana_hop_size;

    scalar_t const m_omega;
    scalar_t const m_ana_hop_inv;

    scalar_t m_fft_buffer1[window_size];
    ComplexPolar<scalar_t> m_fft_buffer2[window_size / 2 + 1];
    scalar_t m_pre_ana_phase_frame[window_size / 2];    
    scalar_t m_pre_syn_phase_frame[window_size / 2];
    scalar_t m_fft_window[window_size];
    scalar_t m_ana_frame[window_size * 2];
    circular_iterator<scalar_t> m_ana_frame_it;
    scalar_t m_syn_frame[max_syn_size * 2];
    circular_iterator<scalar_t> m_syn_frame_it;
    fft_adapter_t &m_fft_adapter;
};

} // namespace pv

