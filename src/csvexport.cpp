#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "csvexport.h"

CSVExport::CSVExport(const char* filename, USBModel& _model) : model(_model)
{
    fh = fopen(filename, "w");
    assert(fh);
}

CSVExport::~CSVExport(void)
{
    fclose(fh);
}

void CSVExport::write(void)
{
    const USBAggregator& aggregator = model.getAggregator();
    USBItem* root = aggregator.getRoot();
    USBItem* node = nullptr;

    writeGlobalHeader();

    /* This writes all USBPacket flat, without hierarchy

    for (int i = 0; i < aggregator.count(); i++) {
        writePacket(*aggregator.value(i));
    }
    */

    /* This writes the USBRecord as seen in the tree view.
    Only top level entries are written (USBTransaction, USBGroup).
    */
    for (int i=0; i < root->childCount(); i++) {
        node = root->child(i);
        writeItem(node);
    }
}

void CSVExport::writeGlobalHeader(void)
{
    fprintf(fh, "Name,Timestamp,Device,Endpoint,Status,Length,Summary\n");
}

void CSVExport::writePacket(USBPacket& packet)
{
    for (int i = 0; i < 7; i++) {
        fprintf(fh, "%s,", packet.data(i).toString().toUtf8().constData());
    }
    fprintf(fh, "\n");
}

void CSVExport::writeItem(const USBItem* item)
{
    if (!item) {
        return;
    }

    for (int i = 0; i < 7; i++) {
        fprintf(fh, "%s,", item->data(i).toString().toUtf8().constData());
    }
    fprintf(fh, "\n");
}
