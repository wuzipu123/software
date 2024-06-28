%% Notes for user 

%{
Where to get the calibration parameters: 
Calibration parameters are generated in file calibrate_sensor.m

calibration parameters are stored in (names used in file calibrate_sensors.m)
    sensor_PM_2_5_regression and sensor_PM_10_regression 
        for linreg_wo_offset,poly1,poly2,poly3,exp,power 
        stored in {calibration_method}{1} 
        with calibration_method are the above mentioned calibration methods
        stored in: 
            linreg_wo_offset=2
            poly1=3
            poly2=4
            poly3=5
            exp=6
            power=7
        (example: calibration_method=3 would mean the data from poly1 are used) 
        (calibration_method=0 is no calibration, calibration_method=8 is
        regression tree; tree was not considered in calibration) 

    sensor_PM_2_5_humtemp_regression_variables and sensor_PM_10_humtemp_regression_variables
        stored in {1}{1} 
        (cell only has calibration method humtemp, it is extra since it has
        more variables for calibration than rest of calibration methods
        other calibration methods only have sensor_data and as target reference_data, 
        humtemp additionally has humidity and temperature as variables) 

The calibration method to be used is also chosen by calibrate_sensor.m and
is shown in the command window for both PM 2.5 and PM 10 

Statistics for calibration are shown in sensor_PM_2_5_statistics and
sensor_PM_10_statistics (where humtemp is included) 
or 
sensor_PM_2_5_statistics_short_table or sensor_PM_10_statistics_short_table
(where only R2 and RSME, as well as function name and function itself are
shown, this table is given in command window) 

%}
%% Check which sensor to be used

use_SensMat_particle_sensor=0;
use_sensorbox_SPS=0;
use_sensorbox_OPC=1;
use_humtemp=1; %check, whether humidity and temperature are measured


%time of sensor start
t_real=datetime(2020,03,10,10,40,00);
%starting time defined by sensor (NOT real starting time)
%time = datetime(YYYY,MM,DD,hh,mm,ss)
t_sensor=datetime(2019,12,10,12,56,54);
%correction for slight differences in timescale that might appear 
tcorr=minutes(0);
%difference between sensor time and real time 
t_diff=datenum(t_real-t_sensor+tcorr);

%if starting time shown by sensor is the same as the real starting time,
%tdiff is 0. Either t_real and t_sensor are then the same, or t_diff can be
%set to 0 manually
t_diff=0;


%Possible strings for calibration: 
%   linreg_wo_offset 
%   poly 
%   exp 
%   power

%poly all use the same line of code, the amount of calibration parameters
%   are what determines which poly function is used
calibration_function_PM_2_5="poly"; 
calibration_parameters_PM_2_5=[1 3 5]; 

calibration_function_PM_10="poly"; 
calibration_parameters_PM_10=[1 3 4]; 


%% Read in sensor data

%sensor=readtable('C:\Users\therumakisakura\Documents\Daten\SensMat_Particle_Sensor_Data\data_2020-11-30_10-35-02.csv');
sensor=readtable('..\..\Measurement\Data\Weiz_Kalibrierung_200227_200310\Sensor 1\Data_OPC-N3_10_12_2019_12_58.csv');

%OPC sheet to calculate mass
if use_sensorbox_OPC==1
    cal_OPC=readtable('..\..\Docs\Sensors\OPC_N3\calibration_sheet_OPCN3.csv'); 
end


%% Process sensor data

if use_sensorbox_OPC==1
    %factors for calculating OPC µg/m3; Volume of each bin multiplied by the
    %respiratory factor(see sheet for OPC) 
    factor2_5=cal_OPC{:,8}.*cal_OPC{:,6};
    factor10=cal_OPC{:,8}.*cal_OPC{:,7};

    %function to adjust cell data to a plottable time 
    %[plot_time_OPC] = time_adjustment(OPC_date,OPC_time,tdiff)
    plot_time_sensor = time_adjustment(sensor{:,1},sensor{:,2},t_diff);                                              

    %factor_OPC = 1.65 [g/cm3] / (100 [] * flowrate [ml/s] * 1 [s]) 
    %1 cm3 = 1 ml 
    %->[g/cm3]/([ml/s]*[s]) = [[g/cm3^2]

    %factor10 = [µm3]
    %cm3 = [µm3] * 10^-12 [cm3/µm3]

    %OPC_PM_10 = [g/cm3^2]*10^-12[cm3] = 10^-12 [g/cm3]
    %[µg/m3] = 10^-12*[g/cm3] * 10^6[µg/g] * 10^6[cm3/m3]
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
        date_time{i,1}=append(date_time_split{i,3},'.',date_time_split{i,2},'.',date_time_split{i,1});
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

%% Calibration of sensors (with external data) 

%PM 2,5 
if strcmp(calibration_function_PM_2_5,"linreg_wo_offset")
    calibrated_PM_2_5=sensor_PM_2_5/calibration_parameters_PM_2_5(1,1);
elseif strcmp(calibration_function_PM_2_5,"poly")
    calibrated_PM_2_5=polyval(calibration_parameters_PM_2_5,sensor_PM_2_5);
elseif strcmp(calibration_function_PM_2_5,"exp")
    calibrated_PM_2_5=calibration_parameters_PM_2_5(1,1)*exp(calibration_parameters_PM_2_5(1,2)*sensor_data);
elseif strcmp(calibration_function_PM_2_5,"power")
    calibrated_PM_2_5=calibration_parameters_PM_2_5(1,1)*sensor_data.^calibration_parameters_PM_2_5(1,2);
elseif strcmp(calibration_function_PM_2_5,"humtemp")
    calibration_humtemp=[sensor_PM_2_5 sensor_hum sensor_temp];
    calibrated_PM_2_5=calibration_humtemp*calibration_parameters_PM_2_5; 
end

%PM 10 
if strcmp(calibration_function_PM_10,"linreg_wo_offset")
    calibrated_PM_10=sensor_PM_10/calibration_parameters_PM_10(1,1);
elseif strcmp(calibration_function_PM_10,"poly")
    calibrated_PM_10=polyval(calibration_parameters_PM_10,sensor_PM_10);
elseif strcmp(calibration_function_PM_10,"exp")
    calibrated_PM_10=calibration_parameters_PM_10(1,1)*exp(calibration_parameters_PM_10(1,2)*sensor_data);
elseif strcmp(calibration_function_PM_10,"power")
    calibrated_PM_10=calibration_parameters_PM_10(1,1)*sensor_data.^calibration_parameters_PM_10(1,2);
elseif strcmp(calibration_function_PM_10,"humtemp")
    calibration_humtemp=[sensor_PM_10 sensor_hum sensor_temp];
    calibrated_PM_10=calibration_humtemp*calibration_parameters_PM_10; 
end




%% Plotting of sensor 

Sensor_data=[calibrated_PM_2_5 calibrated_PM_10];

title_subplot={'PM 2.5','PM 10'};

sensor_object_plot={{'Sensor',plot_time_sensor,Sensor_data,'Sensor',title_subplot}};

particle_plot_multiple(sensor_object_plot)









