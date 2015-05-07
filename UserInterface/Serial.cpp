#include "Serial.h"

HANDLE Serial::openSerial()
{

	//PortChat::Main();
	HANDLE m_hCommPort = ::CreateFile((LPCWSTR)COMPORT,
		GENERIC_READ,  // access ( read and write)
		0,                           // (share) 0:cannot share the COM port
		0,                           // security  (None)
		OPEN_EXISTING,               // creation : open_existing
		FILE_ATTRIBUTE_NORMAL,		//FILE_FLAG_OVERLAPPED,        // we want overlapped operation
		0                            // no templates file for COM port...
		);

	if (m_hCommPort != INVALID_HANDLE_VALUE){
        qDebug("Successfully opened %s\n", COMPORT);
	}
	else {
        qDebug("Error opening %s: error num : %d\n", COMPORT, GetLastError());
	}

	DCB dcb = { 0 };
	dcb.DCBlength = sizeof(DCB);

	if (!::GetCommState(m_hCommPort, &dcb))
	{
        qDebug("CSerialCommHelper : Failed to Get Comm State Reason: %d\n", GetLastError());
        //getchar();
		return NULL;
	}

    qDebug("Current Settings: \nBaud Rate %d;	Parity %d; Byte Size %d; Stop Bits %d\n", dcb.BaudRate, dcb.Parity, dcb.ByteSize, dcb.StopBits);

	dcb.BaudRate = 115200;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = ONESTOPBIT;


	if (!::SetCommState(m_hCommPort, &dcb))
	{
        qDebug("CSerialCommHelper : Failed to Set Comm State Reason: %d\n", GetLastError());
        //getchar();
		return NULL;
	}
    qDebug("Current Settings: \nBaud Rate %d;	Parity %d; Byte Size %d; Stop Bits %d\n", dcb.BaudRate, dcb.Parity, dcb.ByteSize, dcb.StopBits);

	OVERLAPPED ov;
	memset(&ov, 0, sizeof(ov));
	ov.hEvent = CreateEvent(0, true, 0, 0);

	SetCommMask(m_hCommPort, EV_RXCHAR);

	

	return m_hCommPort;
}

int Serial::getData(HANDLE port)
{
	DWORD dwEvtMask;
	DWORD bytesRead = 0;
	char buffer[50] = { 0 };

	static char lineBuffer[50] = { 0 };
	static int index = 0;

	int bufIndex = 0;

	WaitCommEvent(port, &dwEvtMask, NULL);
	ReadFile(port, &buffer, 30, &bytesRead, NULL);
	for (int i = 0; i < bytesRead; i++){
		if (buffer[i] == '\n'){ //we have polled a finished line
			//copy digits of the line into the buffer
			memcpy(&lineBuffer[index], &buffer[bufIndex], sizeof(BYTE)*(i + 1 - bufIndex));
			index += (i + 1 - bufIndex);
            parseBuffer(lineBuffer);
			bufIndex = i + 1;
			index = 0;
            qDebug("X Angle: %.2f\tY Angle: %.2f\t Z Angle: %.2f\n", xangle, yangle, zangle);
            qDebug("Window X: %d\t Window Y: %d\n", windowX, windowY);
			updateWindow();
		}
	}
	memcpy(&lineBuffer[index], &buffer[bufIndex], sizeof(BYTE)*(bytesRead - bufIndex));
	index += bytesRead - bufIndex;

	return 0;
}

void Serial::parseBuffer(char * buffer){
    try {
        QString bufferTxt = buffer;
        QStringList rows = bufferTxt.split(",\n");
        QStringList columns;

        foreach (QString row, rows){
            columns += row.split(",");
        }

        xangle = columns.at(0).toInt();
        yangle = columns.at(1).toInt();
        zangle = columns.at(2).toInt();
	}
    // Necessary for when the buffer does not line up perfectly on a full line, will create errors
    // if not full line.
    catch (...) {
	}
}

void Serial::updateWindow(){
	if (xangle > 25){
		windowX += (int)(4 * PANRATE);
	}
	else if (xangle > 15){
		windowX += (int)(2 * PANRATE);
	}
	else if (xangle > 5){
		windowX += (int)(1 * PANRATE);
	}
	else if (xangle < -25){
		windowX -= (int)(4 * PANRATE);
	}
	else if (xangle < -15){
		windowX -= (int)(2 * PANRATE);
	}
	else if (xangle < -5){
		windowX -= (int)(1 * PANRATE);
	}

	if (yangle > 25){
		windowY += (int)(4 * PANRATE);
	}
	else if (yangle > 15){
		windowY += (int)(2 * PANRATE);
	}
	else if (yangle > 5){
		windowY += (int)(1 * PANRATE);;
	}
	else if (yangle < -25){
		windowY -= (int)(4 * PANRATE);
	}
	else if (yangle < -15){
		windowY -= (int)(2 * PANRATE);
	}
	else if (yangle < -5){
		windowY -= (int)(1 * PANRATE);
	}

	if (windowX > WINXSIZE){
		windowX = WINXSIZE;
	}
	else if (windowX < 0){
		windowX = 0;
	}

	if (windowY > WINYSIZE){
		windowY = WINYSIZE;
	}
	else if (windowY < 0){
		windowY = 0;
	}
}

int Serial::getx()
{
	return windowX;
}

int Serial::gety()
{
	return windowY;
}
