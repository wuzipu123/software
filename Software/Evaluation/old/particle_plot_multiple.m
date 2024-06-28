%sensor_object_plot={{1,2,3,4,5}{1,2,3,4,5}}
%sensor_object_plot={{'OPC_name', OPC_time, OPC_matrix, 'OPC_legend',title_subplot},...
                    %{'SPS_name', SPS_time, SPS_matrix, 'SPS_legend',title_subplot}};

%p_name={'OPC', 'SPS'}; -> 1
%p_time={plot_time_OPC,plot_time_SPS}; -> 2
%p_matrix={OPC_normalize,SPS_normalize}; -> 3
%p_legend={'OPC','SPS'}; -> 4
%title_subplot={{'PN 0.5'},{'PN 1'},{'PN 2.5'},{'PN 4'},{'PN 10'}}; -> 5 

%defines a function with no output variables 
function particle_plot_safe_multiple(sensor_object_plot)

%creates figure with figure handle for the comparision of OPC and SPS
fig_compare = figure('Name','OPC vs SPS');
%initialize cell with legend labels for the comparison plot 
legend_labels = cell(1, numel(sensor_object_plot));

% loop to create single plots for OPC and SPS 
    for k=1:numel(sensor_object_plot)   
        %creates figure with figure handle for OPC and SPS values 
        fig_single = figure('Name',sensor_object_plot{k}{1});
        %creates title for the subplots 
        title(sensor_object_plot{k}{1})
        
        % calls function where the subplots are made 
        particle_plot_single(fig_single,sensor_object_plot{k});    %stores it in fig_single for ceach increment (OPC and SPS)
        particle_plot_single(fig_compare,sensor_object_plot{k});   %stores it in fig_compare for ceach increment (OPC and SPS)
        %creates legends for the single plots 
        legend_labels{k} = sensor_object_plot{k}{4};
    end

figure(fig_compare)
size_of_matrix=size(sensor_object_plot{1}{3}); 

    % prevents overwrite of the legend in the comparision figure 
    for ll=1:size_of_matrix(2) 
        subplot(size_of_matrix(2),1,ll)
        legend(legend_labels);
    end
end 




