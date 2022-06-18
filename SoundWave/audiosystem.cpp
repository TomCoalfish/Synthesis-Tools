#include "audiosystem.h"


MidiMsg * midi_queue = NULL;
int midi_channel = 0;
PmStream * pm_midi_input = NULL;
PmStream * pm_midi_output = NULL;
pthread_mutex_t Lock;
PaStreamParameters outputParameters;
PaStreamParameters inputParameters;
PaStream *stream;
int isAudioRunning=false;

audio_func audio_callback;

midi_func  note_on_callback;
midi_func  note_off_callback;
midi_func  polyphonic_pressure_callback;
midi_func  control_change_callback;
midi_func  pitch_bend_callback;
midi_func  reset_all_controllers_callback;
midi_func  local_control_callback;
midi_func  all_notes_off_callback;
midi_func  omni_off_callback;
midi_func  omni_on_callback;
midi_func  mono_mode_callback;
midi_func  poly_mode_callback;
midi_func  clock_callback;
midi_func  start_sequence_callback;
midi_func  continue_sequence_callback;
midi_func  stop_sequence_callback;
midi_func  active_sense_callback;
midi_func  system_reset_callback;
midi_func  midi_timing_code_callback;
midi_func  song_position_callback;
midi_func  song_select_callback;
midi_func  tune_request_callback;
midi_func  system_exclusive_callback;

void set_note_on_callback( midi_func cb)
{
    note_on_callback  = cb;
}
void set_note_off_callback( midi_func cb)
{
    note_off_callback = cb;
}
void set_polyphonic_pressure_callback( midi_func cb)
{
    polyphonic_pressure_callback = cb;
}
void set_control_change_callback( midi_func cb)
{
    control_change_callback = cb;
}
void set_pitch_bend_callback( midi_func cb)
{
    pitch_bend_callback = cb;
}
void set_reset_all_controllers_callback(midi_func cb) {
    reset_all_controllers_callback = cb;
}
void set_local_control_callback(midi_func cb) {
    reset_local_control_callback = cb;
}
void set_all_notes_off_callback(midi_func cb) {
    all_notes_off_callback = cb;
}
void set_omni_off_callback( midi_func cb)
{
    omni_off_callback  = cb;
}
void set_omni_on_callback( midi_func cb)
{
    omni_on_callback  = cb;
}
void set_mono_mode_callback( midi_func cb)
{
    mono_mode_callback  = cb;
}
void set_poly_mode_callback( midi_func cb)
{
    poly_mode_callback  = cb;
}
void set_clock_callback( midi_func cb)
{
    clock_callback  = cb;
}
void set_start_sequence_callback( midi_func cb)
{
    start_sequence_callback  = cb;
}
void set_continue_sequence_callback( midi_func cb)
{
    continue_sequence_callback  = cb;
}
void set_stop_sequence_callback( midi_func cb)
{
    stop_sequence_callback  = cb;
}
void set_active_sense_callback( midi_func cb)
{
    active_sense_callback  = cb;
}
void set_system_reset_callback( midi_func cb)
{
    system_resett_callback  = cb;
}
void set_midi_timing_code_callback( midi_func cb)
{
    midi_timing_code_callback  = cb;
}
void set_song_position_callback( midi_func cb)
{
    song_position_callback  = cb;
}
void set_song_select_callback( midi_func cb)
{
    song_select_callback  = cb;
}
void set_time_request_callback( midi_func cb)
{
    time_request_callback  = cb;
}
void set_system_exclusive_callback( midi_func cb)
{
    system_exclusive_callback  = cb;
}

midi_func  song_position_callback;
midi_func  song_select_callback;
midi_func  tune_request_callback;
midi_func  system_exclusive_callback;

size_t GetNumMidiDevices()
{
    return Pm_CountDevices();
}

