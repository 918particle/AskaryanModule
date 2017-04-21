include Makefile.arch

SYSINCLUDES	=
SYSLIBS =

DLLSUF = ${DllSuf}
OBJSUF = ${ObjSuf}
SRCSUF = ${SrcSuf}

#Toggles the FFT functions on and off
#USE_FFT_TOOLS=1

ifdef USE_FFT_TOOLS
FFTLIBS = -lRootFftwWrapper -lfftw3 -lMathMore -lgsl 
FFTFLAG = -DUSE_FFT_TOOLS
else
FFTLIBS =
FFTFLAG =
endif

ifdef ARA_UTIL_INSTALL_DIR
	ARA_UTIL_LIB_DIR=${ARA_UTIL_INSTALL_DIR}/lib
	ARA_UTIL_INC_DIR=${ARA_UTIL_INSTALL_DIR}/include
	CXXFLAGS += -DARA_UTIL_EXISTS
	DICT_FLAGS = -DARA_UTIL_EXISTS
	LD_ARA_UTIL=-L${ARA_UTIL_LIB_DIR} -lAraEvent -lsqlite3
	INC_ARA_UTIL=-I${ARA_UTIL_INC_DIR}
	ARA_ROOT_HEADERS=RawIcrrStationHeader.h RawIcrrStationEvent.h  RawAraStationEvent.h  FullIcrrHkEvent.h  AraEventCalibrator.h IcrrTriggerMonitor.h IcrrHkData.h AraRawIcrrRFChannel.h AraAntennaInfo.h AraGeomTool.h  UsefulAraStationEvent.h UsefulIcrrStationEvent.h araIcrrStructures.h AtriEventHkData.h AtriSensorHkData.h araAtriStructures.h araSoft.h araIcrrDefines.h RawAtriSimpleStationEvent.h RawAtriStationBlock.h RawAraGenericHeader.h RawAtriStationEvent.h UsefulAtriStationEvent.h  AraStationInfo.h 
endif
