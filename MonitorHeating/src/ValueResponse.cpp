#include "ValueResponse.hpp"

#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>
#include <assert.h>

#include "Common/src/ValueTable.hpp"

float conversionFunctionDivisor(const uint32_t value, const uint32_t divisor)
{
    return (static_cast<float>(value) / static_cast<float>(divisor));
}

bool conversionFunctionBool(const uint32_t value)
{
    if (0 == value) {
        return false;
    } else {
        return true;
    }
}

// ----------------------------------------------------------------------------------

ValueResponse::ValueResponse(RecDataStoragePtr receiveDataPtr, std::time_t currentUnixTime)
    : m_responsePtr(receiveDataPtr)
    , m_currentUnixTime(currentUnixTime)
{
    std::cout << "Creation Time: " << std::asctime(std::localtime(&currentUnixTime)) << currentUnixTime << " seconds since the Epoch\n";
    std::cout << "Hex time: 0x" << std::hex << m_currentUnixTime << std::dec << " seconds since the Epoch\n";

    if (false == doesFileExist()) {
        std::ofstream wf(fileNameFromDate().c_str(), std::ios::out | std::ios::binary | std::ios_base::app);
        if(!wf) {
            std::cout << "Cannot open file!" << std::endl;
        } else {
            // Add header to the buffer
            std::cout << "Create header of file: '" << fileNameFromDate() << "'" << std::endl;
            writeHeaderVersion01(wf);
            wf.close();
        }
    }
}

uint32_t ValueResponse::getNumberOfEntries() const
{
    return sizeof(ValueTableDecode) / sizeof(ValueEntry);
}

void ValueResponse::decode()
{
//    {  10, /*ID_WEB_Temperatur_TVL*/        "Vorlauftemperatur Heizkreis",                                         10, "°C" },

    std::cout << "xxx ------------" << std::endl;
    uint32_t val = m_responsePtr->getDataField(11);
    printf("%s\n", ValueTableDecode[10].description.c_str());
    printf("10 val: 0x%.8x\n", val);
    printf("10 val: %3.1f\n", static_cast<float>(val) / 10);
    std::cout << "xxx ------------" << std::endl;
    for (uint32_t cnt = 0; cnt < getNumberOfEntries(); cnt++) {
        printf("%s\n", ValueTableDecode[cnt].description.c_str());

//               printf("%s = %3.2f %s\n", ValueTableDecode[cnt].description.c_str(),
//               ValueTableDecode[cnt].fn(m_responsePtr->getDataField(ValueTableDecode[cnt].cmdId + 1), ValueTableDecode[cnt].conversionDivisor),
//               ValueTableDecode[cnt].unit.c_str());
    }
}

// struct tm {
//    int tm_sec;   // seconds of minutes from 0 to 61
//    int tm_min;   // minutes of hour from 0 to 59
//    int tm_hour;  // hours of day from 0 to 24
//    int tm_mday;  // day of month from 1 to 31
//    int tm_mon;   // month of year from 0 to 11
//    int tm_year;  // year since 1900
//    int tm_wday;  // days since sunday
//    int tm_yday;  // days since January 1st
//    int tm_isdst; // hours of daylight savings time
// }


char ValueResponse::serialize()
{
    std::string dateString;

    std::cout << "getNumberOfEntries: " << getNumberOfEntries() << std::endl;

    std::ofstream wf(fileNameFromDate().c_str(), std::ios::out | std::ios::binary | std::ios_base::app);
    if(!wf) {
        std::cout << "Cannot open file!" << std::endl;
        return 1;
    }

    // Copy the unix time to the binary file
    addUnixTimeToBuffer(wf, m_currentUnixTime);

    // Copy the heating data to the binary file
    for (uint32_t cnt = 0; cnt < getNumberOfEntries(); cnt++) {
        uint32_t value = m_responsePtr->getDataField(ValueTableDecode[cnt].cmdId + 1);
        wf.write(reinterpret_cast<char*>(&value), sizeof(uint32_t));
    }
    wf.close();
    return 0;
}

void ValueResponse::addUnixTimeToBuffer(std::ofstream& wf, std::time_t unixTime)
{
    if (8 == sizeof(std::time_t)) {
        wf.write(reinterpret_cast<char*>(&unixTime), sizeof(std::time_t));
    } else if (4 == sizeof(std::time_t)) {
        uint32_t dummy = 0;
        wf.write(reinterpret_cast<char*>(&unixTime), sizeof(std::time_t));
        wf.write(reinterpret_cast<char*>(&dummy), 4);
    } else {
        assert(0);
    }
}

std::string ValueResponse::fileNameFromDate()
{
    struct tm* timeInfo;
    std::stringstream fileNameStream;

    timeInfo = std::localtime(&m_currentUnixTime);

    fileNameStream << std::setw(4) << std::setfill('0') << 1900 + timeInfo->tm_year << "_"
                   << std::setw(2) << std::setfill('0') << 1 + timeInfo->tm_mon << "_"
                   << std::setw(2) << std::setfill('0') << timeInfo->tm_mday << ".dat";
    std::string fileName = fileNameStream.str();
    return fileName;
}

bool ValueResponse::doesFileExist()
{
    std::ifstream infile(fileNameFromDate().c_str());
    return infile.good();
}

void ValueResponse::writeHeaderVersion01(std::ofstream& wf)
{
    typedef struct {
        uint32_t Version;
        uint32_t SizeOfHeader;
        uint32_t NrDataEntries;
    }HeaderVersion01;

    HeaderVersion01 header;

    header.Version = 1;
    header.SizeOfHeader = 3;
    header.NrDataEntries = 69;

    wf.write(reinterpret_cast<char*>(&header.Version), 4);
    wf.write(reinterpret_cast<char*>(&header.SizeOfHeader), 4);
    wf.write(reinterpret_cast<char*>(&header.NrDataEntries), 4);
}