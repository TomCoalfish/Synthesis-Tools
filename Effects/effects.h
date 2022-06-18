
// Hermezhang Effects
#pragma once 

#ifdef __MINGW32__
#include <malloc.h>
#endif
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_SAMPLE (32767 << 8)
#define MAX_CHANNELS 8
#define MAX_SAMPLE_RATE 48000
typedef float gnu_guitar_sample_t;
#define DSP_SAMPLE gnu_guitar_sample_t

////////////////////////////////////
/// DataBloack
////////////////////////////////////
/** @brief Used for containing audio
 * samples. */
struct gnu_guitar_packet {
  /** @brief Where the input data is
   * read from the filters. */
  gnu_guitar_sample_t * data;
  /** @brief Where the output data is
   * written from the filters. */
  gnu_guitar_sample_t * data_swap;
  /** @brief Number of frames in the
   * data buffers. */
  uint_fast32_t len;
  /** Number of frames per second. */
  uint_fast32_t rate;
  /** @brief Number of samples per frame. */
  uint_fast8_t channels;
};

/** @brief For compatibility. */
typedef struct gnu_guitar_packet data_block_t;


//////////////////////////////////
// Backbuf/
//////////////////////////////////

#define BUF_TYPE DSP_SAMPLE

typedef struct Backbuf {
    BUF_TYPE *storage;
    unsigned int mask, nstor, curpos;
    /* method slots */
    void (*add)(struct Backbuf *b, const BUF_TYPE value);
    BUF_TYPE (*get)(struct Backbuf *b, const unsigned int pos);
    BUF_TYPE (*get_interpolated)(struct Backbuf *b, float pos);
    void (*clear)(struct Backbuf *b);
} Backbuf_t;

Backbuf_t * new_Backbuf(const unsigned int size);
void del_Backbuf(Backbuf_t *b);



//////////////////////////////////////
/// Biquad
//////////////////////////////////////


typedef struct {
    float b[4];
    float mem[MAX_CHANNELS][4];
    float b0;
} Biquad_t;

typedef struct {
    Biquad_t        a1[MAX_CHANNELS], a2[MAX_CHANNELS];
    DSP_SAMPLE      x0_tmp[MAX_CHANNELS];
} Hilbert_t;

/* Fs = sampling rate, Fc = center frequency, BW = bandwidth (octaves),
 * G = gain (dB), ripple = 0=butterw, 1-100=cheb (s-domain ellipticity %),
 * delay = unitless 0 .. 1, lowpass = flag whether cheb is lowpass filter */
void     set_peq_biquad(double Fs, double Fc, double BW, double G, Biquad_t *f);
void     set_bpf_biquad(double Fs, double Fc, double BW, Biquad_t *f);
void     set_lpf_biquad(double Fs, double Fc, double BW, Biquad_t *f);
void     set_phaser_biquad(double delay, Biquad_t *f);
void     set_2nd_allpass_biquad(double delay, Biquad_t *f);
void     set_rc_lowpass_biquad(double Fs, double Fc, Biquad_t *f);
void     set_rc_highpass_biquad(double Fs, double Fc, Biquad_t *f);
void     set_lsh_biquad(double Fs, double Fc, double G, Biquad_t *f);
void     set_hsh_biquad(double Fs, double Fc, double G, Biquad_t *f);
void     set_chebyshev1_biquad(double Fs, double Fc, double ripple,
			       int lowpass, Biquad_t *f);

void     hilbert_transform(DSP_SAMPLE in, DSP_SAMPLE *x0, DSP_SAMPLE *x1, Hilbert_t *h, int curr_channel);
void     hilbert_init(Hilbert_t *h);
void     fir_interpolate_2x(DSP_SAMPLE *mem, DSP_SAMPLE in, DSP_SAMPLE *o1, DSP_SAMPLE *o2);
DSP_SAMPLE fir_decimate_2x(DSP_SAMPLE *mem, DSP_SAMPLE in1, DSP_SAMPLE in2);

///////////////////////////////////////////////
// Effect
///////////////////////////////////////////////
#define MAX_EFFECTS 50


struct effect {
  void *params;
  void (*proc_init) (struct effect *);
  void (*proc_done) (struct effect *);
  void (*proc_filter) (struct effect *, data_block_t *);
  short toggle;
};

typedef struct effect effect_t;

typedef struct effect gnu_guitar_effect_t;

void gnu_guitar_effect_init(gnu_guitar_effect_t *effect);

void gnu_guitar_effect_filter(gnu_guitar_effect_t *effect,
                              struct gnu_guitar_packet *packet);

void gnu_guitar_effect_free(gnu_guitar_effect_t *effect);

#ifdef __GNUC__
#define unlikely(x) __builtin_expect((x), 0)
#else
#define unlikely(x) !!(x)
#endif

