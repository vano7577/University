
function lab4
syms x y;
eps = 10.^-2;
f(x,y) = sin(x+y)-y-1.2;
g(x,y) = 2*x+cos(y)-2;
F(x,y)=[f;g];
k=solve(f==0, x);
f11(y)=k(1);
f21(y)=solve(g==0, x);
disp(f11(y));
disp(f21(y));
J(x,y)=jacobian([f, g],[x, y]);
x0=[1.5;-3];
disp(F(x,y));
disp(J(x,y));
disp(inv(J(x0(1), x0(2))))
disp(F(x0(1), x0(2)))
dr(f11, f21);
root1=double(round(newton(F, J, x0, eps)/eps)*eps);
disp('метод Ньютона root1')
disp(root1);
% disp(double(f(root1(1), root1(2))))
% disp(double(g(root1(1), root1(2))))
x0=[1.2; -1.8];
root2=double(round(newton(F, J, x0, eps)/eps)*eps);
disp('метод Ньютона root2')
disp(root2);
% disp(double(f(root2(1), root2(2))))
% disp(double(g(root2(1), root2(2))))
x0=[0.7;0.9];
root3=double(round(newton(F, J, x0, eps)/eps)*eps);
disp('метод Ньютона root3')
disp(root3);
root11=root1;
root21=root2;
root31=root3;
% disp(double(f(root3(1), root3(2))))
% disp(double(g(root3(1), root3(2))))
disp('метод найскорейшего спуска')
disp(root11);
disp(root21);
disp(root31);
end
function dr(f1, f2)
y= linspace(-10,10);
figure
plot(y',[f1(y)' f2(y)']);
xlabel('y')
end
% function root = newton(F, J, x0, eps)
% p = round((x0 - (inv(J(x0(1), x0(2))))*F(x0(1), x0(2)))/eps)*eps;
% root= double(p);
% old_root = x0;
% while abs(old_root(1) - root(1))<= eps
% t = old_root;
% old_root = root;
% p = round((t - (inv(J(t(1), t(2))))*F(t(1), t(2)))/eps)*eps;
% root= double(p);
% end
function root = newton(F, J, x0, eps)
invj=inv(J);
root = x0 - (invj(x0(1), x0(2)))*F(x0(1), x0(2));
old_root = x0;
while abs(old_root(1) - root(1))&&abs(old_root(2) - root(2))<= eps
t = old_root;
old_root = root;
root = t - (invj(t(1), t(2)))*F(t(1), t(2));
end
end

