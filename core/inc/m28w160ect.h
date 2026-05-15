#ifndef H_M23W160ECT_H_
#define H_M23W160ECT_H_

#include "stdint.h"

#define STM28W_ManufacterCode_OffSet 0x00u 
#define STM28W_DeviceCode_OffSet 0x01U

#define STM28W_ManufacterCode_Data 0x0020U 
#define STM28W_DeviceCode1_Data 0x88ceU
#define STM28W_DeviceCode2_Data 0x88cfU

#ifdef __cplusplus
extern "C"{
#endif

typedef enum{
    STM28W_OK,
    STM28W_ERROR,
    STM28W_BUSY,
    STM28W_TIMEOUT
}STM28W_Status;

typedef STM28W_Status (*readfn)(uint8_t reg, uint16_t * dest);
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

#endif /* H_M23W160ECT_H_ */