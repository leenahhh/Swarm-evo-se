//
// Generated file, do not edit! Created by opp_msgtool 6.1 from src/protocol/Messages.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "Messages_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

namespace swarmevose {

Register_Class(CandidateMsg)

CandidateMsg::CandidateMsg(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

CandidateMsg::CandidateMsg(const CandidateMsg& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

CandidateMsg::~CandidateMsg()
{
}

CandidateMsg& CandidateMsg::operator=(const CandidateMsg& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void CandidateMsg::copy(const CandidateMsg& other)
{
    this->senderId = other.senderId;
    this->candidatePseudonym = other.candidatePseudonym;
    this->zkProofSerialized = other.zkProofSerialized;
    this->epoch = other.epoch;
    this->locationX = other.locationX;
    this->locationY = other.locationY;
    this->h0 = other.h0;
    this->isMalicious_ = other.isMalicious_;
}

void CandidateMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->senderId);
    doParsimPacking(b,this->candidatePseudonym);
    doParsimPacking(b,this->zkProofSerialized);
    doParsimPacking(b,this->epoch);
    doParsimPacking(b,this->locationX);
    doParsimPacking(b,this->locationY);
    doParsimPacking(b,this->h0);
    doParsimPacking(b,this->isMalicious_);
}

void CandidateMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->senderId);
    doParsimUnpacking(b,this->candidatePseudonym);
    doParsimUnpacking(b,this->zkProofSerialized);
    doParsimUnpacking(b,this->epoch);
    doParsimUnpacking(b,this->locationX);
    doParsimUnpacking(b,this->locationY);
    doParsimUnpacking(b,this->h0);
    doParsimUnpacking(b,this->isMalicious_);
}

const char * CandidateMsg::getSenderId() const
{
    return this->senderId.c_str();
}

void CandidateMsg::setSenderId(const char * senderId)
{
    this->senderId = senderId;
}

const char * CandidateMsg::getCandidatePseudonym() const
{
    return this->candidatePseudonym.c_str();
}

void CandidateMsg::setCandidatePseudonym(const char * candidatePseudonym)
{
    this->candidatePseudonym = candidatePseudonym;
}

const char * CandidateMsg::getZkProofSerialized() const
{
    return this->zkProofSerialized.c_str();
}

void CandidateMsg::setZkProofSerialized(const char * zkProofSerialized)
{
    this->zkProofSerialized = zkProofSerialized;
}

unsigned int CandidateMsg::getEpoch() const
{
    return this->epoch;
}

void CandidateMsg::setEpoch(unsigned int epoch)
{
    this->epoch = epoch;
}

double CandidateMsg::getLocationX() const
{
    return this->locationX;
}

void CandidateMsg::setLocationX(double locationX)
{
    this->locationX = locationX;
}

double CandidateMsg::getLocationY() const
{
    return this->locationY;
}

void CandidateMsg::setLocationY(double locationY)
{
    this->locationY = locationY;
}

const char * CandidateMsg::getH0() const
{
    return this->h0.c_str();
}

void CandidateMsg::setH0(const char * h0)
{
    this->h0 = h0;
}

bool CandidateMsg::isMalicious() const
{
    return this->isMalicious_;
}

void CandidateMsg::setIsMalicious(bool isMalicious)
{
    this->isMalicious_ = isMalicious;
}

class CandidateMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_senderId,
        FIELD_candidatePseudonym,
        FIELD_zkProofSerialized,
        FIELD_epoch,
        FIELD_locationX,
        FIELD_locationY,
        FIELD_h0,
        FIELD_isMalicious,
    };
  public:
    CandidateMsgDescriptor();
    virtual ~CandidateMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(CandidateMsgDescriptor)

CandidateMsgDescriptor::CandidateMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(swarmevose::CandidateMsg)), "veins::BaseFrame1609_4")
{
    propertyNames = nullptr;
}

CandidateMsgDescriptor::~CandidateMsgDescriptor()
{
    delete[] propertyNames;
}

bool CandidateMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<CandidateMsg *>(obj)!=nullptr;
}

const char **CandidateMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *CandidateMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int CandidateMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 8+base->getFieldCount() : 8;
}

unsigned int CandidateMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_senderId
        FD_ISEDITABLE,    // FIELD_candidatePseudonym
        FD_ISEDITABLE,    // FIELD_zkProofSerialized
        FD_ISEDITABLE,    // FIELD_epoch
        FD_ISEDITABLE,    // FIELD_locationX
        FD_ISEDITABLE,    // FIELD_locationY
        FD_ISEDITABLE,    // FIELD_h0
        FD_ISEDITABLE,    // FIELD_isMalicious
    };
    return (field >= 0 && field < 8) ? fieldTypeFlags[field] : 0;
}

const char *CandidateMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderId",
        "candidatePseudonym",
        "zkProofSerialized",
        "epoch",
        "locationX",
        "locationY",
        "h0",
        "isMalicious",
    };
    return (field >= 0 && field < 8) ? fieldNames[field] : nullptr;
}

int CandidateMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "senderId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "candidatePseudonym") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "zkProofSerialized") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "epoch") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "locationX") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "locationY") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "h0") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "isMalicious") == 0) return baseIndex + 7;
    return base ? base->findField(fieldName) : -1;
}

const char *CandidateMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_senderId
        "string",    // FIELD_candidatePseudonym
        "string",    // FIELD_zkProofSerialized
        "unsigned int",    // FIELD_epoch
        "double",    // FIELD_locationX
        "double",    // FIELD_locationY
        "string",    // FIELD_h0
        "bool",    // FIELD_isMalicious
    };
    return (field >= 0 && field < 8) ? fieldTypeStrings[field] : nullptr;
}

const char **CandidateMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *CandidateMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int CandidateMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    CandidateMsg *pp = omnetpp::fromAnyPtr<CandidateMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void CandidateMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    CandidateMsg *pp = omnetpp::fromAnyPtr<CandidateMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'CandidateMsg'", field);
    }
}

const char *CandidateMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    CandidateMsg *pp = omnetpp::fromAnyPtr<CandidateMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string CandidateMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    CandidateMsg *pp = omnetpp::fromAnyPtr<CandidateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: return oppstring2string(pp->getSenderId());
        case FIELD_candidatePseudonym: return oppstring2string(pp->getCandidatePseudonym());
        case FIELD_zkProofSerialized: return oppstring2string(pp->getZkProofSerialized());
        case FIELD_epoch: return ulong2string(pp->getEpoch());
        case FIELD_locationX: return double2string(pp->getLocationX());
        case FIELD_locationY: return double2string(pp->getLocationY());
        case FIELD_h0: return oppstring2string(pp->getH0());
        case FIELD_isMalicious: return bool2string(pp->isMalicious());
        default: return "";
    }
}

void CandidateMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CandidateMsg *pp = omnetpp::fromAnyPtr<CandidateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: pp->setSenderId((value)); break;
        case FIELD_candidatePseudonym: pp->setCandidatePseudonym((value)); break;
        case FIELD_zkProofSerialized: pp->setZkProofSerialized((value)); break;
        case FIELD_epoch: pp->setEpoch(string2ulong(value)); break;
        case FIELD_locationX: pp->setLocationX(string2double(value)); break;
        case FIELD_locationY: pp->setLocationY(string2double(value)); break;
        case FIELD_h0: pp->setH0((value)); break;
        case FIELD_isMalicious: pp->setIsMalicious(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CandidateMsg'", field);
    }
}

omnetpp::cValue CandidateMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    CandidateMsg *pp = omnetpp::fromAnyPtr<CandidateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: return pp->getSenderId();
        case FIELD_candidatePseudonym: return pp->getCandidatePseudonym();
        case FIELD_zkProofSerialized: return pp->getZkProofSerialized();
        case FIELD_epoch: return (omnetpp::intval_t)(pp->getEpoch());
        case FIELD_locationX: return pp->getLocationX();
        case FIELD_locationY: return pp->getLocationY();
        case FIELD_h0: return pp->getH0();
        case FIELD_isMalicious: return pp->isMalicious();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'CandidateMsg' as cValue -- field index out of range?", field);
    }
}

void CandidateMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    CandidateMsg *pp = omnetpp::fromAnyPtr<CandidateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: pp->setSenderId(value.stringValue()); break;
        case FIELD_candidatePseudonym: pp->setCandidatePseudonym(value.stringValue()); break;
        case FIELD_zkProofSerialized: pp->setZkProofSerialized(value.stringValue()); break;
        case FIELD_epoch: pp->setEpoch(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_locationX: pp->setLocationX(value.doubleValue()); break;
        case FIELD_locationY: pp->setLocationY(value.doubleValue()); break;
        case FIELD_h0: pp->setH0(value.stringValue()); break;
        case FIELD_isMalicious: pp->setIsMalicious(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CandidateMsg'", field);
    }
}

const char *CandidateMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr CandidateMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    CandidateMsg *pp = omnetpp::fromAnyPtr<CandidateMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void CandidateMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    CandidateMsg *pp = omnetpp::fromAnyPtr<CandidateMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'CandidateMsg'", field);
    }
}

Register_Class(PartialSigMsg)

PartialSigMsg::PartialSigMsg(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

PartialSigMsg::PartialSigMsg(const PartialSigMsg& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

PartialSigMsg::~PartialSigMsg()
{
}

PartialSigMsg& PartialSigMsg::operator=(const PartialSigMsg& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void PartialSigMsg::copy(const PartialSigMsg& other)
{
    this->validatorId = other.validatorId;
    this->targetPseudonym = other.targetPseudonym;
    this->sigBytes = other.sigBytes;
    this->epoch = other.epoch;
    this->validatorH0 = other.validatorH0;
    this->accepted = other.accepted;
    this->rejectReason = other.rejectReason;
}

void PartialSigMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->validatorId);
    doParsimPacking(b,this->targetPseudonym);
    doParsimPacking(b,this->sigBytes);
    doParsimPacking(b,this->epoch);
    doParsimPacking(b,this->validatorH0);
    doParsimPacking(b,this->accepted);
    doParsimPacking(b,this->rejectReason);
}

void PartialSigMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->validatorId);
    doParsimUnpacking(b,this->targetPseudonym);
    doParsimUnpacking(b,this->sigBytes);
    doParsimUnpacking(b,this->epoch);
    doParsimUnpacking(b,this->validatorH0);
    doParsimUnpacking(b,this->accepted);
    doParsimUnpacking(b,this->rejectReason);
}

const char * PartialSigMsg::getValidatorId() const
{
    return this->validatorId.c_str();
}

void PartialSigMsg::setValidatorId(const char * validatorId)
{
    this->validatorId = validatorId;
}

const char * PartialSigMsg::getTargetPseudonym() const
{
    return this->targetPseudonym.c_str();
}

void PartialSigMsg::setTargetPseudonym(const char * targetPseudonym)
{
    this->targetPseudonym = targetPseudonym;
}

const char * PartialSigMsg::getSigBytes() const
{
    return this->sigBytes.c_str();
}

void PartialSigMsg::setSigBytes(const char * sigBytes)
{
    this->sigBytes = sigBytes;
}

unsigned int PartialSigMsg::getEpoch() const
{
    return this->epoch;
}

void PartialSigMsg::setEpoch(unsigned int epoch)
{
    this->epoch = epoch;
}

const char * PartialSigMsg::getValidatorH0() const
{
    return this->validatorH0.c_str();
}

void PartialSigMsg::setValidatorH0(const char * validatorH0)
{
    this->validatorH0 = validatorH0;
}

bool PartialSigMsg::getAccepted() const
{
    return this->accepted;
}

void PartialSigMsg::setAccepted(bool accepted)
{
    this->accepted = accepted;
}

const char * PartialSigMsg::getRejectReason() const
{
    return this->rejectReason.c_str();
}

void PartialSigMsg::setRejectReason(const char * rejectReason)
{
    this->rejectReason = rejectReason;
}

class PartialSigMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_validatorId,
        FIELD_targetPseudonym,
        FIELD_sigBytes,
        FIELD_epoch,
        FIELD_validatorH0,
        FIELD_accepted,
        FIELD_rejectReason,
    };
  public:
    PartialSigMsgDescriptor();
    virtual ~PartialSigMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(PartialSigMsgDescriptor)

PartialSigMsgDescriptor::PartialSigMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(swarmevose::PartialSigMsg)), "veins::BaseFrame1609_4")
{
    propertyNames = nullptr;
}

PartialSigMsgDescriptor::~PartialSigMsgDescriptor()
{
    delete[] propertyNames;
}

bool PartialSigMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<PartialSigMsg *>(obj)!=nullptr;
}

const char **PartialSigMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *PartialSigMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int PartialSigMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int PartialSigMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_validatorId
        FD_ISEDITABLE,    // FIELD_targetPseudonym
        FD_ISEDITABLE,    // FIELD_sigBytes
        FD_ISEDITABLE,    // FIELD_epoch
        FD_ISEDITABLE,    // FIELD_validatorH0
        FD_ISEDITABLE,    // FIELD_accepted
        FD_ISEDITABLE,    // FIELD_rejectReason
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *PartialSigMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "validatorId",
        "targetPseudonym",
        "sigBytes",
        "epoch",
        "validatorH0",
        "accepted",
        "rejectReason",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int PartialSigMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "validatorId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "targetPseudonym") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sigBytes") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "epoch") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "validatorH0") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "accepted") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "rejectReason") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *PartialSigMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_validatorId
        "string",    // FIELD_targetPseudonym
        "string",    // FIELD_sigBytes
        "unsigned int",    // FIELD_epoch
        "string",    // FIELD_validatorH0
        "bool",    // FIELD_accepted
        "string",    // FIELD_rejectReason
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **PartialSigMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *PartialSigMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int PartialSigMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    PartialSigMsg *pp = omnetpp::fromAnyPtr<PartialSigMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void PartialSigMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    PartialSigMsg *pp = omnetpp::fromAnyPtr<PartialSigMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'PartialSigMsg'", field);
    }
}

const char *PartialSigMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    PartialSigMsg *pp = omnetpp::fromAnyPtr<PartialSigMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string PartialSigMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    PartialSigMsg *pp = omnetpp::fromAnyPtr<PartialSigMsg>(object); (void)pp;
    switch (field) {
        case FIELD_validatorId: return oppstring2string(pp->getValidatorId());
        case FIELD_targetPseudonym: return oppstring2string(pp->getTargetPseudonym());
        case FIELD_sigBytes: return oppstring2string(pp->getSigBytes());
        case FIELD_epoch: return ulong2string(pp->getEpoch());
        case FIELD_validatorH0: return oppstring2string(pp->getValidatorH0());
        case FIELD_accepted: return bool2string(pp->getAccepted());
        case FIELD_rejectReason: return oppstring2string(pp->getRejectReason());
        default: return "";
    }
}

void PartialSigMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PartialSigMsg *pp = omnetpp::fromAnyPtr<PartialSigMsg>(object); (void)pp;
    switch (field) {
        case FIELD_validatorId: pp->setValidatorId((value)); break;
        case FIELD_targetPseudonym: pp->setTargetPseudonym((value)); break;
        case FIELD_sigBytes: pp->setSigBytes((value)); break;
        case FIELD_epoch: pp->setEpoch(string2ulong(value)); break;
        case FIELD_validatorH0: pp->setValidatorH0((value)); break;
        case FIELD_accepted: pp->setAccepted(string2bool(value)); break;
        case FIELD_rejectReason: pp->setRejectReason((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PartialSigMsg'", field);
    }
}

omnetpp::cValue PartialSigMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    PartialSigMsg *pp = omnetpp::fromAnyPtr<PartialSigMsg>(object); (void)pp;
    switch (field) {
        case FIELD_validatorId: return pp->getValidatorId();
        case FIELD_targetPseudonym: return pp->getTargetPseudonym();
        case FIELD_sigBytes: return pp->getSigBytes();
        case FIELD_epoch: return (omnetpp::intval_t)(pp->getEpoch());
        case FIELD_validatorH0: return pp->getValidatorH0();
        case FIELD_accepted: return pp->getAccepted();
        case FIELD_rejectReason: return pp->getRejectReason();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'PartialSigMsg' as cValue -- field index out of range?", field);
    }
}

void PartialSigMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    PartialSigMsg *pp = omnetpp::fromAnyPtr<PartialSigMsg>(object); (void)pp;
    switch (field) {
        case FIELD_validatorId: pp->setValidatorId(value.stringValue()); break;
        case FIELD_targetPseudonym: pp->setTargetPseudonym(value.stringValue()); break;
        case FIELD_sigBytes: pp->setSigBytes(value.stringValue()); break;
        case FIELD_epoch: pp->setEpoch(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_validatorH0: pp->setValidatorH0(value.stringValue()); break;
        case FIELD_accepted: pp->setAccepted(value.boolValue()); break;
        case FIELD_rejectReason: pp->setRejectReason(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PartialSigMsg'", field);
    }
}

const char *PartialSigMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr PartialSigMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    PartialSigMsg *pp = omnetpp::fromAnyPtr<PartialSigMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void PartialSigMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    PartialSigMsg *pp = omnetpp::fromAnyPtr<PartialSigMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'PartialSigMsg'", field);
    }
}

Register_Class(SafetyMsg)

SafetyMsg::SafetyMsg(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

SafetyMsg::SafetyMsg(const SafetyMsg& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

SafetyMsg::~SafetyMsg()
{
}

SafetyMsg& SafetyMsg::operator=(const SafetyMsg& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void SafetyMsg::copy(const SafetyMsg& other)
{
    this->senderId = other.senderId;
    this->speed = other.speed;
    this->posX = other.posX;
    this->posY = other.posY;
    this->heading = other.heading;
    this->eventType = other.eventType;
    this->messageSignature = other.messageSignature;
    this->sigmaSerialized = other.sigmaSerialized;
    this->filterEpochAtSigning = other.filterEpochAtSigning;
    this->clusterId = other.clusterId;
    this->isMalicious_ = other.isMalicious_;
}

void SafetyMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->senderId);
    doParsimPacking(b,this->speed);
    doParsimPacking(b,this->posX);
    doParsimPacking(b,this->posY);
    doParsimPacking(b,this->heading);
    doParsimPacking(b,this->eventType);
    doParsimPacking(b,this->messageSignature);
    doParsimPacking(b,this->sigmaSerialized);
    doParsimPacking(b,this->filterEpochAtSigning);
    doParsimPacking(b,this->clusterId);
    doParsimPacking(b,this->isMalicious_);
}

void SafetyMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->senderId);
    doParsimUnpacking(b,this->speed);
    doParsimUnpacking(b,this->posX);
    doParsimUnpacking(b,this->posY);
    doParsimUnpacking(b,this->heading);
    doParsimUnpacking(b,this->eventType);
    doParsimUnpacking(b,this->messageSignature);
    doParsimUnpacking(b,this->sigmaSerialized);
    doParsimUnpacking(b,this->filterEpochAtSigning);
    doParsimUnpacking(b,this->clusterId);
    doParsimUnpacking(b,this->isMalicious_);
}

const char * SafetyMsg::getSenderId() const
{
    return this->senderId.c_str();
}

void SafetyMsg::setSenderId(const char * senderId)
{
    this->senderId = senderId;
}

double SafetyMsg::getSpeed() const
{
    return this->speed;
}

void SafetyMsg::setSpeed(double speed)
{
    this->speed = speed;
}

double SafetyMsg::getPosX() const
{
    return this->posX;
}

void SafetyMsg::setPosX(double posX)
{
    this->posX = posX;
}

double SafetyMsg::getPosY() const
{
    return this->posY;
}

void SafetyMsg::setPosY(double posY)
{
    this->posY = posY;
}

double SafetyMsg::getHeading() const
{
    return this->heading;
}

void SafetyMsg::setHeading(double heading)
{
    this->heading = heading;
}

const char * SafetyMsg::getEventType() const
{
    return this->eventType.c_str();
}

void SafetyMsg::setEventType(const char * eventType)
{
    this->eventType = eventType;
}

const char * SafetyMsg::getMessageSignature() const
{
    return this->messageSignature.c_str();
}

void SafetyMsg::setMessageSignature(const char * messageSignature)
{
    this->messageSignature = messageSignature;
}

const char * SafetyMsg::getSigmaSerialized() const
{
    return this->sigmaSerialized.c_str();
}

void SafetyMsg::setSigmaSerialized(const char * sigmaSerialized)
{
    this->sigmaSerialized = sigmaSerialized;
}

unsigned int SafetyMsg::getFilterEpochAtSigning() const
{
    return this->filterEpochAtSigning;
}

void SafetyMsg::setFilterEpochAtSigning(unsigned int filterEpochAtSigning)
{
    this->filterEpochAtSigning = filterEpochAtSigning;
}

const char * SafetyMsg::getClusterId() const
{
    return this->clusterId.c_str();
}

void SafetyMsg::setClusterId(const char * clusterId)
{
    this->clusterId = clusterId;
}

bool SafetyMsg::isMalicious() const
{
    return this->isMalicious_;
}

void SafetyMsg::setIsMalicious(bool isMalicious)
{
    this->isMalicious_ = isMalicious;
}

class SafetyMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_senderId,
        FIELD_speed,
        FIELD_posX,
        FIELD_posY,
        FIELD_heading,
        FIELD_eventType,
        FIELD_messageSignature,
        FIELD_sigmaSerialized,
        FIELD_filterEpochAtSigning,
        FIELD_clusterId,
        FIELD_isMalicious,
    };
  public:
    SafetyMsgDescriptor();
    virtual ~SafetyMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(SafetyMsgDescriptor)

SafetyMsgDescriptor::SafetyMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(swarmevose::SafetyMsg)), "veins::BaseFrame1609_4")
{
    propertyNames = nullptr;
}

SafetyMsgDescriptor::~SafetyMsgDescriptor()
{
    delete[] propertyNames;
}

bool SafetyMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SafetyMsg *>(obj)!=nullptr;
}

const char **SafetyMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SafetyMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SafetyMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 11+base->getFieldCount() : 11;
}

unsigned int SafetyMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_senderId
        FD_ISEDITABLE,    // FIELD_speed
        FD_ISEDITABLE,    // FIELD_posX
        FD_ISEDITABLE,    // FIELD_posY
        FD_ISEDITABLE,    // FIELD_heading
        FD_ISEDITABLE,    // FIELD_eventType
        FD_ISEDITABLE,    // FIELD_messageSignature
        FD_ISEDITABLE,    // FIELD_sigmaSerialized
        FD_ISEDITABLE,    // FIELD_filterEpochAtSigning
        FD_ISEDITABLE,    // FIELD_clusterId
        FD_ISEDITABLE,    // FIELD_isMalicious
    };
    return (field >= 0 && field < 11) ? fieldTypeFlags[field] : 0;
}

const char *SafetyMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderId",
        "speed",
        "posX",
        "posY",
        "heading",
        "eventType",
        "messageSignature",
        "sigmaSerialized",
        "filterEpochAtSigning",
        "clusterId",
        "isMalicious",
    };
    return (field >= 0 && field < 11) ? fieldNames[field] : nullptr;
}

int SafetyMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "senderId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "speed") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "posX") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "posY") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "heading") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "eventType") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "messageSignature") == 0) return baseIndex + 6;
    if (strcmp(fieldName, "sigmaSerialized") == 0) return baseIndex + 7;
    if (strcmp(fieldName, "filterEpochAtSigning") == 0) return baseIndex + 8;
    if (strcmp(fieldName, "clusterId") == 0) return baseIndex + 9;
    if (strcmp(fieldName, "isMalicious") == 0) return baseIndex + 10;
    return base ? base->findField(fieldName) : -1;
}

