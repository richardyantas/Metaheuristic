%v = [0 0 0 0 1];
%P = perms(v)

%combos = combntns([2 2 5],2)
%m = dec2bin(0:10000000);
%disp("Ok")


%P = perms("001")
%P = perms( dec2bin([1:10]) )


% ****************** preprocessed
%m = dec2bin(0:2^10-1);

%10
p = [ 91  78 22  4  48  85  46  81 3  26];

pi = [0 55 23  35 44  5   91  95 26 40; 
      0 0  92  11 20  43  71  83 27 65;
      0 0  0   7  57  33  38  57 63 82;
      0 0  0   0  100 87  91  83 44 48; 
      0 0  0   0  0   69  57  79 89 21;
      0 0  0   0  0   0   9   40 22 26;
      0 0  0   0  0   0   0   50 6  7 ;
      0 0  0   0  0   0   0   0  71 52;
      0 0  0   0  0   0   0   0  0  17;];

w = [34 33 12 3 43 26 10 2 48 39];
Wmax = 145;

k = 1; % Solutions
%sol(1,:) = m(1,:) ;

MaxTotalValue = 0;
MinTotalValue = 10000000;
maxX = m(1,:);
for t=1:1024
  
  TotalWeigth = 0;
  for i=1:10
    if m(t,j) == '1'
      TotalWeigth = TotalWeigth + w(i)*(m(t,i)-'0');
    end
  end
  if TotalWeigth != 0
    TotalWeigth
  end
  
  if TotalWeigth<=Wmax     
%    sol(k,:) = m(t,:);
%    k++;   
    TotalValue = 0;
    for j=1:10
        if m(t,j) == '1'
          TotalValue = TotalValue + (m(t,j)-'0')*p(1,j);
        end
    end
    
    for i=1:9
      for j=i+1:10
        TotalValue = TotalValue + (m(t,i)-'0')*(m(t,j)-'0')*(pi(i,j));
      end
    end 
  
    if TotalValue>MaxTotalValue
      MaxTotalValue = TotalValue;
      maxX = m(t,:);
    end
  end
end

MaxTotalValue
maxX




