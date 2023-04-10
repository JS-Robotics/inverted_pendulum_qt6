//
// Created by ICraveSleep on 10-Apr-23.
//

#ifndef INVERTED_PENDULUM_SIMULATION_COMMUNICATION_ROS_PUBLISHER_H_
#define INVERTED_PENDULUM_SIMULATION_COMMUNICATION_ROS_PUBLISHER_H_

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>

enum class RosDdsErrorCodes {
  kNoError = 0,
  kDataWriterNotCreated = 1,
  kPublisherNotCreated = 2,
  kTopicNotCreated = 3,
  kParticipantNotCreated = 4
};

template<class T>
class RosPublisher {
 public:
  RosPublisher(eprosima::fastdds::dds::DomainParticipant *participant, const std::string &topic_name) :
      participant_(participant),
      topic_name_(topic_name),
      publisher_(nullptr),
      topic_(nullptr),
      data_writer_(nullptr),
      type_support_(new T) {

    error_ = RosDdsErrorCodes::kNoError;
  }

  ~RosPublisher() = default;

  RosDdsErrorCodes Init() {

    if (participant_ == nullptr) {
      SeverityUpdateCheck(RosDdsErrorCodes::kParticipantNotCreated);
      return error_;
    }
    type_support_.register_type(participant_);
    topic_ = participant_->create_topic(topic_name_,
                                        type_support_->getName(),
                                        eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);

    if (topic_ == nullptr) {
      SeverityUpdateCheck(RosDdsErrorCodes::kTopicNotCreated);
      return error_;
    }

    publisher_ = participant_->create_publisher(eprosima::fastdds::dds::PUBLISHER_QOS_DEFAULT, nullptr);
    if (publisher_ == nullptr) {
      SeverityUpdateCheck(RosDdsErrorCodes::kPublisherNotCreated);
      return error_;
    }

    data_writer_ = publisher_->create_datawriter(topic_, eprosima::fastdds::dds::DATAWRITER_QOS_DEFAULT);
    if (data_writer_ == nullptr) {
      SeverityUpdateCheck(RosDdsErrorCodes::kDataWriterNotCreated);
      return error_;
    }

    error_ = RosDdsErrorCodes::kNoError;
    return error_;
  }

  void Publish(typename T::type msg) {  // TODO can it become a problem on larger message types if the variable is not passed by reference?
    data_writer_->write(&msg);
  }

  uint32_t GetErrorCode() {
    return static_cast<uint32_t>(error_);
  }

  uint32_t ErrorCodeToUint32(RosDdsErrorCodes error) {
    return static_cast<uint32_t>(error);
  }

 private:
  RosDdsErrorCodes error_;
  const std::string topic_name_;
  eprosima::fastdds::dds::DomainParticipant *participant_;
  eprosima::fastdds::dds::Publisher *publisher_;
  eprosima::fastdds::dds::Topic *topic_;
  eprosima::fastdds::dds::DataWriter *data_writer_;
  eprosima::fastdds::dds::TypeSupport type_support_;

  void SeverityUpdateCheck(RosDdsErrorCodes code) {
    if (code > error_) {
      error_ = code;
    }
  }

};

#endif //INVERTED_PENDULUM_SIMULATION_COMMUNICATION_ROS_PUBLISHER_H_
