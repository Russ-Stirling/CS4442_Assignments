function result = mySoftmax(input)
    result = exp(input);
    result = result / sum(result);
end