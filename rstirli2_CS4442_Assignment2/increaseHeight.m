function [seam,im,c] = increaseHeight(im,E)
    [originalRows,originalCols, depth] = size(im);
    
    transposedLayers = zeros(originalCols, originalRows, depth);
    
    %transpose each of the 4 layers
    for i=1:depth
        transposedLayers(:,:,i) = (im(:,:,i)).';
    end
    
    [seam,incrImTranspose,c] = increaseWidth(transposedLayers,(E.'));
    
    [incrRowsT,incrColsT, depth] = size(incrImTranspose);
    
    im=zeros(incrColsT, incrRowsT, depth);
    
    %and transpose back
    for i=1:depth
        im(:,:,i) = (incrImTranspose(:,:,i)).';
    end 
end