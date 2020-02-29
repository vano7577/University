function ex3
syms f(x) f1(x);
f1(x) = 1 - cos(x)/2;
f2(x)= asin(x + 6/5) - x;

figure
x = linspace(-10,10);
 plot(x',[f1(x)' f2(x)']);
% df = diff(f);
disp('our diff: ');

% 
% %disp(g);
% %Q = max(abs())
% %fi(x) = x-(f(x))/k
% x0=4;
% root = x0 - f(x0) / df(x0);
% old_root = x0;
% while abs(old_root - root) > 2 * eps
% t = old_root;
% old_root = root;
% root = t - f(t) / df(t);
% end
% disp (root);
% %syms y; 
% %y=str2num(root);
% tf = isa(root, 'double');
% disp(tf);
% disp(y);
% % Метод Ньютона
% % function root = newton(f, df, x0)
% % root = x0 - f(x0) / df(x0);
% % old_root = x0;
% % while abs(old_root - root) > 2 * eps
% % t = old_root;
% % old_root = root;
% % root = t - f(t) / df(t);
% end
