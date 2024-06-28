%% Check which parts of code are to be executed 

%always to execute: 
%   Check which parts of code are to be executed
%   Import data
%   Bring data in form to work with
%       if form of import data "Variable{MEASUREMENT}{SENSORBOX}" stays same, 
%       no changes need to be done to these parts

%necessary for part of code
%	Synchronization of data
%       in this part it is defined, on which time scale the code is synchronized - can be changed
%           example: minutes(30),minutes(240),hours(1),...

%rest: 
%   Calibration of sensors 
%       here only one measurement and one sensorbox is predefined
%       Either use SENSORBOX_X(X=number of sensorbox) or change value of SENSORBOX 
%       (without number behind it, just a value)
%   Plotting of data
%       "plot_sensors_to_Weiz" 
%       "scatter_sensors_to_Weiz/temperature/humidity"
%       "scatter_multiple_polynom" requires "Calibration of sensors"


%number of MEASUREMENT and SENSORBOX important
%example: OPC{MEASUREMENT}{SENSORBOX}
%in loops "m" is used for measurement
MEASUREMENT_1=1;
MEASUREMENT_2=2;
%in loops "s" is used for sensorboxes
SENSORBOX_1=1;
SENSORBOX_2=2;
SENSORBOX_3=3;
%in loops "w" is used for Weiz data
WEIZ_2_5=1;
WEIZ_10=2;
WEIZ_T=3;
WEIZ_H=4;

%time of sensor start
%indices here are for different measurements
t_real{MEASUREMENT_1}=datetime(2020,03,10,10,40,00);
t_real{MEASUREMENT_2}=datetime(2020,02,27,11,40,00);
%starting time defined by sensor (NOT real starting time)
%time = datetime(YYYY,MM,DD,hh,mm,ss)
tsensor{MEASUREMENT_1}=datetime(2019,12,10,12,56,57);
tsensor{MEASUREMENT_2}=datetime(2019,12,10,12,56,57);
%correction for slight differences in timescale that might appear 
tcorr=minutes(-30);
%difference between sensor time and real time 
t_diff{MEASUREMENT_1}=datenum(t_real{MEASUREMENT_1}-tsensor{MEASUREMENT_1}+tcorr);
t_diff{MEASUREMENT_2}=datenum(t_real{MEASUREMENT_2}-tsensor{MEASUREMENT_2}+0);


%"Calibration" and "Plot sensors to Weiz" only work with measurement
%specified in MEASUREMENT 
MEASUREMENT=MEASUREMENT_1;
SENSORBOX=SENSORBOX_3;

%check wich parts of code are to be executed 
calibration_of_sensors=1;

plot_sensors_to_Weiz=0; 
    plot_OPC_to_Weiz=0;
    plot_SPS_to_Weiz=0;
    plot_humtemp_to_Weiz=0;

scatter_sensors_to_Weiz=0;
    scatter_OPC_to_Weiz=0;
    scatter_SPS_to_Weiz=0;
    
scatter_sensors_to_temperature=0;
    scatter_OPC_to_temperature=0;
    scatter_SPS_to_temperature=0;
    
scatter_sensors_to_humidity=0;
    scatter_OPC_to_humidity=0;
    scatter_SPS_to_humidity=0;

scatter_multiple_polynom=0; %reqiures "calibration_of_sensors=1" 

separate_bins=0;
separate_bins_normalization_and_plot=0;
calc_mean_particle_mass=0; %requires "separate_bins=1" 

%% Import data 

%calibration table for OPC to convert to µg/m3
%set path
datapath1='C:\Users\therumakisakura\Documents\SensMat\Docs\Sensors\OPC_N3'; 
addpath(datapath1) 
%import calibrationtable
cal_OPC=readtable('calibration_sheet_OPCN3.csv');


%data from measurement 10.03.2020-14.04.2020
%sensorbox 1
datapath2 = 'C:\Users\therumakisakura\Documents\SensMat\Measurement\Data\Weiz_Kalibrierung_200310_200414\Sensor 1';
addpath(datapath2)
%import OPC data from path
OPC{MEASUREMENT_1}{SENSORBOX_1}=readtable('Data_OPC-N3_10_12_2019_12_56.csv');
%import SPS data from path
SPS{MEASUREMENT_1}{SENSORBOX_1}=readtable('Data_SPS30_10_12_2019_12_56.csv');

%sensorbox 2
datapath3 = 'C:\Users\therumakisakura\Documents\SensMat\Measurement\Data\Weiz_Kalibrierung_200310_200414\Sensor 2';
addpath(datapath3)
OPC{1}{2}=readtable('Data_OPC-N3_10_12_2019_12_56.csv');
SPS{1}{2}=readtable('Data_SPS30_10_12_2019_12_56.csv');

%sensorbox 3
datapath4 = 'C:\Users\therumakisakura\Documents\SensMat\Measurement\Data\Weiz_Kalibrierung_200310_200414\Sensor 3';
addpath(datapath4)
OPC{1}{3}=readtable('Data_OPC-N3_10_12_2019_12_56.csv');
SPS{1}{3}=readtable('Data_SPS30_10_12_2019_12_56.csv');

%Reference data of Weiz
datapath5 = 'C:\Users\therumakisakura\Documents\SensMat\Measurement\Data\Weiz_Kalibrierung_200310_200414\Weiz_Referenzdaten_200310_200414'; 
addpath(datapath5) 
Weiz{1}{1}=readtable('Referenzdaten_Messstation_PM2_5.xls'); 
Weiz{1}{2}=readtable('Referenzdaten_Messstation_PM10.xls'); 
Weiz{1}{3}=readtable('Referenzdaten_Messstation_Temp.xls');
Weiz{1}{4}=readtable('Referenzdaten_Messstation_RelFeuchte.xls');



