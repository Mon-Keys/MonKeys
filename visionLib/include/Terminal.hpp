// Copyright 2021 Monkeys. All rights reserved.
//  __  __                   _  __
// |  \/  |   ___    _ __   | |/ /   ___   _   _   ___
// | |\/| |  / _ \  | '_ \  | ' /   / _ \ | | | | / __|
// | |  | | | (_) | | | | | | . \  |  __/ | |_| | \__ \
// |_|  |_|  \___/  |_| |_| |_|\_\  \___|  \__, | |___/
//                                         |___/

#ifndef VISIONLIB_INCLUDE_TERMINAL_HPP_
#define VISIONLIB_INCLUDE_TERMINAL_HPP_

#include <string>

#include "Verification.hpp"

class Terminal : public Verification {
 public:
  class TempCode {
   private:
    std::string tempCode;
    bool isValid;

   public:
    TempCode();
    explicit TempCode(std::string _tempCode, bool isValid = false);
    ~TempCode();
    TempCode(const TempCode&) = delete;
    TempCode(TempCode&&) = default;
    TempCode& operator=(const TempCode&) = delete;
    TempCode& operator=(TempCode&&) = delete;
    void setTempCode(std::string readTempCode);
    bool isTempCodeValid();
    std::string getTempCode();
  };

  Terminal(TempCode _tempCode, std::string _ID, bool isConnected = false);
  Terminal();
  ~Terminal();
  Terminal(const Terminal&) = delete;
  Terminal(Terminal&&) = delete;
  Terminal& operator=(const Terminal&) = delete;
  Terminal& operator=(Terminal&&) = delete;
  void open();
  std::string readTimeCode();
  bool getIsConnected();
  void establishConnection(const char* url);
  void checkTempCodeValidity();
  void setCompanyID(std::string companyID);
  std::string getCompanyID();
  TempCode getCurrentTempCode();

 private:
  void serverRequest();
  std::string ID;
  TempCode currentTempCode;
  bool isConnected;
  bool isVerification;
};

#endif  // VISIONLIB_INCLUDE_TERMINAL_HPP_
