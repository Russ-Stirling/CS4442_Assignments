function [segm,e2]  = segmentGC(im,scribbleMask,lambda,numClusters,inftyCost)
    im
    scribbleMask
    %fg=2
    %bg=1
    [rows,cols,depth] = size(im)
    segm = zeros(rows,cols);
    e2=0;
    
    fgData = zeros(rows,cols)
    bgData = zeros(rows,cols)
    
    fgData(find(scribbleMask==1)) = inftyCost
    bgData(find(scribbleMask==2)) = inftyCost
    
    
    
    pixelIntensity = mean(im, 3);
    s = size(pixelIntensity)
    
    %find all neighbor pairs here
    for i=1:rows
        for j=1:cols
            if i==1
                
            elseif i==rows
               
            else
            end
            
            if j==1
                
            elseif j==cols
                    
            else
                    
            end
        end
    end
    
    %find sigma here by averaging neighbour differences
    
    %compute edge values for each neighbour
    value = 1 %for now until i can actually compute that
    
    %gotta calculate them all (every neighbour pair)
    edgeW = lambda*exp(value);
    
    
    
    
    %was nowhere near needing this but tried meessing around
    %thought id leave it in
    r=im(:,:,1);
    g=im(:,:,2);
    b=im(:,:,3);
    rgb=[r(:) g(:) b(:)];
    
    if numClusters>0
        [Idx,c]=kmeans(rgb,numClusters)
        
    %out 1 is fg, o is bg
    
    %set the forced vals
    segm(find(scribbleMask==1)) = 0
    segm(find(scribbleMask==2)) = 1
    
end