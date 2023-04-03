//
// Created by ICraveSleep on 03.04.23.
//

#include "turns_publisher.h"

TurnsPublisher::TurnsPublisher() :
    participant_(nullptr),
    publisher_(nullptr),
    topic_(nullptr),
    data_writer_(nullptr),
    type_support_(new std_msgs::msg::Float32PubSubType()) {

}

TurnsPublisher::~TurnsPublisher() {

}