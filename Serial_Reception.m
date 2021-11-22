clc
clear all
delete(instrfind({'port'},{'COM1'}));
puerto=serial('COM1');
puerto.BaudRate=250000;
set(puerto,'StopBits',1);
set(puerto,'DataBits',8);
set(puerto,'Terminator','LF')
set(puerto,'InputBufferSize',4);
fopen(puerto);
muestras_tiempo=128;
muestras_frecuencia=muestras_tiempo*2;
times=0;
while (1)
    finish=0;
    while finish==0
        Iniciador=fread(puerto,1,'single')
        if Iniciador==123456
            for i=1:1:muestras_frecuencia
                magnitud(i)=fread(puerto,1,'single');
            end
            finish=1;
        end
    end
    finish=0;
    while finish==0
        Iniciador=fread(puerto,1,'single')
        if Iniciador==7891011
            for i=1:1:muestras_frecuencia
                frecuencia(i)=fread(puerto,1,'single');
            end
            finish=1;
        end
    end
    plot(frecuencia,magnitud);
    pause(0.0005);
    clear frecuencia;
    clear magnitud;
    times=times+1;
end
fclose(puerto);
delete(puerto);
clear puerto;
