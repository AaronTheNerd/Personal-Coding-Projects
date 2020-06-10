function index = IndexFibo(magnitude)
% This function finds the index of the first term in the Fibonacci Sequence
% to contain magnitude digits
    digits(magnitude);
    Fibo = [];
    Fibo(1) = 1;
    Fibo(2) = 1;
    curr_num = Fibo(2);
    index = 3;
    min_num = vpa(10^(magnitude - 1));
    while (vpa(curr_num) < vpa(min_num))
        Fibo(index) = vpa(Fibo(index - 1) + Fibo(index - 2));
        curr_num = vpa(Fibo(index));
        index = index + 1;
    end
    
    save fibo.mat Fibo
end