%data from measurement 27.02.2020-13.03.2020
datapath6 = 'C:\Users\therumakisakura\Documents\SensMat\Measurement\Data\Weiz_Kalibrierung_200227_200310\Sensor 1';
addpath(datapath6)
OPC{2}{1}=readtable('Data_OPC-N3_10_12_2019_12_58.csv');
SPS{2}{1}=readtable('Data_SPS30_10_12_2019_12_58.csv');

datapath7 = 'C:\Users\therumakisakura\Documents\SensMat\Measurement\Data\Weiz_Kalibrierung_200227_200310\Sensor 2';
addpath(datapath7)
OPC{2}{2}=readtable('Data_OPC-N3_10_12_2019_12_57.csv');
SPS{2}{2}=readtable('Data_SPS30_10_12_2019_12_57.csv');

datapath8 = 'C:\Users\therumakisakura\Documents\SensMat\Measurement\Data\Weiz_Kalibrierung_200227_200310\Sensor 3';
addpath(datapath8)
OPC{2}{3}=readtable('Data_OPC-N3_10_12_2019_12_57.csv');
SPS{2}{3}=readtable('Data_SPS30_10_12_2019_12_57.csv');

%Reference data of Weiz
datapath9 = 'C:\Users\therumakisakura\Documents\SensMat\Measurement\Data\Weiz_Kalibrierung_200227_200310\Weiz_Referenzdaten_200227_200310'; 
addpath(datapath9) 
Weiz{2}{1}=readtable('Referenzdaten_Messstation_PM2_5.xls'); 
Weiz{2}{2}=readtable('Referenzdaten_Messstation_PM10.xls'); 
Weiz{2}{3}=readtable('Referenzdaten_Messstation_Temp.xls');
Weiz{2}{4}=readtable('Referenzdaten_Messstation_RelFeuchte.xls');


%% Bring data in form to work with

%factors for calculating OPC µg/m3; Volume of each bin multiplied by the
%respiratory factor(see sheet for OPC) 
factor2_5=cal_OPC{:,8}.*cal_OPC{:,6};
factor10=cal_OPC{:,8}.*cal_OPC{:,7};

%creates cell for each table of OPC and SPS
sensor_object_date=cell(1,length(OPC));
plot_time_OPC=cell(1,length(OPC));
plot_time_SPS=cell(1,length(SPS));
plot_time_Weiz=cell(1,length(Weiz));
Weiz_date=cell(1,length(Weiz)); 
Weiz_data=cell(1,length(Weiz));
OPC_PM_10=cell(1,length(OPC)); 
OPC_PM_2_5=cell(1,length(OPC)); 
factor_OPC=cell(1,length(OPC)); 
OPC_temp=cell(1,length(OPC)); 
OPC_hum=cell(1,length(OPC)); 


%changes the format of Weiz data to our format
for m=1:length(Weiz)    %m...number of measurement
    Weiz_data{m}=Weiz_adjustment(Weiz{m}); %loop so that it is done for all measurements
end

%adjusts time of Weiz to datenum format
for m=1:length(Weiz)    %m...number of measurement
    for w=1:length(Weiz{m}) %w...which data of Weiz is used (PM 2.5/10,hum,temp)
        Weiz_date{m}{w} = {Weiz_data{m}{w}.Datum,Weiz_data{m}{w}.Uhrzeit};
        plot_time_Weiz{m}{w} = time_adjustment(Weiz_date{m}{w}{1},Weiz_date{m}{w}{2},0);
    end
end