#define CLIP_SAMPLE(sm) \
    if (unlikely(sm > (typeof(sm)) MAX_SAMPLE)) \
        sm = (typeof(sm)) MAX_SAMPLE; \
    if (unlikely(sm < (typeof(sm)) -MAX_SAMPLE)) \
        sm = (typeof(sm)) -MAX_SAMPLE;

/* these macros are used to save my sanity */
#define SAVE_ARGS \
    GKeyFile *preset, gchar *group
#define LOAD_ARGS \
    GKeyFile *preset, gchar *group, GError **error
#define SAVE_DOUBLE(name, param) \
    g_key_file_set_double(preset, group, name, param);
#define LOAD_DOUBLE(name, param) \
    param = g_key_file_get_double(preset, group, name, error); \
    if (*error != NULL) { \
	gnuitar_printf("warning: couldn't read '%s', '%s'\n", group, name); \
	*error = NULL; \
    }
#define SAVE_INT(name, param) \
    g_key_file_set_integer(preset, group, name, param);
#define LOAD_INT(name, param) \
    param = g_key_file_get_integer(preset, group, name, error); \
    if (*error != NULL) { \
	gnuitar_printf("warning: couldn't read '%s', '%s'\n", group, name); \
	*error = NULL; \
    }

/* tabularised sin() */
#define SIN_LOOKUP_SIZE         65536
extern float sin_lookup_table[SIN_LOOKUP_SIZE+1];

static inline float
sin_lookup(float pos) {
    return sin_lookup_table[(int) (pos * (float) SIN_LOOKUP_SIZE)];
}

static inline DSP_SAMPLE
cos_lookup(float pos) {
    if (pos >= 0.75f)
        return sin_lookup(pos - 0.75f);
    else
        return sin_lookup(pos + 0.25f);
}

/* without SSE we just wrap calloc */
static inline void * gnuitar_memalign(unsigned int num, size_t bytes)
{
    void *mem = calloc(num, bytes);
    if (mem == NULL) {
        fprintf(stderr, "failed to allocate aligned memory.\n");
        exit(1);
    }
    return mem;
}

static inline void
gnuitar_free(void *memory) {
    free(memory);
}

// global initialisers
void effect_start(void);
void effect_stop(void);

// effect list operations
void effect_list_print_all(void);
int effect_list_find_by_name(const char *name);

// effect operations
effect_t *effect_create(const int idx);
effect_t *effect_create_without_init(const int idx);
void effect_iterate(void (*func)(effect_t *effect, int idx, void *data), void *data);
void effect_clear(void);
int effect_insert(effect_t *effect, const int idx);
int effect_move(const int start, const int end);
int effect_find(const effect_t *effect);
void effect_destroy(effect_t *effect);
effect_t *effect_delete(const int idx);



////////////////////////////////////////////////////
// Echo
////////////////////////////////////////////////////
#define MAX_ECHO_COUNT 4
#define MAX_ECHO_LENGTH 500 /* ms */

effect_t * echo_create(void);

struct echo_params {
    Backbuf_t *history[MAX_CHANNELS][MAX_ECHO_COUNT];
    double primes[MAX_ECHO_COUNT];
    double size_factor[MAX_ECHO_COUNT];
    double decay_factor[MAX_ECHO_COUNT];
    /** @brief Length of the echo, in milliseconds. */
    double echo_size;
    /** @brief Each echo reduces in volume. The amount
     * of volume reduced is determined by the decay. This
     * value should be between zero and one hundred. */
    double echo_decay;
    /** @brief The number of echoes that occur. */
    unsigned int echoes;
    /** @deprecated */
    short multichannel;
};



// amplifier
struct amp_params {
    float            amp_power; //power of amp
};
struct autowah_params {
    Backbuf_t       *history;   
    float           sweep_time;
    float           freq_low;
    float           freq_high;
    float           res;
    float 	        drywet;
    int             sync;
    int             method;

    float           fresh_accum_delta;
    float           fresh_accum_power;
    float           delayed_accum_delta;
    float           delayed_accum_power;
    int             accum_n;
    
    float           f, smoothed_f, freq_vibrato;
    int             dir;
    float           ya[MAX_CHANNELS];
    float           yb[MAX_CHANNELS];
    float           yc[MAX_CHANNELS];
    float           yd[MAX_CHANNELS];

    Biquad_t        lpf;
    Biquad_t        bpf;
};

/// CHorus
effect_t *   chorus_create(void);

struct chorus_params {
    Backbuf_t      *history[MAX_CHANNELS];
    float           drywet,
                    basedelay,
                    depth,
                    speed,
                    regen,
                    ang;
    int             voices;
    short           multichannel;
};

