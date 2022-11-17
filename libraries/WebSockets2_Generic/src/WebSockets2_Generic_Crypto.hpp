/****************************************************************************************************************************
  WebSockets2_Generic_Crypto.hpp
  For WebSockets2_Generic Library
  
  Based on and modified from Gil Maimon's ArduinoWebsockets library https://github.com/gilmaimon/ArduinoWebsockets
  to support STM32F/L/H/G/WB/MP1, nRF52, SAMD21/SAMD51, SAM DUE, Teensy, RP2040 boards besides ESP8266 and ESP32

  The library provides simple and easy interface for websockets (Client and Server).
  
  Built by Khoi Hoang https://github.com/khoih-prog/Websockets2_Generic
  Licensed under MIT license
  
  Version: 1.13.0

  Version Modified By   Date      Comments
  ------- -----------  ---------- -----------
  1.0.0   K Hoang      14/07/2020 Initial coding/porting to support nRF52 and SAMD21/SAMD51 boards. Add SINRIC/Alexa support
  ...
  1.9.0   K Hoang      30/11/2021 Auto detect ESP32 core version. Fix bug in examples
  1.9.1   K Hoang      17/12/2021 Fix QNEthernet TCP interface
  1.10.0  K Hoang      18/12/2021 Supporting case-insensitive headers, according to RFC2616
  1.10.1  K Hoang      26/02/2022 Reduce QNEthernet latency
  1.10.2  K Hoang      14/03/2022 Fix bug when using QNEthernet staticIP. Add staticIP option to NativeEthernet
  1.10.3  K Hoang      11/04/2022 Use Ethernet_Generic library as default. Support SPI1/SPI2 for RP2040
  1.11.0  K Hoang      08/10/2022 Add support to ESP32 using W5x00 Ethernet
  1.12.0  K Hoang      09/10/2022 Add support to ENC28J60 using EthernetENC or UIPEthernet for all supported boards
  1.12.1  K Hoang      09/10/2022 Fix bug in examples
  1.13.0  K Hoang      11/10/2022 Add support to RP2040W using CYW43439 WiFi
 *****************************************************************************************************************************/

#ifndef _WEBSOCKETS2_GENERIC_CRYPTO_H
#define _WEBSOCKETS2_GENERIC_CRYPTO_H

#pragma once

// KH
#include <WebSockets2_Generic.h>
 
#include <Tiny_Websockets_Generic/internals/wscrypto/crypto.hpp>
#include <Tiny_Websockets_Generic/internals/wscrypto/base64.hpp>
#include <Tiny_Websockets_Generic/internals/wscrypto/sha1.hpp>

#ifndef _WS_CONFIG_NO_TRUE_RANDOMNESS
#include <time.h>
#endif

namespace websockets2_generic
{
  namespace crypto2_generic
  {
    WSString base64Encode(WSString data)
    {
      return internals2_generic::base64_encode(reinterpret_cast<const uint8_t*>(data.c_str()), data.size());
    }
    
    WSString base64Encode(uint8_t* data, size_t len)
    {
      return internals2_generic::base64_encode(reinterpret_cast<const uint8_t*>(data), len);
    }
    
    WSString base64Decode(WSString data)
    {
      return internals2_generic::base64_decode(data);
    }
    
    WSString websocketsHandshakeEncodeKey(WSString key)
    {
      char base64[30];
      internals2_generic::sha1(key.c_str())
      .add("258EAFA5-E914-47DA-95CA-C5AB0DC85B11")
      .finalize()
      .print_base64(base64);
    
      return WSString(base64);
    }
    
    #ifdef _WS_CONFIG_NO_TRUE_RANDOMNESS
    WSString randomBytes(size_t len)
    {
      WSString result;
      result.reserve(len);
    
      for (size_t i = 0; i < len; i++)
      {
        result += "0123456789abcdef"[i % 16];
      }
    
      return result;
    }
    #else
    WSString randomBytes(size_t len)
    {
      static int onlyOnce = []()
      {
        srand(time(NULL));
        return 0;
      }();
    
      WSString result;
      result.reserve(len);
    
      for (size_t i = onlyOnce; i < len; i++)
      {
        result += "0123456789abcdefABCDEFGHIJKLMNOPQRSTUVEXYZ"[rand() % 42];
      }
    
      return result;
    }
    #endif
  }   // namespace crypto2_generic
}     // namespace websockets2_generic

#endif    // _WEBSOCKETS2_GENERIC_CRYPTO_H