const char* GetMidiDeviceName(size_t i)
{
    const PmDeviceInfo * pm = Pm_GetDeviceInfo(i);
    return pm->name;
    
}
void LockMidi()
{
    while( pthread_mutex_lock(&Lock) != 0);
}
void UnlockMidi()
{
    while(pthread_mutex_unlock(&Lock) != 0);
}
MidiMsg* NewMessage(int status, int data1, int data2, int msg) {
    MidiMsg * p = (MidiMsg*)calloc(1,sizeof(MidiMsg));
    p->status = status;
    p->data1  = data1;
    p->data2  = data2;
    p->msg    = msg;
    p->next   = NULL;
    return p;
}
void AddMessage(MidiMsg * head, MidiMsg * last) {
    MidiMsg * p = head;
    if(p == NULL) return;
    while(p->next != NULL) {
        p = p->next;
    }
    p->next = last;
    last->next = NULL;
}
void ExecQueue(MidiMsg * msgs) 
{
    MidiMsg * p = msgs, *t;
    while(p != NULL) 
    {
        int status = p->status;
        int data1  = p->data1;
        int data2  = p->data2;
        int msg    = p->msg & 0xF0;
        int channel= p->msg & 0x0F;
        
        if( msg == 0x90 && note_on.L != 0)
        {                
            // note on
            note_on_callback(p);
        }
        else if( msg == 0x80 && note_off.L != 0)
        {
            // note off                
            note_off_callback(p);
        }
        else if(msg == 0xA0)
        {
            // polyphonic pressure
            polyhonic_pressure_callback(p);
        }
        else if(msg == 0xB0)
        {
            // control change
            control_change_callback(p);
        }
        else if(msg == 0xC0)
        {
            // program change
            program_change_callback(p);
        }
        else if(msg == 0xD0)
        {
            // channel pressure
            channel_pressure_callback(p);
        }
        else if(msg == 0xE0)
        {
            // pitchbend
            pitch_bend_callback(p);
        }
        else if(status == 0x79)
        {
            // reset all conrollers
            reset_all_controllers_callback(p);
        }
        else if(status == 0x7A)
        {
            // local control
            local_control_callback(p);
        }
        else if(status == 0x7B)
        {
            // all notes off
            all_notes_off_callback(p);
        }
        else if(status == 0x7C)
        {
            // omni off
            omni_mode_off_callback(p);
        }
        else if(status == 0x7D)
        {
            // omni on
            omni_mode_on_callback(p);
        }
        else if(status == 0x7E)
        {
            // mono mode
            mono_mode_callback(p);
        }
        else if(status == 0x7F)
        {
            // poly mode
            poly_mode_callback(p);
        }
        else if(status == 0xF8)
        {
            // clock
            clock_callback(p);
        }
        else if(status == 0xFA)
        {
            // start sequences
            start_sequence_callback(p);
        }
        else if(status == 0xFB)
        {
            // continue sequence
            continue_sequence_callback(p);
        }
        else if(status == 0xFC)
        {
            // stop sequence
            stop_sequence_callback(p);
        }
        else if(status == 0xFE)
        {
            // active sense
            active_sense_callback(p);
        }
        else if(status == 0xFF)
        {
            // system reset
            system_reset_callback(p);
        }
        else if(status == 0xF1)
        {
            // midi timing code
            midi_timing_code_callback(p);
        }
        else if(status == 0xF2)
        {
            // song position
            song_position_callback(p);
        }
        else if(status == 0xF3)
        {
            // song select
            song_select_callback(p);
        }
        else if(status == 0xF6)
        {
            // tune request
            time_request_callback(p);
        }
        else if(status == 0xF0)
        {
            // system exclusive
            system_exclusive_callback(p);
        }

        t = p->next;
        free(p);
        p = t;
    }
} 
void RunQueue() {    
    MidiMsg * msgs = midi_queue;
    midi_queue = NULL;
    ExecQueue(msgs);        
}
static void process_midi(PtTimestamp timestamp, void * userData)
{
    PmError result;
    PmEvent buffer;
    int channel;
    lua_State *L;

    LockMidi();
    do
    {
        result = Pm_Poll(pm_midi_input);        
        if(result)
        {
            int status,data1,data2,msg;
            if(Pm_Read(pm_midi_input, &buffer, 1) == pmBufferOverflow)
                continue;
            status = Pm_MessageStatus(buffer.message);
            data1  = Pm_MessageData1(buffer.message);
            data2  = Pm_MessageData2(buffer.message);
            channel = status & 0x0F;
            msg = status & 0xF0;   
            MidiMsg * pMsg = NewMessage(status,data1,data2,msg);
            if(midi_queue == NULL) midi_queue = pMsg;
            else AddMessage(midi_queue,pMsg);
        }
    }        
    while(result);   
    UnlockMidi();
    
}
void Init() {
    pthread_mutex_init(&Lock,NULL);
    LockMidi();
}
void InitMidiDevice(int channel, int input_id, int output_id)
{
    const PmDeviceInfo *in_info,*out_info;
    midi_channel = channel;
    int output_buffer_size = 100;
    int latency = 0;
    
    Pt_Start(10,&process_midi,0);
    Pm_Initialize();
    
    if(input_id > -1)
    {
        in_info  = Pm_GetDeviceInfo(input_id);
        Pm_OpenInput(&pm_midi_input, input_id, NULL, output_buffer_size, NULL, NULL);
    }
    if(output_id > -1)
    {
        out_info  = Pm_GetDeviceInfo(output_id);
        Pm_OpenOutput(&pm_midi_output, output_id, NULL, output_buffer_size, NULL, NULL, latency);
    }
}
void StopMidi()
{    
    Pt_Stop();
    if(pm_midi_input)  Pm_Close(pm_midi_input);
    if(pm_midi_output) Pm_Close(pm_midi_output);    
}



