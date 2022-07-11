require('sndfile')
s = sndfile.SoundFile('test.wav')
size = s:frames()
channels = s:channels()
format = s:format()
samplerate = s:samplerate()

print('format = ', format)
print('channels = ', channels)
print('samplerate = ', samplerate)
print('frames = ', size)

