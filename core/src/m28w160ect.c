#include "../inc/m28w160ect.h"
static STM28W_Status stm28_w_cfi_multi_read(STM28W_Env *Device, uint16_t *reg, uint8_t size)
{
    STM28W_Status returnValue = STM28W_ERROR;
    if (size != 0U)
    {
        Device->rcfiC_FN();
        for (uint8_t i = 0U; i < size; i++)
        {
            returnValue = Device->read_FN((uint8_t)reg[i], &reg[i]);
            if (returnValue != STM28W_OK)
            {
                break;
            }
        }
        Device->readC_FN();
    }
    return returnValue;
}
STM28W_Status STM28W_CheckDevice(STM28W_Env *Device)
{
    STM28W_Status returnValue = STM28W_ERROR;
    uint16_t txrx[2] = {STM28W_ManufacterCode_OffSet, STM28W_DeviceCode_OffSet};
    returnValue = stm28_w_cfi_multi_read(Device, txrx, 2);
    if (!(txrx[0] == STM28W_ManufacterCode_Data))
    {
        returnValue = STM28W_ERROR;
    }
    if ((returnValue != STM28W_ERROR) && ((txrx[1] == STM28W_DeviceCode1_Data) || (txrx[1] == STM28W_DeviceCode2_Data)))
    {
        returnValue = STM28W_OK;
    }
    return returnValue;
}