const char *SafetyMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_senderId
        "double",    // FIELD_speed
        "double",    // FIELD_posX
        "double",    // FIELD_posY
        "double",    // FIELD_heading
        "string",    // FIELD_eventType
        "string",    // FIELD_messageSignature
        "string",    // FIELD_sigmaSerialized
        "unsigned int",    // FIELD_filterEpochAtSigning
        "string",    // FIELD_clusterId
        "bool",    // FIELD_isMalicious
    };
    return (field >= 0 && field < 11) ? fieldTypeStrings[field] : nullptr;
}

const char **SafetyMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SafetyMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SafetyMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SafetyMsg *pp = omnetpp::fromAnyPtr<SafetyMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SafetyMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SafetyMsg *pp = omnetpp::fromAnyPtr<SafetyMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SafetyMsg'", field);
    }
}

const char *SafetyMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SafetyMsg *pp = omnetpp::fromAnyPtr<SafetyMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SafetyMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SafetyMsg *pp = omnetpp::fromAnyPtr<SafetyMsg>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: return oppstring2string(pp->getSenderId());
        case FIELD_speed: return double2string(pp->getSpeed());
        case FIELD_posX: return double2string(pp->getPosX());
        case FIELD_posY: return double2string(pp->getPosY());
        case FIELD_heading: return double2string(pp->getHeading());
        case FIELD_eventType: return oppstring2string(pp->getEventType());
        case FIELD_messageSignature: return oppstring2string(pp->getMessageSignature());
        case FIELD_sigmaSerialized: return oppstring2string(pp->getSigmaSerialized());
        case FIELD_filterEpochAtSigning: return ulong2string(pp->getFilterEpochAtSigning());
        case FIELD_clusterId: return oppstring2string(pp->getClusterId());
        case FIELD_isMalicious: return bool2string(pp->isMalicious());
        default: return "";
    }
}

void SafetyMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SafetyMsg *pp = omnetpp::fromAnyPtr<SafetyMsg>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: pp->setSenderId((value)); break;
        case FIELD_speed: pp->setSpeed(string2double(value)); break;
        case FIELD_posX: pp->setPosX(string2double(value)); break;
        case FIELD_posY: pp->setPosY(string2double(value)); break;
        case FIELD_heading: pp->setHeading(string2double(value)); break;
        case FIELD_eventType: pp->setEventType((value)); break;
        case FIELD_messageSignature: pp->setMessageSignature((value)); break;
        case FIELD_sigmaSerialized: pp->setSigmaSerialized((value)); break;
        case FIELD_filterEpochAtSigning: pp->setFilterEpochAtSigning(string2ulong(value)); break;
        case FIELD_clusterId: pp->setClusterId((value)); break;
        case FIELD_isMalicious: pp->setIsMalicious(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SafetyMsg'", field);
    }
}

omnetpp::cValue SafetyMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SafetyMsg *pp = omnetpp::fromAnyPtr<SafetyMsg>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: return pp->getSenderId();
        case FIELD_speed: return pp->getSpeed();
        case FIELD_posX: return pp->getPosX();
        case FIELD_posY: return pp->getPosY();
        case FIELD_heading: return pp->getHeading();
        case FIELD_eventType: return pp->getEventType();
        case FIELD_messageSignature: return pp->getMessageSignature();
        case FIELD_sigmaSerialized: return pp->getSigmaSerialized();
        case FIELD_filterEpochAtSigning: return (omnetpp::intval_t)(pp->getFilterEpochAtSigning());
        case FIELD_clusterId: return pp->getClusterId();
        case FIELD_isMalicious: return pp->isMalicious();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SafetyMsg' as cValue -- field index out of range?", field);
    }
}

void SafetyMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SafetyMsg *pp = omnetpp::fromAnyPtr<SafetyMsg>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: pp->setSenderId(value.stringValue()); break;
        case FIELD_speed: pp->setSpeed(value.doubleValue()); break;
        case FIELD_posX: pp->setPosX(value.doubleValue()); break;
        case FIELD_posY: pp->setPosY(value.doubleValue()); break;
        case FIELD_heading: pp->setHeading(value.doubleValue()); break;
        case FIELD_eventType: pp->setEventType(value.stringValue()); break;
        case FIELD_messageSignature: pp->setMessageSignature(value.stringValue()); break;
        case FIELD_sigmaSerialized: pp->setSigmaSerialized(value.stringValue()); break;
        case FIELD_filterEpochAtSigning: pp->setFilterEpochAtSigning(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_clusterId: pp->setClusterId(value.stringValue()); break;
        case FIELD_isMalicious: pp->setIsMalicious(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SafetyMsg'", field);
    }
}

const char *SafetyMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr SafetyMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SafetyMsg *pp = omnetpp::fromAnyPtr<SafetyMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SafetyMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SafetyMsg *pp = omnetpp::fromAnyPtr<SafetyMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SafetyMsg'", field);
    }
}

Register_Class(RevokeProposalMsg)

RevokeProposalMsg::RevokeProposalMsg(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

RevokeProposalMsg::RevokeProposalMsg(const RevokeProposalMsg& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

RevokeProposalMsg::~RevokeProposalMsg()
{
}

RevokeProposalMsg& RevokeProposalMsg::operator=(const RevokeProposalMsg& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void RevokeProposalMsg::copy(const RevokeProposalMsg& other)
{
    this->proposerId = other.proposerId;
    this->suspectPseudonym = other.suspectPseudonym;
    this->suspectH0 = other.suspectH0;
    this->evidence = other.evidence;
    this->epoch = other.epoch;
    this->evidenceScore = other.evidenceScore;
}

void RevokeProposalMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->proposerId);
    doParsimPacking(b,this->suspectPseudonym);
    doParsimPacking(b,this->suspectH0);
    doParsimPacking(b,this->evidence);
    doParsimPacking(b,this->epoch);
    doParsimPacking(b,this->evidenceScore);
}

void RevokeProposalMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->proposerId);
    doParsimUnpacking(b,this->suspectPseudonym);
    doParsimUnpacking(b,this->suspectH0);
    doParsimUnpacking(b,this->evidence);
    doParsimUnpacking(b,this->epoch);
    doParsimUnpacking(b,this->evidenceScore);
}

const char * RevokeProposalMsg::getProposerId() const
{
    return this->proposerId.c_str();
}

void RevokeProposalMsg::setProposerId(const char * proposerId)
{
    this->proposerId = proposerId;
}

const char * RevokeProposalMsg::getSuspectPseudonym() const
{
    return this->suspectPseudonym.c_str();
}

void RevokeProposalMsg::setSuspectPseudonym(const char * suspectPseudonym)
{
    this->suspectPseudonym = suspectPseudonym;
}

const char * RevokeProposalMsg::getSuspectH0() const
{
    return this->suspectH0.c_str();
}

void RevokeProposalMsg::setSuspectH0(const char * suspectH0)
{
    this->suspectH0 = suspectH0;
}

const char * RevokeProposalMsg::getEvidence() const
{
    return this->evidence.c_str();
}

void RevokeProposalMsg::setEvidence(const char * evidence)
{
    this->evidence = evidence;
}

unsigned int RevokeProposalMsg::getEpoch() const
{
    return this->epoch;
}

void RevokeProposalMsg::setEpoch(unsigned int epoch)
{
    this->epoch = epoch;
}

double RevokeProposalMsg::getEvidenceScore() const
{
    return this->evidenceScore;
}

void RevokeProposalMsg::setEvidenceScore(double evidenceScore)
{
    this->evidenceScore = evidenceScore;
}

class RevokeProposalMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_proposerId,
        FIELD_suspectPseudonym,
        FIELD_suspectH0,
        FIELD_evidence,
        FIELD_epoch,
        FIELD_evidenceScore,
    };
  public:
    RevokeProposalMsgDescriptor();
    virtual ~RevokeProposalMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(RevokeProposalMsgDescriptor)

