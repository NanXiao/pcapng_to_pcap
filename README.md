# pcapng_to_pcap

[tshark](https://www.wireshark.org/docs/man-pages/tshark.html) can convert `pcapng` file in which all packets were captured through one interface to `pcap` file. If the `pcapng` file contains multiple interfaces information, `tshark` will abort in the middle of conversion:

```
$ tshark -F pcap -r in.pcap -w out.pcap
tshark: Frame 99 of file "in.pcap" has a network type that differs from the network type of earlier packets, which isn't supported in a "Wireshark/tcpdump/... - pcap" file.
```

`pcapng_to_pcap` discards all interfaces information from `pcapng` file and save the packets as if they had been captured through Ethernet.

## Dependency
Please install [PcapPlusPlus](https://github.com/seladb/PcapPlusPlus) before building `pcapng_to_pcap`. E.g., on `macOS`:

```
$ brew install pcapplusplus
```

## Usage
Clone and run `make`, then:  
```
$ pcapng_to_pcap in.pcapng out.pcap
```
