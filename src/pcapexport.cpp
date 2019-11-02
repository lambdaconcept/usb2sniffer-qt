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

    auto& aggregator = model.getAggregator();
    for (int i = 0; i < aggregator.count(); i++) {
        writePacket(*aggregator.value(i));
    }
}

void PCapExport::writeGlobalHeader(void)
{
    pcap_hdr_t header;

    header.magic_number = 0xA1B23C4D;
    header.version_major = 2;
    header.version_minor = 4;
    header.thiszone = 0 /* Assume UTC */;
    header.sigfigs = 0;
    header.snaplen = 2048;
    header.network = DLT_USB_2_0;

    fwrite(&header, sizeof(pcap_hdr_t), 1, fh);
}

void PCapExport::writePacket(USBPacket& packet)
{
    auto packetData = packet.recordData().second;

    pcaprec_hdr_t header;

    header.ts_sec = packet.m_Timestamp / 1000000000;
    header.ts_usec = packet.m_Timestamp % 1000000000;
    header.incl_len = packetData.size();
    header.orig_len = packetData.size();

    fwrite(&header, sizeof(pcaprec_hdr_t), 1, fh);
    fwrite(packetData.data(), packetData.size(), 1, fh);
}
