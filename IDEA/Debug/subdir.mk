################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../IDEA.cpp \
../IDEA_operations.cpp \
../IDEA_rounds.cpp \
../IDEA_shell.cpp \
../main.cpp \
../mastershell.cpp \
../networkinterfacefrontendbase.cpp \
../specialkernel.cpp 

OBJS += \
./IDEA.o \
./IDEA_operations.o \
./IDEA_rounds.o \
./IDEA_shell.o \
./main.o \
./mastershell.o \
./networkinterfacefrontendbase.o \
./specialkernel.o 

CPP_DEPS += \
./IDEA.d \
./IDEA_operations.d \
./IDEA_rounds.d \
./IDEA_shell.d \
./main.d \
./mastershell.d \
./networkinterfacefrontendbase.d \
./specialkernel.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/local/systemc/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