for m=1:length(OPC)
    for s=1:length(OPC{m})
        sensor_object_date{m}{s}={{OPC{m}{s}.Timestamp,OPC{m}{s}.Var2},{SPS{m}{s}.Timestamp,SPS{m}{s}.Var2}};

        %function to adjust cell data to a plottable time 
        %[plot_time_OPC, plot_time_SPS] = time_adjustment(OPC_date,OPC_time,SPS_date,SPS_time)
        plot_time_OPC{m}{s} = time_adjustment(sensor_object_date{m}{s}{1}{1},sensor_object_date{m}{s}{1}{2},t_diff{m});                                              
        plot_time_SPS{m}{s} = time_adjustment(sensor_object_date{m}{s}{2}{1},sensor_object_date{m}{s}{2}{2},t_diff{m});

        %factor_OPC = 1.65 [g/cm3] / (100 [] * flowrate [ml/s] * 1 [s]) 
        %1 cm3 = 1 ml 
        %->[g/cm3]/([ml/s]*[s]) = [[g/cm3^2]

        %factor10 = [µm3]
        %cm3 = [µm3] * 10^-12 [cm3/µm3]

        %OPC_PM_10 = [g/cm3^2]*10^-12[cm3] = 10^-12 [g/cm3]
        %[µg/m3] = 10^-12*[g/cm3] * 10^6[µg/g] * 10^6[cm3/m3]
        for j=1:height(OPC{m}{s})
            factor_OPC{m}{s}(j,1)=1.65/(100*(OPC{m}{s}{j,29}/100));%SFR in 100*ml/s angegeben 
            OPC_PM_10{m}{s}(j,1)=factor_OPC{m}{s}(j,1)*(sum(OPC{m}{s}{j,3:26}'.*factor10)); 
            OPC_PM_2_5{m}{s}(j,1)=factor_OPC{m}{s}(j,1)*(sum(OPC{m}{s}{j,3:26}'.*factor2_5)); 
        end

        OPC_temp{m}{s}=((OPC{m}{s}{:,27}*175)/((2^16)-1))-45; 
        OPC_hum{m}{s}=(100*OPC{m}{s}{:,28})/((2^16)-1); 
    end
end

%% Synchronization of data

%first a cell is created with all necessary information to create the timetable
%{ {column1}, {column2},... }            for each column in the timetable a cell is created
%{ {plot_time,data,column_name}, ... }   columns need time, date and title, so in each cell these three have to be set
Variables_sensor=cell(1,length(OPC));
for m=1:length(OPC) %m = measurement
    for s=1:length(OPC{m}) %s = sensorbox
        Variables_sensor{m}{s}={{plot_time_Weiz{m}{WEIZ_2_5},Weiz_data{m}{WEIZ_2_5}{:,3},'Weiz_2_5'},...
            {plot_time_Weiz{m}{WEIZ_10},Weiz_data{m}{WEIZ_10}{:,3},'Weiz_10'},...
            {plot_time_OPC{m}{s},OPC_PM_2_5{m}{s},'OPC_2_5'},...
            {plot_time_OPC{m}{s},OPC_PM_10{m}{s},'OPC_10'},...
            {plot_time_SPS{m}{s},SPS{m}{s}{:,4},'SPS_2_5'},...
            {plot_time_SPS{m}{s},SPS{m}{s}{:,6},'SPS_10'},...
            {plot_time_OPC{m}{s},OPC_temp{m}{s},'OPC_t'},...
            {plot_time_OPC{m}{s},OPC_hum{m}{s},'OPC_h'},...
            {plot_time_Weiz{m}{WEIZ_T},Weiz_data{m}{WEIZ_T}{:,3},'Weiz_t'},...
            {plot_time_Weiz{m}{WEIZ_H},Weiz_data{m}{WEIZ_H}{:,3},'Weiz_h'}};
    end
end

%synchronization of sensors, function synchronize_data needs cell with structure shown above
synchronized_sensors=cell(1,length(OPC)); %data is synchronized on a time period of 30 minutes
for m=1:length(OPC)
    for s=1:length(OPC{m})
        synchronized_sensors{m}{s}=synchronize_data(Variables_sensor{m}{s},minutes(120));
    end
end
%the time period can be changed, ex. minutes(240), hours(1), ...


%% Calibration of sensors 

MEASUREMENT=2;
SENSORBOX=3;

if MEASUREMENT==1
    MEASUREMENT_OTHER=2;
else
    MEASUREMENT_OTHER=1;
end

%calibration_of_sensors=1;
if calibration_of_sensors==1
    %data is extracted from table 
    %this part is not necessary, since the right part can be used directly as
    %input for "multiple_regression" and "statistics_table" 
    Variables_Weiz_PM_2_5=synchronized_sensors{MEASUREMENT}{SENSORBOX}{:,1}; 
    Variables_Weiz_PM_10=synchronized_sensors{MEASUREMENT}{SENSORBOX}{:,2}; 
    Variables_OPC_PM_2_5=synchronized_sensors{MEASUREMENT}{SENSORBOX}{:,3}; 
    Variables_OPC_PM_10=synchronized_sensors{MEASUREMENT}{SENSORBOX}{:,4}; 
    Variables_SPS_PM_2_5=synchronized_sensors{MEASUREMENT}{SENSORBOX}{:,5}; 
    Variables_SPS_PM_10=synchronized_sensors{MEASUREMENT}{SENSORBOX}{:,6}; 
    Variables_humtemp=synchronized_sensors{MEASUREMENT}{SENSORBOX}{:,7:8}; %hum&temp from OPC

    %multiple regression uses various calibration methods
    %Variables_cell=multiple_regression(sensor_data,calibration_data)
    SPS_2_5_regression=multiple_regression(Variables_SPS_PM_2_5,Variables_Weiz_PM_2_5); 
    %uses the cell generated by function multiple_regression to give statistics(explained in function) 
    SPS_2_5_statistics=statistics_table(SPS_2_5_regression); 

    SPS_10_regression=multiple_regression(Variables_SPS_PM_10,Variables_Weiz_PM_10); 
    SPS_10_statistics=statistics_table(SPS_10_regression); 

    OPC_2_5_regression=multiple_regression(Variables_OPC_PM_2_5,Variables_Weiz_PM_2_5);
    OPC_2_5_statistics=statistics_table(OPC_2_5_regression); 

    OPC_10_regression=multiple_regression(Variables_OPC_PM_10,Variables_Weiz_PM_10);
    OPC_10_statistics=statistics_table(OPC_10_regression); 


    %humidity and temperature of OPC are used for linear regression
    OPC_2_5_cal_humtemp=ones(length(Variables_OPC_PM_2_5),1); %ones necessary for offset of lienar regression 
    OPC_2_5_cal_humtemp(:,2:4)=cat(2,Variables_OPC_PM_2_5,Variables_humtemp);
    OPC_2_5_regression_model_humtemp=OPC_2_5_cal_humtemp\Variables_Weiz_PM_2_5;
    OPC_2_5_regression_humtemp=OPC_2_5_cal_humtemp*OPC_2_5_regression_model_humtemp; 
    
    OPC_PM_2_5_humtemp_function=strcat(num2str(OPC_2_5_regression_model_humtemp(2,1)),'*PM+',num2str(OPC_2_5_regression_model_humtemp(3,1)),'*H+',...
        num2str(OPC_2_5_regression_model_humtemp(4,1)),'*T+',num2str(OPC_2_5_regression_model_humtemp(1,1)));
    %here the cell is created (similar to cell from function
    %multiple_regression)for function statistics_table
    OPC_2_5_humtemp_regression_variables={{OPC_2_5_regression_model_humtemp,OPC_2_5_regression_humtemp,Variables_OPC_PM_2_5,'humtemp',OPC_PM_2_5_humtemp_function}};
    OPC_2_5_humtemp_statistics=statistics_table(OPC_2_5_humtemp_regression_variables);
    %statistics from linear regression with humidity and temperature are added
    %to OPC statistics table
    OPC_2_5_statistics{9,:}=OPC_2_5_humtemp_statistics{1,:};

    %same as OPC PM 2.5
    OPC_10_cal_humtemp=ones(length(Variables_OPC_PM_10),1); 
    
    OPC_10_cal_humtemp(:,2:4)=cat(2,Variables_OPC_PM_10,Variables_humtemp);
    
    OPC_10_regression_model_humtemp=OPC_10_cal_humtemp\Variables_Weiz_PM_10;
    
    OPC_10_regression_humtemp=OPC_10_cal_humtemp*OPC_10_regression_model_humtemp; 
    
    OPC_PM_10_humtemp_function=strcat(num2str(OPC_10_regression_model_humtemp(2,1)),'*PM+',num2str(OPC_10_regression_model_humtemp(3,1)),'*H+',...
        num2str(OPC_10_regression_model_humtemp(4,1)),'*T+',num2str(OPC_10_regression_model_humtemp(1,1)));

    OPC_10_humtemp_regression_variables={{OPC_10_regression_model_humtemp,OPC_10_regression_humtemp,Variables_OPC_PM_10,'humtemp',OPC_PM_10_humtemp_function}};
    OPC_10_humtemp_statistics=statistics_table(OPC_10_humtemp_regression_variables);

    OPC_10_statistics{9,:}=OPC_10_humtemp_statistics{1,:};

end




%generates cell, where a second measurement is tested with the calibration
%   SPS
%parameters of the first one 
SPS_2_5_regression_validation=SPS_2_5_regression;
for i=1:length(SPS_2_5_regression_validation)
    SPS_2_5_regression_validation{i}{3}=synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,1};
end

SPS_2_5_regression_validation{1}{2}=synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,5};
SPS_2_5_regression_validation{2}{2}=synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,5}/SPS_2_5_regression_validation{2}{1}(1,1);
SPS_2_5_regression_validation{3}{2}=polyval(SPS_2_5_regression_validation{3}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,5});
SPS_2_5_regression_validation{4}{2}=polyval(SPS_2_5_regression_validation{4}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,5});
SPS_2_5_regression_validation{5}{2}=polyval(SPS_2_5_regression_validation{5}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,5});
SPS_2_5_regression_validation{6}{2}=SPS_2_5_regression_validation{6}{1}(1,1)*exp(SPS_2_5_regression_validation{6}{1}(1,2)*synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,5});
SPS_2_5_regression_validation{7}{2}=SPS_2_5_regression_validation{7}{1}(1,1)*synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,5}.^SPS_2_5_regression_validation{7}{1}(1,2);
SPS_2_5_regression_validation{8}{2}=predict(SPS_2_5_regression_validation{8}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,5});

