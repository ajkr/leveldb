#ifndef STORAGE_LEVELDB_INCLUDE_BLOCK_H
#define STORAGE_LEVELDB_INCLUDE_BLOCK_H

#include <memory>

#include "leveldb/comparator.h"
#include "leveldb/export.h"
#include "leveldb/iterator.h"
#include "leveldb/options.h"
#include "leveldb/slice.h"

namespace leveldb {

class LEVELDB_EXPORT BlockBuilder {
 public:
  // Reset the contents as if the BlockBuilder was just constructed.
  virtual void Reset() = 0;

  // REQUIRES: Finish() has not been called since the last call to Reset().
  // REQUIRES: key is larger than any previously added key
  virtual void Add(const Slice& key, const Slice& value) = 0;

  // Finish building the block and return a slice that refers to the
  // block contents.  The returned slice will remain valid for the
  // lifetime of this builder or until Reset() is called.
  virtual Slice Finish() = 0;

  // Returns an estimate of the current (uncompressed) size of the block
  // we are building.
  virtual size_t CurrentSizeEstimate() const = 0;

  // Return true iff no entries have been added since the last Reset()
  virtual bool empty() const = 0;

  virtual ~BlockBuilder() {}
};

class LEVELDB_EXPORT Block {
 public:
  virtual size_t size() const = 0;

  virtual Iterator* NewIterator(const Comparator* comparator) = 0;

  virtual ~Block() {}
};

struct BlockContents {
  Slice data;           // Actual contents of data
  bool cachable;        // True iff data can be cached
  bool heap_allocated;  // True iff caller should delete[] data.data()
};

class LEVELDB_EXPORT BlockFactory {
 public:
  virtual Status NewBlockBuilder(const Options* options,
                                 std::unique_ptr<BlockBuilder>* res) const = 0;

  virtual Status NewBlock(const BlockContents& contents,
                          std::unique_ptr<Block>* res) const = 0;

  virtual ~BlockFactory() {}
};

Status NewBlockFactory(std::unique_ptr<BlockFactory>* res);

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_INCLUDE_BLOCK_H
