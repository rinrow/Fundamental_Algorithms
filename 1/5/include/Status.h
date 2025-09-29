#ifndef STATUS_H
#define STATUS_H

typedef enum {
    Ok,
    ErrorWhenWrite,
    InvalidInput,
    HasException,
    UncorrectFlag
} Status;

#endif