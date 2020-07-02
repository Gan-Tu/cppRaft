// Copyright 2020 Gan Tu All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef CPPRAFT_RAFT_INSTANCE_H_
#define CPPRAFT_RAFT_INSTANCE_H_

#include "grpcpp/grpcpp.h"
#include "src/consensus.grpc.pb.h"

namespace cppraft {

class RaftInstance final : public RaftConsensusService::Service {
  // Handle a request from the leader for appending log entries
  // This is also how we communicate with leader for heartbeat monitoring
  grpc::Status AppendEntries(grpc::ServerContext* content,
                             const AppendEntriesRequest* request,
                             AppendEntriesReply* reply) override;

  // Handle a request from a candidate for gathering leader election votes
  grpc::Status RequestVote(grpc::ServerContext* content,
                           const RequestVoteRequest* request,
                           RequestVoteReply* reply) override;
};

}  // namespace cppraft

#endif  // CPPRAFT_RAFT_INSTANCE_H_