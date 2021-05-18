// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#include "TimeCodeGenerator.hpp"

#define TIMEPART_BYTES 8

#define PRIVATE_KEY_BYTES 20
#define PASS_ID_LENGTH 8
#define COMPANY_ID_LENGTH 6

#define CHAR_CONVERSION_ERROR -1

#define TOKEN_PART_TIME_LENGTH 32

std::uint8_t TimeCodeGenerator::convertHexCharToUINT(char ch) {
  if (ch >= '0' && ch <= '9') return ch - '0';
  if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
  if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
  return CHAR_CONVERSION_ERROR;
}

std::bitset<88> TimeCodeGenerator::convertHexTokenToBitset(
    std::string hexToken) {
  std::string binaryString;
  for (int i = hexToken.length() - 1; i >= 0; i--) {
    uint8_t digit = convertHexCharToUINT(hexToken[i]);

    std::bitset<4> temp(digit);
    binaryString = temp.to_string().append(binaryString);
  }
  std::bitset<88> result(binaryString);
  return result;
}

std::bitset<88> TimeCodeGenerator::tableEncoding(std::bitset<88> binToken) {
  std::bitset<88> result;
  size_t index = 0;
  bool massiv[8][11];
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 11; j++) {
      massiv[i][j] = binToken[index];
      index++;
    }
  }
  // std::cout << binToken.to_string() << std::endl;
  index = 0;
  for (int j = 0; j < 11; j++) {
    for (int i = 0; i < 8; i++) {
      result[index] = massiv[i][j];
      index++;
    }
  }
  // std::cout << result.to_string() << std::endl;
  return result;
}

std::string TimeCodeGenerator::binTokenToHex(std::string hexToken) {
  std::string binToHex, tmp = "0000";
  for (size_t j = 0; j < hexToken.length(); j += 4) {
    tmp = hexToken.substr(j, 4);
    if (!tmp.compare("0000"))
      binToHex += "0";
    else if (!tmp.compare("0001"))
      binToHex += "1";
    else if (!tmp.compare("0010"))
      binToHex += "2";
    else if (!tmp.compare("0011"))
      binToHex += "3";
    else if (!tmp.compare("0100"))
      binToHex += "4";
    else if (!tmp.compare("0101"))
      binToHex += "5";
    else if (!tmp.compare("0110"))
      binToHex += "6";
    else if (!tmp.compare("0111"))
      binToHex += "7";
    else if (!tmp.compare("1000"))
      binToHex += "8";
    else if (!tmp.compare("1001"))
      binToHex += "9";
    else if (!tmp.compare("1010"))
      binToHex += "A";
    else if (!tmp.compare("1011"))
      binToHex += "B";
    else if (!tmp.compare("1100"))
      binToHex += "C";
    else if (!tmp.compare("1101"))
      binToHex += "D";
    else if (!tmp.compare("1110"))
      binToHex += "E";
    else if (!tmp.compare("1111"))
      binToHex += "F";
    else
      continue;
  }
  return binToHex;
}

std::string TimeCodeGenerator::generateTimeCode() {
  uint32_t nValue = countFloor();
  std::string hexedNString = (boost::format("%x") % nValue).str();
  int8_t neededZeroes = TIMEPART_BYTES - hexedNString.length();
  hexedNString = std::string(neededZeroes, '0').append(hexedNString);
  int8_t neededZeroesPK = PRIVATE_KEY_BYTES - _privateKey.length();
  if (neededZeroesPK > 0) {
    _privateKey = std::string(neededZeroesPK, '0').append(_privateKey);
  }
  std::string HMACSHA = hexedNString.append(_privateKey);
  std::string SHA1 = getSHA1(HMACSHA);

  uint16_t offsetInteger = convertHexCharToUINT(SHA1[39]);
  std::string token = SHA1.substr(offsetInteger, 16);
  uint8_t first4Bits = convertHexCharToUINT(token[0]);
  std::bitset<4> bitsToChange(first4Bits);
  std::bitset<4> mask("0111");
  bitsToChange &= mask;
  token[0] = char(bitsToChange.to_ulong() + '0');
  uint32_t tokenVal = stol(token, 0, 16);
  // cppcheck-suppress shiftTooManyBits
  tokenVal = tokenVal << TOKEN_PART_TIME_LENGTH;

  //добавляем companyID и passID
  std::string passIDHex = (boost::format("%x") % _PassID).str();
  int8_t neededZeroesPassID = PASS_ID_LENGTH - passIDHex.length();
  if (neededZeroesPassID > 0) {
    passIDHex = std::string(neededZeroesPassID, '0').append(passIDHex);
  }

  std::string tokenHex = passIDHex;

  tokenHex = tokenHex.append((boost::format("%x") % tokenVal).str());

  std::string companyIDHex = (boost::format("%x") % _CompanyID).str();
  int8_t neededZeroesCompanyID = COMPANY_ID_LENGTH - companyIDHex.length();
  if (neededZeroesCompanyID > 0) {
    companyIDHex = std::string(neededZeroesCompanyID, '0').append(companyIDHex);
  }
  tokenHex = tokenHex.append(companyIDHex);
  // std::cout << convertHexTokenToBitset(tokenHex) << std::endl << std::endl;
  std::bitset<88> encodedHex = tableEncoding(convertHexTokenToBitset(tokenHex));
  // std::cout << convertHexTokenToBitset(tokenHex) << std::endl;  // NOLINT
  // std::cout << "binTokenEncodedGet send: " << encodedHex << std::endl <<
  // std::endl;
  std::string timecode = binTokenToHex(encodedHex.to_string());
  return timecode;
}

