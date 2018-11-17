function W = p8(X_train, Y_train, iterNum, WInit, alpha)
    [xRows, ~] =  size(X_train);
    modifiedX = [ones(xRows,1), X_train];
    currentW = WInit;
    for epoch = 1:iterNum
        for i = 1:xRows
            %sample = 1 x (d+1)
            sample = modifiedX(i,:);
            label = Y_train(i,:);
            %step1 =  (1 x (d+1)) * (m x (d+1))'
            %step1= 1 x m
            step1 =  sample * currentW.';
            
            % Finding max in all entries
            %maxCol is the class prediction
            [~, maxCol] = max(step1.');
            if label ~= maxCol
                %it was misclassified so we need to update w(Label,:) and
                %w(maxCol,2)
                currentW(label,:) = currentW(label,:) + alpha*sample;
                currentW(maxCol,:) = currentW(maxCol,:) - alpha*sample;
            end
        end
    end
    W = currentW;
end