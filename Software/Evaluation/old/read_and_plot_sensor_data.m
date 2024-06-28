%IMPORT 
%set path 
datapath = 'C:\Users\mknoll\Nextcloud\Study\Work\Projects\SensMat\SensMat\Measurement\Data\Zeughaus_Messung_191230_200129\Sensor2_secondfloor_2m_window';
addpath(datapath)
%import OPC data from path
OPC=readtable('Data_OPC-N3_10_12_2019_12_56.csv');
%import SPS data from path
SPS=readtable('Data_SPS30_10_12_2019_12_56.csv');


%CALCULATE
%convert date and time 
%imput for time adjustment 
%sensor_object_date={{OPC_date,OPC_time},{SPS_date,SPS_time}} 
sensor_object_date={{OPC.Timestamp,OPC.Var2},{SPS.Timestamp,SPS.Var2}};


%function to adjust cell data to a plottable time 
%[plot_time_OPC, plot_time_SPS] = time_adjustment(OPC_date,OPC_time,SPS_date,SPS_time)
[plot_time_OPC,plot_time_SPS] = time_adjustment(sensor_object_date{1}{1},sensor_object_date{1}{2},...
                                                sensor_object_date{2}{1},sensor_object_date{2}{2});

%%particle data OPC (all bins)
OPC_PN_s=OPC{1:end,3:end-1}; %values #/sec 

%conversion of #/sec to #/cm^3  with flow rate 210mL/min => *(210/60))
OPC_PN_c=OPC_PN_s*(210/60); %values #/cm^3

%OPC bin upper limit 
bin_size_pn_0_5=1;
bin_size_pn_1=3; % bin border 2.3 
bin_size_pn_2_5=6;
bin_size_pn_4=8;
bin_size_pn_10=12;

%summs up the bins according to the upper bin limits defined above 
OPC_PN=[OPC_PN_c(:,bin_size_pn_0_5),sum(OPC_PN_c(:,1:bin_size_pn_1),2),...
                sum(OPC_PN_c(:,1:bin_size_pn_2_5),2),sum(OPC_PN_c(:,1:bin_size_pn_4),2),...
                sum(OPC_PN_c(:,1:bin_size_pn_10),2)];
    
%calculates mean values for OPC 
mean_OPC=max(OPC_PN); 
%normalizes all bins 
OPC_normalize=OPC_PN./mean_OPC;

%particle data SPS: PN0.5,PN1,PN2.5,PN4,PN10
SPS_PN=SPS{1:end,7:11};
%mean values 
% calculate mean value for SPS
mean_SPS=max(SPS_PN);
%normalizes SPS_PN numerical values with SPS mean values 
SPS_normalize=SPS_PN./mean_SPS;


% PLOTS 
%initialize 
%sensor_object_plot={{'OPC_name', OPC_time, OPC_matrix, 'OPC_legend',title_subplot},...
                    %{'SPS_name', SPS_time, SPS_matrix, 'SPS_legend',title_subplot}};
title_subplot={{'PN 0.5'},{'PN 1'},{'PN 2.5'},{'PN 4'},{'PN 10'}};
sensor_object_plot_normalize={{'OPC normalized',plot_time_OPC,OPC_normalize,'OPC',title_subplot},...
                    {'SPS normalized',plot_time_SPS,SPS_normalize,'SPS',title_subplot}};
%initialize for raw data 
sensor_object_plot_raw={{'OPC raw',plot_time_OPC,OPC_PN,'OPC',title_subplot},...
                    {'SPS raw',plot_time_SPS,SPS_PN,'SPS',title_subplot}};

% call plot function 
particle_plot_multiple(sensor_object_plot_normalize)
particle_plot_multiple(sensor_object_plot_raw)

% Correlation coefficients for the different PM size fractions
corr_PM0_5 = corr(sensor_object_plot_normalize{1}{3}(:,1), sensor_object_plot_normalize{2}{3}(:,1))
corr_PM1 = corr(sensor_object_plot_normalize{1}{3}(:,2), sensor_object_plot_normalize{2}{3}(:,2))
corr_PM2_5 = corr(sensor_object_plot_normalize{1}{3}(:,3), sensor_object_plot_normalize{2}{3}(:,3))
corr_PM4 = corr(sensor_object_plot_normalize{1}{3}(:,4), sensor_object_plot_normalize{2}{3}(:,4))
corr_PM10 = corr(sensor_object_plot_normalize{1}{3}(:,5), sensor_object_plot_normalize{2}{3}(:,5))

figure;
plot(sensor_object_plot_normalize{1}{2},sensor_object_plot_normalize{1}{3}(:,5)); 
hold on
%x-axis time. y-axis PN data 
plot(sensor_object_plot_normalize{2}{2},sensor_object_plot_normalize{2}{3}(:,5)); 
%converts serial date numbers back to the imput format 'dd.mm.yyyy HH:MM:SS'
datetick('x')
%title('PN 2.5') 
xlabel(' Time ')
ylabel('Normalized response')
legend('OPC-N3', 'SPS30') 
hold off

%Fit between OPC-N3 and SPS30
fit_OPC_N3_SPS30 = polyfit(sensor_object_plot_normalize{1}{3}(:,5), sensor_object_plot_normalize{2}{3}(:,5), 1);
%fit_OPC_N3_SPS30(2) = 0; %Force fit to go through origin
fit_OPC_N3_SPS30_line = polyval(fit_OPC_N3_SPS30, sensor_object_plot_normalize{1}{3}(:,5));

%Text to be displayed in scatter plot
coef_of_determination_txt = strcat({'R^2 = '}, num2str(corr_PM2_5, 2));
line_equation_txt = strcat({'y = '}, num2str(fit_OPC_N3_SPS30(1), 2), {'x + '}, num2str(fit_OPC_N3_SPS30(2)));

figure;
scatter(sensor_object_plot_normalize{1}{3}(:,5), sensor_object_plot_normalize{2}{3}(:,5));
hold on;
plot(sensor_object_plot_normalize{1}{3}(:,5), fit_OPC_N3_SPS30_line, 'k-', 'LineWidth', 1.5);
xlabel('OPC-N3 normalized');
ylabel('SPS30 normalized');
text(max(sensor_object_plot_normalize{1}{3}(:,5))/16, max(sensor_object_plot_normalize{2}{3}(:,5))*0.8, coef_of_determination_txt);
text(max(sensor_object_plot_normalize{1}{3}(:,5))/16, max(sensor_object_plot_normalize{2}{3}(:,5))*0.75, line_equation_txt);
hold off;


