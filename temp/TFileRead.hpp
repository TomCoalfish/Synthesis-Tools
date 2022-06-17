#pragma once
#include "TStk.hpp"
#include <sys/stat.h>
#include <sys/types.h>
#include <cstring>
#include <cmath>
#include <cstdio>

namespace stk {

/***************************************************/
/*! \class FileRead
    \brief STK audio file input class.

    This class provides input support for various
    audio file formats.  Multi-channel (>2)
    soundfiles are supported.  The file data is
    returned via an external StkFrames<T> object
    passed to the read() function.  This class
    does not store its own copy of the file data,
    rather the data is read directly from disk.

    FileRead currently supports uncompressed WAV,
    AIFF/AIFC, SND (AU), MAT-file (Matlab), and
    STK RAW file formats.  Signed integer (8-,
    16-, 24-, and 32-bit) and floating-point (32- and
    64-bit) data types are supported.  Compressed
    data types are not supported.

    STK RAW files have no header and are assumed to
    contain a monophonic stream of 16-bit signed
    integers in big-endian byte order at a sample
    rate of 22050 Hz.  MAT-file data should be saved
    in an array with each data channel filling a
    matrix row.  The sample rate for MAT-files should
    be specified in a variable named "fs".  If no
    such variable is found, the sample rate is
    assumed to be 44100 Hz.

    by Perry R. Cook and Gary P. Scavone, 1995--2021.
*/
/***************************************************/

template<typename T>
class FileRead : public Stk<T>
{
public:
  //! Default constructor.
  FileRead( void );

  //! Overloaded constructor that opens a file during instantiation.
  /*!
    An StkError will be thrown if the file is not found or its
    format is unknown or unsupported.  The optional arguments allow a
    headerless file type to be supported.  If \c typeRaw is false (the
    default), the subsequent parameters are ignored.
  */
  FileRead( std::string fileName, bool typeRaw = false, unsigned int nChannels = 1,
            StkFormat format = STK_SINT16, T rate = 22050.0 );

  //! Class destructor.
  ~FileRead( void );

  //! Open the specified file and determine its formatting.
  /*!
    An StkError will be thrown if the file is not found or its
    format is unknown or unsupported.  The optional arguments allow a
    headerless file type to be supported.  If \c typeRaw is false (the
    default), the subsequent parameters are ignored.
  */
  void open( std::string fileName, bool typeRaw = false, unsigned int nChannels = 1,
             StkFormat format = STK_SINT16, T rate = 22050.0 );

  //! If a file is open, close it.
  void close( void );

  //! Returns \e true if a file is currently open.
  bool isOpen( void );

  //! Return the file size in sample frames.
  unsigned long fileSize( void ) const { return fileSize_; };

  //! Return the number of audio channels in the file.
  unsigned int channels( void ) const { return channels_; };

  //! Return the data format of the file.
  StkFormat format( void ) const { return dataType_; };

  //! Return the file sample rate in Hz.
  /*!
    WAV, SND, and AIF formatted files specify a sample rate in
    their headers.  By definition, STK RAW files have a sample rate of
    22050 Hz.  MAT-files are assumed to have a rate of 44100 Hz.
  */
  T fileRate( void ) const { return fileRate_; };

  //! Read sample frames from the file into an StkFrames<T> object.
  /*!
    The number of sample frames to read will be determined from the
    number of frames of the StkFrames<T> argument.  If this size is
    larger than the available data in the file (given the file size
    and starting frame index), the extra frames will be unaffected
    (the StkFrames<T> object will not be resized).  Optional parameters
    are provided to specify the starting sample frame within the file
    (default = 0) and whether to normalize the data with respect to
    fixed-point limits (default = true).  An StkError will be thrown
    if a file error occurs or if the number of channels in the
    StkFrames<T> argument is not equal to that in the file.
   */
  void read( StkFrames<T>& buffer, unsigned long startFrame = 0, bool doNormalize = true );

protected:

  // Get STK RAW file information.
  bool getRawInfo( const char *fileName, unsigned int nChannels,
                   StkFormat format, T rate );

  // Get WAV file header information.
  bool getWavInfo( const char *fileName );

  // Get SND (AU) file header information.
  bool getSndInfo( const char *fileName );

  // Get AIFF file header information.
  bool getAifInfo( const char *fileName );

  // Get MAT-file header information.
  bool getMatInfo( const char *fileName );

  // Helper function for MAT-file parsing.
  bool findNextMatArray( SINT32 *chunkSize, SINT32 *rows, SINT32 *columns, SINT32 *nametype );

