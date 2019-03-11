#pragma once

#include <torch/csrc/WindowsTorchApiMacro.h>
#include <torch/csrc/jit/testing/file_check.h>

namespace torch {
namespace jit {
namespace testing {

struct FileCheckImpl;

struct FileCheck {
 public:
  TORCH_API explicit FileCheck();
  TORCH_API ~FileCheck();

  // Run FileCheck against test string
  TORCH_API void run(const std::string& test_string);

  // Checks that the string occurs, starting at the end of the most recent match
  TORCH_API FileCheck* check(const std::string& str);

  // Checks that the string does not occur between the previous match and next
  // match. Consecutive check_nots test against the same previous match and next
  // match
  TORCH_API FileCheck* check_not(const std::string& str);

  // Checks that the string occurs on the same line as the previous match
  TORCH_API FileCheck* check_same(const std::string& str);

  // Checks that the string occurs on the line immediately following the
  // previous match
  TORCH_API FileCheck* check_next(const std::string& str);

  // Checks that the string occurs count number of times, starting at the end
  // of the previous match. If exactly is true, checks that there are exactly
  // count many matches
  TORCH_API FileCheck* check_count(
      const std::string& str,
      size_t count,
      bool exactly = false);

  // A series of consecutive check_dags get turned into a group of checks
  // which can appear in any order relative to each other. The checks begin
  // at the end of the previous match, and the match for the check_dag group
  // is the minimum match of all individual checks to the maximum match of all
  // individual checks.
  TORCH_API FileCheck* check_dag(const std::string& str);

  // reset checks
  TORCH_API void reset();

 private:
  bool has_run = false;
  std::unique_ptr<FileCheckImpl> fcImpl;
};
} // namespace testing
} // namespace jit
} // namespace torch