RevokeProposalMsgDescriptor::RevokeProposalMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(swarmevose::RevokeProposalMsg)), "veins::BaseFrame1609_4")
{
    propertyNames = nullptr;
}

RevokeProposalMsgDescriptor::~RevokeProposalMsgDescriptor()
{
    delete[] propertyNames;
}

bool RevokeProposalMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RevokeProposalMsg *>(obj)!=nullptr;
}

const char **RevokeProposalMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RevokeProposalMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RevokeProposalMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 6+base->getFieldCount() : 6;
}

unsigned int RevokeProposalMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_proposerId
        FD_ISEDITABLE,    // FIELD_suspectPseudonym
        FD_ISEDITABLE,    // FIELD_suspectH0
        FD_ISEDITABLE,    // FIELD_evidence
        FD_ISEDITABLE,    // FIELD_epoch
        FD_ISEDITABLE,    // FIELD_evidenceScore
    };
    return (field >= 0 && field < 6) ? fieldTypeFlags[field] : 0;
}

const char *RevokeProposalMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "proposerId",
        "suspectPseudonym",
        "suspectH0",
        "evidence",
        "epoch",
        "evidenceScore",
    };
    return (field >= 0 && field < 6) ? fieldNames[field] : nullptr;
}

int RevokeProposalMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "proposerId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "suspectPseudonym") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "suspectH0") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "evidence") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "epoch") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "evidenceScore") == 0) return baseIndex + 5;
    return base ? base->findField(fieldName) : -1;
}

const char *RevokeProposalMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_proposerId
        "string",    // FIELD_suspectPseudonym
        "string",    // FIELD_suspectH0
        "string",    // FIELD_evidence
        "unsigned int",    // FIELD_epoch
        "double",    // FIELD_evidenceScore
    };
    return (field >= 0 && field < 6) ? fieldTypeStrings[field] : nullptr;
}

const char **RevokeProposalMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RevokeProposalMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RevokeProposalMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RevokeProposalMsg *pp = omnetpp::fromAnyPtr<RevokeProposalMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RevokeProposalMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RevokeProposalMsg *pp = omnetpp::fromAnyPtr<RevokeProposalMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RevokeProposalMsg'", field);
    }
}

const char *RevokeProposalMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RevokeProposalMsg *pp = omnetpp::fromAnyPtr<RevokeProposalMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RevokeProposalMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RevokeProposalMsg *pp = omnetpp::fromAnyPtr<RevokeProposalMsg>(object); (void)pp;
    switch (field) {
        case FIELD_proposerId: return oppstring2string(pp->getProposerId());
        case FIELD_suspectPseudonym: return oppstring2string(pp->getSuspectPseudonym());
        case FIELD_suspectH0: return oppstring2string(pp->getSuspectH0());
        case FIELD_evidence: return oppstring2string(pp->getEvidence());
        case FIELD_epoch: return ulong2string(pp->getEpoch());
        case FIELD_evidenceScore: return double2string(pp->getEvidenceScore());
        default: return "";
    }
}

void RevokeProposalMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RevokeProposalMsg *pp = omnetpp::fromAnyPtr<RevokeProposalMsg>(object); (void)pp;
    switch (field) {
        case FIELD_proposerId: pp->setProposerId((value)); break;
        case FIELD_suspectPseudonym: pp->setSuspectPseudonym((value)); break;
        case FIELD_suspectH0: pp->setSuspectH0((value)); break;
        case FIELD_evidence: pp->setEvidence((value)); break;
        case FIELD_epoch: pp->setEpoch(string2ulong(value)); break;
        case FIELD_evidenceScore: pp->setEvidenceScore(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RevokeProposalMsg'", field);
    }
}

omnetpp::cValue RevokeProposalMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RevokeProposalMsg *pp = omnetpp::fromAnyPtr<RevokeProposalMsg>(object); (void)pp;
    switch (field) {
        case FIELD_proposerId: return pp->getProposerId();
        case FIELD_suspectPseudonym: return pp->getSuspectPseudonym();
        case FIELD_suspectH0: return pp->getSuspectH0();
        case FIELD_evidence: return pp->getEvidence();
        case FIELD_epoch: return (omnetpp::intval_t)(pp->getEpoch());
        case FIELD_evidenceScore: return pp->getEvidenceScore();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RevokeProposalMsg' as cValue -- field index out of range?", field);
    }
}

void RevokeProposalMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RevokeProposalMsg *pp = omnetpp::fromAnyPtr<RevokeProposalMsg>(object); (void)pp;
    switch (field) {
        case FIELD_proposerId: pp->setProposerId(value.stringValue()); break;
        case FIELD_suspectPseudonym: pp->setSuspectPseudonym(value.stringValue()); break;
        case FIELD_suspectH0: pp->setSuspectH0(value.stringValue()); break;
        case FIELD_evidence: pp->setEvidence(value.stringValue()); break;
        case FIELD_epoch: pp->setEpoch(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_evidenceScore: pp->setEvidenceScore(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RevokeProposalMsg'", field);
    }
}

const char *RevokeProposalMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr RevokeProposalMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RevokeProposalMsg *pp = omnetpp::fromAnyPtr<RevokeProposalMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RevokeProposalMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RevokeProposalMsg *pp = omnetpp::fromAnyPtr<RevokeProposalMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RevokeProposalMsg'", field);
    }
}

Register_Class(RevokeVoteMsg)

RevokeVoteMsg::RevokeVoteMsg(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

RevokeVoteMsg::RevokeVoteMsg(const RevokeVoteMsg& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

RevokeVoteMsg::~RevokeVoteMsg()
{
}

RevokeVoteMsg& RevokeVoteMsg::operator=(const RevokeVoteMsg& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void RevokeVoteMsg::copy(const RevokeVoteMsg& other)
{
    this->voterId = other.voterId;
    this->suspectPseudonym = other.suspectPseudonym;
    this->partialSigBytes = other.partialSigBytes;
    this->epoch = other.epoch;
    this->vote = other.vote;
}

void RevokeVoteMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->voterId);
    doParsimPacking(b,this->suspectPseudonym);
    doParsimPacking(b,this->partialSigBytes);
    doParsimPacking(b,this->epoch);
    doParsimPacking(b,this->vote);
}

void RevokeVoteMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->voterId);
    doParsimUnpacking(b,this->suspectPseudonym);
    doParsimUnpacking(b,this->partialSigBytes);
    doParsimUnpacking(b,this->epoch);
    doParsimUnpacking(b,this->vote);
}

const char * RevokeVoteMsg::getVoterId() const
{
    return this->voterId.c_str();
}

void RevokeVoteMsg::setVoterId(const char * voterId)
{
    this->voterId = voterId;
}

const char * RevokeVoteMsg::getSuspectPseudonym() const
{
    return this->suspectPseudonym.c_str();
}

void RevokeVoteMsg::setSuspectPseudonym(const char * suspectPseudonym)
{
    this->suspectPseudonym = suspectPseudonym;
}

const char * RevokeVoteMsg::getPartialSigBytes() const
{
    return this->partialSigBytes.c_str();
}

void RevokeVoteMsg::setPartialSigBytes(const char * partialSigBytes)
{
    this->partialSigBytes = partialSigBytes;
}

unsigned int RevokeVoteMsg::getEpoch() const
{
    return this->epoch;
}

void RevokeVoteMsg::setEpoch(unsigned int epoch)
{
    this->epoch = epoch;
}

bool RevokeVoteMsg::getVote() const
{
    return this->vote;
}

void RevokeVoteMsg::setVote(bool vote)
{
    this->vote = vote;
}

class RevokeVoteMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_voterId,
        FIELD_suspectPseudonym,
        FIELD_partialSigBytes,
        FIELD_epoch,
        FIELD_vote,
    };
  public:
    RevokeVoteMsgDescriptor();
    virtual ~RevokeVoteMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(RevokeVoteMsgDescriptor)

RevokeVoteMsgDescriptor::RevokeVoteMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(swarmevose::RevokeVoteMsg)), "veins::BaseFrame1609_4")
{
    propertyNames = nullptr;
}

