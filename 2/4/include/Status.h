#ifndef STATUS_H
#define STATUS_H

typedef enum {
    Ok = 0,
    CannotBeRoman,
    VSSFError,
    NotInBase,
    HasException,
    UncorrectNum,
    UncorrectFormat,
    LongOverflow,
    ShouldBeUpper,
    ShouldBeLower,
    IntOverflow,
    BufferOverflow,
    UncorrectZec,
    NotInFormat
} Status;

#endif