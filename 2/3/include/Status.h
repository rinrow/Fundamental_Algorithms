#ifndef STATUS_H
#define STATUS_H

typedef enum {
    Ok = 0,
    CannotBeRoman,
    VSPFError,
    NotInBase,
    HasException,
    UncorrectNum,
    LongOverflow,
    ShouldBeUpper,
    ShouldBeLower
} Status;

#endif