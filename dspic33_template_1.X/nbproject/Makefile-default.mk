#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-default.mk)" "nbproject/Makefile-local-default.mk"
include nbproject/Makefile-local-default.mk
endif

# Environment
MKDIR=gnumkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=default
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=cof
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_template_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=cof
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_template_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/configuration_bits.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/main.o ${OBJECTDIR}/system.o ${OBJECTDIR}/traps.o ${OBJECTDIR}/user.o
POSSIBLE_DEPFILES=${OBJECTDIR}/configuration_bits.o.d ${OBJECTDIR}/interrupts.o.d ${OBJECTDIR}/main.o.d ${OBJECTDIR}/system.o.d ${OBJECTDIR}/traps.o.d ${OBJECTDIR}/user.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/configuration_bits.o ${OBJECTDIR}/interrupts.o ${OBJECTDIR}/main.o ${OBJECTDIR}/system.o ${OBJECTDIR}/traps.o ${OBJECTDIR}/user.o


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
	${MAKE}  -f nbproject/Makefile-default.mk dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_template_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ64MC802
MP_LINKER_FILE_OPTION=,--script=p33FJ64MC802.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/configuration_bits.o: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/configuration_bits.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  configuration_bits.c  -o ${OBJECTDIR}/configuration_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configuration_bits.o.d"    -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=coff -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/configuration_bits.o.d" $(SILENT) 
	
${OBJECTDIR}/interrupts.o: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interrupts.c  -o ${OBJECTDIR}/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/interrupts.o.d"    -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=coff -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/interrupts.o.d" $(SILENT) 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"    -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=coff -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) 
	
${OBJECTDIR}/system.o: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/system.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  system.c  -o ${OBJECTDIR}/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/system.o.d"    -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=coff -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/system.o.d" $(SILENT) 
	
${OBJECTDIR}/traps.o: traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/traps.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  traps.c  -o ${OBJECTDIR}/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/traps.o.d"    -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=coff -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/traps.o.d" $(SILENT) 
	
${OBJECTDIR}/user.o: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/user.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  user.c  -o ${OBJECTDIR}/user.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/user.o.d"    -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=coff -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/user.o.d" $(SILENT) 
	
else
${OBJECTDIR}/configuration_bits.o: configuration_bits.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/configuration_bits.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  configuration_bits.c  -o ${OBJECTDIR}/configuration_bits.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/configuration_bits.o.d"    -g -omf=coff -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/configuration_bits.o.d" $(SILENT) 
	
${OBJECTDIR}/interrupts.o: interrupts.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/interrupts.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  interrupts.c  -o ${OBJECTDIR}/interrupts.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/interrupts.o.d"    -g -omf=coff -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/interrupts.o.d" $(SILENT) 
	
${OBJECTDIR}/main.o: main.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/main.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  main.c  -o ${OBJECTDIR}/main.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/main.o.d"    -g -omf=coff -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/main.o.d" $(SILENT) 
	
${OBJECTDIR}/system.o: system.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/system.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  system.c  -o ${OBJECTDIR}/system.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/system.o.d"    -g -omf=coff -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/system.o.d" $(SILENT) 
	
${OBJECTDIR}/traps.o: traps.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/traps.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  traps.c  -o ${OBJECTDIR}/traps.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/traps.o.d"    -g -omf=coff -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/traps.o.d" $(SILENT) 
	
${OBJECTDIR}/user.o: user.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} ${OBJECTDIR} 
	@${RM} ${OBJECTDIR}/user.o.d 
	${MP_CC} $(MP_EXTRA_CC_PRE)  user.c  -o ${OBJECTDIR}/user.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/user.o.d"    -g -omf=coff -O0 -msmart-io=1 -Wall -msfr-warn=off
	@${FIXDEPS} "${OBJECTDIR}/user.o.d" $(SILENT) 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_template_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_template_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)    -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=coff -Wl,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__ICD2RAM=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_template_1.X.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_template_1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)    -omf=coff -Wl,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,--report-mem$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}\\xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/dspic33_template_1.X.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=coff 
	
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

DEPFILES=$(shell mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
