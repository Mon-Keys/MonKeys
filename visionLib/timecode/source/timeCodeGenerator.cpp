// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "TimeCodeGenerator.hpp"

#include <iostream>

#define TIMEPART_BYTES 8

#define PRIVATE_KEY_BYTES 20

#define CHAR_CONVERSION_ERROR -1

#define TOKEN_PART_TIME_LENGTH 100000000

std::uint8_t TimeCodeGenerator::convertHexCharToUINT(char ch){
  if (ch >= '0' && ch <= '9')
        return ch - '0';
  if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
  return CHAR_CONVERSION_ERROR;
}

std::string TimeCodeGenerator::generateTimeCode() {
  // делаю временную часть для HMAC-SHA1 (8 байт)
  uint32_t nValue = countFloor();
  std::string hexedNString =  (boost::format("%x") % nValue).str();
  std::cout << "HEXED: " << hexedNString << " Length of a string: " << hexedNString.length() << std::endl;
  int8_t neededZeroes = TIMEPART_BYTES - hexedNString.length();
  hexedNString = std::string(neededZeroes, '0').append(hexedNString);
  std::cout << std::endl << "COMPLETED TIMEPART: " << hexedNString << std::endl;
  std::cout << _privateKey << std::endl;
  std::cout << _privateKey.length() << std::endl;
  // private key часть (20 байт)
  std::cout << _privateKey << std::endl;
  int8_t neededZeroesPK = PRIVATE_KEY_BYTES - _privateKey.length();
  if(neededZeroesPK>0) {
    _privateKey = std::string(neededZeroesPK, '0').append(_privateKey);
  }

  std::cout << "COMPLETE PRIVATE KEY(20BYTES): " <<  _privateKey << std::endl;
  std::string HMACSHA = hexedNString.append(_privateKey);
  std::string SHA1 = getSHA1(HMACSHA); 
  std::cout << SHA1 << std::endl; 
  std::cout << "CONVETING CHAR " << SHA1[39] << std::endl; 
  uint16_t offsetInteger = convertHexCharToUINT(SHA1[39]);
  //TRUNCATE
  std::cout << "i am still here" << std::endl;
  std::string token = SHA1.substr(offsetInteger, 8);
  std::cout << "i am still here" << std::endl;
  std::cout << "TOKEN: " << token << std::endl;
  // std::bitset<16> bitToken("a123");
  uint8_t first4Bits = convertHexCharToUINT(token[0]);
  std::bitset<4> bitt(first4Bits);
  std::cout << "FIRST FOUR BITS" << bitt << std::endl;
  std::bitset<4> mask("0111");
  bitt&=mask;
  token[0]=char(bitt.to_ulong()+'0');
  std::cout << "FIRST FOUR BITS" << bitt << std::endl;
  // std::cout << "TOKEN: " << bitToken << std::endl;
  
 //bitToken &= mask;
  // std::cout << "TOKEN: " << bitToken << std::endl;
  std::cout << "TOKEN WITH MASK: " << token << std::endl;

  // std::cout << int(converted) << std::endl;
  uint32_t tokenVal = stoi(token,0,16);
  std::cout << tokenVal << std::endl;
  // std::cout << SHA1 << std::endl << "UNHEXED SHA1: " << unhexedSHA1 << std::endl;
  
  tokenVal = tokenVal % TOKEN_PART_TIME_LENGTH;
  std::cout << tokenVal << std::endl;
  // uint32_t unhexedValue = stoi(hexedNString,0,16);
  // std::cout << "UNHEXED:" <<  unhexedValue << std::endl;
  // std::cout << "hello world check";
  return "foo";
  //std::string toHMAC = hexVal+_privateKey;
  //std::cout << toHMAC << std::endl << getSHA1(toHMAC);
}

TimeCodeGenerator::TimeCodeGenerator() {}

TimeCodeGenerator::~TimeCodeGenerator() {}

std::string TimeCodeGenerator::getHashedOTP() { return ""; }

void TimeCodeGenerator::updateTime() {}

uint64_t TimeCodeGenerator::getTParameter() { return 1; }

// cppcheck-suppress uninitMemberVar
TimeCodeGenerator::TimeCodeGenerator(std::string privateKey, uint64_t PassID,
                                     uint64_t CompanyID, uint16_t timeInterval
                                     ) {
                                       _PassID = PassID;
                                  
                                       _CompanyID = CompanyID;
                                       _privateKey = privateKey;
                                       _timeInterval = timeInterval;
                                     }

// cppcheck-suppress uninitMemberVar

uint64_t TimeCodeGenerator::countFloor(){ 
  return std::time(0)/_timeInterval;
}

TimeCode::TimeCode(std::string timecodeString) {}

TimeCode::~TimeCode() {}

std::string TimeCodeGenerator::getSHA1(const std::string& message){
   boost::uuids::detail::sha1 sha1;
    sha1.process_bytes(message.data(), message.size());
    unsigned hash[5] = {0};
    sha1.get_digest(hash);
    char buf[41] = {0};
    std::cout << std::endl << std::endl <<std::endl <<  std::endl << hash << std::endl << std::endl << std::endl ;
  
    for (int i = 0; i < 5; i++)
    {
        std::sprintf(buf + (i << 3), "%08x", hash[i]);
    }

    return std::string(buf);
 }

uint64_t TimeCode::decodeFrom64(std::string toDecode) {}

uint64_t TimeCode::getCompanyID() {}

uint64_t TimeCode::getPassID() {}

bool TimeCode::isValid() {}

std::string TimeCode::getTimePart() {}
