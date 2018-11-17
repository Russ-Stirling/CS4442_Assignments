function eng = computeEngGrad(im,F)
    imgOut = sum(im, 3)/3;

    
    value1 = applyFilter(imgOut, F);
    value2 = applyFilter(imgOut, F.');
    
    value3 = value1.^2;
    value4 = value2.^2;
    
    eng = sqrt( value3+ value4 );
    %eng = sqrt(|F X imG|^2 + |FT X imG|^2)
    
end