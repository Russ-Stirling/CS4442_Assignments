function W = p9(X_Train,Y_Train, iterNum, WInit, alpha)
    [xRows, ~] =  size(X_Train);
    modifiedX = [ones(xRows,1), X_Train];
    currentW = WInit;
    for epoch = 1:iterNum
        for i = 1:xRows
           %do softmax stuff 
           sample = modifiedX(i, :);
           label = Y_Train(i, :);
           
           step1 =  (currentW * sample');
           step2 = mySoftmax(step1);
           
           yi = zeros(size(step2));
           yi(label) = 1;
           
           step3 = alpha*(yi - step2);
           
           step4 = step3 * sample;
           currentW = currentW + step4;
           
        end
    end
    W=currentW;
end