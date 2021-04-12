//
// Created by Monkeys on 11.04.2021.
//


#include "../include/Logger.hpp"

unsigned int Database::OpenLog(){

}

unsigned int Database::CloseLog(){

}

unsigned int Database::WriteLog(const char* errorMessage){

}

unsigned int LogFile::OpenLog(){

}

unsigned int LogFile::CloseLog(){

}

unsigned int LogFile::WriteLog(const char* errorMessage){
    
}

void Logger::CloseLog(IWriteToLog &Log){
    
}

void Logger::OpenLog(IWriteToLog &Log){
    
}


void Logger::WriteLog(IWriteToLog &Log, std::string text){
    
}