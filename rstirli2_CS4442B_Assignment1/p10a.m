function [net,valErr] = p10a(X_train,Y_train, H, regularizerWeight)
    net = patternnet(H);
    
    net.divideParam.testRatio = 0;
    net.divideParam.valRatio = 0.3;
    net.divideParam.trainRatio = 0.7;
    
    net.performParam.regularization = regularizerWeight;
    
    X = X_train.';
    
    [~, cols] = size(X);
    
    Y = zeros(max(Y_train), cols);
    
    for i=1:cols
        Y(Y_train(i),i)=1;
    end
    
    [net,tr] = train(net,X,Y);
    
    %testCases = X_train(tr.valInd,1: size(X_train, 2))
    testCase = X(:, tr.valInd);
    
    yTestClassified = (net(testCase));
    valueOfClassPosition = max(yTestClassified);
    [classFormatted, ~] = find(yTestClassified==valueOfClassPosition);
    
    yTrueLabels = Y_train(tr.valInd, 1);
    
    [valErr, ~] = p2(classFormatted,yTrueLabels);
    
    
end