SPS_2_5_statistics_validation=statistics_table(SPS_2_5_regression_validation); 

%plot of SPS 2.5 compare calibrated to not calibrated 
figure
subplot(2,1,1)
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,SPS_2_5_regression_validation{1}{2})
hold on
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,1})
title('not calibrated')
legend('SPS PM 2.5','Weiz PM 2.5')
subplot(2,1,2)
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,SPS_2_5_regression_validation{7}{2})
hold on
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,1})
title('calibrated')
legend('SPS PM 2.5','Weiz PM 2.5')


%parameters of the first one 
SPS_10_regression_validation=SPS_10_regression;
for i=1:length(SPS_10_regression_validation)
    SPS_10_regression_validation{i}{3}=synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,2};
end

SPS_10_regression_validation{1}{2}=synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,6};
SPS_10_regression_validation{2}{2}=synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,6}/SPS_10_regression_validation{2}{1}(1,1);
SPS_10_regression_validation{3}{2}=polyval(SPS_10_regression_validation{3}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,6});
SPS_10_regression_validation{4}{2}=polyval(SPS_10_regression_validation{4}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,6});
SPS_10_regression_validation{5}{2}=polyval(SPS_10_regression_validation{5}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,6});
SPS_10_regression_validation{6}{2}=SPS_10_regression_validation{6}{1}(1,1)*exp(SPS_10_regression_validation{6}{1}(1,2)*synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,6});
SPS_10_regression_validation{7}{2}=SPS_10_regression_validation{7}{1}(1,1)*synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,6}.^SPS_10_regression_validation{7}{1}(1,2);
SPS_10_regression_validation{8}{2}=predict(SPS_10_regression_validation{8}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,6});

SPS_10_statistics_validation=statistics_table(SPS_10_regression_validation); 

%plot of SPS 10 compare calibrated to not calibrated 
figure
subplot(2,1,1)
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,SPS_10_regression_validation{1}{2})
hold on
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,2})
title('not calibrated')
legend('SPS PM 10','Weiz PM 10')
subplot(2,1,2)
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,SPS_10_regression_validation{5}{2})
hold on
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,2})
title('calibrated')
legend('SPS PM 10','Weiz PM 10')



%   OPC
%parameters of the first one 
OPC_2_5_regression_validation=OPC_2_5_regression;
for i=1:length(OPC_2_5_regression_validation)
    OPC_2_5_regression_validation{i}{3}=synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,1};
end

OPC_2_5_regression_validation{1}{2}=synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,3};
OPC_2_5_regression_validation{2}{2}=synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,3}/OPC_2_5_regression_validation{2}{1}(1,1);
OPC_2_5_regression_validation{3}{2}=polyval(OPC_2_5_regression_validation{3}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,3});
OPC_2_5_regression_validation{4}{2}=polyval(OPC_2_5_regression_validation{4}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,3});
OPC_2_5_regression_validation{5}{2}=polyval(OPC_2_5_regression_validation{5}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,3});
OPC_2_5_regression_validation{6}{2}=OPC_2_5_regression_validation{6}{1}(1,1)*exp(OPC_2_5_regression_validation{6}{1}(1,2)*synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,3});
OPC_2_5_regression_validation{7}{2}=OPC_2_5_regression_validation{7}{1}(1,1)*synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,5}.^OPC_2_5_regression_validation{7}{1}(1,2);
OPC_2_5_regression_validation{8}{2}=predict(OPC_2_5_regression_validation{8}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,3});

