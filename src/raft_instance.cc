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

#include "src/raft_instance.h"

#include <glog/logging.h>

namespace cppraft {

using grpc::Server;
using grpc::ServerBuilder;

void RaftInstance::Start(const std::string& server_address,
                         std::shared_ptr<grpc::ServerCredentials> credentials) {
  RaftImpl raft_impl;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, credentials);
  builder.RegisterService(&raft_impl);
  server_ = builder.BuildAndStart();
  LOG(INFO) << "Raft instance listening on " << server_address;
}
}  // namespace cppraft