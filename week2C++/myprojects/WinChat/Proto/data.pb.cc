// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: data.proto

#include "data.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)
namespace chat {
class dataDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<data>
      _instance;
} _data_default_instance_;
}  // namespace chat
namespace protobuf_data_2eproto {
void InitDefaultsdataImpl() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  ::google::protobuf::internal::InitProtobufDefaultsForceUnique();
#else
  ::google::protobuf::internal::InitProtobufDefaults();
#endif  // GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
  {
    void* ptr = &::chat::_data_default_instance_;
    new (ptr) ::chat::data();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::chat::data::InitAsDefaultInstance();
}

void InitDefaultsdata() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &InitDefaultsdataImpl);
}

::google::protobuf::Metadata file_level_metadata[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::chat::data, _has_bits_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::chat::data, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::chat::data, nameinnumber_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::chat::data, name_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::chat::data, str_),
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::chat::data, ins_),
  ~0u,
  0,
  1,
  2,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 9, sizeof(::chat::data)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::chat::_data_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  ::google::protobuf::MessageFactory* factory = NULL;
  AssignDescriptors(
      "data.proto", schemas, file_default_instances, TableStruct::offsets, factory,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\ndata.proto\022\004chat\"D\n\004data\022\024\n\014nameinnumb"
      "er\030\001 \003(\014\022\014\n\004name\030\002 \001(\014\022\013\n\003str\030\003 \001(\014\022\013\n\003i"
      "ns\030\004 \001(\014"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 88);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "data.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static GOOGLE_PROTOBUF_DECLARE_ONCE(once);
  ::google::protobuf::GoogleOnceInit(&once, &AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_data_2eproto
namespace chat {

// ===================================================================

void data::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int data::kNameinnumberFieldNumber;
const int data::kNameFieldNumber;
const int data::kStrFieldNumber;
const int data::kInsFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

data::data()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  if (GOOGLE_PREDICT_TRUE(this != internal_default_instance())) {
    ::protobuf_data_2eproto::InitDefaultsdata();
  }
  SharedCtor();
  // @@protoc_insertion_point(constructor:chat.data)
}
data::data(const data& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      _has_bits_(from._has_bits_),
      _cached_size_(0),
      nameinnumber_(from.nameinnumber_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_name()) {
    name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
  }
  str_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_str()) {
    str_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.str_);
  }
  ins_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_ins()) {
    ins_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.ins_);
  }
  // @@protoc_insertion_point(copy_constructor:chat.data)
}

void data::SharedCtor() {
  _cached_size_ = 0;
  name_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  str_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ins_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

data::~data() {
  // @@protoc_insertion_point(destructor:chat.data)
  SharedDtor();
}

void data::SharedDtor() {
  name_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  str_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  ins_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void data::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* data::descriptor() {
  ::protobuf_data_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_data_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const data& data::default_instance() {
  ::protobuf_data_2eproto::InitDefaultsdata();
  return *internal_default_instance();
}

data* data::New(::google::protobuf::Arena* arena) const {
  data* n = new data;
  if (arena != NULL) {
    arena->Own(n);
  }
  return n;
}

void data::Clear() {
// @@protoc_insertion_point(message_clear_start:chat.data)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  nameinnumber_.Clear();
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 7u) {
    if (cached_has_bits & 0x00000001u) {
      GOOGLE_DCHECK(!name_.IsDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited()));
      (*name_.UnsafeRawStringPointer())->clear();
    }
    if (cached_has_bits & 0x00000002u) {
      GOOGLE_DCHECK(!str_.IsDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited()));
      (*str_.UnsafeRawStringPointer())->clear();
    }
    if (cached_has_bits & 0x00000004u) {
      GOOGLE_DCHECK(!ins_.IsDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited()));
      (*ins_.UnsafeRawStringPointer())->clear();
    }
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

bool data::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:chat.data)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated bytes nameinnumber = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->add_nameinnumber()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bytes name = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(18u /* 18 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_name()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bytes str = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(26u /* 26 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_str()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // optional bytes ins = 4;
      case 4: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(34u /* 34 & 0xFF */)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_ins()));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:chat.data)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:chat.data)
  return false;
#undef DO_
}

void data::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:chat.data)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated bytes nameinnumber = 1;
  for (int i = 0, n = this->nameinnumber_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteBytes(
      1, this->nameinnumber(i), output);
  }

  cached_has_bits = _has_bits_[0];
  // optional bytes name = 2;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      2, this->name(), output);
  }

  // optional bytes str = 3;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      3, this->str(), output);
  }

  // optional bytes ins = 4;
  if (cached_has_bits & 0x00000004u) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      4, this->ins(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:chat.data)
}

::google::protobuf::uint8* data::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:chat.data)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated bytes nameinnumber = 1;
  for (int i = 0, n = this->nameinnumber_size(); i < n; i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteBytesToArray(1, this->nameinnumber(i), target);
  }

  cached_has_bits = _has_bits_[0];
  // optional bytes name = 2;
  if (cached_has_bits & 0x00000001u) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        2, this->name(), target);
  }

  // optional bytes str = 3;
  if (cached_has_bits & 0x00000002u) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        3, this->str(), target);
  }

  // optional bytes ins = 4;
  if (cached_has_bits & 0x00000004u) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        4, this->ins(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:chat.data)
  return target;
}

size_t data::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:chat.data)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  // repeated bytes nameinnumber = 1;
  total_size += 1 *
      ::google::protobuf::internal::FromIntSize(this->nameinnumber_size());
  for (int i = 0, n = this->nameinnumber_size(); i < n; i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::BytesSize(
      this->nameinnumber(i));
  }

  if (_has_bits_[0 / 32] & 7u) {
    // optional bytes name = 2;
    if (has_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->name());
    }

    // optional bytes str = 3;
    if (has_str()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->str());
    }

    // optional bytes ins = 4;
    if (has_ins()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::BytesSize(
          this->ins());
    }

  }
  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = cached_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void data::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:chat.data)
  GOOGLE_DCHECK_NE(&from, this);
  const data* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const data>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:chat.data)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:chat.data)
    MergeFrom(*source);
  }
}

void data::MergeFrom(const data& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:chat.data)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  nameinnumber_.MergeFrom(from.nameinnumber_);
  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 7u) {
    if (cached_has_bits & 0x00000001u) {
      set_has_name();
      name_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.name_);
    }
    if (cached_has_bits & 0x00000002u) {
      set_has_str();
      str_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.str_);
    }
    if (cached_has_bits & 0x00000004u) {
      set_has_ins();
      ins_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.ins_);
    }
  }
}

void data::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:chat.data)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void data::CopyFrom(const data& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:chat.data)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool data::IsInitialized() const {
  return true;
}

void data::Swap(data* other) {
  if (other == this) return;
  InternalSwap(other);
}
void data::InternalSwap(data* other) {
  using std::swap;
  nameinnumber_.InternalSwap(&other->nameinnumber_);
  name_.Swap(&other->name_);
  str_.Swap(&other->str_);
  ins_.Swap(&other->ins_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_cached_size_, other->_cached_size_);
}

::google::protobuf::Metadata data::GetMetadata() const {
  protobuf_data_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_data_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace chat

// @@protoc_insertion_point(global_scope)