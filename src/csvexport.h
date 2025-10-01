#ifndef CSVEXPORT_H
#define CSVEXPORT_H

#include <stdint.h>
#include "usbpacket.h"
#include "usbmodel.h"

class CSVExport {
	FILE *fh;
	USBModel& model;
	void writeGlobalHeader(void);
	void writePacket(USBPacket& packet);
	void writeItem(const USBItem* item);

public:
	CSVExport(const char* filename, USBModel& _model);
	~CSVExport(void);
	void write(void);
};

#endif /* CSVEXPORT_H */
