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
#define PASS_ID_LENGTH 8
#define COMPANY_ID_LENGTH 6

#define CHAR_CONVERSION_ERROR -1

#define TOKEN_PART_TIME_LENGTH 32

std::uint8_t TimeCodeGenerator::convertHexCharToUINT(char ch){
  if (ch >= '0' && ch <= '9')
        return ch - '0';
  if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
  return CHAR_CONVERSION_ERROR;
}

std::string TimeCodeGenerator::generateTimeCode() {
  uint32_t nValue = countFloor();
  std::string hexedNString =  (boost::format("%x") % nValue).str();
  int8_t neededZeroes = TIMEPART_BYTES - hexedNString.length();
  hexedNString = std::string(neededZeroes, '0').append(hexedNString);
  int8_t neededZeroesPK = PRIVATE_KEY_BYTES - _privateKey.length();
  if(neededZeroesPK>0) {
    _privateKey = std::string(neededZeroesPK, '0').append(_privateKey);
  }
  std::string HMACSHA = hexedNString.append(_privateKey);
  std::string SHA1 = getSHA1(HMACSHA);  
  uint16_t offsetInteger = convertHexCharToUINT(SHA1[39]);
  std::string token = SHA1.substr(offsetInteger, 16);
  uint8_t first4Bits = convertHexCharToUINT(token[0]);
  std::bitset<4> bitsToChange(first4Bits);
  std::bitset<4> mask("0111");
  bitsToChange&=mask;
  token[0]=char(bitsToChange.to_ulong()+'0');
  uint32_t tokenVal = stol(token,0,16);
  tokenVal = tokenVal << TOKEN_PART_TIME_LENGTH;
  std::cout << tokenVal << tokenVal << std::endl;
  
  std::bitset<32> jops(tokenVal);
  std::cout << jops << std::endl;
  //добавляем companyID и passID
  std::string passIDHex = (boost::format("%x") % _PassID).str();
  int8_t neededZeroesPassID = PASS_ID_LENGTH - passIDHex.length();
  if(neededZeroesPassID>0) {
    passIDHex = std::string(neededZeroesPassID, '0').append(passIDHex);
  }
  
  std::string tokenHex =  passIDHex;
  
  tokenHex = tokenHex.append((boost::format("%x") % tokenVal).str());

  std::string companyIDHex = (boost::format("%x") % _CompanyID).str();
  int8_t neededZeroesCompanyID = COMPANY_ID_LENGTH - companyIDHex.length();
  if(neededZeroesCompanyID>0) {
    companyIDHex = std::string(neededZeroesCompanyID, '0').append(companyIDHex);
  }
  tokenHex = tokenHex.append(companyIDHex);
  
  
  std::cout << tokenHex << std::endl;
  
  return "foo";
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
  std::cout << std::time(0) << std::endl; 
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
    // std::cout << std::endl << std::endl <<std::endl <<  std::endl << hash << std::endl << std::endl << std::endl ;
  
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
