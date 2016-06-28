/*
 The MIT License (MIT)

 Copyright (c) [2016] [BTC.COM]

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 */
#ifndef KAFKA_H_
#define KAFKA_H_

#include "Common.h"

#include <librdkafka/rdkafka.h>

#define KAFKA_TOPIC_RAWGBT        "RawGbt2"
#define KAFKA_TOPIC_STRATUM_JOB   "StratumJob"
#define KAFKA_TOPIC_SOLVED_SHARE  "SolvedShare"

#define KAFKA_GROUP_JOBMAKER      "g.JobMaker"

///////////////////////////////// KafkaConsumer ////////////////////////////////
class KafkaConsumer {
  string brokers_;
  string topicStr_;
  string groupId_;
  int    partition_;

  rd_kafka_conf_t  *conf_;
  rd_kafka_t       *consumer_;
  rd_kafka_topic_t *topic_;

public:
  KafkaConsumer(const char *brokers, const char *topic,
                int partition, const string &groupId);
  ~KafkaConsumer();

  bool checkAlive();

  //
  // offset:
  //     RD_KAFKA_OFFSET_BEGINNING
  //     RD_KAFKA_OFFSET_END
  //     RD_KAFKA_OFFSET_STORED
  //     RD_KAFKA_OFFSET_TAIL(CNT)
  //
  bool setup(int64_t offset);
  //
  // don't forget to call rd_kafka_message_destroy() after consumer()
  //
  rd_kafka_message_t *consumer(int timeout_ms);
};


///////////////////////////////// KafkaProducer ////////////////////////////////
class KafkaProducer {
  string brokers_;
  string topicStr_;
  int    partition_;

  rd_kafka_conf_t  *conf_;
  rd_kafka_t       *producer_;
  rd_kafka_topic_t *topic_;

public:
  KafkaProducer(const char *brokers, const char *topic, int partition);
  ~KafkaProducer();

  bool setup();
  bool checkAlive();
  void produce(const void *payload, size_t len);
};

#endif