/////////////////////////////////////////////
// Audio
/////////////////////////////////////////////

void set_audio_func(audio_func callback)
{        
    audio_callback = callback;
}
void RunAudio()
{
    UnlockMidi();
    while(1)    
    {               
        LockMidi();     
        RunQueue();
        UnlockMidi();            
        Pa_Sleep(10);
    }
}
static int luaCallback(     const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData )
{

    LockMidi();    
    isAudioRunning=true;
    audio_callback(inputBuffer,outputBuffer,framesPerBuffer,timeInfo,statusFlags,userData);
    UnlockMidi();
    isAudioRunning=false;
    return paContinue;
}   
static void StreamFinished( void* userData )
{

}

int GetNumAudioDevices()
{
    return Pa_GetDeviceCount();
}
const char* GetAudioDeviceName(size_t i)
{
    const PaDeviceInfo* di = Pa_GetDeviceInfo(i);
    return di->name;
}


int InitAudioDevice(int output_device_number, int input_device_number, size_t num_channels, int sample_rate, int frames_per_second)
{
    PaError err;
    err = Pa_Initialize();    
    
    if( err != paNoError ) goto error;

    if(output_device_number > -1)
    {        
        outputParameters.device = output_device_number;
        if (outputParameters.device == paNoDevice) {
            fprintf(stderr,"Error: No default output device.\n");
            goto error;
        }
        outputParameters.channelCount = num_channels;       /* stereo output */
        outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
        outputParameters.suggestedLatency = 0.001; //Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = NULL;        
    }
    if(input_device_number > -1)
    {        
        inputParameters.device = input_device_number;
        if (inputParameters.device == paNoDevice) {
            fprintf(stderr,"Error: No default output device.\n");
            goto error;
        }
        inputParameters.channelCount = num_channels;       /* stereo output */
        inputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
        inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowOutputLatency;
        inputParameters.hostApiSpecificStreamInfo = NULL;        
    }

    err = Pa_OpenStream(
              &stream,
              input_device_number > -1? &inputParameters : NULL, /* no input */
              output_device_number > -1? &outputParameters : NULL,
              sample_rate,
              frames_per_second,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              luaCallback,
              NULL );
              
    if( err != paNoError ) goto error;

    printf("Start\n") ;
    //err = Pa_SetStreamFinishedCallback( stream, &StreamFinished );
    //if( err != paNoError ) goto error;
    
    err = Pa_StartStream( stream );    
    if( err != paNoError ) goto error;
    
    
    return err;
error:
    Pa_Terminate();
    fprintf( stderr, "An error occurred while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    exit(-1);
    return err;
}

int InitAudio(int sample_rate, int frames_per_second)
{      
    PaError err;
    err = Pa_Initialize();    
    printf("Init\n");
    if( err != paNoError ) goto error;
   
    
    outputParameters.device = Pa_GetDefaultOutputDevice(); /* default output device */
    if (outputParameters.device == paNoDevice) {
        fprintf(stderr,"Error: No default output device.\n");
        goto error;
    }
    outputParameters.channelCount = 2;       /* stereo output */
    outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
    outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
    outputParameters.hostApiSpecificStreamInfo = NULL;

    
    err = Pa_OpenStream(
              &stream,
              NULL, /* no input */
              &outputParameters,
              sample_rate,
              frames_per_second,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              luaCallback,
              NULL );
    if( err != paNoError ) goto error;

    printf("Start\n") ;
    //err = Pa_SetStreamFinishedCallback( stream, &StreamFinished );
    //if( err != paNoError ) goto error;

    err = Pa_StartStream( stream );
    if( err != paNoError ) goto error;

    
    return err;
error:
    Pa_Terminate();
    fprintf( stderr, "An error occurred while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    exit(-1);
    return err;
}


int StopAudio()
{
    PaError err;
    err = Pa_StopStream( stream );
    if( err != paNoError ) goto error;

    err = Pa_CloseStream( stream );
    if( err != paNoError ) goto error;

    Pa_Terminate();
    printf("Test finished.\n");
    return 0;
error:
    Pa_Terminate();
    fprintf( stderr, "An error occurred while using the portaudio stream\n" );
    fprintf( stderr, "Error number: %d\n", err );
    fprintf( stderr, "Error message: %s\n", Pa_GetErrorText( err ) );
    exit(-1);
    return err;

}


void Stop()
{
    LockMidi();
    StopMidi();
    StopAudio();    
    pthread_mutex_destroy(&Lock);
}


