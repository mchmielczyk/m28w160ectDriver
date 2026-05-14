#include "mock_m28w160ectTest.h"
STM28W_Status mock_readfn(uint8_t reg, uint8_t * dest)
{
    return (STM28W_Status)mock().returnIntValueOrDefault(STM28W_OK);
}
STM28W_Status mock_rcfiCommand(void)
{
    return (STM28W_Status)mock().returnIntValueOrDefault(STM28W_OK);
}
STM28W_Status mock_readCommand(void)
{
    return (STM28W_Status)mock().returnIntValueOrDefault(STM28W_OK);
}
STM28W_Env MOCK_Env={
    .read_FN=mock_readfn,
    .rcfiC_FN=mock_rcfiCommand,
    .readC_FN=mock_readCommand
};