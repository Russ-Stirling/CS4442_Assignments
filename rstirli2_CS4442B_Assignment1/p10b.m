function [err,CONF] = p10b(X_test,Y_test, net)
    yTestClassified = (net(X_test'));
    valueOfClassPosition = max(yTestClassified);
    [classFormatted, ~] = find(yTestClassified==valueOfClassPosition);
    
    [err,CONF] = p2(classFormatted,Y_test);
end