OPC_2_5_statistics_validation=statistics_table(OPC_2_5_regression_validation); 

%plot of OPC 2.5 compare calibrated to not calibrated 
figure
subplot(2,1,1)
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,OPC_2_5_regression_validation{1}{2})
hold on
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,1})
title('not calibrated')
legend('OPC PM 2.5','Weiz PM 2.5')
subplot(2,1,2)
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,OPC_2_5_regression_validation{2}{2})
hold on
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,1})
title('calibrated')
legend('OPC PM 2.5','Weiz PM 2.5')


%parameters of the first one 
OPC_10_regression_validation=OPC_10_regression;
for i=1:length(OPC_10_regression_validation)
    OPC_10_regression_validation{i}{3}=synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,2};
end

OPC_10_regression_validation{1}{2}=synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,4};
OPC_10_regression_validation{2}{2}=synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,4}/OPC_10_regression_validation{2}{1}(1,1);
OPC_10_regression_validation{3}{2}=polyval(OPC_10_regression_validation{3}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,4});
OPC_10_regression_validation{4}{2}=polyval(OPC_10_regression_validation{4}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,4});
OPC_10_regression_validation{5}{2}=polyval(OPC_10_regression_validation{5}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,4});
OPC_10_regression_validation{6}{2}=OPC_10_regression_validation{6}{1}(1,1)*exp(OPC_10_regression_validation{6}{1}(1,2)*synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,4});
OPC_10_regression_validation{7}{2}=OPC_10_regression_validation{7}{1}(1,1)*synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,4}.^OPC_10_regression_validation{7}{1}(1,2);
OPC_10_regression_validation{8}{2}=predict(OPC_10_regression_validation{8}{1},synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,4});

OPC_10_statistics_validation=statistics_table(OPC_10_regression_validation); 

%plot of OPC 10 compare calibrated to not calibrated 
figure
subplot(2,1,1)
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,OPC_10_regression_validation{1}{2})
hold on
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,2})
title('not calibrated')
legend('OPC PM 10','Weiz PM 10')
subplot(2,1,2)
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,OPC_10_regression_validation{2}{2})
hold on
plot(synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}.Time,synchronized_sensors{MEASUREMENT_OTHER}{SENSORBOX}{:,2})
title('calibrated')
legend('OPC PM 10','Weiz PM 10')

%figure of the same calibration method but with measurement 1
figure
subplot(2,1,1)
plot(synchronized_sensors{MEASUREMENT}{SENSORBOX}.Time,SPS_2_5_regression{1}{2})
hold on
plot(synchronized_sensors{MEASUREMENT}{SENSORBOX}.Time,synchronized_sensors{MEASUREMENT}{SENSORBOX}{:,2})
title('not calibrated')
legend('OPC PM 10','Weiz PM 10')
subplot(2,1,2)
plot(synchronized_sensors{MEASUREMENT}{SENSORBOX}.Time,SPS_2_5_regression{5}{2})
hold on
plot(synchronized_sensors{MEASUREMENT}{SENSORBOX}.Time,synchronized_sensors{MEASUREMENT}{SENSORBOX}{:,2})
title('calibrated')
legend('OPC PM 10','Weiz PM 10')




%% Plot sensors to Weiz
%MEASUREMENT=1;
%SENSORBOX=1;

%{
plot_sensors_to_Weiz=1;
    plot_OPC_to_Weiz=1;
    plot_SPS_to_Weiz=0;
    plot_humtemp_to_Weiz=0;
%}
%plot of sensor measurements and Weiz on one timescale

if plot_sensors_to_Weiz==1
    
    title_subplot_sensor_to_Weiz={'PM 2.5','PM 10'};
    
    if plot_OPC_to_Weiz==1
        
        %cell used to plot with function particle_plot_multiple for OPC
        sensor_object_plot_OPC=cell(1,length(OPC));
        for m=1:length(OPC)
            for s=1:length(OPC{m})
                sensor_object_plot_OPC{m}{s}={{'OPC',synchronized_sensors{m}{s}.Time,synchronized_sensors{m}{s}{:,3:4},'OPC',title_subplot_sensor_to_Weiz},...
                    {'Weiz',synchronized_sensors{m}{s}.Time,synchronized_sensors{m}{s}{:,1:2},'Weiz',title_subplot_sensor_to_Weiz}};
            end
        end

        %one loop for one measurement with all sensors
        %OPC all sensorboxes one measurement
        for s=1:length(OPC{MEASUREMENT}) %s...number of sensorbox
            particle_plot_multiple(sensor_object_plot_OPC{MEASUREMENT}{s})
        end
    end
    
    if plot_SPS_to_Weiz==1
        %cell used to plot with function particle_plot_multiple for SPS
        sensor_object_plot_SPS=cell(1,length(SPS));
        for m=1:length(SPS)
            for s=1:length(SPS{m})
                sensor_object_plot_SPS{m}{s}={{'OPC',synchronized_sensors{m}{s}.Time,synchronized_sensors{m}{s}{:,5:6},'SPS',title_subplot_sensor_to_Weiz},...
                    {'Weiz', synchronized_sensors{m}{s}.Time, synchronized_sensors{m}{s}{:,1:2},'Weiz',title_subplot_sensor_to_Weiz}};
            end
        end

        %SPS all sensorboxes one measurement
        for s=1:length(SPS{MEASUREMENT}) %s...number of sensorbox
            particle_plot_multiple(sensor_object_plot_SPS{MEASUREMENT}{s})
        end
    end
    
    if plot_humtemp_to_Weiz==1
        %cell for humidity and temperature
        title_subplot_humtemp={'temperature','humidity'};
        sensor_object_plot_temp_hum=cell(1,length(OPC));
        for m=1:length(OPC)
            for s=1:length(OPC{m})
                sensor_object_plot_temp_hum{m}{s}={{'OPC',synchronized_sensors{m}{s}.Time,synchronized_sensors{m}{s}{:,7:8},'OPC',title_subplot_humtemp},...
                    {'Weiz',synchronized_sensors{m}{s}.Time,synchronized_sensors{m}{s}{:,9:10},'Weiz',title_subplot_humtemp}};
            end
        end

        %Temperature and Humidity all sensorboxes one measurement
        for s=1:length(OPC{MEASUREMENT}) %s...number of sensorbox
            particle_plot_multiple(sensor_object_plot_temp_hum{MEASUREMENT}{s})
        end
    end