RevokeVoteMsgDescriptor::~RevokeVoteMsgDescriptor()
{
    delete[] propertyNames;
}

bool RevokeVoteMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<RevokeVoteMsg *>(obj)!=nullptr;
}

const char **RevokeVoteMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *RevokeVoteMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int RevokeVoteMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int RevokeVoteMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_voterId
        FD_ISEDITABLE,    // FIELD_suspectPseudonym
        FD_ISEDITABLE,    // FIELD_partialSigBytes
        FD_ISEDITABLE,    // FIELD_epoch
        FD_ISEDITABLE,    // FIELD_vote
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *RevokeVoteMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "voterId",
        "suspectPseudonym",
        "partialSigBytes",
        "epoch",
        "vote",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int RevokeVoteMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "voterId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "suspectPseudonym") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "partialSigBytes") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "epoch") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "vote") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *RevokeVoteMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_voterId
        "string",    // FIELD_suspectPseudonym
        "string",    // FIELD_partialSigBytes
        "unsigned int",    // FIELD_epoch
        "bool",    // FIELD_vote
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **RevokeVoteMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *RevokeVoteMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int RevokeVoteMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    RevokeVoteMsg *pp = omnetpp::fromAnyPtr<RevokeVoteMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void RevokeVoteMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    RevokeVoteMsg *pp = omnetpp::fromAnyPtr<RevokeVoteMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'RevokeVoteMsg'", field);
    }
}

const char *RevokeVoteMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    RevokeVoteMsg *pp = omnetpp::fromAnyPtr<RevokeVoteMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string RevokeVoteMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    RevokeVoteMsg *pp = omnetpp::fromAnyPtr<RevokeVoteMsg>(object); (void)pp;
    switch (field) {
        case FIELD_voterId: return oppstring2string(pp->getVoterId());
        case FIELD_suspectPseudonym: return oppstring2string(pp->getSuspectPseudonym());
        case FIELD_partialSigBytes: return oppstring2string(pp->getPartialSigBytes());
        case FIELD_epoch: return ulong2string(pp->getEpoch());
        case FIELD_vote: return bool2string(pp->getVote());
        default: return "";
    }
}

void RevokeVoteMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RevokeVoteMsg *pp = omnetpp::fromAnyPtr<RevokeVoteMsg>(object); (void)pp;
    switch (field) {
        case FIELD_voterId: pp->setVoterId((value)); break;
        case FIELD_suspectPseudonym: pp->setSuspectPseudonym((value)); break;
        case FIELD_partialSigBytes: pp->setPartialSigBytes((value)); break;
        case FIELD_epoch: pp->setEpoch(string2ulong(value)); break;
        case FIELD_vote: pp->setVote(string2bool(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RevokeVoteMsg'", field);
    }
}

omnetpp::cValue RevokeVoteMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    RevokeVoteMsg *pp = omnetpp::fromAnyPtr<RevokeVoteMsg>(object); (void)pp;
    switch (field) {
        case FIELD_voterId: return pp->getVoterId();
        case FIELD_suspectPseudonym: return pp->getSuspectPseudonym();
        case FIELD_partialSigBytes: return pp->getPartialSigBytes();
        case FIELD_epoch: return (omnetpp::intval_t)(pp->getEpoch());
        case FIELD_vote: return pp->getVote();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'RevokeVoteMsg' as cValue -- field index out of range?", field);
    }
}

void RevokeVoteMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    RevokeVoteMsg *pp = omnetpp::fromAnyPtr<RevokeVoteMsg>(object); (void)pp;
    switch (field) {
        case FIELD_voterId: pp->setVoterId(value.stringValue()); break;
        case FIELD_suspectPseudonym: pp->setSuspectPseudonym(value.stringValue()); break;
        case FIELD_partialSigBytes: pp->setPartialSigBytes(value.stringValue()); break;
        case FIELD_epoch: pp->setEpoch(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_vote: pp->setVote(value.boolValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RevokeVoteMsg'", field);
    }
}

const char *RevokeVoteMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr RevokeVoteMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    RevokeVoteMsg *pp = omnetpp::fromAnyPtr<RevokeVoteMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void RevokeVoteMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    RevokeVoteMsg *pp = omnetpp::fromAnyPtr<RevokeVoteMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'RevokeVoteMsg'", field);
    }
}

Register_Class(SignedAcfUpdateMsg)

SignedAcfUpdateMsg::SignedAcfUpdateMsg(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

SignedAcfUpdateMsg::SignedAcfUpdateMsg(const SignedAcfUpdateMsg& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

SignedAcfUpdateMsg::~SignedAcfUpdateMsg()
{
}

SignedAcfUpdateMsg& SignedAcfUpdateMsg::operator=(const SignedAcfUpdateMsg& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void SignedAcfUpdateMsg::copy(const SignedAcfUpdateMsg& other)
{
    this->revokedFingerprint = other.revokedFingerprint;
    this->sigmaSerialized = other.sigmaSerialized;
    this->newEpoch = other.newEpoch;
    this->clusterId = other.clusterId;
    this->stateHash = other.stateHash;
}

void SignedAcfUpdateMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->revokedFingerprint);
    doParsimPacking(b,this->sigmaSerialized);
    doParsimPacking(b,this->newEpoch);
    doParsimPacking(b,this->clusterId);
    doParsimPacking(b,this->stateHash);
}

void SignedAcfUpdateMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->revokedFingerprint);
    doParsimUnpacking(b,this->sigmaSerialized);
    doParsimUnpacking(b,this->newEpoch);
    doParsimUnpacking(b,this->clusterId);
    doParsimUnpacking(b,this->stateHash);
}

const char * SignedAcfUpdateMsg::getRevokedFingerprint() const
{
    return this->revokedFingerprint.c_str();
}

void SignedAcfUpdateMsg::setRevokedFingerprint(const char * revokedFingerprint)
{
    this->revokedFingerprint = revokedFingerprint;
}

const char * SignedAcfUpdateMsg::getSigmaSerialized() const
{
    return this->sigmaSerialized.c_str();
}

void SignedAcfUpdateMsg::setSigmaSerialized(const char * sigmaSerialized)
{
    this->sigmaSerialized = sigmaSerialized;
}

unsigned int SignedAcfUpdateMsg::getNewEpoch() const
{
    return this->newEpoch;
}

void SignedAcfUpdateMsg::setNewEpoch(unsigned int newEpoch)
{
    this->newEpoch = newEpoch;
}

const char * SignedAcfUpdateMsg::getClusterId() const
{
    return this->clusterId.c_str();
}

void SignedAcfUpdateMsg::setClusterId(const char * clusterId)
{
    this->clusterId = clusterId;
}

const char * SignedAcfUpdateMsg::getStateHash() const
{
    return this->stateHash.c_str();
}

void SignedAcfUpdateMsg::setStateHash(const char * stateHash)
{
    this->stateHash = stateHash;
}

class SignedAcfUpdateMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_revokedFingerprint,
        FIELD_sigmaSerialized,
        FIELD_newEpoch,
        FIELD_clusterId,
        FIELD_stateHash,
    };
  public:
    SignedAcfUpdateMsgDescriptor();
    virtual ~SignedAcfUpdateMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(SignedAcfUpdateMsgDescriptor)

SignedAcfUpdateMsgDescriptor::SignedAcfUpdateMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(swarmevose::SignedAcfUpdateMsg)), "veins::BaseFrame1609_4")
{
    propertyNames = nullptr;
}

SignedAcfUpdateMsgDescriptor::~SignedAcfUpdateMsgDescriptor()
{
    delete[] propertyNames;
}

bool SignedAcfUpdateMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SignedAcfUpdateMsg *>(obj)!=nullptr;
}

const char **SignedAcfUpdateMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SignedAcfUpdateMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SignedAcfUpdateMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 5+base->getFieldCount() : 5;
}

