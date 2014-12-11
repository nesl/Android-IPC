ashmemIPC
=========

Using /dev/ashmem as an alternative for binder IPC in android

The following are details of the projects present in this directory.

1.FibonacciCommon - Library project, containing definitions of request and response structures.
2.FibonacciService - Android service responsible for creating memory file in /dev/ashmem and writing data to memoryfile.
3.FibonacciActivity - Android application which binds to FibonacciService and then reads data entered by service in /dev/ashmem.

How to run:

Please copy the acc_data.json on to the device in sdcard directory.

1. Import all the projects in eclipse.
2. Install FibonacciService first on your device.
3. Install FibonacciActivity on to the device.
4. Press "Start Sending Data" button to read data from a file on sdcard, do not enter any input in text box in UI.
5. Keep pressing "Start Sending Data" button to keep reading data from file.
6. Press "Stop sending Data" button to close all files and stop reading any more data. After this the "Start Sending Data" button can be pressed again.

