#include <iostream>
#include <PcapFileDevice.h>

int
main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cerr << "Usage: ./pcapng_to_pcap in.pcapng out.pcap\n";
		return EXIT_FAILURE;
	}

	pcpp::PcapNgFileReaderDevice pcapngReader(argv[1]);
	if (!pcapngReader.open()) {
		std::cerr << "Open " << argv[1] << " failed\n";
		return EXIT_FAILURE;
	}

	pcap_t *pcapHandle = pcap_open_dead(DLT_EN10MB, 262144);
	if (pcapHandle == NULL) {
		std::cerr << "Out of memory\n";
		return EXIT_FAILURE;
	}

	pcap_dumper_t *pcapDumper = pcap_dump_open(pcapHandle, argv[2]);
	if (pcapDumper == NULL) {
		std::cerr << "pcap_dump_open error: " << pcap_geterr(pcapHandle) << '\n';
		return EXIT_FAILURE;
	}

	pcpp::RawPacket rawPacket;

	while (pcapngReader.getNextPacket(rawPacket)) {
		pcap_pkthdr pktHdr;
		pktHdr.ts = rawPacket.getPacketTimeStamp();
		pktHdr.caplen = rawPacket.getRawDataLen();
		pktHdr.len = rawPacket.getFrameLength();
		pcap_dump((u_char *)pcapDumper, &pktHdr, rawPacket.getRawData());
	}
	
	pcap_stat stats;
	pcapngReader.getStatistics(stats);
	std::cout << "Read "<<  stats.ps_recv <<" packets successfully and " << stats.ps_drop << " packets could not be read\n";

	pcap_dump_close(pcapDumper);
	pcap_close(pcapHandle);
}
