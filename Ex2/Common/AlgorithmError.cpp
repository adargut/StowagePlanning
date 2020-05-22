#include "AlgorithmError.h"

AlgorithmError::AlgorithmError(uint32_t errorCode) : m_errorCode(errorCode) {}

bool AlgorithmError::setBit(uint32_t bit)
{
    if (bit > 18)
    {
        return false;
    }
    m_errorCode |= uint32_t(1) << bit;
    return true;
}

bool AlgorithmError::getBit(uint32_t bit) const
{
    if (bit > 18)
    {
        return false;
    }
    return m_errorCode & uint32_t(1) << bit;
}

int AlgorithmError::getAndClear()
{
    uint32_t tmpErrorCode = m_errorCode;
    m_errorCode = 0;
    return tmpErrorCode;
}

AlgorithmError::errorCode AlgorithmError::getErrorCode() 
{
    return static_cast<AlgorithmError::errorCode>(m_errorCode);
}

string AlgorithmError::getErrorDescription(errorCode code)
{
    switch (code)
    {
    case ExceedingFloorValue:
        return "ExceedingFloorValue";
    case ExceedingXYValue:
        return "ExceedingXYValue";
    case BadLineFormatOrDuplicateXY:
        return "BadLineFormatOrDuplicateXY";
    case BadPlanFile:
        return "BadPlanFile";
    case ConflictingXY:
        return "ConflictingXY";
    case SamePortConsecutively:
        return "SamePortConsecutively";
    case BadPortSymbol:
        return "BadPortSymbol";
    case BadTravelFile:
        return "BadTravelFile";
    case SinglePortTravel:
        return "SinglePortTravel";
    case Reserved:
        return "Reserved";
    case DuplicateContainerOnPort:
        return "DuplicateContainerOnPort";
    case DuplicateContainerOnShip:
        return "DuplicateContainerOnShip";
    case BadContainerWeight:
        return "BadContainerWeight";
    case BadContainerDest:
        return "BadContainerDest";
    case MissingContainerID:
        return "MissingContainerID";
    case BadContainerID:
        return "BadContainerID";
    case BadCargoFile:
        return "BadCargoFile";
    case LastPortNotEmpty:
        return "LastPortNotEmpty";
    case ContainersExceedingCapacity:
        return "ContainersExceedingCapacity";
    }
    return std::to_string(code);
}

string AlgorithmError::errorToString() 
{
    string res;
    uint32_t mask = 1;
    for (size_t i = 0; i < 19; i++)
    {
        if (mask & m_errorCode) res += AlgorithmError::getErrorDescription(errorCode(i)) + " ";
        mask <<= 1;
    }

    if (!res.empty()) res.pop_back();
    return res;
}