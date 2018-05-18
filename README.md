Wat-tor Simulation
===================
### Overview
This is a short program used to simulate the conditions and relationship between sharks and fishes in an ecosystem. The goal is to implement it utlising threads and bench mark the results.

The world will be mapped using 2d arrays and will be made up of objects that are either sharks, fish, or water.

To measure the speed of the program, it will be run through a 1000 iterations, and the average time will be taken, and documented using graphs.

### Tools & Environment
> - C++ for the main project code
> - Python for scripts
> - Emacs for the  IDE
> - g++ for the compiler
> - Doxygen for the documentation
> - OpenMp for multithreading
> - Gprof for profiling
>  - Plotly for the Graphs
>  - Ubuntu 16.04 for the operating system

----------
### Snapshot
![alt text](https://github.com/phelantomas/Wa-tor/blob/master/Charts/wator.PNG)

Files
-------------

> **wa-tor.cpp**
> - This is the main application source file.
> 
> **Animal.cpp**
> - This is used to differentiate between a fish, shark, or water. 
> 
> **Animal.h**
> - Header file for Animal.cpp.
> 
> **Makefile**
> - Uses g++ to compile and debug C++ code.
> 
> **timer.py**
> - Times were all generated by running the code 100 times.


#### <i class="icon-file"></i> Code running in parrallel
> **System Specs:**

> - Ram : 3541MB
> - Processor : Intel(R) Core(TN) i7-4700HQ CPU @ 2.40GHz
> - OS : Ubuntu
> - Cores : 3

(35 x 60) Size of World

![alt text](https://github.com/phelantomas/Wa-tor/blob/master/Charts/NoOfThreadsChart.png)

![alt text](https://github.com/phelantomas/Wa-tor/blob/master/Charts/NoPauseCharts.png)

(18 x 30) Size of World

![alt text](https://github.com/phelantomas/Wa-tor/blob/master/Charts/SmallWorld.png)

> - Ram : 2780MB
> - Processor : Intel Core i5-6200U CPU @ 2.40GHz
> - OS : Ubuntu
> - Cores: 1

(40 x 70) Size of World

![alt text](https://github.com/phelantomas/Wa-tor/blob/master/Charts/JakeSSWorld.png)

(35 x 60) Size of World

![alt text](https://github.com/phelantomas/Wa-tor/blob/master/Charts/JakeSWorld.png)

(18 x 30) Size of World

![alt text](https://github.com/phelantomas/Wa-tor/blob/master/Charts/JakeWorld.png)


