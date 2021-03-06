#pragma once

#include "Common/src/ValueTableCommon.hpp"

/// Implements the current value table. This table is currently active if data is logged
///  to the binary file or written into the Influx data base.
class ValueTable : public ValueTableCommon
{
public:
    /// Constructs the value table of the current version. Files will be written according
    ///  this table. The InfluxDB is also written accroding this table version.
    /// \param[in] enableLog if set to true, more information is written to
    ///   the STDOUT.
    ValueTable(bool enableLog);
    virtual ~ValueTable();

    uint32_t getFileVersion() const override;
    uint32_t getSizeOfHeader() const override;

private:
    void initValueTable() override;

    const uint32_t FILE_Version = 5;          ///< Current file version
    const uint32_t FILE_SizeOfHeader = 3;     ///< Current header size in 32 bit blocks.
};
