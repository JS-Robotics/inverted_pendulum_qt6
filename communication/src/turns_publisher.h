//
// Created by ICraveSleep on 03.04.23.
//

#ifndef INVERTED_PENDULUM_SIMULATION_COMMUNICATION_SRC_TURNS_PUBLISHER_H_
#define INVERTED_PENDULUM_SIMULATION_COMMUNICATION_SRC_TURNS_PUBLISHER_H_

#include "message_types/Float32/Float32PubSubTypes.h"

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>

class TurnsPublisher {
 public:
  TurnsPublisher();
  ~TurnsPublisher();

  bool Init();
  bool Publish(float turns);
  void Run();

 private:
  std_msgs::msg::Float32 turns_message_;
  eprosima::fastdds::dds::DomainParticipant *participant_;
  eprosima::fastdds::dds::Publisher *publisher_;
  eprosima::fastdds::dds::Topic *topic_;
  eprosima::fastdds::dds::DataWriter *data_writer_;
  eprosima::fastdds::dds::TypeSupport type_support_;

  class PubListener : public eprosima::fastdds::dds::DataWriterListener {
   public:

    PubListener()
        : matched_(0) {
    }

    ~PubListener() override {
    }

    void on_publication_matched(
        eprosima::fastdds::dds::DataWriter *,
        const eprosima::fastdds::dds::PublicationMatchedStatus &info) override {
      if (info.current_count_change == 1) {
        matched_ = info.total_count;
        std::cout << "Publisher matched." << std::endl;
      } else if (info.current_count_change == -1) {
        matched_ = info.total_count;
        std::cout << "Publisher unmatched." << std::endl;
      } else {
        std::cout << info.current_count_change
                  << " is not a valid value for PublicationMatchedStatus current count change." << std::endl;
      }
    }
    std::atomic_int matched_;
  } listener_;

};

#endif //INVERTED_PENDULUM_SIMULATION_COMMUNICATION_SRC_TURNS_PUBLISHER_H_
