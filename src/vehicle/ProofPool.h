#ifndef PROOFPOOL_H
#define PROOFPOOL_H

#include "../crypto/ZKProof.h"

#include <cstddef>
#include <cstdint>
#include <unordered_map>

class ProofPool {
public:
    void store(uint32_t index, const ZKProof& proof);
    ZKProof retrieve(uint32_t index) const;
    std::size_t size() const;
    void clear();

private:
    std::unordered_map<uint32_t, ZKProof> proofs_;
};

#endif // PROOFPOOL_H
