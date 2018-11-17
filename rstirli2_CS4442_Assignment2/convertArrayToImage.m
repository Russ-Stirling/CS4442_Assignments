function imageName = convertArrayToImage(array, saveAs)
    imwrite(uint8(array),saveAs);
    imageName = saveAs;
end