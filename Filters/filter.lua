
filt = { 
    x0 = 0;
    y0 = 0;
}

function filter(B,A,x)
    local y = B[1]*x + B[2]*filt.x0 - A[1]*filt.y0
    filt.x0 = x 
    filt.y0 = y 
    return y 
end 

X = {1,2,3,4,5,6,7,8,9,10}
B = {1,1}
A = {0}

for i=1,10 do 
    y = filter(B,A,X[i])
    print(y)
end