TimeCodeGenerator::TimeCodeGenerator() {}

TimeCodeGenerator::~TimeCodeGenerator() {}

std::string TimeCodeGenerator::getHashedOTP() { return ""; }

void TimeCodeGenerator::updateTime() {}

uint64_t TimeCodeGenerator::getTParameter() { return 1; }

// cppcheck-suppress uninitMemberVar
TimeCodeGenerator::TimeCodeGenerator(std::string privateKey, uint64_t PassID,
                                     uint64_t CompanyID,
                                     uint16_t timeInterval) {
  _PassID = PassID;

  _CompanyID = CompanyID;
  _privateKey = privateKey;
  _timeInterval = timeInterval;
}

// cppcheck-suppress uninitMemberVar

uint64_t TimeCodeGenerator::countFloor() {
  return std::time(0) / _timeInterval;
}

std::string TimeCodeGenerator::getSHA1(const std::string& message) {
  boost::uuids::detail::sha1 sha1;
  sha1.process_bytes(message.data(), message.size());
  unsigned hash[5] = {0};
  sha1.get_digest(hash);
  char buf[41] = {0};

  for (int i = 0; i < 5; i++) {
    std::sprintf(buf + (i << 3), "%08x", hash[i]);
  }

  return std::string(buf);
}

TimeCode::TimeCode(std::string timecodeString) {
  if (timecodeString.length() == 22) {
    valid = true;
    timecodeDecoded = decodeTable(convertHexTokenToBitset(timecodeString));
    // std::cout << timecodeDecoded << std::endl;
  } else {
    valid = false;
  }

  // timecodeDecoded[23] = !timecodeDecoded[23];
  // std::cout << timecodeDecoded << std::endl << std::endl << std::endl <<
  // std::endl << std::endl;
}

std::uint8_t TimeCode::convertHexCharToUINT(char ch) {
  if (ch >= '0' && ch <= '9') return ch - '0';
  if (ch >= 'a' && ch <= 'f') return ch - 'a' + 10;
  if (ch >= 'A' && ch <= 'F') return ch - 'A' + 10;
  return CHAR_CONVERSION_ERROR;
}

std::bitset<88> TimeCode::decodeTable(std::bitset<88> binToken) {
  std::bitset<88> result;
  size_t index = 0;
  bool massiv[8][11];
  // std::cout << "binTokenEncodedGet received: " << binToken << std::endl <<
  // std::endl;
  for (int j = 0; j < 11; j++) {
    for (int i = 0; i < 8; i++) {
      massiv[i][j] = binToken[index];
      index++;
    }
  }
  index = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 11; j++) {
      result[index] = massiv[i][j];
      index++;
    }
  }
  return result;
}

std::bitset<88> TimeCode::convertHexTokenToBitset(std::string hexToken) {
  std::string binaryString;
  for (int i = hexToken.length(); i >= 0; i--) {
    uint8_t digit = convertHexCharToUINT(hexToken[i]);
    // std::cout << hexToken[i] << std::endl;
    std::bitset<4> temp(digit);
    binaryString = temp.to_string().append(binaryString);
    // std::cout << binaryString << std::endl;
  }
  // std::cout << std::endl;
  std::bitset<88> result(binaryString);
  // std::cout << result << std:: endl;
  return result;
}

TimeCode::~TimeCode() {}

uint64_t TimeCode::getCompanyID() {
  std::bitset<24> temp;
  for (int i = 0; i < 24; i++) {
    temp[i] = timecodeDecoded[i];
    // std::cout << temp[i];
  }
  // std::cout << std::endl;
  uint64_t result = temp.to_ullong();
  return result;
}

uint64_t TimeCode::getPassID() {
  std::bitset<24> temp;
  for (int i = 56; i < 88; i++) {
    temp[i - 56] = timecodeDecoded[i];
    // std::cout << temp[i-56];
  }
  // std::cout << std::endl;
  uint64_t result = temp.to_ullong();
  return result;
}

bool TimeCode::isValid() { return valid; }
