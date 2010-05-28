################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../W.cpp \
../calcBuddies.cpp \
../calcDerivatives.cpp \
../dW.cpp \
../main.cpp \
../marchTime.cpp \
../plotShock.cpp \
../setupSim.cpp 

OBJS += \
./W.o \
./calcBuddies.o \
./calcDerivatives.o \
./dW.o \
./main.o \
./marchTime.o \
./plotShock.o \
./setupSim.o 

CPP_DEPS += \
./W.d \
./calcBuddies.d \
./calcDerivatives.d \
./dW.d \
./main.d \
./marchTime.d \
./plotShock.d \
./setupSim.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


