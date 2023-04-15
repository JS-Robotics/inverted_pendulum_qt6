//
// Created by ICraveSleep on 11-Apr-23.
//

#ifndef INVERTED_PENDULUM_SIMULATION_COMMUNICATION_SRC_ROS_SUBSCRIBER_H_
#define INVERTED_PENDULUM_SIMULATION_COMMUNICATION_SRC_ROS_SUBSCRIBER_H_

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>
#include "message_types/Float32/Float32PubSubTypes.h"

template<class ClassRef, typename PubSub, typename MessageType>
class RosSubscriber : public eprosima::fastdds::dds::DataReaderListener {
 public:
  RosSubscriber(void (ClassRef::*callback)(MessageType),
                eprosima::fastdds::dds::DomainParticipant *participant,
                const std::string &topic_name,
                ClassRef *context) :

      participant_(participant),
      topic_name_(topic_name),
      subscriber_(nullptr),
      topic_(nullptr),
      data_reader_(nullptr),
      type_support_(new PubSub),
      context_(context),
      callback_(callback)
//      listener_(callback, context)
  {

  }

  ~RosSubscriber() {
    if (data_reader_ != nullptr) {
      subscriber_->delete_datareader(data_reader_);
    }
    if (topic_ != nullptr) {
      participant_->delete_topic(topic_);
    }
    if (subscriber_ != nullptr) {
      participant_->delete_subscriber(subscriber_);
    }
  }

  bool Init() {

    if (participant_ == nullptr) {
      return false;
    }

    // Register the Type
    type_support_.register_type(participant_);

    // Create the subscriptions Topic
    topic_ =
        participant_->create_topic(topic_name_, type_support_->getName(), eprosima::fastdds::dds::TOPIC_QOS_DEFAULT);

    if (topic_ == nullptr) {
      return false;
    }

    // Create the Subscriber
    subscriber_ = participant_->create_subscriber(eprosima::fastdds::dds::SUBSCRIBER_QOS_DEFAULT, nullptr);

    if (subscriber_ == nullptr) {
      return false;
    }

    // Create the DataReader
    data_reader_ = subscriber_->create_datareader(topic_, eprosima::fastdds::dds::DATAREADER_QOS_DEFAULT, this);

    if (data_reader_ == nullptr) {
      return false;
    }

    return true;
  }

 private:
//RosDdsErrorCodes error_;
  const std::string topic_name_;
  eprosima::fastdds::dds::DomainParticipant *participant_;
  eprosima::fastdds::dds::Subscriber *subscriber_;
  eprosima::fastdds::dds::Topic *topic_;
  eprosima::fastdds::dds::DataReader *data_reader_;
  eprosima::fastdds::dds::TypeSupport type_support_;
  void (ClassRef::*callback_)(MessageType);
  ClassRef *context_;
  typename PubSub::type message_;

  void on_subscription_matched(
      eprosima::fastdds::dds::DataReader *,
      const eprosima::fastdds::dds::SubscriptionMatchedStatus &info) override {
    if (info.current_count_change == 1) {
      std::cout << "Subscriber matched." << std::endl;
    } else if (info.current_count_change == -1) {
      std::cout << "Subscriber unmatched." << std::endl;
    } else {
      std::cout << info.current_count_change
                << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
    }
  }

  void on_data_available(
      eprosima::fastdds::dds::DataReader *reader) override {
    eprosima::fastdds::dds::SampleInfo info;
    if (reader->take_next_sample(&message_, &info) == ReturnCode_t::RETCODE_OK) {
      if (info.valid_data) {
        (context_->*callback_)(message_);
      }
    }
  }


//  class SubListener : public eprosima::fastdds::dds::DataReaderListener {
//   public:
//
//    SubListener(void (ClassRef::*callback)(MessageType), ClassRef *context) :
//        callback_(callback), context_(context) {
//    }
//
//    ~SubListener() override {
//    }
//
//    void on_subscription_matched(
//        eprosima::fastdds::dds::DataReader *,
//        const eprosima::fastdds::dds::SubscriptionMatchedStatus &info) override {
//      if (info.current_count_change == 1) {
//        std::cout << "Subscriber matched." << std::endl;
//      } else if (info.current_count_change == -1) {
//        std::cout << "Subscriber unmatched." << std::endl;
//      } else {
//        std::cout << info.current_count_change
//                  << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
//      }
//    }
//
//    void on_data_available(
//        eprosima::fastdds::dds::DataReader *reader) override {
//      eprosima::fastdds::dds::SampleInfo info;
//      if (reader->take_next_sample(&message_, &info) == ReturnCode_t::RETCODE_OK) {
//        if (info.valid_data) {
//          context_->*callback_(message_);
//        }
//      }
//    }
//
//    MessageType message_;
//    void (ClassRef::*callback_)(MessageType);
//    ClassRef* context_;
//
//  } listener_;

};

#endif //INVERTED_PENDULUM_SIMULATION_COMMUNICATION_SRC_ROS_SUBSCRIBER_H_
