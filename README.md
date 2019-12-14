# BusNavigation
- install vcpkg:  
+ git clone 
+ cd
+ ./bootstrap
- install json-c:  
+ ./vcpkg install json-c
+ ./vcpkg integrate install
- run gcc:  
+ gcc -c ${file} -Wall -I ${path} -ljson-c -o output 
