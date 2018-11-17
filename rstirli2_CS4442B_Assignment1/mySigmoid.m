function result = mySigmoid(t)
    result = zeros(size(t));
    result = 1./(1+ exp(-t));
end