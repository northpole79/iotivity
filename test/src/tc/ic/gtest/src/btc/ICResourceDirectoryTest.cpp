/******************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
 *
 *
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************/
#include "ICHelper.h"

using namespace OC;
using namespace OC::OCPlatform;

class ICResourceDirectoryTest_btc: public ::testing::Test
{
public:
    ResourceHandles m_resourceHandles;
    OCPresenceHandle m_ocPresenceHandle = nullptr;
    QueryParamsList m_queryParams =
    { };
    const std::vector< std::string > m_vecDeviceIdentifier;bool m_isCallbackInvoked;
    OCStackResult m_actualResult;

protected:
    ICHelper* m_ICHelper;

    ICResourceDirectoryTest_btc()
    {
        m_isCallbackInvoked = false;
        m_ICHelper = nullptr;
        m_actualResult = OC_STACK_ERROR;
    }

    virtual void SetUp()
    {
        CommonUtil::runCommonTCSetUpPart();
        m_ICHelper = ICHelper::getInstance();
        m_actualResult = OC_STACK_ERROR;
        m_isCallbackInvoked = false;
    }

    virtual void TearDown()
    {
        CommonUtil::runCommonTCTearDownPart();
    }

public:
    void onPublish(const OCRepresentation& rep, const int& eCode)
    {
        m_isCallbackInvoked = true;
        IOTIVITYTEST_LOG(INFO, "[ICResourceDirectoryTest_btc] Response from onPublish\n");
    }

    void onDelete(const int& eCode)
    {
        m_isCallbackInvoked = true;
        IOTIVITYTEST_LOG(INFO, "[ICResourceDirectoryTest_btc] Response from onDelete\n");
    }

    void onObserve(const HeaderOptions headerOption, const OCRepresentation&, const int& val1,
            const int& val2)
    {
        m_isCallbackInvoked = true;
        IOTIVITYTEST_LOG(INFO, "[ICResourceDirectoryTest_btc] Response from onObserve\n");
    }
};

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' positively to Publish Virtual Resource to RD
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                             PublishResourceCallback callback)
 * @test_data       1. host                 Host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onPublish as callback
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will Publish Virtual Resource to Resource Directory & return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRD_SRC_FSV_P)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS, IC_CONNECTIVITY_TYPE,
                std::bind(&ICResourceDirectoryTest_btc::onPublish,this, placeholders::_1, placeholders::_2));
        EXPECT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        FAIL() << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/**
 * @since           2015-11-30
 * @see             static OCStackResult provisionInit(const std::string& dbPath)
 * @see             static OCStackResult setOwnerTransferCallbackData(OicSecOxm_t oxm, OTMCallbackData_t* callbackData, InputPinCallback inputPin)
 * @see             static OCStackResult discoverUnownedDevices(unsigned short timeout, DeviceList_t &list)
 * @see             OCStackResult doOwnershipTransfer(ResultCallBack resultCallback)
 * @see             static OCStackResult discoverOwnedDevices(unsigned short timeout, DeviceList_t &list)
 * @objective       test provisionACL positively with minimum range of Acl permission
 * @target          OCStackResult provisionACL(const OicSecAcl_t* acl, ResultCallBack resultCallback)
 * @test_data       Acl permission with minimum Range
 * @pre_condition   start two justworks simulators
 * @procedure       1. call provisionInit
 *                  2. call discoverUnownedDevices
 *                  3. call setOwnerTransferCallbackData
 *                  4. call doOwnershipTransfer
 *                  5. call discoverOwnedDevices
 *                  6. call provisionACL
 * @post_condition  None
 * @expected        provisionACL will return OC_STACK_OK
 */
