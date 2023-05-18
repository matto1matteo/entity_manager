#pragma once

class CLifespan {
public:
    int remaning = 0;
    int total = 0;

    CLifespan(int total)
        : remaning(total)
        , total(total)
    {
    }

private:
};
