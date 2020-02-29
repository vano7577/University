function ex
% Введём функцию f(x)
syms f(x) f1(x) f2(x);
f(x) = sqrt(x)-(x.^-1)*log(x+4)-1.5;
f1(x) = sqrt(x)-1.5;
f2(x)= (x.^-1)*log(x+4);

figure
x = linspace(-10,10);
 plot(x',[f1(x)' f2(x)']);
 
dif = diff(f);
disp(dif);
root1 = newton(f, dif, 4);
% Проверим корни
root2 = newtonnew(f, 4);
disp(root2)
a = round(root1*10^3)/10^3;
b = round(root2*10^3)/10^3;
h = double(a);
w = double(b);
disp('метод Ньютона')
disp(h);
disp('Разносный метод Ньютона с постоянным шагом')
disp(w);
% Метод Ньютона
function root = newton(f, df, x0)
eps = 0.001;
root = x0 - f(x0) / df(x0);
old_root = x0;
while abs(old_root - root) > 2 * eps
t = old_root;
old_root = root;
root = t - f(t) / df(t);
end
function rootnew = newtonnew(f, x0)
ep = 0.001;
rootnew= x0-(f(x0)*ep)/(f(x0+ep)-f(x0));
oldrootnew=x0; 
 disp(rootnew);
while abs(oldrootnew-rootnew)<eps
   
t=oldrootnew;
oldrootnew=rootnew;
rootnew= t-(f(t)*ep)/(f(t+ep)-f(t));
end