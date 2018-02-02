Wat-tor Simulation
===================

This is a short program used to simulate the conditions and relationship between sharks and fishes in an ecosystem. It is being developed in C++, and OpenMp.

----------


Files
-------------

Wa-tor.cpp

> **Note:**

> - This is the main application source file.

Animal.cpp

> **Note:**

> - This is used to differentiate between a fish, shark, or water. 

Animal.h

> **Note:**

> - Header file for Animal.cpp

Makefile

> **Note:**

> - Uses g++ to compile and debug C++ code


#### <i class="icon-file"></i> Code running in serial

> **Note:**  
> Flat profile:  
> Each sample counts as 0.01 seconds.  
>   %   cumulative   self              self     total           
>  time   seconds   seconds    calls  ms/call  ms/call  name    
>  33.36      0.01     0.01   274453     0.00     0.00  frame_dummy  
>  33.36      0.02     0.01      800     0.01     0.01  displayMap()  
>  33.36      0.03     0.01                             checkOcean()  
>   0.00      0.03     0.00  1684200     0.00     0.00  Animal::makeAnimal(int, int, int)  
>   0.00      0.03     0.00    29692     0.00     0.00  Animal::showAnimal()  
>   0.00      0.03     0.00    23820     0.00     0.00  findPartner(int, int, int, Animal*)  
>   0.00      0.03     0.00     5872     0.00     0.00  moveShark(int, int)  
>   0.00      0.03     0.00     2100     0.00     0.00  __do_global_dtors_aux  
>   0.00      0.03     0.00      803     0.00     0.00  moveFish(int, int)  
>   0.00      0.03     0.00        1     0.00    12.15  __static_initialization_and_destruction_0(int, int)  
>   0.00      0.03     0.00        1     0.00     0.00  std::operator&(std::_Ios_Fmtflags, std::_Ios_Fmtflags)  
>   0.00      0.03     0.00        1     0.00    12.15  main  
>   
> 			Call graph  
>   
>   
> granularity: each sample hit covers 2 byte(s) for 33.31% of 0.03 seconds  
>   
> index % time    self  children    called     name  
>                                                  <spontaneous>  
> [1]     59.5    0.01    0.01                 checkOcean() [1]  
>                 0.00    0.01    5872/5872        moveShark(int, int) [7]  
>                 0.00    0.00       1/803         moveFish(int, int) [8]  
> -----------------------------------------------  
>                 0.00    0.01       1/1           __static_initialization_and_destruction_0(int, int) [3]  
> [2]     40.5    0.00    0.01       1         main [2]  
>                 0.01    0.00     800/800         displayMap() [6]  
>                 0.00    0.00     802/803         moveFish(int, int) [8]  
>                 0.00    0.00    3270/274453      frame_dummy [5]  
>                 0.00    0.00    2100/2100        __do_global_dtors_aux [17]  
>                 0.00    0.00       1/1           std::operator&(std::_Ios_Fmtflags, std::_Ios_Fmtflags) [18]  
> -----------------------------------------------  
>                 0.00    0.01       1/1           std::ios_base::setf(std::_Ios_Fmtflags, std::_Ios_Fmtflags) [4]  
> [3]     40.5    0.00    0.01       1         __static_initialization_and_destruction_0(int, int) [3]  
>                 0.00    0.01       1/1           main [2]  
> -----------------------------------------------  
>                                                  <spontaneous>  
> [4]     40.5    0.00    0.01                 std::ios_base::setf(std::_Ios_Fmtflags, std::_Ios_Fmtflags) [4]  
>                 0.00    0.01       1/1           __static_initialization_and_destruction_0(int, int) [3]  
> -----------------------------------------------  
>                 0.00    0.00    3270/274453      main [2]  
>                 0.00    0.00   55669/274453      moveFish(int, int) [8]  
>                 0.01    0.00  215514/274453      moveShark(int, int) [7]  
> [5]     33.3    0.01    0.00  274453         frame_dummy [5]  
> -----------------------------------------------  
>                 0.01    0.00     800/800         main [2]  
> [6]     33.3    0.01    0.00     800         displayMap() [6]  
>                 0.00    0.00   23820/23820       findPartner(int, int, int, Animal*) [16]  
> -----------------------------------------------  
>                 0.00    0.01    5872/5872        checkOcean() [1]  
> [7]     26.2    0.00    0.01    5872         moveShark(int, int) [7]  
>                 0.01    0.00  215514/274453      frame_dummy [5]  
>                 0.00    0.00   23820/29692       Animal::showAnimal() [15]  
> -----------------------------------------------  
>                 0.00    0.00       1/803         checkOcean() [1]  
>                 0.00    0.00     802/803         main [2]  
> [8]      6.8    0.00    0.00     803         moveFish(int, int) [8]  
>                 0.00    0.00   55669/274453      frame_dummy [5]  
>                 0.00    0.00    5872/29692       Animal::showAnimal() [15]  
> -----------------------------------------------  
>                 0.00    0.00 1684200/1684200     populateMap() [20]  
> [14]     0.0    0.00    0.00 1684200         Animal::makeAnimal(int, int, int) [14]  
> -----------------------------------------------  
>                 0.00    0.00    5872/29692       moveFish(int, int) [8]  
>                 0.00    0.00   23820/29692       moveShark(int, int) [7]  
> [15]     0.0    0.00    0.00   29692         Animal::showAnimal() [15]  
> -----------------------------------------------  
>                 0.00    0.00   23820/23820       displayMap() [6]  
> [16]     0.0    0.00    0.00   23820         findPartner(int, int, int, Animal*) [16]  
> -----------------------------------------------  
>                 0.00    0.00    2100/2100        main [2]  
> [17]     0.0    0.00    0.00    2100         __do_global_dtors_aux [17]  
> -----------------------------------------------  
>                 0.00    0.00       1/1           main [2]  
> [18]     0.0    0.00    0.00       1         std::operator&(std::_Ios_Fmtflags, std::_Ios_Fmtflags) [18]  
> -----------------------------------------------  
>   
> Index by function name  
>   
>    [1] checkOcean()            [8] moveFish(int, int)     [18] std::operator&(std::_Ios_Fmtflags, std::_Ios_Fmtflags)  
>    [6] displayMap()            [7] moveShark(int, int)    [17] __do_global_dtors_aux  
>   [16] findPartner(int, int, int, Animal*) [14] Animal::makeAnimal(int, int, int) [5] frame_dummy  
>    [3] __static_initialization_and_destruction_0(int, int) [15] Animal::showAnimal() [2] main  

#### <i class="icon-file"></i> Code running in parrallel
> **System Specs:**

> - Ram : 3541
> - Processor : Intel(R) Core(TN) i7-4700HQ CPU @ 2.40GHz
> - OS : Ubuntu

(35 x 60) Size of World

![alt text](https://github.com/phelantomas/Wa-tor/blob/master/barchart.png)

(18 x 30) Size of World

![alt text](https://github.com/phelantomas/Wa-tor/blob/master/barchart2.png)




