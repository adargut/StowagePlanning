#ifndef EX1_FLOOR_H
#define EX1_FLOOR_H

#include <vector>
#include "Container.h"


class Floor {
    typedef typename std::vector<std::vector<Container>> Containers;
    typedef typename std::vector<std::vector<bool>> BoolMatrix;
private:
    BoolMatrix legal_cells;
    bool legalAddition(int row, int col);
    bool legalRemoval(int row, int col);
public:
    Floor(BoolMatrix _legal_cells);
    bool addContainer (const Container& container, int row, int col);
    Container removeContainer(int row, int col);
};

#endif //EX1_FLOOR_H
