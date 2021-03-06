/* Copyright 2016 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
// This class is designed to get accurate profiles for programs

#include "tensorflow/core/platform/hexagon/profile_utils/cpu_utils.h"
#include "tensorflow/core/platform/logging.h"
#include "tensorflow/core/platform/test.h"

namespace tensorflow {
namespace profile_utils {

static constexpr bool DBG = false;

TEST(CpuUtils, CheckGetCurrentCycleClock) {
  static constexpr int LOOP_COUNT = 10;
  const uint64 start_clock_count = CpuUtils::GetCurrentCycleClock();
  CHECK_GT(start_clock_count, 0);
  uint64 prev_clock_count = start_clock_count;
  for (int i = 0; i < LOOP_COUNT; ++i) {
    const uint64 clock_count = CpuUtils::GetCurrentCycleClock();
    CHECK_GE(clock_count, prev_clock_count);
    prev_clock_count = clock_count;
  }
  const uint64 end_clock_count = CpuUtils::GetCurrentCycleClock();
  if (DBG) {
    LOG(INFO) << "start clock = " << start_clock_count;
    LOG(INFO) << "end clock = " << end_clock_count;
    LOG(INFO) << "average clock = "
              << ((end_clock_count - start_clock_count) / LOOP_COUNT);
  }
}

}  // namespace profile_utils
}  // namespace tensorflow
