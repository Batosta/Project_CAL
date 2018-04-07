################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Client.cpp \
../src/Functions.cpp \
../src/Rideshare.cpp \
../src/Travel.cpp \
../src/connection.cpp \
../src/graphviewer.cpp \
../src/main.cpp \
../src/menu.cpp 

OBJS += \
./src/Client.o \
./src/Functions.o \
./src/Rideshare.o \
./src/Travel.o \
./src/connection.o \
./src/graphviewer.o \
./src/main.o \
./src/menu.o 

CPP_DEPS += \
./src/Client.d \
./src/Functions.d \
./src/Rideshare.d \
./src/Travel.d \
./src/connection.d \
./src/graphviewer.d \
./src/main.d \
./src/menu.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1z -O0 -g3 -Wall -c -fmessage-length=0 -Wno-attributes -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


