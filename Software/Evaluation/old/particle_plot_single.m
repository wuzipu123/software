%sensor_object_plot={{1,2,3,4,5}{1,2,3,4,5}}
%sensor_object_plot={{'OPC_name', OPC_time, OPC_matrix, 'OPC_legend',title_subplot},...
                    %{'SPS_name', SPS_time, SPS_matrix, 'SPS_legend',title_subplot}};

%p_name={'OPC', 'SPS'}; -> 1
%p_time={plot_time_OPC,plot_time_SPS}; -> 2
%p_matrix={OPC_normalize,SPS_normalize}; -> 3
%p_legend={'OPC','SPS'}; -> 4
%title_subplot={{'PN 0.5'},{'PN 1'},{'PN 2.5'},{'PN 4'},{'PN 10'}}; -> 5 

function particle_plot_single(fig_handle, sensor_object_plot)
%void myfun(void)
% singl plots
figure(fig_handle);
size_of_matrix=size(sensor_object_plot{3}); 
%for the number od particle number data colums 
    for l=1:size_of_matrix(2) 
        %create subplots for each colum below the other 
        subplot(size_of_matrix(2),1,l)
        hold on
        %x-axis time. y-axis PN data 
        plot(sensor_object_plot{2},sensor_object_plot{3}(:,l)); 
        %converts serial date numbers back to the imput format 'dd.mm.yyyy HH:MM:SS'
        datetick('x')
        title(sensor_object_plot{5}{l}) 
        xlabel(' Time ')
        ylabel('PN [ #/cm^3 ]')
        legend(sensor_object_plot{4}) 
        hold off  
    end   
end 




