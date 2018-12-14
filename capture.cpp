#include "capture.h"
#include "usbaggregator.h"

void CaptureThread::run()
{
    USBAggregator aggregator;
    USBModel *usbModel = new USBModel(aggregator.getRoot());

    for (int i = 0; i < 5; ++i) {
        aggregator.append(new USBPacket(i, QByteArray::fromHex("a50f18")));

        sleep(1); // FIXME
    }
    aggregator.append(new USBPacket(10, QByteArray::fromHex("d2")));

    emit resultReady(usbModel);
}
