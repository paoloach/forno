#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/LCD.c src/user.c src/configuration_bits.c src/main.c src/system.c src/ADC.c src/TempConverter.c src/DS18B20.c src/RS232.c src/PWM.c src/webServer.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/LCD.p1 ${OBJECTDIR}/src/user.p1 ${OBJECTDIR}/src/configuration_bits.p1 ${OBJECTDIR}/src/main.p1 ${OBJECTDIR}/src/system.p1 ${OBJECTDIR}/src/ADC.p1 ${OBJECTDIR}/src/TempConverter.p1 ${OBJECTDIR}/src/DS18B20.p1 ${OBJECTDIR}/src/RS232.p1 ${OBJECTDIR}/src/PWM.p1 ${OBJECTDIR}/src/webServer.p1
POSSIBLE_DEPFILES=${OBJECTDIR}/src/LCD.p1.d ${OBJECTDIR}/src/user.p1.d ${OBJECTDIR}/src/configuration_bits.p1.d ${OBJECTDIR}/src/main.p1.d ${OBJECTDIR}/src/system.p1.d ${OBJECTDIR}/src/ADC.p1.d ${OBJECTDIR}/src/TempConverter.p1.d ${OBJECTDIR}/src/DS18B20.p1.d ${OBJECTDIR}/src/RS232.p1.d ${OBJECTDIR}/src/PWM.p1.d ${OBJECTDIR}/src/webServer.p1.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/LCD.p1 ${OBJECTDIR}/src/user.p1 ${OBJECTDIR}/src/configuration_bits.p1 ${OBJECTDIR}/src/main.p1 ${OBJECTDIR}/src/system.p1 ${OBJECTDIR}/src/ADC.p1 ${OBJECTDIR}/src/TempConverter.p1 ${OBJECTDIR}/src/DS18B20.p1 ${OBJECTDIR}/src/RS232.p1 ${OBJECTDIR}/src/PWM.p1 ${OBJECTDIR}/src/webServer.p1

# Source Files
SOURCEFILES=src/LCD.c src/user.c src/configuration_bits.c src/main.c src/system.c src/ADC.c src/TempConverter.c src/DS18B20.c src/RS232.c src/PWM.c src/webServer.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=18F4620
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/LCD.p1: src/LCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/LCD.p1.d 
	@${RM} ${OBJECTDIR}/src/LCD.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/LCD.p1  src/LCD.c 
	@-${MV} ${OBJECTDIR}/src/LCD.d ${OBJECTDIR}/src/LCD.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/LCD.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/user.p1: src/user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/user.p1.d 
	@${RM} ${OBJECTDIR}/src/user.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/user.p1  src/user.c 
	@-${MV} ${OBJECTDIR}/src/user.d ${OBJECTDIR}/src/user.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/user.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/configuration_bits.p1: src/configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/configuration_bits.p1.d 
	@${RM} ${OBJECTDIR}/src/configuration_bits.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/configuration_bits.p1  src/configuration_bits.c 
	@-${MV} ${OBJECTDIR}/src/configuration_bits.d ${OBJECTDIR}/src/configuration_bits.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/configuration_bits.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/main.p1: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.p1.d 
	@${RM} ${OBJECTDIR}/src/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/main.p1  src/main.c 
	@-${MV} ${OBJECTDIR}/src/main.d ${OBJECTDIR}/src/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/system.p1: src/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.p1.d 
	@${RM} ${OBJECTDIR}/src/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/system.p1  src/system.c 
	@-${MV} ${OBJECTDIR}/src/system.d ${OBJECTDIR}/src/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ADC.p1: src/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/ADC.p1.d 
	@${RM} ${OBJECTDIR}/src/ADC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ADC.p1  src/ADC.c 
	@-${MV} ${OBJECTDIR}/src/ADC.d ${OBJECTDIR}/src/ADC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ADC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/TempConverter.p1: src/TempConverter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/TempConverter.p1.d 
	@${RM} ${OBJECTDIR}/src/TempConverter.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/TempConverter.p1  src/TempConverter.c 
	@-${MV} ${OBJECTDIR}/src/TempConverter.d ${OBJECTDIR}/src/TempConverter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/TempConverter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/DS18B20.p1: src/DS18B20.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/DS18B20.p1.d 
	@${RM} ${OBJECTDIR}/src/DS18B20.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/DS18B20.p1  src/DS18B20.c 
	@-${MV} ${OBJECTDIR}/src/DS18B20.d ${OBJECTDIR}/src/DS18B20.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/DS18B20.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/RS232.p1: src/RS232.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/RS232.p1.d 
	@${RM} ${OBJECTDIR}/src/RS232.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/RS232.p1  src/RS232.c 
	@-${MV} ${OBJECTDIR}/src/RS232.d ${OBJECTDIR}/src/RS232.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/RS232.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/PWM.p1: src/PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/PWM.p1.d 
	@${RM} ${OBJECTDIR}/src/PWM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/PWM.p1  src/PWM.c 
	@-${MV} ${OBJECTDIR}/src/PWM.d ${OBJECTDIR}/src/PWM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/PWM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/webServer.p1: src/webServer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/webServer.p1.d 
	@${RM} ${OBJECTDIR}/src/webServer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/webServer.p1  src/webServer.c 
	@-${MV} ${OBJECTDIR}/src/webServer.d ${OBJECTDIR}/src/webServer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/webServer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
