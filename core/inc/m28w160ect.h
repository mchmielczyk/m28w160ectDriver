#ifndef _H_M23W160ECT_H_
#define _H_M23W160ECT_H_

#include "stdint.h"

#ifdef __cplusplus
extern "C"{
#endif

typedef enum{
    STM28W_OK,
    STM28W_ERROR,
    STM28W_BUSY,
    STM28W_TIMEOUT
}STM28W_Status;

typedef STM28W_Status (*readfn)(uint8_t reg, uint8_t * dest);
typedef STM28W_Status (*rcfiCommand)(void);
typedef STM28W_Status (*readCommand)(void);

typedef struct{
    readfn read_FN;
    rcfiCommand rcfiC_FN;
    readCommand readC_FN;
}STM28W_Env;

STM28W_Status STM28W_CheckDevice(STM28W_Env *Device);

#ifdef __cplusplus
}
#endif

#endif /* _H_M23W160ECT_H_ */