unsigned int SignedAcfUpdateMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_revokedFingerprint
        FD_ISEDITABLE,    // FIELD_sigmaSerialized
        FD_ISEDITABLE,    // FIELD_newEpoch
        FD_ISEDITABLE,    // FIELD_clusterId
        FD_ISEDITABLE,    // FIELD_stateHash
    };
    return (field >= 0 && field < 5) ? fieldTypeFlags[field] : 0;
}

const char *SignedAcfUpdateMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "revokedFingerprint",
        "sigmaSerialized",
        "newEpoch",
        "clusterId",
        "stateHash",
    };
    return (field >= 0 && field < 5) ? fieldNames[field] : nullptr;
}

int SignedAcfUpdateMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "revokedFingerprint") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "sigmaSerialized") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "newEpoch") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "clusterId") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "stateHash") == 0) return baseIndex + 4;
    return base ? base->findField(fieldName) : -1;
}

const char *SignedAcfUpdateMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_revokedFingerprint
        "string",    // FIELD_sigmaSerialized
        "unsigned int",    // FIELD_newEpoch
        "string",    // FIELD_clusterId
        "string",    // FIELD_stateHash
    };
    return (field >= 0 && field < 5) ? fieldTypeStrings[field] : nullptr;
}

const char **SignedAcfUpdateMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SignedAcfUpdateMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SignedAcfUpdateMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SignedAcfUpdateMsg *pp = omnetpp::fromAnyPtr<SignedAcfUpdateMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SignedAcfUpdateMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SignedAcfUpdateMsg *pp = omnetpp::fromAnyPtr<SignedAcfUpdateMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SignedAcfUpdateMsg'", field);
    }
}

const char *SignedAcfUpdateMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SignedAcfUpdateMsg *pp = omnetpp::fromAnyPtr<SignedAcfUpdateMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SignedAcfUpdateMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SignedAcfUpdateMsg *pp = omnetpp::fromAnyPtr<SignedAcfUpdateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_revokedFingerprint: return oppstring2string(pp->getRevokedFingerprint());
        case FIELD_sigmaSerialized: return oppstring2string(pp->getSigmaSerialized());
        case FIELD_newEpoch: return ulong2string(pp->getNewEpoch());
        case FIELD_clusterId: return oppstring2string(pp->getClusterId());
        case FIELD_stateHash: return oppstring2string(pp->getStateHash());
        default: return "";
    }
}

void SignedAcfUpdateMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignedAcfUpdateMsg *pp = omnetpp::fromAnyPtr<SignedAcfUpdateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_revokedFingerprint: pp->setRevokedFingerprint((value)); break;
        case FIELD_sigmaSerialized: pp->setSigmaSerialized((value)); break;
        case FIELD_newEpoch: pp->setNewEpoch(string2ulong(value)); break;
        case FIELD_clusterId: pp->setClusterId((value)); break;
        case FIELD_stateHash: pp->setStateHash((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignedAcfUpdateMsg'", field);
    }
}

omnetpp::cValue SignedAcfUpdateMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SignedAcfUpdateMsg *pp = omnetpp::fromAnyPtr<SignedAcfUpdateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_revokedFingerprint: return pp->getRevokedFingerprint();
        case FIELD_sigmaSerialized: return pp->getSigmaSerialized();
        case FIELD_newEpoch: return (omnetpp::intval_t)(pp->getNewEpoch());
        case FIELD_clusterId: return pp->getClusterId();
        case FIELD_stateHash: return pp->getStateHash();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SignedAcfUpdateMsg' as cValue -- field index out of range?", field);
    }
}

void SignedAcfUpdateMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SignedAcfUpdateMsg *pp = omnetpp::fromAnyPtr<SignedAcfUpdateMsg>(object); (void)pp;
    switch (field) {
        case FIELD_revokedFingerprint: pp->setRevokedFingerprint(value.stringValue()); break;
        case FIELD_sigmaSerialized: pp->setSigmaSerialized(value.stringValue()); break;
        case FIELD_newEpoch: pp->setNewEpoch(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_clusterId: pp->setClusterId(value.stringValue()); break;
        case FIELD_stateHash: pp->setStateHash(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignedAcfUpdateMsg'", field);
    }
}

const char *SignedAcfUpdateMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr SignedAcfUpdateMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SignedAcfUpdateMsg *pp = omnetpp::fromAnyPtr<SignedAcfUpdateMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SignedAcfUpdateMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SignedAcfUpdateMsg *pp = omnetpp::fromAnyPtr<SignedAcfUpdateMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SignedAcfUpdateMsg'", field);
    }
}

Register_Class(ClusterTransitionCertMsg)

ClusterTransitionCertMsg::ClusterTransitionCertMsg(const char *name, short kind) : ::veins::BaseFrame1609_4(name, kind)
{
}

ClusterTransitionCertMsg::ClusterTransitionCertMsg(const ClusterTransitionCertMsg& other) : ::veins::BaseFrame1609_4(other)
{
    copy(other);
}

ClusterTransitionCertMsg::~ClusterTransitionCertMsg()
{
}

ClusterTransitionCertMsg& ClusterTransitionCertMsg::operator=(const ClusterTransitionCertMsg& other)
{
    if (this == &other) return *this;
    ::veins::BaseFrame1609_4::operator=(other);
    copy(other);
    return *this;
}

void ClusterTransitionCertMsg::copy(const ClusterTransitionCertMsg& other)
{
    this->vehiclePseudonym = other.vehiclePseudonym;
    this->vehicleH0 = other.vehicleH0;
    this->outgoingClusterId = other.outgoingClusterId;
    this->sigmaSerialized = other.sigmaSerialized;
    this->epoch = other.epoch;
    this->issuedAtX = other.issuedAtX;
    this->issuedAtY = other.issuedAtY;
}

void ClusterTransitionCertMsg::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::veins::BaseFrame1609_4::parsimPack(b);
    doParsimPacking(b,this->vehiclePseudonym);
    doParsimPacking(b,this->vehicleH0);
    doParsimPacking(b,this->outgoingClusterId);
    doParsimPacking(b,this->sigmaSerialized);
    doParsimPacking(b,this->epoch);
    doParsimPacking(b,this->issuedAtX);
    doParsimPacking(b,this->issuedAtY);
}

void ClusterTransitionCertMsg::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::veins::BaseFrame1609_4::parsimUnpack(b);
    doParsimUnpacking(b,this->vehiclePseudonym);
    doParsimUnpacking(b,this->vehicleH0);
    doParsimUnpacking(b,this->outgoingClusterId);
    doParsimUnpacking(b,this->sigmaSerialized);
    doParsimUnpacking(b,this->epoch);
    doParsimUnpacking(b,this->issuedAtX);
    doParsimUnpacking(b,this->issuedAtY);
}

const char * ClusterTransitionCertMsg::getVehiclePseudonym() const
{
    return this->vehiclePseudonym.c_str();
}

void ClusterTransitionCertMsg::setVehiclePseudonym(const char * vehiclePseudonym)
{
    this->vehiclePseudonym = vehiclePseudonym;
}

const char * ClusterTransitionCertMsg::getVehicleH0() const
{
    return this->vehicleH0.c_str();
}

void ClusterTransitionCertMsg::setVehicleH0(const char * vehicleH0)
{
    this->vehicleH0 = vehicleH0;
}

const char * ClusterTransitionCertMsg::getOutgoingClusterId() const
{
    return this->outgoingClusterId.c_str();
}

void ClusterTransitionCertMsg::setOutgoingClusterId(const char * outgoingClusterId)
{
    this->outgoingClusterId = outgoingClusterId;
}

const char * ClusterTransitionCertMsg::getSigmaSerialized() const
{
    return this->sigmaSerialized.c_str();
}

void ClusterTransitionCertMsg::setSigmaSerialized(const char * sigmaSerialized)
{
    this->sigmaSerialized = sigmaSerialized;
}

unsigned int ClusterTransitionCertMsg::getEpoch() const
{
    return this->epoch;
}

void ClusterTransitionCertMsg::setEpoch(unsigned int epoch)
{
    this->epoch = epoch;
}

