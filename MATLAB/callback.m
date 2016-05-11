
%%
function callback(s, BytesAvailable)
    out = fscanf(s);
    disp(out);
end