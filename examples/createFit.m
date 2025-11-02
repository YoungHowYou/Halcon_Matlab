function [fitresult, gof] = createFit(U, L)
%CREATEFIT(U,L)
%  创建一个拟合。
%
%  要进行 '无标题拟合 1' 拟合的数据:
%      X 输入: U
%      Y 输出: L
%  输出:
%      fitresult: 表示拟合的拟合对象。
%      gof: 带有拟合优度信息的结构体。
%
%  另请参阅 FIT, CFIT, SFIT.

%  由 MATLAB 于 27-Mar-2025 16:05:05 自动生成


%% 拟合: '无标题拟合 1'。
[xData, yData] = prepareCurveData( U, L );

% 设置 fittype 和选项。
ft = fittype( '(I01*(exp(x/(n1*0.0256064))-1)+I02*(exp(x/(n2*0.0256064))-1)+x/Rsh)/K', 'independent', 'x', 'dependent', 'y' );
opts = fitoptions( 'Method', 'NonlinearLeastSquares' );
opts.Display = 'Off';
opts.Lower = [0 0 0 500 0 0];
opts.Robust = 'LAR';
opts.StartPoint = [0 0 1 2500 1 1];
opts.Upper = [0.1 0.1 1000 5000 5 5];

% 对数据进行模型拟合。
[fitresult, gof] = fit( xData, yData, ft, opts );

% 绘制数据拟合图。
figure( 'Name', '无标题拟合 1' );
h = plot( fitresult, xData, yData );
legend( h, 'L vs. U', '无标题拟合 1', 'Location', 'NorthEast', 'Interpreter', 'none' );
% 为坐标区加标签
xlabel( 'U', 'Interpreter', 'none' );
ylabel( 'L', 'Interpreter', 'none' );
grid on