double ClusterTransitionCertMsg::getIssuedAtX() const
{
    return this->issuedAtX;
}

void ClusterTransitionCertMsg::setIssuedAtX(double issuedAtX)
{
    this->issuedAtX = issuedAtX;
}

double ClusterTransitionCertMsg::getIssuedAtY() const
{
    return this->issuedAtY;
}

void ClusterTransitionCertMsg::setIssuedAtY(double issuedAtY)
{
    this->issuedAtY = issuedAtY;
}

class ClusterTransitionCertMsgDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_vehiclePseudonym,
        FIELD_vehicleH0,
        FIELD_outgoingClusterId,
        FIELD_sigmaSerialized,
        FIELD_epoch,
        FIELD_issuedAtX,
        FIELD_issuedAtY,
    };
  public:
    ClusterTransitionCertMsgDescriptor();
    virtual ~ClusterTransitionCertMsgDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ClusterTransitionCertMsgDescriptor)

ClusterTransitionCertMsgDescriptor::ClusterTransitionCertMsgDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(swarmevose::ClusterTransitionCertMsg)), "veins::BaseFrame1609_4")
{
    propertyNames = nullptr;
}

ClusterTransitionCertMsgDescriptor::~ClusterTransitionCertMsgDescriptor()
{
    delete[] propertyNames;
}

bool ClusterTransitionCertMsgDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ClusterTransitionCertMsg *>(obj)!=nullptr;
}

const char **ClusterTransitionCertMsgDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ClusterTransitionCertMsgDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ClusterTransitionCertMsgDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 7+base->getFieldCount() : 7;
}

unsigned int ClusterTransitionCertMsgDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_vehiclePseudonym
        FD_ISEDITABLE,    // FIELD_vehicleH0
        FD_ISEDITABLE,    // FIELD_outgoingClusterId
        FD_ISEDITABLE,    // FIELD_sigmaSerialized
        FD_ISEDITABLE,    // FIELD_epoch
        FD_ISEDITABLE,    // FIELD_issuedAtX
        FD_ISEDITABLE,    // FIELD_issuedAtY
    };
    return (field >= 0 && field < 7) ? fieldTypeFlags[field] : 0;
}

const char *ClusterTransitionCertMsgDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "vehiclePseudonym",
        "vehicleH0",
        "outgoingClusterId",
        "sigmaSerialized",
        "epoch",
        "issuedAtX",
        "issuedAtY",
    };
    return (field >= 0 && field < 7) ? fieldNames[field] : nullptr;
}

int ClusterTransitionCertMsgDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "vehiclePseudonym") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "vehicleH0") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "outgoingClusterId") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "sigmaSerialized") == 0) return baseIndex + 3;
    if (strcmp(fieldName, "epoch") == 0) return baseIndex + 4;
    if (strcmp(fieldName, "issuedAtX") == 0) return baseIndex + 5;
    if (strcmp(fieldName, "issuedAtY") == 0) return baseIndex + 6;
    return base ? base->findField(fieldName) : -1;
}

const char *ClusterTransitionCertMsgDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "string",    // FIELD_vehiclePseudonym
        "string",    // FIELD_vehicleH0
        "string",    // FIELD_outgoingClusterId
        "string",    // FIELD_sigmaSerialized
        "unsigned int",    // FIELD_epoch
        "double",    // FIELD_issuedAtX
        "double",    // FIELD_issuedAtY
    };
    return (field >= 0 && field < 7) ? fieldTypeStrings[field] : nullptr;
}

const char **ClusterTransitionCertMsgDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ClusterTransitionCertMsgDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ClusterTransitionCertMsgDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ClusterTransitionCertMsg *pp = omnetpp::fromAnyPtr<ClusterTransitionCertMsg>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void ClusterTransitionCertMsgDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ClusterTransitionCertMsg *pp = omnetpp::fromAnyPtr<ClusterTransitionCertMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ClusterTransitionCertMsg'", field);
    }
}

const char *ClusterTransitionCertMsgDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ClusterTransitionCertMsg *pp = omnetpp::fromAnyPtr<ClusterTransitionCertMsg>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ClusterTransitionCertMsgDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ClusterTransitionCertMsg *pp = omnetpp::fromAnyPtr<ClusterTransitionCertMsg>(object); (void)pp;
    switch (field) {
        case FIELD_vehiclePseudonym: return oppstring2string(pp->getVehiclePseudonym());
        case FIELD_vehicleH0: return oppstring2string(pp->getVehicleH0());
        case FIELD_outgoingClusterId: return oppstring2string(pp->getOutgoingClusterId());
        case FIELD_sigmaSerialized: return oppstring2string(pp->getSigmaSerialized());
        case FIELD_epoch: return ulong2string(pp->getEpoch());
        case FIELD_issuedAtX: return double2string(pp->getIssuedAtX());
        case FIELD_issuedAtY: return double2string(pp->getIssuedAtY());
        default: return "";
    }
}

void ClusterTransitionCertMsgDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ClusterTransitionCertMsg *pp = omnetpp::fromAnyPtr<ClusterTransitionCertMsg>(object); (void)pp;
    switch (field) {
        case FIELD_vehiclePseudonym: pp->setVehiclePseudonym((value)); break;
        case FIELD_vehicleH0: pp->setVehicleH0((value)); break;
        case FIELD_outgoingClusterId: pp->setOutgoingClusterId((value)); break;
        case FIELD_sigmaSerialized: pp->setSigmaSerialized((value)); break;
        case FIELD_epoch: pp->setEpoch(string2ulong(value)); break;
        case FIELD_issuedAtX: pp->setIssuedAtX(string2double(value)); break;
        case FIELD_issuedAtY: pp->setIssuedAtY(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ClusterTransitionCertMsg'", field);
    }
}

omnetpp::cValue ClusterTransitionCertMsgDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ClusterTransitionCertMsg *pp = omnetpp::fromAnyPtr<ClusterTransitionCertMsg>(object); (void)pp;
    switch (field) {
        case FIELD_vehiclePseudonym: return pp->getVehiclePseudonym();
        case FIELD_vehicleH0: return pp->getVehicleH0();
        case FIELD_outgoingClusterId: return pp->getOutgoingClusterId();
        case FIELD_sigmaSerialized: return pp->getSigmaSerialized();
        case FIELD_epoch: return (omnetpp::intval_t)(pp->getEpoch());
        case FIELD_issuedAtX: return pp->getIssuedAtX();
        case FIELD_issuedAtY: return pp->getIssuedAtY();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ClusterTransitionCertMsg' as cValue -- field index out of range?", field);
    }
}

void ClusterTransitionCertMsgDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ClusterTransitionCertMsg *pp = omnetpp::fromAnyPtr<ClusterTransitionCertMsg>(object); (void)pp;
    switch (field) {
        case FIELD_vehiclePseudonym: pp->setVehiclePseudonym(value.stringValue()); break;
        case FIELD_vehicleH0: pp->setVehicleH0(value.stringValue()); break;
        case FIELD_outgoingClusterId: pp->setOutgoingClusterId(value.stringValue()); break;
        case FIELD_sigmaSerialized: pp->setSigmaSerialized(value.stringValue()); break;
        case FIELD_epoch: pp->setEpoch(omnetpp::checked_int_cast<unsigned int>(value.intValue())); break;
        case FIELD_issuedAtX: pp->setIssuedAtX(value.doubleValue()); break;
        case FIELD_issuedAtY: pp->setIssuedAtY(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ClusterTransitionCertMsg'", field);
    }
}

const char *ClusterTransitionCertMsgDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ClusterTransitionCertMsgDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ClusterTransitionCertMsg *pp = omnetpp::fromAnyPtr<ClusterTransitionCertMsg>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ClusterTransitionCertMsgDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ClusterTransitionCertMsg *pp = omnetpp::fromAnyPtr<ClusterTransitionCertMsg>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ClusterTransitionCertMsg'", field);
    }
}

}  // namespace swarmevose

namespace omnetpp {

}  // namespace omnetpp

