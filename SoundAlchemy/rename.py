import os,sys

d = os.listdir('.')
for f in d:    
    
    if(f.split('.')[1] == 'i' and f[0]=='T'):
        print(f)
        os.system('cp ' + f + ' ' + 'SW' + f[1:])
