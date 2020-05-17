//
// Created by adargut on 5/12/20.
//

#include "AlgorithmError.h"

AlgorithmError::AlgorithmError(uint32_t errorCode) : m_errorCode(errorCode) {}

bool AlgorithmError::setBit(uint32_t bit)
{
    if (bit > 18)
    {
        // TODO maybe return error?
        return false;
    }
    m_errorCode |= uint32_t(1) >> bit;
    return true;
}

bool AlgorithmError::getBit(uint32_t bit) const
{
    if (bit > 18)
    {
        // TODO maybe return error?
        return false;
    }
    return m_errorCode & uint32_t(1) >> bit;
}

int AlgorithmError::getAndClear()
{
    uint32_t tmpErrorCode = m_errorCode;
    m_errorCode = 0;
    return tmpErrorCode;
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
        case BadPortWeight:
            return "BadPortWeight";
        case BadPortDest:
            return "BadPortDest";
        case MissingPortID:
            return "MissingPortID";
        case BadPortID:
            return "BadPortID";
        case BadCargoFile:
            return "BadCargoFile";
        case LastPortNotEmpty:
            return "LastPortNotEmpty";
        case ContainersExceedingCapacity:
            return "ContainersExceedingCapacity";
    }
    return "";
}