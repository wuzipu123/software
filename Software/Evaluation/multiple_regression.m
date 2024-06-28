function [Variables_for_statistics] = multiple_regression(sensor_data,calibration_data)
%'multiple_regression' uses data from sensor and reference to generate 8
%different calibrations. The data is stored in a cell containing 8 cells,
%where each one has the data for one calibration method. 

%not calibrated, lin reg wo offset, poly1, poly2, poly3, exp, power, reg_tree, 
%      1               2              3      4     5      6     7       8

%In each cell for one specific calibration method, the following structure
%is generated: 

%{{model_coefficients, predicted_data, observed_data, Name, Function}}
%{{        1          ,        2      ,        3     ,   4  ,  5    }}

%Important notice: While 'predicted_data' and 'observed_data' are stored as
%one column, 'model_coefficients' are stored in a row. 'lin_reg_wo_offset'
%has a value in the second row. The first value (1,1) represents the mean of
%the quotient between all data points, which is used for the calibration.
%The second value (2,1) is the standard deviation. This is not used in the
%calibration. 

%Variables_for_statistics={calibration method}{model_coefficients,predicted_data,observed_data,Name}
%Exactly this structure is needed for the functions 'statistics_table'
%and 'scatter_multiple'
%While 'scatter multiple' uses strictly this structure with the 8 calibration
%methods, the generated cell from this function can be expanded for
%'statistics_table', as long as the structure is kept the same

own_fit_mean=mean(sensor_data./calibration_data);
own_fit_std=std(sensor_data./calibration_data);
own_fit=[own_fit_mean;own_fit_std];
own_calibrated=sensor_data/own_fit_mean;

poly1=polyfit(sensor_data,calibration_data,1); 
polyval1=polyval(poly1,sensor_data);

poly2=polyfit(sensor_data,calibration_data,2);
polyval2=polyval(poly2,sensor_data);

poly3=polyfit(sensor_data,calibration_data,3);
polyval3=polyval(poly3,sensor_data); 

exp_fit=fit(sensor_data,calibration_data,'exp1');
exp1=coeffvalues(exp_fit);
expval=exp1(1,1)*exp(exp1(1,2)*sensor_data);

power_fit=fit(sensor_data,calibration_data,'power1');
power1=coeffvalues(power_fit);
powerval=power1(1,1)*sensor_data.^power1(1,2);

tree_fit=fitrtree(sensor_data,calibration_data);
tree=predict(tree_fit,sensor_data);

Function1=strcat('1*x');
Function2=strcat(num2str(own_fit(1,1)),'*x');
Function3=strcat(num2str(poly1(1,1)),'*x+',num2str(poly1(1,2)));
Function4=strcat(num2str(poly2(1,1)),'*x^2+',num2str(poly2(1,2)),'*x+',num2str(poly2(1,3)));
Function5=strcat(num2str(poly3(1,1)),'*x^3+',num2str(poly3(1,2)),'*x^2+',num2str(poly3(1,3)),'*x+',num2str(poly3(1,4)));
Function6=strcat(num2str(exp1(1,1)),'*exp(',num2str(exp1(1,2)),'*x)');
Function7=strcat(num2str(power1(1,1)),'*x^',num2str(power1(1,2)));

Variables_for_statistics={{1,sensor_data,calibration_data,'not calibrated',Function1},...
    {own_fit,own_calibrated,calibration_data,'linreg wo offset',Function2},...
    {poly1,polyval1,calibration_data,'poly1',Function3},...
    {poly2,polyval2,calibration_data,'poly2',Function4},...
    {poly3,polyval3,calibration_data,'poly3',Function5},...
    {exp1,expval,calibration_data,'exp',Function6},...
    {power1,powerval,calibration_data,'power',Function7},...
    {tree_fit,tree,calibration_data,'regression tree','/'}};





%{
polynom
1   x
2   a1*x
3   a1+a2*x
4   a1+a2*x+a3*x^2
5   a1+a2*x+a3*x^2+a4*x^3
6   a1*exp(a2*x)
7   a1*x^a2
8   /
%}


