#pragma once

class CLifespan {
public:
    /// Remaning lifespan amount
    int remaning = 0;
    /// Initial lifespan amount
    int total = 0;

    CLifespan(int total)
        : remaning(total)
        , total(total)
    {
    }

private:
};