else
${OBJECTDIR}/src/LCD.p1: src/LCD.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/LCD.p1.d 
	@${RM} ${OBJECTDIR}/src/LCD.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/LCD.p1  src/LCD.c 
	@-${MV} ${OBJECTDIR}/src/LCD.d ${OBJECTDIR}/src/LCD.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/LCD.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/user.p1: src/user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/user.p1.d 
	@${RM} ${OBJECTDIR}/src/user.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/user.p1  src/user.c 
	@-${MV} ${OBJECTDIR}/src/user.d ${OBJECTDIR}/src/user.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/user.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/configuration_bits.p1: src/configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/configuration_bits.p1.d 
	@${RM} ${OBJECTDIR}/src/configuration_bits.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/configuration_bits.p1  src/configuration_bits.c 
	@-${MV} ${OBJECTDIR}/src/configuration_bits.d ${OBJECTDIR}/src/configuration_bits.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/configuration_bits.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/main.p1: src/main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/main.p1.d 
	@${RM} ${OBJECTDIR}/src/main.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/main.p1  src/main.c 
	@-${MV} ${OBJECTDIR}/src/main.d ${OBJECTDIR}/src/main.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/main.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/system.p1: src/system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/system.p1.d 
	@${RM} ${OBJECTDIR}/src/system.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/system.p1  src/system.c 
	@-${MV} ${OBJECTDIR}/src/system.d ${OBJECTDIR}/src/system.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/system.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/ADC.p1: src/ADC.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/ADC.p1.d 
	@${RM} ${OBJECTDIR}/src/ADC.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/ADC.p1  src/ADC.c 
	@-${MV} ${OBJECTDIR}/src/ADC.d ${OBJECTDIR}/src/ADC.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/ADC.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/TempConverter.p1: src/TempConverter.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/TempConverter.p1.d 
	@${RM} ${OBJECTDIR}/src/TempConverter.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/TempConverter.p1  src/TempConverter.c 
	@-${MV} ${OBJECTDIR}/src/TempConverter.d ${OBJECTDIR}/src/TempConverter.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/TempConverter.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/DS18B20.p1: src/DS18B20.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/DS18B20.p1.d 
	@${RM} ${OBJECTDIR}/src/DS18B20.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/DS18B20.p1  src/DS18B20.c 
	@-${MV} ${OBJECTDIR}/src/DS18B20.d ${OBJECTDIR}/src/DS18B20.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/DS18B20.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/RS232.p1: src/RS232.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/RS232.p1.d 
	@${RM} ${OBJECTDIR}/src/RS232.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/RS232.p1  src/RS232.c 
	@-${MV} ${OBJECTDIR}/src/RS232.d ${OBJECTDIR}/src/RS232.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/RS232.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/PWM.p1: src/PWM.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/PWM.p1.d 
	@${RM} ${OBJECTDIR}/src/PWM.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/PWM.p1  src/PWM.c 
	@-${MV} ${OBJECTDIR}/src/PWM.d ${OBJECTDIR}/src/PWM.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/PWM.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
${OBJECTDIR}/src/webServer.p1: src/webServer.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src" 
	@${RM} ${OBJECTDIR}/src/webServer.p1.d 
	@${RM} ${OBJECTDIR}/src/webServer.p1 
	${MP_CC} --pass1 $(MP_EXTRA_CC_PRE) --chip=$(MP_PROCESSOR_OPTION) -Q -G  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    -o${OBJECTDIR}/src/webServer.p1  src/webServer.c 
	@-${MV} ${OBJECTDIR}/src/webServer.d ${OBJECTDIR}/src/webServer.p1.d 
	@${FIXDEPS} ${OBJECTDIR}/src/webServer.p1.d $(SILENT) -rsi ${MP_CC_DIR}../  
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.${IMAGE_TYPE}.map  -D__DEBUG=1 --debugger=none  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"       --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	@${RM} dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.${IMAGE_TYPE}.hex 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE) --chip=$(MP_PROCESSOR_OPTION) -G -mdist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.${IMAGE_TYPE}.map  --double=24 --float=24 --emi=wordwrite --opt=default,+asm,+asmfile,+speed,-space,-debug --addrqual=ignore --mode=free -D_XTAL_FREQ=12000000 -P -N255 -I"../../../../../opt/microchip/xc8/v1.35/include" --warn=0 --asmlist --summary=default,-psect,+class,+mem,-hex,+file --output=default,-inhx032 --runtime=default,+clear,+init,-keep,-no_startup,-download,+config,+clib,+plib --output=+mcof,-elf:multilocs --stack=compiled:auto:auto:auto "--errformat=%f:%l: error: (%n) %s" "--warnformat=%f:%l: warning: (%n) %s" "--msgformat=%f:%l: advisory: (%n) %s"    --memorysummary dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml -odist/${CND_CONF}/${IMAGE_TYPE}/MPLAB.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}     
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/default
	${RM} -r dist/default

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
