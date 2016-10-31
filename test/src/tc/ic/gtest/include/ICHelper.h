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


#ifndef INCLUDE_TESTCASE_ICHELPER_H_
#define INCLUDE_TESTCASE_ICHELPER_H_

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <mutex>
#include <ctime>
#include <unistd.h>
#include <functional>
#include <bitset>
#include <map>
#include <set>
#include <exception>
#include <memory>
#include <stdexcept>
#include <condition_variable>

#include "gtest/gtest.h"
#include "gtest_custom.h"
#include "OCResource.h"
#include "octypes.h"
#include "OCApi.h"
#include "OCPlatform.h"
#include <InitializeException.h>
#include "OCException.h"
#include <ocstack.h>
#include "ocpayload.h"
#include "rd_client.h"
#include "rd_server.h"
#include "rd_database.h"
#include "ICResource.h"
#include "IotivityTest_Logger.h"
#include "ICTemperatureResource.h"
#include "ICBinarySwitchResource.h"
#include "ICAirconditionerResource.h"
#include "CommonUtil.h"

#define SERVER ""
#define IC_HOST_ADDRESS_INVALID                 "AAA.BBB:GGG"
#define IC_HOST_ADDRESS_EMPTY                   ""
#define IC_CONNECTIVITY_TYPE                    CT_ADAPTER_TCP
#define IC_OC_QUALITY_OF_SERVICE                QualityOfService::LowQos
#define IC_OC_QUALITY_OF_SERVICE_NULL           NULL
#define IC_CALLBACK_HANDLER_NULL                NULL

#define IC_HOST_ADDRESS_EMPTY                   ""
#define IC_SLEEPTIME_MAX                        5
#define IC_SLEEPTIME_MIN                        2

#define IC_ACCOUNT_MANAGER_HOST_ADDRESS         "127.0.0.1:5685"
#define IC_CLOUD_INTERFACE_HOST_ADDRESS         "127.0.0.1:5683"
#define IC_CLOUD_RD_PORT                        "5684"
#define IC_CLOUD_ACCOUNT_PORT                   "5685"
#define IC_CLOUD_MSG_PORT                       "5686"
#define AUTH_PROVIDER                           "github"
#define AUTH_CODE                               "8a3f4b35695b09d875b2"
#define RESOURCE_SERVER_DAT                     "./resource_server.dat"
#define CALLBACK_TIMEOUT                        7

#define IC_RESOURCE_URI_AIRCON                  "/sec/aircon/0"
#define IC_RESOURCE_TYPE_AIRCON                 "x.com.samsung.da.device"
#define IC_RESOURCE_URI_TEMP                    "/temperature/0"
#define IC_RESOURCE_TYPE_TEMP                   "oic.r.temperature"
#define IC_RESOURCE_URI_BSWITCH                 "/power/0"
#define IC_RESOURCE_TYPE_BSWITCH                "oic.r.switch.binary"

#define MAX_SEQUENCE_NUMBER 0xFFFFFF

const string IC_HOST_ADDRESS = "coap+tcp://127.0.0.1:5683";

using namespace std;
using namespace OC;
using namespace OC::OCPlatform;

class ICHelper
{

private:
    static ICHelper* s_ICHelper;
    pthread_t m_helperThread;

public:
    ICHelper(void);
    ~ICHelper(void);
    static string UID;
    static string ACCESS_TOKEN;
    static string GROUP_ID;
    static string GROUP_TYPE;
    static std::vector<std::string> DEVICE_ID;

    static std::mutex s_mutex;
    static bool isServerResponsed;
    static bool isSignedUp;
    static ResourceHandles g_ResourceHandles;
    static OC::OCResource::Ptr m_binaryswitchResource;
    static bool isPostRequestSuccess;
    /**
     * @brief  function for getting helper instance
     * @return helper instance
     */
    static ICHelper* getInstance(void);
    static void icPrintRepresentation(OCRepresentation rep);
    static FILE *readResourceDATFile(const char * /*path*/, const char *mode);
    static void * executeThread(void *threadID);
    static void waitForServerResponse();
    bool isResourceRegistered();
};

#endif
