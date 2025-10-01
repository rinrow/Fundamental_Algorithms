#ifndef STATUS_H
#define STATUS_H

typedef enum {
    Ok,
    UnocorrectNum,
    LongOverflow,
    NotInBase,
    NumHasLower,
    HasException
} Status;

#endif