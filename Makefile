OS := $(shell uname)

ifeq ($(OS), Linux)
include /usr/local/etc/PcapPlusPlus.mk
endif
ifeq ($(OS), Darwin)
include /opt/homebrew/Cellar/pcapplusplus/22.11/etc/PcapPlusPlus.mk
endif

# All Target
all:
	g++ $(PCAPPP_BUILD_FLAGS) $(PCAPPP_INCLUDES) -c -o main.o main.cpp
	g++ $(PCAPPP_LIBS_DIR) -o pcapng_to_pcap main.o $(PCAPPP_LIBS)

# Clean Target
clean:
	rm main.o
	rm pcapng_to_pcap
