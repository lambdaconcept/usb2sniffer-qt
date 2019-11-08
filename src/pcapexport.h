#ifndef PCAPEXPORT_H
#define PCAPEXPORT_H

#include <stdint.h>
#include "usbpacket.h"
#include "usbmodel.h"

extern "C" {
	typedef struct pcap_hdr_s {
    	uint32_t magic_number; /* magic number */
    	uint16_t version_major; /* major version number */
    	uint16_t version_minor; /* minor version number */
    	int32_t  thiszone; /* GMT to local correction */
    	uint32_t sigfigs; /* accuracy of timestamps */
    	uint32_t snaplen; /* max length of captured packets, in octets */
    	uint32_t network; /* data link type */
	} __attribute__((packed)) pcap_hdr_t;

	typedef struct pcaprec_hdr_s {
    	uint32_t ts_sec; /* timestamp seconds */
    	uint32_t ts_usec; /* timestamp microseconds */
    	uint32_t incl_len; /* number of octets of packet saved in file */
    	uint32_t orig_len; /* actual length of packet */
	} __attribute__((packed)) pcaprec_hdr_t;
}

class PcapExport {
	FILE *fh;
	USBModel& model;
	void writeGlobalHeader(void);
	void writePacket(USBPacket& packet);

public:
	PcapExport(const char* filename, USBModel& _model);
	~PcapExport(void);
	void write(void);
};

#endif /* PCAPEXPORT_H */