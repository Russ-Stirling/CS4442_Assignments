function outIm = applyFilter(im,F)
    [rows,cols] = size(F);
    [imR,imC] = size(im);
    rowPadding = (rows-1)/2;
    colPadding = (cols-1)/2;
    
    paddedIm = padarray(im,[rowPadding colPadding],0,'both');
    [padRows, padCols] = size(paddedIm);
    outIm = zeros(imR, imC);
    
    for i = (rowPadding+1):(padRows-rowPadding)
        for j = (colPadding+1):(padCols-colPadding)
            step1 = paddedIm((i-rowPadding):(i+rowPadding), (j-colPadding):(j+colPadding)).*F;
            step2 = sum(step1(:));
            
            outIm(i-rowPadding,j-colPadding)= step2;
            
        end
    end
end
