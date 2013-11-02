/**
 * Autogenerated by Thrift Compiler (0.9.1)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#include "aether_types.h"

#include <algorithm>



const char* ServiceUnavailable::ascii_fingerprint = "3F5FC93B338687BC7235B1AB103F47B3";
const uint8_t ServiceUnavailable::binary_fingerprint[16] = {0x3F,0x5F,0xC9,0x3B,0x33,0x86,0x87,0xBC,0x72,0x35,0xB1,0xAB,0x10,0x3F,0x47,0xB3};

uint32_t ServiceUnavailable::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_I32) {
          xfer += iprot->readI32(this->error_code);
          this->__isset.error_code = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_STRING) {
          xfer += iprot->readString(this->error_message);
          this->__isset.error_message = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t ServiceUnavailable::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("ServiceUnavailable");

  xfer += oprot->writeFieldBegin("error_code", ::apache::thrift::protocol::T_I32, 1);
  xfer += oprot->writeI32(this->error_code);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("error_message", ::apache::thrift::protocol::T_STRING, 2);
  xfer += oprot->writeString(this->error_message);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(ServiceUnavailable &a, ServiceUnavailable &b) {
  using ::std::swap;
  swap(a.error_code, b.error_code);
  swap(a.error_message, b.error_message);
  swap(a.__isset, b.__isset);
}

const char* Vector::ascii_fingerprint = "EFFAD640FBA2CA56C50155B2A4545897";
const uint8_t Vector::binary_fingerprint[16] = {0xEF,0xFA,0xD6,0x40,0xFB,0xA2,0xCA,0x56,0xC5,0x01,0x55,0xB2,0xA4,0x54,0x58,0x97};

uint32_t Vector::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->x);
          this->__isset.x = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 2:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->y);
          this->__isset.y = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      case 3:
        if (ftype == ::apache::thrift::protocol::T_DOUBLE) {
          xfer += iprot->readDouble(this->z);
          this->__isset.z = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Vector::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("Vector");

  xfer += oprot->writeFieldBegin("x", ::apache::thrift::protocol::T_DOUBLE, 1);
  xfer += oprot->writeDouble(this->x);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("y", ::apache::thrift::protocol::T_DOUBLE, 2);
  xfer += oprot->writeDouble(this->y);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldBegin("z", ::apache::thrift::protocol::T_DOUBLE, 3);
  xfer += oprot->writeDouble(this->z);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Vector &a, Vector &b) {
  using ::std::swap;
  swap(a.x, b.x);
  swap(a.y, b.y);
  swap(a.z, b.z);
  swap(a.__isset, b.__isset);
}

const char* Moxel::ascii_fingerprint = "4FE4B4C8952003BE2B266957AF72F8B4";
const uint8_t Moxel::binary_fingerprint[16] = {0x4F,0xE4,0xB4,0xC8,0x95,0x20,0x03,0xBE,0x2B,0x26,0x69,0x57,0xAF,0x72,0xF8,0xB4};

uint32_t Moxel::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_STRUCT) {
          xfer += this->position.read(iprot);
          this->__isset.position = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Moxel::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("Moxel");

  xfer += oprot->writeFieldBegin("position", ::apache::thrift::protocol::T_STRUCT, 1);
  xfer += this->position.write(oprot);
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Moxel &a, Moxel &b) {
  using ::std::swap;
  swap(a.position, b.position);
  swap(a.__isset, b.__isset);
}

const char* Space::ascii_fingerprint = "25A3CDDFF8FCED7F1C79B8F32C3AAAD9";
const uint8_t Space::binary_fingerprint[16] = {0x25,0xA3,0xCD,0xDF,0xF8,0xFC,0xED,0x7F,0x1C,0x79,0xB8,0xF3,0x2C,0x3A,0xAA,0xD9};

uint32_t Space::read(::apache::thrift::protocol::TProtocol* iprot) {

  uint32_t xfer = 0;
  std::string fname;
  ::apache::thrift::protocol::TType ftype;
  int16_t fid;

  xfer += iprot->readStructBegin(fname);

  using ::apache::thrift::protocol::TProtocolException;


  while (true)
  {
    xfer += iprot->readFieldBegin(fname, ftype, fid);
    if (ftype == ::apache::thrift::protocol::T_STOP) {
      break;
    }
    switch (fid)
    {
      case 1:
        if (ftype == ::apache::thrift::protocol::T_LIST) {
          {
            this->moxels.clear();
            uint32_t _size0;
            ::apache::thrift::protocol::TType _etype3;
            xfer += iprot->readListBegin(_etype3, _size0);
            this->moxels.resize(_size0);
            uint32_t _i4;
            for (_i4 = 0; _i4 < _size0; ++_i4)
            {
              xfer += this->moxels[_i4].read(iprot);
            }
            xfer += iprot->readListEnd();
          }
          this->__isset.moxels = true;
        } else {
          xfer += iprot->skip(ftype);
        }
        break;
      default:
        xfer += iprot->skip(ftype);
        break;
    }
    xfer += iprot->readFieldEnd();
  }

  xfer += iprot->readStructEnd();

  return xfer;
}

uint32_t Space::write(::apache::thrift::protocol::TProtocol* oprot) const {
  uint32_t xfer = 0;
  xfer += oprot->writeStructBegin("Space");

  xfer += oprot->writeFieldBegin("moxels", ::apache::thrift::protocol::T_LIST, 1);
  {
    xfer += oprot->writeListBegin(::apache::thrift::protocol::T_STRUCT, static_cast<uint32_t>(this->moxels.size()));
    std::vector<Moxel> ::const_iterator _iter5;
    for (_iter5 = this->moxels.begin(); _iter5 != this->moxels.end(); ++_iter5)
    {
      xfer += (*_iter5).write(oprot);
    }
    xfer += oprot->writeListEnd();
  }
  xfer += oprot->writeFieldEnd();

  xfer += oprot->writeFieldStop();
  xfer += oprot->writeStructEnd();
  return xfer;
}

void swap(Space &a, Space &b) {
  using ::std::swap;
  swap(a.moxels, b.moxels);
  swap(a.__isset, b.__isset);
}


