function [seam,im,c] = reduceHeight(im,E)

    [originalRows,originalCols, depth] = size(im);
    
    transposedLayers = zeros(originalCols, originalRows, depth);
    
    %transpose each of the 4 layers
    for i=1:depth
        transposedLayers(:,:,i) = (im(:,:,i)).';
    end
    
    [seam,reducedImTranspose,c] = reduceWidth(transposedLayers,(E.'));
    
    [reducedRowsT,reducedColsT, depth] = size(reducedImTranspose);
    
    im=zeros(reducedColsT, reducedRowsT, depth);
    
    %and transpose back
    for i=1:depth
        im(:,:,i) = (reducedImTranspose(:,:,i)).';
    end 
end