#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDwithInvalidHost_USV_N)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS_INVALID, IC_CONNECTIVITY_TYPE,
                std::bind(&ICResourceDirectoryTest_btc::onPublish,this, placeholders::_1, placeholders::_2));
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_URI, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' negatively with Empty string value
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                             PublishResourceCallback callback)
 * @test_data       1. host                 empty host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onPublish as callback
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_PARAM
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDwithEmptyHost_ESV_N)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS_EMPTY, IC_CONNECTIVITY_TYPE,
                std::bind(&ICResourceDirectoryTest_btc::onPublish,this, placeholders::_1, placeholders::_2));
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' negatively with NULL string value but API handled
 *                  null callback properly
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                             PublishResourceCallback callback)
 * @test_data       1. host                 invalid host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             null as callback
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will success & return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDwithNullCallback_NV_N)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS, IC_CONNECTIVITY_TYPE,IC_CALLBACK_HANDLER_NULL);
        ASSERT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        FAIL() << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' positively to Publish Resource to RD
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                             PublishResourceCallback callback,QualityOfService QoS)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onPublish as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will Publish Resource to Resource Directory & return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDWithQOS_SRC_FSV_P)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS, IC_CONNECTIVITY_TYPE,
                std::bind(&ICResourceDirectoryTest_btc::onPublish,this, placeholders::_1, placeholders::_2),IC_OC_QUALITY_OF_SERVICE);
        EXPECT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        FAIL() << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' negatively with Unformatted value
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                                      PublishResourceCallback callback,QualityOfService QoS)
 * @test_data       1. host                 invalid host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onPublish as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_URI
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDWithQOSWithInvalidHost_USV_N)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS_INVALID, IC_CONNECTIVITY_TYPE,
                std::bind(&ICResourceDirectoryTest_btc::onPublish,this, placeholders::_1, placeholders::_2),IC_OC_QUALITY_OF_SERVICE);
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_URI, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' negatively with Empty IC_HOST_ADDRESS value
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                             PublishResourceCallback callback,QualityOfService QoS)
 * @test_data       1. host                 empty address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onPublish as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_PARAM
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDWithQOSWithEmptyHost_ESV_N)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS_EMPTY, IC_CONNECTIVITY_TYPE,
                std::bind(&ICResourceDirectoryTest_btc::onPublish,this, placeholders::_1, placeholders::_2),IC_OC_QUALITY_OF_SERVICE);
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' negatively with NULL string value but API handled
 *                  null callback properly
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                             PublishResourceCallback callback,QualityOfService QoS)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             null as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will success & return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDWithQOSWithNullCallback_NV_N)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS, IC_CONNECTIVITY_TYPE,IC_CALLBACK_HANDLER_NULL,IC_OC_QUALITY_OF_SERVICE);
        ASSERT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        FAIL() << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' positively to Publish Virtual Resource to RD
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                                      ResourceHandles& resourceHandles,PublishResourceCallback callback)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onPublish as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will Publish Virtual Resource to Resource Directory & return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDWithResourceHandle_SRC_FSV_P)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                std::bind(&ICResourceDirectoryTest_btc::onPublish,this, placeholders::_1, placeholders::_2));
        EXPECT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        FAIL() << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' negatively with Unformatted value
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                                      ResourceHandles& resourceHandles,PublishResourceCallback callback)
 * @test_data       1. host                 invalid host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onPublish as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_URI
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDWithResourceHandleWithInvalidHost_USV_N)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS_INVALID, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                std::bind(&ICResourceDirectoryTest_btc::onPublish,this, placeholders::_1, placeholders::_2));
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_URI, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' negatively with Empty string value
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                                      ResourceHandles& resourceHandles,PublishResourceCallback callback)
 * @test_data       1. host                 empty address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onPublish as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_PARAM
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDWithResourceHandleWithEmptyHost_ESV_N)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS_EMPTY, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                std::bind(&ICResourceDirectoryTest_btc::onPublish,this, placeholders::_1, placeholders::_2));
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' negatively with NULL string value but API handled
 *                  null callback properly
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                                      ResourceHandles& resourceHandles,PublishResourceCallback callback)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             null as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will success & return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDWithResourceHandleWithNullCallback_NV_N)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                IC_CALLBACK_HANDLER_NULL);
        ASSERT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        FAIL() << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' positively to Publish Resource to RD
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                                      ResourceHandles& resourceHandles,PublishResourceCallback callback,QualityOfService QoS)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onPublish as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will Publish Resource to Resource Directory & return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDWithResourceHandleAndWithQOS_SRC_FSV_P)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                std::bind(&ICResourceDirectoryTest_btc::onPublish,this, placeholders::_1, placeholders::_2),IC_OC_QUALITY_OF_SERVICE);
        EXPECT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        FAIL() << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' negatively with Unformatted value
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                                      ResourceHandles& resourceHandles,PublishResourceCallback callback,QualityOfService QoS)
 * @test_data       1. host                 invalid host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onPublish as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_URI
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDWithResourceHandleAndWithQOSWithInvalidHost_USV_N)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS_INVALID, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                std::bind(&ICResourceDirectoryTest_btc::onPublish,this, placeholders::_1, placeholders::_2),IC_OC_QUALITY_OF_SERVICE);
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_URI, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' negatively with Empty IC_HOST_ADDRESS value
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                                      ResourceHandles& resourceHandles,PublishResourceCallback callback,QualityOfService QoS)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onPublish as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_PARAM
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDWithResourceHandleAndWithQOSWithEmptyHost_ESV_N)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS_EMPTY, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                std::bind(&ICResourceDirectoryTest_btc::onPublish,this, placeholders::_1, placeholders::_2),IC_OC_QUALITY_OF_SERVICE);
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'publishResourceToRD' negatively with NULL string value but API handled
 *                  null callback properly
 * @target          publishResourceToRD(const std::string& host,OCConnectivityType connectivityType,
 *                                      ResourceHandles& resourceHandles,PublishResourceCallback callback,QualityOfService QoS)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onPublish as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call publishResourceToRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will success & return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, PublishResourceToRDWithResourceHandleAndWithQOSWithNullCallback_NV_N)
{
    try
    {
        m_actualResult = OCPlatform::publishResourceToRD(IC_HOST_ADDRESS, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                IC_CALLBACK_HANDLER_NULL,IC_OC_QUALITY_OF_SERVICE);
        ASSERT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        FAIL() << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' positively to delete Published Resource from RD
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                              DeleteResourceCallback callback)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onDelete as callback
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will delete Published Resource from Resource Directory & return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRD_SRC_FSV_P)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS, IC_CONNECTIVITY_TYPE,
                std::bind(&ICResourceDirectoryTest_btc::onDelete,this, placeholders::_1));
        ASSERT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        FAIL() << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' negatively with Unformatted value
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       DeleteResourceCallback callback)
 * @test_data       1. host                 invalid host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onDelete as callback
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_URI
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDWithInvalidHost_USV_N)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS_INVALID, IC_CONNECTIVITY_TYPE,
                std::bind(&ICResourceDirectoryTest_btc::onDelete,this, placeholders::_1));
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_URI, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' negatively with Empty string value
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       DeleteResourceCallback callback)
 * @test_data       1. host                 empty host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onDelete as callback
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_PARAM
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDWithEmptyHost_ESV_N)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS_EMPTY, IC_CONNECTIVITY_TYPE, std::bind(&ICResourceDirectoryTest_btc::onDelete,
                        this, placeholders::_1));
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' negatively with NULL string value
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       DeleteResourceCallback callback)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             null as callback
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_PARAM
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDDWithNullCallback_NV_N)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS_EMPTY, IC_CONNECTIVITY_TYPE,IC_CALLBACK_HANDLER_NULL);
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' positively to delete Published Resource from RD
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       DeleteResourceCallback callback,QualityOfService QoS)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onDelete as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will delete Published Resource from Resource Directory & return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDWithQOS_SRC_FSV_P)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS, IC_CONNECTIVITY_TYPE,
                std::bind(&ICResourceDirectoryTest_btc::onDelete,this, placeholders::_1),IC_OC_QUALITY_OF_SERVICE);
        ASSERT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        FAIL() << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' negatively with Unformatted value
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       DeleteResourceCallback callback,QualityOfService QoS)
 * @test_data       1. host                 invalid host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onDelete as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_URI
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDWithQOSWithInvalidHost_USV_N)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS_INVALID, IC_CONNECTIVITY_TYPE,
                std::bind(&ICResourceDirectoryTest_btc::onDelete,this, placeholders::_1),IC_OC_QUALITY_OF_SERVICE);
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_URI, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' negatively with Empty string value
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       DeleteResourceCallback callback,QualityOfService QoS)
 * @test_data       1. host                 epmty host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             onDelete as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_PARAM
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDWithQOSWithEmptyHost_ESV_N)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS_EMPTY, IC_CONNECTIVITY_TYPE, std::bind(&ICResourceDirectoryTest_btc::onDelete,
                        this, placeholders::_1),IC_OC_QUALITY_OF_SERVICE);
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' negatively with NULL string value
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       DeleteResourceCallback callback,QualityOfService QoS)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. callback             null as callback
 *                  4. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_PARAM
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDWithQOSWithNullCallback_NV_N)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS_EMPTY, IC_CONNECTIVITY_TYPE,IC_CALLBACK_HANDLER_NULL,IC_OC_QUALITY_OF_SERVICE);
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' positively to delete Published Resource from RD
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       ResourceHandles& resourceHandles,DeleteResourceCallback callback)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. resourceHandles      ResourceHandles
 *                  4. callback             onDelete as callback
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will delete Published Resource from Resource Directory & return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDWithResourceHandler_SRC_FSV_P)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                std::bind(&ICResourceDirectoryTest_btc::onDelete,this, placeholders::_1));
        ASSERT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        FAIL() << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' negatively with Unformatted value
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       ResourceHandles& resourceHandles,DeleteResourceCallback callback)
 * @test_data       1. host                 invalid host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. resourceHandles      ResourceHandles
 *                  4. callback             onDelete as callback
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_URI
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDWithResourceHandlerWithInvalidHost_USV_N)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS_INVALID, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                std::bind(&ICResourceDirectoryTest_btc::onDelete,this, placeholders::_1));
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_URI, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' negatively with Empty string value
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       ResourceHandles& resourceHandles,DeleteResourceCallback callback)
 * @test_data       1. host                 empty host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. resourceHandles      ResourceHandles
 *                  4. callback             onDelete as callback
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_PARAM
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDWithResourceHandlerWithEmptyHost_ESV_N)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS_EMPTY, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                std::bind(&ICResourceDirectoryTest_btc::onDelete,this, placeholders::_1));
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' negatively with NULL string value
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       ResourceHandles& resourceHandles,DeleteResourceCallback callback)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. resourceHandles      ResourceHandles
 *                  4. callback             null as callback
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_PARAM
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDWithResourceHandlerWithNullCallback_NV_N)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS_EMPTY, IC_CONNECTIVITY_TYPE,m_resourceHandles,IC_CALLBACK_HANDLER_NULL);
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' positively to delete Published Resource from RD
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       ResourceHandles& resourceHandles,DeleteResourceCallback callback, QualityOfService QoS)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. resourceHandles      ResourceHandles
 *                  4. callback             onDelete as callback
 *                  5. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will delete Published Resource from Resource Directory & return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDWithResourceHanlderAndQOS_SRC_FSV_P)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                std::bind(&ICResourceDirectoryTest_btc::onDelete,this, placeholders::_1),IC_OC_QUALITY_OF_SERVICE);
        ASSERT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        FAIL() << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' negatively with Unformatted value
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       ResourceHandles& resourceHandles,DeleteResourceCallback callback, QualityOfService QoS)
 * @test_data       1. host                 invalid host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. resourceHandles      ResourceHandles
 *                  4. callback             onDelete as callback
 *                  5. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_URI
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDWithResourceHanlderAndQOSWithInvalidHost_USV_N)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS_INVALID, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                std::bind(&ICResourceDirectoryTest_btc::onDelete,this, placeholders::_1),IC_OC_QUALITY_OF_SERVICE);
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_URI, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }
}
#endif

