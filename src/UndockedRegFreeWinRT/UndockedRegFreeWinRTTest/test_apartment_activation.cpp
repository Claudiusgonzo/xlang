#include "pch.h"
#include <iostream>

#include <Windows.h>
#include <roapi.h>
#include <rometadataresolution.h>
#include <windows.foundation.h>
#include <stdio.h>
#include <wrl\client.h>
#include <wrl\wrappers\corewrappers.h>
#include "winrt\TestComponent.h"

#include "../UndockedRegFreeWinRT/extwinrt.h"

using namespace Microsoft::WRL;
using namespace ABI::Windows::Foundation;
using namespace Microsoft::WRL::Wrappers;

TEST_CASE("Undocked Regfree WinRT Activation")
{
    RegFreeWinRTInitializeForTest();


    //SECTION("Cross Apartment MTA Activation")
    //{
    //    winrt::init_apartment(winrt::apartment_type::single_threaded);
    //    winrt::TestComponent::ClassMta c;
    //    REQUIRE(c.Apartment() == APTTYPE_MTA);
    //    winrt::clear_factory_cache();
    //    winrt::uninit_apartment();
    //}
    SECTION("Test Get Metadata File")
    {
        HString result;
        REQUIRE(RoGetMetaDataFile(HStringReference(L"TestComponent").Get(), nullptr, result.GetAddressOf(), nullptr, nullptr) == S_OK);
        REQUIRE(wcsstr(WindowsGetStringRawBuffer(result.Get(), 0), L"TestComponent.winmd") != nullptr);
    }

    RegFreeWinRTUninitializeForTest();
}
