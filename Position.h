//
// Created by 24833 on 7/26/2023.
//

#ifndef BIQUADRIS_POSITION_H
#define BIQUADRIS_POSITION_H

struct Posn {
    int x;
    int y;
public:
    Posn(int x = 0, int y = 0);
    bool operator==(const Posn& other) const;
    bool operator!=(const Posn& other) const;
};

#endif //BIQUADRIS_POSITION_H
