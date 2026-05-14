#include "../inc/m28w160ect.h"
STM28W_Status STM28W_CheckDevice(STM28W_Env *Device)
{
    uint8_t manCode,devCode;
    Device->rcfiC_FN();
    Device->read_FN(0x00,&manCode);
    Device->read_FN(0x01,&devCode);
    Device->readC_FN();
    if(!(manCode==0x20))return STM28W_ERROR;
    if(devCode==0xce||devCode==0xcf)
    {
        return STM28W_OK;
    }
    return STM28W_ERROR;
}