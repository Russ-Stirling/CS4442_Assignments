function w = p6(X_Train, Y_Train, iterNum, wInit, alpha)
    [xRows,~] = size(X_Train);
    modifiedX = [ones(xRows,1), X_Train];
    [~,xModCols] = size(modifiedX);
    Y_Train(Y_Train==2)=0;
    currentW = wInit;
    for i = 1:iterNum
        test1 = modifiedX * currentW;
        test2 = mySigmoid(test1);
        
        test3 = Y_Train - test2;
        
        test4 = repmat(test3, 1, xModCols);
        test5 = test4.* modifiedX;
        test6 = sum(test5,1);
        test7 = alpha * test6;
        
        currentW = currentW + test7';
        
    end
    w = currentW;
end
