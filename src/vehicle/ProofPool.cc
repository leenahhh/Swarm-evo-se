#include "ProofPool.h"

void ProofPool::store(uint32_t index, const ZKProof& proof) {
    proofs_[index] = proof;
}

ZKProof ProofPool::retrieve(uint32_t index) const {
    const auto it = proofs_.find(index);
    if (it != proofs_.end()) {
        return it->second;
    }

    ZKProof missing{};
    missing.pseudonymIndex = index;
    missing.valid = false;
    return missing;
}

std::size_t ProofPool::size() const {
    return proofs_.size();
}

void ProofPool::clear() {
    proofs_.clear();
}
