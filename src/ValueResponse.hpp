#pragma once

#include <ctime>

#include "ReceiveDataBuffer.hpp"


typedef struct
{
    uint32_t cmdId;
    // identifier is not used
    std::string description;
    uint32_t conversionDivisor;
    std::string unit;
} ValueEntry;




/// \brief Class to process the value response (cmd 3004).
/// It serializes the data and stores it to a binary files named with the current date.
class ValueResponse
{
public:
    /// Creates Object and writes a data file if the file does not yet exist. The header is
    /// written to the data file.
    /// \param[in] receiveDataPtr pointer to the received TCP raw data.
    /// \param[in] currentUnixTime time of the data sample in seconds since January, 1st 1970.
    ValueResponse(RecDataStoragePtr receiveDataPtr, std::time_t currentUnixTime);

    /// Returns the number data entries in the current data set.
    /// \return returns the number of data entries in a single data sample
    uint32_t getNumberOfEntries() const;

    /// Decodes the current data sample and prints it to the command line (No yet finished)
    void decode();

    /// Serializes the current data and stores it to a binary file. There is one file created per day.
    /// \return 0 if the sample is successfully serialized. Not 0 if there is an error.
    char serialize();

private:
    /// Add the current Unix time in seconds since January, 1st 1970 to the data file.
    ///  Use 8 bytes independent on the HW/Compiler.
    /// \param[in] wf: Reference to the file stream.
    /// \param[in] unixTime: Unix time to be written to the file.
    void addUnixTimeToBuffer(std::ofstream& wf, std::time_t unixTime);

    /// Creates a file name from the given date
    /// \returns the file name from the current date in the format yyyy_mm_dd.dat
    std::string fileNameFromDate();

    /// Check if the file for today already exist
    /// \return true, if the file already exists
    bool doesFileExist();

    /// Writes the header version 1 to the file.
    /// Header:
    ///   Version (32bit)
    ///   Size of header (32bit), in 32 bit units, currently 3
    ///   Number of data entries (32bit), currently 69
    /// A data entry consists of 64 time in Unix format, followed by the 69 32bit data values
    /// \param[in] wf: Reference to the file stream, were the header is written to.
    void writeHeaderVersion01(std::ofstream& wf);

    /// Pointer to the response received on the TCP connection to the command 3004
    RecDataStoragePtr m_responsePtr;

    /// Time of the current sample in Unix time.
    std::time_t m_currentUnixTime;
};


#if 0
// Command Values 3004

//typedef float (* ConversionFunctionDivisor)(const uint32_t value, const uint32_t divisor);
//typedef bool (* ConversionFunctionBool)(const uint32_t value);


//float conversionFunctionDivisor(const uint32_t value, const uint32_t divisor);
//bool conversionFunctionBool(const uint32_t value);



//typedef union
//{
//    ConversionFunctionDivisor convFuncDivisor;
//    ConversionFunctionBool convFuncBool;
//} ConversionFunctions;

#endif