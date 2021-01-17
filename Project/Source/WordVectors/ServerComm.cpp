#include "ServerComm.h"

#include <string>
#include <iostream>
#include <sstream>

#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

using namespace WordVectors;

ServerComm::ServerComm(std::string baseEndpoint) {
    analogyEndpoint = baseEndpoint + "/analogy";
    addEndpoint = baseEndpoint + "/add";
    subtractEndpoint = baseEndpoint + "/subtract";
    nearestEndpoint = baseEndpoint + "/nearest";
}

std::string ServerComm::makeRequest(std::string url) {
    curlpp::Cleanup cleanup;
    curlpp::Easy request;
    
    std::cout << "Making request to: " << url << std::endl;

    curlpp::options::Url opURL(url);

    std::ostringstream outputStream;
    curlpp::options::WriteStream opWriteStream(&outputStream);

    request.setOpt(opURL);
    request.setOpt(opWriteStream);

    request.perform();

    std::string response = outputStream.str();

    std::cout << "Got response: " << response << std::endl;

    return response;
}

std::string ServerComm::getNearestWord(std::string word) {
    return makeRequest(nearestEndpoint + "?word=" + word);
}

std::string ServerComm::getWordAddition(std::string firstWord, std::string secondWord) {
    return makeRequest(addEndpoint + "?first=" + firstWord + "&second=" + secondWord);
}

std::string ServerComm::getWordSubtraction(std::string firstWord, std::string secondWord) {
    return makeRequest(subtractEndpoint + "?first=" + firstWord + "&second=" + secondWord);
}

std::string ServerComm::getWordAnalogy(std::string firstWord, std::string comparison, std::string secondWord) {
    return makeRequest(analogyEndpoint + "?first=" + firstWord + "&second=" + comparison + "&third=" + secondWord);
}