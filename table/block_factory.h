#ifndef STORAGE_LEVELDB_TABLE_BLOCK_FACTORY_H_
#define STORAGE_LEVELDB_TABLE_BLOCK_FACTORY_H_

#include "leveldb/block.h"

namespace leveldb {

class BlockFactoryImpl : public BlockFactory {
 public:
  Status NewBlockBuilder(const Options* options,
                         std::unique_ptr<BlockBuilder>* res) const override;

  Status NewBlock(const BlockContents& contents,
                  std::unique_ptr<Block>* res) const override;
};

}  // namespace leveldb

#endif  // STORAGE_LEVELDB_TABLE_BLOCK_FACTORY_H_