end
%end of if-statement for checking whether sensors and Weiz are to be ploted


%% Scatter sensors to Weiz
%{
scatter_sensors_to_Weiz=1;
    scatter_OPC_to_Weiz=0;
    scatter_SPS_to_Weiz=0;
%}

if scatter_sensors_to_Weiz==1
    %scatter OPC(y-axis) to Weiz(x-axis)
    %the names of the figures are created for PM2.5
    %M...measurement; S...Sensorbox 
    
    if scatter_OPC_to_Weiz==1
        
        title_scatter_OPC=cell(length(OPC),length(OPC{1}));
        for m=1:length(OPC)     %m...measurement
            for s=1:length(OPC{m})  %s...sensorbox
                title_scatter_OPC{m,s}=append('M',num2str(m),'S',num2str(s),' OPC');
            end
        end

        %scatter of particle measurements all sensors and measurements
        for m=1:length(OPC)
            for s=1:length(OPC{m})
                figure('Name',title_scatter_OPC{m,s})
                subplot(2,1,1)
                scatter(synchronized_sensors{m}{s}.Weiz_2_5,synchronized_sensors{m}{s}.OPC_2_5)
                xlabel('Weiz [µg/m3]')
                ylabel('OPC [µg/m3]')
                title('PM 2.5')
                subplot(2,1,2)
                scatter(synchronized_sensors{m}{s}.Weiz_10,synchronized_sensors{m}{s}.OPC_10)
                xlabel('Weiz [µg/m3]')
                ylabel('OPC [µg/m3]')
                title('PM 10')
            end
        end
    end
    
    if scatter_SPS_to_Weiz==1
        
        title_scatter_SPS=cell(length(OPC),length(OPC{1}));
        for m=1:length(OPC)     %m...measurement
            for s=1:length(OPC{m})  %s...sensorbox
                title_scatter_SPS{m,s}=append('M',num2str(m),'S',num2str(s),' SPS');
            end
        end
        
        for m=1:length(SPS)
            for s=1:length(SPS{m})
                figure('Name',title_scatter_SPS{m,s})
                subplot(2,1,1)
                scatter(synchronized_sensors{m}{s}.Weiz_2_5,synchronized_sensors{m}{s}.SPS_2_5)
                xlabel('Weiz [µg/m3]')
                ylabel('SPS [µg/m3]')
                title('PM 2.5')
                subplot(2,1,2)
                scatter(synchronized_sensors{m}{s}.Weiz_10,synchronized_sensors{m}{s}.SPS_10)
                xlabel('Weiz [µg/m3]')
                ylabel('SPS [µg/m3]')
                title('PM 10')
            end
        end
    end
end


%% Scatter particle measurement to temperature 

%{
scatter_sensors_to_temperature=1;
    scatter_OPC_to_temperature=0;
    scatter_SPS_to_temperature=0;
%}
    
if scatter_sensors_to_temperature==1
    %scatter of particle measurement and temperature
    title_scatter_temp=cell(length(OPC),length(OPC{1}));
    for m=1:length(OPC)
        for s=1:length(OPC{m})
            title_scatter_temp{m,s}=append('M',num2str(m),'S',num2str(s),' Temperature');
        end
    end

    if scatter_OPC_to_temperature==1
        %scatter OPC and temperature
        for m=1:length(OPC)
            for s=1:length(OPC{m})
                figure('Name',title_scatter_temp{m,s})
                subplot(2,1,1)
                scatter(synchronized_sensors{m}{s}.OPC_t,synchronized_sensors{m}{s}.OPC_2_5)
                xlabel('Temperature [°C]')
                ylabel('OPC [µg/m3]')
                title('PM 2.5')
                subplot(2,1,2)
                scatter(synchronized_sensors{m}{s}.OPC_t,synchronized_sensors{m}{s}.OPC_10)
                xlabel('Temperature [°C]')
                ylabel('OPC [µg/m3]')
                title('PM 10')
            end
        end
    end
        
    if scatter_SPS_to_temperature==1
        for m=1:length(SPS)
            for s=1:length(SPS{m})
                figure('Name',title_scatter_temp{m,s})
                subplot(2,1,1)
                scatter(synchronized_sensors{m}{s}.OPC_t,synchronized_sensors{m}{s}.SPS_2_5)
                xlabel('Temperature [°C]')
                ylabel('SPS [µg/m3]')
                title('PM 2.5')
                subplot(2,1,2)
                scatter(synchronized_sensors{m}{s}.OPC_t,synchronized_sensors{m}{s}.SPS_10)
                xlabel('Temperature [°C]')
                ylabel('SPS [µg/m3]')
                title('PM 10')
            end
        end
    end
end


%% Scatter particle measurement to humidity 

%{
scatter_sensors_to_humidity=1;
    scatter_OPC_to_humidity=0;
    scatter_SPS_to_humidity=0;
%}

