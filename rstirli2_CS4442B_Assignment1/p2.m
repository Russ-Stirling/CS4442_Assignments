function [err,CONF] = p2(C,T)
    %put t and c together into one matrix
    TC = [T,C];
    
    %identify the unique classes
    classes = unique(TC);
    
    totalTrueLabels = length(T);
    totalClasses = max(TC(:));
    
    subscripts = ones(totalTrueLabels,1);
    
    CONF = accumarray(TC,subscripts,[totalClasses,totalClasses]);
    
    diagonalSum = trace(CONF);
    
    err = (totalTrueLabels-diagonalSum)/totalTrueLabels;
    
end