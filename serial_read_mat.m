clear all;

s = serial('COM5'); %Setiing the Serial COM
set(s, 'BaudRate', 250000); %Setting the byte rate
fopen(s);

%Setting up the variables
j = 0;
theta = [];
phi = [];
dist = [];
%Runs the loop while dataAvailable is true
dataAvailable = true;

%Using try-catch to catch the error and close the port
try
    while(dataAvailable) %Runs while it is true
        if s.BytesAvailable>=0
            j = j+1;
            serialLine = fscanf(s); %scanning the complete line
            position = sscanf(serialLine, '%d %d %d'); %All three are ints
            endOf = sscanf(serialLine, '%s');%Also scans it as a char
            %fprintf(,'%d');

            if strcmp(endOf, 'AWS') %If the char scanned is AWS
                disp('ending data'); 
                %Makes dataAvailable false and breaks out of the loop
                dataAvailable = false; 
            else
                %Assigns the scanned values to the respective variable
                theta(j) = position(2);
                phi(j) = position(1);
                dist(j) = position(3);
            end
        end
    end
        %Closes the port and exits it
        disp('Out while');
        fclose(s);
        delete(s);
        clear s
catch
    %Catches the error and makes sure that the serial port is closed
    disp('Catch')
    fclose(s);
    delete(s);
    clear s
end

%Making the two-dimensional array for pcolor
%w helps with the depth of the pcolor plot
w = 1;
 for j = 1:71
     for i = 1:61
         A(i,j) = dist(w);
         w = w + 1;
     end
 end
 A = rot90(A,2); %Rotating the matrix to plot is upright
 pcolor(A);