if scatter_sensors_to_humidity==1
    %scatter of particle measurement and humidity
    title_scatter_hum=cell(length(OPC),length(OPC{1}));
    for m=1:length(OPC)
        for s=1:length(OPC{m})
            title_scatter_hum{m,s}=append('M',num2str(m),'S',num2str(s),' Humidity');
        end
    end

    if scatter_OPC_to_humidity==1
        %scatter OPC and humidity
        for m=1:length(OPC)
            for s=1:length(OPC{m})
                figure('Name',title_scatter_hum{m,s})
                subplot(2,1,1)
                scatter(synchronized_sensors{m}{s}.OPC_h,synchronized_sensors{m}{s}.OPC_2_5)
                xlabel('Humidity [%]')
                ylabel('OPC [µg/m3]')
                title('PM 2.5')
                subplot(2,1,2)
                scatter(synchronized_sensors{m}{s}.OPC_h,synchronized_sensors{m}{s}.OPC_10)
                xlabel('Humidity [%]')
                ylabel('OPC [µg/m3]')
                title('PM 10')
            end
        end
    end
    
    if scatter_SPS_to_humidity==1
        for m=1:length(SPS)
            for s=1:length(SPS{m})
                figure('Name',title_scatter_hum{m,s})
                subplot(2,1,1)
                scatter(synchronized_sensors{m}{s}.OPC_h,synchronized_sensors{m}{s}.SPS_2_5)
                xlabel('Humidity [%]')
                ylabel('SPS [µg/m3]')
                title('PM 2.5')
                subplot(2,1,2)
                scatter(synchronized_sensors{m}{s}.OPC_h,synchronized_sensors{m}{s}.SPS_10)
                xlabel('Humidity [%]')
                ylabel('SPS [µg/m3]')
                title('PM 10')
            end
        end
    end
end


if scatter_multiple_polynom==1
    scatter_multiple(SPS_2_5_regression,Variables_SPS_PM_2_5,'SPS 2.5')
    scatter_multiple(SPS_10_regression,Variables_SPS_PM_10,'SPS 10')
    scatter_multiple(OPC_2_5_regression,Variables_OPC_PM_2_5,'OPC 2.5')
    scatter_multiple(OPC_10_regression,Variables_OPC_PM_10,'OPC 10')
end


%plot: 
    %Weiz and sensors particle measurement 	%%before calibration possible 
    %compare humidity and temperature from sensor and Weiz  %%before calibration possible
    %calibrated/uncalibrated sensors and Weiz   only after calibration
%scatter: 
    %Weiz and sensors to each other with polynom fitted %%with scatter multiple after calibration 
    %Weiz and sensors to each other without polynom     %%before calibration possible
    %temperature and humidity to sensor particle measurement %%before calibration possible
    %calibrated/uncalibrated sensors and Weiz




%% Separated bins for sensors

if separate_bins==1
    %only particles in bin for SPS PN; PN2.5=PN1-PN2.5, PN4=PN2.5-PN4, ...
    SPS_PN_dif=cell(1,length(SPS)); 
    for m=1:length(SPS)
        for s=1:length(SPS{m})
            SPS_PN_dif{m}{s}=[SPS{m}{s}{:,7},...
                SPS{m}{s}{:,8}-SPS{m}{s}{:,7},...
                SPS{m}{s}{:,9}-SPS{m}{s}{:,8},...
                SPS{m}{s}{:,10}-SPS{m}{s}{:,9},...
                SPS{m}{s}{:,11}-SPS{m}{s}{:,10}];
        end
    end

    %same with OPC, same bins of 0.5, 1, 2.5, 4, 10
    OPC_PN_dif_wo_flowRate=cell(1,length(OPC)); 
    OPC_PN_dif=cell(1,length(OPC));
    for m=1:length(OPC) %m...measurement
        for s=1:length(OPC{m})  %s...sensorbox
            OPC_PN_dif_wo_flowRate{m}{s}=[sum(OPC{m}{s}{:,3:4},2),sum(OPC{m}{s}{:,5:6},2),sum(OPC{m}{s}{:,7:9},2),sum(OPC{m}{s}{:,10:11},2),sum(OPC{m}{s}{:,12:15},2)]; 

            %incorporates flowrate to bins to get concentration an not only counts 
            for j=1:length(OPC_PN_dif_wo_flowRate{m}{s}) 
                OPC_PN_dif{m}{s}(j,:)=OPC_PN_dif_wo_flowRate{m}{s}(j,:)./OPC{m}{s}{j,29};
            end
        end
    end
end

%% Normalization of separated bins 

