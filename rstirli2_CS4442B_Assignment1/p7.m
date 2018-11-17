function C = p7(W,X)
    %x is (n x d) where n is number of samples
    % w is (m x (d+1)) where m = number of class, d = x columns
    
    [xRows, ~] =  size(X);
    
    %add column of 1's to x for multiplication
    %modified x is now (n X (d+1))
    modifiedX = [ones(xRows,1), X];
    
    linearClassification = modifiedX * W';
    
    [test, classCol] = max(linearClassification,[],2);
    
    C = classCol;
end