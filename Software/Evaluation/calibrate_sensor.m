%% Check which parts to be executed
clear all
use_SensMat_particle_sensor=1;
use_sensorbox_SPS=0;
use_sensorbox_OPC=0;
use_humtemp=1; %check, whether humidity and temperature are measured

SYNCHRONIZE_TIME=minutes(30); %time on which Synchronize data is synchronized

check_calibrate_sensors=1;


%plots before calibration possible
check_plot_sensor_PM_to_reference_PM_over_time=0;
check_plot_sensor_hum_temp_to_reference_hum_temp_over_time=0;
check_scatter_sensor_PM_to_reference_PM=0;
check_scatter_sensor_PM_to_sensor_humidity=0;
check_scatter_sensor_PM_to_sensor_temperature=0;




%plots only after calibration possible 
check_scatter_sensors_to_reference_with_function=0; %needs calibration

CALIBRATION_METHOD_2_5=5;
CALIBRATION_METHOD_10=2; %necessary to define for check_plot_PM_2_5_cal_uncal
%calibration methods: not calibrated, lin reg wo offset, poly1, poly2, poly3, exp, power, reg_tree
%numbers to use:            1               2              3      4      5     6     7       8   
check_plot_PM_2_5_cal_uncal_over_time=1;
check_plot_PM_10_cal_uncal_over_time=0;
check_scatter_PM_2_5_cal_uncal=0;
check_scatter_PM_10_cal_uncal=0;


%time of sensor start
t_real=datetime(2021,02,15,09,54,00);
%starting time defined by sensor (NOT real starting time)
%time = datetime(YYYY,MM,DD,hh,mm,ss)
t_sensor=datetime(2021,02,15,09,54,00);
%correction for slight differences in timescale that might appear 
tcorr=0;
%difference between sensor time and real time 
t_diff=datenum(t_real-t_sensor+tcorr);
%if starting time shown by sensor is the same as the real starting time,
%tdiff is 0. Either t_real and t_sensor are then the same, or t_diff can be
%set to 0 manually
t_diff=0;


%constant definition for reference data reading
REFERENCE_PM_2_5=1;
REFERENCE_PM_10=2;
REFERENCE_H=3;
REFERENCE_T=4;


%% Read in sensor data

sensor=readtable('..\..\Measurement\Data\Weiz_Kalibrierung_SensMat_Partikelsensor_210215_210222\Particle_02\data_joined_2021-02-15.csv');


%OPC sheet to calculate mass
if use_sensorbox_OPC==1
    cal_OPC=readtable('..\..\Docs\Sensors\OPC_N3\calibration_sheet_OPCN3.csv'); 
end


%% Read in and process Weiz data 

%Reference data of Weiz
%get data from luis data 
%http://app.luis.steiermark.at/luft2/suche.php?station1=178&station2=&komponente1=110&station3=&station4=&komponente2=&von_tag=28&von_monat=2&von_jahr=2021&mittelwert=1&bis_tag=3&bis_monat=3&bis_jahr=2021
datapath = '..\..\Measurement\Data\Weiz_Kalibrierung_SensMat_Partikelsensor_210215_210222\Weiz_Referenzdaten_210215_210222'; 
addpath(datapath) 
reference_raw{REFERENCE_PM_2_5}=readtable('pm2-5.xls'); 
reference_raw{REFERENCE_PM_10}=readtable('pm10.xls'); 
reference_raw{REFERENCE_H}=readtable('humidity.xls');
reference_raw{REFERENCE_T}=readtable('temperature.xls');


%changes the format of Weiz data to our format
reference=Weiz_adjustment(reference_raw); 


plot_time_reference=cell(1,length(reference_raw));
%adjusts time of Weiz to datenum format
for w=1:length(reference_raw) %w...which data of Weiz is used (PM 2.5/10,hum,temp)
    plot_time_reference{w} = time_adjustment(reference{w}.Datum,reference{w}.Uhrzeit,0);
end


%% Process sensor data

