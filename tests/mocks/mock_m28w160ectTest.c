#include "mock_m28w160ectTest.h"
STM28W_Status mock_readfn(uint8_t * reg, uint16_t *dest)
{
    mock_c()->actualCall("read_FN")->withIntParameters("reg", *reg)->withOutputParameter("dest", dest);
    return STM28W_Status(mock_c()->returnIntValueOrDefault(0));
}
STM28W_Status mock_writefn(uint8_t * reg,uint16_t * value)
{
    mock_c()->actualCall("write_FN")->withIntParameters("reg",*reg)->withIntParameters("value", *value);
    return STM28W_Status(mock_c()->returnIntValueOrDefault(0));
}
STM28W_Status mock_rcfiCommand(void)
{
    mock_c()->actualCall("rcfiC_FN");
    return STM28W_OK;
}
STM28W_Status mock_readCommand(void)
{
    mock_c()->actualCall("readC_FN");
    return STM28W_OK;
}
STM28W_Env MOCK_Env = {
    .read_FN = mock_readfn,
    .write_FN = mock_writefn,
    .rcfiC_FN = mock_rcfiCommand,
    .readC_FN = mock_readCommand};