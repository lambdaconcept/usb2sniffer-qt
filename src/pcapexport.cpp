#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "pcapexport.h"

/*
	Useful documentation:
	- https://wiki.wireshark.org/Development/LibpcapFileFormat
	- http://www.tcpdump.org/linktypes.html
*/

#define DLT_USB_2_0 288

PCapExport::PCapExport(const char* filename, USBModel& _model) : model(_model)
{
	fh = fopen(filename, "wb");
	assert(fh);
}

PCapExport::~PCapExport(void)
{
	fclose(fh);
}

void PCapExport::write(void)
{
	writeGlobalHeader();

	writePacketsFromItem(model.getRoot());
}

void PCapExport::writeGlobalHeader(void)
{
	pcap_hdr_t header;

    header.magic_number = 0xA1B2C3D4;
    header.version_major = 2;
    header.version_minor = 4;
    header.thiszone = 0 /* Assume UTC */;
    header.sigfigs = 0;
    header.snaplen = 2048;
    header.network = DLT_USB_2_0;

    fwrite(&header, sizeof(pcap_hdr_t), 1, fh);
}

void PCapExport::writePacketsFromItem(USBItem& item)
{
	for (int i = 0; i < item.childCount(); i++) {
		writePacketsFromItem(*item.child(i));
	}

	auto record = item.getRecord();
	if (record) {
		writePacketsFromRecord(*record);
	}
}

void PCapExport::writePacketsFromRecord(USBRecord& record)
{
	for (int i = 0; i < record.packetCount(); i++) {
		auto packet = record.packet(i);
		if (packet) {
			writePacket(*packet);
		}
	}
}

void PCapExport::writePacket(USBPacket& packet)
{
	auto packetData = packet.recordData().second;

	pcaprec_hdr_t header;

	header.ts_sec = packet.m_Timestamp / 1000000000;
	header.ts_usec = (packet.m_Timestamp / 1000) % 1000000;
	header.incl_len = packetData.size();
    header.orig_len = packetData.size();

    fwrite(&header, sizeof(pcaprec_hdr_t), 1, fh);
    fwrite(packetData.data(), packetData.size(), 1, fh);
}