if use_sensorbox_OPC==1

    %factors for calculating OPC �g/m3; Volume of each bin multiplied by the
    %respiratory factor(see sheet for OPC) 
    factor2_5=cal_OPC{:,8}.*cal_OPC{:,6};
    factor10=cal_OPC{:,8}.*cal_OPC{:,7};

    %function to adjust cell data to a plottable time 
    %[plot_time_OPC] = time_adjustment(OPC_date,OPC_time,tdiff)
    plot_time_sensor = time_adjustment(sensor{:,1},sensor{:,2},t_diff);                                              

    %factor_OPC = 1.65 [g/cm3] / (100 [] * flowrate [ml/s] * 1 [s]) 
    %1 cm3 = 1 ml 
    %->[g/cm3]/([ml/s]*[s]) = [[g/cm3^2]

    %factor10 = [�m3]
    %cm3 = [�m3] * 10^-12 [cm3/�m3]

    %OPC_PM_10 = [g/cm3^2]*10^-12[cm3] = 10^-12 [g/cm3]
    %[�g/m3] = 10^-12*[g/cm3] * 10^6[�g/g] * 10^6[cm3/m3]
    factor_OPC=nan(height(sensor),1);
    sensor_PM_2_5=nan(height(sensor),1);
    sensor_PM_10=nan(height(sensor),1);
    
    for j=1:height(sensor)
        factor_OPC(j,1)=1.65/(100*(sensor{j,29}/100));%SFR in 100*ml/s angegeben 
        sensor_PM_10(j,1)=factor_OPC(j,1)*(sum(sensor{j,3:26}'.*factor10)); 
        sensor_PM_2_5(j,1)=factor_OPC(j,1)*(sum(sensor{j,3:26}'.*factor2_5)); 
    end

    sensor_temp=((sensor{:,27}*175)/((2^16)-1))-45; 
    sensor_hum=(100*sensor{:,28})/((2^16)-1); 
end



if use_sensorbox_SPS==1
    plot_time_sensor = time_adjustment(sensor{:,1},sensor{:,2},t_diff);

    sensor_PM_2_5=sensor{:,4};
    sensor_PM_10=sensor{:,6};    
end



if use_SensMat_particle_sensor==1
%separates date and time
    date_time_split=split(sensor{:,1},{'-','T'});
%appends date of timescale
    date_time=cell(length(date_time_split),1);
    for i=1:length(date_time_split)
        date_time{i,1}=strcat(date_time_split{i,3},'.',date_time_split{i,2},'.',date_time_split{i,1});
    end
%adds time to timescale
    date_time(:,2)=date_time_split(:,4);
%generates plot time in datenum format
    plot_time_sensor = time_adjustment(date_time(:,1),date_time(:,2),t_diff);

    sensor_PM_2_5=sensor{:,3};
    sensor_PM_10=sensor{:,5};  

    sensor_temp=sensor{:,12};
    sensor_hum=sensor{:,14};
end


%% Synchronize data

%first a cell is created with all necessary information to create the timetable
%{ {column1}, {column2},... }            for each column in the timetable a cell is created
%{ {plot_time,data,column_name}, ... }   columns need time, date and title, so in each cell these three have to be set
synchronization_cell={{plot_time_reference{REFERENCE_PM_2_5},reference{REFERENCE_PM_2_5}{:,3},'Reference_PM_2_5'},...
    {plot_time_reference{REFERENCE_PM_10},reference{REFERENCE_PM_10}{:,3},'Reference_PM_10'},...
    {plot_time_sensor,sensor_PM_2_5,'Sensor_PM_2_5'},...
    {plot_time_sensor,sensor_PM_10,'Sensor_PM_10'}};


if use_humtemp==1
    synchronization_cell{1,5}={plot_time_sensor,sensor_hum,'Sensor_H'};
    synchronization_cell{1,6}={plot_time_sensor,sensor_temp,'Sensor_T'};
    synchronization_cell{1,7}={plot_time_reference{REFERENCE_H},reference{REFERENCE_H}{:,3},'Reference_H'};
    synchronization_cell{1,8}={plot_time_reference{REFERENCE_T},reference{REFERENCE_T}{:,3},'Reference_T'};
end

%synchronization of sensors, function synchronize_data needs cell with structure shown above
synchronized_sensors=synchronize_data(synchronization_cell,SYNCHRONIZE_TIME);



%% Autocorrelation 

%synchronized_sensors(250:end,:)=[];

[PM_2_5_xcorr,lags_PM_2_5_xcorr]=xcorr(synchronized_sensors{:,1},synchronized_sensors{:,3});
[max_PM_2_5_xcorr,index_PM_2_5_xcorr]=max(PM_2_5_xcorr);
shift_PM_2_5=lags_PM_2_5_xcorr(index_PM_2_5_xcorr);

[humidity_xcorr,lags_humidity_xcorr]=xcorr(synchronized_sensors{:,5},synchronized_sensors{:,7});
[max_humidity_xcorr,index_humidity_xcorr]=max(humidity_xcorr);
shift_humidity=lags_humidity_xcorr(index_humidity_xcorr);

[temperature_xcorr,lags_temperature_xcorr]=xcorr(synchronized_sensors{:,6},synchronized_sensors{:,8});
[max_temperature_xcorr,index_temperature_xcorr]=max(temperature_xcorr);
shift_temperature=lags_temperature_xcorr(index_temperature_xcorr);

synchronized_sensors{:,3:4}=circshift(synchronized_sensors{:,3:4},shift_PM_2_5,1);
if shift_PM_2_5>0
    synchronized_sensors(end+shift_PM_2_5+1:end,:)=[];
elseif shift_PM_2_5<0
    synchronized_sensors(1:shift_PM_2_5,:)=[];
end

%figure
%plot(lags_PM_2_5_xcorr,PM_2_5_xcorr)



%% Calibrate sensors 
    
synchronized_sensors(synchronized_sensors{:,3}<=0,:)=[];
synchronized_sensors(synchronized_sensors{:,4}<=0,:)=[];


if check_calibrate_sensors==1
    
    %creates cell with different calibration methods, for more information see function 
    sensor_PM_2_5_regression=multiple_regression(synchronized_sensors.Sensor_PM_2_5,synchronized_sensors.Reference_PM_2_5); 
    %uses the cell generated by function multiple_regression to give statistics(explained in function) 
    sensor_PM_2_5_statistics=statistics_table(sensor_PM_2_5_regression); 

    sensor_PM_10_regression=multiple_regression(synchronized_sensors.Sensor_PM_10,synchronized_sensors.Reference_PM_10); 
    sensor_PM_10_statistics=statistics_table(sensor_PM_10_regression); 


    if check_calibrate_sensors && use_humtemp==1
        %humidity and temperature of sensor are used for linear regression
        sensor_PM_2_5_cal_humtemp=ones(length(synchronized_sensors.Sensor_PM_2_5),1); %ones necessary for offset of lienar regression 
        %data is added to calibration matrix
        sensor_PM_2_5_cal_humtemp(:,2:4)=cat(2,synchronized_sensors.Sensor_PM_2_5,synchronized_sensors.Sensor_H,synchronized_sensors.Sensor_T);
        %linear regression to get coefficients
        sensor_PM_2_5_regression_model_humtemp=sensor_PM_2_5_cal_humtemp\synchronized_sensors.Reference_PM_2_5;
        %coefficients multiplied with data to get calibrated values
        sensor_PM_2_5_regression_humtemp=sensor_PM_2_5_cal_humtemp*sensor_PM_2_5_regression_model_humtemp;

        %generates function to show in statistics table
        %2-3-4-1 
        %PM-hum-temp-offset
        sensor_PM_2_5_humtemp_function=strcat(num2str(sensor_PM_2_5_regression_model_humtemp(2,1)),'*PM+',num2str(sensor_PM_2_5_regression_model_humtemp(3,1)),'*H+',...
            num2str(sensor_PM_2_5_regression_model_humtemp(4,1)),'*T+',num2str(sensor_PM_2_5_regression_model_humtemp(1,1)));

        %cell is created (similar to cell from function multiple_regression)for function statistics_table
        sensor_PM_2_5_humtemp_regression_variables={{sensor_PM_2_5_regression_model_humtemp',sensor_PM_2_5_regression_humtemp,synchronized_sensors.Sensor_PM_2_5,'humtemp',sensor_PM_2_5_humtemp_function}};
        %statistics table generated for H&T
        sensor_PM_2_5_humtemp_statistics=statistics_table(sensor_PM_2_5_humtemp_regression_variables);
        %statistics from linear regression with humidity and temperature are added to sensor statistics table
        sensor_PM_2_5_statistics{9,:}=sensor_PM_2_5_humtemp_statistics{1,:};


        %same for sensor_PM_10
        sensor_PM_10_cal_humtemp=ones(length(synchronized_sensors.Sensor_PM_10),1); 
        sensor_PM_10_cal_humtemp(:,2:4)=cat(2,synchronized_sensors.Sensor_PM_10,synchronized_sensors.Sensor_H,synchronized_sensors.Sensor_T);
        sensor_PM_10_regression_model_humtemp=sensor_PM_10_cal_humtemp\synchronized_sensors.Reference_PM_10;
        sensor_PM_10_regression_humtemp=sensor_PM_10_cal_humtemp*sensor_PM_10_regression_model_humtemp; 

        sensor_PM_10_humtemp_function=strcat(num2str(sensor_PM_10_regression_model_humtemp(2,1)),'*PM+',num2str(sensor_PM_10_regression_model_humtemp(3,1)),'*hum+',...
            num2str(sensor_PM_10_regression_model_humtemp(4,1)),'*temp+',num2str(sensor_PM_10_regression_model_humtemp(1,1)));

        sensor_PM_10_humtemp_regression_variables={{sensor_PM_10_regression_model_humtemp,sensor_PM_10_regression_humtemp,synchronized_sensors.Sensor_PM_10,'humtemp',sensor_PM_10_humtemp_function}};
        sensor_PM_10_humtemp_statistics=statistics_table(sensor_PM_10_humtemp_regression_variables);
        sensor_PM_10_statistics{9,:}=sensor_PM_10_humtemp_statistics{1,:};
    end

    display_calibration_methods=["linear regression without offset";"polynom 1st degree";"polynom 2nd degree";"polynom 3rd degree";"exponential";"power";"linear regression with humidity and temperature"];
    disp('Calibration methods')
    disp(display_calibration_methods)
    %disp('Calibration methods: linear regression without offset, polynom (1st, 2nd and 3rd degree), exponential, power, linear regression with humidity and temperature')

    %PM 2.5 table is generated for statistics table with only name of
    %fitting-function, function used, RSME and R2
    sensor_PM_2_5_statistics_short_var_types={'string','string','double','double'};
    sensor_PM_2_5_statistics_short_var_names={'Calibration_method','Function','RSME','R2'};
    sensor_PM_2_5_statistics_short_table=table('Size',[height(sensor_PM_2_5_statistics) length(sensor_PM_2_5_statistics_short_var_types)],'VariableTypes',sensor_PM_2_5_statistics_short_var_types,'VariableNames',sensor_PM_2_5_statistics_short_var_names);
    %parts of initial statistics table are selected, which are used for shorter
    %statistics table
    sensor_PM_2_5_statistics_short_table(:,1)=sensor_PM_2_5_statistics(:,1);
    sensor_PM_2_5_statistics_short_table(:,2)=sensor_PM_2_5_statistics(:,10);
    sensor_PM_2_5_statistics_short_table(:,3)=sensor_PM_2_5_statistics(:,6);
    sensor_PM_2_5_statistics_short_table(:,4)=sensor_PM_2_5_statistics(:,7);
    sensor_PM_2_5_statistics_short_table(8,:)=[];
    disp('PM 2.5 statistics')
    disp(sensor_PM_2_5_statistics_short_table)

    %here the function with the smalles RSME is chosen to be displayed alone
    [sensor_PM_2_5_min_RSME,sensor_PM_2_5_min_RSME_index]=min(sensor_PM_2_5_statistics_short_table.RSME);
    sensor_PM_2_5_statistics_lowest_RSME=sensor_PM_2_5_statistics_short_table(sensor_PM_2_5_min_RSME_index,:);
    disp(sensor_PM_2_5_statistics_lowest_RSME)


    sensor_PM_10_statistics_short_var_types={'string','string','double','double'};
    sensor_PM_10_statistics_short_var_names={'Calibration_method','Function','RSME','R2'};
    sensor_PM_10_statistics_short_table=table('Size',[height(sensor_PM_10_statistics) length(sensor_PM_10_statistics_short_var_types)],'VariableTypes',sensor_PM_10_statistics_short_var_types,'VariableNames',sensor_PM_10_statistics_short_var_names);

    sensor_PM_10_statistics_short_table(:,1)=sensor_PM_10_statistics(:,1);
    sensor_PM_10_statistics_short_table(:,2)=sensor_PM_10_statistics(:,10);
    sensor_PM_10_statistics_short_table(:,3)=sensor_PM_10_statistics(:,6);
    sensor_PM_10_statistics_short_table(:,4)=sensor_PM_10_statistics(:,7);
    sensor_PM_10_statistics_short_table(8,:)=[];
    disp('PM 10 statistics')
    disp(sensor_PM_10_statistics_short_table)

    [sensor_PM_10_min_RSME,sensor_PM_10_min_RSME_index]=min(sensor_PM_10_statistics_short_table.RSME);
    sensor_PM_10_statistics_lowest_RSME=sensor_PM_10_statistics_short_table(sensor_PM_10_min_RSME_index,:);
    disp(sensor_PM_10_statistics_lowest_RSME)

end


%% Plotting of sensor to reference

if check_plot_sensor_PM_to_reference_PM_over_time==1
    %plot sensor PM to reference PM 
    title_subplot_PM={'PM 2.5','PM 10'};

    sensor_object_plot={{'Sensor',synchronized_sensors.Time,synchronized_sensors{:,3:4},'Sensor',title_subplot_PM},...
        {'Reference',synchronized_sensors.Time,synchronized_sensors{:,1:2},'Reference',title_subplot_PM}};

    particle_plot_multiple(sensor_object_plot)
end

if check_plot_sensor_hum_temp_to_reference_hum_temp_over_time==1
    %plot humidity&temperature of sensor to reference PM
    figure
    subplot(2,1,1)
    plot(synchronized_sensors.Time,synchronized_sensors.Sensor_H)
    hold on
    plot(synchronized_sensors.Time,synchronized_sensors.Reference_H)
    xlabel('Time')
    ylabel('[%]')
    title('Humidity')
    legend('Sensor','Reference')
    subplot(2,1,2)
    plot(synchronized_sensors.Time,synchronized_sensors.Sensor_T)
    hold on
    plot(synchronized_sensors.Time,synchronized_sensors.Reference_T)
    xlabel('Time')
    ylabel('[�C]')
    title('Temperature')
    legend('Sensor','Reference')
end

if check_scatter_sensors_to_reference_with_function==1
    %scatter sensor to reference with polynom
    scatter_multiple(sensor_PM_2_5_regression,synchronized_sensors.Sensor_PM_2_5,'Sensor PM 2.5')
    scatter_multiple(sensor_PM_10_regression,synchronized_sensors.Sensor_PM_10,'Sensor PM 10')
end

if check_scatter_sensor_PM_to_reference_PM==1
%scatter sensor PM to reference PM
    figure
    subplot(2,1,1)
    scatter(synchronized_sensors.Reference_PM_2_5,synchronized_sensors.Sensor_PM_2_5)
    xlabel('Reference PM [�g/m3]')
    ylabel('Sensor PM [�g/m3]')
    title('PM 2.5')
    subplot(2,1,2)
    scatter(synchronized_sensors.Reference_PM_10,synchronized_sensors.Sensor_PM_10)
    xlabel('Reference PM [�g/m3]')
    ylabel('Sensor PM [�g/m3]')
    title('PM 10')
end

if check_scatter_sensor_PM_to_sensor_humidity==1
    %scatter sensor PM to humidity
    figure
    subplot(2,1,1)
    scatter(synchronized_sensors.Sensor_H,synchronized_sensors.Sensor_PM_2_5)
    xlabel('Humidity [%]')
    ylabel('Sensor PM [�g/m3]')
    title('PM 2.5')
    subplot(2,1,2)
    scatter(synchronized_sensors.Sensor_H,synchronized_sensors.Sensor_PM_10)
    xlabel('Humidity [%]')
    ylabel('Sensor PM [�g/m3]')
    title('PM 10')
end

if check_scatter_sensor_PM_to_sensor_temperature==1
    %scatter sensor PM to temperature
    figure
    subplot(2,1,1)
    scatter(synchronized_sensors.Sensor_T,synchronized_sensors.Sensor_PM_2_5)
    xlabel('Temperature [�C]')
    ylabel('Sensor PM [�g/m3]')
    title('PM 2.5')
    subplot(2,1,2)
    scatter(synchronized_sensors.Sensor_T,synchronized_sensors.Sensor_PM_10)
    xlabel('Temperature [�C]')
    ylabel('Sensor PM [�g/m3]')
    title('PM 10')
end


if check_plot_PM_2_5_cal_uncal_over_time==1
    %PM 2.5
    figure
    subplot(2,1,1)
    plot(synchronized_sensors.Time,synchronized_sensors.Sensor_PM_2_5)
    hold on
    plot(synchronized_sensors.Time,synchronized_sensors.Reference_PM_2_5)
    xlabel('Time')
    ylabel('PM [�g/m3]')
    legend('Sensor','Reference')
    title('Not calibrated')
    subplot(2,1,2)
    plot(synchronized_sensors.Time,sensor_PM_2_5_regression{CALIBRATION_METHOD_2_5}{2})
    hold on
    plot(synchronized_sensors.Time,synchronized_sensors.Reference_PM_2_5)
    xlabel('Time')
    ylabel('PM [�g/m3]')
    legend('Sensor','Reference')
    title('Calibrated')
end

if check_plot_PM_10_cal_uncal_over_time==1
    %PM 10
    figure
    subplot(2,1,1)
    plot(synchronized_sensors.Time,synchronized_sensors.Sensor_PM_10)
    hold on
    plot(synchronized_sensors.Time,synchronized_sensors.Reference_PM_10)
    xlabel('Time')
    ylabel('PM [�g/m3]')
    legend('Sensor','Reference')
    title('Not calibrated')
    subplot(2,1,2)
    plot(synchronized_sensors.Time,sensor_PM_10_regression{CALIBRATION_METHOD_10}{2})
    hold on
    plot(synchronized_sensors.Time,synchronized_sensors.Reference_PM_10)
    xlabel('Time')
    ylabel('PM [�g/m3]')
    legend('Sensor','Reference')
    title('Calibrated')
end


if check_scatter_PM_2_5_cal_uncal==1
    figure
    subplot(2,1,1)
    scatter(synchronized_sensors.Reference_PM_2_5,sensor_PM_2_5_regression{CALIBRATION_METHOD_2_5}{2})
    xlabel('Reference [�g/m3]')
    ylabel('Sensor [�g/m3]')
    title('PM 2.5 calibrated')
    subplot(2,1,2)
    scatter(synchronized_sensors.Reference_PM_2_5,synchronized_sensors.Sensor_PM_2_5)
    xlabel('Reference [�g/m3]')
    ylabel('Sensor [�g/m3]')
    title('PM 2.5 not calibrated')
end
    
if check_scatter_PM_10_cal_uncal==1
    figure
    subplot(2,1,1)
    scatter(synchronized_sensors.Reference_PM_10,sensor_PM_10_regression{CALIBRATION_METHOD_10}{2})
    xlabel('Reference [�g/m3]')
    ylabel('Sensor [�g/m3]')
    title('PM 10 calibrated')
    subplot(2,1,2)
    scatter(synchronized_sensors.Reference_PM_10,synchronized_sensors.Sensor_PM_10)
    xlabel('Reference [�g/m3]')
    ylabel('Sensor [�g/m3]')
    title('PM 10 not calibrated')
end







