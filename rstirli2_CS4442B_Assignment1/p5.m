function w = p5(X_train,Y_train, iterNum)
    [~,xCol] = size(X_train);
    wPossibles = randn(xCol+1, iterNum);
    w= wPossibles(:,1);
    error = 1;
    for i = 1:iterNum
        testingW = wPossibles(:, i);
        testClassifications = p4(testingW, X_train);
        [testErr,~] = p2(testClassifications,Y_train);
        if testErr<error
            error = testErr;
            w=testingW;
        end
    end
    %w
    error
end