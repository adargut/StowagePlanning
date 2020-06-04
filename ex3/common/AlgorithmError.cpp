#include "AlgorithmError.h"

// constructor
AlgorithmError::AlgorithmError(uint32_t errorCode) : m_errorCode(errorCode) {}

// Flip the of the error that occurred from 0 to 1
bool AlgorithmError::setBit(uint32_t bit)
{
    if (bit > 18)
    {
        return false;
    }
    m_errorCode |= uint32_t(1) << bit;
    return true;
}

// Check if certain bit is turned on or not
bool AlgorithmError::getBit(uint32_t bit) const
{
    if (bit > 18)
    {
        return false;
    }
    return m_errorCode & uint32_t(1) << bit;
}

// Fetches int corresponding to the errors that happened, then clears it
int AlgorithmError::getAndClear()
{
    uint32_t tmpErrorCode = m_errorCode;
    m_errorCode = 0;
    return tmpErrorCode;
}

// Converts the error code to its string description (just one bit)
string AlgorithmError::getErrorDescription(errorCode code)
{
    switch (code)
    {
    case ExceedingFloorValue:
        return "Exceeding Floor Value";
    case ExceedingXYValue:
        return "Exceeding XY Value";
    case BadLineFormatOrDuplicateXY:
        return "Bad Line Format Or Duplicate XY";
    case BadPlanFile:
        return "Bad Plan File";
    case ConflictingXY:
        return "Conflicting XY";
    case SamePortConsecutively:
        return "Same Port Consecutively";
    case BadPortSymbol:
        return "Bad Port Symbol";
    case BadTravelFile:
        return "Bad Travel File";
    case SinglePortTravel:
        return "Single Port Travel";
    case Reserved:
        return "Reserved";
    case DuplicateContainerOnPort:
        return "Duplicate Container On Port";
    case DuplicateContainerOnShip:
        return "Duplicate Container On Ship";
    case BadContainerWeight:
        return "Bad Container Weight";
    case BadContainerDest:
        return "Bad Container Dest";
    case MissingContainerID:
        return "Missing Container ID";
    case BadContainerID:
        return "Bad Container ID";
    case BadCargoFile:
        return "Bad Cargo File";
    case LastPortNotEmpty:
        return "Last Port Not Empty";
    case ContainersExceedingCapacity:
        return "Containers Exceeding Capacity";
    }
    return std::to_string(code);
}

// Convert an error int to its string (all the bits together)
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