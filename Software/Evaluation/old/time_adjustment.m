function [plot_time_OPC, plot_time_SPS] = time_adjustment(OPC_date,OPC_time,SPS_date,SPS_time)

%initialize plot time 
plot_time_OPC = nan(size(OPC_date));
plot_time_SPS = nan(size(SPS_date));
%define format for the loop in the time_adjustment function 
formatIn = 'dd.mm.yyyy HH:MM:SS';

    % for every increment in OPC date 
    for i=1:numel(OPC_date)
        % converts the datetime or duration values in the input array (OPC_date and OPC_time) to serial date numbers
        plot_time_OPC(i) = datenum([OPC_date{i},' ',char(OPC_time(i))],formatIn);
    end
    % for every increment in SPS date 
    for j=1:numel(SPS_date)
        % converts the datetime or duration values in the input array (SPS_date and SPS_time) to serial date numbers
        plot_time_SPS(j) = datenum([SPS_date{j},' ',char(SPS_time(j))],formatIn);
    end
end

