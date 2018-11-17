function imOut = removeSeamV(im,seam)
    [seamSize, ~] = size(seam);
    [~,imCols,~] = size(im);
    imOut = zeros(seamSize, imCols-1, 4);
    
    %imOut(:,1:seam()-1, :)=im(:,1:seam()-1, :);
    %take values from 1 after the seem index to the end
    %imOut(:, seam():imCols-1, :) = im(:,(seam()+1):imCols,:);
    
    for i=1:size(seam)
        %take values in im from 1 to 1 before the seam index
        imOut(i,1:seam(i)-1, :)=im(i,1:seam(i)-1, :);
        %take values from 1 after the seem index to the end
        imOut(i, seam(i):imCols-1, :) = im(i,(seam(i)+1):imCols,:);
    end
end