function [eig_val, eig_vec] = Power_Method(A, es, maxit)

[m, n]=size(A);
if m~=n, error('Error : it is not a square matrix'); end

SQorSYMM = 0;
for i = 1 : n
    for j = 1 : m
       if A(i,j) ~= A(j,i), SQorSYMM = SQorSYMM+1; end
    end   
end

if SQorSYMM ~= 0, disp('it is not a symmetric matrix'); error('It is not a symmetric matrix')
else
    disp('it is a symmetric matrix')
    
    it = 0;
    ea = 100;
    x = ones(m,1);
    eig_val_temp = 1;

    selection=input('Type max or min:', 's');

    switch selection
        case 'max'
        while(1)
            if ea <= es || it >= maxit, break, end
            x = A*x;
            temp =x(1);
            for i = 2:n
                if abs(temp) <= abs(x(i)), temp = x(i);end
            end 
            x = x/ temp;
            eig_vec_temp = x;
            ea = abs((temp - eig_val_temp)/temp*100);
            
            eig_val_temp = temp;
            it=it+1;
        end        

        case 'min'
        A=inv(A);
        while 1
            if ea <= es || it >= maxit, break, end
            x = A*x;
            temp =x(1);
            for i = 2:n
                if abs(temp) <= abs(x(i)), temp = x(i);end
            end 
            x = x/ temp;
            eig_vec_temp = x;
            ea = abs((temp - eig_val_temp)/temp*100);
            
            eig_val_temp = 1/temp;
            it=it+1;
        end
    end
    
 eig_val = eig_val_temp
 eig_vec = eig_vec_temp
end