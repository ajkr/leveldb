#include "table/block_factory.h"

#include "table/block.h"
#include "table/block_builder.h"

namespace leveldb {

Status BlockFactoryImpl::NewBlockBuilder(
    const Options* options, std::unique_ptr<BlockBuilder>* res) const {
  res->reset(new BlockBuilderImpl(options));
  return Status::OK();
}

Status BlockFactoryImpl::NewBlock(const BlockContents& contents,
                                  std::unique_ptr<Block>* res) const {
  res->reset(new BlockImpl(contents));
  return Status::OK();
}

Status NewBlockFactory(std::unique_ptr<BlockFactory>* res) {
  res->reset(new BlockFactoryImpl());
  return Status::OK();
}

}  // namespace leveldb
