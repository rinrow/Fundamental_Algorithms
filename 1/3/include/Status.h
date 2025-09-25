#ifndef STATUS_H
#define STATUS_H

typedef enum {
    Ok,
    InvalidInput,
    HasException,
    NotInteger,
    Zero,
    NegativeNum,
    LongOverflow,
} Status;

#endif