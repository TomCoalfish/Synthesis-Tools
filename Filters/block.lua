filt = { 
    x0 = 0;
    y0 = 0;
}

-- y(n) = x(n) - x(n-1) + R * y(n-1)
-- R = 1 - (pi*2 * frequency /samplerate)

function filter(B,A,x)
    x = x + 5
    local y = B[1]*x + B[2]*filt.x0 - A[1]*filt.y0
    filt.x0 = x 
    filt.y0 = y 
    return y 
end 

X = {1,2,3,4,5,6,7,8,9,10}
B = {1,-1}
A = { -1*(1 - (math.pi*2*250/44100))}

for j=1,100 do
for i=1,10 do 
    y = filter(B,A,X[i])
    print(y)
end
end
