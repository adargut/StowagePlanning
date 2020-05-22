//
// Created by adargut on 5/12/20.
//

#ifndef EX2_ALGORITHMERROR_H
#define EX2_ALGORITHMERROR_H

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

using string = std::string;

class AlgorithmError 
{
private:
    uint32_t m_errorCode;
public:
    enum errorCode
    {
        // Errors related to ship plan
        ExceedingFloorValue=0, ExceedingXYValue=1, BadLineFormatOrDuplicateXY=2, BadPlanFile=3, ConflictingXY=4,
        // Errors related travel route
        SamePortConsecutively=5, BadPortSymbol=6, BadTravelFile=7, SinglePortTravel=8, Reserved=9,
        // Errors related to containers
        DuplicateContainerOnPort=10, DuplicateContainerOnShip=11, BadContainerWeight=12, BadContainerDest=13, 
        MissingContainerID=14, BadContainerID=15, BadCargoFile=16, LastPortNotEmpty=17, ContainersExceedingCapacity=18
    };
    explicit AlgorithmError(uint32_t errorCode=0);
    explicit operator bool() const { return m_errorCode > 0; }
    bool setBit(uint32_t bit);
    bool getBit(uint32_t bit) const;
    int getAndClear();
    errorCode getErrorCode();
    string errorToString();
    static string getErrorDescription(errorCode code);
};


#endif //EX2_ALGORITHMERROR_H
