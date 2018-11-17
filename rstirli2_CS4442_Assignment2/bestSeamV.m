function [seam,c] = bestSeamV(M,P)
    [rows,~] = size(M);
    
    seam=zeros(rows,1);
    
    %this will get the first occurence of min so will take leftmost
    [c, index] = min(M(rows, :));
    
    for i = rows:-1:1
        seam(i) = index;
        index = P(i,index);
    end
end