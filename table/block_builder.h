// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#ifndef STORAGE_LEVELDB_TABLE_BLOCK_BUILDER_H_
#define STORAGE_LEVELDB_TABLE_BLOCK_BUILDER_H_

#include <cstdint>
#include <vector>

#include "leveldb/block.h"
#include "leveldb/slice.h"

namespace leveldb {

struct Options;

class BlockBuilderImpl : public BlockBuilder {
 public:
  explicit BlockBuilderImpl(const Options* options);

  BlockBuilderImpl(const BlockBuilderImpl&) = delete;
  BlockBuilderImpl& operator=(const BlockBuilderImpl&) = delete;

  // Reset the contents as if the BlockBuilderImpl was just constructed.
  void Reset() override;

  // REQUIRES: Finish() has not been called since the last call to Reset().
  // REQUIRES: key is larger than any previously added key
  void Add(const Slice& key, const Slice& value) override;

  // Finish building the block and return a slice that refers to the
  // block contents.  The returned slice will remain valid for the
  // lifetime of this builder or until Reset() is called.
  Slice Finish() override;

  // Returns an estimate of the current (uncompressed) size of the block
  // we are building.
  size_t CurrentSizeEstimate() const override;

  // Return true iff no entries have been added since the last Reset()
  bool empty() const override { return buffer_.empty(); }

 private:
  const Options* options_;
  std::string buffer_;              // Destination buffer
  std::vector<uint32_t> restarts_;  // Restart points
  int counter_;                     // Number of entries emitted since restart
  bool finished_;                   // Has Finish() been called?
  std::string last_key_;
};

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_TABLE_BLOCK_BUILDER_H_
