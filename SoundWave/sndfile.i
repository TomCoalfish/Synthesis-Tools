%module sndfile
%{
#include <sndfile.hh>
#include <vector>
#include <cassert>

using namespace std;
%}

%include "stdint.i"
%include "std_vector.i"




%template (byte_vector) std::vector<unsigned char>;
%template (short_vector) std::vector<short>;
%template (int_vector) std::vector<int>;
%template (float_vector) std::vector<float>;
%template (double_vector) std::vector<double>;

//%include <sndfile.h>

%inline 
%{

    struct SoundFile 
    {
        SndfileHandle * handle;
        
        SoundFile(char  *path, int mode = SFM_READ, int format = 0, int channels=0, int samplerate=0)
        {
            handle = new SndfileHandle(path,mode,format, channels, samplerate);            
        }

        ~SoundFile()
        {
            delete handle;
        }

        
        size_t frames() { return handle->frames(); }
        int    format() { return handle->format(); }
        int channels() { return handle->channels(); }
        int samplerate() { return handle->samplerate(); }
        int error() { return handle->error(); }
        const char * str_error() { return handle->strError(); }
        size_t seek(size_t frames, int whence) { return handle->seek(frames,whence); }
        void write_sync() { handle->writeSync(); }
        int set_string(int str_type, const char * str) { return handle->setString(str_type,str); }
        const char* get_string(int str_type) { return handle->getString(str_type); }
        int format_check(int format, int channels, int samplerate) { return handle->formatCheck(format, channels, samplerate); }

        size_t read( std::vector<short> & in, size_t n) { return handle->read(in.data(), n); }
        size_t read( std::vector<int> & in, size_t n) { return handle->read(in.data(), n); }
        size_t read( std::vector<float> & in, size_t n) { return handle->read(in.data(), n); }
        size_t read( std::vector<double> & in, size_t n) { return handle->read(in.data(), n); }

        size_t write( const std::vector<short> & out, size_t n) { return handle->write(out.data(), n); }
        size_t write( const std::vector<int> & out, size_t n) { return handle->write(out.data(), n); }
        size_t write( const std::vector<float> & out, size_t n) { return handle->write(out.data(), n); }
        size_t write( const std::vector<double> & out, size_t n) { return handle->write(out.data(), n); }

        size_t readf( std::vector<short> & in, size_t n) { return handle->readf(in.data(), n); }
        size_t readf( std::vector<int> & in, size_t n) { return handle->readf(in.data(), n); }
        size_t readf( std::vector<float> & in, size_t n) { return handle->readf(in.data(), n); }
        size_t readf( std::vector<double> & in, size_t n) { return handle->readf(in.data(), n); }

        size_t writef( const std::vector<short> & out, size_t n) { return handle->writef(out.data(), n); }
        size_t writef( const std::vector<int> & out, size_t n) { return handle->writef(out.data(), n); }
        size_t writef( const std::vector<float> & out, size_t n) { return handle->writef(out.data(), n); }
        size_t writef( const std::vector<double> & out, size_t n) { return handle->writef(out.data(), n); }

        SNDFILE* raw_handle() { return handle->rawHandle(); }
        SNDFILE* take_owndership() { return handle->takeOwnership();}
    };

    template<typename T>
    struct SoundFileReader
    {
        T * buffer;
        size_t N;
        SndfileHandle * handle;

        SoundFileReader() { buffer = nullptr; N = 0; }
        SoundFileReader(size_t n) {
            buffer = new T[N=n];
            assert(buffer != nullptr);
        }
        SoundFileReader(const SoundFileReader & sfr) {
            N = sfr.N;
            buffer = new T[N];
            memcpy(buffer,sfr.buffer,N*sizeof(T));
        }
        ~SoundFileReader() {            
            if(buffer) delete [] buffer;
            if(handle) delete handle;
        }

        void open(const char  *path, int mode = SFM_READ, int format = 0, int channels=0, int samplerate=0) {
            handle = new SndfileHandle(path,mode,format, channels, samplerate);            
            assert(handle != nullptr);
        }
        void close() {
            if(handle) delete handle;
            handle = nullptr;
        }
        virtual size_t read( size_t nn, std::vector<T> & in) = 0;        
        virtual size_t readf( size_t nn, std::vector<T> & in) = 0;        

        size_t frames() { return handle->frames(); }
        int    format() { return handle->format(); }
        int channels() { return handle->channels(); }
        int samplerate() { return handle->samplerate(); }
        int error() { return handle->error(); }
        const char * str_error() { return handle->strError(); }
        size_t seek(size_t frames, int whence) { return handle->seek(frames,whence); }
        void write_sync() { handle->writeSync(); }
        int set_string(int str_type, const char * str) { return handle->setString(str_type,str); }
        const char* get_string(int str_type) { return handle->getString(str_type); }
        int format_check(int format, int channels, int samplerate) { return handle->formatCheck(format, channels, samplerate); }
        SNDFILE* raw_handle() { return handle->rawHandle(); }
        SNDFILE* take_owndership() { return handle->takeOwnership();}
    };

    
    struct SoundFileReaderShort : public SoundFileReader<short>
    {
        size_t read(size_t n, std::vector<short> & in) {
            in.resize(n);
            return handle->read(in.data(), n);            
        }

        size_t readf(size_t n, std::vector<short> & in) {
            in.resize(n);
            return handle->readf(in.data(), n);            
        }
    };
    
    struct SoundFileReaderInt : public SoundFileReader<int>
    {
        size_t read(size_t n, std::vector<int> & in) {
            in.resize(n);
            return handle->read(in.data(), n);            
        }

        size_t readf(size_t n, std::vector<int> & in) {
            in.resize(n);
            return handle->readf(in.data(), n);            
        }
    };
    
    struct SoundFileReaderFloat : public SoundFileReader<float>
    {
        size_t read(size_t n, std::vector<float> & in) {
            in.resize(n);
            return handle->read(in.data(), n);            
        }

        size_t readf(size_t n, std::vector<float> & in) {
            in.resize(n);
            return handle->readf(in.data(), n);            
        }
    };
    
    struct SoundFileReaderDouble : public SoundFileReader<double>
    {
        size_t read(size_t n, std::vector<double> & in) {
            in.resize(n);
            return handle->read(in.data(), n);            
        }

        size_t readf(size_t n, std::vector<double> & in) {
            in.resize(n);
            return handle->readf(in.data(), n);            
        }
    };

    template<typename T>
    struct SoundFileWriter
    {
        T * buffer;
        size_t N;
        SndfileHandle * handle;

        SoundFileWriter() { buffer = nullptr; N = 0; }
        SoundFileWriter(size_t n) {
            buffer = new T[N=n];
            assert(buffer != nullptr);
        }
        SoundFileWriter(const SoundFileWriter & sfw) {
            N = sfw.N;
            buffer = new T[N];
            memcpy(buffer,sfw.buffer,N*sizeof(T));
        }
        ~SoundFileWriter() {            
            if(buffer) delete [] buffer;
            if(handle) delete handle;
        }

        void open(const char  *path, int mode = SFM_WRITE, int format = 0, int channels=0, int samplerate=0) {
            handle = new SndfileHandle(path,mode,format, channels, samplerate);            
            assert(handle != nullptr);
        }
        void close() {
            if(handle) delete handle;
            handle = nullptr;
        }
        virtual size_t write( size_t nn, std::vector<T> & in) = 0;        
        virtual size_t writef( size_t nn, std::vector<T> & in) = 0;        

        size_t frames() { return handle->frames(); }
        int    format() { return handle->format(); }
        int channels() { return handle->channels(); }
        int samplerate() { return handle->samplerate(); }
        int error() { return handle->error(); }
        const char * str_error() { return handle->strError(); }
        size_t seek(size_t frames, int whence) { return handle->seek(frames,whence); }
        void write_sync() { handle->writeSync(); }
        int set_string(int str_type, const char * str) { return handle->setString(str_type,str); }
        const char* get_string(int str_type) { return handle->getString(str_type); }
        int format_check(int format, int channels, int samplerate) { return handle->formatCheck(format, channels, samplerate); }
        SNDFILE* raw_handle() { return handle->rawHandle(); }
        SNDFILE* take_owndership() { return handle->takeOwnership();}
    };

    
    struct SoundFileWriterShort : public SoundFileWriter<short>
    {
        size_t write(size_t n, std::vector<short> & in) {
            in.resize(n);
            return handle->write(in.data(), n);            
        }

        size_t writef(size_t n, std::vector<short> & in) {
            in.resize(n);
            return handle->writef(in.data(), n);            
        }
    };
    
    struct SoundFileWriterInt : public SoundFileWriter<int>
    {
        size_t write(size_t n, std::vector<int> & in) {
            in.resize(n);
            return handle->write(in.data(), n);            
        }

        size_t writef(size_t n, std::vector<int> & in) {
            in.resize(n);
            return handle->writef(in.data(), n);            
        }
    };
    
    struct SoundFileWriterFloat : public SoundFileWriter<float>
    {
        size_t write(size_t n, std::vector<float> & in) {
            in.resize(n);
            return handle->write(in.data(), n);            
        }

        size_t writef(size_t n, std::vector<float> & in) {
            in.resize(n);
            return handle->writef(in.data(), n);            
        }
    };
    
    struct SoundFileWriterDouble : public SoundFileWriter<double>
    {
        size_t write(size_t n, std::vector<double> & in) {
            in.resize(n);
            return handle->write(in.data(), n);            
        }

        size_t writef(size_t n, std::vector<double> & in) {
            in.resize(n);
            return handle->writef(in.data(), n);            
        }
    };

%}

