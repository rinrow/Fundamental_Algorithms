#ifndef STATUS_H
#define STATUS_H

typedef enum {
    Ok = 0,
    ErrorOnMalloc,
    ErrorOnReading,
    ErrorOnRealloc,
    HasException
} Status;

#endif