/*
 * @since           2016-08-24
 * @see             OCConnectivityType connectivityType
 * @objective       Test 'deleteResourceFromRD' negatively with Empty string value
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       ResourceHandles& resourceHandles,DeleteResourceCallback callback, QualityOfService QoS)
 * @test_data       1. host                 empty host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. resourceHandles      ResourceHandles
 *                  4. callback             onDelete as callback
 *                  5. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_PARAM
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDWithResourceHanlderAndQOSWithEmptyHost_ESV_N)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS_EMPTY, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                std::bind(&ICResourceDirectoryTest_btc::onDelete,this, placeholders::_1),IC_OC_QUALITY_OF_SERVICE);
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-24
 * @see             none
 * @objective       Test 'deleteResourceFromRD' negatively with NULL string value
 * @target          deleteResourceFromRD(const std::string& host,OCConnectivityType connectivityType,
 *                                       ResourceHandles& resourceHandles,DeleteResourceCallback callback, QualityOfService QoS)
 * @test_data       1. host                 host address
 *                  2. connectivityType     CT_DEFAULT as connectivity
 *                  3. resourceHandles      ResourceHandles
 *                  4. callback             null as callback
 *                  5. QoS                  QualityOfService::HighQos
 * @pre_condition   none
 * @procedure       1. Call deleteResourceFromRD API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not success & return OC_STACK_INVALID_PARAM
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, DeleteResourceFromRDWithResourceHanlderAndQOSWithNullCallback_NV_N)
{
    try
    {
        m_actualResult = OCPlatform::deleteResourceFromRD(IC_HOST_ADDRESS_EMPTY, IC_CONNECTIVITY_TYPE,m_resourceHandles,
                IC_CALLBACK_HANDLER_NULL,IC_OC_QUALITY_OF_SERVICE);
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-25
 * @see             none
 * @objective       Test 'subscribeDevicePresence' positively to subscribes to a server's device presence change events
 * @target          subscribeDevicePresence(OCPresenceHandle& presenceHandle,const std::string& host,const std::vector<std::string>& di,
 *                                          OCConnectivityType connectivityType,ObserveCallback callback)
 * @test_data       1. presenceHandle       OCPresenceHandle
 *                  2. host                 host address
 *                  3. di                   device Identity
 *                  4. connectivityType     CT_DEFAULT
 *                  5. callback             onObserve as callback
 * @pre_condition   none
 * @procedure       1. Call subscribeDevicePresence API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will subscribes to a server's device presence change events & return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, SubscribeDevicePresenceWithValidParameters_SRC_FSV_P)
{
    try
    {
        m_actualResult = OCPlatform::subscribeDevicePresence(m_ocPresenceHandle,IC_HOST_ADDRESS, m_vecDeviceIdentifier,IC_CONNECTIVITY_TYPE,
                std::bind(&ICResourceDirectoryTest_btc::onObserve, this,placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4));
        ASSERT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        FAIL() << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-25
 * @see             none
 * @objective       Test 'subscribeDevicePresence' negatively with Invalid Host address
 * @target          subscribeDevicePresence(OCPresenceHandle& presenceHandle,const std::string& host,const std::vector<std::string>& di,
 *                                          OCConnectivityType connectivityType,ObserveCallback callback)
 * @test_data       1. presenceHandle       OCPresenceHandle
 *                  2. host                 invalid host address
 *                  3. di                   device Identity
 *                  4. connectivityType     CT_DEFAULT
 *                  5. callback             onObserve as callback
 * @pre_condition   none
 * @procedure       1. Call subscribeDevicePresence API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not subscribes & will return OC_STACK_INVALID_URI
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, SubscribeDevicePresenceWithInvalidHostAddress_USV_N)
{
    try
    {
        m_actualResult = OCPlatform::subscribeDevicePresence(m_ocPresenceHandle,IC_HOST_ADDRESS_INVALID, m_vecDeviceIdentifier,IC_CONNECTIVITY_TYPE,
                std::bind(&ICResourceDirectoryTest_btc::onObserve, this,placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4));
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_URI, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-25
 * @see             none
 * @objective       Test 'subscribeDevicePresence' negatively with Empty IC_HOST_ADDRESS
 * @target          subscribeDevicePresence(OCPresenceHandle& presenceHandle,const std::string& host,const std::vector<std::string>& di,
 *                                          OCConnectivityType connectivityType,ObserveCallback callback)
 * @test_data       1. presenceHandle       OCPresenceHandle
 *                  2. host                 empty host address
 *                  3. di                   device Identity
 *                  4. connectivityType     CT_DEFAULT
 *                  5. callback             onObserve as callback
 * @pre_condition   none
 * @procedure       1. Call subscribeDevicePresence API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not subscribes & should return OC_STACK_INVALID_PARAM
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, SubscribeDevicePresenceWithEmptyHost_ESV_N)
{
    try
    {
        m_actualResult = OCPlatform::subscribeDevicePresence(m_ocPresenceHandle,IC_HOST_ADDRESS_EMPTY, m_vecDeviceIdentifier,IC_CONNECTIVITY_TYPE,
                std::bind(&ICResourceDirectoryTest_btc::onObserve, this,placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4));
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        EXPECT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-25
 * @see             none
 * @objective       Test 'subscribeDevicePresence' negatively with null OnObserve
 * @target          subscribeDevicePresence(OCPresenceHandle& presenceHandle,const std::string& host,const std::vector<std::string>& di,
 *                                          OCConnectivityType connectivityType,ObserveCallback callback)
 * @test_data       1. presenceHandle       OCPresenceHandle
 *                  2. host                 host address
 *                  3. di                   device Identity
 *                  4. connectivityType     CT_DEFAULT
 *                  5. callback             null as callback
 * @pre_condition   none
 * @procedure       1. Call subscribeDevicePresence API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not subscribes & should not return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, SubscribeDevicePresenceWithNullCallback_NV_N)
{
    try
    {
        m_actualResult = OCPlatform::subscribeDevicePresence(m_ocPresenceHandle,IC_HOST_ADDRESS_EMPTY, m_vecDeviceIdentifier,
                IC_CONNECTIVITY_TYPE,IC_CALLBACK_HANDLER_NULL);
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        ASSERT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-25
 * @see             subscribeDevicePresence(OCPresenceHandle& presenceHandle,const std::string& host,const std::vector<std::string>& di,
 *                                          OCConnectivityType connectivityType,ObserveCallback callback)
 * @objective       Test 'unsubscribePresence' with positive value
 * @target          unsubscribePresence(OCPresenceHandle presenceHandle)
 * @test_data       1. presenceHandle       OCPresenceHandle
 * @pre_condition   none
 * @procedure       1. Call subscribeDevicePresence API
 *                  2. Check it's return value
 *                  3. Call unsubscribePresence API
 *                  4. Check it's return value
 * @post_condition  none
 * @expected        It will unsubscribes & should return OC_STACK_OK
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, UnsubscribePresenceWithValidParameters_SRC_FSV_P)
{
    try
    {
        m_actualResult = OCPlatform::subscribeDevicePresence(m_ocPresenceHandle,IC_HOST_ADDRESS, m_vecDeviceIdentifier,IC_CONNECTIVITY_TYPE,
                std::bind(&ICResourceDirectoryTest_btc::onObserve, this,placeholders::_1, placeholders::_2, placeholders::_3, placeholders::_4));
        EXPECT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);

        m_actualResult = OC_STACK_ERROR;
        m_actualResult = OCPlatform::unsubscribePresence(m_ocPresenceHandle);
        ASSERT_EQ(OC_STACK_OK,m_actualResult) << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        FAIL() << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif

/*
 * @since           2016-08-25
 * @see             none
 * @objective       Test 'subscribeDevicePresence' negatively with Invalid Host address
 * @target          unsubscribePresence(OCPresenceHandle presenceHandle)
 * @test_data       1. presenceHandle       nullptr as OCPresenceHandle
 * @pre_condition   none
 * @procedure       1. Call subscribeDevicePresence API
 *                  2. Check it's return value
 * @post_condition  none
 * @expected        It will not subscribes & will return OC_STACK_INVALID_PARAM
 */

#if defined(__LINUX__) || defined(__TIZEN__)
TEST_F(ICResourceDirectoryTest_btc, UnSubscribeDevicePresenceWithInvalidOCPresentHandler_USV_N)
{
    try
    {
        m_actualResult = OCPlatform::unsubscribePresence(nullptr);
        FAIL() << "Actual result string : " << CommonUtil::s_OCStackResultString.at(m_actualResult);
    }
    catch(OCException ex)
    {
        ASSERT_EQ(OC_STACK_INVALID_PARAM, ex.code()) << "OCException result string : " << CommonUtil::s_OCStackResultString.at(ex.code());
    }

    SUCCEED();
}
#endif