if separate_bins_normalization_and_plot==1
    title_subplot_all={{'PN 0.5'},{'PN 1'},{'PN 2.5'},{'PN 4'},{'PN 10'}}; 
    title_subplot_wo_0_5={{'PN 1'},{'PN 2.5'},{'PN 4'},{'PN 10'}}; 
    
    SPS_PN_dif_mean=cell(1,length(SPS));
    OPC_PN_dif_mean=cell(1,length(OPC));
    SPS_PN_dif_normalize=cell(1,length(SPS));
    OPC_PN_dif_normalize=cell(1,length(OPC));
    sensor_object_plot_SPS_dif=cell(1,length(SPS));
    sensor_object_plot_OPC_dif=cell(1,length(OPC));
    sensor_object_plot_dif_normalize_compare=cell(1,length(OPC));
    
    %normalizes SPS and OPC PN to compare them 
    for m=1:length(OPC)
        for s=1:length(OPC{m})
            SPS_PN_dif_mean{m}{s}=mean(SPS_PN_dif{m}{s}); 
            OPC_PN_dif_mean{m}{s}=mean(OPC_PN_dif{m}{s}); 

            SPS_PN_dif_normalize{m}{s}=SPS_PN_dif{m}{s}./SPS_PN_dif_mean{m}{s}; 
            OPC_PN_dif_normalize{m}{s}=OPC_PN_dif{m}{s}./OPC_PN_dif_mean{m}{s}; 

            sensor_object_plot_dif_normalize_compare{m}{s}={{'OPC PN normalize',plot_time_OPC{m}{s},OPC_PN_dif_normalize{m}{s},'OPC PN',title_subplot_all},...
                {'SPS PN normalize',plot_time_SPS{m}{s},SPS_PN_dif_normalize{m}{s},'SPS PN',title_subplot_all}};
        end
    end
    
    particle_plot_multiple(sensor_object_plot_dif_normalize_compare{MEASUREMENT}{SENSORBOX})

    SPS_PN_dif2=cell(1,length(SPS));
    OPC_PN_dif2=cell(1,length(OPC));
    SPS_mean2=cell(1,length(SPS));
    OPC_mean2=cell(1,length(OPC));
    SPS_normalize2=cell(1,length(SPS));
    OPC_normalize2=cell(1,length(OPC));
    sensor_object_plot_dif_normalize_compare2=cell(1,length(OPC));

    
    for m=1:length(OPC)
        for s=1:length(OPC{m})
            %PN0.5 eliminated, SPS and OPC weigh bin PN1 and PN0.5 differently 
            SPS_PN_dif2{m}{s}(:,1)=SPS_PN_dif{m}{s}(:,1)+SPS_PN_dif{m}{s}(:,2); 
            SPS_PN_dif2{m}{s}(:,2:4)=SPS_PN_dif{m}{s}(:,3:5); 
            OPC_PN_dif2{m}{s}(:,1)=OPC_PN_dif_wo_flowRate{m}{s}(:,1)+OPC_PN_dif_wo_flowRate{m}{s}(:,2); 
            OPC_PN_dif2{m}{s}(:,2:4)=OPC_PN_dif_wo_flowRate{m}{s}(:,3:5); 

            %normalize SPS and OPC to compare to each other
            SPS_mean2{m}{s}=mean(SPS_PN_dif2{m}{s}); 
            OPC_mean2{m}{s}=mean(OPC_PN_dif2{m}{s}); 

            SPS_normalize2{m}{s}=SPS_PN_dif2{m}{s}./SPS_mean2{m}{s}; 
            OPC_normalize2{m}{s}=OPC_PN_dif2{m}{s}./OPC_mean2{m}{s}; 


            sensor_object_plot_dif_normalize_compare2{m}{s}={{'SPS PN normalized',plot_time_SPS{m}{s},SPS_normalize2{m}{s},'SPS PN',title_subplot_wo_0_5},... 
                {'OPC PN normalized',plot_time_OPC{m}{s},OPC_normalize2{m}{s},'OPC PN',title_subplot_wo_0_5}};

        end
    end
    
    particle_plot_multiple(sensor_object_plot_dif_normalize_compare2{MEASUREMENT}{SENSORBOX})

end

%% Mean particle mass

if calc_mean_particle_mass==1
    %calculates mean particle mass for each measurement
    SPS_mean_particle_mass=cell(1,length(SPS));
    OPC_mean_particle_mass=cell(1,length(OPC));

    %kg=V*kg/V
    %mean radius is the mean of the two boundaries of the bin; 0.3-0.5 ->
    %(0.3+0.5)/2=0.4 -> first bin
    mean_radius=[0.4;0.75;1.75;3.75;7];
    mean_volume=nan(5,1);
    %mean volume calculated with mean radius V=(4*pi*r^3)/3
    for s=1:5
        mean_volume(s,1)=(4*pi/3)*(mean_radius(s,1)^3);
    end

    %mean particle mass
    %sum(particles_in_bin*mean_volume_of_particles) over all bins
    for m=1:length(OPC)
        for s=1:length(OPC{m})
            for j=1:length(SPS_PN_dif{m}{s}) 
                SPS_mean_particle_mass{m}{s}(j,1)=(SPS_PN_dif{m}{s}(j,1)*mean_volume(1,1)+SPS_PN_dif{m}{s}(j,2)*mean_volume(2,1)+SPS_PN_dif{m}{s}(j,3)*mean_volume(3,1)+SPS_PN_dif{m}{s}(j,4)*mean_volume(4,1)+SPS_PN_dif{m}{s}(j,5)*mean_volume(5,1))/sum(SPS_PN_dif{m}{s}(j,:));
            end

            for j=1:length(OPC_PN_dif_wo_flowRate{m}{s}) 
                OPC_mean_particle_mass{m}{s}(j,1)=(OPC_PN_dif_wo_flowRate{m}{s}(j,1)*mean_volume(1,1)+OPC_PN_dif_wo_flowRate{m}{s}(j,2)*mean_volume(2,1)+OPC_PN_dif_wo_flowRate{m}{s}(j,3)*mean_volume(3,1)+OPC_PN_dif_wo_flowRate{m}{s}(j,4)*mean_volume(4,1)+OPC_PN_dif_wo_flowRate{m}{s}(j,5)*mean_volume(5,1))/sum(OPC_PN_dif_wo_flowRate{m}{s}(j,:));
            end
        end
    end
end

%{
%synchronize_SPS_PM_dif
Weiz_2_5_dif=synchronize_SPS_PM_dif{3}{:,1};
SPS_2_5_dif=ones(height(synchronize_SPS_PM_dif{3}),1); 
SPS_2_5_dif(:,2:3)=synchronize_SPS_PM_dif{3}{:,3:4};
SPS_2_5_dif_regression_model=SPS_2_5_dif\Weiz_2_5_dif; 
SPS_2_5_dif_regression=SPS_2_5_dif*SPS_2_5_dif_regression_model; 

SPS_2_5_dif_variables={{1,Variables_SPS_PM_2_5,Variables_Weiz_PM_2_5,'uncal'},...
    {SPS_2_5_dif_regression_model,SPS_2_5_dif_regression,Weiz_2_5_dif,'lower bins regression'}};
SPS_2_5_dif_statistics=statistics_table(SPS_2_5_dif_variables);


%Variables_dif=synchronize_SPS_PM_dif{3}(:,3:5);
%}

