function [seam,im,c] = increaseWidth(im,E)
    [M,P] = seamV_DP(E);
    [seam,c] = bestSeamV(M,P);
    
    im = addSeamV(im,seam);
end
