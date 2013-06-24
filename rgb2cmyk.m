function c = cmyk2rgb(c)

s = size(c);

c = 1 - c([1 2 3]);
%c = 1 - ( c([1 2 3]) + c([4 4 4]) );

 
   
