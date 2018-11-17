function imOut = addSeamV(im,seam)
    [seamSize, ~] = size(seam);
    [~,imCols,~] = size(im);
    imOut = zeros(seamSize, imCols+1, 4);
    
    
    
    for i=1:size(seam)
        %take values in im from 1 to 1 before the seam index
        imOut(i,1:seam(i), :)=im(i,1:seam(i), :);
        %add value at seam
        imOut(i,(seam(i)+1),:) = im(i,seam(i),:);
        %take values from 1 after the seem index to the end
        imOut(i, seam(i)+2:imCols+1, :) = im(i,seam(i)+1:imCols,:);
    end
end

