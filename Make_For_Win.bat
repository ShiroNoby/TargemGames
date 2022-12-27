mkdir temp

cd temp
g++ -c CString.o ..\src\CString.cpp
g++ -c main.o ..\src\main.cpp
cd ..

g++ -o resoult temp\CString.o temp\main.o
rd /s /q temp