  FILE *fd_;
  bool byteswap_;
  bool wavFile_;
  unsigned long fileSize_;
  unsigned long dataOffset_;
  unsigned int channels_;
  StkFormat dataType_;
  T fileRate_;
};

/***************************************************/
/*! \class FileRead
    \brief STK audio file input class.

    This class provides input support for various
    audio file formats.  Multi-channel (>2)
    soundfiles are supported.  The file data is
    returned via an external StkFrames<T> object
    passed to the read() function.  This class
    does not store its own copy of the file data,
    rather the data is read directly from disk.

    FileRead currently supports uncompressed WAV,
    AIFF/AIFC, SND (AU), MAT-file (Matlab), and
    STK RAW file formats.  Signed integer (8-,
    16-, 24- and 32-bit) and floating-point (32- and
    64-bit) data types are supported.  Compressed
    data types are not supported.

    STK RAW files have no header and are assumed to
    contain a monophonic stream of 16-bit signed
    integers in big-endian byte order at a sample
    rate of 22050 Hz.  MAT-file data should be saved
    in an array with each data channel filling a
    matrix row.  The sample rate for MAT-files should
    be specified in a variable named "fs".  If no
    such variable is found, the sample rate is
    assumed to be 44100 Hz.

    by Perry R. Cook and Gary P. Scavone, 1995--2021.
*/
/***************************************************/


template<typename T>
FileRead<T>::FileRead()
  : fd_(0), fileSize_(0), channels_(STK_NONE), dataType_(STK_NONE), fileRate_(0.0)
{
}

template<typename T>
FileRead<T>::FileRead( std::string fileName, bool typeRaw, unsigned int nChannels,
                      StkFormat format, T rate )
  : fd_(0)
{
  open( fileName, typeRaw, nChannels, format, rate );
}

template<typename T>
FileRead<T>::~FileRead()
{
  if ( fd_ )
    fclose( fd_ );
}

template<typename T>
void FileRead<T>::close( void )
{
  if ( fd_ ) fclose( fd_ );
  fd_ = 0;
  wavFile_ = false;
  fileSize_ = 0;
  channels_ = 0;
  dataType_ = STK_NONE;
  fileRate_ = 0.0;
}

template<typename T>
bool FileRead<T>::isOpen( void )
{
  if ( fd_ ) return true;
  else return false;
}

template<typename T>
void FileRead<T>::open( std::string fileName, bool typeRaw, unsigned int nChannels,
                       StkFormat format, T rate )
{
  // If another file is open, close it.
  close();

  // Try to open the file.
  fd_ = fopen( fileName.c_str(), "rb" );
  if ( !fd_ ) {
    this->oStream_ << "FileRead::open: could not open or find file (" << fileName << ")!";
    this->handleError( StkError::FILE_NOT_FOUND );
  }

  // Attempt to determine file type from header (unless RAW).
  bool result = false;
  if ( typeRaw )
    result = getRawInfo( fileName.c_str(), nChannels, format, rate );
  else {
    char header[12];
    if ( fread( &header, 4, 3, fd_ ) != 3 ) goto error;
    if ( !strncmp( header, "RIFF", 4 ) &&
         !strncmp( &header[8], "WAVE", 4 ) )
      result = getWavInfo( fileName.c_str() );
    else if ( !strncmp( header, ".snd", 4 ) )
      result = getSndInfo( fileName.c_str() );
    else if ( !strncmp( header, "FORM", 4 ) &&
              ( !strncmp( &header[8], "AIFF", 4 ) || !strncmp(&header[8], "AIFC", 4) ) )
      result = getAifInfo( fileName.c_str() );
    else {
      if ( fseek( fd_, 126, SEEK_SET ) == -1 ) goto error;
      if ( fread( &header, 2, 1, fd_ ) != 1 ) goto error;
      if ( !strncmp( header, "MI", 2 ) ||
           !strncmp( header, "IM", 2 ) )
        result = getMatInfo( fileName.c_str() );
      else {
        this->oStream_ << "FileRead::open: file (" << fileName << ") format unknown.";
        this->handleError( StkError::FILE_UNKNOWN_FORMAT );
      }
    }
  }

  // If here, we had a file type candidate but something else went wrong.
  if ( result == false )
    this->handleError( StkError::FILE_ERROR );

  // Check for empty files.
  if ( fileSize_ == 0 ) {
    this->oStream_ << "FileRead::open: file (" << fileName << ") data size is zero!";
    this->handleError( StkError::FILE_ERROR );
  }

  return;

 error:
  this->oStream_ << "FileRead::open: error reading file (" << fileName << ")!";
  this->handleError( StkError::FILE_ERROR );
}

template<typename T>
bool FileRead<T>::getRawInfo( const char *fileName, unsigned int nChannels, StkFormat format, T rate )
{
  // Use the system call "stat" to determine the file length.
  struct stat filestat;
  if ( stat(fileName, &filestat) == -1 ) {
    this->oStream_ << "FileRead: Could not stat RAW file (" << fileName << ").";
    return false;
  }
  if ( nChannels == 0 ) {
    this->oStream_ << "FileRead: number of channels can't be 0 (" << fileName << ").";
    return false;
  }

  // Rawwave files have no header and by default, are assumed to
  // contain a monophonic stream of 16-bit signed integers in
  // big-endian byte order at a sample rate of 22050 Hz.  However,
  // different parameters can be specified if desired.
  dataOffset_ = 0;
  channels_ = nChannels;
  dataType_ = format;
  fileRate_ = rate;
  int sampleBytes = 0;
  if ( format == STK_SINT8 ) sampleBytes = 1;
  else if ( format == STK_SINT16 ) sampleBytes = 2;
  else if ( format == STK_SINT32 || format == STK_FLOAT32 ) sampleBytes = 4;
  else if ( format == STK_FLOAT64 ) sampleBytes = 8;
  else {
    this->oStream_ << "FileRead: StkFormat " << format << " is invalid (" << fileName << ").";
    return false;
  }

  fileSize_ = (long) filestat.st_size / sampleBytes / channels_;  // length in frames

  byteswap_ = false;
#ifdef __LITTLE_ENDIAN__
  byteswap_ = true;
#endif

  return true;
}

template<typename T>
bool FileRead<T>::getWavInfo( const char *fileName )
{
  // Find "format" chunk ... it must come before the "data" chunk.
  char id[4];
  SINT32 chunkSize;
  if ( fread(&id, 4, 1, fd_) != 1 ) goto error;
  while ( strncmp(id, "fmt ", 4) ) {
    if ( fread(&chunkSize, 4, 1, fd_) != 1 ) goto error;
#ifndef __LITTLE_ENDIAN__
    this-> swap32((unsigned char *)&chunkSize);
#endif
    if ( fseek(fd_, chunkSize, SEEK_CUR) == -1 ) goto error;
    if ( fread(&id, 4, 1, fd_) != 1 ) goto error;
  }

  // Check that the data is not compressed.
  unsigned short format_tag;
  if ( fread(&chunkSize, 4, 1, fd_) != 1 ) goto error; // Read fmt chunk size.
  if ( fread(&format_tag, 2, 1, fd_) != 1 ) goto error;
#ifndef __LITTLE_ENDIAN__
  this->swap16((unsigned char *)&format_tag);
  this->swap32((unsigned char *)&chunkSize);
#endif
  if ( format_tag == 0xFFFE ) { // WAVE_FORMAT_EXTENSIBLE
    dataOffset_ = ftell(fd_);
    if ( fseek(fd_, 14, SEEK_CUR) == -1 ) goto error;
    unsigned short extSize;
    if ( fread(&extSize, 2, 1, fd_) != 1 ) goto error;
#ifndef __LITTLE_ENDIAN__
    this->swap16((unsigned char *)&extSize);
#endif
    if ( extSize == 0 ) goto error;
    if ( fseek(fd_, 6, SEEK_CUR) == -1 ) goto error;
    if ( fread(&format_tag, 2, 1, fd_) != 1 ) goto error;
#ifndef __LITTLE_ENDIAN__
    this->swap16((unsigned char *)&format_tag);
#endif
    if ( fseek(fd_, dataOffset_, SEEK_SET) == -1 ) goto error;
  }
  if ( format_tag != 1 && format_tag != 3 ) { // PCM = 1, FLOAT = 3
    this->oStream_ << "FileRead: "<< fileName << " contains an unsupported data format type (" << format_tag << ").";
    return false;
  }

  // Get number of channels from the header.
  SINT16 temp;
  if ( fread(&temp, 2, 1, fd_) != 1 ) goto error;
#ifndef __LITTLE_ENDIAN__
  this->swap16((unsigned char *)&temp);
#endif
  channels_ = (unsigned int ) temp;

  // Get file sample rate from the header.
  SINT32 srate;
  if ( fread(&srate, 4, 1, fd_) != 1 ) goto error;
#ifndef __LITTLE_ENDIAN__
  this->swap32((unsigned char *)&srate);
#endif
  fileRate_ = (T) srate;

  // Determine the data type.
  dataType_ = STK_NONE;
  if ( fseek(fd_, 6, SEEK_CUR) == -1 ) goto error;   // Locate bits_per_sample info.
  if ( fread(&temp, 2, 1, fd_) != 1 ) goto error;
#ifndef __LITTLE_ENDIAN__
  this->swap16((unsigned char *)&temp);
#endif
  if ( format_tag == 1 ) {
    if ( temp == 8 )
      dataType_ = STK_SINT8;
    else if ( temp == 16 )
      dataType_ = STK_SINT16;
    else if ( temp == 24 )
      dataType_ = STK_SINT24;
    else if ( temp == 32 )
      dataType_ = STK_SINT32;
  }
  else if ( format_tag == 3 ) {
    if ( temp == 32 )
      dataType_ = STK_FLOAT32;
    else if ( temp == 64 )
      dataType_ = STK_FLOAT64;
  }
  if ( dataType_ == 0 ) {
    this->oStream_ << "FileRead: " << temp << " bits per sample with data format " << format_tag << " are not supported (" << fileName << ").";
    return false;
  }

  // Jump over any remaining part of the "fmt" chunk.
  if ( fseek(fd_, chunkSize-16, SEEK_CUR) == -1 ) goto error;

  // Find "data" chunk ... it must come after the "fmt" chunk.
  if ( fread(&id, 4, 1, fd_) != 1 ) goto error;

  while ( strncmp(id, "data", 4) ) {
    if ( fread(&chunkSize, 4, 1, fd_) != 1 ) goto error;
#ifndef __LITTLE_ENDIAN__
    this->swap32((unsigned char *)&chunkSize);
#endif
    chunkSize += chunkSize % 2; // chunk sizes must be even
    if ( fseek(fd_, chunkSize, SEEK_CUR) == -1 ) goto error;
    if ( fread(&id, 4, 1, fd_) != 1 ) goto error;
  }

  // Get length of data from the header.
  SINT32 bytes;
  if ( fread(&bytes, 4, 1, fd_) != 1 ) goto error;
#ifndef __LITTLE_ENDIAN__
  this->swap32((unsigned char *)&bytes);
#endif
  fileSize_ = bytes / temp / channels_;  // sample frames
  fileSize_ *= 8;  // sample frames

  dataOffset_ = ftell(fd_);
  byteswap_ = false;
#ifndef __LITTLE_ENDIAN__
  byteswap_ = true;
#endif

  wavFile_ = true;
  return true;

 error:
  this->oStream_ << "FileRead: error reading WAV file (" << fileName << ").";
  return false;
}

template<typename T>
bool FileRead<T>::getSndInfo( const char *fileName )
{
  // Determine the data type.
  UINT32 format;
  if ( fseek(fd_, 12, SEEK_SET) == -1 ) goto error;   // Locate format
  if ( fread(&format, 4, 1, fd_) != 1 ) goto error;
#ifdef __LITTLE_ENDIAN__
    swap32((unsigned char *)&format);
#endif

  if (format == 2) dataType_ = STK_SINT8;
  else if (format == 3) dataType_ = STK_SINT16;
  else if (format == 4) dataType_ = STK_SINT24;
  else if (format == 5) dataType_ = STK_SINT32;
  else if (format == 6) dataType_ = STK_FLOAT32;
  else if (format == 7) dataType_ = STK_FLOAT64;
  else {
    this->oStream_ << "FileRead: data format in file " << fileName << " is not supported.";
    return false;
  }

  // Get file sample rate from the header.
  UINT32 srate;
  if ( fread(&srate, 4, 1, fd_) != 1 ) goto error;
#ifdef __LITTLE_ENDIAN__
  swap32((unsigned char *)&srate);
#endif
  fileRate_ = (T) srate;

  // Get number of channels from the header.
  UINT32 chans;
  if ( fread(&chans, 4, 1, fd_) != 1 ) goto error;
#ifdef __LITTLE_ENDIAN__
  swap32((unsigned char *)&chans);
#endif
  channels_ = chans;

  UINT32 offset;
  if ( fseek(fd_, 4, SEEK_SET) == -1 ) goto error;
  if ( fread(&offset, 4, 1, fd_) != 1 ) goto error;
#ifdef __LITTLE_ENDIAN__
  swap32((unsigned char *)&offset);
#endif
  dataOffset_ = offset;

  // Get length of data from the header.
  if ( fread(&fileSize_, 4, 1, fd_) != 1 ) goto error;
#ifdef __LITTLE_ENDIAN__
  swap32((unsigned char *)&fileSize_);
#endif
  // Convert to sample frames.
  if ( dataType_ == STK_SINT8 )
    fileSize_ /= channels_;
  if ( dataType_ == STK_SINT16 )
    fileSize_ /= 2 * channels_;
  else if ( dataType_ == STK_SINT24 )
    fileSize_ /= 3 * channels_;
  else if ( dataType_ == STK_SINT32 || dataType_ == STK_FLOAT32 )
    fileSize_ /= 4 * channels_;
  else if ( dataType_ == STK_FLOAT64 )
    fileSize_ /= 8 * channels_;

  byteswap_ = false;
#ifdef __LITTLE_ENDIAN__
  byteswap_ = true;
#endif

  return true;

 error:
  this->oStream_ << "FileRead: Error reading SND file (" << fileName << ").";
  return false;
}

template<typename T>
bool FileRead<T>::getAifInfo( const char *fileName )
{
  bool aifc = false;
  char id[4];

  // Determine whether this is AIFF or AIFC.
  if ( fseek(fd_, 8, SEEK_SET) == -1 ) goto error;
  if ( fread(&id, 4, 1, fd_) != 1 ) goto error;
  if ( !strncmp(id, "AIFC", 4) ) aifc = true;

  // Find "common" chunk
  SINT32 chunkSize;
  if ( fread(&id, 4, 1, fd_) != 1) goto error;
  while ( strncmp(id, "COMM", 4) ) {
    if ( fread(&chunkSize, 4, 1, fd_) != 1 ) goto error;
#ifdef __LITTLE_ENDIAN__
    swap32((unsigned char *)&chunkSize);
#endif
    chunkSize += chunkSize % 2; // chunk sizes must be even
    if ( fseek(fd_, chunkSize, SEEK_CUR) == -1 ) goto error;
    if ( fread(&id, 4, 1, fd_) != 1 ) goto error;
  }

  // Get number of channels from the header.
  SINT16 temp;
  if ( fseek(fd_, 4, SEEK_CUR) == -1 ) goto error; // Jump over chunk size
  if ( fread(&temp, 2, 1, fd_) != 1 ) goto error;
#ifdef __LITTLE_ENDIAN__
  swap16((unsigned char *)&temp);
#endif
  channels_ = temp;

  // Get length of data from the header.
  SINT32 frames;
  if ( fread(&frames, 4, 1, fd_) != 1 ) goto error;
#ifdef __LITTLE_ENDIAN__
  swap32((unsigned char *)&frames);
#endif
  fileSize_ = frames; // sample frames

  // Read the number of bits per sample.
  if ( fread(&temp, 2, 1, fd_) != 1 ) goto error;
#ifdef __LITTLE_ENDIAN__
  swap16((unsigned char *)&temp);
#endif

  // Get file sample rate from the header.  For AIFF files, this value
  // is stored in a 10-byte, IEEE Standard 754 floating point number,
  // so we need to convert it first.
  unsigned char srate[10];
  unsigned char exp;
  unsigned long mantissa;
  unsigned long last;
  if ( fread(&srate, 10, 1, fd_) != 1 ) goto error;
  mantissa = (unsigned long) *(unsigned long *)(srate+2);
#ifdef __LITTLE_ENDIAN__
  swap32((unsigned char *)&mantissa);
#endif
  exp = 30 - *(srate+1);
  last = 0;
  while (exp--) {
    last = mantissa;
    mantissa >>= 1;
  }
  if (last & 0x00000001) mantissa++;
  fileRate_ = (T) mantissa;

  byteswap_ = false;
#ifdef __LITTLE_ENDIAN__
  byteswap_ = true;
#endif

  // Determine the data format.
  dataType_ = STK_NONE;
  if ( aifc == false ) {
    if ( temp <= 8 ) dataType_ = STK_SINT8;
    else if ( temp <= 16 ) dataType_ = STK_SINT16;
    else if ( temp <= 24 ) dataType_ = STK_SINT24;
    else if ( temp <= 32 ) dataType_ = STK_SINT32;
  }
  else {
    if ( fread(&id, 4, 1, fd_) != 1 ) goto error;
    if ( !strncmp(id, "sowt", 4) ) { // uncompressed little-endian
      if ( byteswap_ == false ) byteswap_ = true;
      else byteswap_ = false;
    }
    if ( !strncmp(id, "NONE", 4) || !strncmp(id, "sowt", 4) ) {
      if ( temp <= 8 ) dataType_ = STK_SINT8;
      else if ( temp <= 16 ) dataType_ = STK_SINT16;
      else if ( temp <= 24 ) dataType_ = STK_SINT24;
      else if ( temp <= 32 ) dataType_ = STK_SINT32;
    }
    else if ( (!strncmp(id, "fl32", 4) || !strncmp(id, "FL32", 4)) && temp == 32 ) dataType_ = STK_FLOAT32;
    else if ( (!strncmp(id, "fl64", 4) || !strncmp(id, "FL64", 4)) && temp == 64 ) dataType_ = STK_FLOAT64;
  }
  if ( dataType_ == 0 ) {
    this->oStream_ << "FileRead: AIFF/AIFC file (" << fileName << ") has unsupported data type (" << id << ").";
    return false;
  }

  // Start at top to find data (SSND) chunk ... chunk order is undefined.
  if ( fseek(fd_, 12, SEEK_SET) == -1 ) goto error;

  // Find data (SSND) chunk
  if ( fread(&id, 4, 1, fd_) != 1 ) goto error;
  while ( strncmp(id, "SSND", 4) ) {
    if ( fread(&chunkSize, 4, 1, fd_) != 1 ) goto error;
#ifdef __LITTLE_ENDIAN__
    swap32((unsigned char *)&chunkSize);
#endif
    chunkSize += chunkSize % 2; // chunk sizes must be even
    if ( fseek(fd_, chunkSize, SEEK_CUR) == -1 ) goto error;
    if ( fread(&id, 4, 1, fd_) != 1 ) goto error;
  }

  // Skip over chunk size, offset, and blocksize fields
  if ( fseek(fd_, 12, SEEK_CUR) == -1 ) goto error;

  dataOffset_ = ftell(fd_);
  return true;

 error:
  this->oStream_ << "FileRead: Error reading AIFF file (" << fileName << ").";
  return false;
}

template<typename T>
bool FileRead<T>::findNextMatArray( SINT32 *chunkSize, SINT32 *rows, SINT32 *columns, SINT32 *nametype )
{
  // Look for the next data array element. The file pointer should be
  // at the data element type when this function is called.
  SINT32 datatype;
  *chunkSize = 0;
  do {
    if ( fseek(fd_, *chunkSize, SEEK_CUR) == -1 ) return false;
    if ( fread(&datatype, 4, 1, fd_) != 1 ) return false;
    if ( byteswap_ ) this->swap32((unsigned char *)&datatype);
    if ( fread(chunkSize, 4, 1, fd_) != 1 ) return false;
    if ( byteswap_ ) this->swap32((unsigned char *)chunkSize);
  } while ( datatype != 14 );

  // Check dimension subelement size to make sure 2D
  if ( fseek(fd_, 20, SEEK_CUR) == -1 ) return false;
  SINT32 size;
  if ( fread(&size, 4, 1, fd_) != 1 ) return false;
  if ( byteswap_ ) this->swap32((unsigned char *)&size);
  if ( size != 8 ) return false;

  // Read dimensions data
  if ( fread(rows, 4, 1, fd_) != 1 ) return false;
  if ( byteswap_ ) this->swap32((unsigned char *)rows);
  if ( fread(columns, 4, 1, fd_) != 1 ) return false;
  if ( byteswap_ ) this->swap32((unsigned char *)columns);

  // Read array name subelement type
  if ( fread(nametype, 4, 1, fd_) != 1 ) return false;
  if ( byteswap_ ) this->swap32((unsigned char *)nametype);

  return true;
}

template<typename T>
bool FileRead<T>::getMatInfo( const char *fileName )
{
  // MAT-file formatting information is available at:
  // http://www.mathworks.com/access/helpdesk/help/pdf_doc/matlab/matfile_format.pdf

  // Verify this is a version 5 MAT-file format.
  char head[5];
  if ( fseek(fd_, 0, SEEK_SET) == -1 ) goto error;
  if ( fread(&head, 4, 1, fd_) != 1 ) goto error;
  // If any of the first 4 characters of the header = 0, then this is
  // a Version 4 MAT-file.
  head[4] = '\0';
  if ( strstr(head, "0") ) {
    this->oStream_ << "FileRead: " << fileName << " appears to be a Version 4 MAT-file, which is not currently supported.";
    return false;
  }

  // Determine the endian-ness of the file.
  char mi[2];
  byteswap_ = false;
  // Locate "M" and "I" characters in header.
  if ( fseek(fd_, 126, SEEK_SET) == -1 ) goto error;
  if ( fread(&mi, 2, 1, fd_) != 1) goto error;
#ifdef __LITTLE_ENDIAN__
  if ( !strncmp(mi, "MI", 2) )
    byteswap_ = true;
  else if ( strncmp(mi, "IM", 2) ) goto error;
#else
  if ( !strncmp(mi, "IM", 2))
    byteswap_ = true;
  else if ( strncmp(mi, "MI", 2) ) goto error;
#endif

  // We are expecting a data element containing the audio data and an
  // optional data element containing the sample rate (with an array
  // name of "fs").  Both elements should be stored as a Matlab array
  // type (14).

  bool doneParsing, haveData, haveSampleRate;
  SINT32 chunkSize, rows, columns, nametype;
  long dataoffset;
  doneParsing = false;
  haveData = false;
  haveSampleRate = false;
  while ( !doneParsing ) {

    dataoffset = ftell( fd_ ); // save location in file
    if ( findNextMatArray( &chunkSize, &rows, &columns, &nametype ) == false ) {
      // No more Matlab array type chunks found.
      if ( !haveData ) {
        this->oStream_ << "FileRead: No audio data found in MAT-file (" << fileName << ").";
        return false;
      }
      else if ( !haveSampleRate ) {
        fileRate_ = 44100.0;
        this->oStream_ << "FileRead: No sample rate found ... assuming 44100.0";
        this->handleError( StkError::WARNING );
        return true;
      }
      else return true;
    }

    if ( !haveSampleRate && rows == 1 && columns == 1 ) { // Parse for sample rate.

      SINT32 namesize = 4;
      if ( nametype == 1 ) { // array name > 4 characters
        if ( fread(&namesize, 4, 1, fd_) != 1 ) goto error;
        if ( byteswap_ ) this->swap32((unsigned char *)&namesize);
        if ( namesize != 2 ) goto tryagain; // expecting name = "fs"
        namesize = 8; // field must be padded to multiple of 8 bytes
      }
      char name[3]; name[2] = '\0';
      if ( fread(&name, 2, 1, fd_) != 1) goto error;
      if ( strncmp(name, "fs", 2) ) goto tryagain;

      // Jump to real part data subelement, which is likely to be in a
      // small data format.
      if ( fseek(fd_, namesize-2, SEEK_CUR) == -1 ) goto error;
      UINT32 type;
      T srate;
      if ( fread(&type, 4, 1, fd_) != 1 ) goto error;
      if ( byteswap_ ) this->swap32((unsigned char *)&type);
      if ( (type & 0xffff0000) != 0 ) // small data format
        type = (type & 0x0000ffff);
      else
        if ( fseek(fd_, 4, SEEK_CUR) == -1 ) goto error;
      if ( type == 1 ) { // SINT8
        signed char rate;
        if ( fread(&rate, 1, 1, fd_) != 1 ) goto error;
        srate = (T) rate;
      }
      else if ( type == 2 ) { // UINT8
        unsigned char rate;
        if ( fread(&rate, 1, 1, fd_) != 1 ) goto error;
        srate = (T) rate;
      }
      else if ( type == 3 ) { // SINT16
        SINT16 rate;
        if ( fread(&rate, 2, 1, fd_) != 1 ) goto error;
        if ( byteswap_ ) this->swap16((unsigned char *)&rate);
        srate = (T) rate;
      }
      else if ( type == 4 ) { // UINT16
        UINT16 rate;
        if ( fread(&rate, 2, 1, fd_) != 1 ) goto error;
        if ( byteswap_ ) this->swap16((unsigned char *)&rate);
        srate = (T) rate;
      }
      else if ( type == 5 ) { // SINT32
        SINT32 rate;
        if ( fread(&rate, 4, 1, fd_) != 1 ) goto error;
        if ( byteswap_ ) this->swap32((unsigned char *)&rate);
        srate = (T) rate;
      }
      else if ( type == 6 ) { // UINT32
        UINT32 rate;
        if ( fread(&rate, 4, 1, fd_) != 1 ) goto error;
        if ( byteswap_ ) this->swap32((unsigned char *)&rate);
        srate = (T) rate;
      }
      else if ( type == 7 ) { // FLOAT32
        FLOAT32 rate;
        if ( fread(&rate, 4, 1, fd_) != 1 ) goto error;
        if ( byteswap_ ) this->swap32((unsigned char *)&rate);
        srate = (T) rate;
      }
      else if ( type == 9 ) { // FLOAT64
        FLOAT64 rate;
        if ( fread(&rate, 8, 1, fd_) != 1 ) goto error;
        if ( byteswap_ ) this->swap64((unsigned char *)&rate);
        srate = (T) rate;
      }
      else
        goto tryagain;

      if ( srate > 0 ) fileRate_ = srate;
      haveSampleRate = true;
    }
    else if ( !haveData ) { // Parse for data.

      // Assume channels = smaller of rows or columns.
      if ( rows < columns ) {
        channels_ = rows;
        fileSize_ = columns;
      }
      else {
        this->oStream_ << "FileRead: Transpose the MAT-file array so that audio channels fill matrix rows (not columns).";
        return false;
      }

      SINT32 namesize = 4;
      if ( nametype == 1 ) { // array name > 4 characters
        if ( fread(&namesize, 4, 1, fd_) != 1 ) goto error;
        if ( byteswap_ ) this->swap32((unsigned char *)&namesize);
        namesize = (SINT32) ceil((float)namesize / 8);
        if ( fseek( fd_, namesize*8, SEEK_CUR) == -1 ) goto error;  // jump over array name
      }
      else {
        if ( fseek( fd_, 4, SEEK_CUR ) == -1 ) goto error;
      }

      // Now at real part data subelement
      SINT32 type;
      if ( fread(&type, 4, 1, fd_) != 1 ) goto error;
      if ( byteswap_ ) this->swap32((unsigned char *)&type);
      if ( type == 1 )  dataType_ = STK_SINT8;
      else if ( type == 3 ) dataType_ = STK_SINT16;
      else if ( type == 5 ) dataType_ = STK_SINT32;
      else if ( type == 7 ) dataType_ = STK_FLOAT32;
      else if ( type == 9 ) dataType_ = STK_FLOAT64;
      else {
        this->oStream_ << "FileRead: The MAT-file array data format (" << type << ") is not supported.";
        return false;
      }

      // Jump to the data.
      if ( fseek(fd_, 4, SEEK_CUR) == -1 ) goto error;
      dataOffset_ = ftell(fd_);
      haveData = true;
    }

  tryagain:
    if ( haveData && haveSampleRate ) doneParsing = true;
    else // jump to end of data element and keep trying
      if ( fseek( fd_, dataoffset+chunkSize+8, SEEK_SET) == -1 ) goto error;
  }

  return true;

 error:
  this->oStream_ << "FileRead: Error reading MAT-file (" << fileName << ") header.";
  return false;
}

template<typename T>
void FileRead<T>::read( StkFrames<T>& buffer, unsigned long startFrame, bool doNormalize )
{
  // Make sure we have an open file.
  if ( fd_ == 0 ) {
    this->oStream_ << "FileRead::read: a file is not open!";
    Stk<T>::handleError( StkError::WARNING ); return;
  }

  // Check the buffer size.
  unsigned long nFrames = buffer.frames();
  if ( nFrames == 0 ) {
    this->oStream_ << "FileRead::read: StkFrames<T> buffer size is zero ... no data read!";
    Stk<T>::handleError( StkError::WARNING ); return;
  }

  if ( buffer.channels() != channels_ ) {
    this->oStream_ << "FileRead::read: StkFrames<T> argument has incompatible number of channels!";
    Stk<T>::handleError( StkError::FUNCTION_ARGUMENT );
  }

  if ( startFrame >= fileSize_ ) {
    this->oStream_ << "FileRead::read: startFrame argument is greater than or equal to the file size!";
    Stk<T>::handleError( StkError::FUNCTION_ARGUMENT );
  }

  // Check for file end.
  if ( startFrame + nFrames > fileSize_ )
    nFrames = fileSize_ - startFrame;

  long i, nSamples = (long) ( nFrames * channels_ );
  unsigned long offset = startFrame * channels_;

  // Read samples into StkFrames<T> data buffer.
  if ( dataType_ == STK_SINT16 ) {
    SINT16 *buf = (SINT16 *) &buffer[0];
    if ( fseek( fd_, dataOffset_+(offset*2), SEEK_SET ) == -1 ) goto error;
    if ( fread( buf, nSamples * 2, 1, fd_ ) != 1 ) goto error;
    if ( byteswap_ ) {
      SINT16 *ptr = buf;
      for ( i=nSamples-1; i>=0; i-- )
        this->swap16( (unsigned char *) ptr++ );
    }
    if ( doNormalize ) {
      T gain = 1.0 / 32768.0;
      for ( i=nSamples-1; i>=0; i-- )
        buffer[i] = buf[i] * gain;
    }
    else {
      for ( i=nSamples-1; i>=0; i-- )
        buffer[i] = buf[i];
    }
  }
  else if ( dataType_ == STK_SINT32 ) {
    SINT32 *buf = (SINT32 *) &buffer[0];
    if ( fseek( fd_, dataOffset_+(offset*4 ), SEEK_SET ) == -1 ) goto error;
    if ( fread( buf, nSamples * 4, 1, fd_ ) != 1 ) goto error;
    if ( byteswap_ ) {
      SINT32 *ptr = buf;
      for ( i=nSamples-1; i>=0; i-- )
        this->swap32( (unsigned char *) ptr++ );
    }
    if ( doNormalize ) {
      T gain = 1.0 / 2147483648.0;
      for ( i=nSamples-1; i>=0; i-- )
        buffer[i] = buf[i] * gain;
    }
    else {
      for ( i=nSamples-1; i>=0; i-- )
        buffer[i] = buf[i];
    }
  }
  else if ( dataType_ == STK_FLOAT32 ) {
    FLOAT32 *buf = (FLOAT32 *) &buffer[0];
    if ( fseek( fd_, dataOffset_+(offset*4), SEEK_SET ) == -1 ) goto error;
    if ( fread( buf, nSamples * 4, 1, fd_ ) != 1 ) goto error;
    if ( byteswap_ ) {
      FLOAT32 *ptr = buf;
      for ( i=nSamples-1; i>=0; i-- )
        this->swap32( (unsigned char *) ptr++ );
    }
    for ( i=nSamples-1; i>=0; i-- )
      buffer[i] = buf[i];
  }
  else if ( dataType_ == STK_FLOAT64 ) {
    FLOAT64 *buf = (FLOAT64 *) &buffer[0];
    if ( fseek( fd_, dataOffset_+(offset*8), SEEK_SET ) == -1 ) goto error;
    if ( fread( buf, nSamples * 8, 1, fd_ ) != 1 ) goto error;
    if ( byteswap_ ) {
      FLOAT64 *ptr = buf;
      for ( i=nSamples-1; i>=0; i-- )
        this->swap64( (unsigned char *) ptr++ );
    }
    for ( i=nSamples-1; i>=0; i-- )
      buffer[i] = buf[i];
  }
  else if ( dataType_ == STK_SINT8 && wavFile_ ) { // 8-bit WAV data is unsigned!
    unsigned char *buf = (unsigned char *) &buffer[0];
    if ( fseek( fd_, dataOffset_+offset, SEEK_SET ) == -1 ) goto error;
    if ( fread( buf, nSamples, 1, fd_) != 1 ) goto error;
    if ( doNormalize ) {
      T gain = 1.0 / 128.0;
      for ( i=nSamples-1; i>=0; i-- )
        buffer[i] = ( buf[i] - 128 ) * gain;
    }
    else {
      for ( i=nSamples-1; i>=0; i-- )
        buffer[i] = buf[i] - 128.0;
    }
  }
  else if ( dataType_ == STK_SINT8 ) { // signed 8-bit data
    char *buf = (char *) &buffer[0];
    if ( fseek( fd_, dataOffset_+offset, SEEK_SET ) == -1 ) goto error;
    if ( fread( buf, nSamples, 1, fd_ ) != 1 ) goto error;
    if ( doNormalize ) {
      T gain = 1.0 / 128.0;
      for ( i=nSamples-1; i>=0; i-- )
        buffer[i] = buf[i] * gain;
    }
    else {
      for ( i=nSamples-1; i>=0; i-- )
        buffer[i] = buf[i];
    }
  }
  else if ( dataType_ == STK_SINT24 ) {
    // 24-bit values are harder to import efficiently since there is
    // no native 24-bit type.  The following routine works but is much
    // less efficient than that used for the other data types.
    SINT32 temp;
    unsigned char *ptr = (unsigned char *) &temp;
    T gain = 1.0 / 2147483648.0;
    if ( fseek(fd_, dataOffset_+(offset*3), SEEK_SET ) == -1 ) goto error;
    for ( i=0; i<nSamples; i++ ) {
#ifdef __LITTLE_ENDIAN__
      if ( byteswap_ ) {
        if ( fread( ptr, 3, 1, fd_ ) != 1 ) goto error;
        temp &= 0x00ffffff;
        this->swap32( (unsigned char *) ptr );
      }
      else {
        if ( fread( ptr+1, 3, 1, fd_ ) != 1 ) goto error;
        temp &= 0xffffff00;
      }
#else
      if ( byteswap_ ) {
        if ( fread( ptr+1, 3, 1, fd_ ) != 1 ) goto error;
        temp &= 0xffffff00;
        this->swap32( (unsigned char *) ptr );
      }
      else {
        if ( fread( ptr, 3, 1, fd_ ) != 1 ) goto error;
        temp &= 0x00ffffff;
      }
#endif

      if ( doNormalize ) {
        buffer[i] = (T) temp * gain; // "gain" also  includes 1 / 256 factor.
      }
      else
        buffer[i] = (T) temp / 256;  // right shift without affecting the sign bit
    }
  }

  buffer.setDataRate( fileRate_ );

  return;

 error:
  this->oStream_ << "FileRead: Error reading file data.";
  this->handleError( StkError::FILE_ERROR);
}

} // stk namespace