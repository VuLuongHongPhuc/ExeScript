# Encapsulate script in executable file

# 1. Description
This project is use to encapsulate the script in an executable file. It hide your script text with a simple random ascii table.

- ascii_table : create a random ascii table. This table has to be place in ascii.h : encoder and decoder folder
- encoder : create your hidefile.cpp with your script file inside.
- decoder : create executable file with your script inside.

If you don't use the random ascii table, your script command can be read easily by opening the executable in text.<br>
The project is cross-platform, it works for Windows and Linux.

# 2. How to use
1. Put your script file in encoder\script\yoursciptfile
2. You can rebuild the exe with "make" or use the prebuild in "encoder\bin\convertfile.exe"
3. Move to "encoder\bin\" folder
4. Execute the command: ./convertfile.exe -f:yourscripfile
5. Copy the ouput file "hidefile.cpp" from "encoder\ouput\" into "decoder\src\" folder
6. Move to decoder folder and build the executable with "make"
7. Your script is now encapsulated in the executable named "LaunchThisScript" in "decoder\bin\" folder