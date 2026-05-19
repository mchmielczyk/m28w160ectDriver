#include "../inc/m28w160ect.h"
static STM28W_Status stm28_w_cfi_multi_read(STM28W_Env *Device, uint16_t *reg, uint8_t size)
{
    STM28W_Status returnValue = STM28W_ERROR;
    if ((size != 0U) && (Device != NULL))
    {
        Device->rcfiC_FN();
        for (uint8_t i = 0U; i < size; i++)
        {
            returnValue = Device->read_FN((uint8_t *)&reg[i], &reg[i]);
            if (returnValue != STM28W_OK)
            {
                break;
            }
        }
        Device->readC_FN();
    }
    return returnValue;
}
static STM28W_Status stm28_w_signle_write(STM28W_Env *Device, uint8_t *reg, uint16_t *value)
{
    STM28W_Status returnValue = STM28W_ERROR;
    if ((Device != NULL) && (reg != NULL) && (value != NULL))
    {
        returnValue = Device->write_FN(reg, value);
    }
    return returnValue;
}
STM28W_Status STM28W_CheckDevice(STM28W_Env *Device)
{
    STM28W_Status returnValue = STM28W_ERROR;
    if (Device != NULL)
    {
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
        else
        {
            returnValue = STM28W_ERROR;
        }
    }
    return returnValue;
}
STM28W_Status STM28W_EraseSuspend(STM28W_Env *Device, uint8_t *targetRegion)
{
    STM28W_Status returnStatus = STM28W_ERROR;
    if ((Device != NULL) && (targetRegion != NULL))
    {
        returnStatus = STM28W_OK;
    }
    if (returnStatus == STM28W_OK)
    {
        uint16_t writeFirstValue = 0xb0;
        returnStatus = stm28_w_signle_write(Device, targetRegion, &writeFirstValue);
    }
    if (returnStatus == STM28W_OK)
    {   
        uint16_t writeSecondValue = 0x70;
        returnStatus = stm28_w_signle_write(Device, targetRegion, &writeSecondValue);
    }
    uint16_t statusRegister = 0U;
    if (returnStatus == STM28W_OK)
    {
        statusRegister = *targetRegion;
        returnStatus = stm28_w_cfi_multi_read(Device, &statusRegister, 1);
    }
    if ((returnStatus == STM28W_OK) && (statusRegister & (1U << 7U)))
    {
        uint16_t writeBufferReadyValue = 0xff;
        if ((statusRegister & (1U << 6U))!=0U)
        {
            returnStatus = stm28_w_signle_write(Device, targetRegion, &writeBufferReadyValue);
            if (returnStatus != STM28W_ERROR)
            {
                uint16_t writeContinueProgramValue = 0xd0;
                returnStatus = stm28_w_signle_write(Device, targetRegion, &writeContinueProgramValue);
            }
        }
        else
        {
            returnStatus = stm28_w_signle_write(Device, targetRegion, &writeBufferReadyValue);
        }
    }
    else
    {
        returnStatus = STM28W_ERROR;
    }

    return returnStatus;
}