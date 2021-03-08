#
# COP 4531 Project 1
# Wendy Slattery
# 3/1/20
#
# makefile
#

CC = g++ -std=c++11 -Wall -Wextra -I .

all: mergeSort.exe quickSort.exe bucketSort.exe radixSort.exe countingSort.exe heapSort.exe insertionSort.exe

mergeSort.exe: mergeSort.o 
	$(CC) -o mergeSort.exe mergeSort.o 

quickSort.exe: quickSort.o
	$(CC) -o quickSort.exe quickSort.o

bucketSort.exe: bucketSort.o
	$(CC) -o bucketSort.exe bucketSort.o

radixSort.exe: radixSort.o
	$(CC) -o radixSort.exe radixSort.o

countingSort.exe: countingSort.o
	$(CC) -o countingSort.exe countingSort.o

heapSort.exe: heapSort.o
	$(CC) -o heapSort.exe heapSort.o

insertionSort.exe: insertionSort.o
	$(CC) -o insertionSort.exe insertionSort.o

mergeSort.o: mergeSort.cpp  
	$(CC) -c mergeSort.cpp

quickSort.o: quickSort.cpp
	$(CC) -c quickSort.cpp

bucketSort.o: bucketSort.cpp
	$(CC) -c bucketSort.cpp

radixSort.o: radixSort.cpp
	$(CC) -c radixSort.cpp

countingSort.o: countingSort.cpp
	$(CC) -c countingSort.cpp

heapSort.o: heapSort.cpp
	$(CC) -c heapSort.cpp

insertionSort.o: insertionSort.cpp
	$(CC) -c insertionSort.cpp

clean: 
	rm -f *.txt *.o *~ 



