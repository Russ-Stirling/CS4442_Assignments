function [M,P] = seamV_DP(E)
    M = zeros(size(E));
    P = zeros(size(E));
    
    P(1,:) = -1;
    M(1,:) = E(1,:);
    
    [rows,cols] = size(E);
    
    for i=2:rows
       for j=1:cols
           range = j-1:j+1;
           fixer = j-2;
           if j==1
               range = j:j+1;
               fixer = 0;
           elseif j==cols
               range = j-1:j;
           end
           
           %this will get the first occurence of min so will take leftmost
           [mValue,pValue] = min(M(i-1, range));
           M(i,j) = mValue+E(i,j);
           P(i,j) = pValue + fixer;
       end
    end
    
    
end