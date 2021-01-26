#include "SerialStream.h"
#include "dhry.h"
#include "mbed.h"

#define BAUDRATE 115200

DigitalOut myled(LED1);
Timer timer;
BufferedSerial serial(USBTX, USBRX, BAUDRATE);
SerialStream<BufferedSerial> pc(serial);

int main()
{
    double benchtime, dps;
    unsigned long loops;

    pc.printf("Dhrystone Benchmark Program C/1 12/01/84\r\n");
    timer.start();
    while(1)
    {
        loops = 0l;
        myled = 1;
        timer.reset();
        do
        {
            Proc0();
            loops += LOOPS;
            benchtime = timer.read();
        } while(benchtime <= 60.000);
        myled = 0;
        dps = (double)loops / benchtime;
        pc.printf("Dhrystone time for %ld passes = %.3f sek\r\n", loops,
                  benchtime);
        pc.printf("This machine benchmarks at %.0f dhrystones/second\r\n", dps);

        ThisThread::sleep_for(1s);
    }
}
