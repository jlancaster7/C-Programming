# C-Programming Project

This project was apart of the Duke University Introduction to C Programming Course.

It provides a full simulation of a game of texas hold'em, if given the initial hands. This can include only 2 hole cards and the rest will be drawn from the deck. 
It can then give you odds on how often a given hand will win with other hands present. This is done through Monte Carlo simulations. The input file just needs to be
a text file with the hands entered as follows:

3h ?0 Kc ?1 Qh ?2 2h\n
Ac ?1 Jd ?2 3d ?3 5c\n
Qc ?2 Qd ?3 3h ?4 2s\n
Js ?3 0s ?4 9c ?5 6d\n
7h ?4 3h ?5 2h ?0 Ah\n
Kd ?5 Qh ?0 Js ?1 As\n

The program arguments needed are first the input file, second the number of Monte Carlo simulations you would like run. If nothing is entered for the number of simulations
the program defaults to 10,000.

