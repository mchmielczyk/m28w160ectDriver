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
TEST(M28W_CFI, STM28_EraseSuspend_ValidValuesEraseComplete_ReturnOk)
{
      uint8_t validRegion = 0x05;
      uint16_t validStatusRegister = (1<<7);

      mock().expectOneCall("write_FN")
            .withIntParameter("reg",validRegion)
            .withIntParameter("value",0xb0)
            .andReturnValue(STM28W_OK)
            .andReturnValue(STM28W_OK);

      mock().expectOneCall("write_FN")
            .withIntParameter("reg",validRegion)
            .withIntParameter("value",0x70)
            .andReturnValue(STM28W_OK);

      mock().expectOneCall("rcfiC_FN");

      mock().expectOneCall("read_FN")
            .withIntParameter("reg",validRegion)
            .withOutputParameterReturning("dest",&validStatusRegister,sizeof(uint16_t))
            .andReturnValue(STM28W_OK);

      mock().expectOneCall("readC_FN");

      mock().expectOneCall("write_FN")
            .withIntParameter("reg",validRegion)
            .withIntParameter("value",0xff)
            .andReturnValue(STM28W_OK);

            
      STM28W_Status result = STM28W_EraseSuspend(&MOCK_Env, &validRegion);
      CHECK_EQUAL(STM28W_OK,result);
}
TEST(M28W_CFI, STM28_EraseSuspend_ValidValuesEraseNotComplete_ReturnOk)
{
      uint8_t validRegion = 0x05;
      uint16_t validStatusRegister = (1<<7)|(1<<6);

      mock().expectOneCall("write_FN")
            .withIntParameter("reg",validRegion)
            .withIntParameter("value",0xb0)
            .andReturnValue(STM28W_OK)
            .andReturnValue(STM28W_OK);

      mock().expectOneCall("write_FN")
            .withIntParameter("reg",validRegion)
            .withIntParameter("value",0x70)
            .andReturnValue(STM28W_OK);

      mock().expectOneCall("rcfiC_FN");

      mock().expectOneCall("read_FN")
            .withIntParameter("reg",validRegion)
            .withOutputParameterReturning("dest",&validStatusRegister,sizeof(uint16_t))
            .andReturnValue(STM28W_OK);

      mock().expectOneCall("readC_FN");

      mock().expectOneCall("write_FN")
            .withIntParameter("reg",validRegion)
            .withIntParameter("value",0xff)
            .andReturnValue(STM28W_OK);

      mock().expectOneCall("write_FN")
            .withIntParameter("reg",validRegion)
            .withIntParameter("value",0xd0)
            .andReturnValue(STM28W_OK);

            
      STM28W_Status result = STM28W_EraseSuspend(&MOCK_Env, &validRegion);
      CHECK_EQUAL(STM28W_OK,result);
}
TEST(M28W_CFI, STM28_EraseSuspend_NotValidRegion_ReturnError)
{
      uint8_t * notValidRegion = NULL;

      mock().expectNoCall("write_FN");
            
      STM28W_Status result = STM28W_EraseSuspend(&MOCK_Env, notValidRegion);
      CHECK_EQUAL(STM28W_ERROR,result);
}