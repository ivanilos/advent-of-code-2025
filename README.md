# advent-of-code-2025
My codes for advent of code 2025

## Compiling

All codes were compiled using C++11

The following commands create a binary `part_two.exe` on the directory of the source
```
mingw32-gcc-4.9.2.exe -O2 -Wextra -Wall -std=c++11 -m32 -std=c++0x  -c part_two.cpp -o part_two.o
g++.exe  -o part_two.exe part_two.o  -O2 -m32 -Wl,--stack,268435456
```

## Running

Running is done by the input redirection mechanism.
```
part_two.exe < ../inputs/07/input.txt
```

Problem inputs are kept in a private repository as suggested by https://adventofcode.com/about#faq_copying.

I strongly dislike this as inputs are part of the problem and, sometimes, analysis of the input has proven to be helpful on solving the problem as the input was more specific than the statement conveyed, e.g., part 2 of https://adventofcode.com/2020/day/14. In some previous years I did not hide my inputs but I decided to do so this year. 
