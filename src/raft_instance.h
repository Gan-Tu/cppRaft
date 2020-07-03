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

#include <memory>
#include <string>

#include "grpcpp/grpcpp.h"
#include "src/raft_impl.h"

namespace cppraft {

class RaftInstance {
 public:
  // Start the Raft instance and listen on |server_address| using |credentials|.
  void Start(const std::string& server_address,
             const std::shared_ptr<grpc::ServerCredentials>& credentials);

  // Similar to Start(...), but use grpc insecure credentials as default.
  void StartInsecure(const std::string& server_address);

  // Block until process is killed
  void Wait();

  ~RaftInstance() {
    if (server_ != nullptr) {
      server_->Shutdown();
    }
  }

 private:
  std::unique_ptr<grpc::Server> server_ = nullptr;
};
}  // namespace cppraft

#endif  // CPPRAFT_RAFT_INSTANCE_H_