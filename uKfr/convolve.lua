require('kfr')

w = kfr.load_wav("test.wav")
v = kfr.load_wav("baby_elephant.wav")

x = kfr.convolve(w,v)
kfr.save_wav(x,"convolve.wav",1,kfr.audio_sample_type_f32,44100)