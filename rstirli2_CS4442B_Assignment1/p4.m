function C = p4(w,X)
    [xRows,~] = size(X);
    modifiedX = [ones(xRows,1), X];

    C = modifiedX*w;
    
    C(C>=0)=1;
    C(C<0)=2;
end
