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
  if (data_writer_ != nullptr) {
    publisher_->delete_datawriter(data_writer_);
  }

  if (publisher_ != nullptr) {
    participant_->delete_publisher(publisher_);
  }

  if (topic_ != nullptr) {
    participant_->delete_topic(topic_);
  }

  eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->delete_participant(participant_);
}

bool TurnsPublisher::Init() {
  turns_message_.data() = 0.2f;

  eprosima::fastdds::dds::DomainParticipantQos turns_qos;
  turns_qos.name("turn_publisher_participant");
  eprosima::fastdds::dds::DomainId_t domain_id = 0;
  participant_ =
      eprosima::fastdds::dds::DomainParticipantFactory::get_instance()->create_participant(domain_id, turns_qos);

  if (participant_ == nullptr) {
    std::cout << "Not able to create participant"
              << std::endl; // TODO Change to use return value in order to inform about this
    return false;
  }

  type_support_.register_type(participant_);
  topic_ =
      participant_->create_topic("rt/ivp/turns", type_support_->getName(), eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);
  std::cout << "Turns publisher type_support name: " << type_support_->getName() << std::endl;
  if (topic_ == nullptr) {
    std::cout << "Not able to create topic"
              << std::endl; // TODO Change to use return value in order to inform about this
    return false;
  }

  publisher_ = participant_->create_publisher(eprosima::fastdds::dds::PUBLISHER_QOS_DEFAULT, nullptr);
  if (publisher_ == nullptr) {
    std::cout << "Not able to create publisher"
              << std::endl; // TODO Change to use return value in order to inform about this
    return false;
  }

  data_writer_ = publisher_->create_datawriter(topic_, eprosima::fastdds::dds::DATAWRITER_QOS_DEFAULT);
  if (data_writer_ == nullptr) {
    std::cout << "Not able to create data writer"
              << std::endl; // TODO Change to use return value in order to inform about this
    return false;
  }
  return true;
}

bool TurnsPublisher::Publish(float turns) {
  if (listener_.matched_ > 0) {
    turns_message_.data(turns);
    data_writer_->write(&turns_message_);
    return true;
  }
  return false;
}

void TurnsPublisher::Run() {
  int Samples = 10;
  uint32_t samples_sent = 0;
  while (samples_sent < Samples) {
    if (Publish(0.01f)) {
      samples_sent++;
      std::cout << "Message: " << turns_message_.data() << " SENT" << std::endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
}
