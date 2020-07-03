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

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "absl/strings/str_cat.h"
#include "glog/logging.h"
#include "src/raft_instance.h"

ABSL_FLAG(std::string, logdir, "", "Write logs to logdir, instead of stderr");
ABSL_FLAG(uint32_t, port, 50051, "Port for Raft instance to listen on");

using cppraft::RaftInstance;

int main(int argc, char* argv[]) {
  absl::ParseCommandLine(argc, argv);

  // Prepare logging libraries
  const std::string log_dir = absl::GetFlag(FLAGS_logdir);
  if (log_dir.empty()) {
    FLAGS_logtostderr = true;
  } else {
    FLAGS_log_dir = log_dir;
  }
  google::InitGoogleLogging(/*program_name=*/argv[0]);

  RaftInstance raft;
  const std::string server_address =
      absl::StrCat("0.0.0.0:", absl::GetFlag(FLAGS_port));
  raft.StartInsecure(server_address);
  raft.Wait();

  return 0;
}