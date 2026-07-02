% --- MATLAB Simulation for AeroGuard Air Quality Monitor ---
% Author: S. Pranesh Kumaran
clear; clc; close all;

% 1. System Parameters 
AQI_THRESHOLD = 800;
simulation_time = 60; % Simulate 60 seconds of operation

% 2. Generate Simulated Sensor Data
t = 1:simulation_time; 

% Simulate Gas Level: Normal air (~300), sudden leak at t=20 to 40
rawGasValue = 300 + 50*randn(1, simulation_time); 
rawGasValue(20:40) = rawGasValue(20:40) + 600;    

% Simulate Temp and Humidity
temp = 32 + 0.5*randn(1, simulation_time); 
hum = 57 + 1.5*randn(1, simulation_time);  

% 3. Initialize Output Array for Buzzer
buzzer_state = zeros(1, simulation_time);

% 4. Control Logic (Mimicking ESP32)
for i = 1:simulation_time
    if rawGasValue(i) > AQI_THRESHOLD
        buzzer_state(i) = 1; % Buzzer ON
    else
        buzzer_state(i) = 0; % Buzzer OFF
    end
end

% 5. Visualization 
figure('Name', 'AeroGuard Simulation', 'NumberTitle', 'off', 'Position', [100, 100, 800, 600]);

subplot(3,1,1);
plot(t, rawGasValue, 'b', 'LineWidth', 1.5); hold on;
yline(AQI_THRESHOLD, 'r--', 'Threshold (800)', 'LineWidth', 1.5, 'LabelHorizontalAlignment', 'left');
title('Simulated MQ135 Gas Sensor Level');
ylabel('Analog Value'); grid on;

subplot(3,1,2);
plot(t, temp, 'r', 'LineWidth', 1.5); hold on;
plot(t, hum, 'c', 'LineWidth', 1.5);
title('Simulated DHT11 Climate Data');
legend('Temp (C)', 'Humidity (%)', 'Location', 'best');
ylabel('Value'); grid on;

subplot(3,1,3);
stairs(t, buzzer_state, 'k', 'LineWidth', 2);
title('Buzzer Output State (0 = OFF, 1 = ON)');
xlabel('Time (s)'); ylabel('Logic State');
ylim([-0.5 1.5]); yticks([0 1]); yticklabels({'OFF', 'ON'}); grid on;