function imageArray = convertImageToArray(fileName)
    A = imread(fileName);
    imageArray = double(A);
end