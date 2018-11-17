function eng = computeEngColor(im,W)
    %eng = W(1) * imR + W(2) * imG + W(3) * imB.
    %well... that was easy
    eng = W(1) * im(:,:,1) + W(2) * im(:,:,2) + W(3) * im(:,:,3);

end
