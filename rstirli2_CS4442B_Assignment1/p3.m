function C = p3(X_train, Y_train, X_test,k)
    totalSamples = size(Y_train, 1);
    totalTests = size(X_test, 1);
    C = zeros(totalTests, 1);
    %using for loop as not using one causes failure on A1.mat data sue to
    %being unable to create a matrix that large
    for i = 1:totalTests
        testSample = X_test(i,:);
        testMatrix = repelem(testSample,totalSamples,1);
        absDiff = abs(X_train - testMatrix);
        absDiff = (absDiff.^2);
        distance = sum(absDiff,2);
        [~,I] = sort(distance);
        
        neighborsInd = I(1:k,:);
        neighbors = Y_train(neighborsInd);
        
        [theMode, frequency] = mode(neighbors);
        if frequency==1
            theMode = neighbors(1);
        end
        C(i) = theMode;
    end   
end
