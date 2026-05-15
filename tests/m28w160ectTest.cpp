#include "m28w160ectTest.hpp"
extern "C"{
extern STM28W_Env MOCK_Env;
}
TEST_GROUP(M28W_CFI)
{
    void setup(){}
    void teardown(){
        mock().checkExpectations();
        mock().clear();
    }
};
TEST(M28W_CFI,STM28_CheckDevice_ValidManAndDev1_ReturnOk)
{
    uint16_t manCode = STM28W_ManufacterCode_Data;
    uint16_t devCode = STM28W_DeviceCode1_Data;
    mock().expectOneCall("rcfiC_FN");

    mock().expectOneCall("read_FN")
          .withParameter("reg",STM28W_ManufacterCode_OffSet)
          .withOutputParameterReturning("dest",&manCode,sizeof(uint16_t))
          .andReturnValue(STM28W_OK);

    mock().expectOneCall("read_FN")
          .withParameter("reg",STM28W_DeviceCode_OffSet)
          .withOutputParameterReturning("dest",&devCode,sizeof(uint16_t))
          .andReturnValue(STM28W_OK);

    mock().expectOneCall("readC_FN");

    STM28W_Status result = STM28W_CheckDevice(&MOCK_Env);
    CHECK_EQUAL(STM28W_OK, result);
}
TEST(M28W_CFI,STM28_CheckDevice_ValidManAndDev2_ReturnOk)
{
    uint16_t manCode = STM28W_ManufacterCode_Data;
    uint16_t devCode = STM28W_DeviceCode2_Data;
    mock().expectOneCall("rcfiC_FN");

    mock().expectOneCall("read_FN")
          .withParameter("reg",STM28W_ManufacterCode_OffSet)
          .withOutputParameterReturning("dest",&manCode,sizeof(uint16_t))
          .andReturnValue(STM28W_OK);

    mock().expectOneCall("read_FN")
          .withParameter("reg",STM28W_DeviceCode_OffSet)
          .withOutputParameterReturning("dest",&devCode,sizeof(uint16_t))
          .andReturnValue(STM28W_OK);

    mock().expectOneCall("readC_FN");

    STM28W_Status result = STM28W_CheckDevice(&MOCK_Env);

    CHECK_EQUAL(STM28W_OK, result);
}
TEST(M28W_CFI,STM28_CheckDevice_InvalidManReturn_ReturnError)
{
    uint16_t invalidManufacterCodeReturn = 0xff;

    mock().expectOneCall("rcfiC_FN");

    mock().expectOneCall("read_FN")
          .withParameter("reg",STM28W_ManufacterCode_OffSet)
          .withOutputParameterReturning("dest",&invalidManufacterCodeReturn,sizeof(uint16_t))
          .andReturnValue(STM28W_ERROR);
  
    mock().expectNoCall("read_FN");
    mock().expectOneCall("readC_FN");

    STM28W_Status result = STM28W_CheckDevice(&MOCK_Env);
    CHECK_EQUAL(STM28W_ERROR,result);
}
TEST(M28W_CFI,STM28_CheckDevice_InvalidDevReturn_ReturnError)
{
    uint16_t invalidDeviceCodeReturn = 0xff;
    uint16_t devCode = STM28W_DeviceCode2_Data;
    
    mock().expectOneCall("rcfiC_FN");

    mock().expectOneCall("read_FN")
          .withParameter("reg",STM28W_ManufacterCode_OffSet)
          .withOutputParameterReturning("dest",&invalidDeviceCodeReturn,sizeof(uint16_t))
          .andReturnValue(STM28W_OK);

    mock().expectOneCall("read_FN")
          .withParameter("reg",STM28W_DeviceCode_OffSet)
          .withOutputParameterReturning("dest",&devCode,sizeof(uint16_t))
          .andReturnValue(STM28W_OK);

    mock().expectOneCall("readC_FN");

    STM28W_Status result = STM28W_CheckDevice(&MOCK_Env);
    CHECK_EQUAL(STM28W_ERROR,result);
}