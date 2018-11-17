function[X_out,Y_out] = p1(X,Y,l1,l2)
    [I1,~] = find(Y==l1);
    [I2,~] = find(Y==l2);    
    
    X_1 = X(I1, :);
    X_2 = X(I2, :);
    
    X_out = [X_1;X_2];
    
    if l1<l2
        %l1 = 1
        I1(:,:) = 1;
        I2(:,:) = 2;
        
    else
        %l2=1
        I1(:,:) = 2;
        I2(:,:) = 1;
    end
    
    Y_out = [I1;I2];
end
