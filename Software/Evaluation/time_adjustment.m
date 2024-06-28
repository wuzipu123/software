function [plot_time_Sensor] = time_adjustment(Sensor_date,Sensor_time,tdiff)
%'time_adjustment' is used to change the time format given by the sensors
%and reference to the datenum format. 

%Input: 
%Date,Time,timedifference
%Date must be in format dd.mm.yyyy or 'dd.mm.yyyy'
%Time format: has more options how to look, since SensMat_particle_sensor,
%SPS and OPC from sensorbox and reference data from Weiz all have to be
%read differently, since some are a table, some are cells. 


%Output: 
%Date and time in datenum format as a column. 


%initialize plot time 
plot_time_Sensor = nan(size(Sensor_date));
%define format for the loop in the time_adjustment function 
formatIn = 'dd.mm.yyyy HH:MM:SS';

    % for every increment in sensor date 
    for i=1:numel(Sensor_date)
        % converts the datetime or duration values in the input array to serial date numbers
        %'char' is needed for input of time, since sensorbox saves time as
        %duration - not possible to read in without use of 'char'
        plot_time_Sensor(i) = (datenum([Sensor_date{i},' ',char(Sensor_time(i))],formatIn)+tdiff);
    end

end
