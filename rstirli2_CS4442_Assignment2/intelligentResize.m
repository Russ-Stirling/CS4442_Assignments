function [totalCost,imOut] = intelligentResize(imInput,v,h,W,mask,maskWeight)
    %imInput = colour image input
    %v = number of verticle seams, positive adds, negative subtracts
    %h = number of horizontal seams, positive adds, negative subtracts
    %W = weight vector for colour energy
    %mask = mask image
    %maskWeight = mask image weight
    im4 = cat(3,imInput,mask);
    
    
    %given in question
    F = [-1, 0, 1];
    
    totalCost=0;
    loop = abs(h);
    if abs(v)>abs(h)
        loop = abs(v);
    end
    
    for i=1:loop
        if h>0
            eng = computeEng(im4,F,W,maskWeight);
            [~,im4,cost] = increaseHeight(im4,eng);
            totalCost = totalCost + cost;
            h = h-1;
        elseif h<0
            eng = computeEng(im4,F,W,maskWeight);
            [~,im4,cost] = reduceHeight(im4,eng);
            totalCost = totalCost + cost;
            h = h+1;
        end
        
        if v>0
            eng = computeEng(im4,F,W,maskWeight);
            [~,im4,cost] = increaseWidth(im4,eng);
            totalCost = totalCost + cost;
            v=v-1;
        elseif v<0
            eng = computeEng(im4,F,W,maskWeight);
            [~,im4,cost] = reduceWidth(im4,eng);
            totalCost = totalCost + cost;
            v=v+1;
        end
    end
    
    imOut = im4(:,:,1:3);
    
end
