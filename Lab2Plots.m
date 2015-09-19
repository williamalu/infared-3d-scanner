%Voltage and output calculation
C = [60,55,50,45,40,35,30,25,20,15];
D = [217,237,257,289,317,360,407,470,514,561];
E = (D./1023).*5;
plot(C,E, 'bo-')
%axis([13 62 210 570])
axis([13 62 0 5])
xlabel('Actual Distances (cm)');
ylabel('Analog Voltage Reading (0-1023)');
title('Distance v/s Voltage Reading');

%Error Calculation for POE Lab 2
%{
A = [21 26 31 36 41 46 51 56];
B = [21 27 31 37 42 48 51 57];
plot(A,B, 'bo-')
axis([15 60 15 60])
xlabel('Actual Distances (cm)');
ylabel('Calculated Distances (cm)');
title('Error Plot after Calibration');
%}